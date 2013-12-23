#include "JSContext.h"
#include <sstream>
#include <log4cplus/loggingmacros.h>
#include "JSGlobalClass.h"
#include <jsdbgapi.h>


namespace fsm
{
namespace env
{
	unsigned long JsContext::StackChunkSize = 8*1024;
	size_t JsContext::gMaxStackSize = DEFAULT_MAX_STACK_SIZE;
	size_t JsContext::gScriptStackQuota = JS_DEFAULT_SCRIPT_STACK_QUOTA;

	JsContext::JsContext(::JSRuntime * rt,Context *const _parent):Context(_parent),
		JSrt(rt),ar(NULL),ctx(NULL),global_obj(NULL)
	{
		log = log4cplus::Logger::getInstance("JsContext");
		LOG4CPLUS_DEBUG(log,  "new a fsm.env.JsContext object:" << this << " parent:" << parent);
		InitializeInstanceFields();
		LOG4CPLUS_DEBUG(log, "new a SpiderMonkey JSContext.");
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
			return eval(vars[name],"",0);
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
		LOG4CPLUS_DEBUG(log, "reset ");
		for (std::map<std::string,std::string>::const_iterator iter = vars.begin();
			iter != vars.end(); iter++)
		{
			std::string expr = "delete ";
			expr.append(iter->first);
			expr.append(";");
			JSBool status = JS_EvaluateScript(ctx,global_obj , expr.c_str(), expr.length(), NULL, 0, NULL); 
			if (status != JS_TRUE)
				LOG4CPLUS_ERROR(log, "delete variable " << iter->first << " failed.");
			else
				LOG4CPLUS_TRACE(log, "delete Variable " << iter->first << " ok." );
		}
		vars.clear();
	}

	Context *JsContext::getParent()
	{
		LOG4CPLUS_DEBUG(log, "getParent:" << parent);
		return parent;
	}

	std::map<std::string,std::string> & JsContext::getVars(){
		return this->vars;
	}

	void JsContext::setVars(const std::map<std::string,std::string> &varMap)
	{
		for (std::map<std::string,std::string>::const_iterator iter = varMap.begin();
			iter != varMap.end(); iter++)
		{
			//LOG4CPLUS_TRACE(log,"setVars set a var name:"<<iter->first << ",value:"<<iter->second);
			setLocal(iter->first,iter->second);
		}
	}
	void JsContext::setLocal(const std::string &name, const std::string & value,bool isDelete)
	{
		std::string expr = name + "=" + (value.empty()? "''":value) + ";";
		JSBool status = JS_EvaluateScript(ctx,global_obj , expr.c_str(), expr.length(), NULL, 0, NULL); 
		if (status != JS_TRUE)
			LOG4CPLUS_ERROR(log, "set variable " << name << " failed.");
		else
			LOG4CPLUS_DEBUG(log, "set Variable " << name << "=" << value );
		if(isDelete)vars[name] = value;
	}


	std::string JsContext::eval(const std::string &expr,const std::string &filename, unsigned int line)
	{
		try
		{
			JSAutoEnterCompartment ac;
			if (!ac.enter(ctx, global_obj)){
				LOG4CPLUS_ERROR(log,"JSAutoEnterCompartment enter error.");
				return "";
			}

			jsval rval; 
			//JS_AddValueRoot(jsctx->ctx,&rval);
			JSBool status = JS_EvaluateScript(ctx,global_obj , expr.c_str(), expr.length(), filename.c_str(), line, &rval); 

			std::stringstream ss;

			if (status == JS_TRUE && !JSVAL_IS_VOID(rval) && !JSVAL_IS_NULL(rval)){ 
				
				JSString * str = JS_ValueToString(ctx,rval);
				if (!str)
					return ss.str();

				char * bytes = NULL;
				bytes = JS_EncodeString(ctx, str);
				if (!bytes)
					return ss.str();
				ss << bytes;
				JS_free(ctx, bytes);
			}
			//JS_RemoveValueRoot(jsctx->ctx,&rval);

			return ss.str();
		}
		catch(std::exception &e)
		{
			LOG4CPLUS_ERROR(log, "error:" <<e.what());
		}
		catch(...)
		{
			LOG4CPLUS_ERROR(log, "unknown error.");
		}
		return "";
	}

