#include "ACDExtension.h"
#include <common/xmlHelper.h>
#include <log4cplus/loggingmacros.h>

namespace chilli{
namespace ACD{


ACDExtension::ACDExtension() :chilli::model::Extension()
{
	log = log4cplus::Logger::getInstance("chilli.IVR.Extension");
	LOG4CPLUS_DEBUG(log,"new a IVR extension object.");
}
ACDExtension::~ACDExtension(){
	LOG4CPLUS_DEBUG(log,"destruction a IVR extension object.");
}

bool ACDExtension::LoadConfig(void)
{
	return true;
}

bool ACDExtension::Init(void)
{
	//stateMachie.setscInstance(&IVRModule::scInstance);
	return true;
}
int ACDExtension::EvtHandler(std::string strEvent)
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


void ACDExtension::fireSend(const std::string & strContent)
{
	LOG4CPLUS_TRACE(log," recive a Send event from stateMachine:" << strContent);
}

int ACDExtension::processEvent(const std::string& strEvent)
{
	helper::xml::CXmlDocumentPtr xDocPtr = xmlParseMemory(strEvent.c_str(),strEvent.length());
	if (xDocPtr._xDocPtr == NULL)
	{
		LOG4CPLUS_ERROR(log," Convert a string to xml error was encountered,string="<<strEvent);
		return -1;
	}
	xmlNodePtr xrootNode = xmlDocGetRootElement(xDocPtr._xDocPtr);

	if (xrootNode == NULL){
		LOG4CPLUS_ERROR(log, ": Convert a string to xml error was encountered,string="<<strEvent);
		return -1;
	}		

	//std::string _event = fsm::xmlHelper::getXmlNodeAttributesValue(xrootNode,"event");
	//this->_event_data = fsm::xmlHelper::getXmlNodeAttributesValue(xrootNode,"from");
	//fsm::TriggerEvent evt(_event,this->_event_data,0);
	//LOG4CPLUS_INFO(log, " Recived a event,"<< "from " <<  this->_event_data << "event=" << evt.ToString());
	//stateMachie.pushEvent(evt);

	return 0;
}

bool ACDExtension::processTransfer(std::string strEvent, std::string from)
{
//	IVRModule::recEvtBuffer.addData(strEvent);
	return true;
}

bool ACDExtension::addAcdEvent(const std::string& strEvent)
{
	//IVRModule::recEvtBuffer.addData(strEvent);
	return true;
}

}
}