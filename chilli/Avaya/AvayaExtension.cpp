#include "AvayaExtension.h"
#include "TSAPIModule.h"
#include <log4cplus/loggingmacros.h>
#include <scxml/TriggerEvent.h>

namespace chilli {
namespace Avaya {

	AvayaExtension::AvayaExtension(TSAPIModule * model, const std::string &ext, const std::string &smFileName)
		:m_model(model), ExtensionImp(model, ext, smFileName)
	{
		std::string logName = "AvayaExtension.";
		log = log4cplus::Logger::getInstance(logName.append(m_ExtNumber));
	}

	AvayaExtension::~AvayaExtension() {
	}

	void AvayaExtension::fireSend(const std::string &strContent, const void * param)
	{
		LOG4CPLUS_TRACE(log, "fireSend:" << strContent);
		bool bHandled = false;
		this->processSend(strContent, param, bHandled);
		
	}

	void AvayaExtension::processSend(const std::string & strContent, const void * param, bool & bHandled)
	{
		m_model->processSend(strContent, param, bHandled, this);
		if (!bHandled) {
			ExtensionImp::processSend(strContent, param, bHandled);
		}
	}

}
}