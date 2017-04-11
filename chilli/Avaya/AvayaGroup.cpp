#include "AvayaGroup.h"
#include "TSAPIModule.h"
#include <log4cplus/loggingmacros.h>
#include <scxml/TriggerEvent.h>

namespace chilli {
namespace Avaya {

	AvayaGroup::AvayaGroup(TSAPIModule * model, const std::string &ext, const std::string &smFileName)
		:m_model(model), ExtensionImp(model, ext, smFileName)
	{
		std::string logName = "AvayaGroup.";
		log = log4cplus::Logger::getInstance(logName.append(m_ExtNumber));
	}

	AvayaGroup::~AvayaGroup() {
	}

	void AvayaGroup::fireSend(const std::string &strContent, const void * param)
	{
		LOG4CPLUS_TRACE(log, "fireSend:" << strContent);
		bool bHandled = false;
		this->processSend(strContent, param, bHandled);
	}

	void AvayaGroup::processSend(const std::string & strContent, const void * param, bool & bHandled)
	{
		m_model->processSend(strContent, param, bHandled, this);
		if (!bHandled) {
			ExtensionImp::processSend(strContent, param, bHandled);
		}
	}

}
}