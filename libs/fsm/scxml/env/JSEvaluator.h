#pragma once
#include "../Evaluator.h"
#include <log4cplus/logger.h>
#include "jsapi.h"
#include <exception>


namespace fsm
{
namespace env
{
	
	/// <summary>
	/// Evaluator implementation enabling use of JS expressions 
	/// 
	/// </summary>
	class JSEvaluator : public Evaluator
	{

	private:
			::JSRuntime *m_jsrt = nullptr;
			log4cplus::Logger log;
	public:

		JSEvaluator(); 
		virtual ~JSEvaluator();

		virtual Context * newContext(const std::string &sessionid, Context *const parent) override;
		virtual void releaseContext(Context * const cx) override;
		virtual void deleteContext(size_t count) override;
		virtual size_t getContextCount() override;
		virtual bool hasContext() override;
	protected:
		std::list<Context * > m_contexts;
		std::list<Context *> m_removedContexts;
	};
}
}
