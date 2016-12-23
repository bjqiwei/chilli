#include <stdint.h>
#include <esl.h>
#include "FreeSwitchModule.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/json.h>


namespace chilli{
namespace FreeSwitch{


FreeSwtichModule::FreeSwtichModule(const std::string & id):ProcessModule(id)
{
	log = log4cplus::Logger::getInstance("chilli.FreeSwtichModule");
	LOG4CPLUS_DEBUG(log, "Constuction a FreeSwitch module.");
}


FreeSwtichModule::~FreeSwtichModule(void)
{
	if (bRunning){
		Stop();
	}

	LOG4CPLUS_DEBUG(log, "Destruction a FreeSwitch module.");
}

int FreeSwtichModule::Stop(void)
{
	LOG4CPLUS_DEBUG(log, "Stop...  FreeSwitch module");
	bRunning = false;

	if (m_Thread.joinable()){
		m_Thread.join();
	}
	
	return 0;
}

int FreeSwtichModule::Start()
{
	LOG4CPLUS_DEBUG(log, "Start...  FreeSwitch module");
	if(!m_Thread.joinable()){
		bRunning = true;
		m_Thread = std::thread(&FreeSwtichModule::ConnectFS, this);
	}
	return 0;
}

bool FreeSwtichModule::LoadConfig(const std::string & configContext)
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

	return true;
}

const std::map<std::string, model::ExtensionPtr> & FreeSwtichModule::GetExtension()
{
	return m_Extension;
}

void FreeSwtichModule::fireSend(const std::string & strContent, const void * param)
{
	LOG4CPLUS_WARN(log, "fireSend not implement.");
}

void FreeSwtichModule::ConnectFS()
{
	LOG4CPLUS_DEBUG(log, "Run  FreeSwitch module");
	while (bRunning)
	{
		esl_handle_t handle = { { 0 } };

		esl_status_t status = esl_connect_timeout(&handle, m_Host.c_str(), m_Port, m_User.c_str(), m_Password.c_str(),10*1000);

		if (!handle.connected){
			LOG4CPLUS_ERROR(log, "connect freeswitch error");
			continue;
		}

		LOG4CPLUS_INFO(log, "Connected to FreeSWITCH");
		esl_events(&handle, ESL_EVENT_TYPE_JSON, "all");
		LOG4CPLUS_DEBUG(log, handle.last_sr_reply);

		while (bRunning){
			esl_status_t status = esl_recv_timed(&handle, 1000);
			if (status == ESL_SUCCESS){
				if (handle.last_event && handle.last_event->body) {
					LOG4CPLUS_DEBUG(log, handle.last_event->body);
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

