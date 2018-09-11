#pragma once
#include <string>
#include "FSMimp.h"
#include <libxml/parser.h>
#include "scxml/TriggerEvent.h"
#include "scxml/SendInterface.h"
#include "scxml/model/State.h"
#include "scxml/model/Scriptmodel.h"
#include "scxml/model/Datamodel.h"
#include "scxml/model/OnEntry.h"
#include "scxml/model/OnExit.h"
#include "scxml/model/Event.h"
#include "scxml/model/Send.h"
#include "scxml/model/Transition.h"
#include "scxml/model/Log.h"
#include "scxml/model/Timer.h"
#include "scxml/model/Raise.h"
#include "scxml/model/Sleep.h"



namespace fsm{
	class  parseFSM {

	public:
		static StateMachineimp * fsmParseFileImp(const std::string & filename);
		static StateMachineimp * fsmParseMemoryImp(const char *buffer, size_t size);
	private:
		static bool isDatamodel(const xmlNodePtr & xmlNode);
		static bool isScriptModel(const xmlNodePtr & xmlNode);
		static bool isData(const xmlNodePtr & xmlNode);
		static bool isState(const xmlNodePtr &xmlNode) ;
		static bool isTransition(const xmlNodePtr &Node) ;
		static bool isLog(const xmlNodePtr &Node) ;
		static bool isEvent(const xmlNodePtr &Node) ;
		static bool isEntry(const xmlNodePtr &Node) ;
		static bool isExit(const xmlNodePtr &Node) ;
		static bool isSend(const xmlNodePtr &Node) ;
		static bool isScript(const xmlNodePtr &Node) ;
		static bool isTimer(const xmlNodePtr &Node) ;
		static bool isRaise(const xmlNodePtr &Node) ;
		static bool isSleep(const xmlNodePtr &Node);

		static StateMachineimp * parsefsm(xmlDocPtr _xmlDocPtr, const std::string & filename);
		static void parseDataModel(xmlNodePtr datamodelNode, StateMachineimp * imp, const std::string & filename);
		static void parseScriptModel(xmlNodePtr scriptmodelNode, StateMachineimp * imp, const std::string & filename);
		static void parseState(model::State * parent, xmlNodePtr stateNode, StateMachineimp * imp, const std::string & filename);
		static std::shared_ptr<model::OnEntry> parseOnEntry(xmlNodePtr onentryNode, const std::string & filename);
		static std::shared_ptr<model::OnExit> parseOnExit(xmlNodePtr onexitNode, const std::string & filename);
		static std::shared_ptr<model::Event> parseEvent(xmlNodePtr eventNode, const std::string & filename);
		static std::shared_ptr<model::Data> parseData(xmlNodePtr dataNode, const std::string & filename);
		static std::shared_ptr<model::Log> parseLog(xmlNodePtr logNode, const std::string & filename);
		static std::shared_ptr<model::Script> parseScript(xmlNodePtr scriptNode, const std::string & filename);
		static std::shared_ptr<model::Send> parseSend(xmlNodePtr sendNode, const std::string & filename);
		static std::shared_ptr<model::Timer> parseTimer(xmlNodePtr timerNode, const std::string & filename);
		static std::shared_ptr<model::Raise> parseRaise(xmlNodePtr raiseNode, const std::string & filename);
		static std::shared_ptr<model::Sleep> parseSleep(xmlNodePtr sleepNode, const std::string & filename);
		static std::shared_ptr<model::Transition> parseTransition(xmlNodePtr transitionNode, const std::string & filename);



	public:
		/****************************************************  
		@describle   应用XML Schema模板文件验证案例文档 
		@param schema_filename  模式文件  
		@param xml           XML格式的案例文档 
		@param xmlType		案例文档是磁盘文件还是内存字符串。
		@ErrorMsg		返回的错误内容
		@retval  ==0  验证成功 
				>0  验证失败  
		****************************************************/  
		static int is_valid(const std::string &schema_filename, const std::string & xml, int xtype, std::string &ErrorMsg);
		static void XMLCALL myXmlStructuredErrorFunc (void *userData, xmlErrorPtr error)
		{
			fprintf(stderr,"%s file'%s',line:%d\n",error->message,error->file,error->line);
			return;
		}
	};
}