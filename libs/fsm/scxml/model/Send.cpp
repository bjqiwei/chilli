#include "Send.h"
#include <cstring>
#include <log4cplus/loggingmacros.h>
#include <json/config.h>
#include <json/json.h>

namespace fsm
{
namespace model
{


	Send::Send(const std::string &filename, uint32_t lineno)
		:Action(filename,lineno)
	{

	}


	const std::string& Send::getId()const
	{
		return id;
	}
	void Send::setId(const std::string &strValue)
	{
		this->id = strValue;
	}
	const std::string & Send::getIdExpr()const
	{
		// TODO: insert return statement here
		return idexpr;
	}
	void Send::setIdExpr(const std::string & idexpr)
	{
		this->idexpr = idexpr;
	}

	const std::string& Send::getTarget()const
	{
		return target;
	}

	void Send::setTarget(const std::string & target)
	{
		this->target = target;
	}


	//const std::string& Send::getTargetExpr() const
	//{
	//	return this->targetexpr;
	//}

	//void Send::setTargetExpr(const std::string & targetexpr)
	//{
	//	this->targetexpr = targetexpr;
	//}

	const std::string& Send::getFrom()const
	{
		return from;
	}

	void Send::setFrom(const std::string & from)
	{
		this->from = from;
	}

	const std::string & Send::getFromExpr() const
	{
		// TODO: insert return statement here
		return fromexpr;
	}

	void Send::setFromExpr(const std::string & fromexpr)
	{
		this->fromexpr = fromexpr;
	}

	const std::string& Send::getType()const
	{
		return type;
	}

	void Send::setType(const std::string & type)
	{
		this->type = type;
	}

	const std::string & Send::getTypeExpr() const
	{
		// TODO: insert return statement here
		return this->typeexpr;
	}

	void Send::setTypeExpr(const std::string & typeexpr)
	{
		this->typeexpr = typeexpr;
	}

	const std::string& Send::getEvent()const
	{
		return this->_event;
	}

	void Send::setEvent(const std::string & event)
	{
		this->_event = event;
	}

	const std::string & Send::getEventExpr()const
	{
		// TODO: insert return statement here
		return this->eventexpr;
	}

	void Send::setEventExpr(const std::string & eventexpr)
	{
		this->eventexpr = eventexpr;
	}

	void Send::addParam(const std::string & name, const std::string & type, const std::string & value, uint32_t lineno)
	{
		ParamStruct param;
		param.name = name;
		param.type = type;
		param.value = value;
		param.lineno = lineno;
		m_Params.push_back(param);
	}


	const std::string& Send::getDestination()const
	{
		return this->dest;
	}

	void Send::setDestination(const std::string & dest)
	{
		this->dest = dest;
	}

	const std::string & Send::getDestinationExpr() const
	{
		// TODO: insert return statement here
		return this->destexpr;
	}

	void Send::setDestinationExpr(const std::string & destexpr)
	{
		this->destexpr = destexpr;
	}

	/*std::string& Send::getNamelist()
	{
		return this->namelist;
	}*/
	//std::map<std::string, std::string>& Send::getParams()
	//{
	//	return params;
	//}

	//std::string& Send::getTargetExpr()
	//{
	//	return targetexpr;
	//}

