#include "JSEvaluator.h"
#include "JSContext.h"
#include <log4cplus/loggingmacros.h>
#include <mutex>


namespace fsm
{
namespace env
{
	static std::atomic_ulong g_JSEvaluatorReferce(0);

	static const size_t gMaxHeapSize = 1024 * 1024 * 1024;

#if defined(DEBUG)
	static const size_t gMaxStackSize = 2 * 128 * sizeof(size_t) * 1024;
#else
	static const size_t gMaxStackSize = 128 * sizeof(size_t) * 1024;
#endif

	static std::mutex g_InitMtx;

	static void reportError(::JSContext *cx, const char *message, JSErrorReport *report);

	JSEvaluator::JSEvaluator()
	{
		log = log4cplus::Logger::getInstance("fsm.JSEvaluator");

		std::unique_lock<std::mutex> lck(g_InitMtx);
		if (g_JSEvaluatorReferce.fetch_add(1) == 0) {
			if (!JS_Init()) {
				LOG4CPLUS_ERROR(log, "", ",JS_Init error.");
				throw std::logic_error("JS_Init error.");
			}
		}
		this->m_jsrt = JS_NewRuntime(gMaxHeapSize); // JS_NewRuntime 不是线程安全的，需要做线程安全处理

		lck.unlock();
		if ( m_jsrt == NULL ){
			LOG4CPLUS_ERROR(log, "", "new evaluator runtime error.");
			throw std::logic_error("JS_NewRuntime error.");
		}

		JS_SetErrorReporter(m_jsrt, reportError);

		JS_SetNativeStackQuota(m_jsrt, gMaxStackSize);

		LOG4CPLUS_DEBUG(log, "", "construct a JSEvaluator object.");

	}
	JSEvaluator::~JSEvaluator(){
		
		if (!m_contexts.empty())
			LOG4CPLUS_WARN(log, "", "has " << m_contexts.size() << " context when evaluator delete.");

		if (m_jsrt)
			JS_DestroyRuntime(m_jsrt);

		g_InitMtx.lock();
		if (g_JSEvaluatorReferce.fetch_sub(1) == 1) {
			JS_ShutDown();
		}
		g_InitMtx.unlock();
		LOG4CPLUS_DEBUG(log, "", "deconstruct a JSEvaluator object.");
	}


	Context * JSEvaluator::newContext(const std::string &sessionid, Context *const parent)
	{
		//LOG4CPLUS_DEBUG(log, sessionid << " new a JsContext,parent="<< parent);
		Context * cx = nullptr;
		if (!m_removedContexts.empty()){
			cx = m_removedContexts.front();
			m_removedContexts.pop_front();
		}
		else {
			cx = new env::JsContext(this->m_jsrt, sessionid, this, parent);
		}
		m_contexts.push_back(cx);
		return cx;

	}

	void JSEvaluator::releaseContext(Context * const cx)
	{
		m_contexts.remove(cx);
		m_removedContexts.push_back(cx);
	}

	void JSEvaluator::deleteContext(size_t count)
	{
		while (!m_removedContexts.empty() && count--)
		{
			Context * const cx = m_removedContexts.front();
			m_removedContexts.pop_front();
			delete cx;
		}
	}

	size_t JSEvaluator::getContextCount()
	{
		return m_contexts.size() + m_removedContexts.size();
	}

	bool JSEvaluator::hasContext()
	{
		return getContextCount() > 0;
	}


	static void reportError(::JSContext *cx, const char *message, JSErrorReport *report) {

		const JsContext * This = (JsContext *)JS_GetContextPrivate(cx);

		// Get exception object before printing and clearing exception.
		JS::RootedValue exception(cx);
		if (JS_IsExceptionPending(cx))
			JS_GetPendingException(cx, &exception);

		JS_ClearPendingException(cx);

		if (!report) {
			throw jsexception(message, 0, 0, 0);
		}
		else {
			throw jsexception(message, report->filename, report->lineno, report->column);
		}
	}
}
}
