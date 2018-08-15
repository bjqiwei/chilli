#pragma once
#include <string>
#include <stdint.h>
#include <json/config.h>
#include <json/json.h>

namespace chilli {
namespace model {
	typedef struct _EventType
	{
		_EventType() {};
		explicit _EventType(const Json::Value & _event) :event(_event) {};
		//explicit _EventType(const Json::Value & _event, uint64_t _connect) :event(_event),connect(_connect) {};
		Json::Value event;
		//uint64_t connect = 0;
	}EventType_t;

	typedef struct _SQLEventType
	{
		_SQLEventType() {};
		explicit _SQLEventType(const std::string & sql) :m_sql(sql) {};
		explicit _SQLEventType(const std::string & sql, const std::string & ext) :m_sql(sql), m_ExtNumber(ext) {};
		std::string m_sql;
		std::string m_ExtNumber;
		std::string m_ConnectionID;
		uint32_t m_times = 0;
	}SQLEventType_t;
}

enum 
{
INVALID_REQUEST         = 1000,
INVALID_CALLING_DEVICE  = 1001,
INVALID_CALLED_DEVICE   = 1002,
INVALID_CALL_CONNECTION = 1003,
INVALID_CALL            = 1004,
NO_ANSWER               = 1005,
FILE_NOT_FOUND          = 1401,
USER_NOT_REGISTERED     = 1606,
};

}