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
