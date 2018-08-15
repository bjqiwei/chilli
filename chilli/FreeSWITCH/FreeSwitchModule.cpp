#include <stdint.h>
#include <esl.h>
#include "FreeSwitchModule.h"
#include "FreeSwitchDevice.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/config.h>
#include <json/json.h>
#include "../stringHelper.h"
#include "../uuid.h"
#include <regex>


namespace chilli{
namespace FreeSwitch{

FreeSwitchModule::FreeSwitchModule(const std::string & id):ProcessModule(id)
{
	log = log4cplus::Logger::getInstance("chilli.FSModule");
	log.setAppendName("." + this->getId());
	LOG4CPLUS_DEBUG(log, "Constuction a FreeSwitch module.");
}


FreeSwitchModule::~FreeSwitchModule(void)
{
	if (m_bRunning){
		Stop();
	}

	LOG4CPLUS_DEBUG(log, "Destruction a FreeSwitch module.");
}

int FreeSwitchModule::Stop(void)
{
	LOG4CPLUS_DEBUG(log, "Stop...  FreeSwitch module");
	if (m_bRunning)
	{
		ProcessModule::Stop();
		m_bRunning = false;

		if (m_Thread.joinable()) {
			m_Thread.join();
		}
	}
	return 0;
}

int FreeSwitchModule::Start()
{
	LOG4CPLUS_DEBUG(log," Start...  FreeSwitch module");
	if(!m_bRunning){
		ProcessModule::Start();
		m_bRunning = true;
		m_Thread = std::thread(&FreeSwitchModule::ConnectFS, this);
	}
	return 0;
}

bool FreeSwitchModule::LoadConfig(const std::string & configContext)
{
	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if (config.Parse(configContext.c_str()) != XMLError::XML_SUCCESS)
	{
		LOG4CPLUS_ERROR(log, " load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}
	tinyxml2::XMLElement * eConfig = config.FirstChildElement();
	m_Host = eConfig->Attribute("host") ? eConfig->Attribute("host"):"";
	m_Port = eConfig->IntAttribute("port");
	m_User = eConfig->Attribute("user") ? eConfig->Attribute("user") : "";
	m_Password = eConfig->Attribute("password") ? eConfig->Attribute("password") : "";

	// devices 
	XMLElement * deviceList = eConfig->FirstChildElement("Devices");

	if (deviceList != nullptr) {

		for (XMLElement *child = deviceList->FirstChildElement("Device");
			child != nullptr;
			child = child->NextSiblingElement("Device"))
		{

			const char * num = child->Attribute("DeviceID");
			const char * sm = child->Attribute("StateMachine");

			num = num ? num : "";
			sm = sm ? sm : "";

			m_device_StateMachine[num] = sm;
		}
	}

	return true;
}

void FreeSwitchModule::fireSend(const std::string & strContent, const void * param)
{
	LOG4CPLUS_TRACE(log, " fireSend:" << strContent);
	Json::Value jsonData;
	Json::Reader jsonReader;

	if (!jsonReader.parse(strContent, jsonData)) {
		LOG4CPLUS_ERROR(log, strContent << " not json data.");
		return;
	}

	bool bHandled = false;
	this->processSend(jsonData, param, bHandled, log);

}

void FreeSwitchModule::processSend(Json::Value & jsonData, const void * param, bool & bHandled, log4cplus::Logger & log)
{


	std::string eventName;
	std::string typeName;
	std::string dest;

	if (jsonData["type"].isString()) {
		typeName = jsonData["type"].asString();
	}

	if (typeName != "cmd") {
		return;
	}

	if (jsonData["dest"].isString()) {
		dest = jsonData["dest"].asString();
	}

	if (jsonData["event"].isString()) {
		eventName = jsonData["event"].asString();
	}

	if (eventName == "MakeCall")
	{
		bHandled = MakeCall(jsonData["param"], log);
	}
	else if (eventName == "MakeConnection")
	{
		bHandled = MakeConnection(jsonData["param"], log);
	}
	else if (eventName == "ClearConnection")
	{
		bHandled = ClearConnection(jsonData["param"], log);
	}
	else if (eventName == "DivertCall")
	{
		bHandled = Divert(jsonData["param"], log);
	}
	else if (eventName == "StartRecord")
	{
		bHandled = StartRecord(jsonData["param"], log);
	}
	else if (eventName == "TransferAgent")
	{
		std::string uuid = "";
		std::string origcaller = "";
		std::string agentid = "";

		if (jsonData["param"]["ConnectionID"].isString())
			uuid = jsonData["param"]["ConnectionID"].asString();

		if (jsonData["param"]["origcaller"].isString())
			origcaller = jsonData["param"]["origcaller"].asString();

		if (jsonData["param"]["agentId"].isString())
			agentid = jsonData["param"]["agentId"].asString();

		static std::string lastAgent;
		std::string findAgent;

		/*
		auto pe = this->getPerformElement(agentid);
		if (pe != nullptr) {
			LOG4CPLUS_DEBUG(log, agentid << " state:" << pe->getStateId());
			if (pe->getStateId() == "Ready") {
				findAgent = agentid;
				goto _findAgent;
			}
		}
		
		LOG4CPLUS_DEBUG(log, " All device:" << this->GetExtensions().size());

		if (lastAgent == ""){
			for (auto it : this->GetExtensions())
			{
				LOG4CPLUS_DEBUG(log, it.first << " state:" << it.second->getStateId());
				if (it.second->getStateId() == "Ready") {
					findAgent = it.first;
					break;
				}
			}
		}
		else{
			bool bfindLastAgent = false;


			for (auto it : this->GetExtensions())
			{
				if (it.first == lastAgent){
					bfindLastAgent = true;
					continue;
				}

				if (bfindLastAgent == true)
				{
					LOG4CPLUS_DEBUG(log, it.first << " state:" << it.second->getStateId());
					if (it.second->getStateId() == "Ready") {
						findAgent = it.first;
						break;
					}
				}
			}

			if (findAgent == "")
			{
				for (auto it : this->GetExtensions())
				{
					LOG4CPLUS_DEBUG(log, it.first << " state:" << it.second->getStateId());
					if (it.second->getStateId() == "Ready"){
						findAgent = it.first;
						break;
					}
				}
			}
		}
		
	_findAgent:
		lastAgent = findAgent;
		LOG4CPLUS_DEBUG(log, " find agent:" << findAgent);
		if (!findAgent.empty()){
			Json::Value ext = this->getExtension(findAgent)->getVar("_agent.Device");
			if (ext.isString())
			{
				std::string cmd = "bgapi uuid_transfer " + uuid +" " + ext.asString() + " XML default";
				esl_status_t status = esl_send(&m_Handle, cmd.c_str());
				LOG4CPLUS_DEBUG(log, " esl_send:" << cmd << ", status:" << status);
			}
		}

		bHandled = true;
		*/
	}
}
bool FreeSwitchModule::MakeCall(Json::Value & param, log4cplus::Logger & log)
{
	std::string caller = "";
	std::string called = "";
	std::string sessionId = "";
	std::string display = "";

	if (param["caller"].isString())
		caller = param["caller"].asString();

	if (param["called"].isString())
		called = param["called"].asString();

	if (param["display"].isString())
		display = param["display"].asString();
	else
		display = caller;

	if (param["sessionID"].isString())
		sessionId = param["sessionID"].asString();

	m_Session_DeviceId[sessionId] = caller;

	if (caller.length() < 5) {
		caller = "sofia/internal/" + caller + "%192.168.2.232";
	}
	else {
		caller = "sofia/external/" + caller + "@192.168.2.220";
	}

	if (called.length() < 5) {
		called = "sofia/internal/" + called + "%192.168.2.232";
	}
	else {
		called = "sofia/external/" + called + "@192.168.2.220";
	}

	std::string cmd = "bgapi originate {origination_uuid=" + sessionId + "}" + caller + " &bridge({origination_caller_id_number=" + display + "}" + called + ")";

	esl_status_t status = esl_send(&m_Handle, cmd.c_str());
	LOG4CPLUS_DEBUG(log, " esl_send:" << cmd << ", status:" << status);

	return true;

}
bool FreeSwitchModule::MakeConnection(Json::Value & param, log4cplus::Logger & log)
{
	std::string called = "";
	std::string sessionId = "";
	std::string display = "";

	if (param["called"].isString())
		called = param["called"].asString();

	if (param["display"].isString())
		display = param["display"].asString();

	if (param["sessionID"].isString())
		sessionId = param["sessionID"].asString();

	m_Session_DeviceId[sessionId] = called;

	if (called.length() < 5) {
		called = "sofia/internal/" + called + "%192.168.2.232";
	}
	else {
		called = "sofia/external/" + called + "@192.168.2.220";
	}

	std::string cmd = "bgapi originate {origination_uuid=" + sessionId + "}" + called + " &park()";

	esl_status_t status = esl_send(&m_Handle, cmd.c_str());
	LOG4CPLUS_DEBUG(log, " esl_send:" << cmd << ", status:" << status);
	return true;

}
bool FreeSwitchModule::ClearConnection(Json::Value & param, log4cplus::Logger & log)
{
	std::string sessionId = "";

	if (param["sessionID"].isString())
		sessionId = param["sessionID"].asString();

	std::string cmd = "bgapi uuid_kill " + sessionId;
	esl_send(&m_Handle, cmd.c_str());
	esl_status_t status = esl_send(&m_Handle, cmd.c_str());
	LOG4CPLUS_DEBUG(log, " esl_send:" << cmd << ", status:" << status);

	return true;
}

bool FreeSwitchModule::StartRecord(Json::Value & param, log4cplus::Logger & log)
{
	std::string uuid = "";
	std::string filename = "";

	if (param["ConnectionID"].isString())
		uuid = param["ConnectionID"].asString();

	if (param["filename"].isString())
		filename = param["filename"].asString();

	std::string cmd = "bgapi uuid_record " + uuid + " start " + filename;
	esl_status_t status = esl_send(&m_Handle, cmd.c_str());
	LOG4CPLUS_DEBUG(log, " esl_send:" << cmd << ", status:" << status);
	return true;
}

bool FreeSwitchModule::Divert(Json::Value & param, log4cplus::Logger & log)
{
	std::string called = "";
	std::string sessionId = "";
	std::string display = "";

	if (param["called"].isString())
		called = param["called"].asString();

	if (param["display"].isString())
		param["display"].asString();

	if (param["sessionID"].isString())
		param["sessionID"].asString();

	if (called.length() < 5) {
		called = "sofia/internal/" + called + "%192.168.2.232";
	}
	else {
		called = "sofia/external/" + called + "@192.168.2.220";
	}

	esl_status_t status = esl_execute(&m_Handle, "bridge", called.c_str(), sessionId.c_str());
	LOG4CPLUS_DEBUG(log, " esl_execute:bridge " << called << ", status:" << status);

	return true;
}

bool FreeSwitchModule::PlayFile(Json::Value & param, log4cplus::Logger & log)
{
	std::string sessionId;
	std::string filename;

	if (param["sessionID"].isString())
		sessionId = param["sessionID"].asString();

	if (param["filename"].isString())
		filename = param["filename"].asString();

	esl_status_t status = esl_execute(&m_Handle, "playback", filename.c_str(), sessionId.c_str());
	LOG4CPLUS_DEBUG(log, " esl_execute:playback " << filename << ", status:" << status);
	return true;
}

void esl_logger(const char *file, const char *func, int line, int level, const char *fmt, ...)
{
	static log4cplus::Logger log = log4cplus::Logger::getInstance("esl_log");
	const char *fp;
	char *data;
	va_list ap;
	int ret;

	if (level < 0 || level > 7) {
		level = 7;
	}

	va_start(ap, fmt);

	ret = esl_vasprintf(&data, fmt, ap);
	if (ret != -1) {
		if (level == ESL_LOG_LEVEL_DEBUG){
			LOG4CPLUS_DEBUG(log, fp << ":" << line << " " << func << "() " << data);
		}
		else if (level == ESL_LOG_LEVEL_INFO){
			LOG4CPLUS_INFO(log, fp << ":" << line << " " << func << "() " << data);
		}
		else if (level == ESL_LOG_LEVEL_NOTICE) {
			LOG4CPLUS_INFO(log, fp << ":" << line << " " << func << "() " << data);
		}
		else if (level == ESL_LOG_LEVEL_WARNING) {
			LOG4CPLUS_WARN(log, fp << ":" << line << " " << func << "() " << data);
		}
		else if (level == ESL_LOG_LEVEL_ERROR) {
			LOG4CPLUS_ERROR(log, fp << ":" << line << " " << func << "() " << data);
		}
		else if (level == ESL_LOG_LEVEL_CRIT) {
			LOG4CPLUS_FATAL(log, fp << ":" << line << " " << func << "() " << data);
		}
		free(data);
	}

	va_end(ap);
}

void FreeSwitchModule::ConnectFS()
{
	LOG4CPLUS_DEBUG(log, " Run  FreeSwitch module");

	//esl_handle_t handle = { { 0 } };

	while (m_bRunning)
	{
		LOG4CPLUS_DEBUG(log, " connect freeswitch " << m_Host << ":" << m_Port);

		esl_status_t status = esl_connect_timeout(&m_Handle, m_Host.c_str(), m_Port, m_User.c_str(), m_Password.c_str(),5*1000);

		if (!m_Handle.connected){
			LOG4CPLUS_ERROR(log, " connect freeswitch " << m_Host << ":" << m_Port << " error,"
				<< m_Handle.errnum << " " << m_Handle.err);
			if (m_bRunning)
				std::this_thread::sleep_for(std::chrono::seconds(5));
			continue;
		}

		LOG4CPLUS_INFO(log, " Connected to FreeSWITCH");

		esl_events(&m_Handle, ESL_EVENT_TYPE_JSON, "All");
		esl_send(&m_Handle, "nixevent json API HEARTBEAT RE_SCHEDULE RECV_RTCP_MESSAGE MESSAGE_QUERY MESSAGE_WAITING PRESENCE_IN CUSTOM sofia::pre_register sofia::register_attempt");
		LOG4CPLUS_DEBUG(log, " " << m_Handle.last_sr_reply);

		while (m_bRunning){
			esl_status_t status = esl_recv_event_timed(&m_Handle, 1000, true, NULL);
			if (status == ESL_SUCCESS){
				if (m_Handle.last_event && m_Handle.last_event->body) {
					Json::Reader reader;
					Json::Value event;

					if (reader.parse(m_Handle.last_event->body, event) && event.isObject()) {

						std::string eventName;
						if (event["Event-Name"].isString()) {
							eventName = event["Event-Name"].asString();
							event.removeMember("Event-Name");
						}

						LOG4CPLUS_DEBUG(log, " " << m_Handle.last_event->body);

						if (eventName == "CHANNEL_CREATE" 
							|| eventName == "CHANNEL_PROGRESS"
							|| eventName == "CHANNEL_ANSWER"
							|| eventName == "CHANNEL_BRIDGE"
							|| eventName == "CHANNEL_UNBRIDGE"
							|| eventName == "CHANNEL_HANGUP"
							|| eventName == "CHANNEL_DESTROY"
							|| eventName == "CHANNEL_OUTGOING"
							|| eventName == "CHANNEL_ORIGINATE"
							|| eventName == "CHANNEL_EXECUTE"
							|| eventName == "CHANNEL_EXECUTE_COMPLETE")
						{
							event.removeMember("Core-UUID");
							event.removeMember("FreeSWITCH-Hostname");
							event.removeMember("FreeSWITCH-Switchname");
							event.removeMember("FreeSWITCH-IPv4");
							event.removeMember("FreeSWITCH-IPv6");
							event.removeMember("Event-Calling-File");
							event.removeMember("Event-Calling-Function");
							event.removeMember("Event-Calling-Line-Number");
							event.removeMember("Event-Sequence");
							event.removeMember("Caller-Dialplan");
							event.removeMember("Caller-Caller-ID-Name");
							event.removeMember("Caller-Channel-Name");
							event.removeMember("Caller-Context");
							event.removeMember("Caller-Orig-Caller-ID-Name");
							event.removeMember("Caller-Network-Addr");
							event.removeMember("Caller-Privacy-Hide-Name");
							event.removeMember("Caller-Privacy-Hide-Number");
							event.removeMember("Caller-Profile-Created-Time");
							event.removeMember("Caller-Profile-Index");
							event.removeMember("Caller-Screen-Bit");
							event.removeMember("Caller-Source");
							event.removeMember("Channel-HIT-Dialplan");
							event.removeMember("Channel-Name");
							event.removeMember("Channel-Presence-ID");
							event.removeMember("Event-Date-GMT");
							event.removeMember("Event-Date-Timestamp");
							event.removeMember("Caller-Unique-ID");
							event.removeMember("Caller-Direction");
							event.removeMember("CallerLogical-Direction");
							event.removeMember("Channel-Call-UUID");
							event.removeMember("Channel-Name");
							event.removeMember("Channel-Call-State");
							event.removeMember("Presence-Call-Direction");
							event.removeMember("Channel-State-Number");

							if (eventName == "CHANNEL_EXECUTE_COMPLETE")
								eventName = event["Application"].asString();

							std::string caller = event["Caller-ANI"].asString();
							std::string called = event["Caller-Destination-Number"].asString();
							std::string dir = event["Call-Direction"].asString();

							model::EventType_t evt;
							for (auto & varname : event.getMemberNames()) {
								std::string newvarname = varname;
								if (newvarname.find("variable_") == std::string::npos) {
									helper::string::replaceString(newvarname, "-", "");
									evt.event["param"][newvarname] = event[varname];
								}
							}


							
							std::string sessionId = evt.event["param"]["UniqueID"].asString();
							evt.event["param"].removeMember("UniqueID");

							if (m_Session_DeviceId.find(sessionId) == m_Session_DeviceId.end()){
								if (dir == "inbound")
									m_Session_DeviceId[sessionId] = caller.substr(0,caller.find("%"));
								else if (dir == "outbound")
									m_Session_DeviceId[sessionId] = called.substr(0,called.find("%"));
								
							}
							
							evt.event["id"] = m_Session_DeviceId[sessionId];
							evt.event["event"] = eventName;
							evt.event["param"]["sessionID"] = sessionId;

							//Channel _ Create：通道创建事件
							//Channel _ Progress：通道振铃事件
							//Channel _ Answer：通道应答事件
							//Channel _ Bridge：通道桥接事件
							//Channel _ Hangup：通道挂断事件

							this->PushEvent(evt);

							if (eventName == "CHANNEL_DESTROY")
								m_Session_DeviceId.erase(evt.event["sessionID"].asString());
							
						}
					}
					
				}
			}
			else if (status == ESL_BREAK)
				continue;
			else{
				LOG4CPLUS_ERROR(log, " " << m_Handle.err);
				break;
			}
		}

		esl_disconnect(&m_Handle);
	}
	LOG4CPLUS_DEBUG(log, " Stoped  FreeSwitch module");
	log4cplus::threadCleanup();
}
void FreeSwitchModule::run()
{
	LOG4CPLUS_INFO(log, " Starting...");
	try
	{

		while (m_bRunning)
		{
			try
			{
				model::EventType_t Event;
				if (m_RecEvtBuffer.Get(Event) && !Event.event.isNull())
				{
					const Json::Value & jsonEvent = Event.event;
					std::string peId;
					if (jsonEvent["id"].isString()) {
						peId = jsonEvent["id"].asString();
					}

					if (peId.empty()){
						LOG4CPLUS_WARN(log, " not find device:" << peId);
						continue;
					}


					if (this->getPerformElement(peId) == nullptr) {

						for (auto & it : this->m_device_StateMachine) {
							std::regex regPattern(it.first);
							if (std::regex_match(peId, regPattern)) {
								model::PerformElementPtr peptr(new FreeSwitchDevice(this, peId, it.second));
								if (peptr != nullptr && this->addPerformElement(peId, peptr)) {
									peptr->setVar("_device.deviceID", peId);
								}

								break;
							}
						}

					}

					auto extptr = getPerformElement(peId);

					if (extptr != nullptr) {
						extptr->pushEvent(Event);
						extptr->mainEventLoop();

						if (extptr->IsClosed())
							this->removePerfromElement(peId);
						
					}
					else {
						LOG4CPLUS_WARN(log, " not find device:" << peId);
					}
				}
			}
			catch (std::exception & e)
			{
				LOG4CPLUS_ERROR(log, e.what());
			}
		}

	}
	catch (std::exception & e)
	{
		LOG4CPLUS_ERROR(log, e.what());
	}

	LOG4CPLUS_INFO(log, " Stoped.");
	log4cplus::threadCleanup();
}
}
}

