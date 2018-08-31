#include "ShExtension.h"
#include "ShAPI.h"
#include <log4cplus/loggingmacros.h>


namespace chilli{
namespace ShDev{

using namespace SHAPI;

ShExtension::ShExtension(model::ProcessModule * model, const std::string &ext, const std::string &smFileName)
	:Device(model, ext, smFileName)
{
	this->log = log4cplus::Logger::getInstance("chilli.ShDeivce");
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " new a extension object.");
}



ShExtension::~ShExtension(void)
{
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " destruction a extension object.");
}

bool ShExtension::setType(const std::string & strType)
{
	/*if (this->nType != ShDevModule::getDeviceTypeByName(strType))
	{
		LOG4CPLUS_ERROR(log,"." + this->getId(), "the type set not match the device type:"<<strType << ",set UnEnable.");
		this->m_bEnable = false;
		return false;
	}*/
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " set type="<<strType);
	return true;
}
void ShExtension::setType(int _type)
{
	return ;
}

int ShExtension::getChannelID()
{
	return -1;
}



void ShExtension::fireSend(const fsm::FireDataType & fireData, const void * param)
{
	LOG4CPLUS_TRACE(log, "." + this->getId(), " recive a Send event from stateMachine:" << fireData.event);
}

}
}
