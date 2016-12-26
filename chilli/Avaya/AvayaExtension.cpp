#include "AvayaExtension.h"
#include <log4cplus/loggingmacros.h>
#include <scxml/TriggerEvent.h>

namespace chilli{
namespace Avaya{


AvayaExtension::AvayaExtension(const std::string &ext, const std::string &smFileName) 
	:Extension(ext,smFileName), m_ExtNumber(ext)
{
	std::string logName = "AvayaExtension.";
	log = log4cplus::Logger::getInstance(logName.append(m_ExtNumber));
	LOG4CPLUS_DEBUG(log,"new a Avaya extension object.");
}
AvayaExtension::~AvayaExtension(){
	LOG4CPLUS_DEBUG(log,"destruction a Avaya extension object.");
}

const std::string & AvayaExtension::getExtensionNumber() const
{
	return m_ExtNumber;
}


void AvayaExtension::setSessionId(const std::string & sessinId)
{
	this->m_SessionId = sessinId;
}
const std::string & AvayaExtension::getSessionId()
{
	return this->m_SessionId;
}


int AvayaExtension::Answer()
{
	LOG4CPLUS_WARN(log, "not implement.");
	return 0;
}

int AvayaExtension::PlayFile(const std::string &fileName)
{
	LOG4CPLUS_WARN(log, "not implement.");
	return 0;
}

int AvayaExtension::HangUp()
{
	LOG4CPLUS_WARN(log, "not implement.");
	return 0;
}

void AvayaExtension::fireSend(const std::string &strContent, const void * param)
{
	LOG4CPLUS_TRACE(log," recive a Send event from stateMachine:" << strContent);
}

int AvayaExtension::pushEvent(const model::EventType_t & Event)
{
	Json::Value jsonEvent;
	Json::Reader jsonReader;
	if (jsonReader.parse(Event.event, jsonEvent)){
		std::string eventName;
		std::string _from;
		if (jsonEvent["event"].isString()){
			eventName = jsonEvent["event"].asString();
		}

		if (jsonEvent["from"].isString()){
			_from = jsonEvent["from"].asString();
		}


		fsm::TriggerEvent evt(eventName, _from);
		LOG4CPLUS_INFO(log, " Recived a event," << "from " << _from << "event=" << evt.ToString());
		m_SM->pushEvent(evt);

	}
	else{
		LOG4CPLUS_ERROR(log, __FUNCTION__ ",event:" << Event.event << " not json data.");
	}

	return 0;
}
}
}