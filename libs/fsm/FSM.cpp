#include "FSM.h"
#include <string>
#include <ObjBase.h>
#include <cstdio>
#include "scxml/model/Script.h"
#include "scxml/model/Event.h"
#include "scxml/model/Script.h"
#include "scxml/model/Send.h"
#include "scxml/model/ModelTimer.h"
#include "scxml/model/Transition.h"
#include "scxml/model/Functionmodel.h"
#include "scxml/model/Datamodel.h"
#include "scxml/model/Log.h"
#include <stdexcept>
#include <log4cplus/loggingmacros.h>


using namespace std;

fsm::StateMachine::StateMachine(const string  &xml):m_strStateFile(xml),m_xmlDocPtr(NULL),m_initState(NULL)
	,m_currentStateNode(NULL),m_rootNode(NULL),xpathCtx(NULL),m_scInstance(NULL)
{

	log = log4cplus::Logger::getInstance("fsm.StateMachine");
	LOG4CPLUS_DEBUG(log, m_strSessionID << ",creat a fsm object." );

	return ;
}

fsm::StateMachine::~StateMachine()
 { 
	 //if (_ctxt) xmlClearParserCtxt(_ctxt);
	 //_ctxt = NULL;
	 if(m_scInstance)m_scInstance->removeContext(m_rootNode);
	 LOG4CPLUS_DEBUG(log, m_strSessionID << ",destruction a smscxml object.");

 }


void fsm::StateMachine::reset()
{ 
	//if (_ctxt) xmlClearParserCtxt(_ctxt);
	//_ctxt = NULL;
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
		 if (rootNode !=NULL && xmlStrEqual(rootNode->name,BAD_CAST("scm")))
		 {
			 m_rootNode = rootNode;
			 LOG4CPLUS_TRACE(log,"set rootNode=" << m_rootNode);
			// normalize(_rootNode);
			 m_initState = getXmlChildNode(m_rootNode,"state");
			 LOG4CPLUS_TRACE(log,"set initState=" <<  getXmlNodeAttributesValue(m_initState,"id"));
			 
			// SCXMLHelper::cloneDatamodel(getXmlChildNode(_rootNode,"datamodel"),scInstance->getContext(_rootNode,logger),scInstance->getEvaluator(),logger);
			//SCXMLHelper::cloneFunctionmodel(getXmlChildNode(_rootNode,"functionmodel"),scInstance->getContext(_rootNode,log),scInstance->getEvaluator(),log);
			 
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

bool fsm::StateMachine::Init(const string &xmlFile)
{
	this->m_strStateFile = xmlFile;
	return Init();
}

void fsm::StateMachine::normalize(const xmlNodePtr &smscxml)
{
	//检查文件内容，初始化状态机
	LOG4CPLUS_WARN(log, "normalize fuction is not implement." );
	return ;
}


const xmlNodePtr fsm::StateMachine::getCurrentState(void) const
{
	return m_currentStateNode;
}

const std::string fsm::StateMachine::getCurrentStateID(void) const
{
	return helper::xml::getXmlNodeAttributesValue(m_currentStateNode,"id");
}

inline bool fsm::StateMachine::isState(const xmlNodePtr &xNode) const 
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

void fsm::StateMachine::pushEvent( TriggerEvent & trigEvent)const
{
	using namespace helper::xml;
	//m_lock.Lock();
	m_currentEvt = trigEvent;
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
				if(m_scInstance)
					event.execute(m_scInstance->getContext(m_rootNode));
				else
					event.execute(NULL);
				if (event.isEnabledEvent(m_currentEvt.getEventName()) && event.isEnabledCondition())
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
	//m_lock.Unlock();
}
fsm::StateMachine::StateMachine(const StateMachine &other):m_strStateFile(other.m_strStateFile),m_xmlDocPtr(NULL),
	m_initState(NULL),m_currentStateNode(NULL),m_rootNode(NULL),log(other.log),xpathCtx(NULL)
	,m_scInstance(other.m_scInstance)
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
		if (m_strStateFile.empty())
		{
			LOG4CPLUS_ERROR(log, m_strSessionID << ",stateMachine file is empty."); 
			return;
		}
		LOG4CPLUS_DEBUG(log,"Parse xml file:" << m_strStateFile);
		m_xmlDocPtr = xmlParseFile(m_strStateFile.c_str());
	}
	catch(std::exception &e){ 
		LOG4CPLUS_ERROR(log, e.what());
	}

	if (NULL == m_xmlDocPtr._xDocPtr) 
	{  
		LOG4CPLUS_ERROR(log, m_strStateFile << m_strSessionID << ",Document not parsed successfully."); 
		//throw std::logic_error( "Document not parsed successfully."); 
	} 
}

