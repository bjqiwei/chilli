#include "SimpleEvaluator.h"
#include "SimpleContext.h"


namespace fsm
{
namespace env
{


	const std::string SimpleEvaluator::ERR_CTX_TYPE = "Error evaluating Simple expression.";
	
	SimpleEvaluator::SimpleEvaluator()
	{
	}
	SimpleEvaluator::~SimpleEvaluator(){
		while(!m_contexts.empty())
		{
			delete m_contexts.front();
			m_contexts.pop_front();
		}
	}


	Context * SimpleEvaluator::newContext(const std::string &sessionid, Context *const parent)
	{
		Context * cx = nullptr;
		if (!m_removedContexts.empty()) {
			cx = m_removedContexts.front();
			m_removedContexts.pop_front();
		}
		else {
			cx = new SimpleContext(parent);
		}
		m_contexts.push_back(cx);
		return cx;
	}


	void SimpleEvaluator::releaseContext(Context * const cx)
	{
		m_contexts.remove(cx);
		m_removedContexts.push_back(cx);
	}

	void SimpleEvaluator::deleteContext(size_t count) {
		while (!m_removedContexts.empty() && count--)
		{
			Context * const cx =  m_removedContexts.front();
			m_removedContexts.pop_front();
			delete cx;
		}
	}

	size_t SimpleEvaluator::getContextCount()
	{
		return m_contexts.size();
	}

	bool SimpleEvaluator::hasContext()
	{
		return !m_contexts.empty();
	}

}
}
