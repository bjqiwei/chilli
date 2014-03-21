#pragma once
#ifndef _SCXML_ENV_SIMPLEEVALUATOR_HEADER_
#define _SCXML_ENV_SIMPLEEVALUATOR_HEADER_
#include "../Evaluator.h"
#include "../Context.h"
#include "SimpleContext.h"
#include <string>
#include <map>
#include <vector>


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

	
		virtual Context * newContext(Context *const parent);

		/// <summary>
		/// Create a new context which is the summation of contexts from the
		/// current state to document root, child has priority over parent
		/// in scoping rules.
		/// </summary>
		/// <param name="nodeCtx"> The JexlContext for this state. </param>
		/// <returns> The effective JexlContext for the path leading up to
		///         document root. </returns>
		virtual void deleteContext(Context * const cx);
		virtual bool hasContext();
	private:
		env::SimpleContext  *getEffectiveContext(env::SimpleContext *const nodeCtx);

	};
}
}
#endif //end Simple evaluator head