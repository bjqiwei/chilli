#include "AvayaDevice.h"
#include "TSAPIModule.h"
#include <log4cplus/loggingmacros.h>
#include <scxml/TriggerEvent.h>

namespace chilli {
namespace Avaya {

	AvayaDevice::AvayaDevice(TSAPIModule * model, const std::string &ext, const std::string &smFileName)
		:m_model(model), Device(model, ext, smFileName)
	{
		std::string logName = "AvayaExtension.";
		log = log4cplus::Logger::getInstance(logName.append(m_ExtNumber));
	}

	AvayaDevice::~AvayaDevice() {
	}

	void AvayaDevice::fireSend(const std::string &strContent, const void * param)
	{
		LOG4CPLUS_TRACE(log, "fireSend:" << strContent);
		bool bHandled = false;
		this->processSend(strContent, param, bHandled);
		
	}

	void AvayaDevice::processSend(const std::string & strContent, const void * param, bool & bHandled)
	{
		m_model->processSend(strContent, param, bHandled, this);
		if (!bHandled) {
			Device::processSend(strContent, param, bHandled);
		}
	}

}
}