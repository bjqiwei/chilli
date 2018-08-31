#include "Group.h"
#include "../model/ProcessModule.h"
#include <log4cplus/loggingmacros.h>
#include <scxml/TriggerEvent.h>

namespace chilli {
namespace Group {

	Group::Group(model::ProcessModule * model, const std::string &ext, const std::string &smFileName)
		:Device(model, ext, smFileName)
	{
		std::string logName = "GroupImp";
		log = log4cplus::Logger::getInstance(logName);
		LOG4CPLUS_DEBUG(log, "." + this->getId(), " new a group object.");
	}

	Group::~Group() {
		LOG4CPLUS_DEBUG(log, "." + this->getId(), " destruction a group object.");
	}

	void Group::processSend(const fsm::FireDataType & fireData, const void * param, bool & bHandled)
	{
		return Device::processSend(fireData, param, bHandled);	
	}

	void Group::fireSend(const fsm::FireDataType & fireData, const void * param)
	{
		LOG4CPLUS_TRACE(log, "." + this->getId(), " fireSend:" << fireData.event);

		bool bHandled = false;
		this->processSend(fireData, param, bHandled);
	}

}
}