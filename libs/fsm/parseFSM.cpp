#include "parseFSM.h"
#include "common/xmlHelper.h"

inline bool fsm::parseFSM::isDatamodel(const xmlNodePtr & xNode)
{
	return xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name, BAD_CAST("datamodel")); ;
}

inline bool fsm::parseFSM::isScriptModel(const xmlNodePtr & xNode)
{
	return xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name, BAD_CAST("scriptmodel")); ;
}

inline bool fsm::parseFSM::isData(const xmlNodePtr & xNode)
{
	return xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name, BAD_CAST("data")); ;
}

inline bool fsm::parseFSM::isState(const xmlNodePtr &xNode)
{
	return xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("state")) ; 
}

inline bool fsm::parseFSM::isTransition(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("transition")); 
}

inline bool fsm::parseFSM::isLog(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("log")); 
}

inline bool fsm::parseFSM::isEvent(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("event")); 
}

inline bool fsm::parseFSM::isExit(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("onexit")); 
}

inline bool fsm::parseFSM::isEntry(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("onentry")); 
}

inline bool fsm::parseFSM::isSend(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("send")); 
}

inline bool fsm::parseFSM::isScript(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("script")); 
}

inline bool fsm::parseFSM::isTimer(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("timer")); 
}

inline bool fsm::parseFSM::isRaise(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("raise")); 
}

inline bool fsm::parseFSM::isSleep(const xmlNodePtr &xNode)
{
	return  xNode && xNode->type == XML_ELEMENT_NODE && xmlStrEqual(xNode->name,BAD_CAST("sleep")); 
}

fsm::StateMachineimp * fsm::parseFSM::fsmParseFileImp(const std::string & filename)
{
	xmlDocPtr _xmlDocPtr = nullptr;

	_xmlDocPtr = xmlParseFile(filename.c_str());

	if (NULL == _xmlDocPtr)
		return nullptr;

	StateMachineimp * imp = parsefsm(_xmlDocPtr, filename);

	if (_xmlDocPtr)
		xmlFreeDoc(_xmlDocPtr);

	return imp;
}

fsm::StateMachineimp * fsm::parseFSM::fsmParseMemoryImp(const char * buffer, size_t size)
{
	xmlDocPtr _xmlDocPtr = nullptr;

	_xmlDocPtr = xmlParseMemory(buffer, size);

	if (NULL == _xmlDocPtr)
		return nullptr;

	StateMachineimp * imp = parsefsm(_xmlDocPtr, "");

	if (_xmlDocPtr)
		xmlFreeDoc(_xmlDocPtr);

	return imp;
}

fsm::StateMachineimp * fsm::parseFSM::parsefsm(xmlDocPtr _xmlDocPtr, const std::string & filename)
{
	using namespace helper::xml;
	StateMachineimp * imp = nullptr;
	xmlNodePtr rootNode = xmlDocGetRootElement(_xmlDocPtr);
	if (rootNode != NULL && xmlStrEqual(rootNode->name, BAD_CAST("fsm")))
	{
		imp = new StateMachineimp();
		
		imp->m_strStateFile = filename;

		imp->m_strName = getXmlNodeAttributesValue(rootNode, "name");
		imp->m_initState = getXmlNodeAttributesValue(rootNode, "initial");
		imp->m_finalState = getXmlNodeAttributesValue(rootNode, "final");

		for (xmlNodePtr childNode = rootNode->children; childNode != NULL; childNode = childNode->next)
		{
			if (isDatamodel(childNode))
			{
				parseDataModel(childNode, imp, filename);
			}
			else if (isScriptModel(childNode))
			{
				parseScriptModel(childNode, imp, filename);
			}
			else if (isState(childNode))
			{
				parseState(nullptr, childNode, imp, filename);
			}
		}

	}

	return imp;
}

