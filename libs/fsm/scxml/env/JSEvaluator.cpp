#include "JSEvaluator.h"
#include "JSContext.h"
#include <log4cplus/loggingmacros.h>


namespace fsm
{
namespace env
{

	JSEvaluator::JSEvaluator()
	{
		log = log4cplus::Logger::getInstance("fsm.JSEvaluator");
		LOG4CPLUS_DEBUG(log,"construct a JSEvaluator object.");		
	}
	JSEvaluator::~JSEvaluator(){
		
		if (!m_contexts.empty())
			LOG4CPLUS_WARN(log, "has " << m_contexts.size() << " context when evaluator delete.");

		while(!m_contexts.empty())
		{
			LOG4CPLUS_DEBUG(log,"contexts size " << m_contexts.size());
			delete m_contexts.front();
			m_contexts.pop_front();
		}

		LOG4CPLUS_DEBUG(log, "deconstruct a JSEvaluator object.");
	}


	Context * JSEvaluator::newContext(const std::string &sessionid, Context *const parent)
	{
		//LOG4CPLUS_DEBUG(log, sessionid << " new a JsContext,parent="<< parent);
		std::lock_guard<std::mutex>lck(m_mtx);
		Context * cx = new env::JsContext(sessionid, this, parent);
		m_contexts.push_back(cx);
		LOG4CPLUS_DEBUG(log, "push context:" << cx << " contexts size " << m_contexts.size());
		return cx;

	}
	void JSEvaluator::deleteContext(Context * const cx)
	{
		std::lock_guard<std::mutex>lck(m_mtx);
		m_contexts.remove(cx);
		delete cx;
		LOG4CPLUS_DEBUG(log, "remove context:" << cx << " contexts size " << m_contexts.size());
	}

	bool JSEvaluator::hasContext()
	{
		std::lock_guard<std::mutex>lck(m_mtx);
		return !m_contexts.empty();
	}

}
}
