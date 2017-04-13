#include "TriggerEvent.h"
#include <sstream>

namespace fsm
{

	TriggerEvent::TriggerEvent(const std::string &name):m_strEventName(name),m_ParamPtr(nullptr)
	{
	}

	TriggerEvent::TriggerEvent(const std::string &name, const std::string &type):m_strEventName(name),
		m_strMsgType(type),m_ParamPtr(NULL)
	{
	}
	

	bool TriggerEvent::Equals(const TriggerEvent & obj)
	{
		if (m_strMsgType.compare(obj.m_strMsgType)==0 && m_strEventName ==obj.m_strEventName) {
			return true;
		}

		return false;
	}

	std::string TriggerEvent::ToString()
	{
		std::stringstream ss;
		ss <<  "TriggerEvent{name=" << m_strEventName << ",msgtype=" << m_strMsgType << "}";
		return ss.str();
	}

	void TriggerEvent::addVars(const std::string & name, const Json::Value & value)
	{
		m_eventVars.insert(std::make_pair(name, value));
	}


}

