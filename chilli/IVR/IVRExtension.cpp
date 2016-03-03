#include "IVRExtension.h"
#include <common/xmlHelper.h>
#include <log4cplus/loggingmacros.h>

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

bool IVRExtension::Init(void)
{
	//stateMachie.setscInstance(&IVRModule::scInstance);
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
	processCmd(strContent);
}

int IVRExtension::processCmd(const std::string& strCmd)
{
	using namespace helper::xml;
	CXmlParseHelper xmlParse(strCmd);

	std::string _cmd = xmlParse.getRootProp("cmd");
	if (_cmd.compare("reloadConfig") == 0)
	{
		//this->reload();
	}else if (_cmd.compare("transfer") == 0)
	{
		//this->_event_data = xmlParse.getRootProp("from");
		//fsm::TriggerEvent evt(_cmd,this->_event_data,0);
		//LOG4CPLUS_INFO(log,  " Recived a event,"<<"from " <<  this->_event_data << "event=" << evt.ToString());
		//stateMachie.pushEvent(evt);
	}
	else{
		LOG4CPLUS_ERROR(log," not implement this cmd: " << _cmd);
	}
	return 0;
}

int IVRExtension::processEvent(const std::string& strEvent)
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

bool IVRExtension::processTransfer(std::string strEvent,std::string from)
{
//	IVRModule::recEvtBuffer.addData(strEvent);
	return true;
}

bool IVRExtension::addAcdEvent(const std::string& strEvent)
{
	//IVRModule::recEvtBuffer.addData(strEvent);
	return true;
}

}
}