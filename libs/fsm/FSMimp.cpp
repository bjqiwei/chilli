#include "FSMimp.h"
#include "scxml/env/JSEvaluator.h"
#include "scxml/model/Script.h"
#include "scxml/model/Event.h"
#include "scxml/model/Script.h"
#include "scxml/model/Send.h"
#include "scxml/model/Timer.h"
#include "scxml/model/Transition.h"
#include "scxml/model/Scriptmodel.h"
#include "scxml/model/Datamodel.h"
#include "scxml/model/Log.h"
#include "scxml/model/Raise.h"
#include "scxml/model/Sleep.h"
#include <log4cplus/loggingmacros.h>
#include "common/stringHelper.h"
#include "common/Timer.h"
#include "common/tls.h"


using namespace std;

enum xmlType{
	File,
	Memory,
};
namespace fsm {
	//static std::atomic_ulong g_StateMachineReferce = 0;
	//static Evaluator * g_Evaluator = nullptr;
	static std::map<StateMachineimp*, StateMachineimp*>g_StateMachines;
	static std::mutex g_StateMtx;
	static tls_key_type g_tls_storage_key = 0;
	static helper::TimerServer * g_TimerServer = nullptr;
}

fsm::StateMachineimp::StateMachineimp(const std::string &sessionid, const string  &xml, int xtype, helper::OnTimerExpiredFunc func)
	:m_xmlType(xtype), m_xmlDocPtr(nullptr), xpathCtx(nullptr), m_strSessionID(sessionid), m_TimeOutFunc(func), m_Running(false), m_Block(false)
{
	log = log4cplus::Logger::getInstance("fsm.StateMachine");

	if (m_xmlType == File)
	{
		m_strStateFile = xml;
	}
	else{
		m_strStateContent = xml;
	}

	std::unique_lock<std::mutex> lck(g_StateMtx);
	if (g_tls_storage_key == 0){
		g_tls_storage_key = tls_init(nullptr);
	}

	if (g_StateMachines.empty()){
		g_TimerServer = new helper::TimerServer();
		g_TimerServer->Start();
	}

	LOG4CPLUS_DEBUG(log, m_strSessionID << ",creat a fsm object." << this);

	g_StateMachines.insert(std::make_pair(this, this));

}

fsm::StateMachineimp::~StateMachineimp()
 { 
	 //if (_ctxt) xmlClearParserCtxt(_ctxt);
	 //_ctxt = NULL;
	std::unique_lock<std::mutex> lck(g_StateMtx);
	g_StateMachines.erase(this);

	if (g_StateMachines.empty()) {

		tls_cleanup(g_tls_storage_key);
		g_tls_storage_key = 0;

		g_TimerServer->Stop();
		delete g_TimerServer;
		g_TimerServer = nullptr;

	}
	LOG4CPLUS_DEBUG(log, m_strSessionID << ",destruction a smscxml object." << this);
 }

bool fsm::StateMachineimp::Init(void)
{
	using namespace helper::xml;
	if (parse()) {

		xmlNodePtr rootNode =  xmlDocGetRootElement(m_xmlDocPtr._xDocPtr);
		 if (rootNode !=NULL && xmlStrEqual(rootNode->name,BAD_CAST("fsm")))
		 {
			 m_rootNode = rootNode;
			 //LOG4CPLUS_TRACE(log, m_strSessionID << ",set rootNode=" << m_rootNode);

			 m_strName =  getXmlNodeAttributesValue(m_rootNode,"name");
			 LOG4CPLUS_TRACE(log, m_strSessionID << ",set name=" << m_strName);

			  /* Create xpath evaluation context */
			  if (xpathCtx._xPathCtxPtr == NULL)
			  {
				  xpathCtx = xmlXPathNewContext(m_xmlDocPtr._xDocPtr);
			  }

			  if (xpathCtx._xPathCtxPtr == NULL) {
				  LOG4CPLUS_ERROR(log, m_strSessionID << ": unable to create new XPath context");
				  throw std::logic_error("Error: unable to create new XPath context");
			  }
			// normalize(_rootNode);
			 string strInitState = getXmlNodeAttributesValue(m_rootNode,"initial");
			 if (m_initState = getState(strInitState)){
			 }
			 else{ 
				m_initState = getXmlChildNode(m_rootNode,"state");
			 }

			 string strFinalState = getXmlNodeAttributesValue(m_rootNode, "final");
			 m_finalState = getState(strFinalState);

			 LOG4CPLUS_TRACE(log, m_strSessionID << ", set initState=" << getXmlNodeAttributesValue(m_initState, "id"));
			 
		 }
		 else
		 {

			 LOG4CPLUS_ERROR(log, m_strSessionID << " ,Cannot find root fsm element." );
			 //throw std::logic_error( "Cannot find FSM element.");
			 return false;
		 }
	}
	else {

		LOG4CPLUS_ERROR(log,  m_strSessionID <<" ,Interpreter has no DOM at all!");
		//throw std::logic_error("Interpreter has no DOM at all!");
		return false;
	}
	return true;
}


