#include "TriggerEvent.h"
#include <sstream>

namespace fsm
{

	TriggerEvent::TriggerEvent(const std::string &name, int const type)
	{
		this->name = name;
		this->type = type;
	}

	TriggerEvent::TriggerEvent(const std::string &name, const std::string &data,int const type)
	{
		this->name = name;
		this->type = type;
		this->data = data;
	}
	std::string &TriggerEvent::getName()
	{
		return name;
	}
	std::string &TriggerEvent::getData()
	{
		return data;
	}

	int TriggerEvent::getType()
	{
		return type;
	}

	bool TriggerEvent::Equals(const TriggerEvent & obj)
	{
		if (type == obj.type && name ==obj.name && data == obj.data) {
			return true;
		}

		return false;
	}

	std::string TriggerEvent::ToString()
	{
		std::stringstream ss;
		ss <<  "TriggerEvent{name=" << name << ",type=" << type << ",data=" << data <<"}";
		return ss.str();
	}

}

