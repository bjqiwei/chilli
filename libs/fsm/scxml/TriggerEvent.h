#pragma once
#ifndef _SCXML_TRIGGEREVENT_HEADER_
#define _SCXML_TRIGGEREVENT_HEADER_
#include "..\config.h"
#include <string>
#include <json/json.h>

namespace fsm
{

	//状态机事件类，当有事件时，生成一个此对象，然后发送给状态机。
	class FSM_EXPORT TriggerEvent
	{

	public:

		TriggerEvent():m_ParamPtr(NULL){};
		//根据事件名称和事件类型生成一个事件。
		TriggerEvent(const std::string &name); //this(name,nullptr);
		//根据事件名称，数据，事件类型生成一个事件。
		TriggerEvent(const std::string &name, const std::string & type); 

		
	private:
		std::string m_strEventName;
		std::string m_strMsgType;
		const void * m_ParamPtr;
		std::map<std::string, Json::Value> m_eventVars;
		
		
	public:
		void setEventName(const std::string &strEventName){m_strEventName = strEventName;}
		void setMsgType(const std::string &strMsgtype){m_strMsgType = strMsgtype;}
		void setParam(const void * param){m_ParamPtr = param;}
		void addVars(const std::string & name, const Json::Value & value);

		const std::string &getEventName()const{return m_strEventName;}
		const std::string &getMsgType(){return m_strMsgType;}
		const void * getParam(){return m_ParamPtr;}
		const std::map <std::string,Json::Value> &getVars() { return m_eventVars; };

		virtual bool Equals(const TriggerEvent & obj);
		virtual std::string ToString();

	};
}

#endif // end head file