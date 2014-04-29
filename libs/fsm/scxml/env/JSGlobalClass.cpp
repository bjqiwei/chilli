#include "JSGlobalClass.h"
#include "JSHelper.h"
#include "..\..\FSM.h"
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

namespace fsm{
namespace env{
	JSBool JsGlobal::logging(JSContext *cx,unsigned int argc, jsval *vp){ 
		static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.JsContex.Log");
		uintN i;

		std::stringstream ss;
		//::JS::CallArgs args = CallArgsFromVp(argc, vp);
		jsval *argv = JS_ARGV(cx,vp);
		for (i = 0; i < argc; i++) {
			fsm::env::Js::ToString toString(cx, argv[i]);
			ss << (i ? " " : "") << toString.getBytes();
		}

		LOG4CPLUS_DEBUG(log,ss.str());
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE; 
	}

	JSBool JsGlobal::addProperty(JSContext *cx, JSObject *obj, jsid id, jsval *vp,const char * const objName)
	{
		//static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.JsContext.addProperty");
		//fsm::env::Js::IdToString idString(cx, id);
		////fsm::env::Js::ToString objString(cx,OBJECT_TO_JSVAL(obj));
		//fsm::env::Js::ToString valueString(cx, *vp);
		//LOG4CPLUS_TRACE(log, "adding [" << objName<< "] property " << idString.getBytes() << ", initial value " << valueString.getBytes());
		return JS_TRUE;
	}
	JSBool JsGlobal::event_addProperty(JSContext *cx, JSObject *obj, jsid id, jsval *vp)
	{
		return addProperty(cx,obj,id,vp,"_event");
	}

	JSBool JsGlobal::global_addProperty(JSContext *cx, JSObject *obj, jsid id, jsval *vp)
	{
		return addProperty(cx,obj,id,vp,"global");
	}

	JSBool JsGlobal::delProperty(JSContext *cx, JSObject *obj, jsid id, jsval *vp,const char * const objName)
	{
		//static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.JsContext.delProperty");
		//fsm::env::Js::IdToString idString(cx, id);
		////fsm::env::Js::ToString objString(cx,OBJECT_TO_JSVAL(obj));
		//fsm::env::Js::ToString valueString(cx, *vp);
		//LOG4CPLUS_TRACE(log, "deleting ["<< objName <<"] property " << idString.getBytes() << ", initial value " << valueString.getBytes());
		return JS_TRUE;
	}

	JSBool JsGlobal::event_delProperty(JSContext *cx, JSObject *obj, jsid id, jsval *vp)
	{
		return delProperty(cx,obj,id,vp,"_event");
	}

	JSBool JsGlobal::global_delProperty(JSContext *cx, JSObject *obj, jsid id, jsval *vp)
	{
		return delProperty(cx,obj,id,vp,"global");
	}

	void JsGlobal::finalize(JSContext *cx, JSObject *obj,const char * const objName)
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.JsContext.finalize");
		jsval *rootedVal;
		//fsm::env::Js::ToString objString(cx,OBJECT_TO_JSVAL(obj));
		LOG4CPLUS_DEBUG(log, "finalizing [" << objName << "]." );
		rootedVal = (jsval *) JS_GetPrivate(cx, obj);
		if (rootedVal) {
			JS_RemoveValueRoot(cx, rootedVal);
			JS_SetPrivate(cx, obj, NULL);
			delete[] rootedVal;
		}
	}

	void JsGlobal::event_finalize(JSContext *cx, JSObject *obj)
	{
		return finalize(cx,obj,"_event");
	}
	void JsGlobal::global_finalize(JSContext *cx, JSObject *obj)
	{
		return finalize(cx,obj,"global");
	}

