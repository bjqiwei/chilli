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
	
	//java解析器的上下文环境
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
	public:
		::JSContext * ctx;
		::JSObject * global;
		::JSObject * event;
	private:
		std::map<void*,void*>mapObjectRoot;
	public:
		JsContext(::JSRuntime * rt,Evaluator * eval,Context * parent); 
		virtual ~JsContext();

		/// <summary>
		/// Assigns a new value to an existing variable or creates a new one.
		/// The method searches the chain of parent Contexts for variable
		/// existence.
		/// </summary>
		/// <param name="name"> The variable name </param>
		/// <param name="value"> The variable value </param>
		virtual void set(const std::string &name, std::string const &value);

		/// <summary>
		/// Get the value of this variable; delegating to parent.
		/// </summary>
		/// <param name="name"> The variable name </param>
		/// <returns> Object The variable value </returns>
		virtual std::string get(const std::string &name);

		/// <summary>
		/// Check if this variable exists, delegating to parent.
		/// </summary>
		/// <param name="name"> The variable name </param>
		/// <returns> boolean true if this variable exists </returns>
		virtual bool has(const std::string &name);

		/// <summary>
		/// Clear this Context.
		/// </summary>
		virtual void reset();

	
		virtual Context *getParent();

		/// <summary>
		/// Assigns a new value to an existing variable or creates a new one.
		/// The method allows to shaddow a variable of the same name up the
		/// Context chain.
		/// </summary>
		/// <param name="name"> The variable name </param>
		/// <param name="value"> The variable value </param>
		virtual void setLocal(const std::string &name, const std::string & value, bool isDelete=true);

		virtual std::string eval(const std::string &expr,const std::string &filename, unsigned int line,void *xmlNode);

		///<summary>
		///计算一段boolen表达式脚本
		///</summary>
		///<returns>返回此表达式执行的结果。</returns>
		virtual bool evalCond(const std::string &expr,const std::string &filename, unsigned int line,void *);
		virtual xmlNodePtr evalLocation(const std::string &expr, const std::string &filename, unsigned int line,void *);
		virtual bool CompileScript(const std::string &script,const std::string &filename, unsigned int line,void *);
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
		virtual std::map<std::string,std::string> & getVars();

		/// <summary>
		/// Set the Map of all variables in this Context.
		/// </summary>
		virtual void setVars(const std::map<std::string,std::string> &varMap);

		//virtual JSObject * JSDefineObject (const char * name, JSClass * clasp);
		//virtual bool JSDefineProperties (JSObject *obj,  JSPropertySpec *ps);
		static void reportError(::JSContext *_ctx, const char *message, JSErrorReport *report);
		static void ReportException(JSContext *cx);
		static JSBool ShellOperationCallback(JSContext *cx);
		
	private:
		void InitializeInstanceFields();
		JSObject *getScriptObject(const std::string &expr,const std::string &filename, unsigned int line,void *xmlNode);
		void clearVars();
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