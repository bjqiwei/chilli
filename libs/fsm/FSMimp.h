#pragma once
#include "common/CEventBuffer.h"
#include "common/Timer.h"
#include <string>
#include <map>
#include <queue>
#include <list>
#include <log4cplus/logger.h>
#include "scxml/TriggerEvent.h"
#include "scxml/SendInterface.h"
#include "scxml/model/State.h"
#include "scxml/model/Scriptmodel.h"
#include "scxml/model/Datamodel.h"
#include "scxml/model/Transition.h"
#include "scxml/model/Send.h"
#include "scxml/model/Event.h"
#include "scxml/model/Timer.h"
#include "scxml/model/Script.h"
#include "scxml/model/Event.h"
#include "scxml/model/Log.h"
#include "scxml/model/Raise.h"
#include "scxml/model/Sleep.h"



namespace fsm{

	class Context;
	class  StateMachineimp {
		friend class StateMachine;
		friend class parseFSM;
	protected:
		StateMachineimp();
		virtual ~StateMachineimp();

		StateMachineimp(const StateMachineimp &other);
		StateMachineimp & operator=(const StateMachineimp & other);

		//开始进入初始化状态
		bool start(bool block = true);
		//停止运行
		void stop();
		//const model::State * getCurrentState(void) const;
		const std::string getCurrentStateID(void) const;

		//void setName(const string &strName);
		const std::string& getName() const;

		void setOnTimer(helper::OnTimerInterface * func);
		void setLoggerId(const std::string & logId);
		void setSessionID(const std::string &strSessionid);
		const std::string& getSessionID()const;

		bool setVar(const std::string &name, const Json::Value &value);

		bool addSendImplement( SendInterface * evtDsp);
		void setLog(log4cplus::Logger log);

		void pushEvent(const TriggerEvent & Evt);
		void mainEventLoop();
		bool isInFinalState();
	public:
		static void initialize();
		static void threadCleanup();
		static void threadIdle();
		static void unInitialize();
	private:
		std::string m_strStateFile;
		//xmlHelper::xmlDocumentPtr _docPtr2;
		std::string m_initState;
		std::string m_finalState;
		std::string m_strName;
		std::string m_strSessionID;
		const model::State * m_currentState = nullptr;
		Context *  m_Context = nullptr;
		helper::TimerServer * m_TimerServer = nullptr;
		helper::OnTimerInterface * m_TimeOutFunc = nullptr;

	private:
		TriggerEvent m_currentEvt;

		std::atomic_bool m_Running;
		std::atomic_bool m_Block;
		std::queue<TriggerEvent> m_internalQueue;
		helper::CEventBuffer<TriggerEvent> m_externalQueue;
		std::list<std::pair<std::string, Json::Value>> m_globalVars;
		std::map<std::string, SendInterface *> m_mapSendObject;
		typedef std::string TStateID;
		std::vector<std::shared_ptr<model::Scriptmodel>> m_ScriptModel;
		std::vector<std::shared_ptr<model::Datamodel>> m_Datamodel;
		std::map<TStateID, std::shared_ptr<model::State>>m_States;

		log4cplus::Logger  log;
	protected:

		bool processEvent(const TriggerEvent &event);

		bool processEvent( const model::Event * eventNode) const;
		bool processTransition(const model::Transition * transition) const;
		bool processExit(const model::OnExit * onexit) const;

		//处理entry节点函数，传入entry节点指针，返回值表示是否继续执行余下的entry节点。
		bool processEntry(const model::OnEntry * onentry)const;
		bool processSend(const model::Send * send)const;
		bool processScript(const model::Script * script)const;
		bool processTimer(const model::Timer * timer)const;
		bool processLog(const model::Log * log) const;
		bool processRaise(const model::Raise * raise)const;
		bool processSleep(const model::Sleep * sleep)const;

		void enterStates(const model::State * state) const;
		void exitStates() const;

		Context * getRootContext() const; 
		void releaseContext(Context * ctx);
		model::State * getState(const std::string & stateId) const;
		const model::State * getParentState(const model::State * currentState)const;

		helper::TimerServer * getTimerServer() const;
	};
}