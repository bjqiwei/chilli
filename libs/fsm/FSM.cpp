#include <FSM.h>
#include <string>
#include <ObjBase.h>
#include <cstdio>
#include <scxml/model/Script.h>
#include <scxml/model/Event.h>
#include <scxml/model/Script.h>
#include <scxml/model/Send.h>
#include <scxml/model/Timer.h>
#include <scxml/model/Transition.h>

#ifdef USE_LOG4CPLUS
using namespace log4cplus;
#endif
using namespace std;

fsm::StateMachine::StateMachine(const string  xml):_docPtr(NULL),_initState(NULL)
	,_currentState(NULL),_rootNode(NULL),scInstance(NULL)
{
#ifdef USE_LOG4CPLUS
	log =log4cplus::Logger::getInstance("Interpreter.fsm");	
#endif
	InitializeCriticalSection(&csection);
	this->_strStateFile = xml;
#ifdef USE_LOG4CPLUS
	LOG4CPLUS_DEBUG(log, _strSessionID << ",creat a fsm object.");
#endif
	return ;
}

fsm::StateMachine::~StateMachine()
 { 
	 //if (_ctxt) xmlClearParserCtxt(_ctxt);
	 //_ctxt = NULL;
	 DeleteCriticalSection(&csection);
#ifdef USE_LOG4CPLUS
	 LOG4CPLUS_DEBUG(log, _strSessionID << ",destruction a smscxml object.");
#endif
 }


void fsm::StateMachine::Init(void)
{
	using namespace xmlHelper;
	parse();
	if (_docPtr._xDocPtr ) {

		if (_rootNode) scInstance->removeContext(_rootNode);

		xmlNodePtr rootNode =  xmlDocGetRootElement(_docPtr._xDocPtr);
		 if (rootNode !=NULL && xmlStrEqual(rootNode->name,BAD_CAST("fsm")))
		 {
			 _rootNode = rootNode;
			 normalize(_rootNode);
			 _initState = getXmlChildNode(_rootNode,"state");
			 model::Datamodel datamodel(getXmlChildNode(_rootNode,"datamodel"));
			 if (scInstance){
				 datamodel.execute(scInstance->getEvaluator(),scInstance->getContext(_rootNode,log));
			 }
			 
			// SCXMLHelper::cloneDatamodel(getXmlChildNode(_rootNode,"datamodel"),scInstance->getContext(_rootNode,logger),scInstance->getEvaluator(),logger);
			//SCXMLHelper::cloneFunctionmodel(getXmlChildNode(_rootNode,"functionmodel"),scInstance->getContext(_rootNode,log),scInstance->getEvaluator(),log);
			 
		 }
		 else
		 {
#ifdef USE_LOG4CPLUS
			 LOG4CPLUS_ERROR(log,_strSessionID << " ,Cannot find root FSM element.");
#endif
			 throw exception( "Cannot find FSM element.");
		 }
	}
	else {
#ifdef USE_LOG4CPLUS
		LOG4CPLUS_ERROR(log, _strName << ":" << _strSessionID << " ,Interpreter has no DOM at all!");
#endif
		throw exception("Interpreter has no DOM at all!");
	}
	return ;
}

void fsm::StateMachine::Init(const string xmlFile)
{
	this->_strStateFile = xmlFile;
	return Init();
}

void fsm::StateMachine::normalize(const xmlNodePtr smscxml)
{
	//检查文件内容，初始化状态机
#ifdef USE_LOG4CPLUS
	LOG4CPLUS_WARN(log, _strSessionID << ",normalize fuction is not implement.");
#endif
	return ;
}


const xmlNodePtr fsm::StateMachine::getCurrentState(void) const
{
	return _currentState;
}

const std::string fsm::StateMachine::getCurrentStateID(void) const
{
	return xmlHelper::getXmlNodeAttributesValue(_currentState,"id");
}

