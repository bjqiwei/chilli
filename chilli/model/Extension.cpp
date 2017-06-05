#include "Extension.h"
#include "ProcessModule.h"
#include <log4cplus/loggingmacros.h>

namespace chilli {
namespace model {


	Extension::Extension(ProcessModule * model, const std::string &ext, const std::string &smFileName) :
		m_model(model), m_ExtNumber(ext), SendInterface("this")
	{
		m_SM = new fsm::StateMachine(ext, smFileName, ProcessModule::OnTimerExpiredFunc);
	}

	Extension::~Extension() {
		delete m_SM;
	}

	void Extension::Start() {
		LOG4CPLUS_INFO(log, " Start.");
		m_SM->start(false);
	}

	void Extension::Stop() {
		m_SM->stop();
		LOG4CPLUS_INFO(log, " Stop.");
	}

	bool Extension::IsFinalState()
	{
		return m_SM->isInFinalState();
	}

	bool Extension::AddSendImplement(SendInterface * evtDsp) {
		return m_SM->addSendImplement(evtDsp);
	}

	bool Extension::setVar(const std::string &name, const Json::Value &value)
	{
		return m_SM->setVar(name, value);
	}

	const std::string & Extension::getExtNumber() {
		return m_ExtNumber;
	}

	int Extension::pushEvent(const EventType_t & Event)
	{
		const Json::Value & jsonEvent = Event.event;

		std::string eventName;

		if (jsonEvent["event"].isString()) {
			eventName = jsonEvent["event"].asString();
		}

		fsm::TriggerEvent evt(eventName);

		for (auto & it : jsonEvent.getMemberNames()) {
			evt.addVars(it, jsonEvent[it]);
		}

		LOG4CPLUS_DEBUG(log, " Recived a event," << Event.event.toStyledString());

		m_SM->pushEvent(evt);

		return 0;
	}

	void Extension::mainEventLoop()
	{
		return m_SM->mainEventLoop();
	}

	void Extension::setSessionId(const std::string & sessinId) {
		m_SessionId = sessinId;
	}

	const std::string & Extension::getSessionId() {
		return m_SessionId;
	}

	log4cplus::Logger Extension::getLogger() {
		return log;
	}

	ExtensionConfig::ExtensionConfig(ProcessModule * model, const std::string &ext, const std::string &smFileName, uint32_t type) :
		m_model(model), m_ExtNumber(ext), m_SMFileName(smFileName), m_ExtType(type)
	{

	}

}
}