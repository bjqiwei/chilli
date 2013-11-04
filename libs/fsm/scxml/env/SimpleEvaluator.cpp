#include "SimpleEvaluator.h"


namespace fsm
{
namespace env
{


	const std::string SimpleEvaluator::ERR_CTX_TYPE = "Error evaluating Simple expression.";
	
	SimpleEvaluator::SimpleEvaluator()
	{
	}
	SimpleEvaluator::~SimpleEvaluator(){}

	std::string SimpleEvaluator::eval(Context *const ctx, const std::string &expr)
	{
		if (expr == "" || !ctx)
		{
			return "";
		}
		return ctx->get(expr);
		
	}

	bool SimpleEvaluator::evalCond(Context *const ctx, const std::string &expr) 
	{
		if (expr == "")
		{
			return false;
		}
		if(ctx->get(expr).compare("0") ==0)
			return false;
		return true;
	}

	xmlNodePtr SimpleEvaluator::evalLocation(Context *const ctx, const std::string &expr)
	{
		if (expr == "")
		{
			return NULL;
		}
		return NULL;
	}

	Context * SimpleEvaluator::newContext(Context *const parent)
	{
		return new SimpleContext(parent);
	}

	env::SimpleContext  *getEffectiveContext(env::SimpleContext *const nodeCtx)
	{
		return NULL;
	}
}
}
