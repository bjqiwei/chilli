#include "JsContext.h"


namespace fsm
{
namespace env
{
	

	JsContext::JsContext(::JSRuntime * rt,log4cplus::Logger _log):ctx(NULL),JSrt(rt)
		,ac(NULL),ar(NULL),global_obj(NULL)
	{
		log = _log;
		InitializeInstanceFields();
		LOG4CPLUS_DEBUG(log, "new a fsm.env.JsContext object:" << this);
	}

	JsContext::JsContext(::JSRuntime * rt,Context *const parent,log4cplus::Logger _log):
		ctx(NULL),JSrt(rt),ar(NULL),ac(NULL),global_obj(NULL)
	{
		log = _log;
		InitializeInstanceFields();
		LOG4CPLUS_DEBUG(log, "new a fsm.env.JsContext object this:" << this << " parent:" << parent);
		this->parent  =parent;
		
	}

	void JsContext::set(const std::string &name, const std::string &value)
	{
		if (vars.count(name)>0) //first try to override local
		{
			setLocal(name, value);
		} //then check for global
		else if (parent != 0 && parent->has(name))
		{
			parent->set(name, value);
		} //otherwise create a new local variable
		else
		{
			setLocal(name, value);
		}
	}

	std::string JsContext::get(const std::string &name)
	{
		if (vars.count(name)>0)
		{
			return vars[name];
		}
		else if (parent != 0)
		{
			return parent->get(name);
		}
		else
		{
			return "";
		}
	}

	bool JsContext::has(const std::string &name)
	{
		if (vars.count(name)>0)
		{
			return true;
		}
		else if (parent != 0 && parent->has(name))
		{
			return true;
		}
		return false;
	}

	void JsContext::reset()
	{
		LOG4CPLUS_WARN(log, "reset ");
		vars.clear();
	}

	Context *JsContext::getParent()
	{
		LOG4CPLUS_DEBUG(log, "getParent " << parent);
		return parent;
	}

	void JsContext::setLocal(const std::string &name, const std::string & value)
	{
		std::string expr = name + "=" + (value.empty()? "''":value) + ";";
		JSBool status = JS_EvaluateScript(ctx,global_obj , expr.c_str(), expr.length(), NULL, 0, NULL); 
		if (status != JS_TRUE)
			LOG4CPLUS_ERROR(log,"set variable " << name << " failed.");
		LOG4CPLUS_INFO(log, "set Variable " << name << "=" << value << ".");
	}

	void JsContext::setVars(std::map<std::string,std::string>const & vars)
	{
		LOG4CPLUS_INFO(log,"set variable value a map.");
		this->vars = vars;
	}

	std::map<std::string,std::string> & JsContext::getVars()
	{
		LOG4CPLUS_DEBUG(log," get the vars .");
		return vars;
	}

	void JsContext::InitializeInstanceFields()
	{
		ctx = JS_NewContext(JSrt,8L*1024L);
		if (ctx == NULL){
			LOG4CPLUS_ERROR(log,"JS_NewContext error.");
			return ;
		}
		LOG4CPLUS_DEBUG(log,"new a SpiderMonkey JSContext.");
		JS_SetOptions(ctx, JSOPTION_VAROBJFIX);
		LOG4CPLUS_DEBUG(log,"set JSContext options:JSOPTION_VAROBJFIX" );
		JS_SetErrorReporter(ctx, reportError);
		LOG4CPLUS_DEBUG(log,"set JSContext reportError" );

		ar =new JSAutoRequest(this->ctx);
		if (ar){
			LOG4CPLUS_DEBUG(log," new the  JSContext AutoRequest ok." );
		}else{
			LOG4CPLUS_ERROR(log," new the  JSContext AutoRequest failed." );
			return;
		}

		this->global_obj = JS_NewGlobalObject(this->ctx, &global_class,NULL);
		if (global_obj == NULL){
			LOG4CPLUS_ERROR(log,"JS_NewGlobalObject error.");
			return ;
		}else{
			LOG4CPLUS_DEBUG(log,"JS_NewGlobalObject ok.");
		}
		//RootedObject glob(this->ctx,global);

		ac = new JSAutoCompartment(this->ctx,global_obj);
		if (ar){
			LOG4CPLUS_DEBUG(log," new the  JSAutoCompartment ok." );
		}else{
			LOG4CPLUS_ERROR(log," new the  JSAutoCompartment failed." );
			return;
		}

		JS_SetGlobalObject(this->ctx, global_obj);
		LOG4CPLUS_ERROR(log," JS_SetGlobalObject." );
		/* Populate the global object with the standard globals, like Object and Array. */
		if (!JS_InitStandardClasses(this->ctx, global_obj))
		{
			LOG4CPLUS_ERROR(log,"JS_InitStandardClasses error.");
			return ;
		}else{
			LOG4CPLUS_DEBUG(log,"JS_InitStandardClasses ok.");
		}

		if(!JS_DefineFunctions(this->ctx,global_obj,global_functions)){
			LOG4CPLUS_ERROR(log,"JS_DefineFunctions error.");
			return ;
		}else{
			LOG4CPLUS_DEBUG(log,"JS_DefineFunctions sucessed.");
		}
	}

