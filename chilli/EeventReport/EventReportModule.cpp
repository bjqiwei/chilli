#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <event2/thread.h>

#pragma comment(lib,"ws2_32.lib")

#include "EventReportModule.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/json.h>
#include "../websocket/websocket.h"
#include "../uuid.h"


namespace chilli{
namespace EventReport{

EventReportModule::EventReportModule(const std::string & id) :ProcessModule(id)
{
	log = log4cplus::Logger::getInstance("chilli.EventReportModule");
	LOG4CPLUS_DEBUG(log, this->getId() << " Constuction a EventReport module.");
}


EventReportModule::~EventReportModule(void)
{
	if (m_bRunning){
		Stop();
	}

	LOG4CPLUS_DEBUG(log, this->getId() << " Destruction a EventReport module.");
}

int EventReportModule::Stop(void)
{

	if (m_bRunning){
		ProcessModule::Stop();
		m_bRunning = false;

		if(m_Base)
			event_base_loopexit(m_Base, nullptr);

		for (auto & it : this->m_Threads) {
			if (it.joinable()) {
				it.join();
			}
		}
	}
	m_Threads.clear();
	return 0;
}

int EventReportModule::Start()
{
	
	if(!m_bRunning){
		ProcessModule::Start();
		m_bRunning = true;

		if (this->m_tcpPort !=-1){
			std::thread th(&EventReportModule::listenTCP, this, this->m_tcpPort);
			m_Threads.push_back(std::move(th));
		}

		if (this->m_wsPort != -1){
			std::thread th(&EventReportModule::listenWS, this, this->m_wsPort);
			m_Threads.push_back(std::move(th));
		}

	}
	return 0;
}

bool EventReportModule::LoadConfig(const std::string & configContext)
{
	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if (config.Parse(configContext.c_str()) != XMLError::XML_SUCCESS)
	{
		LOG4CPLUS_ERROR(log, this->getId() << " load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}
	
	tinyxml2::XMLElement * eventreport = config.FirstChildElement();
	eventreport->QueryIntAttribute("TCPPort", &this->m_tcpPort);
	eventreport->QueryIntAttribute("WSPort", &this->m_wsPort);
	if (eventreport->Attribute("WSUrl"))
		this->m_wsUrl = eventreport->Attribute("WSUrl");

	if (m_wsPort == -1)
	{
		const char * prot = nullptr;
		const char *address = nullptr;
		const char *path = nullptr;
		char urlbuff[1024];
		memset(urlbuff, 0, sizeof(urlbuff));
		strncpy_s(urlbuff, m_wsUrl.c_str(), sizeof(urlbuff));
		lws_parse_uri(urlbuff, &prot, &address, &m_wsPort, &path);
	}

	return true;
}


void EventReportModule::processSend(const std::string &strContent, const void * param, bool & bHandled)
{
	Json::Value jsonData;
	Json::Reader jsonReader;
	if (jsonReader.parse(strContent, jsonData)) {

		bHandled = true;

	}
	else {
		LOG4CPLUS_ERROR(log, this->getId() << strContent << " not json data.");
	}
}

void EventReportModule::fireSend(const std::string & strContent, const void * param)
{
	LOG4CPLUS_DEBUG(log, this->getId() << " fireSend:" << strContent);
	bool bHandled = false;
	processSend(strContent, param, bHandled);
}


static void listener_cb(struct evconnlistener *, evutil_socket_t, struct sockaddr *, int socklen, void *);
static void conn_read_cb(struct bufferevent *bev, void *ctx);
static void conn_writecb(struct bufferevent *, void *);
static void conn_eventcb(struct bufferevent *, short, void *);

static void listener_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sa, int socklen, void *user_data)
{
	EventReportModule * This = reinterpret_cast<EventReportModule *>(user_data);

	struct event_base *base = evconnlistener_get_base(listener);
	struct bufferevent *bev;
	
	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE | BEV_OPT_THREADSAFE);
	if (!bev) {
		LOG4CPLUS_ERROR(This->getLogger(), This->getId() << " Error constructing bufferevent!");
		event_base_loopbreak(base);
		return;
	}

	bufferevent_setcb(bev, conn_read_cb, conn_writecb, conn_eventcb, user_data);
	bufferevent_enable(bev, EV_WRITE | EV_READ);
	LOG4CPLUS_DEBUG(This->getLogger(), This->getId() << " accept client:" << bev);

}

static void conn_read_cb(struct bufferevent *bev, void * user_data)
{
	EventReportModule * This = reinterpret_cast<EventReportModule *>(user_data);
	LOG4CPLUS_DEBUG(This->getLogger(), This->getId() << ":" << bev);
	/* This callback is invoked when there is data to read on bev. */
	struct evbuffer *input = bufferevent_get_input(bev);
	struct evbuffer *output = bufferevent_get_output(bev);

	/* Copy all the data from the input buffer to the output buffer. */
	evbuffer_add_buffer(output, input);
}

static void conn_writecb(struct bufferevent *bev, void *user_data)
{
	EventReportModule * This = reinterpret_cast<EventReportModule *>(user_data);

	LOG4CPLUS_DEBUG(This->getLogger(), This->getId() << " write:" << bev);
	struct evbuffer *output = bufferevent_get_output(bev);
	
}

static void conn_eventcb(struct bufferevent *bev, short events, void * user_data)
{
	EventReportModule * This = reinterpret_cast<EventReportModule *>(user_data);

	LOG4CPLUS_DEBUG(This->getLogger(), This->getId() << ":" << bev);
	if (events & BEV_EVENT_ERROR)
		LOG4CPLUS_DEBUG(This->getLogger(), This->getId() << " Error from bufferevent");
	if (events & (BEV_EVENT_EOF | BEV_EVENT_ERROR)) {
		LOG4CPLUS_DEBUG(This->getLogger(), This->getId() << " Connection closed." << bev);
		bufferevent_free(bev);
	}
}

bool EventReportModule::listenTCP(int port)
{
	struct sockaddr_in sin;
	struct evconnlistener *listener;

	LOG4CPLUS_INFO(log, this->getId() << " listen TCP Starting...");
#ifdef WIN32
	evthread_use_windows_threads();
	WSADATA wsa_data;
	WSAStartup(MAKEWORD(2, 2), &wsa_data);
#else
	evthread_use_pthreads();
#endif

	const char ** methods = event_get_supported_methods();
	for (int i = 0; methods[i] != nullptr; ++i) {
		//LOG4CPLUS_INFO(log, this->getId() << ",libevent supported method:" << methods[i]);
	}

	m_Base = event_base_new();
	LOG4CPLUS_INFO(log, this->getId() << ",libevent current method:" <<  event_base_get_method(m_Base));

	if (!m_Base) {
		LOG4CPLUS_ERROR(log, this->getId() << " Could not initialize libevent!");
		goto done;
	}

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(0);
	sin.sin_port = htons(port);

	listener = evconnlistener_new_bind(m_Base, listener_cb, this,
		LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE | LEV_OPT_THREADSAFE, -1,
		(struct sockaddr*)&sin,
		sizeof(sin));

	if (!listener) {
		LOG4CPLUS_ERROR(log, this->getId() << " Could not create a listener!");
		goto done;
	}

	LOG4CPLUS_INFO(log, this->getId() << ",start listen tcp port:" << port);

	while (m_bRunning){
		event_base_dispatch(m_Base);
	}

done:
	if (listener){
		evconnlistener_free(listener);
		listener = nullptr;
	}
	
	if (m_Base){
		event_base_free(m_Base);
		m_Base = nullptr;
	}
	
#ifdef WIN32
	WSACleanup();
#endif
	LOG4CPLUS_INFO(log, this->getId() << " listen TCP Stoped.");
	log4cplus::threadCleanup();
	return true;
}

class EventReportWSConnection :public WebSocket::WSConnection
{
public:
	explicit EventReportWSConnection(struct lws * wsi, model::ProcessModule * module) 
		:WSConnection(wsi),m_module(module)
	{
		this->log = log4cplus::Logger::getInstance("chilli.WSConnection");
		LOG4CPLUS_TRACE(log, m_SessionId << " construction");
	};

