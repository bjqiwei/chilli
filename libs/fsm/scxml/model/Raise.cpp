#include "Raise.h"

namespace fsm{
namespace model {
	Raise::Raise(const std::string &filename, uint32_t lineno)
		:Action(filename, lineno)
	{

	}


	Raise::~Raise(void)
	{
	}

	const std::string &Raise::getEvent()const
	{
		return m_strEvent;
	}

	void Raise::setEvent(const std::string & event)
	{
		this->m_strEvent = event;
	}

	void Raise::execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId)const
	{
	}
}
}
