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
	}

	AvayaDevice::~AvayaDevice() {
	}

	void AvayaDevice::fireSend(const fsm::FireDataType &fireData, const void * param)
	{
		LOG4CPLUS_TRACE(log, "." + this->getId(), " fireSend:" << fireData.event);

		bool bHandled = false;
		this->processSend(fireData, param, bHandled);
		
	}

	void AvayaDevice::processSend(const fsm::FireDataType &fireData, const void * param, bool & bHandled)
	{
		m_model->processSend(fireData, param, bHandled, this);
		if (!bHandled) {
			Device::processSend(fireData, param, bHandled);
		}
	}

}
}