	~EventReportWSConnection()
	{
		LOG4CPLUS_TRACE(log, m_SessionId << " deconstruct");
	}

	virtual void OnClose(const std::string & errorCode) override
	{
		delete this;
	};

	virtual void OnError(const std::string & errorCode) override
	{
		
		delete this;
	};

	virtual void OnMessage(const std::string & message) override
	{
		//LOG4CPLUS_DEBUG(log, m_SessionId << " OnMessage:" << message);
		
		Json::Value request;
		Json::Reader jsonReader;
		if (jsonReader.parse(message, request)) {

			std::string requestid;
			if (request["request"].isString())
				requestid = request["request"].asString();

			if (requestid == "heartBeat") {
				Json::Value response;
				response["invokeID"] = request["invokeID"];
				response["type"] = "response";
				response["response"] = "heartBeat";
				response["status"] = 0;
				this->Send(response);
			}
			else {
				LOG4CPLUS_DEBUG(log, m_SessionId << " OnMessage:" << message);
			}

			if (requestid == "connect")
			{
				Json::Value response;
				response["invokeID"] = request["invokeID"];
				response["type"] = "response";
				response["response"] = "connect";
				response["status"] = 0;
				response["param"]["version"] = "1.0.0.0";
				this->Send(response);
			}
			else if (requestid == "disConnect")
			{
				Json::Value response;
				response["invokeID"] = request["invokeID"];
				response["type"] = "response";
				response["response"] = "disConnect";
				response["status"] = 0;
				this->Send(response);
			}
			else if (requestid == "MakeCall")
			{
				std::string calling;
				std::string called;
				Json::Value response;
				response["invokeID"] = request["invokeID"];
				response["type"] = "response";
				response["response"] = "MakeCall";

				if (request["param"]["callingDevice"].isString())
					calling = request["param"]["callingDevice"].asString();
				else {
					response["status"] = 1;
					this->Send(response);
					return;
				}

				if (request["param"]["calledDirectoryNumber"].isString())
					called = request["param"]["calledDirectoryNumber"].asString();
				else {
					response["status"] = 2;
					this->Send(response);
					return;
				}
				response["status"] = 0;
				response["param"]["initiatedCall"]["connectionID"] = uuid();
				response["param"]["initiatedCall"]["callID"] = uuid();
				response["param"]["initiatedCall"]["sessionID"] = uuid();

				this->Send(response);
				request["param"]["initiatedCall"] = response["param"]["initiatedCall"];
				model::EventType_t evt(request);
				m_module->PushEvent(evt);
			}
		}
		else {
			LOG4CPLUS_ERROR(log, m_SessionId << " OnMessage not json string:" << message);
		}

	};

