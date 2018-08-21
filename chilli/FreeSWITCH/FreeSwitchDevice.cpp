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
		LOG4CPLUS_DEBUG(log, "." + this->getId(), " new a device object.");
	}

	FreeSwitchDevice::~FreeSwitchDevice() {
		LOG4CPLUS_DEBUG(log, "." + this->getId(), " destruction a device object.");
	}

	void FreeSwitchDevice::fireSend(const std::string &strContent, const void * param)
	{
		LOG4CPLUS_TRACE(log, "." + this->getId(), " fireSend:" << strContent);
		Json::Value jsonData;
		Json::CharReaderBuilder b;
		std::shared_ptr<Json::CharReader> jsonReader(b.newCharReader());
		std::string jsonerr;

		if (!jsonReader->parse(strContent.c_str(), strContent.c_str()+strContent.length(), &jsonData, &jsonerr)) {
			LOG4CPLUS_ERROR(log, "." + this->getId(), strContent << " not json data." << jsonerr);
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
		else if (jsonData["event"].asString() == "StartRecord")
		{
			bHandled = m_model->StartRecord(jsonData["param"], this->log);
		}
		else if (jsonData["event"].asString() == "PlayFile")
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