#ifndef _FSM_ENV_JSHELPER_HEADER_
#define _FSM_ENV_JSHELPER_HEADER_
#include <jsatom.h>
#include <jsapi.h>

namespace fsm{
namespace env{
namespace Js{
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
} //end namespace Js
} //end namespace env
}//end namespace fsm
#endif//end head file