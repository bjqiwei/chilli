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

		//根据事件名称和事件类型生成一个事件。
		TriggerEvent(const std::string &name, int const type); //this(name, type, nullptr);
		//根据事件名称，数据，事件类型生成一个事件。
		TriggerEvent(const std::string &name, const std::string &data, int const type); 
		/// <summary>
		/// <code>CALL_EVENT</code>.
		/// </summary>
		static const int CALL_EVENT = 1;

		/// <summary>
		/// <code>CHANGE_EVENT</code>.
		/// 
		/// </summary>
		static const int CHANGE_EVENT = 2;

		/// <summary>
		/// <code>SIGNAL_EVENT</code>.
		/// 
		/// </summary>
		static const int SIGNAL_EVENT = 3;

		/// <summary>
		/// <code>TIME_EVENT</code>.
		/// 
		/// </summary>
		static const int TIME_EVENT = 4;

		/// <summary>
		/// <code>ERROR_EVENT</code>.
		/// 
		/// </summary>
		static const int ERROR_EVENT = 5;

		
	private:
		std::string name;
		int type;
		std::string data;
	public:
		virtual std::string &getName();
		virtual std::string &getData();
		virtual int getType();
		virtual bool Equals(const TriggerEvent & obj);
		virtual std::string ToString();

	};
}

#endif // end head file