void fsm::StateMachineimp::normalize(const xmlNodePtr &smscxml)
{
	//检查文件内容，初始化状态机
	LOG4CPLUS_WARN(log, m_strSessionID << ",normalize fuction is not implement.");
	return ;
}


//const xmlNodePtr fsm::StateMachine::getCurrentState(void) const
//{
//	return m_currentStateNode;
//}

const std::string fsm::StateMachineimp::getCurrentStateID(void) const
{
	return helper::xml::getXmlNodeAttributesValue(m_currentStateNode,"id");
}

inline bool fsm::StateMachineimp::isState(const xmlNodePtr &xNode)
{
	return xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("state")) ; 
}

inline bool fsm::StateMachineimp::isTransition(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("transition")); 
}

inline bool fsm::StateMachineimp::isLog(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("log")); 
}

inline bool fsm::StateMachineimp::isEvent(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("event")); 
}

inline bool fsm::StateMachineimp::isExit(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("onexit")); 
}

inline bool fsm::StateMachineimp::isEntry(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("onentry")); 
}

inline bool fsm::StateMachineimp::isSend(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("send")); 
}

inline bool fsm::StateMachineimp::isScript(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("script")); 
}

inline bool fsm::StateMachineimp::isTimer(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("timer")); 
}

inline bool fsm::StateMachineimp::isRaise(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("raise")); 
}

inline bool fsm::StateMachineimp::isSleep(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("sleep")); 
}

void fsm::StateMachineimp::pushEvent(const TriggerEvent & trigEvent)
{
	m_externalQueue.Put(trigEvent);
}


//将文件解析成xml文档。
bool fsm::StateMachineimp::parse()
{

	if (NULL != m_xmlDocPtr._xDocPtr) {
		LOG4CPLUS_WARN(log, m_strSessionID << ",xmldocument is not empty , there not Parse file:" << this->m_strStateFile);
		return true;
	}

	try{
		/* parse the file */
		//_docPtr = xmlCtxtReadFile(_ctxt, _strStateFile.c_str(), NULL, XML_PARSE_NOERROR);
		if (m_xmlType == File)
		{
			LOG4CPLUS_DEBUG(log, m_strSessionID << ", Parse xml file:" << m_strStateFile);
			m_xmlDocPtr = xmlParseFile(m_strStateFile.c_str());
		}else
		{
			LOG4CPLUS_DEBUG(log,m_strSessionID << ", Parse xml Content:" << m_strStateContent);
			m_xmlDocPtr = xmlParseMemory(m_strStateContent.c_str(), m_strStateContent.length());
		}
	}
	catch(std::exception &e){ 
		LOG4CPLUS_ERROR(log, m_strSessionID << "," << e.what());
		return false;
	}

	if (NULL == m_xmlDocPtr._xDocPtr) 
	{  
		LOG4CPLUS_ERROR(log, m_strSessionID<< "," << m_strStateFile << ",Document not parsed successfully."); 
		//throw std::logic_error( "Document not parsed successfully."); 
		return false;
	} 
	return true;
}

