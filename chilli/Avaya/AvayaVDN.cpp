#include "AvayaVDN.h"
#include "TSAPIModule.h"
#include <log4cplus/loggingmacros.h>
#include <scxml/TriggerEvent.h>

namespace chilli {
namespace Avaya {

	AvayaVDN::AvayaVDN(TSAPIModule * model, const std::string &ext, const std::string &smFileName)
		:m_model(model), Extension(model, ext, smFileName)
	{
		std::string logName = "AvayaVDN.";
		log = log4cplus::Logger::getInstance(logName.append(m_ExtNumber));
	}

	AvayaVDN::~AvayaVDN() {
	}

	void AvayaVDN::Start()
	{
	}

	void AvayaVDN::Stop()
	{
	}

	bool AvayaVDN::IsFinalState()
	{
		return false;
	}

	bool AvayaVDN::setVar(const std::string & name, const Json::Value & value)
	{
		if (name == "_extension.companyid")
		{
			if (value.isString())
				m_companyid = value.asString();
		}
		else if (name == "_stationNo")
		{
			if (value.isString())
				m_stationNo = value.asString();
		}
		return true;
	}

	int AvayaVDN::pushEvent(const model::EventType_t &evt)
	{
		//return m_EventBuffer.Put(evt);
		const Json::Value & jsonEvent = evt.event;
		if (jsonEvent["event"].isString()) {

			uint32_t callid = 0;
			if (jsonEvent["callid"].isInt())
				callid = jsonEvent["callid"].asInt();

			if (callid == 0)
			{
				LOG4CPLUS_WARN(log, "callid is invalid," << jsonEvent.toStyledString());
				return -1;

			}

			if (m_model->m_callid2ACDExtenion.find(callid) == m_model->m_callid2ACDExtenion.end())
			{
				for (auto & it : m_model->m_ACDExts){
					if (it.second == false) {
						it.second = true;
						m_model->addcallid2ACD(callid, it.first);
						break;
					}
				}
			}

			auto & ext = m_model->m_callid2ACDExtenion.find(callid);

			if (ext == m_model->m_callid2ACDExtenion.end())
			{
				LOG4CPLUS_ERROR(log, "overload max acd size:" << m_model->m_ACDExts.size());
				return -1;
			}

			chilli::model::EventType_t newEvent(jsonEvent);
			newEvent.event["extension"] = ext->second;
			newEvent.event["stationNo"] = m_stationNo;
			newEvent.event["companyid"] = m_companyid;
			
			this->m_model->PushEvent(newEvent);

			if (jsonEvent["event"].asString() == "CALL_CLEARED")
			{
				m_model->m_ACDExts[ext->second] = false;
				m_model->removecallid2ACD(callid);
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

	int AvayaVDN::Answer()
	{
		return 0;
	}

	int AvayaVDN::PlayFile(const std::string & fileName)
	{
		return 0;
	}

	int AvayaVDN::HangUp()
	{
		return 0;
	}

}
}