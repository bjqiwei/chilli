#pragma once
#include <string>
#include <stdint.h>

namespace chilli {
namespace model {
	typedef struct _EventType
	{
		_EventType() {};
		_EventType(const std::string & _event) :event(_event) {};
		_EventType(const std::string & _event, uint64_t _connect) :event(_event),connect(_connect) {};
		std::string event;
		uint64_t connect = 0;
	}EventType_t;
}
}