bool fsm::StateMachineimp::processEvent(const xmlNodePtr &eventNode)const
{
	if (!eventNode){
		return false ;
	}
	bool doneSomething = false;
	for (xmlNodePtr actionNode = eventNode->children; actionNode != NULL; actionNode = actionNode->next)
	{

		if (isTransition(actionNode))
		{
			if (processTransition(actionNode)){
				doneSomething = true;
				break;//transition 元素下的元素将不再执行
			}
		}
		else if (isLog(actionNode))
		{
			processLog(actionNode)? doneSomething = true:false;
			continue;
		}

		else if (isSend(actionNode))
		{
			processSend(actionNode)? doneSomething = true:false;
			continue;
		}
		else if (isScript(actionNode))
		{
			processScript(actionNode)? doneSomething = true:false;
			continue;
		}
		else if (isTimer(actionNode))
		{
			processTimer(actionNode)? doneSomething = true:false;
			continue;
		}
		else if (isRaise(actionNode))
		{
			processRaise(actionNode)? doneSomething = true:false;
			continue;
		}
		else if (isSleep(actionNode))
		{
			processSleep(actionNode)? doneSomething = true:false;
			continue;
		}
		else if(actionNode->type == XML_ELEMENT_NODE)
		{
			LOG4CPLUS_ERROR(log, m_strSessionID << ", " << actionNode->name << " process not implement.");
		}
	}
	
	if (!doneSomething)
	{
		LOG4CPLUS_WARN(log, m_strSessionID << ", this event " << helper::xml::getXmlNodeAttributesValue(eventNode, "event") << " done nothing,line:" << eventNode->line);
	}
	return doneSomething;
}

bool fsm::StateMachineimp::processTransition(const xmlNodePtr &actionNode)const
{
	model::Transition transition(actionNode,m_strSessionID,m_strStateFile);
	if (!transition.isEnabledCondition(this->getRootContext()))
		return false ;
	if (xmlNodePtr stateNode = getState(transition.getTarget()))
	{
		exitStates();
		enterStates(stateNode);
	}
	else
	{
		LOG4CPLUS_ERROR(log, m_strSessionID << ","<<m_strStateFile<<" file,not find the target:" << transition.getTarget() << " state, line:" << actionNode->line);
	}
	return true;
}

bool fsm::StateMachineimp::processSend(const xmlNodePtr &Node)const
{
	using namespace helper::xml;
	model::Send send(Node,m_strSessionID,m_strStateFile);

	if (send.isEnabledCondition(this->getRootContext())){
		send.execute(this->getRootContext());
	}
	else{
		return false;
	}

	std::map<std::string , SendInterface *>::const_iterator it = m_mapSendObject.find(send.getTarget());
	if (it != m_mapSendObject.end()) {
		it->second->fireSend(send.getContent(),this);
	}
	else {

		LOG4CPLUS_ERROR(log,m_strSessionID << " not find the send target:" << send.getTarget());
	}
	return true;
}


bool fsm::StateMachineimp::processTimer(const xmlNodePtr &Node)const
{
	if (!Node) return false;
	model::Timer timer(Node,m_strSessionID,m_strStateFile);

	if (timer.isEnabledCondition(this->getRootContext()))
	{
		timer.execute(this->getRootContext());
	}
	else{
		return false;
	}
	

	//LOG4CPLUS_DEBUG(logger,_strName << ":" << _strSessionID << "execute a script:" << script.getContent());
	LOG4CPLUS_DEBUG(log, m_strSessionID << ",set a timer,id=" << timer.getId() << ", interval=" << timer.getInterval());
	Json::Value vars;
	vars["sessionId"] = this->m_strSessionID;
	vars["timerId"] = timer.getId();
	vars["interval"] = timer.getInterval();
	
	g_TimerServer->SetTimer(timer.getInterval(), vars.toStyledString(), m_TimeOutFunc , const_cast<StateMachineimp *>(this));

	return true;
}

bool fsm::StateMachineimp::processLog(const xmlNodePtr &Node)const
{
	if (!Node) return false;
	model::Log log(Node,m_strSessionID,m_strStateFile);
	
	if(log.isEnabledCondition(this->getRootContext())){
		log.execute(this->getRootContext());
	}else{
		return false;
	}
	
	return true;
}

bool fsm::StateMachineimp::processScript(const xmlNodePtr &node) const
{
	if (!node) return false;
	model::Script script(node,m_strSessionID,m_strStateFile);

	if(script.isEnabledCondition(this->getRootContext())){
		script.execute(this->getRootContext());
		return true;
	}
	
	return false;
}