void fsm::parseFSM::parseDataModel(xmlNodePtr datamodelNode, StateMachineimp * imp, const std::string & filename)
{
	std::shared_ptr<model::Datamodel> datamodelptr(new model::Datamodel(filename, datamodelNode->line));
	//datamodelptr->setCond(helper::xml::getXmlNodeAttributesValue(datamodelNode, "cond"));
	imp->m_Datamodel.push_back(datamodelptr);

	for (xmlNodePtr dataNode = datamodelNode->children; dataNode != nullptr; dataNode = dataNode->next)
	{
		if (isData(dataNode))
		{
			datamodelptr->addData(parseData(dataNode, filename));
		}
	}
}

void fsm::parseFSM::parseScriptModel(xmlNodePtr scriptmodelNode, StateMachineimp * imp, const std::string & filename)
{
	std::shared_ptr<model::Scriptmodel> scriptmodelptr(new model::Scriptmodel(filename, scriptmodelNode->line));
	//scriptmodelptr->setCond(helper::xml::getXmlNodeAttributesValue(scriptmodelNode, "cond"));
	imp->m_ScriptModel.push_back(scriptmodelptr);

	for (xmlNodePtr scriptNode = scriptmodelNode->children; scriptNode != nullptr; scriptNode = scriptNode->next)
	{
		if (isScript(scriptNode))
		{
			scriptmodelptr->addScript(parseScript(scriptNode, filename));
		}
	}
}

void fsm::parseFSM::parseState(model::State * parent, xmlNodePtr stateNode, StateMachineimp * imp, const std::string & filename)
{

	std::shared_ptr<model::State> stateptr(new model::State(filename, stateNode->line));
	stateptr->setId(helper::xml::getXmlNodeAttributesValue(stateNode, "id"));
	stateptr->setName(helper::xml::getXmlNodeAttributesValue(stateNode, "name"));
	stateptr->setDescription(helper::xml::getXmlNodeAttributesValue(stateNode, "memo"));
	stateptr->setParent(parent);
	imp->m_States[stateptr->getId()] = stateptr;

	for (xmlNodePtr childNode = stateNode->children; childNode != nullptr; childNode = childNode->next)
	{
		if (isEntry(childNode)){
			stateptr->addOnEntry(parseOnEntry(childNode, filename));
		}
		else if (isEvent(childNode))
		{
			stateptr->addEvent(parseEvent(childNode, filename));
		}
		else if (isExit(childNode))
		{
			stateptr->addOnExit(parseOnExit(childNode, filename));
		}
		else if (isState(childNode))
		{
			parseState(stateptr.get(), childNode, imp, filename);
		}

	}
}

std::shared_ptr<fsm::model::OnEntry> fsm::parseFSM::parseOnEntry(xmlNodePtr onentryNode, const std::string & filename)
{
	std::shared_ptr<model::OnEntry> onentry(new model::OnEntry(filename, onentryNode->line));
	for (xmlNodePtr actionNode = onentryNode->children; actionNode != nullptr; actionNode = actionNode->next)
	{
		if (isLog(actionNode))
		{
			onentry->addAction(parseLog(actionNode, filename));
		}
		else if (isSend(actionNode))
		{
			onentry->addAction(parseSend(actionNode, filename));
		}
		else if (isScript(actionNode))
		{
			onentry->addAction(parseScript(actionNode,filename));
		}
		else if (isTimer(actionNode))
		{
			onentry->addAction(parseTimer(actionNode, filename));
		}
		else if (isRaise(actionNode))
		{
			onentry->addAction(parseRaise(actionNode, filename));
		}
		else if (isSleep(actionNode))
		{
			onentry->addAction(parseSleep(actionNode, filename));
		}
		else if (isTransition(actionNode))
		{
			onentry->addAction(parseTransition(actionNode, filename));
		}

	}
	return std::move(onentry);
}

std::shared_ptr<fsm::model::OnExit> fsm::parseFSM::parseOnExit(xmlNodePtr onexitNode, const std::string & filename)
{
	std::shared_ptr<model::OnExit> onexit(new model::OnExit(filename, onexitNode->line));
	for (xmlNodePtr actionNode = onexitNode->children; actionNode != nullptr; actionNode = actionNode->next)
	{
		if (isLog(actionNode))
		{
			onexit->addAction(parseLog(actionNode, filename));
		}
		else if (isSend(actionNode))
		{
			onexit->addAction(parseSend(actionNode, filename));
		}
		else if (isScript(actionNode))
		{
			onexit->addAction(parseScript(actionNode, filename));
		}
		else if (isTimer(actionNode))
		{
			onexit->addAction(parseTimer(actionNode, filename));
		}
		else if (isRaise(actionNode))
		{
			onexit->addAction(parseRaise(actionNode, filename));
		}
		else if (isSleep(actionNode))
		{
			onexit->addAction(parseSleep(actionNode, filename));
		}

	}
	return std::move(onexit);
}

