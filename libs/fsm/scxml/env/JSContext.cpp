#include "JSContext.h"
#include <sstream>
#include <log4cplus/loggingmacros.h>
#include "JSGlobalClass.h"
#include <jsdbgapi.h>
#include "JSHelper.h"


namespace fsm
{
namespace env
{
	unsigned long JsContext::StackChunkSize = 8*1024;
	size_t JsContext::gMaxStackSize = DEFAULT_MAX_STACK_SIZE;
	size_t JsContext::gScriptStackQuota = JS_DEFAULT_SCRIPT_STACK_QUOTA;
	log4cplus::Logger JsContext::log =  log4cplus::Logger::getInstance("fsm.JsContext");

	JsContext::JsContext(::JSRuntime * rt,Evaluator * eval,Context * _parent):Context(eval,_parent),
		JSrt(rt),ar(NULL),/*ac(NULL),*/ctx(NULL),global(NULL)
	{
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
			return eval(vars[name],"",0,NULL);
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
		//LOG4CPLUS_DEBUG(log, "reset ");

		//js_GetClassObject(ctx,)
		clearVars();

		jsval * rootedVal = (jsval *) JS_GetPrivate(ctx, event);
		if (rootedVal) {
			JS_RemoveValueRoot(ctx, rootedVal);
			JS_SetPrivate(ctx, event, NULL);
			delete[] rootedVal;
		}

		std::map<void*,void*>::iterator it;
		while((it = mapObjectRoot.begin())!= mapObjectRoot.end())
		{
			JSObject ** jsObj = (JSObject **)it->second;
			JS_RemoveObjectRoot(ctx, jsObj);  /* scriptObj becomes unreachable
                                             and will eventually be collected. */
			delete jsObj;
			mapObjectRoot.erase(it);
		}
		
		JS_SetContextPrivate(ctx, NULL);

		JS_MaybeGC(ctx);
	}

	void JsContext::clearVars()
	{
		JSAutoEnterCompartment ac ;
		ac.enter(ctx, global);
		std::string expr;
		for (std::map<std::string,std::string>::const_iterator iter = vars.begin();
			iter != vars.end(); ++iter)
		{
			expr.append(iter->first);
			expr.append("=null;");
		}

		JSBool status = JS_EvaluateScript(ctx,global , expr.c_str(), expr.length(), NULL, 0, NULL); 
		if (status != JS_TRUE)
			LOG4CPLUS_ERROR(log, "set variable " << expr << " failed.");
		else
			LOG4CPLUS_TRACE(log, "set Variable " << expr << " ok." );

		expr = "";
		if (vars.size() > 1000)
		{
			std::map<std::string,std::string>::iterator iter = vars.begin();
			while(iter != vars.end()){
				expr.append("delete ");
				expr.append(iter->first);
				expr.append(";");
				vars.erase(iter);
				iter = vars.begin();
			}
			JSBool status = JS_EvaluateScript(ctx,global , expr.c_str(), expr.length(), NULL, 0, NULL); 
			if (status != JS_TRUE)
				LOG4CPLUS_ERROR(log, "delete variable " << expr << " failed.");
			else
				LOG4CPLUS_TRACE(log, "delete Variable " << expr << " ok." );
			vars.clear();
		}
		
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
		clearVars();
		std::string expr;
		for (std::map<std::string,std::string>::const_iterator iter = varMap.begin();
			iter != varMap.end(); ++iter)
		{
			//LOG4CPLUS_TRACE(log,"setVars set a var name:"<<iter->first << ",value:"<<iter->second);
			expr.append(iter->first);
			expr.append("=");
			expr.append((iter->second.empty()? "null":iter->second));
			expr.append(";");
			vars[iter->first];
		}
		JSBool status = JS_EvaluateScript(ctx,global , expr.c_str(), expr.length(), NULL, 0, NULL); 
		if (status != JS_TRUE)
			LOG4CPLUS_ERROR(log, "set variable " << expr << " failed.");
		//else
		//LOG4CPLUS_DEBUG(log, "set Variable " << name << "=" << value );
	}
	void JsContext::setLocal(const std::string &name, const std::string & value,bool isDelete)
	{
		std::string expr = name + "=" + (value.empty()? "''":value) + ";";
		JSAutoEnterCompartment ac ;
		ac.enter(ctx, global);
		JSBool status = JS_EvaluateScript(ctx,global , expr.c_str(), expr.length(), NULL, 0, NULL); 
		if (status != JS_TRUE)
			LOG4CPLUS_ERROR(log, "set variable " << name << " failed.");
		else
			LOG4CPLUS_DEBUG(log, "set Variable " << name << "=" << value );
		if(isDelete)vars[name];
	}


