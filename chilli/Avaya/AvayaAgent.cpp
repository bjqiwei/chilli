#include "AvayaAgent.h"
#include "TSAPIModule.h"
#include <log4cplus/loggingmacros.h>
#include <json/json.h>

namespace chilli{
namespace Avaya{

AvayaAgent::AvayaAgent(TSAPIModule * model, const std::string &ext, const std::string &smFileName)
	:m_model(model), Agent(model, ext, smFileName)
{
	log.setAppendName("." + this->getId());
}

AvayaAgent::~AvayaAgent(){

}

void AvayaAgent::fireSend(const std::string & strContent,const void * param)
{
	LOG4CPLUS_TRACE(log, " fireSend:" << strContent);
	Json::Value jsonEvent;
	Json::Reader jsonReader;
	if (!jsonReader.parse(strContent, jsonEvent)) {
		LOG4CPLUS_ERROR(log, this->getId() << " " << " not json data.");
		return;
	}

	bool bHandled = false;
	this->processSend(jsonEvent, param, bHandled);
	
}

void AvayaAgent::processSend(Json::Value & jsonEvent, const void * param, bool & bHandled)
{
	m_model->processSend(jsonEvent, param, bHandled, this);
	if (!bHandled) {
		Agent::processSend(jsonEvent, param, bHandled);
	}
}

}
}