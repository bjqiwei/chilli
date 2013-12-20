#include "Send.h"
#include "../SCXMLHelper.h"
#include <cstring>
#include <log4cplus/loggingmacros.h>
#include "../../xmlHelper.h"

namespace fsm
{
namespace model
{


	Send::Send(xmlNodePtr xNode,const std::string &session,const std::string &filename):node(xNode),m_strSession(session),
		m_strFilename(filename)
	{
		log = log4cplus::Logger::getInstance("StateMachine.model.Send");

		this->id = xmlHelper::getXmlNodeAttributesValue(node,"id");
		this->idexpr = xmlHelper::getXmlNodeAttributesValue(node,"idexpr");
		this->target = xmlHelper::getXmlNodeAttributesValue(node,"target");
		this->targetexpr = xmlHelper::getXmlNodeAttributesValue(node,"targetexpr");
		this->type = xmlHelper::getXmlNodeAttributesValue(node,"type");
		this->typeexpr = xmlHelper::getXmlNodeAttributesValue(node,"typeexpr");
		this->_event = xmlHelper::getXmlNodeAttributesValue(node,"event");
		this->eventexpr = xmlHelper::getXmlNodeAttributesValue(node,"eventexpr");
		//this->namelist = xmlHelper::getXmlNodeAttributesValue(node,"namelist");
		this->from = xmlHelper::getXmlNodeAttributesValue(node,"from");
		this->fromexpr = xmlHelper::getXmlNodeAttributesValue(node,"fromexpr");
		this->dest = xmlHelper::getXmlNodeAttributesValue(node,"dest");
		this->destexpr = xmlHelper::getXmlNodeAttributesValue(node,"destexpr");
	}


	std::string& Send::getId()
	{
		return id;
	}
	void Send::setId(const std::string strValue)
	{
		id = strValue;
	}
	//std::string& Send::getIdLocation()
	//{
	//	return idlocation;
	//}
	std::string& Send::getTarget()
	{
		return target;
	}

	std::string& Send::getFrom()
	{
		return from;
	}

	std::string& Send::getType()
	{
		return type;
	}

	std::string& Send::getEvent()
	{
		return this->_event;
	}
	//std::string& Send::getEventExpr()
	//{
	//	return this->eventexpr;
	//}

	std::string& Send::getDestination()
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

	std::string& Send::getContent()
	{
		return content;
	}
	void Send::execute(fsm::Context * ctx)
	{
		using namespace  xmlHelper;
		if (SCXMLHelper::isStringEmpty(id)){
			id = ctx->eval(idexpr,m_strFilename,node->line);
		}
		
		if (SCXMLHelper::isStringEmpty(target)){
			target = ctx->eval(targetexpr,m_strFilename,node->line);
		}

		if (SCXMLHelper::isStringEmpty(type)){
			type = ctx->eval(typeexpr,m_strFilename,node->line);
		}

		if (SCXMLHelper::isStringEmpty(_event)){
			_event = ctx->eval(eventexpr,m_strFilename,node->line);
		}

		if (SCXMLHelper::isStringEmpty(from)){
			from = ctx->eval(fromexpr,m_strFilename,node->line);
		}

		if (SCXMLHelper::isStringEmpty(dest)){
			dest = ctx->eval(destexpr,m_strFilename,node->line);
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
	
		CXmlDocmentHelper m_xmlDoc;

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
					m_xmlDoc.newRootProp((char *)attrPtr->name, XStr(xmlGetProp(node,attrPtr->name)).strForm());
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
				std::string _type = xmlHelper::getXmlNodeAttributesValue(childNode,"type");
				if(_type.compare("script") == 0)
					m_xmlDoc.addChild((char *)childNode->name,ctx->eval(XStr(xmlNodeGetContent(childNode)).strForm(),m_strFilename,childNode->line));
				else
					m_xmlDoc.addChild((char *)childNode->name,XStr(xmlNodeGetContent(childNode)).strForm());

				//xmlFreeNode(newNode);
			}
			childNode = childNode->next;
		}
		content = m_xmlDoc.getContent();
		LOG4CPLUS_TRACE(log,m_strSession << ",send content:" << content);
	}
}
}

