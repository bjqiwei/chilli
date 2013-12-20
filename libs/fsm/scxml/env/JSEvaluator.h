#pragma once
#ifndef _FSM_ENV_JSEVALUATOR_HEADER_
#define _FSM_ENV_JSEVALUATOR_HEADER_
#include "../Evaluator.h"
#include "../Context.h"
#include "JSContext.h"
#include <jsapi.h>
#include <string>
#include <map>
#include <vector>
#include <log4cplus/logger.h>


namespace fsm
{
namespace env
{
		

	/// <summary>
	/// Evaluator implementation enabling use of JS expressions 
	/// 
	/// </summary>
	class FSM_EXPORT JSEvaluator : public Evaluator
	{

	private:
			static const std::string ERR_CTX_TYPE;
			JSRuntime *rt;
			log4cplus::Logger log;
	public:

		JSEvaluator(); 
		virtual ~JSEvaluator();

		/// <summary>
		/// Evaluate an expression.
		/// </summary>
		/// <param name="ctx"> variable context </param>
		/// <param name="expr"> expression </param>
		/// <returns> a result of the evaluation </returns>
		/// <exception cref="SCXMLExpressionException"> For a malformed expression </exception>
		/*virtual std::string eval(Context *const ctx, const std::string &expr,const std::string &filename, unsigned int line);


		virtual bool evalCond(Context *const ctx, const std::string &expr,const std::string &filename, unsigned int line);

		/// <seealso cref= Evaluator#evalLocation(Context, String) </seealso>
		virtual xmlNodePtr evalLocation(Context *const ctx, const std::string &expr, const std::string &filename, unsigned int line);
*/
		/// <summary>
		/// Create a new child context.
		/// </summary>
		/// <param name="parent"> parent context </param>
		/// <returns> new child context </returns>
		/// <seealso cref= Evaluator#newContext(Context) </seealso>
		virtual Context * newContext(Context *const parent);
		/// <summary>
		/// Create a new context which is the summation of contexts from the
		/// current state to document root, child has priority over parent
		/// in scoping rules.
		/// </summary>
		/// <param name="nodeCtx"> The JexlContext for this state. </param>
		/// <returns> The effective JexlContext for the path leading up to
		///         document root. </returns>
	private:
		Context  *getEffectiveContext(Context *const nodeCtx);

	};
}
}

#endif //end head file