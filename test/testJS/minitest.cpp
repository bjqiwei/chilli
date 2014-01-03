#include "jsapi.h"
#include <strstream>
#include <iostream>

#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/loggingmacros.h>

JSBool compileAndRepeat(JSContext *cx, JSObject *global,const char * script,const char *filename);

/* The class of the global object. */
static JSClass global_class = { "global",
	JSCLASS_NEW_RESOLVE | JSCLASS_GLOBAL_FLAGS,
	JS_PropertyStub,
	JS_PropertyStub,
	JS_PropertyStub,
	JS_StrictPropertyStub,
	JS_EnumerateStub,
	JS_ResolveStub,
	JS_ConvertStub,
	NULL,
	JSCLASS_NO_OPTIONAL_MEMBERS
};

/* The error reporter callback. */
void reportError(JSContext *cx, const char *message, JSErrorReport *report) {
	fprintf(stderr, "%s:%u:%s\n",
		report->filename ? report->filename : "<no filename="">",
		(unsigned int) report->lineno,
		message);
}

int run(JSContext *cx) {
	/* Enter a request before running anything in the context */
	JSAutoRequest ar(cx);

	/* Create the global object in a new compartment. */
	JSObject *global = JS_NewCompartmentAndGlobalObject(cx, &global_class,NULL);
	if (global == NULL)
		return 1;

	/* Set the context's global */
	JSAutoEnterCompartment ac;
	ac.enter(cx, global);
	JS_SetGlobalObject(cx, global);

	/* Populate the global object with the standard globals, like Object and Array. */
	if (!JS_InitStandardClasses(cx, global))
		return 1;

	/* Your application code here. This may include JSAPI calls to create your own custom JS objects and run scripts. */
	char *script = "(function(a, b){return a * b;})(15, 6);"; 
	jsval rval; 

	JSBool status = compileAndRepeat(cx,global,script,"");
	//JSBool status = JS_EvaluateScript(cx, global, script, strlen(script), NULL, 0, &rval); 

	if (status == JS_TRUE){ 
		JSString *d; 
		d =JS_ValueToString(cx, rval); 
		std::cout << "eval result =" << d;
		
	} 
	return 0;
}

int main(int argc, const char *argv[]) {
	log4cplus::initialize();
	/* Create a JS runtime. */
	JSRuntime *rt = JS_NewRuntime(8L * 1024L * 1024L);
	if (rt == NULL)
		return 1;

	/* Create a context. */
	JSContext *cx = JS_NewContext(rt, 8192);
	if (cx == NULL)
		return 1;
	JS_SetOptions(cx, JSOPTION_VAROBJFIX);
	JS_SetErrorReporter(cx, reportError);

	int status = run(cx);

	JS_DestroyContext(cx);
	JS_DestroyRuntime(rt);
	JS_ShutDown();
	return status;
}

/*
 * Compile a script and execute it repeatedly until an
 * error occurs.  (If this ever returns, it returns false.
 * If there's no error it just keeps going.)
 */
JSBool compileAndRepeat(JSContext *cx, JSObject *global,const char * content,const char *filename)
{
    JSObject *scriptObj;

	scriptObj = JS_CompileScript(cx, global, content,strlen(content),filename,0);
	if (scriptObj == NULL)
        return JS_FALSE;   /* compilation error */

	
    if (!JS_AddNamedObjectRoot(cx, &scriptObj, "compileAndRepeat script object"))
        return JS_FALSE;

    for (;;) {
        jsval result;
        if (!JS_ExecuteScript(cx, global, scriptObj, &result))
            break;
        JS_MaybeGC(cx);
    }

    JS_RemoveObjectRoot(cx, &scriptObj);  /* scriptObj becomes unreachable
                                             and will eventually be collected. */
    return JS_FALSE;
}