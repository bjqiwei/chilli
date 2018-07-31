#include "FreeSwitchExtension.h"
#include "FreeSwitchModule.h"
#include <log4cplus/loggingmacros.h>
#include <scxml/TriggerEvent.h>

namespace chilli {
namespace FreeSwitch {

	FreeSwitchExtension::FreeSwitchExtension(FreeSwitchModule * model, const std::string &ext, const std::string &smFileName)
		:m_model(model), Device(model, ext, smFileName)
	{
		std::string logName = "FreeSwitchExtension.";
		log = log4cplus::Logger::getInstance(logName.append(m_ExtNumber));
	}

	FreeSwitchExtension::~FreeSwitchExtension() {
	}

	void FreeSwitchExtension::fireSend(const std::string &strContent, const void * param)
	{
		LOG4CPLUS_TRACE(log, "fireSend:" << strContent);
		bool bHandled = false;
		this->processSend(strContent, param, bHandled);
		
	}

	void FreeSwitchExtension::processSend(const std::string & strContent, const void * param, bool & bHandled)
	{
		m_model->processSend(strContent, param, bHandled, this);
		if (!bHandled) {
			Device::processSend(strContent, param, bHandled);
		}
	}

}
}