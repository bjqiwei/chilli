#pragma once
#ifndef _SCXML_ENV_SIMPLECONTEXT_HEADER_
#define _SCXML_ENV_SIMPLECONTEXT_HEADER_
#include "../Context.h"
#include <string>
#include <map>
#include <log4cplus/logger.h>

namespace fsm
{
namespace env
{
	class SimpleContext : public Context
	{

	private:

		log4cplus::Logger log;

	public:

		SimpleContext(); 
		virtual ~SimpleContext();
	
		SimpleContext(Context *const parent); //this(parent, nullptr);

		///<summary>
		///对一个变量设置新值。
		///</summary>
		///<returns></returns>
		virtual void setVar(const std::string & name, const Json::Value & value, ValueContext va = globalObject);

		///<summary>
		///获取一个变量值。
		///</summary>
		///<returns>返回此变量值。</returns>
		virtual Json::Value getVar(const std::string &name, ValueContext va = globalObject);

		///<summary>
		///删除一个变量。
		///</summary>
		///<returns></returns>
		virtual void deleteVar(const std::string & name, ValueContext va = globalObject);

		/// <summary>
		/// reset this Context.
		/// </summary>
		virtual void Reset();

		virtual Context *getParent();
		
		/// <summary>
		/// Set the log used by this <code>Context</code> instance.
		/// </summary>
		/// <param name="log"> The new log. </param>

		virtual std::string eval( const std::string &expr,const std::string &filename, unsigned int line,const void *xmlNode);
		virtual bool evalCond(const std::string &expr,const std::string &filename, unsigned int line,const void *xmlNode);
		virtual void ExecuteFile(const std::string &fileName);
		virtual void SetContextPrivate(void *data);

		virtual bool CompileScript(const std::string &script,const std::string &filename, unsigned int line,const void*);

	private:
		void InitializeInstanceFields();
	};
}
}

#endif // end simple context head file