void fsm::StateMachine::processEvent(const xmlNodePtr &eventNode)const
{
	if (!eventNode){
		return ;
	}
	bool doneSomething = false;
	for (xmlNodePtr actionNode = eventNode->children; actionNode != NULL; actionNode = actionNode->next)
	{

		if (isTransition(actionNode))
		{
			model::Transition transition(actionNode,m_strSessionID,m_strStateFile);
			if(m_scInstance)
				transition.execute(m_scInstance->getContext(m_rootNode));
			else
				transition.execute(NULL);
			if (transition.isEnabledCondition())
			{
				doneSomething = true;
				processTransition(transition);
				break;
			}
		}
		else if (isLog(actionNode))
		{
			model::Log log(actionNode,m_strSessionID,m_strStateFile);
			if(m_scInstance)
				log.execute(m_scInstance->getContext(m_rootNode));
			else
				log.execute(NULL);
			doneSomething = true;
			continue;
		}

		else if (isSend(actionNode))
		{
			doneSomething = true;
			processSend(actionNode);
			continue;
		}
		else if (isScript(actionNode))
		{
			doneSomething = true;
			model::Script script(actionNode,m_strSessionID,m_strStateFile);
			if(m_scInstance)
				script.execute(m_scInstance->getContext(m_rootNode));
			
			continue;
		}
		else if (isTimer(actionNode))
		{
			doneSomething = true;
			processTimer(actionNode);
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
}

void fsm::StateMachine::processTransition(model::Transition & trasition)const
{
	
	if (xmlNodePtr stateNode = getState(trasition.getTarget()))
	{
		exitStates();
		enterStates(stateNode);
		return ;
	}
	else
	{
		LOG4CPLUS_ERROR(log, m_strSessionID << ","<<m_strStateFile<<" file,not find the target:" << trasition.getTarget() << " state");
	}
}

void fsm::StateMachine::processSend(const xmlNodePtr &Node)const
{
	using namespace helper::xml;
	if (!Node) return;
	model::Send send(Node,m_strSessionID,m_strStateFile);

	if(m_scInstance)
		send.execute(m_scInstance->getContext(m_rootNode));
	else
		send.execute(NULL);

	std::map<std::string , EventDispatcher *>::const_iterator it = m_mapSendObject.find(send.getTarget());
	if (it != m_mapSendObject.end()) {
		it->second->fireSend(send.getContent(),this->m_currentEvt.getParam());
	}
	else {

		LOG4CPLUS_ERROR(log,m_strSessionID << " not find the send target:" << send.getTarget());
	}
	return;
}


void fsm::StateMachine::processTimer(const xmlNodePtr &Node)const
{
	if (!Node) return;
	model::Timer timer(Node,m_strSessionID,m_strStateFile);

	if(m_scInstance)
		timer.execute(m_scInstance->getContext(m_rootNode));
	else
		timer.execute(NULL);

	//LOG4CPLUS_DEBUG(logger,_strName << ":" << _strSessionID << "execute a script:" << script.getContent());
	//LOG4CPLUS_DEBUG(log,m_strSessionID << ",set a timer,id=" << timer.getId() << ", interval=" << timer.getInterval());
	if(m_scInstance)m_scInstance->SetTimer(timer.getInterval(), this->m_strSessionID + ":" + timer.getId());

	return;
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

void fsm::StateMachine::setName(const string &strName)
{
	m_strName = strName;
	LOG4CPLUS_DEBUG(log,"set this stateMachine name=" << m_strName);
}


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
				if(!processEntry(entryNode)) break;
			}
		}
	}
	else
	{
		LOG4CPLUS_ERROR(log, m_strSessionID <<  ",Will enter the node is not a status node.");

	}
}