std::shared_ptr<fsm::model::Event> fsm::parseFSM::parseEvent(xmlNodePtr eventNode, const std::string & filename)
{
	std::shared_ptr<model::Event> eventptr(new model::Event(filename, eventNode->line));
	eventptr->setCond(helper::xml::getXmlNodeAttributesValue(eventNode, "cond"));
	eventptr->setEvent(helper::xml::getXmlNodeAttributesValue(eventNode, "event"));
	for (xmlNodePtr actionNode = eventNode->children; actionNode != nullptr; actionNode = actionNode->next)
	{
		if (isLog(actionNode))
		{
			eventptr->addAction(parseLog(actionNode, filename));
		}
		else if (isSend(actionNode))
		{
			eventptr->addAction(parseSend(actionNode, filename));
		}
		else if (isScript(actionNode))
		{
			eventptr->addAction(parseScript(actionNode, filename));
		}
		else if (isTimer(actionNode))
		{
			eventptr->addAction(parseTimer(actionNode, filename));
		}
		else if (isRaise(actionNode))
		{
			eventptr->addAction(parseRaise(actionNode, filename));
		}
		else if (isSleep(actionNode))
		{
			eventptr->addAction(parseSleep(actionNode, filename));
		}
		else if (isTransition(actionNode))
		{
			eventptr->addAction(parseTransition(actionNode, filename));
		}

	}
	return std::move(eventptr);
}

std::shared_ptr<fsm::model::Data> fsm::parseFSM::parseData(xmlNodePtr dataNode, const std::string & filename)
{
	std::shared_ptr<model::Data> dataptr(new model::Data(filename, dataNode->line));
	dataptr->setCond(helper::xml::getXmlNodeAttributesValue(dataNode, "cond"));
	dataptr->setId(helper::xml::getXmlNodeAttributesValue(dataNode, "id"));
	dataptr->setExpr(helper::xml::getXmlNodeAttributesValue(dataNode, "expr"));
	return std::move(dataptr);
}

std::shared_ptr<fsm::model::Log> fsm::parseFSM::parseLog(xmlNodePtr logNode, const std::string & filename)
{
	std::shared_ptr<model::Log> logptr(new model::Log(filename, logNode->line));
	logptr->setCond(helper::xml::getXmlNodeAttributesValue(logNode, "cond"));
	logptr->setExpr(helper::xml::getGetContent(logNode));
	logptr->setType(helper::xml::getXmlNodeAttributesValue(logNode, "type"));
	logptr->setLevel(helper::xml::getXmlNodeAttributesValue(logNode, "level"));
	return std::move(logptr);
}

std::shared_ptr<fsm::model::Script> fsm::parseFSM::parseScript(xmlNodePtr scriptNode, const std::string & filename)
{
	std::shared_ptr<model::Script> scriptptr(new model::Script(filename, scriptNode->line));
	scriptptr->setContext(helper::xml::getGetContent(scriptNode));
	scriptptr->setFileName(helper::xml::getXmlNodeAttributesValue(scriptNode, "src"));
	scriptptr->setCond(helper::xml::getXmlNodeAttributesValue(scriptNode, "cond"));

	return std::move(scriptptr);
}