	bool JsContext::evalCond(const std::string &expr,const std::string &filename, unsigned int line)
	{
		try
		{
			jsval rval; 
			JSAutoEnterCompartment ac;
			if (!ac.enter(ctx, global_obj)){
				LOG4CPLUS_ERROR(log,"JSAutoEnterCompartment enter error.");
				return true;
			}

			JSBool status = JS_EvaluateScript(ctx,global_obj , expr.c_str(), expr.length(), filename.c_str(), line, &rval); 

			//JSString *jsstr =NULL;
			if (status == JS_TRUE && JSVAL_IS_BOOLEAN(rval)){ 
				return JSVAL_TO_BOOLEAN(rval) == JS_TRUE;
			} 

			return false;
		}
		catch(std::exception &e)
		{
			LOG4CPLUS_ERROR(log, "error:" << e.what());
		}
		catch(...)
		{
			LOG4CPLUS_ERROR(log, "unknown error.");
		}
		return true;
	}

	xmlNodePtr JsContext::evalLocation(const std::string &expr, const std::string & filename, unsigned int line)
	{
		if (expr == "")
		{
			return NULL;
		}
		return NULL;
	}

	void JsContext::InitializeInstanceFields()
	{
		ctx = JS_NewContext(JSrt,StackChunkSize);
		if (ctx == NULL){
			LOG4CPLUS_ERROR(log,"JS_NewContext error.");
			return ;
		}
		JS_SetErrorReporter(ctx, reportError);
		JS_SetVersion(ctx, JSVERSION_LATEST);

		JS_SetNativeStackQuota(ctx, gMaxStackSize);
		JS_SetScriptStackQuota(ctx, gScriptStackQuota);
		JS_SetOperationCallback(ctx, ShellOperationCallback);
		JS_ToggleOptions(ctx, JSOPTION_JIT);
		JS_ToggleOptions(ctx, JSOPTION_METHODJIT);

		JS_SetOptions(ctx,JS_GetOptions(ctx) | JSOPTION_ANONFUNFIX);
		//LOG4CPLUS_DEBUG(log, "set JSContext options:JSOPTION_VAROBJFIX" );

		JS_SetGCParameterForThread(ctx, JSGC_MAX_CODE_CACHE_BYTES, 16 * 1024 * 1024);

		ar =new JSAutoRequest(this->ctx);
		if (!ar){
			LOG4CPLUS_ERROR(log, " new the  JSContext AutoRequest failed." );
			return;
		}

		this->global_obj = JS_NewCompartmentAndGlobalObject(this->ctx, &JsGlobal::global_class,NULL);
		if (global_obj == NULL){
			LOG4CPLUS_ERROR(log, "JS_NewCompartmentAndGlobalObject error.");
			return ;
		}

		
		//RootedObject glob(this->ctx,global);

		JSAutoEnterCompartment ac;
		if (ac.enter(ctx, global_obj)){
			//LOG4CPLUS_TRACE(log," new the  JSAutoCompartment ok." );
		}else{
			LOG4CPLUS_ERROR(log, " new the  JSAutoCompartment failed." );
			return;
		}

		if (!JS_InitStandardClasses(this->ctx, global_obj))
		{
			LOG4CPLUS_ERROR(log, "JS_InitStandardClasses error.");
			return ;
		}else{
			LOG4CPLUS_TRACE(log, "JS_InitStandardClasses ok.");
		}

		
		if (!JS::RegisterPerfMeasurement(ctx, global_obj))
			return ;
		//if(!JS_DefineProperties(ctx,global_obj,JsGlobal::global_Properties)){
		//	LOG4CPLUS_ERROR(log, "global_DefineProperties error.");
		//	return ;
		//}else{
		//	LOG4CPLUS_DEBUG(log, "global_DefineProperties sucessed.");
		//}

		if(!JS_DefineFunctions(this->ctx,global_obj,JsGlobal::global_functions) ||
			!JS_DefineProfilingFunctions(ctx, global_obj)){
			LOG4CPLUS_ERROR(log, "global_DefineFunctions error.");
			return ;
		}else{
			LOG4CPLUS_DEBUG(log, "global_DefineFunctions sucessed.");
		}

		//if (!JS_DefineProperty(ctx, global_obj, "sessionid", JSVAL_VOID, JsGlobal::global_getter,
		//	JsGlobal::global_setter, JSPROP_READONLY | JSPROP_ENUMERATE | JSPROP_PERMANENT)){

		//		LOG4CPLUS_ERROR(log,"define global property sessionid failed.");
		//}

		//if (!JS_DefineProperty(ctx, global_obj, "serviceid", JSVAL_VOID, JsGlobal::global_getter,
		//	JsGlobal::global_setter, JSPROP_READONLY | JSPROP_ENUMERATE | JSPROP_PERMANENT)){

		//		LOG4CPLUS_ERROR(log,"define global property serviceid failed.");
		//}
		JS_WrapObject(ctx, &global_obj);
		
		JS_SetGlobalObject(this->ctx, global_obj);
		//LOG4CPLUS_DEBUG(log, " JS_SetGlobalObject." );

		//if(!JS_InitCTypesClass(ctx, global_obj)){
		//	LOG4CPLUS_ERROR(log, "JS_InitCTypesClass error.");
		//	return ;
		//}else{
		//	LOG4CPLUS_TRACE(log, "JS_InitCTypesClass ok.");
		//}
		
		
	}

