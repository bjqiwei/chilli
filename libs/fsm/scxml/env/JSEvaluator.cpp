#include "JSEvaluator.h"
#include <sstream>
#include <stdexcept>
#include <log4cplus/loggingmacros.h>


namespace fsm
{
namespace env
{

	const std::string JSEvaluator::ERR_CTX_TYPE = "Error evaluating JS expression, Context Is SpiderMonkey context.";
	
	JSEvaluator::JSEvaluator():rt(NULL)
	{
		log = log4cplus::Logger::getInstance("JSEvaluator");
		this->rt = JS_NewRuntime(160L*1024L*1024L);
		if ( rt == NULL ){
			LOG4CPLUS_ERROR(log, "new evaluator runtime error.");
			throw std::logic_error("new evaluator runtime error.");
		}
		LOG4CPLUS_DEBUG(log,"construct a JSEvaluator object.");

	}
	JSEvaluator::~JSEvaluator(){
		LOG4CPLUS_DEBUG(log,"deconstruct a JSEvaluator object.");
		if(rt) JS_DestroyRuntime(rt);
		//JS_ShutDown();
	}


	Context * JSEvaluator::newContext(Context *const parent)
	{
		LOG4CPLUS_DEBUG(log,"new a JsContext,parent="<< parent);
		if (parent)
		{
			return new env::JsContext(rt,parent);
		}
		return new env::JsContext(rt);
	}

	Context  *getEffectiveContext(Context *const nodeCtx)
	{
		return NULL;
	}
}
}
