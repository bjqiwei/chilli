#pragma once

#include "config.h"
#include <string>
#include <json/config.h>
#include <json/json.h>
#include <log4cplus/logger.h>
#include "scxml/TriggerEvent.h"
#include "scxml/SendInterface.h"
#include "common/TimerInterface.h"


using namespace std;

namespace fsm{
	class StateMachineimp;
	typedef helper::OnTimerInterface OnTimerInterface;
	//template class INTERPRETER_EXPORT std::map<std::string, Send *>;

	FSM_EXPORT class StateMachine * fsmParseFile(const std::string & filename);
	FSM_EXPORT class StateMachine * fsmParseMemory(const char *buffer, size_t size);
	FSM_EXPORT void initialize();
	FSM_EXPORT void threadCleanup();
	FSM_EXPORT void threadIdle();
	FSM_EXPORT void unInitialize();

	class FSM_EXPORT StateMachine {
	protected:
		StateMachine();
	public:
		virtual ~StateMachine();
		StateMachine(const StateMachine &other);
		StateMachine & operator=(const StateMachine & other);
		
		//开始进入初始化状态
		bool start(bool block = true);
		//停止运行
		void stop();

		const std::string getCurrentStateID(void) const;

		//void setName(const string &strName);
		const std::string& getName() const;

		void setOnTimer(OnTimerInterface * func);
		void setLoggerId(const std::string & logId);
		void setSessionID(const std::string &strSessionid);
		const std::string& getSessionId()const;

		bool setVar(const std::string &name, const Json::Value &value);

		bool addSendImplement( SendInterface * evtDsp);

		void pushEvent(const TriggerEvent & Evt);
		void mainEventLoop();
		bool isInFinalState();

	private:
		StateMachineimp * imp;
		friend FSM_EXPORT StateMachine * fsmParseFile(const std::string & filename);
		friend FSM_EXPORT StateMachine * fsmParseMemory(const char *buffer, size_t size);
	};
}
