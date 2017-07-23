#include <stdint.h>
#include <esl.h>
#include "FreeSwitchModule.h"
#include "FreeSwitchExtension.h"
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

	return true;
}

void FreeSwitchModule::fireSend(const std::string & strContent, const void * param)
{
	LOG4CPLUS_WARN(log, "fireSend not implement.");
}

void FreeSwitchModule::processSend(const std::string & strContent, const void * param, bool & bHandled, model::Extension * ext)
{
}

void FreeSwitchModule::ConnectFS()
{
	LOG4CPLUS_DEBUG(log, "Run  FreeSwitch module");

	esl_handle_t handle = { { 0 } };

	while (m_bRunning)
	{
		LOG4CPLUS_DEBUG(log, "connect freeswitch " << m_Host << ":" << m_Port);

		esl_status_t status = esl_connect_timeout(&handle, m_Host.c_str(), m_Port, m_User.c_str(), m_Password.c_str(),5*1000);

		if (!handle.connected){
			LOG4CPLUS_ERROR(log, "connect freeswitch " << m_Host << ":" << m_Port << " error,"
				<< handle.errnum << " " << handle.err);
			if (m_bRunning)
				std::this_thread::sleep_for(std::chrono::seconds(5));
			continue;
		}

		LOG4CPLUS_INFO(log, "Connected to FreeSWITCH");

		esl_events(&handle, ESL_EVENT_TYPE_JSON, "all");
		LOG4CPLUS_DEBUG(log, handle.last_sr_reply);

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
			esl_status_t status = esl_recv_event_timed(&handle, 1000, true, NULL);
			if (status == ESL_SUCCESS){
				if (handle.last_event && handle.last_event->body) {
					Json::Reader reader;
					Json::Value event;
					if (reader.parse(handle.last_event->body, event) && event.isObject()) {
						if (event["Event-Name"].isString() && event["Event-Name"].asString() == "HEARTBEAT")
							continue;
						if (event["Event-Name"].isString() && event["Event-Name"].asString() == "RE_SCHEDULE")
							continue;
						if (event["Event-Name"].isString() && event["Event-Name"].asString() == "CHANNEL_EXECUTE")
							continue;
						if (event["Event-Name"].isString() && event["Event-Name"].asString() == "CHANNEL_EXECUTE_COMPLETE")
							continue;
						
						if (event["Event-Name"].isString() && event["Event-Name"].asString() == "CHANNEL_STATE")
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
							//event.removeMember("Caller-Caller-ID-Name");
							//event.removeMember("Caller-Channel-Name");
							//event.removeMember("Caller-Context");
							event.removeMember("Caller-Orig-Caller-ID-Name");
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

							model::EventType_t evt;
							for (auto & varname : event.getMemberNames()) {
								std::string newvarname = varname;
								helper::string::replaceString(newvarname, "-", "");
								evt.event[newvarname] = event[varname];
							}

							std::string Channel_Presence_ID;
							if (evt.event["ChannelPresenceID"].isString()){
								Channel_Presence_ID = evt.event["ChannelPresenceID"].asString();
							}
							
							std::string extNum = Channel_Presence_ID.substr(0, Channel_Presence_ID.find("@"));
							evt.event["extension"] = extNum;
							evt.event["event"] = evt.event["EventName"];

							this->PushEvent(evt);
						}
						else {
							LOG4CPLUS_DEBUG(log, handle.last_event->body);
						}
					}
					
				}
			}
			else if (status == ESL_BREAK)
				continue;
			else
				break;
		}

		esl_disconnect(&handle);
	}
	LOG4CPLUS_DEBUG(log, "Stoped  FreeSwitch module");
	log4cplus::threadCleanup();
}
}
}