	JSObject * JsContext::JSDefineObject (const char * name, JSClass * clasp)
	{
		LOG4CPLUS_DEBUG(log,"JSDefineObject object:" << name);
		return JS_DefineObject(ctx,global_obj,name,clasp,0,JSPROP_ENUMERATE);		
	}

	bool JsContext::JSDefineProperties (JSObject *obj,  JSPropertySpec *ps)
	{
		if (obj){
			LOG4CPLUS_DEBUG(log,"JSDefineProperties to the object.");
			return JS_DefineProperties(ctx,obj,ps) == 0 ? false:true;
		}
		else{
			LOG4CPLUS_DEBUG(log,"JSDefineProperties to global object.");
			return JS_DefineProperties(ctx,global_obj,ps) == 0 ? false:true;
		}
	}

	bool JsContext::CompileScript(const std::string script)
	{
		LOG4CPLUS_DEBUG(log,"CompileScript:" << script);
		JSBool status = JS_EvaluateScript(ctx,global_obj , script.c_str(), script.length(), NULL, 0, NULL); 
		if (status != JS_TRUE)
			LOG4CPLUS_ERROR(log,"CompileScript:" << script << " failed");
	
		return true;
	}


	void JsContext::reportError(::JSContext *_ctx, const char *message, JSErrorReport *report) {
		log4cplus::Logger log = log4cplus::Logger::getInstance("scxml.SCInstance.JsContext.Error");
		std::stringstream ss;
		ss <<(report->filename ? report->filename : "<no filename="">")
			<<"lineno="<< (unsigned int) report->lineno 
			<<":"<<message;
		LOG4CPLUS_ERROR(log, ss.str().c_str());
	}

	JSClass JsContext::global_class = { "global",
		JSCLASS_NEW_RESOLVE | JSCLASS_GLOBAL_FLAGS,
		JS_PropertyStub,
		JS_DeletePropertyStub,
		JS_PropertyStub,
		JS_StrictPropertyStub,
		JS_EnumerateStub,
		JS_ResolveStub,
		JS_ConvertStub,
		NULL,
		JSCLASS_NO_OPTIONAL_MEMBERS
	};

	JSBool  JsContext::logging(JSContext *context,unsigned int argc, jsval *vp){ 
		log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.env.JsContext.logging");
		JSString *jss; 
		std::stringstream ss;
		//::JS::CallArgs args = CallArgsFromVp(argc, vp);
		jsval *args = JS_ARGV(context,vp);
		for(unsigned i = 0; i < argc; i++){ 
			if(JSVAL_IS_STRING(args[i])){
				jss = JS_ValueToString(context, args[i]); 
				ss << JS_EncodeString(context,jss); 
			}
		} 
		LOG4CPLUS_INFO(log,ss.str().c_str());

		return JS_TRUE; 
	} 

	JSFunctionSpec JsContext::global_functions[] = { 
		JS_FNINFO("logging", JsContext::logging,0, 0, JSPROP_ENUMERATE), 
		JS_FS_END
	}; 

	JsContext::~JsContext()
	{
		LOG4CPLUS_DEBUG(log,"destruction a scmxl.env.JsContext object." );
		if (this->ac) delete ac;
		if (this->ar) delete ar;
		if (ctx) JS_DestroyContext(ctx);
	}

	static void ReportException(JSContext *cx)
	{
		if (JS_IsExceptionPending(cx)) {
			if (!JS_ReportPendingException(cx))
				JS_ClearPendingException(cx);
		}
	}

	/*ToStringHelper::ToStringHelper(JSContext *aCx, js::HandleValue v, bool aThrow)
		: cx(aCx), mStr(cx, JS_ValueToString(cx, v))
	{
		if (!aThrow && !mStr)
			ReportException(cx);
	}
	ToStringHelper::ToStringHelper(JSContext *aCx, js::HandleId id, bool aThrow)
		: cx(aCx), mStr(cx, JS_ValueToString(cx, IdToValue(id)))
	{
		if (!aThrow && !mStr)
			ReportException(cx);
	}
	bool ToStringHelper::threw() { return !mStr; }
	jsval ToStringHelper::getJSVal() { return STRING_TO_JSVAL(mStr); }
	const char *ToStringHelper::getBytes() {
		if (mStr && (mBytes.ptr() || mBytes.encodeLatin1(cx, mStr)))
			return mBytes.ptr();
		return "(error converting value)";
	}*/
}
}
