#pragma once
#ifndef _FSM_ENV_JSCONTEXT_HEADER_
#define _FSM_ENV_JSCONTEXT_HEADER_
#include "../Context.h"
#include <jsapi.h>
#include <string>
#include <map>
#include <log4cplus/logger.h>
#include "libxml/tree.h"


namespace fsm
{
namespace env
{
	#if (defined(DEBUG) && defined(__SUNPRO_CC))  || defined(JS_CPU_SPARC)
	/* Sun compiler uses larger stack space for js_Interpret() with debug
	   Use a bigger gMaxStackSize to make "make check" happy. */
	#define DEFAULT_MAX_STACK_SIZE 500000
	#else
	#define DEFAULT_MAX_STACK_SIZE 500000
	#endif

	#define JS_DEFAULT_SCRIPT_STACK_QUOTA   ((size_t) 0x8000000)
	
	//JavaScript解析器的上下文环境
	class  JsContext : public Context
	{

	private:
		
		//JavaScript Runtime，多个context共同使用一个Runtime
		::JSRuntime * JSrt;
		//JS Context需要资源
		JSAutoRequest *ar;
		//JSAutoEnterCompartment *ac;
		static log4cplus::Logger log;
	
		static unsigned long StackChunkSize; 
		static size_t  gMaxStackSize;
		static size_t gScriptStackQuota;
	private:
		::JSContext * ctx;
		::JSObject * global;
		::JSObject * event;
	private:
		std::map<void*,void*>mapObjectRoot;
	public:
		JsContext(::JSRuntime * rt,Evaluator * eval,Context * parent); 
		virtual ~JsContext();

		/// <summary>
		/// reset this Context.
		/// </summary>
		virtual void Reset();

		/// <summary>
		/// Get this parent Context.
		/// </summary>
		virtual Context *getParent();

		/// <summary>
		/// Assigns a new value to an existing variable or creates a new one.
		/// The method allows to shaddow a variable of the same name up the
		/// Context chain.
		/// </summary>
		/// <param name="name"> The variable name </param>
		/// <param name="value"> The variable value </param>
		/// <param name="eventVars"> The variable is or not event var  </param>
		virtual void setLocal(const std::string &name, const std::string & value, bool eventVars=true);

		virtual std::string eval(const std::string &expr,const std::string &filename, unsigned int line,void *xmlNode);

		///<summary>
		///计算一段boolen表达式脚本
		///</summary>
		///<returns>返回此表达式执行的结果。</returns>
		virtual bool evalCond(const std::string &expr,const std::string &filename, unsigned int line,void *xmlNode);
		virtual bool CompileScript(const std::string &script,const std::string &filename, unsigned int line,void *xmlNode);
		virtual void SetContextPrivate(void *data);
		virtual void ExecuteFile(const std::string &fileName);
	protected:

		static void operator delete(void *p){ delete (char *)p;};
		friend class JSEvaluator;
	public:
		/// <summary>
		/// Get the Map of all local variables in this Context.
		/// </summary>
		/// <returns> Returns the vars. </returns>
		virtual std::map<std::string,std::string> & getEventVars();

		/// <summary>
		/// Set the Map of all variables in this Context.
		/// </summary>
		virtual void SetEventVars(const std::map<std::string,std::string> &varMap);
		virtual void ClearEventVars();

		//virtual JSObject * JSDefineObject (const char * name, JSClass * clasp);
		//virtual bool JSDefineProperties (JSObject *obj,  JSPropertySpec *ps);
		static void reportError(::JSContext *_ctx, const char *message, JSErrorReport *report);
		static void ReportException(JSContext *cx);
		static JSBool ShellOperationCallback(JSContext *cx);
		
	private:
		void InitializeInstanceFields();
		JSObject *getScriptObject(const std::string &expr,const std::string &filename, unsigned int line,void *xmlNode);

	};

	
	//class INTERPRETER_EXPORT ToStringHelper
	//{
	//  public:
	//	ToStringHelper(JSContext *aCx, js::HandleValue v, bool aThrow = false);
	//	ToStringHelper(JSContext *aCx, js::HandleId id, bool aThrow = false);
	//	bool threw();
	//	jsval getJSVal();
	//	const char *getBytes();
	//  private:
	//	JSContext *cx;
	//	js::RootedString mStr;  // Objects of this class are always stack-allocated.
	//	JSAutoByteString mBytes;
	//};

}
}

#endif // end head 