	void Send::execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId)const
	{
	}
	void Send::execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId, FireDataType & fireData) const
	{
		fireData.id = this->getId();
		if (ctx && id.empty() && !idexpr.empty()){
			Json::Value jsonid = ctx->eval(idexpr,m_strFileName, m_lineNo/*,xmlHasProp(m_node,BAD_CAST"idexpr")*/);
			if (jsonid.isString() || jsonid.isBool() || jsonid.isNull()){
				fireData.id = jsonid.asString();
			}
		}
		
		fireData.target = this->getTarget();
		//if (ctx && target.empty() && !targetexpr.empty()){
		//	Json::Value jsontarget = ctx->eval(targetexpr,m_strFileName,m_lineNo/*,xmlHasProp(m_node,BAD_CAST"targetexpr")*/);
		//	if (jsontarget.isString() || jsontarget.isBool() || jsontarget.isNull()){
		//		fireData.target = jsontarget.asString();
		//	}
		//}

		fireData.type = this->getType();
		if (ctx && type.empty() && !typeexpr.empty()){
			Json::Value jsontype = ctx->eval(typeexpr,m_strFileName,m_lineNo/*,xmlHasProp(m_node,BAD_CAST"typeexpr")*/);
			if (jsontype.isString() || jsontype.isBool() || jsontype.isNull()){
				fireData.type = jsontype.asString();
			}
		}

		fireData.event = this->getEvent();
		if (ctx && _event.empty() && !eventexpr.empty()){
			Json::Value jsonEvent = ctx->eval(eventexpr,m_strFileName,m_lineNo/*,xmlHasProp(m_node,BAD_CAST"eventexpr")*/);
			if (jsonEvent.isString() || jsonEvent.isBool() || jsonEvent.isNull()){
				fireData.event = jsonEvent.asCString();
			}
		}

		fireData.from = this->getFrom();
		if (ctx && from.empty() && !fromexpr.empty()){
			Json::Value jsonfrom = ctx->eval(fromexpr,m_strFileName,m_lineNo/*,xmlHasProp(m_node,BAD_CAST"fromexpr")*/);
			if (jsonfrom.isString() || jsonfrom.isBool() || jsonfrom.isNull()){
				fireData.from = jsonfrom.asCString();
			}
		}

		fireData.dest = this->getDestination();
		if (ctx && dest.empty() && !destexpr.empty()){
			Json::Value jsondest = ctx->eval(destexpr,m_strFileName, m_lineNo/*,xmlHasProp(m_node,BAD_CAST"destexpr")*/);
			if (jsondest.isString() || jsondest.isBool() || jsondest.isNull()){
				fireData.dest = jsondest.asString();
			}
		}

	/*	if (!SCXMLHelper::isStringEmpty(namelist)){
			char * pNamelist =(char *) malloc(namelist.length()+1);
			memset(pNamelist,0,namelist.length()+1);
			memcpy(pNamelist,namelist.c_str(),namelist.length());
			char *next_token = NULL;
#ifdef WIN32
			char * pch = strtok_s(pNamelist," \r\t\n",&next_token);
#else
			char * pch = strtok_r(pNamelist," \r\t\n",&next_token);
#endif
			while(pch != NULL)
			{
				std::string _value = ctx->get(pch);
				params[pch]=_value;
#ifdef WIN32
				pch = strtok_s(NULL, " \r\t\n",&next_token);
#else
				pch = strtok_r(NULL, " \r\t\n",&next_token);
#endif
			}
			free(pNamelist);
		}*/

		/*xmlNodePtr xParaNode = node->children;
		while(xParaNode != NULL)
		{
			if (xParaNode->type == XML_ELEMENT_NODE)
			{
				params[(char *)xParaNode->name] = XStr(xmlNodeGetContent(xParaNode)).strForm();
			}
			xParaNode = xParaNode->next;
		}
*/
		//·¢ËÍÊý¾Ý

		/*xmlAttrPtr attrPtr = m_node->properties;
		while (attrPtr != NULL)
		{
			if (!xmlStrEqual(attrPtr->name, BAD_CAST "id") &&
				!xmlStrEqual(attrPtr->name, BAD_CAST "type")&&
				!xmlStrEqual(attrPtr->name, BAD_CAST "from")&&
				!xmlStrEqual(attrPtr->name, BAD_CAST "dest")&&
				!xmlStrEqual(attrPtr->name, BAD_CAST "target")&&
				!xmlStrEqual(attrPtr->name, BAD_CAST "event")&&
				!xmlStrEqual(attrPtr->name, BAD_CAST "idexpr")&&
				!xmlStrEqual(attrPtr->name, BAD_CAST "targetexpr")&&
				!xmlStrEqual(attrPtr->name, BAD_CAST "typeexpr")&&
				!xmlStrEqual(attrPtr->name, BAD_CAST "fromexpr")&&
				!xmlStrEqual(attrPtr->name, BAD_CAST "destexpr")&&
				!xmlStrEqual(attrPtr->name, BAD_CAST "eventexpr")&&
				!xmlStrEqual(attrPtr->name, BAD_CAST "cond")){
					sendValue[(const char *)attrPtr->name] = helper::xml::XStr(xmlGetProp(m_node,attrPtr->name)).strForm();
			}
			attrPtr = attrPtr->next;
		}*/

		//m_xmlDoc.addAddChildList(node->children);
		for (auto & param : m_Params) {

			if (ctx && param.type.compare("script") == 0)
				fireData.param[param.name] = ctx->eval(param.value, m_strFileName, param.lineno/*,childNode*/);
			else
				fireData.param[param.name] = param.value;

			//xmlFreeNode(newNode);
		}	
		
		//LOG4CPLUS_TRACE(log,",send content:" << content);
	}

}
}

