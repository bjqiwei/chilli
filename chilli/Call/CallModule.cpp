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
			jsonData["param"]["from"] = jsonData["from"];
			jsonData["param"]["id"] = call->second;
			jsonData["param"]["event"] = jsonData["event"];
			jsonData["param"]["type"] = jsonData["type"];
			chilli::model::EventType_t sendData(jsonData["param"]);

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
	LOG4CPLUS_TRACE(log, this->getId() << "fireSend:" << strContent);
	bool bHandled = false;
	processSend(strContent, param, bHandled);
}

}
}
