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
			LOG4CPLUS_ERROR(log, e.what());
		}

	}

	void Call::processSend(Json::Value & jsonData, const void * param, bool & bHandled)
	{

		if (jsonData.isObject() && jsonData["dest"].isString() && !jsonData["dest"].asString().empty())
		{
			Json::Value newEvent;
			newEvent["from"] = jsonData["from"];
			newEvent["id"] = jsonData["dest"];
			newEvent["event"] = jsonData["event"];
			newEvent["type"] = jsonData["type"];
			newEvent["param"] = jsonData["param"];
			const auto & pe = this->m_model->getPerformElementByGlobal(newEvent["id"].asString());
			if (pe != nullptr){
				pe->PushEvent(chilli::model::EventType_t(newEvent));
			}
			else {
				LOG4CPLUS_WARN(log, "not find device:" << newEvent["id"].asString());
			}
			bHandled = true;
		}

	}

	void Call::fireSend(const std::string &strContent, const void * param)
	{
		LOG4CPLUS_TRACE(log, " fireSend:" << strContent);
		Json::Value jsonData;
		Json::CharReaderBuilder b;
		std::shared_ptr<Json::CharReader> jsonReader(b.newCharReader());
		std::string jsonerr;

		if (jsonReader->parse(strContent.c_str(),strContent.c_str()+strContent.length(), &jsonData, &jsonerr)) {
			bool bHandled = false;
			this->processSend(jsonData, param, bHandled);
		}
		else {
			LOG4CPLUS_ERROR(log, strContent << " not json data." << jsonerr);
		}
	}

}
}