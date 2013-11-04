#include "Data.h"
#include <xmlHelper.h>
#include "scxml\SCXMLHelper.h"

namespace fsm
{
namespace model
{

	Data::Data(xmlNodePtr xNode):node(xNode)
	{
		m_strId = xmlHelper::getXmlNodeAttributesValue(node,"id");
		m_strExpr = xmlHelper::getXmlNodeAttributesValue(node,"expr");
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
	void Data::execute(fsm::Evaluator * evl,fsm::Context * ctx)
	{
			
		/*if (!SCXMLHelper::isStringEmpty(datum.getSrc()))
		{
			ctx->setLocal(datum.getId(),datum.getSrc());
		}
		else */if (!SCXMLHelper::isStringEmpty(this->getExpr()))
		{
			std::string value;
			value = evl->eval(ctx, getExpr(),node->line);
			ctx->setLocal(getId(), value);
			
		}
		else
		{
			ctx->setLocal(getId(), "");
		}
	}
}
}

