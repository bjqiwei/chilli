#include "FSM.h"
#include <string>
#include <ObjBase.h>
#include <cstdio>
#include "scxml/model/Script.h"
#include "scxml/model/Event.h"
#include "scxml/model/Script.h"
#include "scxml/model/Send.h"
#include "scxml/model/Timer.h"
#include "scxml/model/Transition.h"
#include "scxml/model/Functionmodel.h"
#include "scxml/model/Datamodel.h"
#include "scxml/model/Log.h"
#include "scxml/model/Raise.h"
#include <stdexcept>
#include <log4cplus/loggingmacros.h>
#include "common/stringHelper.h"


using namespace std;

fsm::StateMachine::StateMachine(const string  &xml, xmlType xtype):m_xmlDocPtr(NULL),m_initState(NULL)
	,m_currentStateNode(NULL),m_rootNode(NULL),xpathCtx(NULL),m_scInstance(NULL)
	,m_xmlType(xtype),m_running(true)
{

	log = log4cplus::Logger::getInstance("fsm.StateMachine");
	if (m_xmlType == File)
	{
		m_strStateFile = xml;
	}else{
		m_strStateContent = xml;
	}
	
	LOG4CPLUS_DEBUG(log, m_strSessionID << ",creat a fsm object." );

}

fsm::StateMachine::~StateMachine()
 { 
	 //if (_ctxt) xmlClearParserCtxt(_ctxt);
	 //_ctxt = NULL;
	 this->reset();
	 LOG4CPLUS_DEBUG(log, m_strSessionID << ",destruction a smscxml object.");

 }


void fsm::StateMachine::reset()
{ 
	//if (_ctxt) xmlClearParserCtxt(_ctxt);
	//_ctxt = NULL;
	std::map<std::string,Json::Value>::const_iterator it = m_globalVars.begin();
	while (it != m_globalVars.end())
	{
		if (getRootContext())
		{
			getRootContext()->deleteVar("_"+it->first);
		}
		m_globalVars.erase(it++);
	}
	if(m_scInstance)m_scInstance->removeContext(m_rootNode);
	LOG4CPLUS_DEBUG(log, m_strSessionID << ",reset a smscxml object.");

}


bool fsm::StateMachine::Init(void)
{
	using namespace helper::xml;
	parse();
	if (m_xmlDocPtr._xDocPtr ) {

		if (m_rootNode && m_scInstance) m_scInstance->removeContext(m_rootNode);

		xmlNodePtr rootNode =  xmlDocGetRootElement(m_xmlDocPtr._xDocPtr);
		 if (rootNode !=NULL && xmlStrEqual(rootNode->name,BAD_CAST("fsm")))
		 {
			 m_rootNode = rootNode;
			 LOG4CPLUS_TRACE(log,"set rootNode=" << m_rootNode);

			 m_strName =  getXmlNodeAttributesValue(m_rootNode,"name");
			  LOG4CPLUS_TRACE(log,"set name=" <<  m_strName);
			// normalize(_rootNode);
			 m_initState = getXmlChildNode(m_rootNode,"state");
			 LOG4CPLUS_TRACE(log,"set initState=" <<  getXmlNodeAttributesValue(m_initState,"id"));
			 
		 }
		 else
		 {

			 LOG4CPLUS_ERROR(log, m_strSessionID << " ,Cannot find root FSM element." );
			 //throw std::logic_error( "Cannot find FSM element.");
			 return false;
		 }
	}
	else {

		LOG4CPLUS_ERROR(log,  m_strName << ":" << m_strSessionID <<" ,Interpreter has no DOM at all!");
		//throw std::logic_error("Interpreter has no DOM at all!");
		return false;
	}
	return true;
}

bool fsm::StateMachine::Init(const string &xml, xmlType xtype)
{
	m_xmlType = xtype;
	if (m_xmlType == File)
	{
		m_strStateFile = xml;
	}else{
		m_strStateContent = xml;
	}

	return Init();
}

