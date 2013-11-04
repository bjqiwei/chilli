#include "Send.h"
#include <scxml/SCXMLHelper.h>

namespace fsm
{
namespace model
{


	Send::Send(xmlNodePtr xNode):node(xNode)
	{
		log = log4cplus::Logger::getInstance("scxml.model.send");
		this->id = xmlHelper::getXmlNodeAttributesValue(node,"id");
		this->idlocation = xmlHelper::getXmlNodeAttributesValue(node,"idlocation");
		this->target = xmlHelper::getXmlNodeAttributesValue(node,"target");
		this->targetexpr = xmlHelper::getXmlNodeAttributesValue(node,"targetexpr");
		this->type = xmlHelper::getXmlNodeAttributesValue(node,"type");
		this->typeexpr = xmlHelper::getXmlNodeAttributesValue(node,"typeexpr");
		this->_event = xmlHelper::getXmlNodeAttributesValue(node,"event");
		this->eventexpr = xmlHelper::getXmlNodeAttributesValue(node,"eventexpr");
		this->namelist = xmlHelper::getXmlNodeAttributesValue(node,"namelist");
		this->from = xmlHelper::getXmlNodeAttributesValue(node,"from");
		this->dest = xmlHelper::getXmlNodeAttributesValue(node,"dest");
	}


	std::string& Send::getId()
	{
		return id;
	}
	void Send::setId(const std::string strValue)
	{
		id = strValue;
	}
	std::string& Send::getIdLocation()
	{
		return idlocation;
	}
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
	std::string& Send::getEventExpr()
	{
		return this->eventexpr;
	}

	std::string& Send::getDestination()
	{
		return this->dest;
	}

	std::string& Send::getNamelist()
	{
		return this->namelist;
	}
	std::map<std::string, std::string>& Send::getParams()
	{
		return params;
	}

	std::string& Send::getTargetExpr()
	{
		return targetexpr;
	}
	void Send::execute(fsm::Evaluator * evl,fsm::Context * ctx)
	{

		if (SCXMLHelper::isStringEmpty(id)){
			id = evl->eval(ctx,idlocation,node->line);
		}
		
		if (SCXMLHelper::isStringEmpty(target)){
			target = evl->eval(ctx,targetexpr,node->line);
		}

		if (SCXMLHelper::isStringEmpty(type)){
			type = evl->eval(ctx,typeexpr,node->line);
		}

		if (SCXMLHelper::isStringEmpty(_event)){
			_event = evl->eval(ctx,eventexpr,node->line);
		}

		if (!SCXMLHelper::isStringEmpty(from)){
			from = evl->eval(ctx,from,node->line);
		}

		if (!SCXMLHelper::isStringEmpty(dest)){
			dest = evl->eval(ctx,dest,node->line);
		}

		if (!SCXMLHelper::isStringEmpty(namelist)){
			char * pNamelist =(char *) malloc(namelist.length()+1);
			memset(pNamelist,0,namelist.length()+1);
			memcpy(pNamelist,namelist.c_str(),namelist.length());
			char *next_token = NULL;

			char * pch = strtok_s(pNamelist," \r\t\n",&next_token);
			while(pch != NULL)
			{
				std::string _value = ctx->get(pch);
				params[pch]=_value;
				pch = strtok_s(NULL, " \r\t\n",&next_token);
			}
			free(pNamelist);
		}

		xmlNodePtr xParaNode = node->children;
		while(xParaNode != NULL)
		{
			if (xParaNode->type == XML_ELEMENT_NODE)
			{
				params[(char *)xParaNode->name] = 
				evl->eval(ctx,xmlHelper::XStr(xmlNodeGetContent(xParaNode)).strForm(),xParaNode->line);
			}
			xParaNode = xParaNode->next;
		}
	}
}
}

