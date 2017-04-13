#pragma once
#include <string>
#include <stdint.h>
#include <json/json.h>

namespace chilli {
namespace model {
	typedef struct _EventType
	{
		_EventType() {};
		explicit _EventType(const Json::Value & _event) :event(_event) {};
		explicit _EventType(const Json::Value & _event, uint64_t _connect) :event(_event),connect(_connect) {};
		Json::Value event;
		uint64_t connect = 0;
	}EventType_t;
}
}