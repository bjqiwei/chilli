#include "AvayaVDN.h"
#include "TSAPIModule.h"
#include <log4cplus/loggingmacros.h>
#include <scxml/TriggerEvent.h>

namespace chilli {
namespace Avaya {

	AvayaVDN::AvayaVDN(TSAPIModule * model, const std::string &ext, const std::string &smFileName)
		:m_model(model), Device(model, ext, smFileName)
	{
		std::string logName = "AvayaVDN";
		log = log4cplus::Logger::getInstance(logName);
	}

	AvayaVDN::~AvayaVDN() {
	}

	bool AvayaVDN::IsClosed()
	{
		return false;
	}

	bool AvayaVDN::pushEvent(const model::EventType_t &evt)
	{
		//return m_EventBuffer.Put(evt);
		const Json::Value & jsonEvent = evt.event;
		if (jsonEvent["event"].isString()) {

			uint32_t callid = 0;
			if (jsonEvent["callid"].isInt())
				callid = jsonEvent["callid"].asInt();

			if (callid == 0)
			{
				LOG4CPLUS_WARN(log, this->getId() << " callid is invalid," << jsonEvent.toStyledString());
				return -1;

			}

			std::string ext = m_model->findACDByCallid(callid);
		
			if (ext.empty()) {
				ext = m_model->findIdleACD(callid);
			}

			if (!ext.empty())
			{
				chilli::model::EventType_t newEvent(jsonEvent);
				newEvent.event["extension"] = ext;
				newEvent.event["stationNo"] = m_stationNo;
				newEvent.event["companyid"] = m_companyid;

				this->m_model->PushEvent(newEvent);
			}
		}
		return 0;
	}

	void AvayaVDN::mainEventLoop()
	{
	}

	void AvayaVDN::fireSend(const std::string &strContent, const void * param)
	{
	}


}
}