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
		Context * cx = new SimpleContext(parent);
		m_contexts.push_back(cx);
		return cx;
	}

	void SimpleEvaluator::deleteContext(Context * const cx){
		m_contexts.remove(cx);
		delete cx;
	}

	bool SimpleEvaluator::hasContext()
	{
		return !m_contexts.empty();
	}

}
}
