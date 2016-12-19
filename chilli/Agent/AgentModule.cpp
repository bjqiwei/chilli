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


namespace chilli{
namespace Agent{

AgentModule::AgentModule(void)
{
	log = log4cplus::Logger::getInstance("chilli.AgentModule");
	LOG4CPLUS_DEBUG(log, "Constuction a Agent module.");
}


AgentModule::~AgentModule(void)
{
	if (m_bRunning){
		Stop();
	}

	LOG4CPLUS_DEBUG(log, "Destruction a Agent module.");
}

int AgentModule::Stop(void)
{
	LOG4CPLUS_DEBUG(log, "Stop  Agent module");

	m_bRunning = false;
	PushEvent(std::string());

	event_base_loopexit(m_Base, nullptr);

	for (auto & it : m_Agents){
		it.second->Stop();
	}
	
	for (auto & it : this->m_Threads) {
		if (it.joinable()) {
			it.join();
		}
	}

	m_Threads.clear();
	return 0;
}

int AgentModule::Start()
{
	LOG4CPLUS_DEBUG(log, "Start  Agent module");

	if(!m_bRunning)
	{
		for (auto & it : m_Agents) {
			it.second->Start();
		}

		m_bRunning = true;
		if (this->m_tcpPort !=-1){
			std::thread th(&AgentModule::listenTCP, this, this->m_tcpPort);
			m_Threads.push_back(std::move(th));
		}

		if (this->m_wsPort != -1){
			std::thread th(&AgentModule::listenWS, this, this->m_wsPort);
			m_Threads.push_back(std::move(th));
		}

		std::thread th(&AgentModule::run, this);
		m_Threads.push_back(std::move(th));
	}
	return 0;
}

bool AgentModule::LoadConfig(const std::string & configContext)
{
	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if (config.Parse(configContext.c_str()) != XMLError::XML_SUCCESS)
	{
		LOG4CPLUS_ERROR(log, "load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}
	
	tinyxml2::XMLElement * eAgent = config.FirstChildElement();
	eAgent->QueryIntAttribute("TCPPort", &this->m_tcpPort);
	eAgent->QueryIntAttribute("WSPort", &this->m_wsPort);

	for (XMLElement *child = eAgent->FirstChildElement("Extension");
		child != nullptr;
		child = child->NextSiblingElement("Extension"))
	{

		const char * num = child->Attribute("ExtensionNumber", "");
		const char * sm = child->Attribute("StateMachine", "");
		if (this->m_Agents.find(num) == this->m_Agents.end())
		{
			model::ExtensionPtr ext(new Agent(num, sm));
			this->m_Agents[num] = ext;

		}
		else {
			LOG4CPLUS_ERROR(log, "alredy had agent:" << num);
		}
	}

	return true;
}

const model::ExtensionMap & AgentModule::GetExtension()
{
	return m_Agents;
}


void AgentModule::run()
{
	while (m_bRunning)
	{
		std::string strEvent;
		if (m_recEvtBuffer.Get(strEvent) && !strEvent.empty())
		{
			Json::Value jsonEvent;
			Json::Reader jsonReader;
			if (jsonReader.parse(strEvent, jsonEvent)){
				std::string eventName;
				std::string sessionId;
				std::string ext;
				if (jsonEvent["event"].isString()){
					eventName = jsonEvent["event"].asString();
				}

				if (jsonEvent["sessionid"].isString()){
					sessionId = jsonEvent["sessionid"].asString();
				}

				if (jsonEvent["extension"].isString()){
					ext = jsonEvent["extension"].asString();
				}

				auto & it = m_Agents.find(ext);

				if (it != m_Agents.end())
				{
					it->second->pushEvent(strEvent);
				}
				else{
					LOG4CPLUS_ERROR(log, " not find extension by event:" << strEvent);
				}

			}
			else{
				LOG4CPLUS_ERROR(log, __FUNCTION__ ",event:" << strEvent << " not json data.");
			}
		}
	}

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
		LOG4CPLUS_ERROR(This->log, "Error constructing bufferevent!");
		event_base_loopbreak(base);
		return;
	}

	bufferevent_setcb(bev, conn_read_cb, conn_writecb, conn_eventcb, user_data);
	bufferevent_enable(bev, EV_WRITE | EV_READ);
	LOG4CPLUS_DEBUG(This->log, "accept client:" << bev);

}

static void conn_read_cb(struct bufferevent *bev, void * user_data)
{
	AgentModule * This = reinterpret_cast<AgentModule *>(user_data);
	LOG4CPLUS_DEBUG(This->log, __FUNCTION__":" << bev);
	/* This callback is invoked when there is data to read on bev. */
	struct evbuffer *input = bufferevent_get_input(bev);
	struct evbuffer *output = bufferevent_get_output(bev);

	/* Copy all the data from the input buffer to the output buffer. */
	evbuffer_add_buffer(output, input);
}

static void conn_writecb(struct bufferevent *bev, void *user_data)
{
	AgentModule * This = reinterpret_cast<AgentModule *>(user_data);

	LOG4CPLUS_DEBUG(This->log, "write:" << bev);
	struct evbuffer *output = bufferevent_get_output(bev);
	
}

static void conn_eventcb(struct bufferevent *bev, short events, void * user_data)
{
	AgentModule * This = reinterpret_cast<AgentModule *>(user_data);

	LOG4CPLUS_DEBUG(This->log, __FUNCTION__":" << bev);
	if (events & BEV_EVENT_ERROR)
		LOG4CPLUS_DEBUG(This->log, "Error from bufferevent");
	if (events & (BEV_EVENT_EOF | BEV_EVENT_ERROR)) {
		LOG4CPLUS_DEBUG(This->log, "Connection closed." << bev);
		bufferevent_free(bev);
	}
}

bool AgentModule::listenTCP(int port)
{
	struct sockaddr_in sin;
	struct evconnlistener *listener;

	LOG4CPLUS_INFO(log, "listen TCP Starting...");
#ifdef WIN32
	evthread_use_windows_threads();
	WSADATA wsa_data;
	WSAStartup(MAKEWORD(2, 2), &wsa_data);
#else
	evthread_use_pthreads();
#endif

	const char ** methods = event_get_supported_methods();
	for (int i = 0; methods[i] != nullptr; ++i) {
		LOG4CPLUS_INFO(log, __FUNCTION__",libevent supported method:" << methods[i]);
	}

	m_Base = event_base_new();
	LOG4CPLUS_INFO(log, __FUNCTION__",libevent current method:" <<  event_base_get_method(m_Base));

	if (!m_Base) {
		LOG4CPLUS_ERROR(log, "Could not initialize libevent!");
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
		LOG4CPLUS_ERROR(log, "Could not create a listener!");
		goto done;
	}

	LOG4CPLUS_INFO(log, __FUNCTION__",start listen tcp port:" << port);

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
	LOG4CPLUS_INFO(log, "listen TCP Stoped.");
	return true;
}

bool AgentModule::listenWS(int port)const
{
	bool result = true;
	WebSocket::WebSocketServer wsserver(port);
	LOG4CPLUS_INFO(log, __FUNCTION__",start listen port:" << port);
	wsserver.InitInstance();

	while (m_bRunning){
		wsserver.Loop(1000);
	}
	wsserver.UnInitInstance();
	return result;
}
}
}
