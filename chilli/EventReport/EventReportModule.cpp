#include "EventReportModule.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/config.h>
#include <json/json.h>
#include "../websocket/websocket.h"
#include "../uuid.h"
#include "../model/TypeDef.h"

#define _STRVERSION(str) #str
#define STRVERSION(str) _STRVERSION(str)
static const char* appversion = STRVERSION(APPVERSION);

namespace chilli{
namespace EventReport{

EventReportModule::EventReportModule(const std::string & id) :ProcessModule(id)
{
	log = log4cplus::Logger::getInstance("chilli.ERModule");
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
		strncpy(urlbuff, m_wsUrl.c_str(), sizeof(urlbuff));
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

void EventReportModule::ConnOnMessage(EPConnection * conn, uint64_t id, const std::string & message, log4cplus::Logger & log)
{
	//LOG4CPLUS_DEBUG(log, m_SessionId << " OnMessage:" << message);

	Json::Value request;
	Json::CharReaderBuilder b;
	std::shared_ptr<Json::CharReader> jsonReader(b.newCharReader());
	std::string jsonerr;
	if (jsonReader->parse(message.c_str(), message.c_str() + message.length(), &request, &jsonerr)) {

		std::string requestid;
		if (request["request"].isString())
			requestid = request["request"].asString();

		if (requestid == "HeartBeat") {

			LOG4CPLUS_TRACE(log, " OnMessage:" << message);

			Json::Value response;
			response["invokeID"] = request["invokeID"];
			response["type"] = "response";
			response["response"] = "HeartBeat";
			response["status"] = 0;
			const auto & c = m_Connections.find(id);
			if (c != m_Connections.end())
				c->second->Send(response);
		}
		else {
			LOG4CPLUS_DEBUG(log, " OnMessage:" << message);
		}

		if (requestid == "Connect")
		{
			Json::Value response;
			response["invokeID"] = request["invokeID"];
			response["type"] = "response";
			response["response"] = "Connect";
			response["status"] = 0;
			response["param"]["version"] = appversion;

			EPConnectionPtr connptr(conn);
			m_Connections[id] = connptr;
			const auto & c = m_Connections.find(id);
			if (c != m_Connections.end())
				c->second->Send(response);
		}
		else if (requestid == "DisConnect")
		{
			Json::Value response;
			response["invokeID"] = request["invokeID"];
			response["type"] = "response";
			response["response"] = "DisConnect";
			response["status"] = 0;
			const auto & c = m_Connections.find(id);
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

			request["param"].removeMember("callingDevice");
			
			if (calling.empty())
			{
				response["status"] = chilli::INVALID_CALLING_DEVICE;
				const auto & c = m_Connections.find(id);
				if (c != m_Connections.end())
					c->second->Send(response);
				return;
			}

			if (request["param"]["calledDirectoryNumber"].isString())
				called = request["param"]["calledDirectoryNumber"].asString();
			request["param"].removeMember("calledDirectoryNumber");

			if(called.empty()){
				response["status"] = chilli::INVALID_CALLED_DEVICE;
				const auto & c = m_Connections.find(id);
				if (c != m_Connections.end())
					c->second->Send(response);
				return;
			}

			response["status"] = 0;
			response["param"]["initiatedCall"]["connectionID"] = helper::uuid();
			response["param"]["initiatedCall"]["callID"] = helper::uuid();
			response["param"]["initiatedCall"]["sessionID"] = helper::uuid();

			response["param"]["calledCall"] = response["param"]["initiatedCall"];
			response["param"]["calledCall"]["sessionID"] = helper::uuid();

			const auto & c = m_Connections.find(id);
			if (c != m_Connections.end())
				c->second->Send(response);

			request["param"]["connectionID"] = response["param"]["initiatedCall"]["connectionID"];
			request["param"]["callID"] = response["param"]["initiatedCall"]["callID"];
			request["param"]["sessionID"] = response["param"]["initiatedCall"]["sessionID"];

			request["param"]["sessionID_called"] = response["param"]["calledCall"]["sessionID"];

			request["param"]["caller"] = calling;
			request["param"]["called"] = called;

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

			request["param"].removeMember("initiatingDevice");

			if(called.empty()){
				response["status"] = chilli::INVALID_CALLED_DEVICE;
				const auto & c = m_Connections.find(id);
				if (c != m_Connections.end())
					c->second->Send(response);
				return;
			}

			response["status"] = 0;
			response["param"]["initiatedCall"]["connectionID"] = helper::uuid();
			response["param"]["initiatedCall"]["callID"] = helper::uuid();
			response["param"]["initiatedCall"]["sessionID"] = helper::uuid();
			const auto & c = m_Connections.find(id);
			if (c != m_Connections.end())
				c->second->Send(response);

			request["param"]["connectionID"] = response["param"]["initiatedCall"]["connectionID"];
			request["param"]["callID"] = response["param"]["initiatedCall"]["callID"];
			request["param"]["sessionID"] = response["param"]["initiatedCall"]["sessionID"];
			request["param"]["called"] = called;
			model::EventType_t evt(request);
			this->PushEvent(evt);
		}

		else if (requestid == "ClearConnection")
		{
			Json::Value response;
			response["invokeID"] = request["invokeID"];
			response["type"] = "response";
			response["response"] = "ClearConnection";
			response["status"] = 0;

			if (request["param"]["connectionToBeCleared"].isObject()){
				if (request["param"]["connectionToBeCleared"]["deviceID"].isString()) {
					std::string deviceid = request["param"]["connectionToBeCleared"]["deviceID"].asString();
					const auto & it = this->getPerformElementByGlobal(deviceid);
					if (it != nullptr){

						const auto & c = m_Connections.find(id);
						if (c != m_Connections.end())
							c->second->Send(response);

						request["param"]["sessionID"] = request["param"]["connectionToBeCleared"]["sessionID"];
						request["param"].removeMember("connectionToBeCleared");
						request["cmd"] = request["request"];
						request.removeMember("request");
						request["event"] = "cmd";
						request["id"] = deviceid;
						model::EventType_t evt(request);
						it->PushEvent(evt);
						return;
					}
				}
			}
			
			response["status"] = chilli::INVALID_CALL;
			const auto & c = m_Connections.find(id);
			if (c != m_Connections.end())
				c->second->Send(response);
			return;

		}
		else if (requestid == "PlayFile")
		{
			Json::Value response;
			response["invokeID"] = request["invokeID"];
			response["type"] = "response";
			response["response"] = request["request"];
			response["status"] = 0;

			if (request["param"]["connection"].isObject()) {
				if (request["param"]["connection"]["deviceID"].isString()) {
					std::string deviceid = request["param"]["connection"]["deviceID"].asString();
					const auto & it = this->getPerformElementByGlobal(deviceid);
					if (it != nullptr) {

						const auto & c = m_Connections.find(id);
						if (c != m_Connections.end())
							c->second->Send(response);

						request["param"]["sessionID"] = request["param"]["connection"]["sessionID"];
						request["param"]["connectionID"] = request["param"]["connection"]["connectionID"];
						request["param"]["callID"] = request["param"]["connection"]["callID"];
						request["param"].removeMember("connection");
						request["cmd"] = request["request"];
						request.removeMember("request");
						request["event"] = "cmd";
						request["id"] = deviceid;
						model::EventType_t evt(request);
						it->PushEvent(evt);
						return;
					}
				}
			}

			response["status"] = chilli::INVALID_CALL;
			const auto & c = m_Connections.find(id);
			if (c != m_Connections.end())
				c->second->Send(response);
			return;
		}

		else {
			Json::Value response;
			response["invokeID"] = request["invokeID"];
			response["type"] = "response";
			response["response"] = request["request"];
			response["status"] = chilli::INVALID_REQUEST;

			const auto & c = m_Connections.find(id);
			if (c != m_Connections.end())
				c->second->Send(response);

		}

	}
	else {
		LOG4CPLUS_ERROR(log, " OnMessage not json string:" << message << ":" << jsonerr);
	}
}


void EventReportModule::processSend(const std::string &strContent, const void * param, bool & bHandled)
{
	Json::Value jsonData;
	Json::CharReaderBuilder b;
	std::shared_ptr<Json::CharReader> jsonReader(b.newCharReader());
	std::string jsonerr;
	if (jsonReader->parse(strContent.c_str(), strContent.c_str()+ strContent.length(), &jsonData, &jsonerr)) {

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
		LOG4CPLUS_ERROR(log, strContent << " not json data." << jsonerr);
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
private:
	const uint32_t INT_SIZE = sizeof(uint32_t);
	union contextlen {
		char buffer[sizeof(uint32_t)];
		uint32_t nlen;
		uint32_t hlen;
	};
public:
	explicit TCPConnection(EventReportModule * module, struct event_base * base, int64_t fd) :EPConnection(module), TCP::TCPConnection(base, fd)
	{
		log = log4cplus::Logger::getInstance("chilli.TCPConnection");
		log.setAppendName("." + to_string(this->GetId()));
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

	virtual void OnReceived(const std::string & oriData) override
	{
		LOG4CPLUS_TRACE(log, " OnReceived:" << oriData);
		contextlen hlen;
		m_reciveBuffer.append(oriData);
		size_t len = m_reciveBuffer.length();

		while (len >= INT_SIZE) {
			memcpy(hlen.buffer, m_reciveBuffer.data(), INT_SIZE);
			hlen.hlen = ntohl(hlen.nlen);

			if (len >= hlen.hlen) {
				std::string data = m_reciveBuffer.substr(0, hlen.hlen);
				m_reciveBuffer.erase(0, hlen.hlen);
				data = data.substr(INT_SIZE);
				m_module->ConnOnMessage(this, GetId(), data, log);
			}
			else {// 不够一个完整的包，跳出循环   
				break;
			}

			len = m_reciveBuffer.length();
		}
		
	}

	virtual int Send(const char * lpBuf, int nBufLen) override
	{
		contextlen nlen;
		std::string buffer;
		nlen.nlen = htonl(nBufLen + INT_SIZE);
		buffer.append(nlen.buffer, INT_SIZE);
		buffer.append(lpBuf, nBufLen);

		LOG4CPLUS_TRACE(log, " Send:" << buffer);
		return TCP::TCPConnection::Send(buffer.c_str(), buffer.length());
	}

	virtual int Send(Json::Value send) override
	{
		Json::FastWriter writer;
		std::string sendData = writer.write(send);
		LOG4CPLUS_DEBUG(log, " Send:" << sendData);
		return this->Send(sendData.c_str(), sendData.length());
	}

private:
	log4cplus::Logger log;
	std::string m_reciveBuffer;
};

class WSConnection :public WebSocket::WSConnection, EPConnection
{
public:
	explicit WSConnection(struct lws * wsi, EventReportModule * module) 
		:WebSocket::WSConnection(wsi), EPConnection(module)
	{
		this->log = log4cplus::Logger::getInstance("chilli.WSConnection");
		log.setAppendName("." + std::to_string(this->GetId()));
		LOG4CPLUS_DEBUG(log, " construction");
	};

	~WSConnection()
	{
		LOG4CPLUS_DEBUG(log, " deconstruct");
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
		//LOG4CPLUS_DEBUG(log, " OnMessage:" << message);
		m_module->ConnOnMessage(this, this->GetId(), message, log);
	};

	virtual int Send(const char * lpBuf, int nBufLen) override {
		return WebSocket::WSConnection::Send(lpBuf, nBufLen);
	}

	virtual int Send(Json::Value send) override {
		Json::FastWriter writer;
		std::string sendData = writer.write(send);
		LOG4CPLUS_DEBUG(log, " Send:" << sendData);
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

std::atomic<uint64_t> EPConnection::__newConnectionId;
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
