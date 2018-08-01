#include "Call.h"
#include <log4cplus/loggingmacros.h>
#include <scxml/TriggerEvent.h>
#include "../model/ProcessModule.h"

using namespace chilli::model;
namespace chilli {
namespace Call {

	Call::Call(ProcessModule * model, const std::string &callid, const std::string &smFileName)
		:PerformElement(model, callid)
	{
		std::string logName = "Call";
		log = log4cplus::Logger::getInstance(logName);
		LOG4CPLUS_DEBUG(log, this->getId() << " new a call object.");
	}

	Call::~Call() {
		m_StateMachines.clear();
		LOG4CPLUS_DEBUG(log, this->getId() << " destruction a call object.");
	}

	void Call::Start()
	{
		LOG4CPLUS_INFO(log, this->getId() << " Start.");
		for (auto & it : m_StateMachines) {
			it.second->start(false);
		}
	}

	void Call::Stop()
	{
		for (auto & it : m_StateMachines) {
			it.second->stop();
		}
		LOG4CPLUS_INFO(log, this->getId() << " Stop.");
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
			model::EventType_t Event;
			if (m_EvtBuffer.Get(Event, 0) && !Event.event.isNull()) {

				return;

				const Json::Value & jsonEvent = Event.event;

				std::string eventName;
				std::string connectid;

				if (jsonEvent["event"].isString()) {
					eventName = jsonEvent["event"].asString();
				}

				fsm::TriggerEvent evt(eventName);

				for (auto & it : jsonEvent.getMemberNames()) {
					evt.addVars(it, jsonEvent[it]);
				}

				LOG4CPLUS_DEBUG(log, this->getId() << " Recived a event," << Event.event.toStyledString());

				if (m_StateMachines.empty()) {
					
					StateMachine call(new fsm::StateMachine(m_Id, m_SMFileName, this->m_model));

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

				auto & it = m_StateMachines.begin();
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
			LOG4CPLUS_ERROR(log, this->getId() << " " << e.what());
		}

	}

	void Call::processSend(const std::string & strContent, const void * param, bool & bHandled)
	{
		Json::Value jsonData;
		Json::Reader jsonReader;
		if (jsonReader.parse(strContent, jsonData)) {

			if (jsonData["dest"].isString() && !jsonData["dest"].asString().empty())
			{
				jsonData["param"]["from"] = jsonData["from"];
				jsonData["param"]["extension"] = jsonData["dest"];
				jsonData["param"]["event"] = jsonData["event"];
				jsonData["param"]["type"] = jsonData["type"];
				chilli::model::EventType_t sendData(jsonData["param"]);
				this->m_model->PushEvent(sendData);
			}
			bHandled = true;

		}
		else {
			LOG4CPLUS_ERROR(log, this->getId() << " " << strContent << " not json data.");
		}
	}

	void Call::fireSend(const std::string &strContent, const void * param)
	{
		LOG4CPLUS_TRACE(log, this->getId() << " fireSend:" << strContent);
		bool bHandled = false;
		this->processSend(strContent, param, bHandled);

	}

}
}