#include "Transition.h"
#include "../../common/xmlHelper.h"


namespace fsm
{
namespace model
{

	Transition::Transition(xmlNodePtr xNode,const std::string &session,const std::string &filename)
		:Action(xNode, session, filename)
	{
		log = log4cplus::Logger::getInstance("fsm.model.Transition");
		m_strTarget = helper::xml::getXmlNodeAttributesValue(m_node,"target");
	}


	const std::string &Transition::getTarget()const
	{
		return m_strTarget;
	}

	void Transition::execute(fsm::Context * ctx)
	{
	}
}
}

