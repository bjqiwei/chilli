#include <stdint.h>
#include <esl.h>
#include "FreeSwitchModule.h"
#include "FreeSwitchExtension.h"
#include "FreeSwitchCall.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/json.h>
#include "../stringHelper.h"


namespace chilli{
namespace FreeSwitch{

FreeSwitchModule::FreeSwitchModule(const std::string & id):ProcessModule(id)
{
	log = log4cplus::Logger::getInstance("chilli.FreeSwitchModule");
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
	LOG4CPLUS_DEBUG(log, "Start...  FreeSwitch module");
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
		LOG4CPLUS_ERROR(log, "load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}
	tinyxml2::XMLElement * eConfig = config.FirstChildElement();
	m_Host = eConfig->Attribute("host") ? eConfig->Attribute("host"):"";
	m_Port = eConfig->IntAttribute("port");
	m_User = eConfig->Attribute("user") ? eConfig->Attribute("user") : "";
	m_Password = eConfig->Attribute("password") ? eConfig->Attribute("password") : "";

	// extensions 
	XMLElement * extensions = eConfig->FirstChildElement("Extensions");

	if (extensions != nullptr) {

		for (XMLElement *child = extensions->FirstChildElement("Extension");
			child != nullptr;
			child = child->NextSiblingElement("Extension"))
		{

			const char * num = child->Attribute("ExtensionNumber");
			const char * sm = child->Attribute("StateMachine");

			num = num ? num : "";
			sm = sm ? sm : "";

			model::ExtensionPtr ext(new FreeSwitchExtension(this, num, sm));
			if (ext != nullptr && addExtension(num, ext)) {
				ext->setVar("_extension.Extension", num);
			}
			else {
				LOG4CPLUS_ERROR(log, "alredy had extension:" << num);
			}
		}
	}

	// extensions 
	XMLElement * call = eConfig->FirstChildElement("Call");
	if (call != nullptr){
		const char * num = call->Attribute("ExtensionNumber");
		const char * sm = call->Attribute("StateMachine");
		model::ExtensionPtr ext(new FreeSwitchCall(this, num, sm));
		if (ext != nullptr && addExtension(num, ext)) {
			ext->setVar("_extension.Extension", num);
			m_CallExt = num;
		}
		else {
			LOG4CPLUS_ERROR(log, "alredy had extension:" << num);
		}
	}

	return true;
}

void FreeSwitchModule::fireSend(const std::string & strContent, const void * param)
{
	LOG4CPLUS_WARN(log, "fireSend not implement.");
}

void FreeSwitchModule::processSend(const std::string & strContent, const void * param, bool & bHandled, model::Extension * ext)
{
	log4cplus::Logger log = ext->getLogger();
	Json::Value jsonEvent;
	Json::Reader jsonReader;
	if (!jsonReader.parse(strContent, jsonEvent) || !jsonEvent.isObject()) {
		LOG4CPLUS_ERROR(log, strContent << " not json object.");
		return;
	}

	std::string eventName;
	std::string typeName;
	std::string dest;

	if (jsonEvent["type"].isString()) {
		typeName = jsonEvent["type"].asString();
	}

	if (typeName != "cmd") {
		return;
	}

	if (jsonEvent["dest"].isString()) {
		dest = jsonEvent["dest"].asString();
	}

	if (dest != "this") {
		return;
	}

	if (jsonEvent["event"].isString()) {
		eventName = jsonEvent["event"].asString();
	}

	if (eventName == "MakeCall")
	{
		std::string calling = "";
		std::string called = "";
		std::string uuid = "";

		if (jsonEvent["param"]["calling"].isString())
			calling = jsonEvent["param"]["calling"].asString();

		if (jsonEvent["param"]["called"].isString())
			called = jsonEvent["param"]["called"].asString();

		if (jsonEvent["param"]["ConnectionID"].isString())
			uuid = jsonEvent["param"]["ConnectionID"].asString();

		std::string cmd = "api originate {origination_uuid=" + uuid + "}user/" + calling + " &bridge(sofia/external/";
		cmd.append(called);
		cmd.append("@192.168.1.254)");
		esl_send(&m_Handle, cmd.c_str());

		bHandled = true;
	}
	else if (eventName == "ClearCall")
	{
		std::string uuid = "";

		if (jsonEvent["param"]["ConnectionID"].isString())
			uuid = jsonEvent["param"]["ConnectionID"].asString();

		std::string cmd = "api uuid_kill " + uuid;
		esl_send(&m_Handle, cmd.c_str());

		bHandled = true;
	}
	else if (eventName == "StartRecord")
	{
		std::string uuid = "";
		std::string filename = "";

		if (jsonEvent["param"]["ConnectionID"].isString())
			uuid = jsonEvent["param"]["ConnectionID"].asString();

		if (jsonEvent["param"]["filename"].isString())
			filename = jsonEvent["param"]["filename"].asString();

		std::string cmd = "api uuid_record " + uuid + " start " + filename;
		esl_send(&m_Handle, cmd.c_str());

		bHandled = true;
	}
}

void FreeSwitchModule::ConnectFS()
{
	LOG4CPLUS_DEBUG(log, "Run  FreeSwitch module");

	//esl_handle_t handle = { { 0 } };

	while (m_bRunning)
	{
		LOG4CPLUS_DEBUG(log, "connect freeswitch " << m_Host << ":" << m_Port);

		esl_status_t status = esl_connect_timeout(&m_Handle, m_Host.c_str(), m_Port, m_User.c_str(), m_Password.c_str(),5*1000);

		if (!m_Handle.connected){
			LOG4CPLUS_ERROR(log, "connect freeswitch " << m_Host << ":" << m_Port << " error,"
				<< m_Handle.errnum << " " << m_Handle.err);
			if (m_bRunning)
				std::this_thread::sleep_for(std::chrono::seconds(5));
			continue;
		}

		LOG4CPLUS_INFO(log, "Connected to FreeSWITCH");

		esl_events(&m_Handle, ESL_EVENT_TYPE_JSON, "all");
		LOG4CPLUS_DEBUG(log, m_Handle.last_sr_reply);

		/*
		for (auto &it : this->GetExtensions()) {
			if (typeid(*it.second) == typeid(FreeSwitchExtension))
			{

				std::string cmd = "api sofia status profile internal reg ";
				cmd.append(it.first);
				LOG4CPLUS_DEBUG(log, "send:" << cmd);
				if (ESL_SUCCESS == esl_send_recv_timed(&handle, cmd.c_str(), 2000)) {
					LOG4CPLUS_DEBUG(log, handle.last_sr_event->body);
					std::string response = handle.last_sr_event->body;

					if (response.length() < 300)
						continue;
					
					model::EventType_t evt;
					evt.event["extension"] = it.first;
					evt.event["event"] = "GetStatus";
					std::string name = "Status:";
					size_t start = response.find(name);				
					if (start != std::string::npos) {
						response = response.substr(start + name.length());
						helper::string::ltrim(response);
						std::string value = response.substr(0,response.find_first_of("(\n"));
						evt.event["Status"] = value;
					}

					response = handle.last_sr_event->body;
					name = "Auth-User:";
					start = response.find(name);
					if (start != std::string::npos) {
						response = response.substr(start + name.length());
						helper::string::ltrim(response);
						std::string value = response.substr(0, response.find_first_of("(\n"));
						evt.event["Auth-User"] = value;
					}
					this->PushEvent(evt);
				}
			}
		}
		*/
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
						}
						if(eventName == "HEARTBEAT")
							continue;
						if (eventName == "RE_SCHEDULE")
							continue;
						if (eventName == "CHANNEL_EXECUTE")
							continue;
						if (eventName == "CHANNEL_EXECUTE_COMPLETE")
							continue;
						if (eventName == "API")
							continue;
						
						if (eventName == "CHANNEL_CREATE" 
							|| eventName == "CHANNEL_PROGRESS"
							|| eventName == "CHANNEL_ANSWER"
							|| eventName == "CHANNEL_BRIDGE"
							|| eventName == "CHANNEL_HANGUP"
							|| eventName == "CHANNEL_DESTROY")
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
							//event.removeMember("Caller-Dialplan");
							//event.removeMember("Caller-Caller-ID-Name");
							//event.removeMember("Caller-Channel-Name");
							event.removeMember("Caller-Context");
							//event.removeMember("Caller-Orig-Caller-ID-Name");
							event.removeMember("Caller-Network-Addr");
							event.removeMember("Caller-Privacy-Hide-Name");
							event.removeMember("Caller-Privacy-Hide-Number");
							event.removeMember("Caller-Profile-Created-Time");
							event.removeMember("Caller-Profile-Index");
							event.removeMember("Caller-Screen-Bit");
							event.removeMember("Caller-Source");
							event.removeMember("Channel-HIT-Dialplan");
							//event.removeMember("Channel-Name");
							//event.removeMember("Channel-Presence-ID");
							event.removeMember("Event-Date-GMT");
							event.removeMember("Event-Date-Timestamp");
							event.removeMember("Caller-Unique-ID");
							//event.removeMember("Unique-ID");

							std::string caller = event["Caller-ANI"].asString();
							std::string called = event["Caller-Destination-Number"].asString();

							model::EventType_t evt;
							for (auto & varname : event.getMemberNames()) {
								std::string tmp = varname.substr(0, sizeof("variable_")-1);
								if (tmp != "variable_"){
									std::string newvarname = varname;
									helper::string::replaceString(newvarname, "-", "");
									evt.event[newvarname] = event[varname];
								}
							}

							if (caller != "0000000000")
								evt.event["extension"] = caller;
							else
								evt.event["extension"] = called;
							
				
							evt.event["event"] = evt.event["EventName"];
							evt.event["ConnectionID"] = evt.event["UniqueID"];

							//Channel _ Create：通道创建事件
							//Channel _ Progress：通道振铃事件
							//Channel _ Answer：通道应答事件
							//Channel _ Bridge：通道桥接事件
							//Channel _ Hangup：通道挂断事件

							this->PushEvent(evt);

							evt.event["extension"] = m_CallExt;
							this->PushEvent(evt);
						}
						else {
							LOG4CPLUS_DEBUG(log, m_Handle.last_event->body);
						}
					}
					
				}
			}
			else if (status == ESL_BREAK)
				continue;
			else
				break;
		}

		esl_disconnect(&m_Handle);
	}
	LOG4CPLUS_DEBUG(log, "Stoped  FreeSwitch module");
	log4cplus::threadCleanup();
}
}
}

