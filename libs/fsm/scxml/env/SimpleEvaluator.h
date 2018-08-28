#pragma once
#include "../Evaluator.h"


namespace fsm
{
namespace env
{
	class  SimpleEvaluator : public Evaluator
	{

	private:
			static const std::string ERR_CTX_TYPE;
	public:

		SimpleEvaluator(); 
		virtual ~SimpleEvaluator();

	
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