#ifndef _INTERPRETER_HEADER_
#define _INTERPRETER_HEADER_
#include "xmlHelper.h"
#include <string>
#include <map>

#ifdef USE_LOG4CPLUS
#include <log4cplus/logger.h>
#endif
#include "config.h"
#include <scxml/TriggerEvent.h>
#include <scxml/EventDispatcher.h>
#include <scxml/Context.h>
#include <scxml/Evaluator.h>
#include <scxml/SCInstance.h>
#include <scxml/model/Transition.h>
#include <scxml/model/Log.h>


using namespace std;


namespace fsm{

	//template class INTERPRETER_EXPORT std::map<std::string, Send *>;
	class FSM_EXPORT StateMachine {
	public:
		StateMachine(const string xml = "");
		StateMachine(const StateMachine &other);
		virtual ~StateMachine();
		StateMachine & operator=(const StateMachine & other);
		
		//初始化状态机
		void Init(void);
		void Init(const string xmlFile);
		//开始进入初始化状态
		void go();
		const xmlNodePtr getCurrentState(void) const;
		const std::string getCurrentStateID(void) const;
		void pushEvent(TriggerEvent & Evt) const;
		void setName(const string strName);
		bool addEventDispatcher( EventDispatcher * evtDsp);
		const std::string& getName();
		const std::string& getSessionId();
		Evaluator * getEvaluator() const;
		Context  *  getRootContext(); 
		xmlNodePtr getDataModel(); 
		void setscInstance(SCInstance *);
		void setLog(log4cplus::Logger log);
	protected:
		std::string _strStateFile;
		xmlHelper::xmlDocumentPtr _docPtr;
		//xmlHelper::xmlDocumentPtr _docPtr2;
		xmlNodePtr  _initState;
		mutable xmlNodePtr _currentState;
		xmlNodePtr _rootNode;
		mutable std::string _strSessionID;
		std::string _strName;
		#ifdef USE_LOG4CPLUS
		log4cplus::Logger log;
		#endif

		void normalize(const xmlNodePtr rootNode);
		bool isState(const xmlNodePtr xmlNode) const;
	private:
		//将文件解析成xml文档。
		void parse();

		static bool inline isTransition(const xmlNodePtr Node) throw();
		static bool inline isLog(const xmlNodePtr Node) throw();
		static bool inline isEvent(const xmlNodePtr Node) throw();
		static bool inline isEntry(const xmlNodePtr Node) throw();
		static bool inline isExit(const xmlNodePtr Node) throw();
		static bool inline isSend(const xmlNodePtr Node) throw();
		static bool inline isScript(const xmlNodePtr Node) throw();
		static bool inline isTimer(const xmlNodePtr Node) throw();

		void processEvent( xmlNodePtr eventNode) const;
		void processTransition(model::Transition & transition) const;
		void processLog( model::Log &log) const;
		void processExit(const xmlNodePtr node) const;
		void processEntry(const xmlNodePtr node)const;
		void processSend(const xmlNodePtr node)const;
		void processScript(const xmlNodePtr node)const;
		void processTimer(const xmlNodePtr node)const;

		void enterStates(const xmlNodePtr stateNode) const;
		void exitStates() const;
		xmlNodePtr getState(const string& stateId) const;

		const ::xmlNodePtr getParentState(const xmlNodePtr currentState)const;
		xmlNodePtr getTargetStates(const xmlNodePtr transition) const;
	private:
		std::map<std::string, EventDispatcher *> _vecSend;
		SCInstance * scInstance;
		mutable CRITICAL_SECTION csection;
		
	};
}
#endif