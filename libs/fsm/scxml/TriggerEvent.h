#pragma once
#ifndef _SCXML_TRIGGEREVENT_HEADER_
#define _SCXML_TRIGGEREVENT_HEADER_
#include <string>

namespace fsm
{

	//状态机事件类，当有事件时，生成一个此对象，然后发送给状态机。
	class FSM_EXPORT TriggerEvent
	{

	public:

		TriggerEvent():m_ParamPtr(NULL),m_port(0),type(-1){};
		//根据事件名称和事件类型生成一个事件。
		TriggerEvent(const std::string &name, int const type); //this(name, type, nullptr);
		//根据事件名称，数据，事件类型生成一个事件。
		TriggerEvent(const std::string &name, const std::string &data, int const type); 

		
	private:
		std::string m_strEventName;
		std::string m_strMsgType;
		std::string m_strData;
		std::string m_ip;
		void * m_ParamPtr;
		unsigned m_port;
		int type;
		
		
	public:
		void setEventName(const std::string &strEventName){m_strEventName = strEventName;}
		void setData(const std::string &strData){m_strData = strData;}
		void setMsgType(const std::string &strMsgtype){m_strMsgType = strMsgtype;}
		void setParam(void * param){m_ParamPtr = param;}
		void setIP(const std::string &strIp){ m_ip = strIp;}
		void setPort(const unsigned &port){ m_port = port ;}

		const std::string &getEventName(){return m_strEventName;}
		const std::string &getData(){return m_strData;}
		const std::string &getMsgType(){return m_strMsgType;}
		void * getParam(){return m_ParamPtr;}
		const std::string &getIP(){ return m_ip;}
		const unsigned &getPort(){return m_port;}

		const int &getType(){return type;}

		virtual bool Equals(const TriggerEvent & obj);
		virtual std::string ToString();

	};
}

#endif // end head file