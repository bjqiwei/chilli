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
			LOG4CPLUS_DEBUG(log, this->getId() << " new a device object.");
		}

		Device::~Device() {
			LOG4CPLUS_DEBUG(log, this->getId() << " destruction a device object.");
		}

		void Device::Start()
		{
			LOG4CPLUS_INFO(log, this->getId()<< " Start.");
			for (auto & it : m_Connections) {
				it.second->start(false);
			}
		}

		void Device::Stop()
		{
			for (auto & it : m_Connections) {
				it.second->stop();
			}
			LOG4CPLUS_INFO(log, this->getId() << " Stop.");
		}

		bool Device::IsClosed()
		{
			return m_Connections.empty();
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
					std::string connectid;
					std::string type;

					if (jsonEvent["type"].isString())
						type = jsonEvent["type"].asString();

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

					LOG4CPLUS_DEBUG(log, this->getId() << " Recived a event," << Event.event.toStyledString());

					if (m_Connections.find(connectid) == m_Connections.end()) {
						Connction connection(new fsm::StateMachine(m_Id, m_SMFileName, nullptr));
						m_Connections[connectid] = connection;

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

					auto & it = m_Connections.find(connectid);
					it->second->pushEvent(evt);
					it->second->mainEventLoop();

					if (it->second->isInFinalState()) {
						it->second->stop();
						m_Connections.erase(it);
					}
				}
			}
			catch (std::exception & e)
			{
				LOG4CPLUS_ERROR(log, this->getId() << e.what());
			}
		}

		void Device::processSend(const std::string & strContent, const void * param, bool & bHandled)
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
				LOG4CPLUS_ERROR(log, this->getId() << strContent << " not json data.");
			}

		}

		void Device::fireSend(const std::string &strContent, const void * param)
		{
			LOG4CPLUS_TRACE(log, this->getId() << "fireSend:" << strContent);
			bool bHandled = false;
			processSend(strContent, param, bHandled);
		}

	}
}