#include "Transition.h"
#include "../../common/xmlHelper.h"


namespace fsm
{
namespace model
{

	Transition::Transition(xmlNodePtr xNode,const std::string &session,const std::string &filename):node(xNode),m_bCond(true),
		m_strSession(session),m_strFilename(filename),cx(NULL)
	{
		log = log4cplus::Logger::getInstance("fsm.model.Transition");
		m_strCond = helper::xml::getXmlNodeAttributesValue(node,"cond");
		m_strTarget = helper::xml::getXmlNodeAttributesValue(node,"target");
	}

	const std::string &Transition::getCond()const
	{
		return m_strCond;
	}
	const std::string &Transition::getTarget()const
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

