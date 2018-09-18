#include "Call.h"
#include <log4cplus/loggingmacros.h>
#include <scxml/TriggerEvent.h>
#include "../model/ProcessModule.h"

using namespace chilli::model;
namespace chilli {
namespace Call {

	Call::Call(ProcessModule * model, const std::string &callid, const std::string &smFileName)
		:PerformElement(model, callid), m_SMFileName(smFileName)
	{
		std::string logName = "Call";
		log = log4cplus::Logger::getInstance(logName);
		LOG4CPLUS_DEBUG(log, "." + this->getId(), " new a call object.");
	}

	Call::~Call() {
		m_StateMachines.clear();
		LOG4CPLUS_DEBUG(log, "." + this->getId(), " destruction a call object.");
	}

	void Call::Start()
	{
		LOG4CPLUS_INFO(log, "." + this->getId(), " Start.");
		for (auto & it : m_StateMachines) {
			it.second->start(false);
		}
	}

	void Call::Stop()
	{
		for (auto & it : m_StateMachines) {
			for (auto & it : m_StateMachines) {
				Json::Value shutdown;
				shutdown["id"] = this->m_Id;
				shutdown["event"] = "ShutDown";
				shutdown["param"]["callID"] = it.first;
				this->PushEvent(model::EventType_t(new model::_EventType(shutdown)));

			}
		}
		LOG4CPLUS_INFO(log, "." + this->getId(), " Stop.");
	}

	bool Call::IsClosed()
	{
		return m_StateMachines.empty();
	}

	bool Call::pushEvent(const model::EventType_t & evt)
	{
		return m_EvtBuffer.Put(evt);
	}

	void Call::mainEventLoop()
	{
		try
		{
			model::PerformElementPtr call;
			model::EventType_t Event;
			if (m_EvtBuffer.Get(Event, 0) && !Event->eventName.empty()) {

				const Json::Value & jsonEvent = Event->jsonEvent;

				std::string connectid;


				fsm::TriggerEvent evt(Event->eventName, Event->type);

				for (auto & it : jsonEvent.getMemberNames()) {
					evt.addVars(it, jsonEvent[it]);
				}

				if (m_StateMachines.empty()) {
					
					StateMachine call(this->m_model->createStateMachine(m_SMFileName));

					if (call == nullptr) {
						LOG4CPLUS_ERROR(log, "." + getId(), m_SMFileName << " parse filed.");
						return;
					}

					call->setLoggerId(this->log.getName());
					call->setSessionID(m_Id);
					call->setOnTimer(this->m_model);
					m_StateMachines[m_Id] = call;
					for (auto & itt : this->m_Vars.getMemberNames())
					{
						call->setVar(itt, this->m_Vars[itt]);
					}

					for (auto & itt : ProcessModule::g_Modules) {
						call->addSendImplement(itt.get());
					}

					call->addSendImplement(this);
					call->start(false);
				}

				LOG4CPLUS_DEBUG(log, "." + this->getId(), " Recived a event," << Event->origData);

				const auto & it = m_StateMachines.begin();
				it->second->pushEvent(evt);
				it->second->mainEventLoop();

				if (it->second->isInFinalState()) {
					it->second->stop();
					m_StateMachines.erase(it);
				}

			}
		}
		catch (std::exception & e)
		{
			LOG4CPLUS_ERROR(log, "." + this->getId(), e.what());
		}

	}

	void Call::processSend(const fsm::FireDataType & fireData, const void * param, bool & bHandled)
	{
		/*
		Json::Value newEvent;
		newEvent["from"] = fireData.from;
		newEvent["id"] = fireData.dest;
		newEvent["event"] = fireData.event;
		newEvent["type"] = fireData.type;
		newEvent["param"] = fireData.param;
		const auto & pe = this->m_model->getPerformElementByGlobal(fireData.dest);
		if (pe != nullptr) {
			pe->PushEvent(model::EventType_t(new model::_EventType(newEvent)));
		}
		else {
			LOG4CPLUS_WARN(log, "." + this->getId(), "not find device:" << fireData.dest);
		}
		*/
		LOG4CPLUS_WARN(log, "." + this->getId(), "processSend not implement.");
		bHandled = true;

	}

	void Call::fireSend(const fsm::FireDataType & fireData, const void * param)
	{
		LOG4CPLUS_TRACE(log, "." + this->getId(), " fireSend:" << fireData.event);
		bool bHandled = false;
		this->processSend(fireData, param, bHandled);
	}

}
}