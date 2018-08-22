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

	void Group::processSend(Json::Value & jsonData, const void * param, bool & bHandled)
	{
		return Device::processSend(jsonData, param, bHandled);	
	}

	void Group::fireSend(const std::string &strContent, const void * param)
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

}
}