bool fsm::StateMachineimp::processRaise(const xmlNodePtr &node)const
{
	if (!node) return false;
	model::Raise raise(node,m_strSessionID,m_strStateFile);

	if(raise.isEnabledCondition(this->getRootContext())){
		TriggerEvent _raiseEvent;
		_raiseEvent.setEventName(raise.getEvent());
		_raiseEvent.setParam(this);
		LOG4CPLUS_TRACE(log, m_strSessionID << ", Raise a event:" << _raiseEvent.ToString());
		const_cast<StateMachineimp*>(this)->m_internalQueue.push(_raiseEvent);
		return true;
	}

	return false;
}

bool fsm::StateMachineimp::processSleep(const xmlNodePtr &node)const
{
	if (!node) return false;
	model::Sleep sleep(node,m_strSessionID,m_strStateFile);

	if(sleep.isEnabledCondition(this->getRootContext())){
		sleep.execute(this->getRootContext());
		return true;
	}

	return false;
}

const xmlNodePtr fsm::StateMachineimp::getParentState(const xmlNodePtr &currentState)const
{
	xmlNodePtr curState = currentState;
	do
	{
		curState = curState->parent;
		if(curState && isState(curState)) return curState;
	}while (curState != NULL && curState != m_rootNode);

	return NULL;
}

//void fsm::StateMachineimp::setName(const string &strName)
//{
//	m_strName = strName;
//	LOG4CPLUS_DEBUG(log,"set this stateMachine name=" << m_strName);
//}


void fsm::StateMachineimp::exitStates() const
{
	if (m_currentStateNode)
	{
		for (xmlNodePtr  childNode = m_currentStateNode->children; childNode != NULL; childNode = childNode->next)
		{
			if (isExit(childNode))
			{
				processExit(childNode);
			}
		}
	}
}

void fsm::StateMachineimp::enterStates(const xmlNodePtr &stateNode) const
{
	if(isState(stateNode))
	{
		const_cast<StateMachineimp*>(this)->m_currentStateNode = stateNode;
		LOG4CPLUS_DEBUG(log, m_strSessionID << ", enter state:" << getCurrentStateID());
		getRootContext()->setVar("_state._id", getCurrentStateID());
		for (xmlNodePtr  entryNode = stateNode->children; entryNode != NULL; entryNode = entryNode->next)
		{
			if (isEntry(entryNode))
			{
				processEntry(entryNode);
			}
		}
	}
	else
	{
		LOG4CPLUS_ERROR(log, m_strSessionID <<  ", Will enter the node is not a status node.");

	}
}



bool fsm::StateMachineimp::processExit(const xmlNodePtr &exitNode) const
{
	if (!exitNode) return false;

	for ( xmlNodePtr  actionNode = exitNode->children; actionNode != NULL ; actionNode = actionNode->next)
	{
		if (isLog(actionNode))
		{
			processLog(actionNode);
			continue;
		}
		else if (isSend(actionNode))
		{
			processSend(actionNode);
			continue;
		}
		else if (isScript(actionNode))
		{
			processScript(actionNode);
			continue;
		}
		else if (isTimer(actionNode))
		{
			processTimer(actionNode);
			continue;
		}
		else if (isRaise(actionNode))
		{
			processRaise(actionNode);
			continue;
		}
		else if (isSleep(actionNode))
		{
			processSleep(actionNode);
			continue;
		}
		else if(actionNode->type == XML_ELEMENT_NODE)
		{
			LOG4CPLUS_ERROR(log, m_strSessionID << "," << actionNode->name <<"  process not implement." );
		}
	}
	return true ;
}

bool fsm::StateMachineimp::processEntry(const xmlNodePtr &node)const
{
	if (!node) return true;

	for ( xmlNodePtr  actionNode = node->children; actionNode != NULL; actionNode = actionNode->next)
	{
		if (isLog(actionNode))
		{
			processLog(actionNode);
			continue;
		}
		else if (isSend(actionNode))
		{
			processSend(actionNode);
			continue;
		}
		else if (isScript(actionNode))
		{
			processScript(actionNode);
			continue;
		}
		else if (isTimer(actionNode))
		{
			processTimer(actionNode);
			continue;
		}
		else if (isRaise(actionNode))
		{
			processRaise(actionNode);
			continue;
		}
		else if (isSleep(actionNode))
		{
			processSleep(actionNode);
			continue;
		}
		else if(actionNode->type == XML_ELEMENT_NODE)
		{
			LOG4CPLUS_ERROR(log, m_strSessionID << ", in the onentry element [" << actionNode->name << "] process not implement,line:" << actionNode->line );
		}
	}
	return true;
}

