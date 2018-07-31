#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <event2/thread.h>

#pragma comment(lib,"ws2_32.lib")

#include "AgentModule.h"
#include "Agent.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/json.h>
#include "../websocket/websocket.h"
#include "../model/ConnectAdapter.h"


namespace chilli{
namespace Agent{

AgentModule::AgentModule(const std::string & id) :ProcessModule(id)
{
	log = log4cplus::Logger::getInstance("chilli.AgentModule");
	LOG4CPLUS_DEBUG(log, this->getId() << " Constuction a Agent module.");
}


AgentModule::~AgentModule(void)
{
	if (m_bRunning){
		Stop();
	}

	LOG4CPLUS_DEBUG(log, this->getId() << " Destruction a Agent module.");
}

int AgentModule::Stop(void)
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

int AgentModule::Start()
{
	
	if(!m_bRunning){
		ProcessModule::Start();
		m_bRunning = true;

		if (this->m_tcpPort !=-1){
			std::thread th(&AgentModule::listenTCP, this, this->m_tcpPort);
			m_Threads.push_back(std::move(th));
		}

		if (this->m_wsPort != -1){
			std::thread th(&AgentModule::listenWS, this, this->m_wsPort);
			m_Threads.push_back(std::move(th));
		}

	}
	return 0;
}

bool AgentModule::LoadConfig(const std::string & configContext)
{
	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if (config.Parse(configContext.c_str()) != XMLError::XML_SUCCESS)
	{
		LOG4CPLUS_ERROR(log, this->getId() << " load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}
	
	tinyxml2::XMLElement * eAgent = config.FirstChildElement();
	eAgent->QueryIntAttribute("TCPPort", &this->m_tcpPort);
	eAgent->QueryIntAttribute("WSPort", &this->m_wsPort);
	if (eAgent->Attribute("WSUrl"))
		this->m_wsUrl = eAgent->Attribute("WSUrl");

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

	for (XMLElement *child = eAgent->FirstChildElement("Agent");
		child != nullptr;
		child = child->NextSiblingElement("Agent"))
	{

		const char * num = child->Attribute("ExtensionNumber");
		const char * sm = child->Attribute("StateMachine");
		const char * password = child->Attribute("password");
		const char * extension = child->Attribute("Extension");

		num = num ? num : "";
		sm = sm ? sm : "";
		password = password ? password : "";
		extension = extension ? extension : "";

		model::PerformElementPtr ext(new Agent(this, num, sm));
	
		if (ext != nullptr && addPerformElement(num,ext)) {
			ext->setVar("_agent.AgentId", num);
			ext->setVar("_agent.Password", password);
			ext->setVar("_agent.Extension", extension);
		}
		else {
			LOG4CPLUS_ERROR(log, this->getId() << " alredy had agent:" << num);
		}
	}

	return true;
}


void AgentModule::fireSend(const std::string & strContent, const void * param)
{
	LOG4CPLUS_WARN(log, this->getId() << " fireSend not implement.");
}


static void listener_cb(struct evconnlistener *, evutil_socket_t, struct sockaddr *, int socklen, void *);
static void conn_read_cb(struct bufferevent *bev, void *ctx);
static void conn_writecb(struct bufferevent *, void *);
static void conn_eventcb(struct bufferevent *, short, void *);

static void listener_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sa, int socklen, void *user_data)
{
	AgentModule * This = reinterpret_cast<AgentModule *>(user_data);

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
	AgentModule * This = reinterpret_cast<AgentModule *>(user_data);
	LOG4CPLUS_DEBUG(This->getLogger(), This->getId() << ":" << bev);
	/* This callback is invoked when there is data to read on bev. */
	struct evbuffer *input = bufferevent_get_input(bev);
	struct evbuffer *output = bufferevent_get_output(bev);

	/* Copy all the data from the input buffer to the output buffer. */
	evbuffer_add_buffer(output, input);
}

static void conn_writecb(struct bufferevent *bev, void *user_data)
{
	AgentModule * This = reinterpret_cast<AgentModule *>(user_data);

	LOG4CPLUS_DEBUG(This->getLogger(), This->getId() << " write:" << bev);
	struct evbuffer *output = bufferevent_get_output(bev);
	
}

static void conn_eventcb(struct bufferevent *bev, short events, void * user_data)
{
	AgentModule * This = reinterpret_cast<AgentModule *>(user_data);

	LOG4CPLUS_DEBUG(This->getLogger(), This->getId() << ":" << bev);
	if (events & BEV_EVENT_ERROR)
		LOG4CPLUS_DEBUG(This->getLogger(), This->getId() << " Error from bufferevent");
	if (events & (BEV_EVENT_EOF | BEV_EVENT_ERROR)) {
		LOG4CPLUS_DEBUG(This->getLogger(), This->getId() << " Connection closed." << bev);
		bufferevent_free(bev);
	}
}

bool AgentModule::listenTCP(int port)
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
		//LOG4CPLUS_INFO(log, ",libevent supported method:" << methods[i]);
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

class AgentWSclient :public WebSocket::WSConnection, chilli::model::ConnectAdapter
{
public:
	explicit AgentWSclient(struct lws * wsi, model::ProcessModule * module) 
		:WSConnection(wsi),m_module(module)
	{
		this->log = log4cplus::Logger::getInstance("chilli.AgentWSclient");
		LOG4CPLUS_TRACE(log, m_SessionId << "construction");
	};

	~AgentWSclient()
	{
		LOG4CPLUS_TRACE(log, m_SessionId << "deconstruct");
	}

	virtual void OnClose(const std::string & errorCode) override
	{
		if (!m_Extension.empty())
		{
			Json::Value event;
			event["extension"] = m_Extension;
			event["event"] = "ConnectClose";
			event["errorCode"] = errorCode;
			model::EventType_t evt(event, GetId());
			m_module->PushEvent(evt);
		}
		delete this;
	};

	virtual void OnError(const std::string & errorCode) override
	{
		if (!m_Extension.empty())
		{
			Json::Value event;
			event["extension"] = m_Extension;
			event["event"] = "ConnectError";
			event["errorCode"] = errorCode;
			model::EventType_t evt(event, GetId());
			m_module->PushEvent(evt);
		}
		delete this;
	};

	virtual void OnMessage(const std::string & message) override
	{
		Json::Value jsonEvent;
		Json::Reader jsonReader;
		if (jsonReader.parse(message, jsonEvent)) {

			if (jsonEvent["event"].isNull())
				jsonEvent["event"] = "cmd";
			if (jsonEvent["extension"].isNull())
				jsonEvent["extension"] = jsonEvent.removeMember("agentid");
			if (jsonEvent["extension"].isNull())
				jsonEvent["extension"] = jsonEvent["operatorid"];

			if (jsonEvent["cmd"].isString() && jsonEvent["cmd"].asString() == "ping") {

			}
			else {
				LOG4CPLUS_TRACE(log, m_SessionId << " OnMessage:" << message);
			}
			model::EventType_t evt(jsonEvent, GetId());
			m_module->PushEvent(evt);
		}
		else {
			LOG4CPLUS_ERROR(log, m_SessionId << " OnMessage not json string:" << message);
		}

	};

	virtual int Send(const char * lpBuf, int nBufLen) override
	{
		//LOG4CPLUS_DEBUG(log, m_SessionId << " Send:" << std::string(lpBuf, nBufLen));
		return WSConnection::Send(lpBuf, nBufLen);
	}

	virtual void Close() override
	{
		return WSConnection::Close();
	}

private:
	model::ProcessModule * m_module;

};

class AgentWSServer :public WebSocket::WebSocketServer
{
public:
	explicit AgentWSServer(int port, model::ProcessModule * module)
		:WebSocketServer(port), m_module(module)
	{};
	virtual WebSocket::WSConnection * OnAccept(struct lws *wsi) override
	{
		WebSocket::WSConnection * wsc = new AgentWSclient(wsi, m_module);
		return wsc;
	}
private:
	model::ProcessModule * m_module;
};

bool AgentModule::listenWS(int port)
{
	bool result = true;

	AgentWSServer wsserver(port, this);
	LOG4CPLUS_INFO(log, this->getId() << ",websocket start listen port:" << port);
	wsserver.InitInstance();

	while (m_bRunning){
		wsserver.Loop(1000);
	}

	wsserver.UnInitInstance();
	log4cplus::threadCleanup();
	return result;
}
}
}
