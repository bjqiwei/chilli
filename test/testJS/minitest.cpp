#include "mozilla/ArrayUtils.h"
#include "mozilla/Atomics.h"
#include "mozilla/DebugOnly.h"
#include "mozilla/GuardObjects.h"
#include "mozilla/mozalloc.h"
#include "mozilla/PodOperations.h"

#ifdef XP_WIN
# include <direct.h>
# include <process.h>
#endif
#include <errno.h>
#include <fcntl.h>
#if defined(XP_WIN)
# include <io.h>     /* for isatty() */
#endif
#include <locale.h>
#if defined(MALLOC_H)
# include MALLOC_H    /* for malloc_usable_size, malloc_size, _msize */
#endif
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef XP_UNIX
# include <sys/mman.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
#endif

#include "jsapi.h"
#include "jsprf.h"
#include "jstypes.h"

#ifdef XP_WIN
# include "jswin.h"
#endif
#include "jswrapper.h"

#include "js/Debug.h"
#include "js/GCAPI.h"
#include "js/Initialization.h"
#include "js/StructuredClone.h"
#include "js/TrackedOptimizationInfo.h"



#include<iostream>


bool compileAndRepeat(JSContext *cx, JSObject *global,const char * script,const char *filename);

/* The class of the global object. */
static JSClass globalClass = {
	"global",
	JSCLASS_GLOBAL_FLAGS,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr, 
	nullptr, 
	nullptr, 
	nullptr,
	JS_GlobalObjectTraceHook
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

	// Create the global object and a new compartment.
	
	JS::CompartmentOptions compileoptions;
	compileoptions.setVersion(JSVERSION_DEFAULT);
	compileoptions.setInvisibleToDebugger(true);

	JS::RootedObject global(cx, JS_NewGlobalObject(cx, &globalClass, nullptr,
		JS::DontFireOnNewGlobalHook, compileoptions));

	if (!global)
		return 1;

	// Enter the new global object's compartment.
	JSAutoCompartment ac(cx, global);

	/* Populate the global object with the standard globals, like Object and Array. */
	if (!JS_InitStandardClasses(cx, global))
		return 1;

	/* Your application code here. This may include JSAPI calls to create your own custom JS objects and run scripts. */
	const char *script = "'hello'+'world, it is '+new Date()";
 
	JS::CompileOptions options(cx);
	options.setFileAndLine(__FILE__, __LINE__);

	JS::RootedValue rv(cx);
	for (int i = 0; i < 100; i++)
	{

		if (JS::Evaluate(cx, options, script, strlen(script), &rv)) {
			JSString *str = rv.toString();
			std::cout << JS_EncodeString(cx, str) << std::endl;
		}
	}
	return 0;
}

int main(int argc, const char *argv[]) {

	// Initialize the JS engine.
	if (!JS_Init()) {
		std::cout << "JS INIT error" << std::endl;
		return 1;
	}

	/* Create a JS runtime. */
	JSRuntime *rt = JS_NewRuntime(8L * 1024L * 1024L);
	if (rt == nullptr) {
		std::cout << "JS NEW RUNTIME error" << std::endl;
		return 1;
	}

	JSContext * cx = JS_NewContext(rt, 8192);
	if (cx == nullptr) {
		std::cout << "js new contest error." << std::endl;
		return 1;
	}
	JS_SetErrorReporter(rt, reportError);

	int status = run(cx);

	std::getchar();

	JS_DestroyContext(cx);
	JS_DestroyRuntime(rt);
	JS_ShutDown();
	
	return 0;
}

/*
 * Compile a script and execute it repeatedly until an
 * error occurs.  (If this ever returns, it returns false.
 * If there's no error it just keeps going.)
 */
bool compileAndRepeat(JSContext *cx, JSObject *global,const char * content,const char *filename)
{
	JS::CompileOptions options(cx);
	options.setIntroductionType("js shell interactive")
		.setUTF8(true)
		.setIsRunOnce(false)
		.setFileAndLine(__FILE__, __LINE__);

	JS::RootedScript jscript(cx);
	if (!JS::Compile(cx, options, content, strlen(content), &jscript))
		return false;


    for (long i =0; i < 10; i++) {
		JS::RootedValue result(cx);
		if (!JS_ExecuteScript(cx, jscript, &result))
			return false;
        JS_MaybeGC(cx);
    }

    return true;
}