xmlNodePtr fsm::StateMachineimp::getState(const string& stateId) const
{

	string strExpression="//state[@id='"+stateId +"']"; 
	helper::xml::CXPathObjectPtr xpathObj(NULL); 

	try{
		
		/* Evaluate xpath expression */
		xpathObj = xmlXPathEvalExpression(BAD_CAST(strExpression.c_str()), xpathCtx._xPathCtxPtr);
		if(xpathObj._xPathObjPtr == NULL) {
			LOG4CPLUS_ERROR(log, m_strSessionID <<",Error: unable to evaluate xpath expression:" << strExpression);
			throw std::logic_error(string("Error: unable to evaluate xpath expression: " +strExpression).c_str());
		}
		
		/* Print results */
		xmlNodePtr xNode =NULL ;
		if (xpathObj._xPathObjPtr->nodesetval) xNode = xpathObj._xPathObjPtr->nodesetval->nodeNr>0? xpathObj._xPathObjPtr->nodesetval->nodeTab[0] : NULL;
		return xNode;
	}
	catch(...)
	{
		throw ;
	}
	/* Cleanup */
}
bool fsm::StateMachineimp::addSendImplement(SendInterface * evtDsp)
{
	if (m_mapSendObject.count(evtDsp->getTarget())) 
		return false;
	m_mapSendObject[evtDsp->getTarget()] = evtDsp;
	LOG4CPLUS_DEBUG(log, m_strSessionID << ",addSendImplement:" << evtDsp->getTarget());
	return true;
}
const std::string & fsm::StateMachineimp::getName() const {
	return m_strName;
}
const std::string & fsm::StateMachineimp::getSessionId()const {
	return m_strSessionID;
}



fsm::Context  *  fsm::StateMachineimp::getRootContext() const{
	if (m_Context == nullptr) {
		Evaluator * evaluator = reinterpret_cast<Evaluator *>(tls_get_value(g_tls_storage_key));

		if (evaluator == nullptr) {
			evaluator = new fsm::env::JSEvaluator();
			tls_set_value(g_tls_storage_key, evaluator);
		}

		const_cast<StateMachineimp*>(this)->m_Context = evaluator->newContext(m_strSessionID, nullptr);
	}
	return m_Context;
}

void fsm::StateMachineimp::deleteContext(Context * ctx)
{
	Evaluator * evaluator = reinterpret_cast<Evaluator *>(tls_get_value(g_tls_storage_key));

	if (evaluator != nullptr) {

		evaluator->deleteContext(m_Context);
		m_Context = nullptr;

		if (!evaluator->hasContext()) {
			delete evaluator;
			tls_set_value(g_tls_storage_key, nullptr);
		}
	}
}

void fsm::StateMachineimp::setLog(log4cplus::Logger log)
{
	this->log = log;
}

bool fsm::StateMachineimp::start(bool block)
{
	m_Block = block;

	if (Init()){
		fsm::Context *ctx = getRootContext();

		if (ctx)
		{
			/*创建JsContext私有数据指针*/
			//ctx->SetContextPrivate(this);
			for (auto & it : m_globalVars){
				ctx->setVar(it.first, it.second);
			}
			m_globalVars.clear();

			ctx->setVar("_name", getName());
			ctx->setVar("_sessionid", getSessionId());

		}
		if (m_rootNode)
		{
			for (xmlNodePtr childNode = m_rootNode->children; childNode != NULL; childNode = childNode->next)
			{
				if (childNode->type == XML_ELEMENT_NODE && xmlStrEqual(childNode->name, BAD_CAST("datamodel")))
				{
					model::Datamodel datamodel(childNode, m_strSessionID, m_strStateFile);
					datamodel.execute(this->getRootContext());

				}
				else if (childNode->type == XML_ELEMENT_NODE && xmlStrEqual(childNode->name, BAD_CAST("scriptmodel")))
				{
					model::Scriptmodel scriptmodel(childNode, m_strSessionID, m_strStateFile);
					scriptmodel.execute(this->getRootContext());
				}
			}
		}
		m_Running = true;
		LOG4CPLUS_DEBUG(log, m_strSessionID << ", start");
		enterStates(this->m_initState);
		return true;
	}
	else{
		throw std::runtime_error("Error: init statemachine.");
	}
	return false;
}

