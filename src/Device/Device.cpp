#include "Device.h"
#include "../model/ProcessModule.h"
#include <log4cplus/loggingmacros.h>


namespace chilli {
	namespace Device {

		Device::Device(model::ProcessModule * model, const std::string &id, const std::string &smFileName)
			:PerformElement(model, id), m_SMFileName(smFileName)
		{
			std::string logName = "Device";
			log = log4cplus::Logger::getInstance(logName);
			//LOG4CPLUS_DEBUG(log, " new a device object.");
		}

		Device::~Device() {
			//LOG4CPLUS_DEBUG(log, " destruction a device object.");
		}

		void Device::Start()
		{
			LOG4CPLUS_INFO(log, "." + this->getId(), " Start.");
			for (auto & it : m_Sessions) {
				it.second->start(false);
			}
		}

		void Device::Stop()
		{
			for (auto & it : m_Sessions) {
				Json::Value shutdown;
				shutdown["id"] = this->m_Id;
				shutdown["event"] = "ShutDown";
				shutdown["type"] = "cmd";
				shutdown["param"]["deviceID"] = this->m_Id;
				shutdown["param"]["sessionID"] = it.first;
				this->PushEvent(model::EventType_t(new model::_EventType(shutdown)));

			}
			LOG4CPLUS_INFO(log, "." + this->getId(), " Stop.");
		}

		bool Device::IsClosed()
		{
			return m_Sessions.empty();
		}

		bool Device::pushEvent(const model::EventType_t &evt)
		{
			return m_EvtBuffer.Put(evt);
		}

		void Device::mainEventLoop()
		{
			try
			{

				model::EventType_t Event;
				if (m_EvtBuffer.Get(Event, 0) && !Event->eventName.empty()) {
					const Json::Value & jsonEvent = Event->jsonEvent;

					const std::string & sessionId = Event->sessionid;

					if (sessionId.empty()) {
						LOG4CPLUS_WARN(log, "." + this->getId(), "sessionid is null:" << Event->origData);
						return;
					}

					fsm::TriggerEvent evt(Event->eventName, Event->type);

					for (const auto & it : jsonEvent.getMemberNames()) {
						evt.addVars(it, jsonEvent[it]);
					}

					if (m_Sessions.find(sessionId) == m_Sessions.end()) {
						Session session(fsm::fsmParseFile(m_SMFileName));

						if (session == nullptr) {
							LOG4CPLUS_ERROR(log, "." + getId(), m_SMFileName << " parse filed.");
							return;
						}

						session->setLoggerId(this->log.getName());
						session->setSessionID(this->getId() + "." + sessionId);
						session->setOnTimer(this->m_model);

						m_Sessions[sessionId] = session;

						for (auto & itt : this->m_Vars.getMemberNames())
						{
							session->setVar(itt, this->m_Vars[itt]);
						}

						for (auto & itt : model::ProcessModule::g_Modules) {
							session->addSendImplement(itt.get());
						}

						session->addSendImplement(this);
						session->start(false);
					}

					LOG4CPLUS_DEBUG(log, "." + this->getId() + "." + sessionId, " Recived a event," << Event->origData);

					const auto & it = m_Sessions.find(sessionId);
					if (it != m_Sessions.end()) {

						it->second->pushEvent(evt);
						it->second->mainEventLoop();
						if (it->second->isInFinalState()) {
							it->second->stop();
							m_Sessions.erase(it);
						}
					}
					else {
						LOG4CPLUS_ERROR(log, "." + this->getId() + "." + sessionId, "no find session :" << Event->origData);
					}

				}
			}
			catch (std::exception & e)
			{
				LOG4CPLUS_ERROR(log, "." + this->getId(), e.what());
			}
		}

		void Device::processSend(const fsm::FireDataType & fireData, const void * param, bool & bHandled)
		{
	
			if (!fireData.dest.empty())
			{
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
					LOG4CPLUS_WARN(log, "." + this->getId(), "not find device:" << newEvent["id"].asString());
				}
				bHandled = true;
			}

		}

		void Device::fireSend(const fsm::FireDataType &fireData, const void * param)
		{
			LOG4CPLUS_TRACE(log, "." + this->getId(), "fireSend:" << fireData.event);
			bool bHandled = false;
			processSend(fireData, param, bHandled);
		}

	}
}