#include "IVRModule.h"
#include "IVRExtension.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/json.h>


namespace chilli{
namespace IVR{


IVRModule::IVRModule(const std::string & id):ProcessModule(id)
{
	log =log4cplus::Logger::getInstance("chilli.IVRModule");
	LOG4CPLUS_DEBUG(log, "Constuction a IVR module.");
}


IVRModule::~IVRModule(void)
{
	if (m_Thread.joinable()){
		Stop();
	}

	LOG4CPLUS_DEBUG(log, "Destruction a IVR module.");
}

int IVRModule::Stop(void)
{
	LOG4CPLUS_DEBUG(log,"Stop  IVR module");
	bRunning = false;
	for (auto & it: m_Extensions){
		it.second->Stop();
	}

	if (m_Thread.joinable()){
		PushEvent(std::string());
		m_Thread.join();
	}

	return 0;
}

int IVRModule::Start()
{
	LOG4CPLUS_DEBUG(log, "Start  IVR module");
	if (!m_Thread.joinable()){
		bRunning = true;
		for (auto & it : m_Extensions) {
			it.second->Start();
		}
		m_Thread = std::thread(&IVRModule::run, this);	
	}
	return 0;
}

bool IVRModule::LoadConfig(const std::string & configContext)
{
	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if (config.Parse(configContext.c_str()) != XMLError::XML_SUCCESS){
		LOG4CPLUS_ERROR(log, "load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}


	for (XMLElement *child = config.FirstChildElement("Extension"); 
		child != nullptr; 
		child = child->NextSiblingElement("Extension")) {

		const char * num = child->Attribute("ExtensionNumber");
		const char * sm = child->Attribute("StateMachine");
		num = num ? num : "";
		sm = sm ? sm : "";
		if (this->m_Extensions.find(num) == this->m_Extensions.end())
		{
			model::ExtensionPtr ext(new IVRExtension(num, sm));
			this->m_Extensions[num] = ext;
		}
		else {
			LOG4CPLUS_ERROR(log, "alredy had extension:" << num);
		}
	}
	return true;
}

const model::ExtensionMap & IVRModule::GetExtension()
{
	return m_Extensions;
}

void IVRModule::fireSend(const std::string &strContent, const void * param)
{
	LOG4CPLUS_WARN(log, "fireSend not implement.");
}

void IVRModule::run()
{
	LOG4CPLUS_INFO(log, "Starting...");

	while (bRunning)
	{
		model::EventType_t Event;
		if (m_recEvtBuffer.Get(Event) && !Event.event.empty())
		{
			Json::Value jsonEvent;
			Json::Reader jsonReader;
			if (jsonReader.parse(Event.event, jsonEvent)){
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

				auto &it = m_Extensions.find(ext);

				if (it != m_Extensions.end()){

					it->second->pushEvent(Event);
				}
				else{
					LOG4CPLUS_ERROR(log, " not find extension by event:" << Event.event);
				}
	
			}
			else{
				LOG4CPLUS_ERROR(log, __FUNCTION__ ",event:" << Event.event << " not json data.");
			}
		}
	}
	LOG4CPLUS_INFO(log, "Stoped.");
	log4cplus::threadCleanup();
}
}
}
