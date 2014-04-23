#include "Send.h"
#include <cstring>
#include <log4cplus/loggingmacros.h>
#include "../../common/xmlHelper.h"
#include "../../common/stringHelper.h"

namespace fsm
{
namespace model
{


	Send::Send(xmlNodePtr xNode,const std::string &session,const std::string &filename):node(xNode),m_strSession(session),
		m_strFilename(filename)
	{
		log = log4cplus::Logger::getInstance("fsm.model.Send");

		this->id = helper::xml::getXmlNodeAttributesValue(node,"id");
		this->idexpr = helper::xml::getXmlNodeAttributesValue(node,"idexpr");
		this->target = helper::xml::getXmlNodeAttributesValue(node,"target");
		this->targetexpr = helper::xml::getXmlNodeAttributesValue(node,"targetexpr");
		this->type = helper::xml::getXmlNodeAttributesValue(node,"type");
		this->typeexpr = helper::xml::getXmlNodeAttributesValue(node,"typeexpr");
		this->_event = helper::xml::getXmlNodeAttributesValue(node,"event");
		this->eventexpr = helper::xml::getXmlNodeAttributesValue(node,"eventexpr");
		//this->namelist = xmlHelper::getXmlNodeAttributesValue(node,"namelist");
		this->from = helper::xml::getXmlNodeAttributesValue(node,"from");
		this->fromexpr = helper::xml::getXmlNodeAttributesValue(node,"fromexpr");
		this->dest = helper::xml::getXmlNodeAttributesValue(node,"dest");
		this->destexpr = helper::xml::getXmlNodeAttributesValue(node,"destexpr");
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

	const std::string& Send::getFrom()const
	{
		return from;
	}

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
			id = ctx->eval(idexpr,m_strFilename,node->line,xmlHasProp(node,BAD_CAST"idexpr"));
		}
		
		if (ctx && helper::string::isStringEmpty(target) && !targetexpr.empty()){
			target = ctx->eval(targetexpr,m_strFilename,node->line,xmlHasProp(node,BAD_CAST"targetexpr"));
		}

		if (ctx && helper::string::isStringEmpty(type) && !typeexpr.empty()){
			type = ctx->eval(typeexpr,m_strFilename,node->line,xmlHasProp(node,BAD_CAST"typeexpr"));
		}

		if (ctx && helper::string::isStringEmpty(_event) && !eventexpr.empty()){
			_event = ctx->eval(eventexpr,m_strFilename,node->line,xmlHasProp(node,BAD_CAST"eventexpr"));
		}

		if (ctx && helper::string::isStringEmpty(from) && !fromexpr.empty()){
			from = ctx->eval(fromexpr,m_strFilename,node->line,xmlHasProp(node,BAD_CAST"fromexpr"));
		}

		if (ctx && helper::string::isStringEmpty(dest) && !destexpr.empty()){
			dest = ctx->eval(destexpr,m_strFilename,node->line,xmlHasProp(node,BAD_CAST"destexpr"));
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
	
		helper::xml::CXmlDocmentHelper m_xmlDoc;

		m_xmlDoc.setRootNode(getType());
		m_xmlDoc.newRootProp(getType(),getEvent());
		m_xmlDoc.newRootProp("id",getId());
		m_xmlDoc.newRootProp("from",getFrom());
		m_xmlDoc.newRootProp("dest",getDestination());
		m_xmlDoc.newRootProp("target",getTarget());

		xmlAttrPtr attrPtr = node->properties;
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
				!xmlStrEqual(attrPtr->name, BAD_CAST "eventexpr")){
					m_xmlDoc.newRootProp((char *)attrPtr->name, helper::xml::XStr(xmlGetProp(node,attrPtr->name)).strForm());
			}
			attrPtr = attrPtr->next;
		}

		//m_xmlDoc.addAddChildList(node->children);
		xmlNodePtr childNode  = node->children;
		while(childNode != NULL)
		{
			if(childNode->type == XML_ELEMENT_NODE){
				//xmlNodePtr newNode = xmlCopyNode(childNode,0);
				//xmlNodePtr content = xmlNewText(BAD_CAST params[(char *)newNode->name].c_str());
				//xmlAddChild(newNode,content);
				std::string _type = helper::xml::getXmlNodeAttributesValue(childNode,"type");
				if(ctx && _type.compare("script") == 0)
					m_xmlDoc.addChild((char *)childNode->name,ctx->eval(helper::xml::XStr(xmlNodeGetContent(childNode)).strForm(),m_strFilename,childNode->line,childNode));
				else
					m_xmlDoc.addChild((char *)childNode->name,helper::xml::XStr(xmlNodeGetContent(childNode)).strForm());

				//xmlFreeNode(newNode);
			}
			childNode = childNode->next;
		}
		content = m_xmlDoc.getContent();
		//LOG4CPLUS_TRACE(log,m_strSession << ",send content:" << content);
	}
}
}

