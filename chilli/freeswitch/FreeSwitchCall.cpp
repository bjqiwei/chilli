#include "FreeSwitchCall.h"
#include "FreeSwitchModule.h"
#include "../uuid.h"
#include <log4cplus/loggingmacros.h>
#include <scxml/TriggerEvent.h>

using namespace chilli::model;
namespace chilli {
namespace FreeSwitch {

	FreeSwitchCall::FreeSwitchCall(FreeSwitchModule * model, const std::string &ext, const std::string &smFileName)
		:m_model(model), Device(model, ext, smFileName)
	{
		std::string logName = "FreeSwitchExtension.";
		log = log4cplus::Logger::getInstance(logName.append(m_ExtNumber));
	}

	FreeSwitchCall::~FreeSwitchCall() {
		m_Calls.clear();
	}

	void FreeSwitchCall::fireSend(const std::string &strContent, const void * param)
	{
		LOG4CPLUS_TRACE(log, "fireSend:" << strContent);
		bool bHandled = false;
		this->processSend(strContent, param, bHandled);
		
	}

	void FreeSwitchCall::mainEventLoop()
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

				if (jsonEvent["ConnectionID"].isString()) {
					connectid = jsonEvent["ConnectionID"].asString();
				}

				fsm::TriggerEvent evt(eventName);

				for (auto & it : jsonEvent.getMemberNames()) {
					evt.addVars(it, jsonEvent[it]);
				}

				LOG4CPLUS_DEBUG(log, " Recived a event," << Event.event.toStyledString());

				if (m_ConnectID2CallID.find(connectid) == m_ConnectID2CallID.end()) {
					std::string callid = uuid();
					Call call(new fsm::StateMachine(m_ExtNumber, m_SMFileName, ProcessModule::OnTimerExpiredFunc));
					m_Calls[callid] = call;
					m_ConnectID2CallID[connectid] = callid;

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

				std::string callid = m_ConnectID2CallID.find(connectid)->second;
				auto & it = m_Calls.find(callid);
				it->second->pushEvent(evt);
				it->second->mainEventLoop();

				if (it->second->isInFinalState()) {
					it->second->stop();
					m_Calls.erase(it);
					m_ConnectID2CallID.erase(connectid);
					auto & itc = m_ConnectID2ConnectID.find(connectid);
					if ( itc != m_ConnectID2ConnectID.end()){
						m_ConnectID2ConnectID.erase(itc);
						m_ConnectID2CallID.erase(itc->second);
					}
				}
			}
		}
		catch (std::exception & e)
		{
			LOG4CPLUS_ERROR(log, e.what());
		}

	}

	bool FreeSwitchCall::IsFinalState()
	{
		return !m_Calls.empty();
	}

	void FreeSwitchCall::Start()
	{
		LOG4CPLUS_INFO(log, " Start.");
		for (auto & it : m_Calls) {
			it.second->start(false);
		}
	}

	void FreeSwitchCall::Stop()
	{
		for (auto & it : m_Calls) {
			it.second->stop();
		}
		LOG4CPLUS_INFO(log, " Stop.");
	}

	void FreeSwitchCall::processSend(const std::string & strContent, const void * param, bool & bHandled)
	{
		m_model->processSend(strContent, param, bHandled, this);
		if (!bHandled) {
			Device::processSend(strContent, param, bHandled);
		}
	}

}
}