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
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " new a ACD device object.");
}
ACDDevice::~ACDDevice(){
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " destruction a ACD device object.");
}

void ACDDevice::mainEventLoop()
{
	try
	{

		model::EventType_t Event;
		if (m_EvtBuffer.Get(Event, 0) && !Event ->jsonEvent.empty()) {
			const Json::Value & jsonEvent = Event->jsonEvent;

			std::string connectid;


			fsm::TriggerEvent evt(Event->eventName, Event->type);

			for (auto & it : jsonEvent.getMemberNames()) {
				evt.addVars(it, jsonEvent[it]);
			}

			LOG4CPLUS_DEBUG(log, "." + this->getId(), " Recived a event," << Event->origData);

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

			const auto & it = m_Sessions.begin();
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
		LOG4CPLUS_ERROR(log, "." + this->getId(), " " << e.what());
	}
}

}
}