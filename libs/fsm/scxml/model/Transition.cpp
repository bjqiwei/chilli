#include "Transition.h"


namespace fsm
{
namespace model
{

	Transition::Transition(const std::string &filename, uint32_t lineno)
		:Action(filename,lineno)
	{

	}


	const std::string &Transition::getTarget()const
	{
		return m_strTarget;
	}

	void Transition::setTarget(const std::string & target)
	{
		this->m_strTarget = target;
	}

	void Transition::execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId)const
	{
	}
}
}

