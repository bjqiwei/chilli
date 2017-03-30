#pragma once
#ifndef _FSM_ENV_JSCONTEXT_HEADER_
#define _FSM_ENV_JSCONTEXT_HEADER_
#include "../Context.h"
#include <jsapi.h>
#include <string>
#include <log4cplus/logger.h>


namespace fsm
{
namespace env
{

	
	//JavaScript解析器的上下文环境
	class  JsContext : public Context
	{

	public:
		log4cplus::Logger log;
		std::string m_strSessionID;
	private:
		::JSRuntime * m_jsrt = nullptr;
		::JSContext * m_jsctx = nullptr;
		::JSObject * m_global = nullptr;
	public:
		JsContext(const std::string &sessionid, Evaluator * eval,Context * parent);
		virtual ~JsContext();

		virtual void setVar(const std::string & name, const Json::Value & value) override;

		virtual Json::Value getVar(const std::string &name) override;

		virtual void deleteVar(const std::string & name) override;

		virtual Context *getParent() override;

		virtual Json::Value eval(const std::string &expr,const std::string &filename, unsigned int line) override;

		virtual bool evalCond(const std::string &expr,const std::string &filename, unsigned int line) override;
		virtual void ExecuteFile(const std::string &fileName);

	private:
		void InitializeInstanceFields();
		JS::Value JsonValueToJsval(const Json::Value &val) const;
		Json::Value JsvalToJsonValue(const JS::Value &val) const;
	};

}
}

#endif // end head 