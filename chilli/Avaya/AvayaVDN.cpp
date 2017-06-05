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
		if (value.isArray())
		{
			for (uint32_t i =0; i< value.size();i++)
			{
				if (value[i].isString())
					m_ACDExts[value[i].asString()] = false;
			}
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

			if (m_callid2Extenion.find(callid) == m_callid2Extenion.end())
			{
				for (auto & it : m_ACDExts){
					if (it.second == false) {
						it.second = true;
						m_callid2Extenion[callid] = it.first;
						break;
					}
				}
				LOG4CPLUS_DEBUG(log, "exist call size:" << m_callid2Extenion.size());
			}

			auto & ext = m_callid2Extenion.find(callid);

			if (ext == m_callid2Extenion.end())
			{
				LOG4CPLUS_ERROR(log, "overload max acd size:" << m_ACDExts.size());
				return -1;
			}

			chilli::model::EventType_t newEvent(jsonEvent);
			newEvent.event["extension"] = ext->second;
			
			this->m_model->PushEvent(newEvent);

			if (jsonEvent["event"].asString() == "CALL_CLEARED")
			{
				m_ACDExts[ext->second] = false;
				m_callid2Extenion.erase(callid);
				LOG4CPLUS_DEBUG(log, "exist call size:" << m_callid2Extenion.size());
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