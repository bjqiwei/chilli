#include "FreeSwitchDevice.h"
#include "FreeSwitchModule.h"
#include <log4cplus/loggingmacros.h>
#include <scxml/TriggerEvent.h>

namespace chilli {
namespace FreeSwitch {

	FreeSwitchDevice::FreeSwitchDevice(FreeSwitchModule * model, const std::string &ext, const std::string &smFileName)
		:m_model(model), Device(model, ext, smFileName)
	{
		std::string logName = "FreeSwitchDevice";
		log = log4cplus::Logger::getInstance(logName);
		LOG4CPLUS_DEBUG(log, this->getId() << " new a device object.");
	}

	FreeSwitchDevice::~FreeSwitchDevice() {
		LOG4CPLUS_DEBUG(log, this->getId() << " destruction a device object.");
	}

	void FreeSwitchDevice::fireSend(const std::string &strContent, const void * param)
	{
		LOG4CPLUS_TRACE(log, this->getId() << " fireSend:" << strContent);
		bool bHandled = false;
		this->processSend(strContent, param, bHandled);
		
	}

	void FreeSwitchDevice::processSend(const std::string & strContent, const void * param, bool & bHandled)
	{
		m_model->processSend(strContent, param, bHandled, this);
		if (!bHandled) {
			Device::processSend(strContent, param, bHandled);
		}
	}

}
}