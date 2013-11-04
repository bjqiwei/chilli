#include "Transition.h"
#include <xmlHelper.h>


namespace fsm
{
namespace model
{

	Transition::Transition(xmlNodePtr xNode):node(xNode)
	{

		m_strCond = xmlHelper::getXmlNodeAttributesValue(node,"cond");
		m_strTarget = xmlHelper::getXmlNodeAttributesValue(node,"target");
	}

	std::string &Transition::getCond()
	{
		return m_strCond;
	}
	std::string &Transition::getTarget()
	{
		return m_strTarget;
	}
	bool Transition::isEnabledCondition() const
	{
		return m_bCond;
	}
	void Transition::execute(fsm::Evaluator * evl,fsm::Context * ctx)
	{
		m_bCond = evl->evalCond(ctx,this->getCond(),node->line);
	}
}
}

