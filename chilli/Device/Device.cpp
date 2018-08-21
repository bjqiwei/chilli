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
				it.second->stop();
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
				if (m_EvtBuffer.Get(Event, 0) && !Event.event.isNull()) {
					const Json::Value & jsonEvent = Event.event;

					std::string eventName;
					std::string sessionId = m_Id;
					std::string type;

					if (jsonEvent["type"].isString())
						type = jsonEvent["type"].asString();

					if (jsonEvent["event"].isString()) {
						eventName = jsonEvent["event"].asString();
					}

					if (jsonEvent["param"]["sessionID"].isString()) {
						sessionId = jsonEvent["param"]["sessionID"].asString();
					}

					if (sessionId.empty()){
						LOG4CPLUS_WARN(log, "." + this->getId(), "sessionid is null");
						return;
					}

					fsm::TriggerEvent evt(eventName, type);

					for (auto & it : jsonEvent.getMemberNames()) {
						evt.addVars(it, jsonEvent[it]);
					}

					Json::FastWriter writer;
					LOG4CPLUS_DEBUG(log, "." + this->getId() + "." + sessionId, " Recived a event," << writer.write(Event.event));

					if (m_Sessions.find(sessionId) == m_Sessions.end()) {
						Session session(new fsm::StateMachine(log.getName(), this->getId() +"." + sessionId, m_SMFileName, this->m_model));
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

					const auto & it = m_Sessions.find(sessionId);
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
				LOG4CPLUS_ERROR(log, "." + this->getId(), e.what());
			}
		}

		void Device::processSend(Json::Value & jsonData, const void * param, bool & bHandled)
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
				if (pe != nullptr) {
					pe->PushEvent(chilli::model::EventType_t(newEvent));
				}
				else {
					LOG4CPLUS_WARN(log, "." + this->getId(), "not find device:" << newEvent["id"].asString());
				}
				bHandled = true;
			}

		}

		void Device::fireSend(const std::string &strContent, const void * param)
		{
			LOG4CPLUS_TRACE(log, "." + this->getId(), "fireSend:" << strContent);
			Json::Value jsonData;
			Json::CharReaderBuilder b;
			std::shared_ptr<Json::CharReader> jsonReader(b.newCharReader());
			std::string jsonerr;

			if (!jsonReader->parse(strContent.c_str(), strContent.c_str()+strContent.length(), &jsonData, &jsonerr)) {
				LOG4CPLUS_ERROR(log, "." + this->getId(), strContent << " not json data." << jsonerr);
				return;
			}
			bool bHandled = false;
			processSend(jsonData, param, bHandled);
		}

	}
}