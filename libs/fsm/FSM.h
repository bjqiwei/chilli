#ifndef _INTERPRETER_HEADER_
#define _INTERPRETER_HEADER_
#include "common/xmlHelper.h"
#include <string>
#include <map>
#include "config.h"
#include <log4cplus/logger.h>

#include "scxml/TriggerEvent.h"
#include "scxml/EventDispatcher.h"
#include "scxml/Context.h"
//#include "scxml/Evaluator.h"
#include "scxml/SMInstance.h"
#include "scxml/model/Transition.h"
//#include "scxml/model/Log.h"
//#include "common/lock.h"


using namespace std;


namespace fsm{

	//template class INTERPRETER_EXPORT std::map<std::string, Send *>;
	class FSM_EXPORT StateMachine {
	public:
		StateMachine(const string &xml = "");
		StateMachine(const StateMachine &other);
		virtual ~StateMachine();
		StateMachine & operator=(const StateMachine & other);
		
		//初始化状态机
		bool Init(void);
		bool Init(const string &xmlFile);
		//开始进入初始化状态
		void go();
		const xmlNodePtr getCurrentState(void) const;
		const std::string getCurrentStateID(void) const;
		void pushEvent(TriggerEvent & Evt) const;
		void setName(const string &strName);
		bool addEventDispatcher( EventDispatcher * evtDsp);
		const std::string& getName();
		const std::string& getSessionId()const;
		Context  *  getRootContext(); 
		xmlNodePtr getDataModel(); 
		void setscInstance(SMInstance *);
		void setLog(log4cplus::Logger log);
		void setSessionID(const std::string &strSessionid);
		void reset();
	protected:
		std::string m_strStateFile;
		helper::xml::CXmlDocumentPtr m_xmlDocPtr;
		//xmlHelper::xmlDocumentPtr _docPtr2;
		xmlNodePtr  m_initState;
		mutable xmlNodePtr m_currentStateNode;
		xmlNodePtr m_rootNode;
		std::string m_strSessionID;
		std::string m_strName;
		log4cplus::Logger  log;
		helper::xml::CXPathContextPtr xpathCtx;

		void normalize(const xmlNodePtr &rootNode);
		bool isState(const xmlNodePtr &xmlNode) const;
	private:
		//将文件解析成xml文档。
		void parse();

		static bool inline isTransition(const xmlNodePtr &Node) ;
		static bool inline isLog(const xmlNodePtr &Node) ;
		static bool inline isEvent(const xmlNodePtr &Node) ;
		static bool inline isEntry(const xmlNodePtr &Node) ;
		static bool inline isExit(const xmlNodePtr &Node) ;
		static bool inline isSend(const xmlNodePtr &Node) ;
		static bool inline isScript(const xmlNodePtr &Node) ;
		static bool inline isTimer(const xmlNodePtr &Node) ;

		void processEvent( const xmlNodePtr &eventNode) const;
		void processTransition(model::Transition & transition) const;
		void processExit(const xmlNodePtr &node) const;

		//处理entry节点函数，传入entry节点指针，返回值表示是否继续执行余下的entry节点。
		bool processEntry(const xmlNodePtr &node)const;
		void processSend(const xmlNodePtr &node)const;
		void processScript(const xmlNodePtr &node)const;
		void processTimer(const xmlNodePtr &node)const;

		void enterStates(const xmlNodePtr &stateNode) const;
		void exitStates() const;
		xmlNodePtr getState(const string& stateId) const;

		const ::xmlNodePtr getParentState(const xmlNodePtr &currentState)const;
		xmlNodePtr getTargetStates(const xmlNodePtr &transition) const;
	private:
		std::map<std::string, EventDispatcher *> m_mapSendObject;
		SMInstance * m_scInstance;
		//mutable helper::CLock m_lock;
	public:
		mutable TriggerEvent m_currentEvt;
		
	};
}
#endif