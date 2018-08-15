#include "ACDDevice.h"
#include <log4cplus/loggingmacros.h>
#include <json/config.h>
#include <json/json.h>
#include "../model/ProcessModule.h"

namespace chilli{
namespace ACD{


ACDDevice::ACDDevice(model::ProcessModule * model, const std::string &ext, const std::string &smFileName) 
	:Device(model, ext,smFileName)
{
	std::string logName = "ACD";
	log = log4cplus::Logger::getInstance(logName);
	log.setAppendName("." + this->getId());
	LOG4CPLUS_DEBUG(log, " new a ACD device object.");
}
ACDDevice::~ACDDevice(){
	LOG4CPLUS_DEBUG(log, " destruction a ACD device object.");
}

void ACDDevice::mainEventLoop()
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

			if (m_Sessions.begin() == m_Sessions.end()) {
				Session connection(new fsm::StateMachine(this->log.getName(), m_Id, m_SMFileName, this->m_model));
				m_Sessions[connectid] = connection;

				for (auto & itt : this->m_Vars.getMemberNames())
				{
					connection->setVar(itt, this->m_Vars[itt]);
				}

				for (auto & itt : model::ProcessModule::g_Modules) {
					connection->addSendImplement(itt.get());
				}

				connection->addSendImplement(this);
				connection->start(false);
			}

			auto & it = m_Sessions.begin();
			it->second->pushEvent(evt);
			it->second->mainEventLoop();

			if (it->second->isInFinalState()) {
				it->second->stop();
				m_Sessions.erase(it);
			}
		}
	}
	catch (std::exception & e)
	{
		LOG4CPLUS_ERROR(log, " " << e.what());
	}
}

}
}