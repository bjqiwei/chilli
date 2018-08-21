#include "AvayaAgent.h"
#include "TSAPIModule.h"
#include <log4cplus/loggingmacros.h>
#include <json/config.h>
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
	LOG4CPLUS_TRACE(log, "." + this->getId(), " fireSend:" << strContent);
	Json::Value jsonEvent;
	Json::CharReaderBuilder b;
	std::shared_ptr<Json::CharReader> jsonReader(b.newCharReader());
	std::string jsonerr;

	if (!jsonReader->parse(strContent.c_str(), strContent.c_str()+strContent.length(), &jsonEvent, &jsonerr)) {
		LOG4CPLUS_ERROR(log, "." + this->getId(), strContent << " " << " not json data." << jsonerr);
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