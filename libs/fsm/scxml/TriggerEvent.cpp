#include "TriggerEvent.h"
#include <sstream>

namespace fsm
{

	TriggerEvent::TriggerEvent(const std::string &name, int const type):m_strEventName(name),m_ParamPtr(NULL)
	{
		this->type = type;
	}

	TriggerEvent::TriggerEvent(const std::string &name, const std::string &data,int const type):m_strEventName(name),
		m_strData(data),m_ParamPtr(NULL)
	{
		this->type = type;
	}
	

	bool TriggerEvent::Equals(const TriggerEvent & obj)
	{
		if (type == obj.type && m_strEventName ==obj.m_strEventName && m_strData == obj.m_strData) {
			return true;
		}

		return false;
	}

	std::string TriggerEvent::ToString()
	{
		std::stringstream ss;
		ss <<  "TriggerEvent{name=" << m_strEventName << ",type=" << type << ",data=" << m_strData <<"}";
		return ss.str();
	}

}

