#ifndef _INTERPRETER_HEADER_
#define _INTERPRETER_HEADER_

#include "config.h"
#include <string>
#include <json/json.h>
#include <log4cplus/logger.h>
#include "scxml/TriggerEvent.h"
#include "scxml/SendInterface.h"


using namespace std;


namespace fsm{

	class StateMachineimp;
	//template class INTERPRETER_EXPORT std::map<std::string, Send *>;
	enum xmlType{
		File,
		Memory,
	};
	class FSM_EXPORT StateMachine {
	public:
		StateMachine(const std::string &sessionid, const string &xml, xmlType xtype = xmlType::File);
		virtual ~StateMachine();
		StateMachine(const StateMachine &other) = delete;
		StateMachine & operator=(const StateMachine & other) = delete;
		
		//开始进入初始化状态
		bool go();
		//停止运行
		void termination();

		const std::string getCurrentStateID(void) const;

		//void setName(const string &strName);
		const std::string& getName() const;

		void setSessionID(const std::string &strSessionid);
		const std::string& getSessionId()const;

		bool setVar(const std::string &name, const Json::Value &value);
		Json::Value getVar(const std::string &name) const;

		bool addSendImplement( SendInterface * evtDsp);

		void pushEvent(const TriggerEvent & Evt);
		void mainEventLoop();

	private:
		StateMachineimp * imp;
	};
}
#endif