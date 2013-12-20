#pragma once
#ifndef _SCXML_TRIGGEREVENT_HEADER_
#define _SCXML_TRIGGEREVENT_HEADER_
#include <string>
#include <config.h>

namespace fsm
{

	//状态机事件类，当有事件时，生成一个此对象，然后发送给状态机。
	class FSM_EXPORT TriggerEvent
	{

	public:

		TriggerEvent():type(-1),m_ParamPtr(NULL){};
		//根据事件名称和事件类型生成一个事件。
		TriggerEvent(const std::string &name, int const type); //this(name, type, nullptr);
		//根据事件名称，数据，事件类型生成一个事件。
		TriggerEvent(const std::string &name, const std::string &data, int const type); 

		
	private:
		std::string m_strEventName;
		std::string m_strMsgType;
		std::string m_strData;
		std::string m_ip;
		unsigned m_port;
		int type;
		void * m_ParamPtr;
		
	public:
		virtual std::string &getName();
		virtual std::string &getData();
		virtual int getType();
		virtual bool Equals(const TriggerEvent & obj);
		virtual std::string ToString();

	};
}

#endif // end head file