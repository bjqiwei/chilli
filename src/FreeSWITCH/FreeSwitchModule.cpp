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

		if (m_FSReceiveThread.joinable()) {
			m_FSReceiveThread.join();
		}

		if (m_FSSendThread.joinable())
		{
			m_FSSendThread.join();
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
		m_FSReceiveThread = std::thread(&FreeSwitchModule::receiveFS, this);
		m_FSSendThread = std::thread(&FreeSwitchModule::sendToFS, this);
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

void FreeSwitchModule::fireSend(const fsm::FireDataType & fireData, const void * param)
{
	LOG4CPLUS_TRACE(log, "." + this->getId(), " fireSend:" << fireData.event);
	
	bool bHandled = false;
	this->processSend(fireData, param, bHandled, log);

}

void FreeSwitchModule::processSend(const fsm::FireDataType & fireData, const void * param, bool & bHandled, log4cplus::Logger & log)
{
	const std::string & eventName = fireData.event;
	const std::string & typeName = fireData.type;
	const std::string & dest = fireData.dest;
	
	Json::Value newEvent;
	newEvent["id"] = dest;
	newEvent["event"] = fireData.event;
	newEvent["type"] = fireData.type;
	newEvent["param"] = fireData.param;
	model::EventType_t evt(new model::_EventType(newEvent));
	this->PushEvent(evt);
	return;
}
bool FreeSwitchModule::MakeCall(const Json::Value & param, log4cplus::Logger & log)
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

	std::string cmd = "bgapi originate {origination_uuid=" + sessionId + "}" + caller + " &bridge({origination_caller_id_number=" + display + "}" + called + ")" + "\nJob-UUID:" + jobid;
	m_FSSendBuffer.Put(std::make_shared<FSSendDataType>(sessionId,cmd));	

	return true;

}
bool FreeSwitchModule::MakeConnection(const Json::Value & param, log4cplus::Logger & log)
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

	std::string cmd = "bgapi originate " + called + " &park()\nJob-UUID:" + jobid;

	m_FSSendBuffer.Put(std::make_shared<FSSendDataType>(sessionId, cmd));
	return true;

}
bool FreeSwitchModule::ClearConnection(const Json::Value & param, log4cplus::Logger & log)
{
	std::string sessionId = "";

	if (param["sessionID"].isString())
		sessionId = param["sessionID"].asString();

	std::string jobid = helper::uuid();
	setJobSession(jobid, sessionId);

	std::string cmd = "bgapi uuid_kill " + sessionId + "\nJob-UUID:" + jobid;
	m_FSSendBuffer.Put(std::make_shared<FSSendDataType>(sessionId, cmd));

	return true;
}

bool FreeSwitchModule::StartRecord(const Json::Value & param, log4cplus::Logger & log)
{
	std::string sessionId = "";
	std::string filename = "";

	if (param["sessionID"].isString())
		sessionId = param["sessionID"].asString();

	if (param["filename"].isString())
		filename = param["filename"].asString();

	std::string jobid = helper::uuid();
	setJobSession(jobid, sessionId);

	std::string cmd = "bgapi uuid_record " + sessionId + " start " + filename + "\nJob-UUID:" + jobid;
	m_FSSendBuffer.Put(std::make_shared<FSSendDataType>(sessionId, cmd));
	return true;
}

bool FreeSwitchModule::StopRecord(const Json::Value & param, log4cplus::Logger & log)
{
	std::string sessionId = "";
	std::string filename = "";

	if (param["sessionID"].isString())
		sessionId = param["sessionID"].asString();

	if (param["filename"].isString())
		filename = param["filename"].asString();

	std::string jobid = helper::uuid();
	setJobSession(jobid, sessionId);

	std::string cmd = "bgapi uuid_record " + sessionId + " stop " + filename + "\nJob-UUID:" + jobid;
	m_FSSendBuffer.Put(std::make_shared<FSSendDataType>(sessionId, cmd));
	return true;
}

bool FreeSwitchModule::Divert(const Json::Value & param, log4cplus::Logger & llog)
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
	m_FSSendBuffer.Put(std::make_shared<FSSendDataType>(sessionId, cmd));

	return true;
}

bool FreeSwitchModule::PlayFile(const Json::Value & param, log4cplus::Logger & llog)
{
	std::string sessionId;
	std::string filename;

	if (param["sessionID"].isString())
		sessionId = param["sessionID"].asString();

	if (param["filename"].isString())
		filename = param["filename"].asString();

	std::string cmd = esl_execute_data("playback", filename.c_str(), sessionId.c_str(), false, false);
	m_FSSendBuffer.Put(std::make_shared<FSSendDataType>(sessionId, cmd));
	return true;
}