inline bool fsm::StateMachine::isState(const xmlNodePtr xNode) const 
{
	return xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("state")) ; 
}

inline bool fsm::StateMachine::isTransition(const xmlNodePtr xNode) 
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("transition")); 
}

inline bool fsm::StateMachine::isLog(const xmlNodePtr xNode) 
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("log")); 
}

inline bool fsm::StateMachine::isEvent(const xmlNodePtr xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("event")); 
}

inline bool fsm::StateMachine::isExit(const xmlNodePtr xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("onexit")); 
}

inline bool fsm::StateMachine::isEntry(const xmlNodePtr xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("onentry")); 
}

inline bool fsm::StateMachine::isSend(const xmlNodePtr xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("send")); 
}

inline bool fsm::StateMachine::isScript(const xmlNodePtr xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("script")); 
}

inline bool fsm::StateMachine::isTimer(const xmlNodePtr xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("timer")); 
}

void fsm::StateMachine::pushEvent( TriggerEvent & trigEvent)const
{
	using namespace xmlHelper;
	EnterCriticalSection(&csection);
	bool foundEvent = false;
	xmlNodePtr filterState = _currentState;
	//std::string strEventData = trigEvent.getData();
	//scInstance->getRootContext()->set("_event.data",strEventData);
	do 
	{
	
		for (xmlNodePtr eventNode = filterState->children; eventNode !=NULL;
			eventNode = eventNode->next)
		{
			
			if (isEvent(eventNode))
			{
				model::Event event(eventNode);
				if (event.isEnabledEvent(trigEvent.getName()) && event.isEnabledCondition())
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
	} while (filterState != NULL && filterState != _rootNode && foundEvent == false);

	if (!foundEvent)
	{
#ifdef USE_LOG4CPLUS
		LOG4CPLUS_WARN(log,_strSessionID << ",stateid="<< getXmlNodeAttributesValue(_currentState,"id")<<" not match the event:" << trigEvent.ToString());
#endif
	}
	LeaveCriticalSection(&csection);
}
fsm::StateMachine::StateMachine(const StateMachine &other):_strStateFile(other._strStateFile),
	_initState(NULL),_currentState(NULL)
	,_rootNode(NULL),_docPtr(NULL),scInstance(other.scInstance)
{
#ifdef USE_LOG4CPLUS
	log = other.log;
#endif
	InitializeCriticalSection(&csection);
	this->_docPtr = xmlCopyDoc(other._docPtr._xDocPtr,1);
	Init();
	return ;
}

fsm::StateMachine & fsm::StateMachine::operator=(const fsm::StateMachine & other)
{
	using namespace xmlHelper;

	if (&other == this)
	{
		return * this;
	}

#ifdef USE_LOG4CPLUS
	log = other.log;
#endif
	InitializeCriticalSection(&csection);
	this->_strStateFile = other._strStateFile;
	this->_initState = NULL;
	this->_currentState = NULL;
	this->_docPtr = xmlCopyDoc(other._docPtr._xDocPtr,1);
	this->_rootNode =NULL;
	this->scInstance =other.scInstance;
	this->Init();
	return *this;
}

//将文件解析成xml文档。
void fsm::StateMachine::parse()
{

	if (NULL != _docPtr._xDocPtr) return;

	try{
		/* parse the file */
		//_docPtr = xmlCtxtReadFile(_ctxt, _strStateFile.c_str(), NULL, XML_PARSE_NOERROR);
		if (_strStateFile.empty())
		{
			LOG4CPLUS_WARN(log, _strSessionID << ",stateMachine file is empty."); 
			return;
		}

		_docPtr = xmlParseFile(_strStateFile.c_str());
	}
	catch (...){ throw;}

	if (NULL == _docPtr._xDocPtr) 
	{  
#ifdef USE_LOG4CPLUS
		LOG4CPLUS_ERROR(log, _strSessionID << ",Document not parsed successfully."); 
#endif
		throw exception( string(_strStateFile + ",Document not parsed successfully.").c_str()); 
	} 
}

void fsm::StateMachine::processEvent(const xmlNodePtr eventNode)const
{
	if (!eventNode){
		return ;
	}
	bool doneSomething = false;
	if (eventNode)
	{
		for (xmlNodePtr actionNode = eventNode->children; actionNode != NULL; actionNode = actionNode->next)
		{
		
			if (isTransition(actionNode))
			{
				model::Transition transition(actionNode);
				transition.execute(scInstance->getEvaluator(),scInstance->getContext(_rootNode,log));
				if (transition.isEnabledCondition())
				{
					doneSomething = true;
					processTransition(transition);
					break;
				}
			}
			else if (isLog(actionNode))
			{
				model::Log log(actionNode);
				log.execute(scInstance->getEvaluator(),scInstance->getContext(_rootNode,this->log));
				doneSomething = true;
				processLog(log);
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
				model::Script script(actionNode);
				script.execute(scInstance->getEvaluator(),scInstance->getContext(_rootNode,log));
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
#ifdef USE_LOG4CPLUS
				LOG4CPLUS_WARN(log, _strSessionID << ",  " << actionNode->name << " process not implement.");
#endif
			}
		}
	}
	if (!doneSomething)
	{
#ifdef USE_LOG4CPLUS
		LOG4CPLUS_WARN(log, _strSessionID << ", this event node done nothing");
#endif
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
#ifdef USE_LOG4CPLUS
		LOG4CPLUS_ERROR(log, _strSessionID << ", not find the target:" << trasition.getTarget() << " state");
#endif
	}
}

void fsm::StateMachine::processSend(const xmlNodePtr Node)const
{
	using namespace xmlHelper;
	if (!Node) return;
	model::Send send(Node);

	send.execute(scInstance->getEvaluator(),scInstance->getContext(_rootNode,log));

	CXmlDocmentHelper m_xmlDoc;
	
	m_xmlDoc.setRootNode(send.getType());
	m_xmlDoc.newRootProp(send.getType(),send.getEvent());
	m_xmlDoc.newRootProp("id",send.getId());
	m_xmlDoc.newRootProp("from",send.getFrom());
	m_xmlDoc.newRootProp("dest",send.getDestination());
	m_xmlDoc.newRootProp("target",send.getTarget());

	xmlAttrPtr attrPtr = Node->properties;
	while (attrPtr != NULL)
	{
		if (!xmlStrEqual(attrPtr->name, BAD_CAST "id") &&
			!xmlStrEqual(attrPtr->name, BAD_CAST "type")&&
			!xmlStrEqual(attrPtr->name, BAD_CAST "from")&&
			!xmlStrEqual(attrPtr->name, BAD_CAST "dest")&&
			!xmlStrEqual(attrPtr->name, BAD_CAST "target")&&
			!xmlStrEqual(attrPtr->name, BAD_CAST "idlocation")&&
			!xmlStrEqual(attrPtr->name, BAD_CAST "targetexpr")&&
			!xmlStrEqual(attrPtr->name, BAD_CAST "typeexpr")&&
			!xmlStrEqual(attrPtr->name, BAD_CAST "eventexpr")&&
			!xmlStrEqual(attrPtr->name, BAD_CAST "namelist")&&
			!xmlStrEqual(attrPtr->name, BAD_CAST "event")){

			m_xmlDoc.newRootProp((char *)attrPtr->name,XStr(xmlGetProp(Node,attrPtr->name)).strForm());
		}
		attrPtr = attrPtr->next;
	}

	xmlNodePtr childNode  = Node->children;
	while(childNode != NULL)
	{
		if(childNode->type == XML_ELEMENT_NODE){
			xmlNodePtr newNode = xmlCopyNode(childNode,0);
			xmlNodePtr content = xmlNewText(BAD_CAST send.getParams()[(char *)newNode->name].c_str());
			xmlAddChild(newNode,content);
			m_xmlDoc.addChild(newNode);
			xmlFreeNode(newNode);
		}
		childNode = childNode->next;
	}

	std::map<std::string , EventDispatcher *>::const_iterator it = _vecSend.find(send.getTarget());
	if (it != _vecSend.end()) {
		it->second->fireSend(m_xmlDoc.getContent());
	}
	else {
#ifdef USE_LOG4CPLUS
		LOG4CPLUS_ERROR(log, _strSessionID << "not find the send target:" << send.getTarget());
#endif
	}
	return;
}


void fsm::StateMachine::processTimer(const xmlNodePtr Node)const
{
	if (!Node) return;
	model::Timer timer(Node);

	timer.execute(scInstance->getEvaluator(),scInstance->getContext(_rootNode,log));

	//LOG4CPLUS_DEBUG(logger,_strName << ":" << _strSessionID << "execute a script:" << script.getContent());
	fsm::Timer _timer(timer.getInterval(),this->_strName,timer.getId());
	scInstance->AddTimer(_timer);

	return;
}

void fsm::StateMachine::processLog( model::Log &_log)const
{
	using namespace xmlHelper;

	string exprValue = _log.getExpr();
	string logLevel = _log.getLevel();
	
#ifdef USE_LOG4CPLUS
	if (!logLevel.compare("trace") == 0){
		LOG4CPLUS_TRACE(log, _strSessionID << "," << exprValue);
	}
	else if (!logLevel.compare("debug") == 0){
		LOG4CPLUS_DEBUG(log, _strSessionID << "," << exprValue);
	}
	else if (!logLevel.compare("info") == 0){
		LOG4CPLUS_INFO(log, _strSessionID << "," << exprValue);
	}
	else if (!logLevel.compare("warn") == 0){
		LOG4CPLUS_WARN(log, _strSessionID << "," << exprValue);
	}
	else if (!logLevel.compare("error") == 0){
		LOG4CPLUS_ERROR(log,_strSessionID << "," << exprValue);
	}
	else if (!logLevel.compare("fatal") == 0){
		LOG4CPLUS_FATAL(log, _strSessionID << "," << exprValue);
	}
	else{

		LOG4CPLUS_INFO(log, _strSessionID << "," << exprValue);
	}
#endif
}

const xmlNodePtr fsm::StateMachine::getParentState( const xmlNodePtr currentState)const
{
	xmlNodePtr curState = currentState;
	do
	{
		curState = curState->parent;
		if(curState && isState(curState)) return curState;
	}while (curState != NULL && curState != _rootNode);

	return NULL;
}

void fsm::StateMachine::setName(const string strName)
{
	_strName = strName;
}


void fsm::StateMachine::exitStates() const
{
	if (_currentState)
	{
		for (xmlNodePtr  childNode = _currentState->children; childNode != NULL; childNode = childNode->next)
		{
			if (isExit(childNode))
			{
				processExit(childNode);
			}
		}
	}
}

void fsm::StateMachine::enterStates(const xmlNodePtr stateNode) const
{
	if(isState(stateNode))
	{
		_currentState = stateNode;

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
#ifdef USE_LOG4CPLUS
		LOG4CPLUS_ERROR(log, _strSessionID << ",Will enter the node is not a status node.");
#endif
	}
}



void fsm::StateMachine::processExit(const xmlNodePtr exitNode) const
{
	if (!exitNode) return ;

	for ( xmlNodePtr  actionNode = exitNode->children; actionNode != NULL ; actionNode = actionNode->next)
	{
		if (isLog(actionNode))
		{
			model::Log log(actionNode);
			log.execute(scInstance->getEvaluator(),scInstance->getContext(_rootNode,this->log));
			processLog(log);
			continue;
		}
		else if (isSend(actionNode))
		{
			processSend(actionNode);
			continue;
		}
		else if (isScript(actionNode))
		{
			model::Script script(actionNode);
			script.execute(scInstance->getEvaluator(),scInstance->getContext(_rootNode,log));
			continue;
		}
		else if (isTimer(actionNode))
		{
			processTimer(actionNode);
			continue;
		}
		else if(actionNode->type == XML_ELEMENT_NODE)
		{
#ifdef USE_LOG4CPLUS
			LOG4CPLUS_WARN(log, _strSessionID << ",  " << actionNode->name << " process not implement.");
#endif
		}
	}
	return ;
}

void fsm::StateMachine::processEntry(const xmlNodePtr node)const
{
	if (!node) return ;

	for ( xmlNodePtr  actionNode = node->children; actionNode != NULL; actionNode = actionNode->next)
	{
		if (isLog(actionNode))
		{
			model::Log log(actionNode);
			log.execute(scInstance->getEvaluator(),scInstance->getContext(_rootNode,this->log));
			processLog(log);
			continue;
		}
		else if (isSend(actionNode))
		{
			processSend(actionNode);
			continue;
		}
		else if (isScript(actionNode))
		{
			model::Script script(actionNode);
			script.execute(scInstance->getEvaluator(),scInstance->getContext(_rootNode,log));

			continue;
		}
		else if (isTransition(actionNode))
		{
			model::Transition transition(actionNode);
			transition.execute(scInstance->getEvaluator(),scInstance->getContext(_rootNode,log));
			if (transition.isEnabledCondition())
			{
				processTransition(transition);
				break;
			}
		}
		else if (isTimer(actionNode))
		{
			processTimer(actionNode);
			continue;
		}
		else if(actionNode->type == XML_ELEMENT_NODE)
		{
#ifdef USE_LOG4CPLUS
			LOG4CPLUS_WARN(log, _strSessionID << ",  " << actionNode->name << ", process not implement.");
#endif
		}
	}
	return ;
}

xmlNodePtr fsm::StateMachine::getState(const string& stateId) const
{
	using namespace xmlHelper;
	string strExpression="//state[@id='"+stateId +"']";
	CXPathContextPtr xpathCtx(NULL); 
	CXPathObjectPtr xpathObj(NULL); 

	try{

		/* Create xpath evaluation context */
		xpathCtx = xmlXPathNewContext(_docPtr._xDocPtr);

		if(xpathCtx._xPathCtxPtr == NULL) {
#ifdef USE_LOG4CPLUS
			LOG4CPLUS_ERROR(log,_strSessionID << ": unable to create new XPath context");
#endif
			throw exception("Error: unable to create new XPath context");
		}

		/* Evaluate xpath expression */
		xpathObj = xmlXPathEvalExpression(BAD_CAST(strExpression.c_str()), xpathCtx._xPathCtxPtr);
		if(xpathObj._xPathObjPtr == NULL) {
#ifdef USE_LOG4CPLUS
			LOG4CPLUS_WARN(log,  _strSessionID << ",Error: unable to evaluate xpath expression: " <<strExpression);
#endif
			throw exception(string("Error: unable to evaluate xpath expression: " +strExpression).c_str());
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
	if (_vecSend.count(evtDsp->getTarget())) return false;
	_vecSend[evtDsp->getTarget()] = evtDsp;
	return true;
}
const std::string & fsm::StateMachine::getName() {
	return _strName;
}
const std::string & fsm::StateMachine::getSessionId() {
	return _strSessionID;
}

fsm::Evaluator * fsm::StateMachine::getEvaluator()const {
	return this->scInstance->getEvaluator();
}

fsm::Context  *  fsm::StateMachine::getRootContext() {
	return this->scInstance->getContext(_rootNode,log);
}

void fsm::StateMachine::setscInstance(SCInstance * scIns)
{
	scInstance = scIns;
}
void fsm::StateMachine::setLog(log4cplus::Logger log)
{
	this->log = log;
}
void fsm::StateMachine::go()
{
	enterStates(this->_initState);
}
