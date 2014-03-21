#include "SimpleEvaluator.h"


namespace fsm
{
namespace env
{


	const std::string SimpleEvaluator::ERR_CTX_TYPE = "Error evaluating Simple expression.";
	
	SimpleEvaluator::SimpleEvaluator()
	{
	}
	SimpleEvaluator::~SimpleEvaluator(){
		while(!contexts.empty())
		{
			delete contexts.front();
			contexts.pop_front();
		}
	}


	Context * SimpleEvaluator::newContext(Context *const parent)
	{
		Context * cx = new SimpleContext(parent);
		contexts.push_back(cx);
		return cx;
	}

	void SimpleEvaluator::deleteContext(Context * const cx){
		contexts.remove(cx);
		delete cx;
	}

	bool SimpleEvaluator::hasContext()
	{
		return true;
	}

	env::SimpleContext  *getEffectiveContext(env::SimpleContext *const nodeCtx)
	{
		return NULL;
	}
}
}
