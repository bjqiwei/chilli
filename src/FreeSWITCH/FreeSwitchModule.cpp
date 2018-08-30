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
#include <apr_hash.h>
#include "../mysql/MySqlModule.h"


namespace chilli{
namespace FreeSwitch{

static std::string esl_execute_data(const char *app, const char *arg, const char *uuid, bool eventlock, bool async);
FreeSwitchModule::FreeSwitchModule(const std::string & id, uint32_t threadSize) :ProcessModule(id, threadSize)
{
	log = log4cplus::Logger::getInstance("chilli.FSModule");
	LOG4CPLUS_DEBUG(log, "." + this->getId(), "Constuction a FreeSwitch module.");
}


FreeSwitchModule::~FreeSwitchModule(void)
{
	if (m_bRunning){
		Stop();
	}

	LOG4CPLUS_DEBUG(log, "." + this->getId(), "Destruction a FreeSwitch module.");
}

int FreeSwitchModule::Stop(void)
{
	LOG4CPLUS_DEBUG(log, "." + this->getId(), "Stop...  FreeSwitch module");
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
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " Start...  FreeSwitch module");
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
		LOG4CPLUS_ERROR(log, "." + this->getId(), " load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
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
	LOG4CPLUS_TRACE(log, "." + this->getId(), " fireSend:" << strContent);
	Json::Value jsonData;
	Json::CharReaderBuilder b;
	std::shared_ptr<Json::CharReader> jsonReader(b.newCharReader());
	std::string jsonerr;

	if (!jsonReader->parse(strContent.c_str(), strContent.c_str()+strContent.length(), &jsonData, &jsonerr)) {
		LOG4CPLUS_ERROR(log, "." + this->getId(), strContent << " not json data." << jsonerr);
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

	if (dest != "this") {
		jsonData["id"] = dest;
		model::EventType_t evt(jsonData);
		this->PushEvent(evt);
		return;
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
			LOG4CPLUS_DEBUG(log, "." + this->getId(), agentid << " state:" << pe->getStateId());
			if (pe->getStateId() == "Ready") {
				findAgent = agentid;
				goto _findAgent;
			}
		}
		
		LOG4CPLUS_DEBUG(log, "." + this->getId(), " All device:" << this->GetExtensions().size());

		if (lastAgent == ""){
			for (auto it : this->GetExtensions())
			{
				LOG4CPLUS_DEBUG(log, "." + this->getId(), it.first << " state:" << it.second->getStateId());
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
					LOG4CPLUS_DEBUG(log, "." + this->getId(), it.first << " state:" << it.second->getStateId());
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
					LOG4CPLUS_DEBUG(log, "." + this->getId(), it.first << " state:" << it.second->getStateId());
					if (it.second->getStateId() == "Ready"){
						findAgent = it.first;
						break;
					}
				}
			}
		}
		
	_findAgent:
		lastAgent = findAgent;
		LOG4CPLUS_DEBUG(log, "." + this->getId(), " find agent:" << findAgent);
		if (!findAgent.empty()){
			Json::Value ext = this->getExtension(findAgent)->getVar("_agent.Device");
			if (ext.isString())
			{
				std::string cmd = "bgapi uuid_transfer " + uuid +" " + ext.asString() + " XML default";
				esl_status_t status = esl_send(&m_Handle, cmd.c_str());
				LOG4CPLUS_DEBUG(log, "." + this->getId(), " esl_send:" << cmd << ", status:" << status);
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
		display = dialStringFindNumber(caller);

	if (param["sessionID"].isString())
		sessionId = param["sessionID"].asString();

	setSessionDevice(sessionId, dialStringFindNumber(caller));

	std::string jobid = helper::uuid();
	setJobSession(jobid, sessionId);

	std::string cmd = "bgapi originate {origination_uuid=" + sessionId + "}" + caller + " &bridge({origination_caller_id_number=" + display + "}" + called + ")" + "\nJob-UUID:" + jobid + "\n\n";

	esl_status_t status = esl_send(&m_Handle, cmd.c_str());
	LOG4CPLUS_DEBUG(log, "." + sessionId, " esl_send:" << cmd << ", status:" << status);

	return true;

}
bool FreeSwitchModule::MakeConnection(Json::Value & param, log4cplus::Logger & log)
{
	std::string called = "";
	std::string sessionId = "";
	std::string caller = "";

	if (param["called"].isString())
		called = param["called"].asString();

	if (param["caller"].isString())
		caller = param["caller"].asString();

	if (param["sessionID"].isString())
		sessionId = param["sessionID"].asString();

	
	setSessionDevice(sessionId, dialStringFindNumber(called));

	called = toDialString(called, sessionId, caller);
	std::string jobid = helper::uuid();
	setJobSession(jobid, sessionId);

	std::string cmd = "bgapi originate " + called + " &park()\nJob-UUID:" + jobid + "\n\n";

	esl_status_t status = esl_send(&m_Handle, cmd.c_str());
	LOG4CPLUS_DEBUG(log, "." + sessionId, " esl_send:" << cmd << ", status:" << status);
	return true;

}
bool FreeSwitchModule::ClearConnection(Json::Value & param, log4cplus::Logger & log)
{
	std::string sessionId = "";

	if (param["sessionID"].isString())
		sessionId = param["sessionID"].asString();

	std::string jobid = helper::uuid();
	setJobSession(jobid, sessionId);

	std::string cmd = "bgapi uuid_kill " + sessionId + "\nJob-UUID:" + jobid + "\n\n";
	esl_status_t status = esl_send(&m_Handle, cmd.c_str());
	LOG4CPLUS_DEBUG(log, "." + sessionId, " esl_send:" << cmd << ", status:" << status);

	return true;
}

bool FreeSwitchModule::StartRecord(Json::Value & param, log4cplus::Logger & log)
{
	std::string sessionId = "";
	std::string filename = "";

	if (param["ConnectionID"].isString())
		sessionId = param["ConnectionID"].asString();

	if (param["filename"].isString())
		filename = param["filename"].asString();

	std::string jobid = helper::uuid();
	setJobSession(jobid, sessionId);

	std::string cmd = "bgapi uuid_record " + sessionId + " start " + filename + "\nJob-UUID:" + jobid + "\n\n";
	esl_status_t status = esl_send(&m_Handle, cmd.c_str());
	LOG4CPLUS_DEBUG(log, "." + sessionId, " esl_send:" << cmd << ", status:" << status);
	return true;
}

bool FreeSwitchModule::Divert(Json::Value & param, log4cplus::Logger & llog)
{
	std::string called = "";
	std::string sessionId = "";
	std::string display = "";

	if (param["called"].isString())
		called = param["called"].asString();

	if (param["display"].isString())
		param["display"].asString();

	if (param["sessionID"].isString())
		sessionId = param["sessionID"].asString();

	std::string cmd = esl_execute_data("bridge", called.c_str(), sessionId.c_str(), false, false);
	esl_status_t status = esl_send(&m_Handle, cmd.c_str());
	LOG4CPLUS_DEBUG(log, "." + sessionId, " esl_send:" << cmd << ", status:" << status);

	return true;
}

bool FreeSwitchModule::PlayFile(Json::Value & param, log4cplus::Logger & llog)
{
	std::string sessionId;
	std::string filename;

	if (param["sessionID"].isString())
		sessionId = param["sessionID"].asString();

	if (param["filename"].isString())
		filename = param["filename"].asString();

	std::string cmd = esl_execute_data("playback", filename.c_str(), sessionId.c_str(), false, false);
	esl_status_t status = esl_send(&m_Handle, cmd.c_str());
	LOG4CPLUS_DEBUG(log, "." + sessionId, " esl_send:" << cmd << ", status:" << status);
	return true;
}

std::string esl_execute_data(const char * app, const char * arg, const char * uuid, bool eventlock, bool async)
{

	char cmd_buf[128] = "sendmsg";
	char app_buf[512] = "";
	char arg_buf[4096] = "";
	const char *el_buf = "event-lock: true\n";
	const char *bl_buf = "async: true\n";
	char send_buf[5120] = "";


	if (uuid) {
		snprintf(cmd_buf, sizeof(cmd_buf), "sendmsg %s", uuid);
	}

	if (app) {
		snprintf(app_buf, sizeof(app_buf), "execute-app-name: %s\n", app);
	}

	if (arg) {
		snprintf(arg_buf, sizeof(arg_buf), "execute-app-arg: %s\n", arg);
	}

	snprintf(send_buf, sizeof(send_buf), "%s\ncall-command: execute\n%s%s%s%s\n\n",
		cmd_buf, app_buf, arg_buf, eventlock ? el_buf : "", async ? bl_buf : "");
	
	return send_buf;

}

std::string FreeSwitchModule::dialStringFindNumber(const std::string & dialString)
{
	std::string number;
	number = dialString.substr(0, dialString.find("%"));
	number = number.substr(0, number.find("@"));
	number = number.substr(min(number.find_last_of("/") + 1, number.length()));
	return number;
}

std::string FreeSwitchModule::toDialString(const std::string & sipId, const std::string & uuid, const std::string & caller)
{
	std::string called = "user/" + sipId;
	std::string _caller = caller;
	for (uint32_t i = 0; i < this->routeConfig.size(); i++) {
		std::string pattern = this->routeConfig[i]["regex_pattern"].asString();
		std::regex regPattern(pattern);
		if (std::regex_match(sipId, regPattern)) {
			std::string ip = this->routeConfig[i]["ip"].asString();
			uint32_t port = this->routeConfig[i]["port"].asUInt();
			if(_caller.empty())
				_caller = this->routeConfig[i]["defaultcaller"].asString();

			called = "sofia/external/" + sipId + "@" + ip + ":" + std::to_string(port);
			break;
		}
	}

	std::string dialstring = "{origination_uuid=" + uuid;
	if (!_caller.empty())
		dialstring.append(",origination_caller_id_number=" + _caller);
	dialstring.append("}");
	dialstring.append(called);

	return dialstring;
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
			LOG4CPLUS_DEBUG(log, "", fp << ":" << line << " " << func << "() " << data);
		}
		else if (level == ESL_LOG_LEVEL_INFO){
			LOG4CPLUS_INFO(log, "", fp << ":" << line << " " << func << "() " << data);
		}
		else if (level == ESL_LOG_LEVEL_NOTICE) {
			LOG4CPLUS_INFO(log, "", fp << ":" << line << " " << func << "() " << data);
		}
		else if (level == ESL_LOG_LEVEL_WARNING) {
			LOG4CPLUS_WARN(log, "", fp << ":" << line << " " << func << "() " << data);
		}
		else if (level == ESL_LOG_LEVEL_ERROR) {
			LOG4CPLUS_ERROR(log, "", fp << ":" << line << " " << func << "() " << data);
		}
		else if (level == ESL_LOG_LEVEL_CRIT) {
			LOG4CPLUS_FATAL(log, "", fp << ":" << line << " " << func << "() " << data);
		}
		free(data);
	}

	va_end(ap);
}

void FreeSwitchModule::ConnectFS()
{
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " Run  FreeSwitch module");

