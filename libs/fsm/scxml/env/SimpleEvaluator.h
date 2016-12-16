#pragma once
#ifndef _SCXML_ENV_SIMPLEEVALUATOR_HEADER_
#define _SCXML_ENV_SIMPLEEVALUATOR_HEADER_
#include "../Evaluator.h"


namespace fsm
{
namespace env
{
	class  SimpleEvaluator : public Evaluator
	{

	private:
			static const std::string ERR_CTX_TYPE;
	public:

		SimpleEvaluator(); 
		virtual ~SimpleEvaluator();

	
		virtual Context * newContext(const std::string &sessionid, Context *const parent) override;
		virtual void deleteContext(Context * const cx) override;
		virtual bool hasContext() override;

	};
}
}
#endif //end Simple evaluator head