bool FreeSwitchModule::PlayFileAndCollects(const Json::Value & param, log4cplus::Logger & log)
{
	std::string sessionId;
	std::string filename;
	uint32_t min = 0;
	uint32_t max = 1;
	uint32_t tries = 3;
	uint32_t timeout = 10000;
	std::string terminators = "#";
	std::string & invalid_file = filename;
	//std::string var_name="_dtmf";
	//std::string regexp = "\d+";
	//uint32_t digit_timeout = 5000;


	if (param["sessionID"].isString())
		sessionId = param["sessionID"].asString();

	if (param["filename"].isString())
		filename = param["filename"].asString();

	if (param["min"].isUInt())
		min = param["min"].asUInt();
	
	if (param["max"].isUInt())
		max = param["max"].asUInt();
	
	if (param["tries"].isUInt())
		tries = param["tries"].asUInt();
	
	if (param["timeout"].isUInt())
		timeout = param["timeout"].asUInt();
	
	if (param["terminators"].isString() && !param["terminators"].asString().empty()) {
		terminators = param["terminators"].asString();
	}
	
	//if (param["digit_timeout"].isUInt())
		//digit_timeout = param["digit_timeout"].asUInt();
	


	std::string appdata = std::to_string(min) + " " + std::to_string(max) + " " + std::to_string(tries) + " " + std::to_string(timeout)
		+ " " + "" + terminators + " " + filename;// +" " + invalid_file + " " + var_name + " " + regexp + " " + std::to_string(digit_timeout);
	std::string cmd = esl_execute_data("play_and_get_digits", appdata.c_str(), sessionId.c_str(), false, false);
	m_FSSendBuffer.Put(std::make_shared<FSSendDataType>(sessionId, cmd));
	return true;
}

bool FreeSwitchModule::StartDTMFCollection(const Json::Value & param, log4cplus::Logger & log)
{
	std::string sessionId;

	if (param["sessionID"].isString())
		sessionId = param["sessionID"].asString();

	std::string cmd = esl_execute_data("start_dtmf", nullptr, sessionId.c_str(), false, false);
	m_FSSendBuffer.Put(std::make_shared<FSSendDataType>(sessionId, cmd));
	return true;
}

