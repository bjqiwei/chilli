#include "ACDModule.h"
#include "ACDExtension.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/json.h>


namespace chilli{
namespace ACD{


ACDModule::ACDModule(void) :SMInstance(this), bRunning(false)
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
	for (auto it: m_Session)
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

int ACDModule::Start()
{
	LOG4CPLUS_DEBUG(log, "Start  ACD module");
	while (!bRunning)
	{
		bRunning = true;
		for (int i = 0; i < 10; i++)
		{
			std::shared_ptr<std::thread> th(new std::thread(&ACDModule::run, this));
			m_Thread.push_back(th);
		}
	}
	return m_Thread.size();
}

bool ACDModule::LoadConfig(const std::string & configFile)
{
	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if(config.LoadFile(configFile.c_str()) != XMLError::XML_SUCCESS) 
	{ 
		LOG4CPLUS_ERROR(log, "load config file error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}
	if (tinyxml2::XMLElement *eConfig  = config.FirstChildElement("Config")){
		if(tinyxml2::XMLElement *eACD = eConfig->FirstChildElement("ACD"))
		{
			for (XMLElement *child = eACD->FirstChildElement("Extension"); child != nullptr; child = child->NextSiblingElement("Extension")){
				const char * num = child->Attribute("ExtensionNumber");
				const char * sm = child->Attribute("StateMachine");
				if (this->m_Extension.find(num) == this->m_Extension.end())
				{
					model::ExtensionPtr ext(new ACDExtension(num, sm, this));
					this->m_Extension[num] = ext;
					this->m_SMFile[num] = sm;
				}
				else{
					LOG4CPLUS_ERROR(log, "alredy had extension:" << num);
				}
			}
		}
		else {
			LOG4CPLUS_ERROR(log, "config file missing ACD element.");
			return false;
		}

	}
	else {
		LOG4CPLUS_ERROR(log, "config file missing Config element.");
		return false;
	}
	return true;
}

const std::map<std::string, model::ExtensionPtr> ACDModule::GetExtension()
{
	return m_Extension;
}

std::shared_ptr<model::Extension> ACDModule::GetSession(const std::string & sessionid, const std::string & eventName, const std::string & ext)
{
	std::lock_guard<std::mutex> lcx(m_SessionLock);
	auto it = m_Session.find(sessionid);
	if (it != m_Session.end())
	{
		return it->second;
	}
	else{
		if (eventName == "timer"){
			LOG4CPLUS_ERROR(log, "timer event session id not find, abandon this event.");
		}
		else{

			std::shared_ptr<model::Extension> extPtr(new ACDExtension(ext, this->m_SMFile[ext], this));
			m_Session.insert(std::make_pair(sessionid, extPtr));
			extPtr->setSessionId(sessionid);
			extPtr->go();
			return extPtr;
		}
	}
	return nullptr;
}

void ACDModule::RemoveSession(const std::string & sessionId)
{
	std::lock_guard<std::mutex> lcx(m_SessionLock);
	m_Session.erase(sessionId);
}

void ACDModule::OnTimerExpired(unsigned long timerId, const std::string & attr)
{
	LOG4CPLUS_DEBUG(log, __FUNCTION__ "," << timerId << ":" << attr);
	Json::Value jsonEvent;
	jsonEvent["event"] = "timer";
	std::string sessionId  = attr.substr(0, attr.find_first_of(":"));
	jsonEvent["sessionid"] = sessionId;

	this->PushEvent(jsonEvent.toStyledString());
}

void ACDModule::run()
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

				std::shared_ptr<model::Extension> extptr = nullptr;
				if (extptr = GetSession(sessionId,eventName, ext))
				{
					extptr->pushEvent(strEvent);
					extptr->run();
					if (eventName == "hangup")
					{
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
	
}
}
}
