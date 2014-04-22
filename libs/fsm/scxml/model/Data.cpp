#include "Data.h"
#include "../../xmlHelper.h"
#include "../SCXMLHelper.h"
#include <log4cplus/loggingmacros.h>

namespace fsm
{
namespace model
{

	Data::Data(xmlNodePtr xNode,const std::string &session,const std::string &filename):node(xNode),m_strSession(session)
		,m_strFileName(filename)
	{
		m_strId = xmlHelper::getXmlNodeAttributesValue(node,"id");
		m_strExpr = xmlHelper::getXmlNodeAttributesValue(node,"expr");
		log = log4cplus::Logger::getInstance("fsm.model.Data");
	}

	const std::string & Data::getId()const
	{
		return m_strId;
	}

	//const std::string  Data::getSrc() const
	//{
	//	return xmlHelper::getXmlNodeAttributesValue(node,"src");
	//}

	const std::string & Data::getExpr() const
	{
		return m_strExpr;
	}

	//xmlNodePtr Data::getNode()
	//{
	//	return node->children;
	//}
	void Data::execute(fsm::Context * ctx)
	{
		//LOG4CPLUS_TRACE(log,m_strSession << ",execute starting...");
		/*if (!SCXMLHelper::isStringEmpty(datum.getSrc()))
		{
			ctx->setLocal(datum.getId(),datum.getSrc());
		}
		else */if (!SCXMLHelper::isStringEmpty(this->getExpr()))
		{
			//std::string value;
			//value = evl->eval(ctx, getExpr(),m_strFileName,node->line);
			ctx->setLocal(getId(), this->getExpr(),false);
			
		}
		else
		{
			ctx->setLocal(getId(), "",false);
		}
		//LOG4CPLUS_TRACE(log,m_strSession << ",execute end.");
	}
}
}

