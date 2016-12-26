#pragma once
#include <string>

namespace chilli {
namespace model {
	typedef struct _EventType
	{
		_EventType() {};
		_EventType(const std::string & _event) :event(_event) {};
		std::string event;
	}EventType_t;
}
}