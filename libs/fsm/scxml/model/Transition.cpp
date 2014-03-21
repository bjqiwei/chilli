#include "Transition.h"
#include "../../xmlHelper.h"


namespace fsm
{
namespace model
{

	Transition::Transition(xmlNodePtr xNode,const std::string &session,const std::string &filename):node(xNode),m_bCond(true),
		m_strSession(session),m_strFilename(filename),cx(NULL)
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
	bool Transition::isEnabledCondition() 
	{
		if (!this->getCond().empty() && cx){
			return cx->evalCond(this->getCond(),m_strFilename,node->line,node);
		}
		return m_bCond;
	}
	void Transition::execute(fsm::Context * ctx)
	{
		cx = ctx;
	}
}
}

