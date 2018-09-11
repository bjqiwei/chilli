#pragma once
#include "../Context.h"
#include <string>
#include <log4cplus/logger.h>

namespace fsm
{
namespace model
{
	/// <summary>
	/// An abstract base class for executable elements in FSM,
	/// such as log¡¢script etc.
	/// 
	/// </summary>
	class  Action 
	{

		/// <summary>
		/// Constructor.
		/// </summary>
	public:

		Action(const std::string &filename, uint32_t lineno):m_strFileName(filename), m_lineNo(lineno), m_bCond(true)
		{
		}; //super();
		virtual~Action(){};
		virtual void execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId) const = 0;
		virtual bool isEnabledCondition(fsm::Context * ctx) const
		{
			if (!this->getCond().empty() && ctx){
				return ctx->evalCond(this->getCond(), m_strFileName, m_lineNo);
			}
			return m_bCond;
		}

		void setCond(const std::string & cond) { m_strCond = cond; }
		const std::string &getCond() const { return this->m_strCond; }
		uint32_t getLineNo()const { return this->m_lineNo; }

	protected:
		std::string m_strCond;
		std::string m_strFileName;
		uint32_t m_lineNo;
	private:
		bool m_bCond;

	};
}
}
