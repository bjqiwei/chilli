#include "JSContext.h"
#include <sstream>
#include <log4cplus/loggingmacros.h>
#include <jsdbgapi.h>
#include <jsperf.h>
#include "../../common/stringHelper.h"


namespace fsm
{
namespace env
{

	//global class
	JSClass JsContext::global_class = { 
		"global",JSCLASS_NEW_RESOLVE | JSCLASS_GLOBAL_FLAGS ,
		JS_PropertyStub,JS_PropertyStub,
		JS_PropertyStub,JS_StrictPropertyStub,
		JS_EnumerateStub,JS_ResolveStub,
		JS_ConvertStub,JS_FinalizeStub,
		JSCLASS_NO_OPTIONAL_MEMBERS
	};

	/*定义_event类*/
	JSClass JsContext::_eventClass = {
		"_event",JSCLASS_NEW_RESOLVE | JSCLASS_NEW_ENUMERATE | JSCLASS_HAS_PRIVATE,
		JS_PropertyStub,JS_PropertyStub,
		JS_PropertyStub, JS_StrictPropertyStub,
		JS_EnumerateStub,JS_ResolveStub,
		JS_ConvertStub,JS_FinalizeStub,
		JSCLASS_NO_OPTIONAL_MEMBERS
	};

	static JSBool logging(JSContext *cx,unsigned int argc, jsval *vp){ 
		static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.JsContex.Log");
		uintN i;

		std::stringstream ss;
		//::JS::CallArgs args = CallArgsFromVp(argc, vp);
		jsval *argv = JS_ARGV(cx,vp);
		for (i = 0; i < argc; i++) {
			ToString toString(cx, argv[i]);
			ss << (i ? " " : "") << toString.getBytes();
		}

		LOG4CPLUS_DEBUG(log,ss.str());
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE; 
	}


	unsigned long JsContext::StackChunkSize = 8*1024;
	size_t JsContext::gMaxStackSize = DEFAULT_MAX_STACK_SIZE;
	size_t JsContext::gScriptStackQuota = JS_DEFAULT_SCRIPT_STACK_QUOTA;
	

	JsContext::JsContext(::JSRuntime * rt,Evaluator * eval,Context * _parent):Context(eval,_parent),
		JSrt(rt),ctx(NULL),global(NULL)
	{
		log =  log4cplus::Logger::getInstance("fsm.JsContext");
		LOG4CPLUS_DEBUG(log,  "new a fsm.env.JsContext object:" << this << " parent:" << parent);
		InitializeInstanceFields();
		LOG4CPLUS_DEBUG(log, "new a fsm.env.JsContext object finish.");
	}

	void JsContext::setVar(const std::string & name, const Json::Value & value, ValueContext va )
	{
		JSAutoRequest ar = JSAutoRequest(this->ctx);
		JSAutoEnterCompartment ac ;
		ac.enter(ctx, global);
		jsval val = JsonValueToJsval(value);
		JSObject * obj = (va==fsm::globalObject ? this->global:this->event);

		std::string out2 = value.toStyledString();
		helper::string::trim(out2);
		LOG4CPLUS_TRACE(log, "set "<< (va==fsm::globalObject? "global.":"_event.") << name << "=" << out2);
		if (!JS_DefineProperty(ctx,obj,name.c_str(), val, NULL,NULL, JSPROP_READONLY | JSPROP_ENUMERATE | JSPROP_PERMANENT)){
			LOG4CPLUS_WARN(log,"define global property " << name << " failed.");
		}
	}

	Json::Value JsContext::getVar(const std::string &name, ValueContext va)
	{
		jsval rval; 
		JSAutoRequest ar = JSAutoRequest(this->ctx);
		JSAutoEnterCompartment ac ;
		ac.enter(ctx, global);

		JSBool status;
		JSObject * obj = (va==fsm::globalObject ? this->global:this->event);
		status = JS_EvaluateScript(ctx,obj , name.c_str(), name.length(), NULL, 0, &rval); 
		if (status == JS_TRUE ){ 
			return JsvalToJsonValue(rval);
			
		}
		return Json::Value();
	}
	void JsContext::deleteVar(const std::string & name, ValueContext va)
	{
		JSAutoRequest ar = JSAutoRequest(this->ctx);
		JSAutoEnterCompartment ac ;
		ac.enter(ctx, global);
		JSObject * obj = (va==fsm::globalObject ? this->global:this->event);
		LOG4CPLUS_TRACE(log, "delete "<< (va==fsm::globalObject? "global.":"_event.") << name );
		JS_DefineProperty(ctx,obj,name.c_str(), JSVAL_NULL, NULL,NULL, JSPROP_ENUMERATE );
		if(!JS_DeleteProperty(ctx, obj, name.c_str())){
			LOG4CPLUS_ERROR(log," delete Var failed.");
		}
	
	}

