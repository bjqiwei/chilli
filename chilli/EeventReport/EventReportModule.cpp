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
	log.setAppendName("." + this->getId());
	LOG4CPLUS_DEBUG(log, " Constuction a EventReport module.");
}


EventReportModule::~EventReportModule(void)
{
	if (m_bRunning){
		Stop();
	}

	LOG4CPLUS_DEBUG(log, " Destruction a EventReport module.");
}

int EventReportModule::Stop(void)
{

	if (m_bRunning){
		ProcessModule::Stop();
		m_bRunning = false;
		TCPServer::Stop();
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
			TCPServer::setLogger(this->log);
			std::thread th(&EventReportModule::ListenTCP, this, this->m_tcpPort);
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
		LOG4CPLUS_ERROR(log, " load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
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

void EventReportModule::ConnOnClose(uint64_t id)
{
	this->m_Connections.erase(id);
}

void EventReportModule::ConnOnError(uint64_t id, const std::string & errorCode)
{
	this->m_Connections.erase(id);
}

void EventReportModule::ConnOnMessage(EPConnection * conn, uint64_t id, const std::string & message, const std::string & logId)
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
			auto & c = m_Connections.find(id);
			if (c != m_Connections.end())
				c->second->Send(response);
		}
		else {
			LOG4CPLUS_DEBUG(log, logId << " OnMessage:" << message);
		}

		if (requestid == "connect")
		{
			Json::Value response;
			response["invokeID"] = request["invokeID"];
			response["type"] = "response";
			response["response"] = "connect";
			response["status"] = 0;
			response["param"]["version"] = "1.0.0.0";

			EPConnectionPtr connptr(conn);
			m_Connections[id] = connptr;
			auto & c = m_Connections.find(id);
			if (c != m_Connections.end())
				c->second->Send(response);
		}
		else if (requestid == "disConnect")
		{
			Json::Value response;
			response["invokeID"] = request["invokeID"];
			response["type"] = "response";
			response["response"] = "disConnect";
			response["status"] = 0;
			auto & c = m_Connections.find(id);
			if (c != m_Connections.end())
				c->second->Send(response);

			m_Connections.erase(id);
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
				auto & c = m_Connections.find(id);
				if (c != m_Connections.end())
					c->second->Send(response);
				return;
			}

			if (request["param"]["calledDirectoryNumber"].isString())
				called = request["param"]["calledDirectoryNumber"].asString();
			else {
				response["status"] = 2;
				auto & c = m_Connections.find(id);
				if (c != m_Connections.end())
					c->second->Send(response);
				return;
			}
			response["status"] = 0;
			response["param"]["initiatedCall"]["connectionID"] = uuid();
			response["param"]["initiatedCall"]["callID"] = uuid();
			response["param"]["initiatedCall"]["sessionID"] = uuid();

			auto & c = m_Connections.find(id);
			if (c != m_Connections.end())
				c->second->Send(response);
			request["param"]["initiatedCall"] = response["param"]["initiatedCall"];
			model::EventType_t evt(request);
			this->PushEvent(evt);
		}
		else if (requestid == "MakeConnection")
		{
			std::string called;
			Json::Value response;
			response["invokeID"] = request["invokeID"];
			response["type"] = "response";
			response["response"] = "MakeConnection";

			if (request["param"]["initiatingDevice"].isString())
				called = request["param"]["initiatingDevice"].asString();
			else {
				response["status"] = 2;
				auto & c = m_Connections.find(id);
				if (c != m_Connections.end())
					c->second->Send(response);
				return;
			}
			response["status"] = 0;
			response["param"]["initiatedCall"]["connectionID"] = uuid();
			response["param"]["initiatedCall"]["callID"] = uuid();
			response["param"]["initiatedCall"]["sessionID"] = uuid();

			auto & c = m_Connections.find(id);
			if (c != m_Connections.end())
				c->second->Send(response);
			request["param"]["initiatedCall"] = response["param"]["initiatedCall"];
			model::EventType_t evt(request);
			this->PushEvent(evt);
		}
		else if (requestid == "ClearConnection")
		{
			Json::Value response;
			response["invokeID"] = request["invokeID"];
			response["type"] = "response";
			response["response"] = "ClearConnection";

			if (request["param"]["connectionToBeCleared"].isObject()){

			}
			else {
				response["status"] = 3;
				auto & c = m_Connections.find(id);
				if (c != m_Connections.end())
					c->second->Send(response);
				return;
			}
			response["status"] = 0;

			auto & c = m_Connections.find(id);
			if (c != m_Connections.end())
				c->second->Send(response);

			model::EventType_t evt(request);
			this->PushEvent(evt);
		}

	}
	else {
		LOG4CPLUS_ERROR(log, logId << " OnMessage not json string:" << message);
	}
}


void EventReportModule::processSend(const std::string &strContent, const void * param, bool & bHandled)
{
	Json::Value jsonData;
	Json::Reader jsonReader;
	if (jsonReader.parse(strContent, jsonData)) {

		jsonData.removeMember("id");
		jsonData.removeMember("dest");
		jsonData.removeMember("from");
		jsonData.removeMember("target");

		for (auto & it:m_Connections){
			it.second->Send(jsonData);
		}
		bHandled = true;

	}
	else {
		LOG4CPLUS_ERROR(log, strContent << " not json data.");
	}
}