	int Send(Json::Value send) {
		Json::FastWriter writer;
		std::string sendData = writer.write(send);
		return WSConnection::Send(sendData.c_str(), sendData.length());
	}

private:
	model::ProcessModule * m_module;

};

class EventReportWSServer :public WebSocket::WebSocketServer
{
public:
	explicit EventReportWSServer(int port, model::ProcessModule * module)
		:WebSocketServer(port), m_module(module)
	{};
	virtual WebSocket::WSConnection * OnAccept(struct lws *wsi) override
	{
		WebSocket::WSConnection * wsc = new EventReportWSConnection(wsi, m_module);
		return wsc;
	}
private:
	model::ProcessModule * m_module;
};

bool EventReportModule::listenWS(int port)
{
	bool result = true;

	EventReportWSServer wsserver(port, this);
	LOG4CPLUS_INFO(log, this->getId() << ",websocket start listen port:" << port);
	wsserver.InitInstance();

	while (m_bRunning){
		wsserver.Loop(1000);
	}

	wsserver.UnInitInstance();
	log4cplus::threadCleanup();
	return result;
}

void EventReportModule::run()
{
	LOG4CPLUS_INFO(log, this->getId() << " Starting...");
	try
	{

		model::ProcessModulePtr callmodule;
		for (auto & m : model::ProcessModule::g_Modules)
		{
			if (m->getId().find("call") != std::string::npos)
			{
				callmodule = m;
			}
		}

		while (m_bRunning)
		{
			try
			{
				model::EventType_t evt;
				if (m_RecEvtBuffer.Get(evt) && !evt.event.isNull())
				{
					const Json::Value & jsonEvent = evt.event;
					callmodule->PushEvent(evt);
				}
			}
			catch (std::exception & e)
			{
				LOG4CPLUS_ERROR(log, this->getId() << " " << e.what());
			}
		}

	}
	catch (std::exception & e)
	{
		LOG4CPLUS_ERROR(log, this->getId() << " " << e.what());
	}

	LOG4CPLUS_INFO(log, this->getId() << " Stoped.");
	log4cplus::threadCleanup();
}

}
}
