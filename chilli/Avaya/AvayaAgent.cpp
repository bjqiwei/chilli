#include "AvayaAgent.h"
#include "TSAPIModule.h"
#include <log4cplus/loggingmacros.h>
#include <json/json.h>

namespace chilli{
namespace Avaya{

AvayaAgent::AvayaAgent(TSAPIModule * model, const std::string &ext, const std::string &smFileName)
	:m_model(model), Agent(model, ext, smFileName)
{

}

AvayaAgent::~AvayaAgent(){

}

void AvayaAgent::fireSend(const std::string & strContent,const void * param)
{
	LOG4CPLUS_TRACE(log,"fireSend:" << strContent);
	bool bHandled = false;
	Json::Value jsonData;
	Json::Reader jsonReader;
	if (jsonReader.parse(strContent, jsonData)) {
		if (jsonData["dest"].asString() == "acd")
		{
			bHandled = true;

			std::string ext = m_model->findIdleACD();
			if (ext.empty()){

				Json::Value newEvent;
				newEvent["event"] = jsonData["event"];
				newEvent[jsonData["event"].asString()]["cause"] = 1;
				newEvent[jsonData["event"].asString()]["reason"] = "System Busy";
				newEvent["extension"] = this->getExtNumber();
				jsonData = newEvent;
				
			}
			else {
				jsonData["extension"] = ext;
			}

			model::EventType_t evt(jsonData);
			m_model->PushEvent(evt);			
		}
	}

	if (!bHandled)
		this->processSend(strContent, param, bHandled);
	
}

void AvayaAgent::processSend(const std::string & strContent, const void * param, bool & bHandled)
{
	m_model->processSend(strContent, param, bHandled, this);
	if (!bHandled) {
		Agent::processSend(strContent, param, bHandled);
	}
}

}
}