void fsm::StateMachine::processExit(const xmlNodePtr &exitNode) const
{
	if (!exitNode) return ;

	for ( xmlNodePtr  actionNode = exitNode->children; actionNode != NULL ; actionNode = actionNode->next)
	{
		if (isLog(actionNode))
		{
			model::Log log(actionNode,m_strSessionID,m_strStateFile);
			if(m_scInstance)
				log.execute(m_scInstance->getContext(m_rootNode));
			else
				log.execute(NULL);
			continue;
		}
		else if (isSend(actionNode))
		{
			processSend(actionNode);
			continue;
		}
		else if (isScript(actionNode))
		{
			model::Script script(actionNode,m_strSessionID,m_strStateFile);
			if(m_scInstance)script.execute(m_scInstance->getContext(m_rootNode));
			continue;
		}
		else if (isTimer(actionNode))
		{
			processTimer(actionNode);
			continue;
		}
		else if(actionNode->type == XML_ELEMENT_NODE)
		{
			LOG4CPLUS_ERROR(log,m_strSessionID << ":" << actionNode->name <<"  process not implement." );
		}
	}
	return ;
}

bool fsm::StateMachine::processEntry(const xmlNodePtr &node)const
{
	if (!node) return true;

	for ( xmlNodePtr  actionNode = node->children; actionNode != NULL; actionNode = actionNode->next)
	{
		if (isLog(actionNode))
		{
			model::Log log(actionNode,m_strSessionID,m_strStateFile);
			if(m_scInstance)
				log.execute(m_scInstance->getContext(m_rootNode));
			else
				log.execute(NULL);
			continue;
		}
		else if (isSend(actionNode))
		{
			processSend(actionNode);
			continue;
		}
		else if (isScript(actionNode))
		{
			model::Script script(actionNode,m_strSessionID,m_strStateFile);
			if(m_scInstance)script.execute(m_scInstance->getContext(m_rootNode));
			continue;
		}
		else if (isTransition(actionNode))
		{
			model::Transition transition(actionNode,m_strSessionID,m_strStateFile);
			if(m_scInstance)
				transition.execute(m_scInstance->getContext(m_rootNode));
			else
				transition.execute(NULL);
			if (transition.isEnabledCondition())
			{
				processTransition(transition);
				return false;
			}
		}
		else if (isTimer(actionNode))
		{
			processTimer(actionNode);
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

	return NULL;
}
bool fsm::StateMachine::addEventDispatcher(EventDispatcher * evtDsp)
{
	if (m_mapSendObject.count(evtDsp->getTarget())) return false;
	m_mapSendObject[evtDsp->getTarget()] = evtDsp;
	return true;
}
const std::string & fsm::StateMachine::getName() {
	return m_strName;
}
const std::string & fsm::StateMachine::getSessionId()const {
	return m_strSessionID;
}



fsm::Context  *  fsm::StateMachine::getRootContext() {
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
	/*创建JsContext私有数据指针*/
	if(ctx){
		ctx->SetContextPrivate(this);
	}

	if (m_rootNode)
	{
		for (xmlNodePtr childNode = m_rootNode->children; childNode != NULL; childNode = childNode->next )
		{
			if(m_scInstance && childNode->type == XML_ELEMENT_NODE && xmlStrEqual(childNode->name,BAD_CAST("datamodel")))
			{
				model::Datamodel datamodel(childNode,m_strSessionID,m_strStateFile);
				datamodel.execute(m_scInstance->getContext(m_rootNode));

			}else if (m_scInstance && childNode->type == XML_ELEMENT_NODE && xmlStrEqual(childNode->name,BAD_CAST("functionmodel")))
			{
				model::Functionmodel funmodel(childNode,m_strSessionID,m_strStateFile);
				funmodel.execute(m_scInstance->getContext(m_rootNode));
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
