#ifndef _FSM_ENV_JSGLOBALCLASS_HEADER_
#define _FSM_ENV_JSGLOBALCLASS_HEADER_
#include <jsapi.h>
#include <jsperf.h>
#include "JSHelper.h"

namespace fsm{
namespace env{
class JsGlobal{
public:
	//Js Context 中全局对象
	static JSClass global_class;
	//Js Context 中调用的C++函数
	static JSBool logging(JSContext *cx,unsigned int argc, jsval *vp){ 
		static log4cplus::Logger log = log4cplus::Logger::getInstance("JSlog");
		uintN i;
		char * bytes;
		JSString *str; 

		std::stringstream ss;
		//::JS::CallArgs args = CallArgsFromVp(argc, vp);
		jsval *argv = JS_ARGV(cx,vp);
		for (i = 0; i < argc; i++) {
			str = JS_ValueToString(cx, argv[i]);
			if (!str)
				return JS_FALSE;
			bytes = JS_EncodeString(cx, str);
			if (!bytes)
				return JS_FALSE;
			ss << (i ? " " : "") << bytes;
			JS_free(cx, bytes);
		}

		LOG4CPLUS_DEBUG(log,ss.str());
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE; 
	} 
	//Js Context 中的C++函数集合
	static JSFunctionSpec global_functions[];
	static JSBool global_getter(JSContext *cx, JSObject *obj, jsid id, jsval *vp);
	static JSBool global_setter(JSContext *cx, JSObject *obj, jsid id, JSBool strict, jsval *vp);
	static JSBool addProperty(JSContext *cx, JSObject *obj, jsid id, jsval *vp,const char * const objName)
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.JsContext.addProperty");
		fsm::env::Js::IdToString idString(cx, id);
		//fsm::env::Js::ToString objString(cx,OBJECT_TO_JSVAL(obj));
		fsm::env::Js::ToString valueString(cx, *vp);
		LOG4CPLUS_TRACE(log, "adding [" << objName<< "] property " << idString.getBytes() << ", initial value " << valueString.getBytes());
		return JS_TRUE;
	}
	static JSBool event_addProperty(JSContext *cx, JSObject *obj, jsid id, jsval *vp)
	{
		return addProperty(cx,obj,id,vp,"_event");
	}

	static JSBool global_addProperty(JSContext *cx, JSObject *obj, jsid id, jsval *vp)
	{
		return addProperty(cx,obj,id,vp,"global");
	}

	static JSBool delProperty(JSContext *cx, JSObject *obj, jsid id, jsval *vp,const char * const objName)
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.JsContext.delProperty");
		fsm::env::Js::IdToString idString(cx, id);
		//fsm::env::Js::ToString objString(cx,OBJECT_TO_JSVAL(obj));
		fsm::env::Js::ToString valueString(cx, *vp);
		LOG4CPLUS_TRACE(log, "deleting ["<< objName <<"] property " << idString.getBytes() << ", initial value " << valueString.getBytes());
		return JS_TRUE;
	}
	static JSBool event_delProperty(JSContext *cx, JSObject *obj, jsid id, jsval *vp)
	{
		return delProperty(cx,obj,id,vp,"_event");
	}

