#include "IVRExtension.h"
#include <log4cplus/loggingmacros.h>
#include <scxml/TriggerEvent.h>

namespace chilli{
namespace IVR{


IVRExtension::IVRExtension(const std::string &ext, const std::string &smFileName, fsm::SMInstance * smInstance) :Extension()
,SendInterface("this"), m_ExtNumber(ext), m_smInstance(smInstance), m_SM(nullptr)
{
	log = log4cplus::Logger::getInstance(m_ExtNumber);
	m_SM = new fsm::StateMachine(smFileName, log);
	LOG4CPLUS_DEBUG(log,"new a IVR extension object.");
}
IVRExtension::~IVRExtension(){
	delete m_SM;
	LOG4CPLUS_DEBUG(log,"destruction a IVR extension object.");
}

const std::string & IVRExtension::getExtensionNumber() const
{
	return m_ExtNumber;
}

bool IVRExtension::isIdle()
{
	return m_SM->getCurrentStateID() == "Idle";
}

void IVRExtension::setSessionId(const std::string & sessinId)
{
	this->m_SessionId = sessinId;
	this->m_SM->setSessionID(m_SessionId);
	this->m_SM->setVar("_sessionid", this->m_SessionId);
}
const std::string & IVRExtension::getSessionId()
{
	return this->m_SessionId;
}

void IVRExtension::go()
{
	m_SM->setSessionID(m_SessionId);
	m_SM->setscInstance(m_smInstance);
	m_SM->addSendImplement(this);
	m_SM->go();
}

void IVRExtension::run()
{
	m_SM->mainEventLoop();
}

void IVRExtension::termination()
{
	m_SM->termination();
}

int IVRExtension::Answer()
{
	LOG4CPLUS_WARN(log, "not implement.");
	return 0;
}

int IVRExtension::PlayFile(const std::string &fileName)
{
	LOG4CPLUS_WARN(log, "not implement.");
	return 0;
}

int IVRExtension::HangUp()
{
	LOG4CPLUS_WARN(log, "not implement.");
	return 0;
}

void IVRExtension::fireSend(const std::string &strContent, const void * param)
{
	LOG4CPLUS_TRACE(log," recive a Send event from stateMachine:" << strContent);
}

int IVRExtension::pushEvent(const std::string& strEvent)
{
	Json::Value jsonEvent;
	Json::Reader jsonReader;
	if (jsonReader.parse(strEvent, jsonEvent)){
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
		LOG4CPLUS_ERROR(log, __FUNCTION__ ",event:" << strEvent << " not json data.");
	}

	return 0;
}
}
}