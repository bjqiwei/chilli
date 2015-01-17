#pragma once
#ifndef _FSM_ENV_JSCONTEXT_HEADER_
#define _FSM_ENV_JSCONTEXT_HEADER_
#include "../Context.h"
#include <jsatom.h>
#include <jsapi.h>
#include <string>
#include <map>
#include <log4cplus/logger.h>
#include "libxml/tree.h"


namespace fsm
{
namespace env
{

	// helper class
	static void ReportException(JSContext *cx){
		if (JS_IsExceptionPending(cx)) {
			if (!JS_ReportPendingException(cx))
				JS_ClearPendingException(cx);
		}
	}

	class ToString {
	public:
		ToString(JSContext *aCx, jsval v, JSBool aThrow = JS_FALSE)
			: cx(aCx), mThrow(aThrow)
		{
			mStr = JS_ValueToString(cx, v);
			if (!aThrow && !mStr)
				ReportException(cx);
			JS_AddNamedStringRoot(cx, &mStr, "Value ToString helper");
		}
		~ToString() {
			JS_RemoveStringRoot(cx, &mStr);
		}
		JSBool threw() { return !mStr; }
		jsval getJSVal() { return STRING_TO_JSVAL(mStr); }
		const char *getBytes() {
			if (mStr && (mBytes.ptr() || mBytes.encode(cx, mStr)))
				return mBytes.ptr();
			return "(error converting value)";
		}
	private:
		JSContext *cx;
		JSString *mStr;
		JSBool mThrow;
		JSAutoByteString mBytes;
	};

	class IdToString : public ToString {
	public:
		IdToString(JSContext *cx, jsid id, JSBool aThrow = JS_FALSE)
			: ToString(cx, js::IdToJsval(id), aThrow)
		{ }
	};
	//end helper class


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
		//Js Context 中全局对象
		static JSClass global_class;
		/*定义_event类*/
		static JSClass _eventClass;

	private:
		
		//JavaScript Runtime，多个context共同使用一个Runtime
		::JSRuntime * JSrt;
		log4cplus::Logger log;
	
		static unsigned long StackChunkSize; 
		static size_t  gMaxStackSize;
		static size_t gScriptStackQuota;
	private:
		::JSContext * ctx;
		::JSObject * global;
		::JSObject * event;
	private:
		std::map<const void*,void*>mapObjectRoot;
	public:
		JsContext(::JSRuntime * rt,Evaluator * eval,Context * parent); 
		virtual ~JsContext();
		///<summary>
		///对一个变量设置新值。
		///</summary>
		///<returns></returns>
		virtual void setVar(const std::string & name, const Json::Value & value, ValueContext va = fsm::globalObject) ;

		///<summary>
		///获取一个变量值。
		///</summary>
		///<returns>返回此变量值。</returns>
		virtual Json::Value getVar(const std::string &name, ValueContext va = fsm::globalObject) ;

		///<summary>
		///删除一个变量。
		///</summary>
		///<returns></returns>
		virtual void deleteVar(const std::string & name, ValueContext va = fsm::globalObject) ;
		/// <summary>
		/// reset this Context.
		/// </summary>
		virtual void Reset();

		/// <summary>
		/// Get this parent Context.
		/// </summary>
		virtual Context *getParent();

		virtual std::string eval(const std::string &expr,const std::string &filename, unsigned int line,const void *xmlNode);

		///<summary>
		///计算一段boolen表达式脚本
		///</summary>
		///<returns>返回此表达式执行的结果。</returns>
		virtual bool evalCond(const std::string &expr,const std::string &filename, unsigned int line,const void *xmlNode);
		virtual bool CompileScript(const std::string &script,const std::string &filename, unsigned int line,const void *xmlNode);
		virtual void ExecuteFile(const std::string &fileName);
		virtual void SetContextPrivate(void *data);
	protected:

		static void operator delete(void *p){ delete (char *)p;};
		friend class JSEvaluator;
		static void reportError(::JSContext *_ctx, const char *message, JSErrorReport *report);
		static JSBool ShellOperationCallback(JSContext *cx);
		
	private:
		void InitializeInstanceFields();
		JSObject *getScriptObject(const std::string &expr,const std::string &filename, unsigned int line,const void *xmlNode);
		jsval JsonValueToJsval(const Json::Value &val) const;
		Json::Value JsvalToJsonValue(const jsval &val) const;
	};

}
}

#endif // end head 