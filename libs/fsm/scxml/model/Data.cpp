#include "Data.h"
#include <log4cplus/loggingmacros.h>

namespace fsm
{
namespace model
{

	Data::Data(const std::string &filename, uint32_t lineno):Action(filename,lineno)
	{
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
	void Data::execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId) const
	{
		if (ctx == NULL){
			return ;
		}

		if (!this->getExpr().empty())
		{
			//std::string value;
			//value = evl->eval(ctx, getExpr(),m_strFileName,node->line);
			ctx->eval("var " + getId() + "=" + this->getExpr() + ";", m_strFileName, m_lineNo/*, m_node*/);
			
		}
		else
		{
			ctx->eval("var " + getId()+";" , m_strFileName, m_lineNo/*, m_node*/);
		}
		LOG4CPLUS_TRACE(log, "." + sessionId, ",set data " << getId() << "=" << getExpr());
		//LOG4CPLUS_TRACE(log,",execute end.");
	}

	bool Data::isEnabledCondition(fsm::Context * ctx) const
	{
		return true;
	}
}
}

