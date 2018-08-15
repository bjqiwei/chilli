#include "AvayaDevice.h"
#include "TSAPIModule.h"
#include <log4cplus/loggingmacros.h>
#include <scxml/TriggerEvent.h>
#include <json/config.h>
#include <json/json.h>

namespace chilli {
namespace Avaya {

	AvayaDevice::AvayaDevice(TSAPIModule * model, const std::string &ext, const std::string &smFileName)
		:m_model(model), Device(model, ext, smFileName)
	{
		std::string logName = "AvayaDevice";
		log = log4cplus::Logger::getInstance(logName);
		log.setAppendName("." + this->getId());
	}

	AvayaDevice::~AvayaDevice() {
	}

	void AvayaDevice::fireSend(const std::string &strContent, const void * param)
	{
		LOG4CPLUS_TRACE(log, " fireSend:" << strContent);
		Json::Value jsonData;
		Json::CharReaderBuilder b;
		std::shared_ptr<Json::CharReader> reader(b.newCharReader());

		std::string err;
		if (!reader->parse(strContent.c_str(), strContent.c_str()+ strContent.length(), &jsonData, &err)) {
			LOG4CPLUS_ERROR(log, strContent << " not json data." << err);
			return;
		}

		bool bHandled = false;
		this->processSend(jsonData, param, bHandled);
		
	}

	void AvayaDevice::processSend(Json::Value & jsonData, const void * param, bool & bHandled)
	{
		m_model->processSend(jsonData, param, bHandled, this);
		if (!bHandled) {
			Device::processSend(jsonData, param, bHandled);
		}
	}

}
}