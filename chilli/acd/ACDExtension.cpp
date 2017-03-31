#include "ACDExtension.h"
#include <log4cplus/loggingmacros.h>
#include <json/json.h>

namespace chilli{
namespace ACD{


ACDExtension::ACDExtension(model::ProcessModule * model, const std::string &ext, const std::string &smFileName) 
	:Extension(model, ext,smFileName)
{
	std::string logName = "ACD.";
	log = log4cplus::Logger::getInstance(logName.append(m_ExtNumber));
	LOG4CPLUS_DEBUG(log,"new a ACD extension object.");
}
ACDExtension::~ACDExtension(){
	LOG4CPLUS_DEBUG(log,"destruction a ACD extension object.");
}


const std::string & ACDExtension::getExtensionNumber() const
{
	return m_ExtNumber;
}


void ACDExtension::setSessionId(const std::string & sessinId)
{
	this->m_SessionId = sessinId;
}

const std::string & ACDExtension::getSessionId()
{
	return this->m_SessionId;
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

int ACDExtension::pushEvent(const model::EventType_t & Event)
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