#include "Log.h"
#include <xmlHelper.h>
using namespace fsm::xmlHelper;
namespace fsm{
namespace model{
	Log::Log(xmlNodePtr xNode):node(xNode){
		m_strExpr =  getXmlNodeAttributesValue(node,"expr");
		m_strLevel = getXmlNodeAttributesValue(node,"level");
	}
	void Log::execute(Evaluator * evl,Context * ctx)
	{
		m_strExpr = evl->eval(ctx,m_strExpr,node->line);
	}
	std::string & Log::getExpr()
	{
		return m_strExpr;
	}
	std::string & Log::getLevel()
	{
		return m_strLevel;
	}
}
}
