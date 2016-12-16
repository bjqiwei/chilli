#pragma once
#ifndef _FSM_ENV_JSEVALUATOR_HEADER_
#define _FSM_ENV_JSEVALUATOR_HEADER_
#include "../Evaluator.h"
#include <log4cplus/logger.h>


namespace fsm
{
namespace env
{
		

	/// <summary>
	/// Evaluator implementation enabling use of JS expressions 
	/// 
	/// </summary>
	class JSEvaluator : public Evaluator
	{

	private:
			log4cplus::Logger log;
	public:

		JSEvaluator(); 
		virtual ~JSEvaluator();

		virtual Context * newContext(const std::string &sessionid, Context *const parent) override;

		virtual void deleteContext(Context * const cx) override;

		virtual bool hasContext() override;

	};
}
}

#endif //end head file