#include "ACDExtension.h"
#include <common/xmlHelper.h>
#include <log4cplus/loggingmacros.h>

namespace chilli{
namespace ACD{


ACDExtension::ACDExtension() :chilli::model::Extension()
{
	log = log4cplus::Logger::getInstance("chilli.ACD.Extension");
	LOG4CPLUS_DEBUG(log,"new a ACD extension object.");
	m_SM.addSendImplement(this);
}
ACDExtension::~ACDExtension(){
	LOG4CPLUS_DEBUG(log,"destruction a ACD extension object.");
}


const std::string & ACDExtension::getExtensionNumber() const
{
	return m_ExtNumber;
}

bool ACDExtension::isIdle()
{
	return m_SM.getCurrentStateID() == "Idle";
}

void ACDExtension::go()
{
	m_SM.go();
}

int ACDExtension::Answer()
{
	LOG4CPLUS_WARN(log, "not implement.");
	return 0;
}

int ACDExtension::PlayFile(const std::string &fileName)
{
	LOG4CPLUS_WARN(log, "not implement.");
	return 0;
}

int ACDExtension::HangUp()
{
	LOG4CPLUS_WARN(log, "not implement.");
	return 0;
}

void ACDExtension::fireSend(const std::string & strContent,const void * param)
{
	LOG4CPLUS_TRACE(log," recive a Send event from stateMachine:" << strContent);
}

int ACDExtension::pushEvent(const std::string& strEvent)
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

	std::string _event = helper::xml::getXmlNodeAttributesValue(xrootNode,"event");
	std::string _from = helper::xml::getXmlNodeAttributesValue(xrootNode,"from");
	fsm::TriggerEvent evt(_event, _from);
	LOG4CPLUS_INFO(log, " Recived a event," << "from " << _from << "event=" << evt.ToString());
	m_SM.pushEvent(evt);

	return 0;
}

}
}