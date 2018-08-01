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
		LOG4CPLUS_DEBUG(log, this->getId() << " new a group object.");
	}

	Group::~Group() {
		LOG4CPLUS_DEBUG(log, this->getId() << " destruction a group object.");
	}

	void Group::processSend(const std::string & strContent, const void * param, bool & bHandled)
	{
		Json::Value jsonData;
		Json::Reader jsonReader;
		if (jsonReader.parse(strContent, jsonData)) {

			jsonData["param"]["from"] = jsonData["from"];
			jsonData["param"]["extension"] = jsonData["dest"];
			jsonData["param"]["event"] = jsonData["event"];
			jsonData["param"]["type"] = jsonData["type"];
			chilli::model::EventType_t sendData(jsonData["param"]);
			this->m_model->PushEvent(sendData);
			bHandled = true;

		}
		else {
			LOG4CPLUS_ERROR(log, this->getId() << " " << strContent << " not json data.");
		}

		if (!bHandled) {
			Device::processSend(strContent, param, bHandled);
		}
	}

	void Group::fireSend(const std::string &strContent, const void * param)
	{
		LOG4CPLUS_TRACE(log, this->getId() << " fireSend:" << strContent);
		bool bHandled = false;
		this->processSend(strContent, param, bHandled);
	}

}
}