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
		const Json::Value & jsonEvent = evt->jsonEvent;
		if (jsonEvent["event"].isString()) {

			uint32_t callid = 0;
			if (jsonEvent["callid"].isInt())
				callid = jsonEvent["callid"].asInt();

			if (callid == 0)
			{
				LOG4CPLUS_WARN(log, "." + this->getId(), " callid is invalid," << evt->origData);
				return false;

			}

			std::string ext = m_model->findACDByCallid(callid);
		
			if (ext.empty()) {
				ext = m_model->findIdleACD(callid);
			}

			if (!ext.empty())
			{
				evt->jsonEvent["id"] = ext;
				evt->id = ext;
				evt->jsonEvent["stationNo"] = m_stationNo;
				evt->jsonEvent["companyid"] = m_companyid;

				this->m_model->PushEvent(evt);
			}
		}
		return 0;
	}

	void AvayaVDN::mainEventLoop()
	{
	}

	void AvayaVDN::fireSend(const fsm::FireDataType &fireData, const void * param)
	{
	}


}
}