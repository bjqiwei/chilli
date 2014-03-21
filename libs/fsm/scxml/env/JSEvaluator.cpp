#include "JSEvaluator.h"
#include <sstream>
#include <stdexcept>
#include <log4cplus/loggingmacros.h>


namespace fsm
{
namespace env
{
#define  CONTEXT_SIZE 1000

	const std::string JSEvaluator::ERR_CTX_TYPE = "Error evaluating JS expression, Context Is SpiderMonkey context.";
	
	JSEvaluator::JSEvaluator():rt(NULL)
	{
		log = log4cplus::Logger::getInstance("fsm.JSEvaluator");
		this->rt = JS_NewRuntime(160L*1024L*1024L);
		if ( rt == NULL ){
			LOG4CPLUS_ERROR(log, "new evaluator runtime error.");
			throw std::logic_error("new evaluator runtime error.");
		}
		LOG4CPLUS_DEBUG(log,"construct a JSEvaluator object.");

	}
	JSEvaluator::~JSEvaluator(){
		LOG4CPLUS_DEBUG(log,"deconstruct a JSEvaluator object.");
		while(!contexts.empty())
		{
			LOG4CPLUS_DEBUG(log,"contexts size " << contexts.size());
			delete contexts.front();
			contexts.pop_front();
		}
		if(rt) JS_DestroyRuntime(rt);
		//JS_ShutDown();
	}


	Context * JSEvaluator::newContext(Context *const parent)
	{
		LOG4CPLUS_DEBUG(log,"new a JsContext,parent="<< parent);
		if (contexts.size() >= CONTEXT_SIZE)
		{
			LOG4CPLUS_WARN(log,"already has " << CONTEXT_SIZE << "context, return NULL.");
			return NULL;
		}

		Context * cx = new env::JsContext(rt,this,parent);
		contexts.push_back(cx);
		LOG4CPLUS_WARN(log,"contexts size " << contexts.size());
		return cx;

	}
	void JSEvaluator::deleteContext(Context * const cx)
	{
		contexts.remove(cx);
		delete cx;
	}

	bool JSEvaluator::hasContext()
	{
		return contexts.size() < CONTEXT_SIZE;
	}

	Context  *getEffectiveContext(Context *const nodeCtx)
	{
		return NULL;
	}
}
}
