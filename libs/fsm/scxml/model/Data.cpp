#include "Data.h"
#include "../../common/xmlHelper.h"
#include "../../common/stringHelper.h"
#include <log4cplus/loggingmacros.h>

namespace fsm
{
namespace model
{

	Data::Data(xmlNodePtr xNode,const std::string &session,const std::string &filename):Action(xNode,session,filename)
	{
		log = log4cplus::Logger::getInstance("fsm.model.Data");
		this->m_strId = helper::xml::getXmlNodeAttributesValue(node,"id");
		this->m_strExpr = helper::xml::getXmlNodeAttributesValue(node,"expr");
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
		else */if (!helper::string::isStringEmpty(this->getExpr()))
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