void fsm::StateMachine::normalize(const xmlNodePtr &smscxml)
{
	//检查文件内容，初始化状态机
	LOG4CPLUS_WARN(log, "normalize fuction is not implement." );
	return ;
}


//const xmlNodePtr fsm::StateMachine::getCurrentState(void) const
//{
//	return m_currentStateNode;
//}

const std::string fsm::StateMachine::getCurrentStateID(void) const
{
	return helper::xml::getXmlNodeAttributesValue(m_currentStateNode,"id");
}

inline bool fsm::StateMachine::isState(const xmlNodePtr &xNode)  
{
	return xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("state")) ; 
}

inline bool fsm::StateMachine::isTransition(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("transition")); 
}

inline bool fsm::StateMachine::isLog(const xmlNodePtr &xNode) 
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("log")); 
}

inline bool fsm::StateMachine::isEvent(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("event")); 
}

inline bool fsm::StateMachine::isExit(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("onexit")); 
}

inline bool fsm::StateMachine::isEntry(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("onentry")); 
}

inline bool fsm::StateMachine::isSend(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("send")); 
}

inline bool fsm::StateMachine::isScript(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("script")); 
}

inline bool fsm::StateMachine::isTimer(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("timer")); 
}

inline bool fsm::StateMachine::isRaise(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("raise")); 
}

void fsm::StateMachine::pushEvent( TriggerEvent & trigEvent)
{
	m_externalQueue.push(trigEvent);
}
fsm::StateMachine::StateMachine(const StateMachine &other):m_strStateFile(other.m_strStateFile),m_xmlDocPtr(NULL),
	m_initState(NULL),m_currentStateNode(NULL),m_rootNode(NULL),log(other.log),xpathCtx(NULL)
	,m_mapSendObject(other.m_mapSendObject),m_scInstance(other.m_scInstance)
	,m_xmlType(other.m_xmlType),m_strStateContent(other.m_strStateContent)
	,m_running(true)
	
{
	LOG4CPLUS_TRACE(log, m_strSessionID << ",creat a fsm object from other statemachine:" << other.getSessionId() );
	this->m_xmlDocPtr = xmlCopyDoc(other.m_xmlDocPtr._xDocPtr,1);
	Init();
	return ;
}

fsm::StateMachine & fsm::StateMachine::operator=(const fsm::StateMachine & other)
{
	if (&other == this)
	{
		return * this;
	}

	log = other.log;
	this->m_strStateFile = other.m_strStateFile;
	this->m_initState = NULL;
	this->m_currentStateNode = NULL;
	this->m_xmlDocPtr = xmlCopyDoc(other.m_xmlDocPtr._xDocPtr,1);
	this->m_rootNode =NULL;
	this->m_scInstance =other.m_scInstance;
	this->m_xmlType = other.m_xmlType;
	this->m_strStateContent = other.m_strStateContent;
	this->m_mapSendObject = other.m_mapSendObject;
	this->m_running = true;
	this->Init();
	return *this;
}

//将文件解析成xml文档。
void fsm::StateMachine::parse()
{

	if (NULL != m_xmlDocPtr._xDocPtr) {
		LOG4CPLUS_WARN(log,"xmldocument is not empty , there not Parse file:" << this->m_strStateFile);
		return;
	}

	try{
		/* parse the file */
		//_docPtr = xmlCtxtReadFile(_ctxt, _strStateFile.c_str(), NULL, XML_PARSE_NOERROR);
		if (m_xmlType == File)
		{
			LOG4CPLUS_DEBUG(log,"Parse xml file:" << m_strStateFile);
			m_xmlDocPtr = xmlParseFile(m_strStateFile.c_str());
		}else
		{
			LOG4CPLUS_DEBUG(log,"Parse xml Content:" << m_strStateContent);
			m_xmlDocPtr = xmlParseMemory(m_strStateContent.c_str(), m_strStateContent.length());
		}
	}
	catch(std::exception &e){ 
		LOG4CPLUS_ERROR(log, e.what());
	}

	if (NULL == m_xmlDocPtr._xDocPtr) 
	{  
		LOG4CPLUS_ERROR(log, m_strSessionID<< ":" << m_strStateFile << ",Document not parsed successfully."); 
		//throw std::logic_error( "Document not parsed successfully."); 
	} 
}

