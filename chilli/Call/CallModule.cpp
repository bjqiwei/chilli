#include "CallModule.h"
#include "Call.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/config.h>
#include <json/json.h>
#include "../uuid.h"


namespace chilli{
namespace Call{

CallModule::CallModule(const std::string & id):ProcessModule(id)
{
	log =log4cplus::Logger::getInstance("chilli.CallModule");
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " Constuction a Call module.");
}


CallModule::~CallModule(void)
{
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " Destruction a ACD module.");
}


bool CallModule::LoadConfig(const std::string & configContext)
{
	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if(config.Parse(configContext.c_str()) != XMLError::XML_SUCCESS) 
	{ 
		LOG4CPLUS_ERROR(log, "." + this->getId(), " load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}
	
	tinyxml2::XMLElement * ecall = config.FirstChildElement();
	const char * sm = ecall->Attribute("StateMachine");
	m_SMFileName = sm ? sm : "";
	return true;
}

void CallModule::processSend(Json::Value & jsonData, const void * param, bool & bHandled)
{

	if (jsonData["dest"].isString() && jsonData["dest"].asString() != "this")
	{
		this->PushEvent(chilli::model::EventType_t(jsonData));
		bHandled = true;
	}

	
}


void CallModule::fireSend(const std::string & strContent, const void * param)
{
	LOG4CPLUS_TRACE(log, "." + this->getId(), " fireSend:" << strContent);
	Json::Value jsonData;
	Json::CharReaderBuilder b;
	std::shared_ptr<Json::CharReader> jsonReader(b.newCharReader());
	std::string jsonerr;
	if (!jsonReader->parse(strContent.c_str(), strContent.c_str()+strContent.length(), &jsonData, &jsonerr)) {
		LOG4CPLUS_ERROR(log, "." + this->getId(), strContent << " not json data." << jsonerr);
		return;
	}

	bool bHandled = false;
	processSend(jsonData, param, bHandled);
}

void CallModule::run()
{

	LOG4CPLUS_INFO(log, "." + this->getId(), " Starting...");
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

					Json::Value  & jsonEvent = evt.event;
					if (jsonEvent["type"] == "request"){
						jsonEvent["event"] = jsonEvent["request"];
					}

					std::string sessionid; 
					if (jsonEvent["param"].isMember("sessionID"))
						sessionid = jsonEvent["param"]["sessionID"].asString();

					std::string newCallId;
					if(jsonEvent["param"].isMember("callID"))
						newCallId = jsonEvent["param"]["callID"].asString();

					std::string newConnectionID;
					if(jsonEvent["param"].isMember("connectionID"))
						newConnectionID = jsonEvent["param"]["connectionID"].asString();

					if (sessionid.empty()){
						LOG4CPLUS_WARN(log, "." + this->getId(), "sessionID is null");
						continue;
					}
					if (m_Calls.find(sessionid) == m_Calls.end()) {

						std::string otherSessionId;
						if (jsonEvent["param"].isMember("otherSessionID") && jsonEvent["param"]["otherSessionID"].isString())
							otherSessionId = jsonEvent["param"]["otherSessionID"].asString();

						if (m_Calls.find(otherSessionId) != m_Calls.end()) {
							m_Calls[sessionid] = m_Calls[otherSessionId];
						}
						else {
							if (newCallId.empty())
								newCallId = helper::uuid();
							if (newConnectionID.empty())
								newConnectionID = helper::uuid();

							model::PerformElementPtr call(new Call(this, newCallId, m_SMFileName));
							call->setVar("_callid", newCallId);
							call->setVar("_connectionid", newConnectionID);
							this->addPerformElement(newCallId, call);
							m_Calls[sessionid] = newCallId;
						}
					}

					newCallId = m_Calls[sessionid];

					const auto & call = this->getPerformElement(newCallId);

					jsonEvent["id"] = newCallId;
						
						
					call->pushEvent(chilli::model::EventType_t(jsonEvent));
					call->mainEventLoop();

					if (call->IsClosed())
						this->removePerfromElement(call->getId());
					
					if (jsonEvent["event"].isString() && jsonEvent["event"].asString() == "Null")
						m_Calls.erase(sessionid);
				}
			}
			catch (std::exception & e)
			{
				LOG4CPLUS_ERROR(log, "." + this->getId(), " " << e.what());
			}
		}

	}
	catch (std::exception & e)
	{
		LOG4CPLUS_ERROR(log, "." + this->getId(), " " << e.what());
	}

	LOG4CPLUS_INFO(log, "." + this->getId(), " Stoped.");
	log4cplus::threadCleanup();
}

}
}