	std::string JsContext::eval(const std::string &expr,const std::string &filename, unsigned int line,void *xmlNode)
	{
		//JS_DumpNamedRoots(JS_GetRuntime(ctx), JsGlobal::dumpRoot, NULL);
		
		try
		{
			jsval rval; 
			//JS_AddValueRoot(jsctx->ctx,&rval);
			JSAutoEnterCompartment ac ;
			ac.enter(ctx, global);

			JSBool status;
			JSObject * scriptObj = getScriptObject(expr,filename,line,xmlNode);
			if (scriptObj == NULL)
			{
				status = JS_EvaluateScript(ctx,global , expr.c_str(), expr.length(), filename.c_str(), line, &rval); 
			}else{
				status = JS_ExecuteScript(ctx,global ,scriptObj , &rval); 
			}

			std::stringstream ss;

			if (status == JS_TRUE && !JSVAL_IS_VOID(rval) && !JSVAL_IS_NULL(rval)){ 
				
				fsm::env::Js::ToString valueString(ctx,rval);
				ss << valueString.getBytes();
			
			}
			//JS_RemoveValueRoot(jsctx->ctx,&rval);
			//JS_MaybeGC(ctx);
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

	bool JsContext::evalCond(const std::string &expr,const std::string &filename, unsigned int line,void *xmlNode)
	{
		try
		{
			jsval rval; 
			JSBool status;

			JSAutoEnterCompartment ac ;
			ac.enter(ctx, global);

			JSObject * scriptObj = getScriptObject(expr,filename,line,xmlNode);
			if (scriptObj == NULL)
			{
				status = JS_EvaluateScript(ctx,global , expr.c_str(), expr.length(), filename.c_str(), line, &rval); 
			}else{
				status = JS_ExecuteScript(ctx,global ,scriptObj , &rval); 
			}
			
			//JS_MaybeGC(ctx);
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

	xmlNodePtr JsContext::evalLocation(const std::string &expr, const std::string & filename, unsigned int line,void *xmlNode)
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

		//JS_SetNativeStackQuota(ctx, gMaxStackSize);
		//JS_SetScriptStackQuota(ctx, gScriptStackQuota);
		//JS_SetOperationCallback(ctx, ShellOperationCallback);
		//JS_ToggleOptions(ctx, JSOPTION_JIT);
		//JS_ToggleOptions(ctx, JSOPTION_METHODJIT);

		JS_SetOptions(ctx,JSOPTION_VAROBJFIX);
		//LOG4CPLUS_DEBUG(log, "set JSContext options:JSOPTION_VAROBJFIX" );

		//JS_SetGCParameterForThread(ctx, JSGC_MAX_CODE_CACHE_BYTES, 16 * 1024 * 1024);

		ar =new JSAutoRequest(this->ctx);
		if (!ar){
			LOG4CPLUS_ERROR(log, " new the  JSContext AutoRequest failed." );
			return;
		}

		this->global = JS_NewCompartmentAndGlobalObject(this->ctx, &JsGlobal::global_class,NULL);
		//this->global = JS_NewGlobalObject(this->ctx,&JsGlobal::global_class);
		if (global == NULL){
			LOG4CPLUS_ERROR(log, "JS_NewCompartmentAndGlobalObject error.");
			return ;
		}

		
		//RootedObject glob(this->ctx,global);

		JSAutoEnterCompartment ac ;
		if (ac.enter(ctx, global)){
			LOG4CPLUS_TRACE(log," new the  JSAutoCompartment ok." );
		}else{
			LOG4CPLUS_ERROR(log, " new the  JSAutoCompartment failed." );
			return;
		}

		JS_SetGlobalObject(this->ctx, global);

		if (!JS_InitStandardClasses(this->ctx, global))
		{
			LOG4CPLUS_ERROR(log, "JS_InitStandardClasses error.");
			return ;
		}else{
			LOG4CPLUS_TRACE(log, "JS_InitStandardClasses ok.");
		}

		
		if (!JS::RegisterPerfMeasurement(ctx, global))
			return ;
		//if(!JS_DefineProperties(ctx,global_obj,JsGlobal::global_Properties)){
		//	LOG4CPLUS_ERROR(log, "global_DefineProperties error.");
		//	return ;
		//}else{
		//	LOG4CPLUS_DEBUG(log, "global_DefineProperties sucessed.");
		//}

		/*if(!JS_DefineFunctions(this->ctx,global,JsGlobal::global_functions) ||
			!JS_DefineProfilingFunctions(ctx, global)){
			LOG4CPLUS_ERROR(log, "global_DefineFunctions error.");
			return ;
		}else{
			LOG4CPLUS_DEBUG(log, "global_DefineFunctions sucessed.");
		}*/

		//if (!JS_DefineProperty(ctx, global_obj, "sessionid", JSVAL_VOID, JsGlobal::global_getter,
		//	JsGlobal::global_setter, JSPROP_READONLY | JSPROP_ENUMERATE | JSPROP_PERMANENT)){

		//		LOG4CPLUS_ERROR(log,"define global property sessionid failed.");
		//}

		//if (!JS_DefineProperty(ctx, global_obj, "serviceid", JSVAL_VOID, JsGlobal::global_getter,
		//	JsGlobal::global_setter, JSPROP_READONLY | JSPROP_ENUMERATE | JSPROP_PERMANENT)){

		//		LOG4CPLUS_ERROR(log,"define global property serviceid failed.");
		//}
		JS_WrapObject(ctx, &global);
		
		//LOG4CPLUS_DEBUG(log, " JS_SetGlobalObject." );

		//if(!JS_InitCTypesClass(ctx, global_obj)){
		//	LOG4CPLUS_ERROR(log, "JS_InitCTypesClass error.");
		//	return ;
		//}else{
		//	LOG4CPLUS_TRACE(log, "JS_InitCTypesClass ok.");
		//}
		/*实例化_event对象*/
		LOG4CPLUS_DEBUG(log, "JSDefineObject object:_event" );
		event = JS_DefineObject(ctx,global,"_event",&JsGlobal::_eventClass,NULL,0);	

		/*创建对象的属性*/
		LOG4CPLUS_DEBUG(log, "JSDefineProperties to the object.");
		JS_DefineProperties(ctx,event,JsGlobal::_eventProperties);
		
	}

	void JsContext::SetContextPrivate(void *data)
	{
		return JS_SetContextPrivate(ctx,data);
	}

	
	bool JsContext::CompileScript(const std::string &script,const std::string &filename, unsigned int line,void *xmlNode)
	{
		LOG4CPLUS_DEBUG(log, "CompileScript:" << script);
		JSBool status;

		JSAutoEnterCompartment ac ;
		ac.enter(ctx, global);

		JSObject * scriptObj = getScriptObject(script,filename,line,xmlNode);
		if (scriptObj == NULL)
		{
			status = JS_EvaluateScript(ctx,global , script.c_str(), script.length(), filename.c_str(), line, NULL); 
		}else{
			status = JS_ExecuteScript(ctx,global ,scriptObj , NULL); 
		}
		
		if (status != JS_TRUE)
			LOG4CPLUS_ERROR(log, "CompileScript:" << script<< " failed");
		//JS_MaybeGC(ctx);
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
		LOG4CPLUS_DEBUG(log,"destruction... a scmxl.env.JsContext object." );
		clearVars();
		reset();
		//if(this->ac) delete ac;
		if (this->ar) delete ar;
		
		LOG4CPLUS_DEBUG(log,"Destroy SpiderMonkey Context." );
		if (ctx) JS_DestroyContext(ctx);
		LOG4CPLUS_DEBUG(log,"destructioned a scmxl.env.JsContext object." );
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
			size_t n ;//= strlen(report->linebuf);
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
	JSObject * JsContext::getScriptObject(const std::string &expr,const std::string &filename, unsigned int line,void *xmlNode)
	{

		//return NULL;
		if (xmlNode == NULL) return NULL;
		typedef struct JSObject*    JSObjectPtr;
		std::map<void *,void*>::iterator it = mapObjectRoot.find(xmlNode);
		if (it != mapObjectRoot.end())
		{
			JSObjectPtr *scriptObj = (JSObjectPtr*)it->second;
			return *scriptObj;
		}
		JSObjectPtr * scriptObj = new (JSObjectPtr);
		JSAutoEnterCompartment ac ;
		ac.enter(ctx, global);
		*scriptObj = JS_CompileScript(ctx,global , expr.c_str(), expr.length(), filename.c_str(), line);
		if (*scriptObj == NULL){
			delete scriptObj;
			return NULL;   /* compilation error */
		}

		if (!JS_AddNamedObjectRoot(ctx, scriptObj, "compileAndRepeat script object"))
			return NULL;
		mapObjectRoot[xmlNode]=(void *)scriptObj;
		return *scriptObj;

	}
	void JsContext::ExecuteFile(const std::string &fileName)
	{
		JSAutoEnterCompartment ac ;
		ac.enter(ctx, global);
		uint32 oldopts = JS_GetOptions(ctx);
		JS_SetOptions(ctx, oldopts | JSOPTION_COMPILE_N_GO | JSOPTION_NO_SCRIPT_RVAL);
		JSObject * obj = JS_CompileFile(ctx,global,fileName.c_str());
		JS_SetOptions(ctx, oldopts);
		if (obj)
		{
			JS_ExecuteScript(ctx,global,obj,NULL);
		}
		
	}
}
}
