#include "Event.h"
#include <regex>
#include <log4cplus/loggingmacros.h>

namespace fsm
{
namespace model
{

	Event::Event(const std::string &filename, uint32_t lineno) :m_strFilename(filename), m_lineNo(lineno)
	{
	}

	const std::string &Event::getEvent()const
	{
		return m_strEvent ;
	}

	void Event::setEvent(const std::string & event)
	{
		this->m_strEvent = event;
	}
	

	bool Event::isEnabledEvent(const std::string& strEventName, const log4cplus::Logger & log, const std::string & sessionId) const
	{
		
		if (m_strEvent.empty()) {

		} else {
			try
			{
				std::regex regPattern(m_strEvent);
				if (!std::regex_match(strEventName, regPattern))
				{
					return false;
				}
			}
			catch (std::exception * e)
			{
				LOG4CPLUS_ERROR(log, "." + sessionId, m_strFilename << ":" << m_lineNo << " " << e->what());
				throw *e;
			}
		}
		return true;
	}

	bool Event::isEnabledCondition(fsm::Context * ctx)
	{
		if (!this->getCond().empty() && ctx) {
			return ctx->evalCond(this->getCond(), m_strFilename, m_lineNo);
		}
		return true;
	}

	void Event::addAction(std::shared_ptr<Action> actionptr)
	{
		this->m_Actions.push_back(actionptr);
	}

}
}