	void JsContext::SetContextPrivate(void *data)
	{
		return JS_SetContextPrivate(ctx,data);
	}

	JSObject * JsContext::JSDefineObject (const char * name, JSClass * clasp)
	{
		LOG4CPLUS_DEBUG(log, "JSDefineObject object:"  << name);
		return JS_DefineObject(ctx,global_obj,name,clasp,NULL,0);		
	}

	bool JsContext::JSDefineProperties (JSObject *obj,  JSPropertySpec *ps)
	{
		if (obj){
			LOG4CPLUS_DEBUG(log, "JSDefineProperties to the object.");
			return JS_DefineProperties(ctx,obj,ps) == 0 ? false:true;
		}
		else{
			LOG4CPLUS_DEBUG(log, "JSDefineProperties to global object.");
			return JS_DefineProperties(ctx,global_obj,ps) == 0 ? false:true;
		}
	}

	bool JsContext::CompileScript(const std::string script,const std::string &filename, unsigned int line)
	{
		LOG4CPLUS_DEBUG(log, "CompileScript:" << script);
		JSBool status = JS_EvaluateScript(ctx,global_obj , script.c_str(), script.length(), filename.c_str(), line, NULL); 
		if (status != JS_TRUE)
			LOG4CPLUS_ERROR(log, "CompileScript:" << script<< " failed");
	
		return true;
	}
	JSBool JsContext::ShellOperationCallback(JSContext *cx)
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.JsConext.ShellOperationCallback");
		LOG4CPLUS_TRACE(log,"do nothing.");
		return JS_FALSE;
	}

	JsContext::~JsContext()
	{
		LOG4CPLUS_DEBUG(log,"destruction a scmxl.env.JsContext object." );
		if (this->ar) delete ar;
		JS_SetContextPrivate(ctx, NULL);
		if (ctx) JS_DestroyContext(ctx);
	}

	void JsContext::reportError(::JSContext *_ctx, const char *message, JSErrorReport *report) {
		static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.JsConext.ErrorReporter");

		std::stringstream ss;
		if (!report) {
			LOG4CPLUS_ERROR(log,message);
			return;
		}
		
		ss <<(report->filename ? report->filename : "<no filename="">")
			<<":line="<< report->lineno;

		if(JSREPORT_IS_WARNING(report->flags))
			ss << (JSREPORT_IS_STRICT(report->flags) ? "strict " : "") << "warning";
		ss << ":";
		std::string prefix = ss.str();
		
		std::string::size_type tmpPos;
		std::string::size_type tmpStartPos = 0;
		std::string strMsg(message);
		/* embedded newlines -- argh! */
		while ((tmpPos = strMsg.find('\n',tmpStartPos)) != std::string::npos) {
			LOG4CPLUS_ERROR(log,prefix << strMsg.substr(tmpStartPos,tmpPos));
			tmpStartPos = ++tmpPos;
		}
		LOG4CPLUS_ERROR(log, prefix << strMsg.substr(tmpStartPos));

		if(report->linebuf){
			/* report->linebuf usually ends with a newline. */
			ss.clear();
			size_t n = strlen(report->linebuf);
			LOG4CPLUS_ERROR(log, prefix << report->linebuf);
			n = report->tokenptr - report->linebuf;
			size_t i,j;
			for (i = j = 0; i < n; i++) {
				if (report->linebuf[i] == '\t') {
					for (size_t k = (j + 8) & ~7; j < k; j++) {
						ss << '.';
					}
					continue;
				}
				ss << '.';
				j++;
			}
			LOG4CPLUS_ERROR(log,ss.str() << "^");
		}

	}

	void JsContext::ReportException(JSContext *cx)
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