bool FreeSwitchModule::StopDTMFCollection(const Json::Value & param, log4cplus::Logger & log)
{
	std::string sessionId;

	if (param["sessionID"].isString())
		sessionId = param["sessionID"].asString();

	std::string cmd = esl_execute_data("stop_dtmf", nullptr, sessionId.c_str(), false, false);
	m_FSSendBuffer.Put(std::make_shared<FSSendDataType>(sessionId, cmd));
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

	snprintf(send_buf, sizeof(send_buf), "%s\ncall-command: execute\n%s%s%s%s\n",
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
			std::string port = this->routeConfig[i]["port"].asString();
			if(_caller.empty())
				_caller = this->routeConfig[i]["defaultcaller"].asString();

			called = "sofia/external/" + sipId + "@" + ip + ":" + port;
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

void FreeSwitchModule::receiveFS()
{
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " Run  FreeSwitch module");

	//esl_handle_t handle = { { 0 } };

	while (m_bRunning)
	{
		esl_global_set_default_logger(5);
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
		std::string cmd = "nixevent json PLAYBACK_START PLAYBACK_STOP CHANNEL_UNPARK CODEC CALL_UPDATE CHANNEL_CALLSTATE CHANNEL_STATE CHANNEL_HANGUP_COMPLETE API HEARTBEAT RE_SCHEDULE RECV_RTCP_MESSAGE MESSAGE_QUERY MESSAGE_WAITING PRESENCE_IN CUSTOM sofia::pre_register sofia::register_attempt";
		m_FSSendBuffer.Put(std::make_shared<FSSendDataType>("", cmd));
		LOG4CPLUS_DEBUG(log, "." + this->getId(), " " << m_Handle.last_sr_reply);

		while (m_bRunning){
			esl_status_t status = esl_recv_event_timed(&m_Handle, 1000, false, NULL);
			if (status == ESL_SUCCESS) {

				if (m_Handle.last_ievent == nullptr) {
					continue;
				}

				std::string eventName;
				Json::Value newEvt;

				for (esl_event_header_t * header = m_Handle.last_ievent->headers; header != nullptr; header = header->next)
				{
					std::string newvarname = header->name;
					if (newvarname == "Core-UUID" || newvarname == "FreeSWITCH-Hostname" || newvarname == "FreeSWITCH-Switchname" || newvarname == "FreeSWITCH-IPv4" || newvarname == "FreeSWITCH-IPv6"
						|| newvarname == "Event-Calling-File" || newvarname == "Event-Calling-Function" || newvarname == "Event-Calling-Line-Number" || newvarname == "Event-Sequence" || newvarname == "Caller-Dialplan"
						|| newvarname == "Caller-Caller-ID-Name" || newvarname == "Caller-Channel-Name" || newvarname == "Caller-Context" || newvarname == "Caller-Orig-Caller-ID-Name" || newvarname == "Caller-Network-Addr"
						|| newvarname == "Caller-Privacy-Hide-Name" || newvarname == "Caller-Privacy-Hide-Number" || newvarname == "Caller-Profile-Created-Time" || newvarname == "Caller-Profile-Index" || newvarname == "Caller-Screen-Bit"
						|| newvarname == "Caller-Source" || newvarname == "Channel-HIT-Dialplan" || newvarname == "Channel-Name" || newvarname == "Channel-Presence-ID" || newvarname == "Event-Date-GMT" || newvarname == "Event-Date-Timestamp"
						|| newvarname == "Caller-Unique-ID" || newvarname == "Caller-Direction" || newvarname == "CallerLogical-Direction" || newvarname == "Channel-Call-UUID" || newvarname == "Channel-Name" || newvarname == "Channel-Call-State"
						|| newvarname == "Presence-Call-Direction" || newvarname == "Channel-State-Number"
						)

						continue;

					if (newvarname.find("variable_") == std::string::npos) {
						helper::string::replaceString(newvarname, "-", "");
						newEvt["param"][newvarname] = header->value;
					}

				}

				if (m_Handle.last_ievent->event_id == ESL_EVENT_CHANNEL_EXECUTE_COMPLETE)
					eventName = newEvt["param"]["Application"].asString();
				else if (m_Handle.last_ievent->event_id == ESL_EVENT_BACKGROUND_JOB) {
					eventName = newEvt["param"]["JobCommand"].asString();

					std::string sessionId;
					getJobSession(newEvt["param"]["JobUUID"].asString(), sessionId);
					newEvt["param"]["UniqueID"] = sessionId;

					removeJobSession(newEvt["param"]["JobUUID"].asString());
				}
				else
					eventName = newEvt["param"]["EventName"].asString();

				if (m_Handle.last_ievent->body) {
					newEvt["param"]["body"] = m_Handle.last_ievent->body;
				}

				std::string caller = newEvt["param"]["CallerANI"].asString();
				std::string called = newEvt["param"]["CallerDestinationNumber"].asString();
				std::string dir = newEvt["param"]["CallDirection"].asString();

				std::string sessionId = newEvt["param"]["UniqueID"].asString();
				newEvt["param"].removeMember("UniqueID");

				std::string device;
				if (getSessionDevice(sessionId, device) == false) {
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



				if (getSessionDevice(sessionId, device)) {
					newEvt["id"] = device;
					newEvt["event"] = eventName;
					newEvt["param"]["sessionID"] = sessionId;
					newEvt["type"] = "fsevent";
					this->PushEvent(model::EventType_t(new model::_EventType(newEvt)));
				}
				else {
					LOG4CPLUS_WARN(log, "." + this->getId(), "Channel is already destroy:" << m_Handle.last_event->body);
				}

				if (eventName == "CHANNEL_DESTROY") {
					removeSessionDevice(sessionId);
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
void FreeSwitchModule::sendToFS()
{
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " Run  FreeSwitch send thread");

	//esl_handle_t handle = { { 0 } };

	while (m_bRunning)
	{
		std::shared_ptr<FSSendDataType> sendData;
		if (m_FSSendBuffer.Get(sendData,1000) && sendData)
		{
			if (m_Handle.connected){
				esl_status_t status = esl_send(&m_Handle, sendData->data.c_str());
				LOG4CPLUS_DEBUG(log, "." + sendData->sessionId, " esl_send:" << sendData->data << ", status:" << status);
			}
			else {
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				m_FSSendBuffer.Put(sendData);
			}
		}
	
	}
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " Stoped  FreeSwitch send thread");
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
				if (m_RecEvtBuffer.Get(Event) && !Event->eventName.empty())
				{
					static uint64_t sum = 0;
					LOG4CPLUS_DEBUG(log, "." + this->getId(), "event buffer size:" << m_RecEvtBuffer.size() << ":" << ++sum);
					const Json::Value & jsonEvent = Event->jsonEvent;
					std::string peId = Event->id;

					if (peId.empty()) {
						LOG4CPLUS_WARN(log, "." + this->getId(), " not find device:" << Event->origData);
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
			if (eventQueue->Get(Event, 1000 * 1) && !Event->eventName.empty())
			{
				const Json::Value & jsonEvent = Event->jsonEvent;
				std::string peId = Event->id;

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

