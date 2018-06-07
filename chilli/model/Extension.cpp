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

	Json::Value Extension::getVar(const std::string & name)
	{
		return m_Vars[name];
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
				std::string connectid;
				std::string type;

				if (jsonEvent["type"].isString())
					type = jsonEvent["type"].asString();

				if (jsonEvent["event"].isString()) {
					eventName = jsonEvent["event"].asString();
				}

				if (jsonEvent["ConnectionID"].isString()) {
					connectid = jsonEvent["ConnectionID"].asString();
				}

				if (eventName == "AgentLogin" && type == "cmd"){
					m_AgentID = jsonEvent[eventName]["agentId"].asString();
					model::EventType_t _event;
					_event.event["event"] = eventName;
					_event.event["extension"] = jsonEvent["from"];
					_event.event["from"] = this->getExtNumber();
					_event.event["type"] = "event";
					_event.event[eventName]["cause"] = 0;
					this->m_model->PushEvent(_event);
					LOG4CPLUS_DEBUG(log, " Push a event," << _event.event.toStyledString());
					return;
				}

				if (eventName == "AgentLogin" && type == "event") {
					this->setVar("_agent.Extension",jsonEvent["from"].asString());
				}

				if (eventName == "AgentLogout" && !jsonEvent["from"].isNull()) {
					m_AgentID.clear();
					model::EventType_t _event;
					_event.event["event"] = eventName;
					_event.event["extension"] = jsonEvent["from"];
					_event.event[eventName]["cause"] = 0;
					this->m_model->PushEvent(_event);
					LOG4CPLUS_DEBUG(log, " Push a event," << _event.event.toStyledString());
					return;
				}

				fsm::TriggerEvent evt(eventName);

				for (auto & it : jsonEvent.getMemberNames()) {
					evt.addVars(it, jsonEvent[it]);
				}

				LOG4CPLUS_DEBUG(log, " Recived a event," << Event.event.toStyledString());

				if (m_Connections.find(connectid) == m_Connections.end()) {
					Connction connection(new fsm::StateMachine(m_ExtNumber, m_SMFileName, ProcessModule::OnTimerExpiredFunc));
					m_Connections[connectid] = connection;

					for (auto & itt : this->m_Vars.getMemberNames())
					{
						connection->setVar(itt, this->m_Vars[itt]);
					}
					connection->setVar("_extension.AgentID", m_AgentID);

					for (auto & itt : ProcessModule::g_Modules) {
						connection->addSendImplement(itt.get());
					}

					connection->addSendImplement(this);
					connection->start(false);
				}

				auto & it = m_Connections.find(connectid);
				it->second->pushEvent(evt);
				it->second->mainEventLoop();

				if (it->second->isInFinalState()) {
					it->second->stop();
					m_Connections.erase(it);
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

	std::string Extension::getStateId()
	{
		if (!m_Connections.empty()){
			return m_Connections.begin()->second->getCurrentStateID();
		}

		return std::string();
	}

	log4cplus::Logger Extension::getLogger() {
		return log;
	}


}
}