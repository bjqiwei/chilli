#include "FreeSwitchDevice.h"
#include "FreeSwitchModule.h"
#include <log4cplus/loggingmacros.h>
#include <scxml/TriggerEvent.h>

namespace chilli {
namespace FreeSwitch {

	FreeSwitchDevice::FreeSwitchDevice(FreeSwitchModule * model, const std::string &ext, const std::string &smFileName)
		:m_model(model), Device(model, ext, smFileName)
	{
		std::string logName = "FSDevice";
		log = log4cplus::Logger::getInstance(logName);
		log.setAppendName("." + this->getId());
		LOG4CPLUS_DEBUG(log, " new a device object.");
	}

	FreeSwitchDevice::~FreeSwitchDevice() {
		LOG4CPLUS_DEBUG(log, " destruction a device object.");
	}

	void FreeSwitchDevice::fireSend(const std::string &strContent, const void * param)
	{
		LOG4CPLUS_TRACE(log, " fireSend:" << strContent);
		Json::Value jsonData;
		Json::Reader jsonReader;

		if (!jsonReader.parse(strContent, jsonData)) {
			LOG4CPLUS_ERROR(log, strContent << " not json data.");
			return;
		}

		bool bHandled = false;
		this->processSend(jsonData, param, bHandled);
		
	}

	void FreeSwitchDevice::processSend(Json::Value & jsonData, const void * param, bool & bHandled)
	{
		if (jsonData["event"].asString() == "ClearConnection")
		{
			bHandled = m_model->ClearConnection(jsonData["param"], this->log);
		}
		if (jsonData["event"].asString() == "StartRecord")
		{
			bHandled = m_model->StartRecord(jsonData["param"], this->log);
		}
		if (jsonData["event"].asString() == "PlayFile")
		{
			bHandled = m_model->PlayFile(jsonData["param"], this->log);
		}
		else
			m_model->processSend(jsonData, param, bHandled, log);

		if (!bHandled) {
			Device::processSend(jsonData, param, bHandled);
		}
	}

}
}