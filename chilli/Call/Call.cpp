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
		log.setAppendName("." + this->getId());
		LOG4CPLUS_DEBUG(log, " new a call object.");
	}

	Call::~Call() {
		m_StateMachines.clear();
		LOG4CPLUS_DEBUG(log, " destruction a call object.");
	}

	void Call::Start()
	{
		LOG4CPLUS_INFO(log, " Start.");
		for (auto & it : m_StateMachines) {
			it.second->start(false);
		}
	}

	void Call::Stop()
	{
		for (auto & it : m_StateMachines) {
			it.second->stop();
		}
		LOG4CPLUS_INFO(log, " Stop.");
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
			if (m_EvtBuffer.Get(Event, 0) && !Event.event.isNull()) {

				const Json::Value & jsonEvent = Event.event;

				std::string eventName;
				std::string connectid;
				std::string type;

				if (jsonEvent["event"].isString()) {
					eventName = jsonEvent["event"].asString();
				}
				if (jsonEvent["type"].isString()){
					type = jsonEvent["type"].asString();
				}

				fsm::TriggerEvent evt(eventName, type);

				for (auto & it : jsonEvent.getMemberNames()) {
					evt.addVars(it, jsonEvent[it]);
				}

				LOG4CPLUS_DEBUG(log, " Recived a event," << Event.event.toStyledString());

				if (m_StateMachines.empty()) {
					
					StateMachine call(new fsm::StateMachine(log.getName(), m_Id, m_SMFileName, this->m_model));

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

				auto & it = m_StateMachines.begin();
				it->second->pushEvent(evt);
				it->second->mainEventLoop();

				if (it->second->isInFinalState()) {
					it->second->stop();
					m_StateMachines.erase(it);
				}

				if (this->IsClosed())
				{
					call = this->m_model->removePerfromElement(this->getId());
				}
			}
		}
		catch (std::exception & e)
		{
			LOG4CPLUS_ERROR(log, e.what());
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
			LOG4CPLUS_ERROR(log, strContent << " not json data.");
		}
	}

	void Call::fireSend(const std::string &strContent, const void * param)
	{
		LOG4CPLUS_TRACE(log, " fireSend:" << strContent);
		bool bHandled = false;
		this->processSend(strContent, param, bHandled);

	}

}
}