	JSBool JsGlobal::convert(JSContext *cx, JSObject *obj, JSType type, jsval *vp,const char * const objName)
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.JsContext.convert");
		//fsm::env::Js::ToString objString(cx,OBJECT_TO_JSVAL(obj));
		LOG4CPLUS_TRACE(log, "converting ["<< objName <<"] to "<< JS_GetTypeName(cx, type) <<" type");
		return JS_TRUE;
	}

	JSBool JsGlobal::event_convert(JSContext *cx, JSObject *obj, JSType type, jsval *vp)
	{
		return convert(cx,obj,type,vp,"_event");
	}

	JSBool JsGlobal::global_convert(JSContext *cx, JSObject *obj, JSType type, jsval *vp)
	{
		return convert(cx,obj,type,vp,"global");
	}


	JSBool JsGlobal::global_enumerate(JSContext *cx, JSObject *obj)
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.JsContext.global_enumerate");
		//fsm::env::Js::ToString objString(cx,OBJECT_TO_JSVAL(obj));
		LOG4CPLUS_TRACE(log, "[global] enumerate.");
		return JS_EnumerateStandardClasses(cx, obj);
	}
	JSBool JsGlobal::ResolveClass(JSContext *cx, JSObject *obj, jsid id, JSBool *resolved)
	{
		if (!JS_ResolveStandardClass(cx, obj, id, resolved))
			return JS_FALSE;
		return JS_TRUE;
	}

	JSBool JsGlobal::global_resolve(JSContext *cx, JSObject *obj, jsid id, uintN flags,JSObject **objp)
	{
		//JSBool resolved;
		//static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.JsContext.global_resolve");
		//fsm::env::Js::IdToString idString(cx, id);
		////fsm::env::Js::ToString objString(cx,OBJECT_TO_JSVAL(obj));
		//LOG4CPLUS_ERROR(log, "resolving [global] property " << idString.getBytes());
		//if (!ResolveClass(cx, obj, id, &resolved))
		//	return JS_FALSE;
		//if (resolved) {
		//	*objp = obj;
		//	return JS_TRUE;
		//}
		return JS_TRUE;
	}

	JSBool JsGlobal::event_enumerate(JSContext *cx, JSObject *obj, JSIterateOp enum_op,
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

	JSBool JsGlobal::event_resolve(JSContext *cx, JSObject *obj, jsid id, uintN flags,
		JSObject **objp)
	{
		//static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.JsContext.resolve");
		//fsm::env::Js::IdToString idString(cx, id);
		////fsm::env::Js::ToString objString(cx,OBJECT_TO_JSVAL(obj));
		//LOG4CPLUS_TRACE(log, "resolving [_event] property " << idString.getBytes()
		//	<<", flags {" << ((flags & JSRESOLVE_QUALIFIED) ? "qualified" : "")
		//	<<"," << ((flags & JSRESOLVE_ASSIGNING) ? "assigning" : "")
		//	<<","<<((flags & JSRESOLVE_DETECTING) ? "detecting" : "")<<"}");

		return JS_TRUE;
	}

	void JsGlobal::dumpRoot(const char *name, void *addr, JSGCRootType,void *data)
	{
    /* The application may use `data` for anything.  In this
       example, we use it to pass the desired output file. */
		static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.JsContex.Dump");
		LOG4CPLUS_TRACE(log, "There is a root named '" << name<< "' at " << addr);
	}

	JSPropertySpec JsGlobal::_eventProperties[] =
	{
		{"_name",name,    JSPROP_READONLY | JSPROP_ENUMERATE | JSPROP_PERMANENT,NULL,NULL },
		//{"_bodydata",  bodydata,     JSPROP_READONLY | JSPROP_ENUMERATE | JSPROP_PERMANENT ,event_GetProperty,NULL},
		//{"_msgtype",  messagetype,     JSPROP_READONLY | JSPROP_ENUMERATE | JSPROP_PERMANENT ,event_GetProperty,NULL},
		//{"_ip",  ip,     JSPROP_READONLY | JSPROP_ENUMERATE | JSPROP_PERMANENT ,event_GetProperty,NULL},
		//{"_port",  port,     JSPROP_READONLY | JSPROP_ENUMERATE | JSPROP_PERMANENT ,event_GetProperty,NULL},
		{"_serviceid",  serviceid,     JSPROP_READONLY | JSPROP_ENUMERATE | JSPROP_PERMANENT ,NULL,NULL},
		{"_sessionid",  sessionid,     JSPROP_READONLY | JSPROP_ENUMERATE | JSPROP_PERMANENT ,NULL,NULL},
		{"_callid",  callid,     JSPROP_READONLY | JSPROP_ENUMERATE | JSPROP_PERMANENT ,NULL,NULL},
		{NULL,0,0,NULL,NULL}
	};


	/*定义_event类*/
	JSClass JsGlobal::_eventClass = {
		"_event",JSCLASS_NEW_RESOLVE | JSCLASS_NEW_ENUMERATE | JSCLASS_HAS_PRIVATE,
		//fsm::env::JsGlobal::event_addProperty,fsm::env::JsGlobal::event_delProperty,
		JS_PropertyStub,JS_PropertyStub,
		event_GetProperty, 
		//event_SetProperty,
		JS_StrictPropertyStub,
		//(JSEnumerateOp)fsm::env::JsGlobal::event_enumerate, (JSResolveOp)fsm::env::JsGlobal::event_resolve,
		JS_EnumerateStub,JS_ResolveStub,
		//fsm::env::JsGlobal::event_convert, 
		JS_ConvertStub,
		event_finalize,
		JSCLASS_NO_OPTIONAL_MEMBERS
	};


	JSBool JsGlobal::event_GetProperty (JSContext *cx, JSObject *obj, jsid id, jsval *vp)
	{
		fsm::StateMachine * pstateMachine = NULL;
		static log4cplus::Logger log = log4cplus::Logger::getInstance("TUserManager.GetProperty");
		pstateMachine = (fsm::StateMachine *)JS_GetContextPrivate(cx);
		if (!pstateMachine){
			LOG4CPLUS_WARN(log,"GetContextPrivate is null.");
		}
		
		if (!JSID_IS_INT(id)) return JS_TRUE;

		int proid = JSID_TO_INT(id);
		
		jsval *val = (jsval *) JS_GetPrivate(cx, obj);
		if (val) {
			if(JSVAL_IS_NULL(*vp) || JSVAL_IS_VOID(*vp))
				*vp = val[proid];
			return JS_TRUE;
		}
		
		val = new jsval[4];
		if (!val) {
			JS_ReportOutOfMemory(cx);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}

		if (!JS_AddValueRoot(cx, val)) {
			delete[] val;
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}

		if (!JS_SetPrivate(cx, obj, (void*)val)) {
			JS_RemoveValueRoot(cx, val);
			delete[] val;
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}

		std::string prefix = "getting [_event] property:";
		fsm::env::Js::IdToString idString(cx, id);
		if(pstateMachine ){

			val[name] = STRING_TO_JSVAL(JS_NewStringCopyZ (cx,pstateMachine->m_currentEvt.getEventName().c_str()));
			//val[bodydata] = STRING_TO_JSVAL(JS_NewStringCopyZ (cx,pstateMachine->m_currentEvt.getData().c_str()));
			//val[messagetype] = STRING_TO_JSVAL(JS_NewStringCopyZ (cx,pstateMachine->m_currentEvt.getMsgType().c_str()));
			//val[ip] = STRING_TO_JSVAL(JS_NewStringCopyZ (cx,pstateMachine->m_currentEvt.getIP().c_str()));
			//val[port] = INT_TO_JSVAL(pstateMachine->m_currentEvt.getPort());
			val[serviceid] = STRING_TO_JSVAL(JS_NewStringCopyZ (cx,pstateMachine->getName().c_str()));
			val[sessionid] = STRING_TO_JSVAL(JS_NewStringCopyZ (cx,pstateMachine->getSessionId().c_str()));
			val[callid] = STRING_TO_JSVAL(JS_NewStringCopyZ (cx,pstateMachine->getSessionId().c_str()));

			switch (proid) {
			case name:
				prefix.append("_name");
				break;
			case serviceid:
				prefix.append("_serviceid");
				break;
			case sessionid:
				prefix.append("_sessionid");
				break;
			case callid:
				prefix.append("_callid");
				break;

				//case from:{
				//	vp.setInt32(pstateMachine->getFrom().c_str());
				//	break;
				//case Enable:
				//	vp.setBoolean(extPtr->m_bEnable);
				//	break;

			default:
				prefix.append(idString.getBytes());
				break;
			}

		}else{
			prefix.append(idString.getBytes());
		}

		fsm::env::Js::ToString valueString(cx, val[proid]);
		//fsm::env::Js::ToString objString(cx,OBJECT_TO_JSVAL(obj));
		*vp = val[proid];
		LOG4CPLUS_DEBUG(log,prefix<< ",value:" << valueString.getBytes());

		return JS_TRUE;
	}

	JSBool JsGlobal::event_SetProperty (JSContext *cx, JSObject *obj, jsid id, JSBool strict, jsval *vp)
	{
		//fsm::StateMachine * pstateMachine = NULL;
		//static log4cplus::Logger log = log4cplus::Logger::getInstance("TUserManager.SetProperty");

		//fsm::env::Js::IdToString idString(cx, id);
		//fsm::env::Js::ToString valueString(cx, *vp);
		////fsm::env::Js::ToString objString(cx,OBJECT_TO_JSVAL(obj));
		//LOG4CPLUS_TRACE(log, "setting [_event] property " << idString.getBytes() << ", new value " <<valueString.getBytes());


		//if (!JSID_IS_ATOM(id))
		//	return JS_TRUE;

		return JS_TRUE;
	}



	//global class
	JSClass JsGlobal::global_class = { 
		"global",JSCLASS_NEW_RESOLVE | JSCLASS_GLOBAL_FLAGS ,
		JS_PropertyStub,JS_PropertyStub,
		JS_PropertyStub,JS_StrictPropertyStub,
		//global_enumerate,(JSResolveOp)global_resolve
		JS_EnumerateStub,JS_ResolveStub,
		JS_ConvertStub,NULL,//global_finalize,
		JSCLASS_NO_OPTIONAL_MEMBERS
	};

	//定义globa 函数数组
	JSFunctionSpec JsGlobal::global_functions[] = { 
		JS_FN("logging", logging,0, 0), 
		JS_FS_END
	}; 

	//JSBool JsGlobal::global_getter(JSContext *cx, JSObject *obj, jsid id, jsval *vp)
	//{
	//	static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.global.getter");
	//	fsm::StateMachine * pstateMachine = (fsm::StateMachine *)JS_GetContextPrivate(cx);

	//	JSString * jss = NULL;
	//	fsm::env::Js::IdToString idString(cx, id);

	//	if (strcmp(idString.getBytes(),"sessionid") == 0)
	//	{
	//		if(pstateMachine)
	//			jss = JS_NewStringCopyZ (cx,pstateMachine->getSessionId().c_str());
	//	}else if(strcmp(idString.getBytes(),"serviceid") == 0)
	//	{
	//		if(pstateMachine)
	//			jss = JS_NewStringCopyZ (cx,pstateMachine->getName().c_str());
	//	}
	//	*vp =  STRING_TO_JSVAL(jss);
	//	
	//	fsm::env::Js::ToString valueString(cx, *vp);
	//	fsm::env::Js::ToString objString(cx,OBJECT_TO_JSVAL(obj));
	//	LOG4CPLUS_TRACE(log,objString.getBytes() << " property name:" << idString.getBytes() << ",value " << valueString.getBytes());
	//	return JS_TRUE;
	//}
	//JSBool JsGlobal::global_setter(JSContext *cx, JSObject *obj, jsid id, JSBool strict, jsval *vp)
	//{
	//	static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.global.setter");
	//	fsm::env::Js::IdToString idString(cx, id);
	//	fsm::env::Js::ToString valueString(cx, *vp);
	//	fsm::env::Js::ToString objString(cx,OBJECT_TO_JSVAL(obj));

	//	LOG4CPLUS_TRACE(log,objString.getBytes() << " property name:" << idString.getBytes() << ",value " << valueString.getBytes());
	//	return JS_TRUE;
	//}

	/*定义global类的属性数组*/
	//JSPropertySpec JsGlobal::global_Properties[] =
	//{
	//	{"sessionid",sessionid,    JSPROP_ENUMERATE },
	//	{0}
	//};
}
}