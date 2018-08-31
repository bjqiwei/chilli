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

void AvayaAgent::fireSend(const fsm::FireDataType &fireData,const void * param)
{
	LOG4CPLUS_TRACE(log, "." + this->getId(), " fireSend:" << fireData.event);

	bool bHandled = false;
	this->processSend(fireData, param, bHandled);
	
}

void AvayaAgent::processSend(const fsm::FireDataType &fireData, const void * param, bool & bHandled)
{
	m_model->processSend(fireData, param, bHandled, this);
	if (!bHandled) {
		Agent::processSend(fireData, param, bHandled);
	}
}

}
}