	//esl_handle_t handle = { { 0 } };

	while (m_bRunning)
	{
		LOG4CPLUS_DEBUG(log, "." + this->getId(), " connect freeswitch " << m_Host << ":" << m_Port);

		esl_status_t status = esl_connect_timeout(&m_Handle, m_Host.c_str(), m_Port, m_User.c_str(), m_Password.c_str(),5*1000);
		
		if (!m_Handle.connected){
			LOG4CPLUS_ERROR(log, "." + this->getId(), " connect freeswitch " << m_Host << ":" << m_Port << " error,"
				<< m_Handle.errnum << " " << m_Handle.err);
			if (m_bRunning)
				std::this_thread::sleep_for(std::chrono::seconds(5));
			continue;
		}

		LOG4CPLUS_INFO(log, "." + this->getId(), " Connected to FreeSWITCH");

		esl_events(&m_Handle, ESL_EVENT_TYPE_JSON, "All");
		esl_send(&m_Handle, "nixevent json PLAYBACK_START PLAYBACK_START CHANNEL_UNPARK CODEC CALL_UPDATE CHANNEL_CALLSTATE CHANNEL_STATE CHANNEL_HANGUP_COMPLETE API HEARTBEAT RE_SCHEDULE RECV_RTCP_MESSAGE MESSAGE_QUERY MESSAGE_WAITING PRESENCE_IN CUSTOM sofia::pre_register sofia::register_attempt");
		LOG4CPLUS_DEBUG(log, "." + this->getId(), " " << m_Handle.last_sr_reply);

		while (m_bRunning){
			esl_status_t status = esl_recv_event_timed(&m_Handle, 1000, true, NULL);
			if (status == ESL_SUCCESS){
				if (m_Handle.last_event && m_Handle.last_event->body) {
					Json::Value event;
					Json::CharReaderBuilder b;
					std::shared_ptr<Json::CharReader> jsonReader(b.newCharReader());
					std::string jsonerr;

					if (jsonReader->parse(m_Handle.last_event->body, m_Handle.last_event->body + std::strlen(m_Handle.last_event->body), &event, &jsonerr) && event.isObject()) {

						std::string eventName;
						if (event["Event-Name"].isString()) {
							eventName = event["Event-Name"].asString();
							event.removeMember("Event-Name");
						}

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
							|| eventName == "CHANNEL_EXECUTE_COMPLETE"
							|| eventName == "CHANNEL_PROGRESS_MEDIA"
							|| eventName == "BACKGROUND_JOB")
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


							if (eventName == "BACKGROUND_JOB"){
								std::string sessionId;
								getJobSession(evt.event["param"]["JobUUID"].asString(), sessionId);
								evt.event["param"]["UniqueID"] = sessionId;
							}

							std::string sessionId = evt.event["param"]["UniqueID"].asString();
							evt.event["param"].removeMember("UniqueID");

							std::string device;
							if (getSessionDevice(sessionId, device) == false){
								if (dir == "inbound" && !caller.empty())
									setSessionDevice(sessionId, caller.substr(0, caller.find("%")));
								else if (dir == "outbound" && !called.empty())
									setSessionDevice(sessionId, called.substr(0, called.find("%")));
								
							}
							

							//Channel _ Create：通道创建事件
							//Channel _ Progress：通道振铃事件
							//Channel _ Answer：通道应答事件
							//Channel _ Bridge：通道桥接事件
							//Channel _ Hangup：通道挂断事件


							
							if (getSessionDevice(sessionId,device)) {
								evt.event["id"] = device;
								evt.event["event"] = eventName;
								evt.event["param"]["sessionID"] = sessionId;
								this->PushEvent(evt);
							}
							else {
								LOG4CPLUS_ERROR(log, "." + this->getId(), "Channel is already destroy:" << m_Handle.last_event->body);
							}

							if (eventName == "BACKGROUND_JOB") {
								removeJobSession(evt.event["JobUUID"].asString());
									
							}
							else if(eventName == "CHANNEL_DESTROY") {
								removeSessionDevice(sessionId);
							}

						}
						else {
							LOG4CPLUS_DEBUG(log, "." + this->getId(), " " << m_Handle.last_event->body);
						}
					}
					
				}
			}
			else if (status == ESL_BREAK)
				continue;
			else{
				LOG4CPLUS_ERROR(log, "." + this->getId(), " " << m_Handle.err);
				break;
			}
		}