void EventReportModule::fireSend(const std::string & strContent, const void * param)
{
	LOG4CPLUS_TRACE(log, " fireSend:" << strContent);
	bool bHandled = false;
	processSend(strContent, param, bHandled);
}

void EventReportModule::run()
{
	LOG4CPLUS_INFO(log, " Starting...");
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
				LOG4CPLUS_ERROR(log, " " << e.what());
			}
		}

	}
	catch (std::exception & e)
	{
		LOG4CPLUS_ERROR(log, " " << e.what());
	}

	LOG4CPLUS_INFO(log, " Stoped.");
	log4cplus::threadCleanup();
}

class TCPConnection :public EPConnection, public TCP::TCPConnection{
public:
	explicit TCPConnection(EventReportModule * module, struct event_base * base, int64_t fd) :EPConnection(module), TCP::TCPConnection(base, fd)
	{
		log = log4cplus::Logger::getInstance("chilli.TCPConnection");
		LOG4CPLUS_DEBUG(log, m_Id << " construction");
	}
	virtual ~TCPConnection()
	{
		LOG4CPLUS_DEBUG(log, m_Id << " deconstruct");
	}

	virtual void OnOpen() override
	{

	}

	virtual void OnSend() override
	{

	}

	virtual void OnClosed() override
	{
		m_module->ConnOnClose(GetId());
	}

	virtual void OnError(uint32_t err) override
	{
		m_module->ConnOnError(GetId(), std::to_string(err));
	}

	virtual void OnReceived(const std::string & data) override
	{
		LOG4CPLUS_DEBUG(log, GetId() << " OnReceived:" << data);
		m_module->ConnOnMessage(this, GetId(), data, std::to_string(this->GetId()));
	}

	virtual int Send(const char * lpBuf, int nBufLen) override
	{
		return TCP::TCPConnection::Send(lpBuf, nBufLen);
	}

	virtual int Send(Json::Value) override
	{
		Json::FastWriter writer;
		std::string sendData = writer.write(send);
		LOG4CPLUS_DEBUG(log, GetId() << " Send:" << sendData);
		return TCP::TCPConnection::Send(sendData.c_str(), sendData.length());
	}

private:
	log4cplus::Logger log;
};

class WSConnection :public WebSocket::WSConnection, EPConnection
{
public:
	explicit WSConnection(struct lws * wsi, EventReportModule * module) 
		:WebSocket::WSConnection(wsi), EPConnection(module)
	{
		this->log = log4cplus::Logger::getInstance("chilli.WSConnection");
		LOG4CPLUS_DEBUG(log, m_SessionId << " construction");
	};

	~WSConnection()
	{
		LOG4CPLUS_DEBUG(log, m_SessionId << " deconstruct");
	}

	virtual void OnOpen() override {

	}

	virtual void OnSend() override {

	}

	virtual void OnClose(const std::string & errorCode) override
	{
		m_module->ConnOnClose(GetId());
	};

	virtual void OnError(const std::string & errorCode) override
	{
		
		m_module->ConnOnError(this->GetId(), errorCode);
	};

	virtual void OnMessage(const std::string & message) override
	{
		LOG4CPLUS_DEBUG(log, GetId() << " OnMessage:" << message);
		m_module->ConnOnMessage(this, this->GetId(), message, m_SessionId);
	};

	virtual int Send(const char * lpBuf, int nBufLen) override {
		return WebSocket::WSConnection::Send(lpBuf, nBufLen);
	}

	virtual int Send(Json::Value send) override {
		Json::FastWriter writer;
		std::string sendData = writer.write(send);
		LOG4CPLUS_DEBUG(log, GetId() << " Send:" << sendData);
		return this->Send(sendData.c_str(), sendData.length());
	}

};

class EventReportWSServer :public WebSocket::WebSocketServer
{
public:
	explicit EventReportWSServer(int port, EventReportModule * module)
		:WebSocketServer(port), m_module(module)
	{};
	virtual WebSocket::WSConnection * OnAccept(struct lws *wsi) override
	{
		WebSocket::WSConnection * wsc = new WSConnection(wsi, m_module);
		return wsc;
	}
private:
	EventReportModule * m_module;
};

TCP::TCPConnection * EventReportModule::OnAccept(event_base * base, int64_t fd)
{
	TCPConnection * conn = new chilli::EventReport::TCPConnection(this, base, fd);
	return conn;
}

void EventReportModule::ListenTCP(uint32_t port)
{
	TCPServer::ListenTCP(port);
}

bool EventReportModule::listenWS(int port)
{
	bool result = true;

	EventReportWSServer wsserver(port, this);
	LOG4CPLUS_INFO(log, ",websocket start listen port:" << port);
	wsserver.InitInstance();

	while (m_bRunning){
		wsserver.Loop(1000);
	}

	wsserver.UnInitInstance();
	log4cplus::threadCleanup();
	return result;
}

std::atomic_uint64_t EPConnection::__newConnectionId = 0;
EPConnection::EPConnection(EventReportModule * module):m_Id(__newConnectionId++), m_module(module)
{
}

EPConnection::~EPConnection()
{
}

uint64_t EPConnection::GetId()
{
	return m_Id;
}

}
}
