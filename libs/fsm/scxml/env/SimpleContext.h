#pragma once
#ifndef _SCXML_ENV_SIMPLECONTEXT_HEADER_
#define _SCXML_ENV_SIMPLECONTEXT_HEADER_
#include "../Context.h"
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

		virtual ~SimpleContext();
	
		SimpleContext(Context *const parent); //this(parent, nullptr);

		virtual void setVar(const std::string & name, const Json::Value & value, ValueContext va = globalObject) override;
		virtual Json::Value getVar(const std::string &name, ValueContext va = globalObject) override;
		virtual void deleteVar(const std::string & name, ValueContext va = globalObject) override;
		virtual Context *getParent() override;
		virtual std::string eval( const std::string &expr,const std::string &filename, unsigned int line) override;
		virtual bool evalCond(const std::string &expr,const std::string &filename, unsigned int line) override;
		virtual void ExecuteFile(const std::string &fileName) override;

	private:
		void InitializeInstanceFields();
	};
}
}

#endif // end simple context head file