bool fsm::StateMachine::processEvent(const xmlNodePtr &eventNode)const
{
	if (!eventNode){
		return false ;
	}
	bool doneSomething = false;
	for (xmlNodePtr actionNode = eventNode->children; actionNode != NULL; actionNode = actionNode->next)
	{

		if (isTransition(actionNode))
		{
			processTransition(actionNode)? doneSomething = true:NULL;
			break;//transition 元素下的元素将不再执行
		}
		else if (isLog(actionNode))
		{
			processLog(actionNode)? doneSomething = true:NULL;
			continue;
		}

		else if (isSend(actionNode))
		{
			processSend(actionNode)? doneSomething = true:NULL;
			continue;
		}
		else if (isScript(actionNode))
		{
			processScript(actionNode)? doneSomething = true:NULL;
			continue;
		}
		else if (isTimer(actionNode))
		{
			processTimer(actionNode)? doneSomething = true:NULL;
			continue;
		}
		else if (isRaise(actionNode))
		{
			processRaise(actionNode)? doneSomething = true:NULL;
			continue;
		}
		else if(actionNode->type == XML_ELEMENT_NODE)
		{
			LOG4CPLUS_ERROR(log, m_strSessionID.c_str() << ": " << actionNode->name << " process not implement.");
		}
	}
	
	if (!doneSomething)
	{
		LOG4CPLUS_ERROR(log, m_strSessionID << ", this event node done nothing,line:" << eventNode->line);
	}
	return doneSomething;
}

bool fsm::StateMachine::processTransition(const xmlNodePtr &actionNode)const
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
		LOG4CPLUS_ERROR(log, m_strSessionID << ","<<m_strStateFile<<" file,not find the target:" << transition.getTarget() << " state");
	}
	return true;
}

bool fsm::StateMachine::processSend(const xmlNodePtr &Node)const
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


bool fsm::StateMachine::processTimer(const xmlNodePtr &Node)const
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
	//LOG4CPLUS_DEBUG(log,m_strSessionID << ",set a timer,id=" << timer.getId() << ", interval=" << timer.getInterval());
	if(m_scInstance)m_scInstance->SetTimer(timer.getInterval(), this->m_strSessionID + ":" + timer.getId());

	return true;
}

bool fsm::StateMachine::processLog(const xmlNodePtr &Node)const
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

bool fsm::StateMachine::processScript(const xmlNodePtr &node) const
{
	if (!node) return false;
	model::Script script(node,m_strSessionID,m_strStateFile);

	if(script.isEnabledCondition(this->getRootContext())){
		script.execute(this->getRootContext());
		return true;
	}
	
	return false;
}

bool fsm::StateMachine::processRaise(const xmlNodePtr &node)const
{
	if (!node) return false;
	model::Raise raise(node,m_strSessionID,m_strStateFile);

	if(raise.isEnabledCondition(this->getRootContext())){
		TriggerEvent _raiseEvent;
		_raiseEvent.setEventName(raise.getEvent());
		_raiseEvent.setParam(this);
		LOG4CPLUS_TRACE(log,"Raise a event:" << _raiseEvent.ToString());
		m_internalQueue.push(_raiseEvent);
		return true;
	}

	return false;
}

const xmlNodePtr fsm::StateMachine::getParentState( const xmlNodePtr &currentState)const
{
	xmlNodePtr curState = currentState;
	do
	{
		curState = curState->parent;
		if(curState && isState(curState)) return curState;
	}while (curState != NULL && curState != m_rootNode);

	return NULL;
}

