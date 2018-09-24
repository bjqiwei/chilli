#include <iostream>
#include <string>
#include <v8.h>
#include <vector>
#include "codingHelper.h"
 
using namespace v8;
 
int main(int argc, char* argv[]) {
  // Get the default Isolate created at startup.
  Isolate* isolate = Isolate::GetCurrent();
  
  std::vector<Handle<Context>> jscontext;
  int i = 2000;
  while (i--)
  {
	  // Create a stack-allocated handle scope.
	  HandleScope handle_scope(isolate);

	  // Create a new context.
	  Handle<Context> context = Context::New(isolate);
	  jscontext.push_back(context);

	  // Enter the created context for compiling and
	  // running the hello world script. 
	  Context::Scope context_scope(context);

	  // Create a string containing the JavaScript source code.
	  Handle<String> source = String::NewFromUtf8(isolate, "'hello'+'world, it is '+new Date()");

	  // Compile the source code.
	  Handle<Script> script = Script::Compile(source);

	  // Run the script to get the result.
	  Handle<Value> result = script->Run();


	  // Convert the result to an UTF8 string and print it.
	  String::Utf8Value utf8v(result);
	  std::cout << UTF_82ASCII(std::string(*utf8v, utf8v.length())) << std::endl;
  }
  std::cout << "finish" << std::endl;
  std::getchar();
  while (!jscontext.empty())
  {
	  jscontext.pop_back();
  }

  std::cout << "DestroyContext" << std::endl;
  getchar();
  return 0;
}
