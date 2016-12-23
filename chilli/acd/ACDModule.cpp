#include "ACDModule.h"
#include "ACDExtension.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/json.h>


namespace chilli{
namespace ACD{


ACDModule::ACDModule(const std::string & id):ProcessModule(id)
{
	log =log4cplus::Logger::getInstance("chilli.ACDModule");
	LOG4CPLUS_DEBUG(log,"Constuction a ACD module.");
}


ACDModule::~ACDModule(void)
{
	if (bRunning){
		Stop();
	}

	LOG4CPLUS_DEBUG(log,"Destruction a ACD module.");
}

int ACDModule::Stop(void)
{
	LOG4CPLUS_DEBUG(log,"Stop  ACD module");
	bRunning = false;
	for (auto & it: m_Session){
		it.second->Stop();
	}

	if (m_Thread.joinable()) {
		PushEvent(std::string());
		m_Thread.join();
	}

	return 0;
}

int ACDModule::Start()
{
	LOG4CPLUS_DEBUG(log, "Start  ACD module");
	while (!bRunning)
	{
		bRunning = true;
		std::thread m_Thread = std::thread(&ACDModule::run, this);
	}
	return 0;
}

bool ACDModule::LoadConfig(const std::string & configContext)
{
	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if(config.Parse(configContext.c_str()) != XMLError::XML_SUCCESS) 
	{ 
		LOG4CPLUS_ERROR(log, "load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}
	
	for (XMLElement *child = config.FirstChildElement("Extension");
		child != nullptr;
		child = child->NextSiblingElement("Extension"))
	{
		const char * num = child->Attribute("ExtensionNumber");
		const char * sm = child->Attribute("StateMachine");
		num = num ? num : "";
		sm = sm ? sm : "";

		if (this->m_Extension.find(num) == this->m_Extension.end())
		{
			model::ExtensionPtr ext(new ACDExtension(num, sm));
			this->m_Extension[num] = ext;
		}
		else {
			LOG4CPLUS_ERROR(log, "alredy had extension:" << num);
		}
	}
	
	return true;
}

const model::ExtensionMap & ACDModule::GetExtension()
{
	return m_Extension;
}

void ACDModule::fireSend(const std::string & strContent, const void * param)
{
	LOG4CPLUS_WARN(log, "fireSend not implement.");
}

model::ExtensionPtr ACDModule::GetSession(const std::string & sessionid, const std::string & eventName, const std::string & ext)
{
	std::lock_guard<std::mutex> lcx(m_SessionLock);
	auto &it = m_Session.find(sessionid);
	if (it != m_Session.end())
	{
		return it->second;
	}
	return nullptr;
}

void ACDModule::RemoveSession(const std::string & sessionId)
{
	std::lock_guard<std::mutex> lcx(m_SessionLock);
	m_Session.erase(sessionId);
}

void ACDModule::run()
{
	while (bRunning)
	{
		std::string strEvent;
		if (m_recEvtBuffer.Get(strEvent) && !strEvent.empty())
		{
			Json::Value jsonEvent;
			Json::Reader jsonReader;
			if (jsonReader.parse(strEvent, jsonEvent)){
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

				model::ExtensionPtr extptr = nullptr;
				if (extptr = GetSession(sessionId,eventName, ext))
				{
					extptr->pushEvent(strEvent);
					if (eventName == "hangup"){
						extptr->Stop();
						RemoveSession(sessionId);
					}
				}
				else{
					LOG4CPLUS_ERROR(log, " not find extension by event:" << strEvent);
				}
	
			}
			else{
				LOG4CPLUS_ERROR(log, __FUNCTION__ ",event:" << strEvent << " not json data.");
			}
		}
	}
	log4cplus::threadCleanup();
}
}
}
