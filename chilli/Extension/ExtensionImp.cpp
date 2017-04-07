#include "ExtensionImp.h"
#include "../model/ProcessModule.h"
#include <log4cplus/loggingmacros.h>
#include <scxml/TriggerEvent.h>

namespace chilli {
	namespace Extension {

		ExtensionImp::ExtensionImp(model::ProcessModule * model, const std::string &ext, const std::string &smFileName)
			:Extension(model, ext, smFileName), m_ExtNumber(ext)
		{
			std::string logName = "ExtensionImp.";
			log = log4cplus::Logger::getInstance(logName.append(m_ExtNumber));
			LOG4CPLUS_DEBUG(log, "new a extension object.");
		}

		ExtensionImp::~ExtensionImp() {
			LOG4CPLUS_DEBUG(log, "destruction a extension object.");
		}

		const std::string & ExtensionImp::getExtensionNumber() const
		{
			return m_ExtNumber;
		}


		void ExtensionImp::setSessionId(const std::string & sessinId)
		{
			this->m_SessionId = sessinId;
		}

		const std::string & ExtensionImp::getSessionId()
		{
			return this->m_SessionId;
		}


		int ExtensionImp::Answer()
		{
			LOG4CPLUS_WARN(log, "not implement.");
			return 0;
		}

		int ExtensionImp::PlayFile(const std::string &fileName)
		{
			LOG4CPLUS_WARN(log, "not implement.");
			return 0;
		}

		int ExtensionImp::HangUp()
		{
			LOG4CPLUS_WARN(log, "not implement.");
			return 0;
		}

		void ExtensionImp::processSend(const std::string & strContent, const void * param, bool & bHandled)
		{
			Json::Value jsonData;
			Json::Reader jsonReader;
			if (jsonReader.parse(strContent, jsonData)) {
				if (jsonData["type"].asString() == "notify")
				{
					std::string dest = jsonData["dest"].asString();
					std::string sendData = jsonData["param"].toStyledString();
					this->m_model->PushEvent(sendData);
				}
			}
			else {
				LOG4CPLUS_ERROR(log, strContent << " not json data.");
			}

		}

		void ExtensionImp::fireSend(const std::string &strContent, const void * param)
		{
			LOG4CPLUS_TRACE(log, " recive a Send event from stateMachine:" << strContent);
			bool bHandled = false;
			processSend(strContent, param, bHandled);
		}

		int ExtensionImp::pushEvent(const model::EventType_t & Event)
		{
			Json::Value jsonEvent;
			Json::Reader jsonReader;
			if (jsonReader.parse(Event.event, jsonEvent)) {
				std::string eventName;

				if (jsonEvent["event"].isString()) {
					eventName = jsonEvent["event"].asString();
				}

				fsm::TriggerEvent evt(eventName);

				for (auto & it : jsonEvent.getMemberNames()) {
					evt.addVars(it, jsonEvent[it]);
				}

				LOG4CPLUS_INFO(log, " Recived a event," << Event.event);
				m_SM->pushEvent(evt);

			}
			else {
				LOG4CPLUS_ERROR(log, __FUNCTION__ ",event:" << Event.event << " not json data.");
			}

			return 0;
		}

	}
}