#include "Send.h"
#include <cstring>
#include <log4cplus/loggingmacros.h>
#include "../../common/xmlHelper.h"
#include "../../common/stringHelper.h"
#include <json/config.h>
#include <json/json.h>

namespace fsm
{
namespace model
{


	Send::Send(xmlNodePtr xNode,const std::string &session,const std::string &filename)
		:Action(xNode, session,	filename)
	{
		log = log4cplus::Logger::getInstance("fsm.model.Send");

		this->id = helper::xml::getXmlNodeAttributesValue(m_node,"id");
		this->idexpr = helper::xml::getXmlNodeAttributesValue(m_node,"idexpr");
		this->target = helper::xml::getXmlNodeAttributesValue(m_node,"target");
		this->targetexpr = helper::xml::getXmlNodeAttributesValue(m_node,"targetexpr");
		this->type = helper::xml::getXmlNodeAttributesValue(m_node,"type");
		this->typeexpr = helper::xml::getXmlNodeAttributesValue(m_node,"typeexpr");
		this->_event = helper::xml::getXmlNodeAttributesValue(m_node,"event");
		this->eventexpr = helper::xml::getXmlNodeAttributesValue(m_node,"eventexpr");
		//this->namelist = xmlHelper::getXmlNodeAttributesValue(node,"namelist");
		//this->from = helper::xml::getXmlNodeAttributesValue(m_node,"from");
		//this->fromexpr = helper::xml::getXmlNodeAttributesValue(m_node,"fromexpr");
		this->dest = helper::xml::getXmlNodeAttributesValue(m_node,"dest");
		this->destexpr = helper::xml::getXmlNodeAttributesValue(m_node,"destexpr");
	}


	const std::string& Send::getId()const
	{
		return id;
	}
	void Send::setId(const std::string &strValue)
	{
		id = strValue;
	}
	//std::string& Send::getIdLocation()
	//{
	//	return idlocation;
	//}
	const std::string& Send::getTarget()const
	{
		return target;
	}

	/*const std::string& Send::getFrom()const
	{
		return from;
	}*/

	const std::string& Send::getType()const
	{
		return type;
	}

	const std::string& Send::getEvent()const
	{
		return this->_event;
	}
	//std::string& Send::getEventExpr()
	//{
	//	return this->eventexpr;
	//}

	const std::string& Send::getDestination()const
	{
		return this->dest;
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

	const std::string& Send::getContent()const
	{
		return content;
	}
	void Send::execute(fsm::Context * ctx)
	{
		if (ctx && helper::string::isStringEmpty(id) && !idexpr.empty()){
			Json::Value jsonid = ctx->eval(idexpr,m_strFileName,m_node->line/*,xmlHasProp(m_node,BAD_CAST"idexpr")*/);
			if (jsonid.isString() || jsonid.isBool() || jsonid.isNull()){
				id = jsonid.asString();
			}
		}
		
		if (ctx && helper::string::isStringEmpty(target) && !targetexpr.empty()){
			Json::Value jsontarget = ctx->eval(targetexpr,m_strFileName,m_node->line/*,xmlHasProp(m_node,BAD_CAST"targetexpr")*/);
			if (jsontarget.isString() || jsontarget.isBool() || jsontarget.isNull()){
				target = jsontarget.asString();
			}
		}

		if (ctx && helper::string::isStringEmpty(type) && !typeexpr.empty()){
			Json::Value jsontype = ctx->eval(typeexpr,m_strFileName,m_node->line/*,xmlHasProp(m_node,BAD_CAST"typeexpr")*/);
			if (jsontype.isString() || jsontype.isBool() || jsontype.isNull()){
				type = jsontype.asString();
			}
		}

		if (ctx && helper::string::isStringEmpty(_event) && !eventexpr.empty()){
			Json::Value jsonEvent = ctx->eval(eventexpr,m_strFileName,m_node->line/*,xmlHasProp(m_node,BAD_CAST"eventexpr")*/);
			if (jsonEvent.isString() || jsonEvent.isBool() || jsonEvent.isNull()){
				_event = jsonEvent.asCString();
			}
		}

		/*if (ctx && helper::string::isStringEmpty(from) && !fromexpr.empty()){
			Json::Value jsonfrom = ctx->eval(fromexpr,m_strFileName,m_node->line,xmlHasProp(m_node,BAD_CAST"fromexpr"));
			if (jsonfrom.isString() || jsonfrom.isBool() || jsonfrom.isNull()){
				from = jsonfrom.asCString();
			}
		}*/

		if (ctx && helper::string::isStringEmpty(dest) && !destexpr.empty()){
			Json::Value jsondest = ctx->eval(destexpr,m_strFileName,m_node->line/*,xmlHasProp(m_node,BAD_CAST"destexpr")*/);
			if (jsondest.isString() || jsondest.isBool() || jsondest.isNull()){
				dest = jsondest.asString();
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
		//Á¬½Ó·¢ËÍ×Ö·û´®
	
		Json::Value sendValue;
		sendValue["type"] = getType();
		sendValue["event"] = getEvent();
		sendValue["id"] = getId();
		sendValue["from"] = m_strSession;
		sendValue["dest"] = getDestination();
		sendValue["target"] = getTarget();

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
		xmlNodePtr childNode  = m_node->children;
		Json::Value param;
		while(childNode != NULL)
		{
			if(childNode->type == XML_ELEMENT_NODE){
				//xmlNodePtr newNode = xmlCopyNode(childNode,0);
				//xmlNodePtr content = xmlNewText(BAD_CAST params[(char *)newNode->name].c_str());
				//xmlAddChild(newNode,content);
				std::string _type = helper::xml::getXmlNodeAttributesValue(childNode,"type");
				if(ctx && _type.compare("script") == 0)
					param[(const char *)childNode->name] = ctx->eval(helper::xml::XStr(xmlNodeGetContent(childNode)).strForm(),m_strFileName,childNode->line/*,childNode*/);
				else
					param[(const char *)childNode->name] = helper::xml::XStr(xmlNodeGetContent(childNode)).strForm();

				//xmlFreeNode(newNode);
			}
			childNode = childNode->next;
		}
		if (!param.isNull())
			sendValue["param"] = param;
		content = sendValue.toStyledString();
		//LOG4CPLUS_TRACE(log,",send content:" << content);
	}

}
}