	static JSBool global_delProperty(JSContext *cx, JSObject *obj, jsid id, jsval *vp)
	{
		return delProperty(cx,obj,id,vp,"global");
	}
	static void finalize(JSContext *cx, JSObject *obj,const char * const objName)
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.JsContext.finalize");
		jsval *rootedVal;
		//fsm::env::Js::ToString objString(cx,OBJECT_TO_JSVAL(obj));
		LOG4CPLUS_DEBUG(log, "finalizing [" << objName << "]." );
		rootedVal = (jsval *) JS_GetPrivate(cx, obj);
		if (rootedVal) {
			JS_RemoveValueRoot(cx, rootedVal);
			JS_SetPrivate(cx, obj, NULL);
			delete rootedVal;
		}
	}
	static void event_finalize(JSContext *cx, JSObject *obj)
	{
		return finalize(cx,obj,"_event");
	}
	static void global_finalize(JSContext *cx, JSObject *obj)
	{
		return finalize(cx,obj,"global");
	}

	static JSBool convert(JSContext *cx, JSObject *obj, JSType type, jsval *vp,const char * const objName)
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.JsContext.convert");
		//fsm::env::Js::ToString objString(cx,OBJECT_TO_JSVAL(obj));
		LOG4CPLUS_TRACE(log, "converting ["<< objName <<"] to "<< JS_GetTypeName(cx, type) <<" type");
		return JS_TRUE;
	}

	static JSBool event_convert(JSContext *cx, JSObject *obj, JSType type, jsval *vp)
	{
		return convert(cx,obj,type,vp,"_event");
	}

	static JSBool global_convert(JSContext *cx, JSObject *obj, JSType type, jsval *vp)
	{
		return convert(cx,obj,type,vp,"global");
	}

	static JSBool global_enumerate(JSContext *cx, JSObject *obj)
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.JsContext.global_enumerate");
		//fsm::env::Js::ToString objString(cx,OBJECT_TO_JSVAL(obj));
		LOG4CPLUS_TRACE(log, "[global] enumerate.");
		return JS_EnumerateStandardClasses(cx, obj);
	}
	static JSBool ResolveClass(JSContext *cx, JSObject *obj, jsid id, JSBool *resolved)
	{
		if (!JS_ResolveStandardClass(cx, obj, id, resolved))
			return JS_FALSE;
		return JS_TRUE;
	}
	static JSBool global_resolve(JSContext *cx, JSObject *obj, jsid id, uintN flags,JSObject **objp)
	{
		JSBool resolved;
		static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.JsContext.global_resolve");
		fsm::env::Js::IdToString idString(cx, id);
		//fsm::env::Js::ToString objString(cx,OBJECT_TO_JSVAL(obj));
		LOG4CPLUS_ERROR(log, "resolving [global] property " << idString.getBytes());
		if (!ResolveClass(cx, obj, id, &resolved))
			return JS_FALSE;
		if (resolved) {
			*objp = obj;
			return JS_TRUE;
		}
		return JS_TRUE;
	}
	static JSBool event_enumerate(JSContext *cx, JSObject *obj, JSIterateOp enum_op,
		jsval *statep, jsid *idp)
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.JsContext.enumerate");
		JSObject *iterator;
		//fsm::env::Js::ToString objString(cx,OBJECT_TO_JSVAL(obj));
		LOG4CPLUS_ERROR(log,"[_event] enumerate.");
		switch (enum_op) {
		case JSENUMERATE_INIT:
		case JSENUMERATE_INIT_ALL:
			LOG4CPLUS_TRACE(log, "enumerate [_event] Init properties.");

			iterator = JS_NewPropertyIterator(cx, obj);
			if (!iterator)
				return JS_FALSE;

			*statep = OBJECT_TO_JSVAL(iterator);
			if (idp)
				*idp = INT_TO_JSID(0);
			break;

		case JSENUMERATE_NEXT:
			/*if (its_enum_fail) {
				JS_ReportError(cx, "its enumeration failed");
				return JS_FALSE;
			}*/
			LOG4CPLUS_TRACE(log, "enumerate [_event] next properties.");
			iterator = (JSObject *) JSVAL_TO_OBJECT(*statep);
			if (!JS_NextProperty(cx, iterator, idp))
				return JS_FALSE;

			if (!JSID_IS_VOID(*idp))
				break;
			/* Fall through. */

		case JSENUMERATE_DESTROY:
			/* Allow our iterator object to be GC'd. */
			LOG4CPLUS_TRACE(log, "enumerate [_event] destroy properties.");
			*statep = JSVAL_NULL;
			break;
		}

		return JS_TRUE;
	}


	static JSBool event_resolve(JSContext *cx, JSObject *obj, jsid id, uintN flags,
		JSObject **objp)
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.JsContext.resolve");
		fsm::env::Js::IdToString idString(cx, id);
		//fsm::env::Js::ToString objString(cx,OBJECT_TO_JSVAL(obj));
		LOG4CPLUS_TRACE(log, "resolving [_event] property " << idString.getBytes()
			<<", flags {" << ((flags & JSRESOLVE_QUALIFIED) ? "qualified" : "")
			<<"," << ((flags & JSRESOLVE_ASSIGNING) ? "assigning" : "")
			<<","<<((flags & JSRESOLVE_DETECTING) ? "detecting" : "")<<"}");
		
		return JS_TRUE;
	}
	//static JSPropertySpec global_Properties[];
};//end class Js
}// end namespace env
}//end namespace fsm
#endif