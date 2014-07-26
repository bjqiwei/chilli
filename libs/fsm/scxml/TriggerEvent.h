#pragma once
#ifndef _SCXML_TRIGGEREVENT_HEADER_
#define _SCXML_TRIGGEREVENT_HEADER_
#include <string>
#include "..\config.h"

namespace fsm
{

	//状态机事件类，当有事件时，生成一个此对象，然后发送给状态机。
	class FSM_EXPORT TriggerEvent
	{

	public:

		TriggerEvent():m_ParamPtr(NULL),type(-1){};
		//根据事件名称和事件类型生成一个事件。
		TriggerEvent(const std::string &name, int const type); //this(name, type, nullptr);
		//根据事件名称，数据，事件类型生成一个事件。
		TriggerEvent(const std::string &name, const std::string &data, int const type); 

		
	private:
		std::string m_strEventName;
		std::string m_strData;
		const void * m_ParamPtr;
		int type;
		
		
	public:
		void setEventName(const std::string &strEventName){m_strEventName = strEventName;}
		void setData(const std::string &strData){m_strData = strData;}
		void setParam(const void * param){m_ParamPtr = param;}

		const std::string &getEventName(){return m_strEventName;}
		const std::string &getData(){return m_strData;}
		const void * getParam(){return m_ParamPtr;}

		const int &getType(){return type;}

		virtual bool Equals(const TriggerEvent & obj);
		virtual std::string ToString();

	};
}

#endif // end head file