void fsm::StateMachineimp::stop()
{
	LOG4CPLUS_DEBUG(log, m_strSessionID << ", stop");
	m_Running = false;
	TriggerEvent trigEvent;
	pushEvent(trigEvent);

	if (!m_Block) {
		this->deleteContext(m_Context);
	}
}
void fsm::StateMachineimp::setSessionID(const std::string &strSessionid)
{
	m_strSessionID = strSessionid;
	LOG4CPLUS_DEBUG(log, m_strSessionID << ", set this stateMachine sessionid=" << m_strSessionID);
}

void fsm::StateMachineimp::mainEventLoop()
{

	//外部事件队列循环

	do {
		try {
			//如果外部事件队列不为空，执行一个外部事件
			TriggerEvent trigEvent;
			if (m_externalQueue.Get(trigEvent, 1000)) {

				for_each(m_globalVars.begin(), m_globalVars.end(), [&](auto & it) {this->getRootContext()->setVar(it.first, it.second); });
				m_globalVars.clear();
				if (!trigEvent.getEventName().empty()) {
					processEvent(trigEvent);
				}
			}

			//内部事件队列循环
			if (m_Running && !m_internalQueue.empty())
			{
				LOG4CPLUS_TRACE(log, m_strSessionID << ", Internal Event Queue size:" << m_internalQueue.size());
				std::queue<TriggerEvent> excQueue;
				// 拷贝现在内部事件队列中的事件到执行队列中
				excQueue.swap(m_internalQueue);

				//执行当前执行队列
				while (m_Running && !excQueue.empty()) {
					TriggerEvent inEvent = excQueue.front();
					excQueue.pop();
					processEvent(inEvent);
				}
			}
		}
		catch (std::exception & e)
		{
			LOG4CPLUS_ERROR(log, e.what());
		}

	} while (m_Running && m_Block);

	if (m_Block){
		this->deleteContext(m_Context);
	}
}

bool fsm::StateMachineimp::isInFinalState()
{
	return m_currentStateNode == m_finalState;
}

bool fsm::StateMachineimp::processEvent(const TriggerEvent &event)
{
	using namespace helper::xml;
	LOG4CPLUS_TRACE(log, m_strSessionID << ",processEvent:" << event.getEventName());
	if (getRootContext()){
		getRootContext()->deleteVar("_event");
		m_currentEvt = event;

		getRootContext()->setVar("_event._name", m_currentEvt.getEventName());
		getRootContext()->setVar("_event._type", m_currentEvt.getMsgType());
		for(auto & it : m_currentEvt.getVars())
		{
			getRootContext()->setVar("_event." + it.first, it.second);
		}
	}else
	{
		m_currentEvt = event;
	}
	bool foundEvent = false;
	xmlNodePtr filterState = m_currentStateNode;
	//std::string strEventData = trigEvent.getData();
	//scInstance->getRootContext()->set("_event.data",strEventData);
	while (filterState != NULL && filterState != m_rootNode && foundEvent == false) 
	{
		LOG4CPLUS_TRACE(log, m_strSessionID << ",matching event stateid=" << getXmlNodeAttributesValue(filterState, "id"));
		for (xmlNodePtr eventNode = filterState->children; eventNode !=NULL;
			eventNode = eventNode->next)
		{

			if (isEvent(eventNode))
			{
				model::Event event(eventNode,m_strSessionID,m_strStateFile);

				if (event.isEnabledEvent(m_currentEvt.getEventName()) 
					&& event.isEnabledCondition(this->getRootContext()))
				{
					foundEvent = true;
					processEvent(eventNode);
					break;
				}
			}
		}
		if (!foundEvent)
		{
			filterState = getParentState(filterState);
		}
	} 

	if (!foundEvent)
	{
		LOG4CPLUS_WARN(log, m_strSessionID << ",stateid=" << getXmlNodeAttributesValue(m_currentStateNode,"id") << " not match the event:"  << m_currentEvt.ToString());
	}
	return foundEvent;
}

bool fsm::StateMachineimp::setVar(const std::string &name, const Json::Value & value)
{  
	this->m_globalVars.push_back(std::make_pair(name,value));
	return true;
}

