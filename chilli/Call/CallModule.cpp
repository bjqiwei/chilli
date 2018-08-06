#include "CallModule.h"
#include "Call.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/json.h>
#include "../uuid.h"


namespace chilli{
namespace Call{

CallModule::CallModule(const std::string & id):ProcessModule(id)
{
	log =log4cplus::Logger::getInstance("chilli.CallModule");
	LOG4CPLUS_DEBUG(log, this->getId() << " Constuction a Call module.");
}


CallModule::~CallModule(void)
{
	LOG4CPLUS_DEBUG(log, this->getId() << " Destruction a ACD module.");
}


bool CallModule::LoadConfig(const std::string & configContext)
{
	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if(config.Parse(configContext.c_str()) != XMLError::XML_SUCCESS) 
	{ 
		LOG4CPLUS_ERROR(log, this->getId() << " load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}
	
	tinyxml2::XMLElement * ecall = config.FirstChildElement();
	const char * sm = ecall->Attribute("StateMachine");
	m_SMFileName = sm ? sm : "";
	return true;
}

void CallModule::processSend(const std::string & strContent, const void * param, bool & bHandled)
{
	Json::Value jsonData;
	Json::Reader jsonReader;
	if (jsonReader.parse(strContent, jsonData)) {

		if (jsonData["dest"].isString() && !jsonData["dest"].asString().empty())
		{
			std::string sessionid = jsonData["dest"].asString();
			if (m_Calls.find(sessionid) == m_Calls.end()) {
				std::string newCallId = uuid();
				model::PerformElementPtr call(new Call(this, newCallId, m_SMFileName));
				this->addPerformElement(newCallId, call);
				m_Calls[sessionid] =newCallId;
			}
				
			auto & call = m_Calls.find(sessionid);
			jsonData["id"] = call->second;
			chilli::model::EventType_t sendData(jsonData);

			this->PushEvent(sendData);
		}
		bHandled = true;

	}
	else {
		LOG4CPLUS_ERROR(log, this->getId() << strContent << " not json data.");
	}
}


void CallModule::fireSend(const std::string & strContent, const void * param)
{
	LOG4CPLUS_TRACE(log, this->getId() << " fireSend:" << strContent);
	bool bHandled = false;
	processSend(strContent, param, bHandled);
}

void CallModule::run()
{

	LOG4CPLUS_INFO(log, this->getId() << " Starting...");
	try
	{
		while (m_bRunning)
		{
			try
			{
				model::EventType_t evt;
				if (m_RecEvtBuffer.Get(evt) && !evt.event.isNull())
				{
					//LOG4CPLUS_DEBUG(log, evt.event.toStyledString());

					Json::Value jsonEvent = evt.event;
					if (jsonEvent["type"] == "request")
					{
						if (jsonEvent["request"].asString() == "MakeCall")
						{

							std::string sessionid = jsonEvent["param"]["initiatedCall"]["sessionID"].asString();
							std::string newCallId = jsonEvent["param"]["initiatedCall"]["callID"].asString();
							if (m_Calls.find(sessionid) == m_Calls.end()) {
								model::PerformElementPtr call(new Call(this, newCallId, m_SMFileName));
								this->addPerformElement(newCallId, call);
								m_Calls[sessionid] = newCallId;
							}

							auto & call = this->getPerformElement(newCallId);

							jsonEvent["id"] = newCallId;
							jsonEvent["event"] = jsonEvent["request"];
							chilli::model::EventType_t sendData(jsonEvent);
							call->pushEvent(sendData);
							call->mainEventLoop();
						}

					}
					else {
						
						std::string peId;
						if (jsonEvent["id"].isString()) {
							peId = jsonEvent["id"].asString();
						}

						auto call = getPerformElement(peId);

						if (call != nullptr) {
							call->pushEvent(evt);
							call->mainEventLoop();
						}
						else {
							LOG4CPLUS_WARN(log, this->getId() << " not find call:" << peId);
						}
					}

				}
			}
			catch (std::exception & e)
			{
				LOG4CPLUS_ERROR(log, this->getId() << " " << e.what());
			}
		}

	}
	catch (std::exception & e)
	{
		LOG4CPLUS_ERROR(log, this->getId() << " " << e.what());
	}

	LOG4CPLUS_INFO(log, this->getId() << " Stoped.");
	log4cplus::threadCleanup();
}

}
}