		esl_disconnect(&m_Handle);
	}
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " Stoped  FreeSwitch module");
	log4cplus::threadCleanup();
}
void FreeSwitchModule::setSessionDevice(const TsessionID & sessionId, const std::string & device)
{
	std::unique_lock<std::mutex> lck(m_sessionMtx);
	m_Session_DeviceId[sessionId] = device;
}

bool FreeSwitchModule::getSessionDevice(const TsessionID & sessionId, std::string & device)
{
	std::unique_lock<std::mutex> lck(m_sessionMtx);
	const auto & it = m_Session_DeviceId.find(sessionId);
	if (it != m_Session_DeviceId.end()){
		device = it->second;
		return true;
	}
	return false;
}

void FreeSwitchModule::removeSessionDevice(const TsessionID & sessionId)
{
	std::unique_lock<std::mutex> lck(m_sessionMtx);
	m_Session_DeviceId.erase(sessionId);
}

void FreeSwitchModule::setJobSession(const TJobID & job, const TsessionID & sessionId)
{
	std::unique_lock<std::mutex> lck(m_sessionMtx);
	m_Job_Session[job] = sessionId;
}

bool FreeSwitchModule::getJobSession(const TJobID & job, TsessionID & sessionId)
{
	std::unique_lock<std::mutex> lck(m_sessionMtx);
	const auto & it = m_Job_Session.find(job);
	if (it != m_Job_Session.end()) {
		sessionId = it->second;
		return true;
	}
	return false;
}