	void JsContext::Reset()
	{
		//LOG4CPLUS_DEBUG(log, "reset ");

		//js_GetClassObject(ctx,)

		/*jsval * rootedVal = (jsval *) JS_GetPrivate(ctx, event);
		if (rootedVal) {
			JS_RemoveValueRoot(ctx, rootedVal);
			JS_SetPrivate(ctx, event, NULL);
			delete[] rootedVal;
		}*/

		std::map<const void*,void*>::iterator it;
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


	
	Context *JsContext::getParent()
	{
		LOG4CPLUS_DEBUG(log, "getParent:" << parent);
		return parent;
	}


	std::string JsContext::eval(const std::string &expr,const std::string &filename, unsigned int line,const void *xmlNode)
	{
		//JS_DumpNamedRoots(JS_GetRuntime(ctx), JsGlobal::dumpRoot, NULL);
		

		jsval rval; 
		JSAutoRequest ar = JSAutoRequest(this->ctx);
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
				
			fsm::env::ToString valueString(ctx,rval);
			ss << valueString.getBytes();
			
		}
		//JS_RemoveValueRoot(jsctx->ctx,&rval);
		//JS_MaybeGC(ctx);
		return ss.str();

	}

	bool JsContext::evalCond(const std::string &expr,const std::string &filename, unsigned int line,const void *xmlNode)
	{

		jsval rval; 
		JSBool status;
		JSAutoRequest ar = JSAutoRequest(this->ctx);
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

		JSAutoRequest ar = JSAutoRequest(this->ctx);

		this->global = JS_NewCompartmentAndGlobalObject(this->ctx, &global_class,NULL);
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

		JS_DefineFunction(ctx,global,"logging",logging,0,JSPROP_ENUMERATE |JSPROP_PERMANENT);
		JS_WrapObject(ctx, &global);
		

		/*实例化_event对象*/
		LOG4CPLUS_DEBUG(log, "JSDefineObject object:_event" );
		event = JS_DefineObject(ctx,global,"_event",&_eventClass,NULL,0);	
		
	}

	void JsContext::SetContextPrivate(void *data)
	{
		return JS_SetContextPrivate(ctx,data);
	}

	bool JsContext::CompileScript(const std::string &script,const std::string &filename, unsigned int line,const void *xmlNode)
	{
		//LOG4CPLUS_DEBUG(log, "CompileScript:" << script);
		JSBool status;
		JSAutoRequest ar = JSAutoRequest(this->ctx);
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
		Reset();
		
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


	JSObject * JsContext::getScriptObject(const std::string &expr,const std::string &filename, unsigned int line,const void *xmlNode)
	{

		//return NULL;
		if (xmlNode == NULL) return NULL;
		typedef struct JSObject*    JSObjectPtr;
		std::map<const void *,void*>::iterator it = mapObjectRoot.find(xmlNode);
		if (it != mapObjectRoot.end())
		{
			JSObjectPtr *scriptObj = (JSObjectPtr*)it->second;
			return *scriptObj;
		}
		JSObjectPtr * scriptObj = new (JSObjectPtr);

		JSAutoRequest ar = JSAutoRequest(this->ctx);
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
		JSAutoRequest ar = JSAutoRequest(this->ctx);
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

	jsval JsContext::JsonValueToJsval(const Json::Value &value)const
	{
		jsval val = JSVAL_VOID;
		if (value.isBool()){
			val = BOOLEAN_TO_JSVAL(value.asBool());

		}else if (value.isDouble()){
			val = DOUBLE_TO_JSVAL(value.asDouble());

		}else if(value.isInt() || value.isIntegral() || value.isNumeric()){
			val = INT_TO_JSVAL(value.asInt());

		}else if (value.isNull()){
			val = JSVAL_NULL;

		}else if (value.isString())
		{
			val = STRING_TO_JSVAL(JS_NewStringCopyZ(this->ctx, value.asCString()));
		}else if (value.isUInt())
		{
			val = UINT_TO_JSVAL(value.asUInt());
		}
		return val;
	}

	Json::Value JsContext::JsvalToJsonValue(const jsval &value)const
	{
		
		if (JSVAL_IS_BOOLEAN(value)){
			return JSVAL_TO_BOOLEAN(value);

		}else if (JSVAL_IS_DOUBLE(value)){
			return JSVAL_TO_DOUBLE(value);

		}else if(JSVAL_IS_INT(value)){
			return JSVAL_TO_INT(value);

		}else if (JSVAL_IS_NULL(value)){
			return Json::Value();

		}else if (JSVAL_IS_NUMBER(value))
		{
			return JSVAL_TO_INT(value);
			
		}else if (JSVAL_IS_STRING(value))
		{
			std::stringstream ss;
			fsm::env::ToString valueString(ctx,value);
			ss << valueString.getBytes();
			return ss.str();
		}
		return Json::Value();
	}
}
}
