#include "TriggerEvent.h"
#include <sstream>

namespace fsm
{

	TriggerEvent::TriggerEvent(const std::string &name):m_strEventName(name),m_ParamPtr(NULL)
	{
	}

	TriggerEvent::TriggerEvent(const std::string &name, const std::string &data):m_strEventName(name),
		m_strData(data),m_ParamPtr(NULL)
	{
	}
	

	bool TriggerEvent::Equals(const TriggerEvent & obj)
	{
		if (m_strMsgType.compare(obj.m_strMsgType)==0 && m_strEventName ==obj.m_strEventName && m_strData == obj.m_strData) {
			return true;
		}

		return false;
	}

	std::string TriggerEvent::ToString()
	{
		std::stringstream ss;
		ss <<  "TriggerEvent{name=" << m_strEventName << ",msgtype=" << m_strMsgType << ",data=" << m_strData <<"}";
		return ss.str();
	}

	void TriggerEvent::addVars(const std::string & name, Json::Value & value)
	{
		m_eventVars.insert(std::make_pair(name, value));
	}


}

