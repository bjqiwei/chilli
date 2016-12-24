#include "Agent.h"
#include <log4cplus/loggingmacros.h>
#include <json/json.h>

namespace chilli{
namespace Agent{


Agent::Agent(const std::string &ext, const std::string &smFileName) 
	:Extension(ext, smFileName), m_ExtNumber(ext)
{
	std::string logName= "Agent.";
	log = log4cplus::Logger::getInstance(logName.append(m_ExtNumber));
	LOG4CPLUS_DEBUG(log,"new a Agent object.");
}

Agent::~Agent(){
	LOG4CPLUS_DEBUG(log,"destruction a Agent object.");
}


const std::string & Agent::getExtensionNumber() const
{
	return m_ExtNumber;
}


void Agent::setSessionId(const std::string & sessinId)
{
	this->m_SessionId = sessinId;
}

const std::string & Agent::getSessionId()
{
	return this->m_SessionId;
}


int Agent::Answer()
{
	LOG4CPLUS_WARN(log, "not implement.");
	return 0;
}

int Agent::PlayFile(const std::string &fileName)
{
	LOG4CPLUS_WARN(log, "not implement.");
	return 0;
}

int Agent::HangUp()
{
	LOG4CPLUS_WARN(log, "not implement.");
	return 0;
}

void Agent::fireSend(const std::string & strContent,const void * param)
{
	LOG4CPLUS_TRACE(log," recive a Send event from stateMachine:" << strContent);
}

int Agent::pushEvent(const std::string& strEvent)
{
	Json::Value jsonEvent;
	Json::Reader jsonReader;
	if (jsonReader.parse(strEvent, jsonEvent)){
		std::string eventName;

		if (jsonEvent["event"].isString()){
			eventName = jsonEvent["event"].asString();
		}

		fsm::TriggerEvent evt(eventName);

		for (auto & it : jsonEvent.getMemberNames()) {
			evt.addVars(it, jsonEvent[it]);
		}

		LOG4CPLUS_INFO(log, " Recived a event," << strEvent);
		m_SM->pushEvent(evt);

	}
	else{
		LOG4CPLUS_ERROR(log, ",event:" << strEvent << " not json data.");
	}

	return 0;
}

}
}