std::shared_ptr<fsm::model::Send> fsm::parseFSM::parseSend(xmlNodePtr sendNode, const std::string & filename)
{
	std::shared_ptr<model::Send> sendptr(new model::Send(filename, sendNode->line));

	sendptr->setCond(helper::xml::getXmlNodeAttributesValue(sendNode, "cond"));
	sendptr->setId(helper::xml::getXmlNodeAttributesValue(sendNode, "id"));
	sendptr->setIdExpr(helper::xml::getXmlNodeAttributesValue(sendNode, "idexpr"));
	sendptr->setTarget(helper::xml::getXmlNodeAttributesValue(sendNode, "target"));
	//sendptr->setTargetExpr(helper::xml::getXmlNodeAttributesValue(sendNode, "targetexpr"));
	sendptr->setType(helper::xml::getXmlNodeAttributesValue(sendNode, "type"));
	sendptr->setTypeExpr(helper::xml::getXmlNodeAttributesValue(sendNode, "typeexpr"));
	sendptr->setEvent(helper::xml::getXmlNodeAttributesValue(sendNode, "event"));
	sendptr->setEventExpr(helper::xml::getXmlNodeAttributesValue(sendNode, "eventexpr"));
	//this->namelist = xmlHelper::getXmlNodeAttributesValue(sendNode,"namelist");
	sendptr->setFrom(helper::xml::getXmlNodeAttributesValue(sendNode, "from"));
	sendptr->setFromExpr(helper::xml::getXmlNodeAttributesValue(sendNode, "fromexpr"));
	sendptr->setDestination(helper::xml::getXmlNodeAttributesValue(sendNode, "dest"));
	sendptr->setDestinationExpr(helper::xml::getXmlNodeAttributesValue(sendNode, "destexpr"));

	for (xmlNodePtr paramNode = sendNode->children; paramNode != nullptr; paramNode = paramNode->next) {
		if (paramNode->type == XML_ELEMENT_NODE) {
			std::string _type = helper::xml::getXmlNodeAttributesValue(paramNode, "type");
			std::string _value = helper::xml::getGetContent(paramNode);
			sendptr->addParam((const char *)paramNode->name, _type, _value, paramNode->line);

		}
	}
	return std::move(sendptr);
}

std::shared_ptr<fsm::model::Timer> fsm::parseFSM::parseTimer(xmlNodePtr timerNode, const std::string & filename)
{
	std::shared_ptr<model::Timer> timerptr(new model::Timer(filename, timerNode->line));

	timerptr->setCond(helper::xml::getXmlNodeAttributesValue(timerNode, "cond"));
	timerptr->setId(helper::xml::getXmlNodeAttributesValue(timerNode, "id"));
	timerptr->setIdExpr(helper::xml::getXmlNodeAttributesValue(timerNode, "idexpr"));
	timerptr->setInterval(helper::xml::getXmlNodeAttributesValue(timerNode, "interval"));
	timerptr->setIntervalExpr(helper::xml::getXmlNodeAttributesValue(timerNode, "intervalexpr"));
	return std::move(timerptr);
}

std::shared_ptr<fsm::model::Raise> fsm::parseFSM::parseRaise(xmlNodePtr raiseNode, const std::string & filename)
{
	std::shared_ptr<model::Raise> raiseptr(new model::Raise(filename, raiseNode->line));
	raiseptr->setCond(helper::xml::getXmlNodeAttributesValue(raiseNode, "cond"));
	raiseptr->setEvent(helper::xml::getXmlNodeAttributesValue(raiseNode, "event"));
	return std::move(raiseptr);
}

std::shared_ptr<fsm::model::Sleep> fsm::parseFSM::parseSleep(xmlNodePtr sleepNode, const std::string & filename)
{
	std::shared_ptr<model::Sleep> sleepptr(new model::Sleep(filename, sleepNode->line));
	sleepptr->setCond(helper::xml::getXmlNodeAttributesValue(sleepNode, "cond"));
	sleepptr->setInterval(helper::xml::getXmlNodeAttributesValue(sleepNode, "interval"));
	return std::move(sleepptr);
}

std::shared_ptr<fsm::model::Transition> fsm::parseFSM::parseTransition(xmlNodePtr transitionNode, const std::string & filename)
{
	std::shared_ptr<model::Transition> transitionptr(new model::Transition(filename, transitionNode->line));
	transitionptr->setCond(helper::xml::getXmlNodeAttributesValue(transitionNode, "cond"));
	transitionptr->setTarget(helper::xml::getXmlNodeAttributesValue(transitionNode, "target"));
	return std::move(transitionptr);
}