//void fsm::StateMachine::setName(const string &strName)
//{
//	m_strName = strName;
//	LOG4CPLUS_DEBUG(log,"set this stateMachine name=" << m_strName);
//}


void fsm::StateMachine::exitStates() const
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

void fsm::StateMachine::enterStates(const xmlNodePtr &stateNode) const
{
	if(isState(stateNode))
	{
		m_currentStateNode = stateNode;
		LOG4CPLUS_DEBUG(log,m_strSessionID << ",enter state:" << getCurrentStateID());
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
		LOG4CPLUS_ERROR(log, m_strSessionID <<  ",Will enter the node is not a status node.");

	}
}



bool fsm::StateMachine::processExit(const xmlNodePtr &exitNode) const
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
		else if(actionNode->type == XML_ELEMENT_NODE)
		{
			LOG4CPLUS_ERROR(log,m_strSessionID << ":" << actionNode->name <<"  process not implement." );
		}
	}
	return true ;
}

bool fsm::StateMachine::processEntry(const xmlNodePtr &node)const
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
		else if(actionNode->type == XML_ELEMENT_NODE)
		{
			LOG4CPLUS_ERROR(log,m_strSessionID << ": in the onentry element [" << actionNode->name << "] process not implement,line:" << actionNode->line );
		}
	}
	return true;
}

