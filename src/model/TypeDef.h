#pragma once
#include <string>
#include <stdint.h>
#include <json/config.h>
#include <json/json.h>

namespace chilli {
namespace model {
	struct _EventType
	{
		explicit _EventType(const std::string &_id, const std::string &_sessionId, const std::string & _eventName, const std::string & _type, const Json::Value & _event, const std::string & data) 
			:id(_id), sessionid(_sessionId), eventName(_eventName), type(_type), jsonEvent(_event), origData(data) {
		};

		explicit _EventType(const Json::Value & _event, const std::string & data)
			:jsonEvent(_event), origData(data) {
			if (jsonEvent["id"].isString())
				this->id = jsonEvent["id"].asString();
			
			if (jsonEvent["event"].isString())
				this->eventName = jsonEvent["event"].asString();
			
			if (jsonEvent["type"].isString())
				this->type = jsonEvent["type"].asString();

			if (jsonEvent["param"]["sessionID"].isString())
				this->sessionid = jsonEvent["param"]["sessionID"].asString();
		};

		explicit _EventType(const Json::Value & _event)
			:jsonEvent(_event) {
			if (jsonEvent["id"].isString())
				this->id = jsonEvent["id"].asString();

			if (jsonEvent["event"].isString())
				this->eventName = jsonEvent["event"].asString();

			if (jsonEvent["type"].isString())
				this->type = jsonEvent["type"].asString();

			if (jsonEvent["param"]["sessionID"].isString())
				this->sessionid = jsonEvent["param"]["sessionID"].asString();

			Json::StreamWriterBuilder builder;
			builder.settings_["indentation"] = "";
			this->origData = Json::writeString(builder, this->jsonEvent);

		};

		//explicit _EventType(const Json::Value & _event, uint64_t _connect) :event(_event),connect(_connect) {};
		Json::Value jsonEvent;
		std::string id;
		std::string sessionid;
		std::string eventName;
		std::string type;
		std::string origData;
		//uint64_t connect = 0;
	};
	typedef std::shared_ptr<_EventType> EventType_t;

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