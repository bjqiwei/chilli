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
	LOG4CPLUS_TRACE(log, this->getId() << " fireSend:" << strContent);
	bool bHandled = false;
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