#include "Extension.h"
#include "ProcessModule.h"
#include <log4cplus/loggingmacros.h>

namespace chilli {
namespace model {


	Extension::Extension(ProcessModule * model, const std::string &ext, const std::string &smFileName) :
		m_model(model), m_ExtNumber(ext), SendInterface("this"), m_SMFileName(smFileName)
	{
		std::string logName = "Extension.";
		this->log = log4cplus::Logger::getInstance(logName.append(m_ExtNumber));
	}

	Extension::~Extension() {
		m_Connections.clear();
	}

	void Extension::Start() {
		LOG4CPLUS_INFO(log, " Start.");
		for (auto & it : m_Connections) {
			it.second->start(false);
		}
	}

	void Extension::Stop() {
		for (auto & it: m_Connections){
			it.second->stop();
		}
		LOG4CPLUS_INFO(log, " Stop.");
	}

	bool Extension::IsFinalState()
	{
		return m_Connections.empty();
	}

	bool Extension::setVar(const std::string &name, const Json::Value &value)
	{
		if (m_Vars.isMember(name))
			return false;

		m_Vars[name] = value;
		return true;
	}

	const std::string & Extension::getExtNumber() {
		return m_ExtNumber;
	}

	int Extension::pushEvent(const EventType_t & Event)
	{
		return m_EvtBuffer.Put(Event) ? 0 : 1;
	}

	void Extension::mainEventLoop()
	{
		try
		{

			model::EventType_t Event;
			if (m_EvtBuffer.Get(Event, 0) && !Event.event.isNull()) {
				const Json::Value & jsonEvent = Event.event;

				std::string eventName;
				std::string callid;

				if (jsonEvent["event"].isString()) {
					eventName = jsonEvent["event"].asString();
				}

				if (jsonEvent["callid"].isString()) {
					callid = jsonEvent["callid"].asString();
				}

				fsm::TriggerEvent evt(eventName);

				for (auto & it : jsonEvent.getMemberNames()) {
					evt.addVars(it, jsonEvent[it]);
				}

				LOG4CPLUS_DEBUG(log, " Recived a event," << Event.event.toStyledString());

				auto & it = m_Connections.find(callid);
				if (it == m_Connections.end()) {
					m_Connections[callid] = Conntion(new fsm::StateMachine(m_ExtNumber, m_SMFileName, ProcessModule::OnTimerExpiredFunc));
					it = m_Connections.find(callid);

					for (auto & itt : this->m_Vars.getMemberNames())
					{
						it->second->setVar(itt, this->m_Vars[itt]);
					}

					for (auto & itt : ProcessModule::g_Modules) {
						it->second->addSendImplement(itt.get());
					}

					it->second->addSendImplement(this);
					it->second->start(false);
				}

				it->second->pushEvent(evt);
				it->second->mainEventLoop();

				if (it->second->isInFinalState()) {
					m_Connections.erase(it);
					it->second->stop();
				}
			}
		}
		catch (std::exception & e)
		{
			LOG4CPLUS_ERROR(log, e.what());
		}
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


}
}