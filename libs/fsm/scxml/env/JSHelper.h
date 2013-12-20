#ifndef _FSM_ENV_JSHELPER_HEADER_
#define _FSM_ENV_JSHELPER_HEADER_
#include <jsatom.h>
#include <jsapi.h>
#include "JSContext.h"

namespace fsm{
namespace env{
namespace Js{
class JSAutoByteString {
public:
	JSAutoByteString(JSContext *cx, JSString *str JS_GUARD_OBJECT_NOTIFIER_PARAM)
		: mBytes(JS_EncodeString(cx, str)),ctx(cx) {
			JS_ASSERT(cx);
			JS_GUARD_OBJECT_NOTIFIER_INIT;
	}

	JSAutoByteString(JS_GUARD_OBJECT_NOTIFIER_PARAM0)
		: mBytes(NULL),ctx(NULL) {
			JS_GUARD_OBJECT_NOTIFIER_INIT;
	}

	~JSAutoByteString() {
		if(ctx)JS_free(ctx,mBytes);
	}

	/* Take ownership of the given byte array. */
	void initBytes(char *bytes) {
		JS_ASSERT(!mBytes);
		mBytes = bytes;
	}

	char *encode(JSContext *cx, JSString *str) {
		JS_ASSERT(!mBytes);
		JS_ASSERT(cx);
		this->ctx = cx;
		mBytes = JS_EncodeString(cx, str);
		return mBytes;
	}

	void clear() {
		if(ctx)JS_free(ctx,mBytes);
		mBytes = NULL;
	}

	char *ptr() const {
		return mBytes;
	}

	bool operator!() const {
		return !mBytes;
	}

private:
	char        *mBytes;
	JSContext *ctx;
	JS_DECL_USE_GUARD_OBJECT_NOTIFIER

		/* Copy and assignment are not supported. */
		JSAutoByteString(const JSAutoByteString &another);
	JSAutoByteString &operator=(const JSAutoByteString &another);
};
class ToStringHelper
{
public:
	ToStringHelper(JSContext *aCx, jsval v, bool aThrow = false)
		: cx(aCx)
	{
		mStr = JS_ValueToString(cx, v);
		if (!aThrow && !mStr)
			fsm::env::JsContext::ReportException(cx);
		JS_AddNamedStringRoot(cx, &mStr, "Value ToString helper");
	}
	~ToStringHelper() {
		JS_RemoveStringRoot(cx, &mStr);
	}
	bool threw() { return !mStr; }
	jsval getJSVal() { return STRING_TO_JSVAL(mStr); }
	const char *getBytes() {
		if (mStr && (mBytes.ptr() || mBytes.encode(cx, mStr)))
			return mBytes.ptr();
		return "(error converting value)";
	}
private:
	JSContext *cx;
	JSString *mStr;
	JSAutoByteString mBytes;
};
class ToString {
public:
	ToString(JSContext *aCx, jsval v, JSBool aThrow = JS_FALSE)
		: cx(aCx), mThrow(aThrow)
	{
		mStr = JS_ValueToString(cx, v);
		if (!aThrow && !mStr)
			fsm::env::JsContext::ReportException(cx);
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