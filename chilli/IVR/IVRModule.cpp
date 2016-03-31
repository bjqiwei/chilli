#include "IVRModule.h"
#include "IVRExtension.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/json.h>


namespace chilli{
namespace IVR{


IVRModule::IVRModule(void) :SMInstance(this), bRunning(false)
{
	log =log4cplus::Logger::getInstance("chilli.IVRModule");
	LOG4CPLUS_DEBUG(log,"Constuction a IVR module.");
}


IVRModule::~IVRModule(void)
{
	if (bRunning){
		Stop();
	}

	LOG4CPLUS_DEBUG(log,"Destruction a IVR module.");
}

int IVRModule::Stop(void)
{
	LOG4CPLUS_DEBUG(log,"Stop  IVR module");
	bRunning = false;
	for (auto it: m_Extension)
	{
		it.second->termination();
	}

	int result = m_Thread.size();
	for (auto it : this->m_Thread){
		if (it->joinable()){
			it->join();
		}
	}

	m_Thread.clear();
	return result;
}

int IVRModule::Start()
{
	LOG4CPLUS_DEBUG(log, "Start  IVR module");
	while (!bRunning)
	{
		bRunning = true;
		for (int i = 0; i < 10; i++)
		{
			shared_ptr<std::thread> th(new std::thread(&IVRModule::run, this));
			m_Thread.push_back(th);
		}
	}
	return m_Thread.size();
}

bool IVRModule::LoadConfig(const std::string & configFile)
{
	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if(config.LoadFile(configFile.c_str()) != XMLError::XML_SUCCESS) 
	{ 
		LOG4CPLUS_ERROR(log, "load config file error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}
	if (tinyxml2::XMLElement *eConfig  = config.FirstChildElement("Config")){
		if(tinyxml2::XMLElement *eACD = eConfig->FirstChildElement("IVR"))
		{
			for (XMLElement *child = eACD->FirstChildElement("Extension"); child != nullptr; child = child->NextSiblingElement("Extension")){
				const char * num = child->Attribute("ExtensionNumber");
				const char * sm = child->Attribute("StateMachine");
				if (this->m_Extension.find(num) == this->m_Extension.end())
				{
					model::ExtensionPtr ext(new IVRExtension(num, sm, this));
					this->m_Extension[num] = ext;
					ext->go();
				}
				else{
					LOG4CPLUS_ERROR(log, "alredy had extension:" << num);
				}
			}
		}
		else {
			LOG4CPLUS_ERROR(log, "config file missing IVR element.");
			return false;
		}

	}
	else {
		LOG4CPLUS_ERROR(log, "config file missing Config element.");
		return false;
	}
	return true;
}

const std::map<std::string, model::ExtensionPtr> IVRModule::GetExtension()
{
	return m_Extension;
}


void IVRModule::OnTimerExpired(unsigned long timerId, const std::string & attr)
{
	LOG4CPLUS_DEBUG(log, __FUNCTION__ "," << timerId << ":" << attr);
	Json::Value jsonEvent;
	jsonEvent["event"] = "timer";
	std::string sessionId  = attr.substr(0, attr.find_first_of(":"));
	jsonEvent["sessionid"] = sessionId;

	jsonEvent["extension"] = attr.substr(attr.find_first_of(":") + 1);

	this->PushEvent(jsonEvent.toStyledString());
}

void IVRModule::run()
{
	while (bRunning)
	{
		std::string strEvent;
		if (m_recEvtBuffer.getData(strEvent, 1000))
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

				auto it = m_Extension.find(ext);

				if (it != m_Extension.end())
				{
					it->second->setSessionId(sessionId);
					it->second->pushEvent(strEvent);
					it->second->run();
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
	
}
}
}
