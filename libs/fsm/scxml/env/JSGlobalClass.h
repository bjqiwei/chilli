#ifndef _FSM_ENV_JSGLOBALCLASS_HEADER_
#define _FSM_ENV_JSGLOBALCLASS_HEADER_
#include <jsapi.h>
#include <jsperf.h>

namespace fsm{
namespace env{
class JsGlobal{
public:
	//Js Context 中全局对象
	static JSClass global_class;
	//Js Context 中调用的C++函数
	static JSBool logging(JSContext *cx,unsigned int argc, jsval *vp);
	//Js Context 中的C++函数集合
	static JSFunctionSpec global_functions[];
	static JSBool global_getter(JSContext *cx, JSObject *obj, jsid id, jsval *vp);
	static JSBool global_setter(JSContext *cx, JSObject *obj, jsid id, JSBool strict, jsval *vp);
	static JSBool addProperty(JSContext *cx, JSObject *obj, jsid id, jsval *vp,const char * const objName);
	static JSBool event_addProperty(JSContext *cx, JSObject *obj, jsid id, jsval *vp);
	
	static JSBool global_addProperty(JSContext *cx, JSObject *obj, jsid id, jsval *vp);


	static JSBool delProperty(JSContext *cx, JSObject *obj, jsid id, jsval *vp,const char * const objName);
	
	static JSBool event_delProperty(JSContext *cx, JSObject *obj, jsid id, jsval *vp);

	static JSBool global_delProperty(JSContext *cx, JSObject *obj, jsid id, jsval *vp);

	static void finalize(JSContext *cx, JSObject *obj,const char * const objName);
	
	static void event_finalize(JSContext *cx, JSObject *obj);

	static void global_finalize(JSContext *cx, JSObject *obj);

	static JSBool convert(JSContext *cx, JSObject *obj, JSType type, jsval *vp,const char * const objName);

	static JSBool event_convert(JSContext *cx, JSObject *obj, JSType type, jsval *vp);

	static JSBool global_convert(JSContext *cx, JSObject *obj, JSType type, jsval *vp);

	static JSBool global_enumerate(JSContext *cx, JSObject *obj);
	
	static JSBool ResolveClass(JSContext *cx, JSObject *obj, jsid id, JSBool *resolved);
	
	static JSBool global_resolve(JSContext *cx, JSObject *obj, jsid id, uintN flags,JSObject **objp);
	
	static JSBool event_enumerate(JSContext *cx, JSObject *obj, JSIterateOp enum_op,
		jsval *statep, jsid *idp);

	static JSBool event_resolve(JSContext *cx, JSObject *obj, jsid id, uintN flags,
		JSObject **objp);

	static void dumpRoot(const char *name, void *addr, JSGCRootType,void *data);

	enum _eventProperty {SMName=0, sessionid, name,/*callid,bodydata,messagetype,ip,port*/};
	
	/*定义_event类的属性数组*/
	static JSPropertySpec _eventProperties[];
	/*定义_event类*/
	static JSClass _eventClass;

	static JSBool event_GetProperty (JSContext *cx, JSObject *obj, jsid id, jsval *vp);
	
	/*定义属性的SETTER*/
	static JSBool event_SetProperty (JSContext *cx, JSObject *obj, jsid id, JSBool strict, jsval *vp);
	
	//static JSPropertySpec global_Properties[];
};//end class Js
}// end namespace env
}//end namespace fsm
#endif