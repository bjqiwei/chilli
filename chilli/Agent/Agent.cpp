#include "Agent.h"
#include <log4cplus/loggingmacros.h>
#include <json/config.h>
#include <json/json.h>
#include "../model/ProcessModule.h"

namespace chilli{
namespace Agent{


Agent::Agent(model::ProcessModule * model, const std::string &ext, const std::string &smFileName)
	:PerformElement(model, ext), m_SMFileName(smFileName)
{
	std::string logName= "Agent";
	log = log4cplus::Logger::getInstance(logName);
	log.setAppendName("." + this->getId());
	LOG4CPLUS_DEBUG(log," new a Agent object.");
}

Agent::~Agent(){
	LOG4CPLUS_DEBUG(log, " destruction a Agent object.");
}

void Agent::processSend(Json::Value & jsonData, const void * param, bool & bHandled)
{

}

void Agent::fireSend(const std::string & strContent,const void * param)
{
	LOG4CPLUS_TRACE(log, " fireSend:" << strContent);
	Json::Value jsonData;
	Json::CharReaderBuilder b;
	std::shared_ptr<Json::CharReader> jsonReader(b.newCharReader());
	std::string jsonerr;

	if (!jsonReader->parse(strContent.c_str(), strContent.c_str()+strContent.length(), &jsonData, &jsonerr)) {
		LOG4CPLUS_ERROR(log, this->getId() << " " << " not json data." << jsonerr);
		return;
	}
	bool bHandled = false;
	processSend(jsonData, param, bHandled);
}

void Agent::Start()
{
	LOG4CPLUS_INFO(log, " Start.");
	for (auto & it : m_StateMachines) {
		it.second->start(false);
	}
}

void Agent::Stop()
{
	for (auto & it : m_StateMachines) {
		it.second->stop();
	}
	LOG4CPLUS_INFO(log, " Stop.");
}

bool Agent::IsClosed()
{
	return m_StateMachines.empty();
}

bool Agent::pushEvent(const model::EventType_t & Event)
{
	return m_EvtBuffer.Put(Event);
}

void Agent::mainEventLoop()
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

			fsm::TriggerEvent evt(eventName, type);

			for (auto & it : jsonEvent.getMemberNames()) {
				evt.addVars(it, jsonEvent[it]);
			}

			LOG4CPLUS_DEBUG(log, " Recived a event," << Event.event.toStyledString());

			if (m_StateMachines.begin() == m_StateMachines.end()) {
				StateMachine sm(new fsm::StateMachine(this->log.getName(), m_Id, m_SMFileName, this->m_model));
				m_StateMachines[connectid] = sm;

				for (auto & itt : this->m_Vars.getMemberNames())
				{
					sm->setVar(itt, this->m_Vars[itt]);
				}

				for (auto & itt : model::ProcessModule::g_Modules) {
					sm->addSendImplement(itt.get());
				}

				sm->addSendImplement(this);
				sm->start(false);
			}

			auto it = m_StateMachines.begin();
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

}
}