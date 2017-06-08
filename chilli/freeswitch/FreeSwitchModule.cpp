#include <stdint.h>
#include <esl.h>
#include "FreeSwitchModule.h"
#include "FreeSwitchExtension.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/json.h>


namespace chilli{
namespace FreeSwitch{

	enum ExtType {
		FreeSwitchExtType =0,
		FreeSwitchACDType,
	};

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

			model::ExtensionConfigPtr extConfig = newExtensionConfig(this, num, sm, ExtType::FreeSwitchExtType);
			if (extConfig != nullptr) {
				extConfig->m_Vars.push_back(std::make_pair("_extension.Extension", num));
			}
			else {
				LOG4CPLUS_ERROR(log, "alredy had extension:" << num);
			}
		}
	}

	return true;
}


model::ExtensionPtr FreeSwitchModule::newExtension(const model::ExtensionConfigPtr & config)
{
	if (config != nullptr)
	{
		if (config->m_ExtType == ExtType::FreeSwitchExtType) {
			model::ExtensionPtr ext(new FreeSwitchExtension(this, config->m_ExtNumber, config->m_SMFileName));
			return ext;
		}
	}
	return nullptr;
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

		for (auto &it : this->GetExtensionConfig()) {
			if (it.second->m_ExtType == ExtType::FreeSwitchExtType)
			{

				std::string cmd = "api sofia status profile internal reg ";
				cmd.append(it.first);
				LOG4CPLUS_DEBUG(log, "send:" << cmd);
				esl_send(&handle, cmd.c_str());

			}
		}

		while (m_bRunning){
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