xmlNodePtr fsm::StateMachine::getState(const string& stateId) const
{

	string strExpression="//state[@id='"+stateId +"']"; 
	helper::xml::CXPathObjectPtr xpathObj(NULL); 

	try{
		
		/* Evaluate xpath expression */
		xpathObj = xmlXPathEvalExpression(BAD_CAST(strExpression.c_str()), xpathCtx._xPathCtxPtr);
		if(xpathObj._xPathObjPtr == NULL) {
			LOG4CPLUS_ERROR(log,m_strSessionID <<",Error: unable to evaluate xpath expression:" << strExpression);
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
bool fsm::StateMachine::addSendImplement(SendInterface * evtDsp)
{
	if (m_mapSendObject.count(evtDsp->getTarget())) return false;
	m_mapSendObject[evtDsp->getTarget()] = evtDsp;
	return true;
}
const std::string & fsm::StateMachine::getName() const {
	return m_strName;
}
const std::string & fsm::StateMachine::getSessionId()const {
	return m_strSessionID;
}



fsm::Context  *  fsm::StateMachine::getRootContext() const{
	if(m_scInstance)
		return this->m_scInstance->getContext(m_rootNode);
	return NULL;
}

void fsm::StateMachine::setscInstance(SMInstance * scIns)
{
	m_scInstance = scIns;
	LOG4CPLUS_DEBUG(log,"set statemachine scInstance=" << m_scInstance);
}
void fsm::StateMachine::setLog(log4cplus::Logger log)
{
	this->log = log;
}
void fsm::StateMachine::go()
{
	fsm::Context *ctx = getRootContext();

	if (ctx)
	{
		/*创建JsContext私有数据指针*/
		ctx->SetContextPrivate(this);
		ctx->setVar("_name",getName());
		ctx->setVar("_sessionid",getSessionId());
	}
	if (m_rootNode)
	{
		for (xmlNodePtr childNode = m_rootNode->children; childNode != NULL; childNode = childNode->next )
		{
			if(m_scInstance && childNode->type == XML_ELEMENT_NODE && xmlStrEqual(childNode->name,BAD_CAST("datamodel")))
			{
				model::Datamodel datamodel(childNode,m_strSessionID,m_strStateFile);
				datamodel.execute(this->getRootContext());

			}else if (m_scInstance && childNode->type == XML_ELEMENT_NODE && xmlStrEqual(childNode->name,BAD_CAST("functionmodel")))
			{
				model::Functionmodel funmodel(childNode,m_strSessionID,m_strStateFile);
				funmodel.execute(this->getRootContext());	
			}
		}
		/* Create xpath evaluation context */
		if (xpathCtx._xPathCtxPtr == NULL)
		{
			xpathCtx = xmlXPathNewContext(m_xmlDocPtr._xDocPtr);
		}
		
		if(xpathCtx._xPathCtxPtr == NULL) {
			LOG4CPLUS_ERROR(log,m_strSessionID << ": unable to create new XPath context");
			throw std::logic_error("Error: unable to create new XPath context");
		}
	}
	enterStates(this->m_initState);
}

void fsm::StateMachine::setSessionID(const std::string &strSessionid)
{
	m_strSessionID = strSessionid;
	LOG4CPLUS_DEBUG(log,"set this stateMachine sessionid=" << m_strSessionID);
}

void fsm::StateMachine::mainEventLoop()
{
	using namespace helper::xml;
	helper::AutoLock autolock(&this->m_lock);

	//外部事件队列循环
	while(m_running){

		//如果外部事件队列不为空，执行一个外部事件
		TriggerEvent trigEvent;
		if(!m_externalQueue.empty()){
			trigEvent = m_externalQueue.front();
			m_externalQueue.pop();
			processEvent(trigEvent);
		}

		//内部事件队列循环
		LOG4CPLUS_TRACE(log, "Internal Event Queue size:" << m_internalQueue.size());
		if(m_running && !m_internalQueue.empty())
		{
			std::queue<TriggerEvent> excQueue;
			// 拷贝现在内部事件队列中的事件到执行队列中
			while(!m_internalQueue.empty()) 
			{
				excQueue.push(m_internalQueue.front());
				m_internalQueue.pop();
			}
			//执行当前执行队列
			while (m_running && !excQueue.empty()){
				TriggerEvent inEvent = excQueue.front();
				excQueue.pop();
				processEvent(inEvent);
			}
		}

		if(isTerminationEvent(trigEvent)){
			m_running = false;
			break;
		}
		//如果外部队列和内部队列都为空，退出外部事件队列循环
		if (m_externalQueue.empty() && m_internalQueue.empty()){
			break;
		}

	}
	
}

bool fsm::StateMachine::processEvent(const TriggerEvent &event)
{
	using namespace helper::xml;
	if (getRootContext()){
		for(std::map<std::string ,std::string >::const_iterator it = m_currentEvt.getVars().begin();
			it != m_currentEvt.getVars().end();++it)
		{
			getRootContext()->deleteVar("_" + it->first,fsm::eventOjbect);
		}
		m_currentEvt = event;

		getRootContext()->setVar("_name", m_currentEvt.getEventName(), fsm::eventOjbect);
		getRootContext()->setVar("_type", m_currentEvt.getMsgType(),fsm::eventOjbect);
		getRootContext()->setVar("_data", m_currentEvt.getData(), fsm::eventOjbect);
		for(std::map<std::string ,std::string >::const_iterator it = m_currentEvt.getVars().begin();
			it != m_currentEvt.getVars().end();++it)
		{
			getRootContext()->setVar("_" + it->first,it->second, fsm::eventOjbect);
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
		LOG4CPLUS_ERROR(log, m_strSessionID << ",stateid=" << getXmlNodeAttributesValue(m_currentStateNode,"id") << " not match the event:"  << m_currentEvt.ToString());
	}
	return foundEvent;
}

bool fsm::StateMachine::setVar(const std::string &name, const Json::Value & value)
{  
	std::string out2 = value.toStyledString();
	LOG4CPLUS_TRACE(log,"set " << name << "=" << helper::string::trim(out2));
	this->m_globalVars[name] = value;
	if (getRootContext())
	{
		getRootContext()->setVar("_"+name,value);
	}
	return true;
}

Json::Value fsm::StateMachine::getVar(const std::string &name)const
{
	std::map<std::string,Json::Value>::const_iterator it = m_globalVars.find(name);
	if (it != m_globalVars.end())
	{
		return it->second;
	}
	return Json::Value();
}
