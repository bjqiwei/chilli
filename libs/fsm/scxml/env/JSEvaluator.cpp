#include "JSEvaluator.h"


namespace fsm
{
namespace env
{

	const std::string JSEvaluator::ERR_CTX_TYPE = "Error evaluating JS expression, Context Is SpiderMonkey context.";
	
	JSEvaluator::JSEvaluator():rt(NULL)
	{
		log = log4cplus::Logger::getInstance("fsm.env.JSEvaluator");

		this->rt = JS_NewRuntime(32L*1024L*1024L,JS_NO_HELPER_THREADS);
		if ( rt == NULL ){
			LOG4CPLUS_ERROR(log,"new evaluator runtime error.");
			throw std::exception("new evaluator runtime error.");
		}

	}
	JSEvaluator::~JSEvaluator(){
		if(rt) JS_DestroyRuntime(rt);
		//JS_ShutDown();
	}

	std::string JSEvaluator::eval(Context *const ctx, const std::string &expr,unsigned int line)
	{

		try
		{
			if (expr == "" || !ctx)
			{
				return "";
			}
			env::JsContext * jsctx = dynamic_cast<env::JsContext *>(ctx);
			if (jsctx == NULL )
			{
				LOG4CPLUS_ERROR(log,"dynamic_cast to JsContext failed.");
				return "";
			}
		
			jsval rval; 
			//JS_AddValueRoot(jsctx->ctx,&rval);
			JSBool status = JS_EvaluateScript(jsctx->ctx,jsctx->global_obj , expr.c_str(), expr.length(), NULL, line, &rval); 
	
			std::stringstream ss;
			
			if (status == JS_TRUE ){ 
				if (JSVAL_IS_STRING(rval))
				{
					JSString *jsstr =NULL;
					jsstr = JSVAL_TO_STRING(rval);
					if (jsstr) ss << JS_EncodeString(jsctx->ctx,jsstr);
				}
				else if (JSVAL_IS_INT(rval))
				{
					ss << JSVAL_TO_INT(rval);
				}
				else if (JSVAL_IS_BOOLEAN(rval))
				{
					ss << JSVAL_TO_BOOLEAN(rval);
				}else if (JSVAL_IS_NUMBER(rval))
				{
					ss << rval.toNumber();
				}
			}
			//JS_RemoveValueRoot(jsctx->ctx,&rval);
			
			return ss.str();
		}
		catch(std::exception &e)
		{
			LOG4CPLUS_ERROR(log,"error:" << e.what());
		}
		catch(...)
		{
			LOG4CPLUS_ERROR(log,"unknown error.");
		}
	}

	bool JSEvaluator::evalCond(Context *const ctx, const std::string &expr,unsigned int line) 
	{
		try
		{
			if (expr == "" || !ctx)
			{
				return "";
			}

			env::JsContext * jsctx = dynamic_cast<env::JsContext *>(ctx);
			if (jsctx == NULL )
			{
				LOG4CPLUS_ERROR(log,"dynamic_cast to JsContext failed.");
				return false;
			}

			jsval rval; 
			

			JSBool status = JS_EvaluateScript(jsctx->ctx,jsctx->global_obj , expr.c_str(), expr.length(), NULL, line, &rval); 

			//JSString *jsstr =NULL;
			if (status == JS_TRUE && JSVAL_IS_BOOLEAN(rval)){ 
				return JSVAL_TO_BOOLEAN(rval) == JS_TRUE;
			} 
			
			return false;
		}
		catch(std::exception &e)
		{
			LOG4CPLUS_ERROR(log,"error:" << e.what());
		}
		catch(...)
		{
			LOG4CPLUS_ERROR(log,"unknown error.");
		}
		return true;
	}

	xmlNodePtr JSEvaluator::evalLocation(Context *const ctx, const std::string &expr,unsigned int line)
	{
		if (expr == "")
		{
			return NULL;
		}
		return NULL;
	}

	Context * JSEvaluator::newContext(Context *const parent,log4cplus::Logger log)
	{
		if (parent)
		{
			return new env::JsContext(rt,parent,log);
		}
		return new env::JsContext(rt,log);
	}

	Context  *getEffectiveContext(Context *const nodeCtx)
	{
		return NULL;
	}
}
}
