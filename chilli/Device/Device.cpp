#include "Device.h"
#include "../model/ProcessModule.h"
#include <log4cplus/loggingmacros.h>
#include <scxml/TriggerEvent.h>

namespace chilli {
	namespace Device {

		Device::Device(model::ProcessModule * model, const std::string &ext, const std::string &smFileName)
			:PerformElement(model, ext, smFileName)
		{
			std::string logName = "Device.";
			log = log4cplus::Logger::getInstance(logName.append(m_ExtNumber));
			LOG4CPLUS_DEBUG(log, "new a extension object.");
		}

		Device::~Device() {
			LOG4CPLUS_DEBUG(log, "destruction a extension object.");
		}

		int Device::Answer()
		{
			LOG4CPLUS_WARN(log, "not implement.");
			return 0;
		}

		int Device::PlayFile(const std::string &fileName)
		{
			LOG4CPLUS_WARN(log, "not implement.");
			return 0;
		}

		int Device::HangUp()
		{
			LOG4CPLUS_WARN(log, "not implement.");
			return 0;
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
				LOG4CPLUS_ERROR(log, strContent << " not json data.");
			}

		}

		void Device::fireSend(const std::string &strContent, const void * param)
		{
			LOG4CPLUS_TRACE(log, "fireSend:" << strContent);
			bool bHandled = false;
			processSend(strContent, param, bHandled);
		}

	}
}