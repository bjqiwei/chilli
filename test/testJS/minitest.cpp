#include "jsapi.h"
#include<iostream>
#include <vector>


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
	for (int i = 0; i < 1; i++)
	{

		if (JS::Evaluate(cx, global, options, script, strlen(script), &rv)) {
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
	JSRuntime *rt = JS_NewRuntime(1024L * 1024L * 1024L);
	JS_SetErrorReporter(rt, reportError);

	if (rt == nullptr) {
		std::cout << "JS NEW RUNTIME error" << std::endl;
		return 1;
	}
	std::vector<JSContext *> allcontext;
	int i = 2000;
	while (i--) {
		JSContext * cx = JS_NewContext(rt, 8192);
		if (cx == nullptr) {
			std::cout << "js new contest error." << std::endl;
			return 1;
		}

		int status = run(cx);

		allcontext.push_back(cx);
	}
	std::cout << "finish" << std::endl;
	std::getchar();
	while (!allcontext.empty())
	{
		JS_DestroyContext(allcontext.back());
		allcontext.pop_back();
	}
	std::cout << "DestroyContext"  << std::endl;
	std::getchar();
	JS_DestroyRuntime(rt);
	std::cout << "DestroyRuntime" << std::endl;
	std::getchar();
	JS_ShutDown();
	std::cout << "ShutDown" << std::endl;
	std::getchar();
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
		.setFileAndLine(__FILE__, __LINE__);

	JS::RootedObject obj(cx, global);
	JS::RootedScript jscript(cx);
	if (!JS::Compile(cx, obj, options, content, strlen(content), &jscript))
		return false;


    for (long i =0; i < 10; i++) {
		JS::RootedValue result(cx);
		if (!JS_ExecuteScript(cx, obj, jscript, &result))
			return false;
        JS_MaybeGC(cx);
    }

    return true;
}