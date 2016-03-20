#include "IVRExtension.h"
#include <common/xmlHelper.h>
#include <log4cplus/loggingmacros.h>
#include <scxml/TriggerEvent.h>

namespace chilli{
namespace IVR{


IVRExtension::IVRExtension():chilli::model::Extension()
{
	log = log4cplus::Logger::getInstance("chilli.IVR.Extension");
	LOG4CPLUS_DEBUG(log,"new a IVR extension object.");
}
IVRExtension::~IVRExtension(){
	LOG4CPLUS_DEBUG(log,"destruction a IVR extension object.");
}

bool IVRExtension::LoadConfig(void)
{
	return true;
}

int IVRExtension::EvtHandler(std::string strEvent)
{
	/*if (!m_bEnable)
	{
		LOG4CPLUS_WARN(log, " ch="<< this->getChannelID()<<", is disable.");
		return 0;
	}*/
	fsm::TriggerEvent evt(strEvent,0);
	//stateMachie.pushEvent(evt);
	return 0;
}


void IVRExtension::fireSend(const std::string & strContent)
{
	LOG4CPLUS_TRACE(log," recive a Send event from stateMachine:" << strContent);
}


bool IVRExtension::processTransfer(std::string strEvent,std::string from)
{
//	IVRModule::recEvtBuffer.addData(strEvent);
	return true;
}


}
}