void FreeSwitchModule::removeJobSession(const TJobID & job)
{
	std::unique_lock<std::mutex> lck(m_sessionMtx);
	m_Job_Session.erase(job);
}

void FreeSwitchModule::run()
{
	LOG4CPLUS_INFO(log, "." + this->getId(), " Starting...");
	try
	{
		DataBase::MySqlModule * mysqlmodule;
		for (auto & m : model::ProcessModule::g_Modules)
		{
			if (m->getId().find("mysql") != std::string::npos)
			{
				mysqlmodule = dynamic_cast<DataBase::MySqlModule*>(m.get());
			}
		}

		if (mysqlmodule){
			routeConfig = mysqlmodule->executeQuery("SELECT * from sip_route left join sip_gateway on sip_route.gateway_id = sip_gateway.id where sip_gateway.ip <> \"\" order by level ASC ;");
			LOG4CPLUS_DEBUG(log, "." + this->getId(), " get route config from database:" << routeConfig.toStyledString());
		}
		else {
			LOG4CPLUS_ERROR(log, "." + this->getId(), "not find mysql module");
		}

		while (m_bRunning)
		{
			try
			{
				model::EventType_t Event;
				if (m_RecEvtBuffer.Get(Event) && !Event.event.isNull())
				{
					LOG4CPLUS_DEBUG(log, "." + this->getId(), "event buffer size:" << m_RecEvtBuffer.size());
					const Json::Value & jsonEvent = Event.event;
					std::string peId;
					if (jsonEvent["id"].isString()) {
						peId = jsonEvent["id"].asString();
					}

					if (peId.empty()) {
						Json::FastWriter writer;
						LOG4CPLUS_WARN(log, "." + this->getId(), " not find device:" << writer.write(Event.event));
						continue;
					}

					apr_ssize_t klen = peId.length();
					uint32_t hash = apr_hashfunc_default(peId.c_str(),  &klen);
					hash %= m_executeThread.size();
					m_executeThread[hash].eventQueue.Put(Event);

				}
			}
			catch (std::exception & e)
			{
				LOG4CPLUS_ERROR(log, "." + this->getId(), e.what());
			}
		}

	}
	catch (std::exception & e)
	{
		LOG4CPLUS_ERROR(log, "." + this->getId(), e.what());
	}

	LOG4CPLUS_INFO(log, "." + this->getId(), " Stoped.");
	log4cplus::threadCleanup();
}
void FreeSwitchModule::execute(helper::CEventBuffer<model::EventType_t> * eventQueue)
{
	LOG4CPLUS_INFO(log, "." + this->getId(), " Process thread Starting...");
	while (m_bRunning)
	{
		try
		{
			model::EventType_t Event;
			if (eventQueue->Get(Event, 1000 * 5) && !Event.event.isNull())
			{
				const Json::Value & jsonEvent = Event.event;
				std::string peId;
				if (jsonEvent["id"].isString()) {
					peId = jsonEvent["id"].asString();
				}

				if (peId.empty()) {
					Json::FastWriter writer;
					LOG4CPLUS_WARN(log, "." + this->getId(), " not find device:" << writer.write(Event.event));
					continue;
				}


				if (this->getPerformElement(peId) == nullptr) {

					for (auto & it : this->m_device_StateMachine) {
						std::regex regPattern(it.first);
						if (std::regex_match(peId, regPattern)) {
							model::PerformElementPtr peptr(new FreeSwitchDevice(this, peId, it.second));
							if (peptr != nullptr && this->addPerformElement(peId, peptr)) {
								LOG4CPLUS_INFO(log, "." + this->getId(), "current session size:" << getPerformElementCount());
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

					if (extptr->IsClosed()) {
						this->removePerfromElement(peId);
						LOG4CPLUS_INFO(log, "." + this->getId(), "current session size:" << getPerformElementCount());
					}


				}
				else {
					LOG4CPLUS_ERROR(log, "." + this->getId(), " not find device:" << peId);
				}
			}
			else {
				fsm::threadIdle();
			}
		}
		catch (std::exception & e)
		{
			LOG4CPLUS_ERROR(log, "." + this->getId(), e.what());
		}
	}

	LOG4CPLUS_INFO(log, "." + this->getId(), " Process thread Stoped.");
	fsm::threadCleanup();
	log4cplus::threadCleanup();
}
}
}

