#pragma once
#ifndef _FSM_ENV_JSCONTEXT_HEADER_
#define _FSM_ENV_JSCONTEXT_HEADER_
#include <scxml/Context.h>
#pragma warning (disable:4800)
#pragma warning (disable:4099)
#include <jsapi.h>
#include <jsfriendapi.h>
#include <string>
#include <map>
#include <log4cplus/logger.h>

namespace fsm
{
namespace env
{
	//java解析器的上下文环境
	class  JsContext : public Context
	{

	private:
		
		//JavaScript Runtime，多个context共同使用一个Runtime
		::JSRuntime * JSrt;
		//JS Context需要资源
		JSAutoRequest *ar;
		//JS context 需要资源
		JSAutoCompartment *ac;
		//Js Context 中全局对象
		static JSClass global_class;
		//Js Context 中调用的C++函数
		static JSBool  logging(JSContext *context,  unsigned int argc, jsval *value);
		//Js Context 中的C++函数集合
		static JSFunctionSpec global_functions[];
		
	public:
		::JSContext * ctx;
		::JSObject * global_obj;
	public:

		JsContext(::JSRuntime * rt,log4cplus::Logger log); 
		virtual ~JsContext();

		JsContext(::JSRuntime * rt,Context *const parent,log4cplus::Logger log); 

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
		virtual void setLocal(const std::string &name, const std::string & value);

		/// <summary>
		/// Set the variables map.
		/// </summary>
		/// <param name="vars"> The new Map of variables. </param>
	protected:
		virtual void setVars(const std::map<std::string,std::string> & vars);

		/// <summary>
		/// Get the Map of all local variables in this Context.
		/// </summary>
		/// <returns> Returns the vars. </returns>
	public:
		virtual std::map<std::string,std::string> & getVars();
		virtual JSObject * JSDefineObject (const char * name, JSClass * clasp);
		virtual bool JSDefineProperties (JSObject *obj,  JSPropertySpec *ps);
		virtual bool CompileScript(const std::string script);

	private:
		void InitializeInstanceFields();
		static void reportError(::JSContext *_ctx, const char *message, JSErrorReport *report);
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