#pragma once
#include "../Context.h"
#include <log4cplus/logger.h>
#include "Action.h"

namespace fsm
{
namespace model
{

	class Event
	{

	private:
		std::string m_strCond;
		std::string m_strEvent;
		std::string m_strFilename;
		uint32_t m_lineNo;
		
	public:
		Event(const std::string &filename, uint32_t lineno);

		const std::string &getEvent() const;
		void setEvent(const std::string & event);
		void setCond(const std::string & cond) { m_strCond = cond; }
		const std::string &getCond() const { return this->m_strCond; }
		uint32_t getLineNo() const { return m_lineNo; }

		bool isEnabledEvent(const std::string& strEventName, const log4cplus::Logger & log, const std::string & sessionId) const ;
		bool isEnabledCondition(fsm::Context * ctx);

		std::vector<std::shared_ptr<Action>> m_Actions;
		void addAction(std::shared_ptr<Action> actionptr);

	};
}
}