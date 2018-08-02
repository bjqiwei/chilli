#include "JSEvaluator.h"
#include "JSContext.h"
#include <log4cplus/loggingmacros.h>


namespace fsm
{
namespace env
{
	static std::atomic_ulong g_JSEvaluatorReferce(0);

	static const size_t gMaxHeapSize = 512 * 1024 * 1024;

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
				LOG4CPLUS_ERROR(log, ",JS_Init error.");
				throw std::logic_error("JS_Init error.");
			}
		}

		this->m_jsrt = JS_NewRuntime(gMaxHeapSize);
		if ( m_jsrt == NULL ){
			LOG4CPLUS_ERROR(log, "new evaluator runtime error.");
			throw std::logic_error("JS_NewRuntime error.");
		}

		JS_SetErrorReporter(m_jsrt, reportError);

		JS_SetNativeStackQuota(m_jsrt, gMaxStackSize);

		LOG4CPLUS_TRACE(log,"construct a JSEvaluator object.");

	}
	JSEvaluator::~JSEvaluator(){
		
		std::unique_lock<std::mutex> lck(g_InitMtx);
		if (!m_contexts.empty())
			LOG4CPLUS_WARN(log, "has " << m_contexts.size() << " context when evaluator delete.");

		while(!m_contexts.empty())
		{
			LOG4CPLUS_DEBUG(log,"contexts size " << m_contexts.size());
			delete m_contexts.front();
			m_contexts.pop_front();
		}

		if (m_jsrt)
			JS_DestroyRuntime(m_jsrt);

		if (g_JSEvaluatorReferce.fetch_sub(1) == 1) {
			JS_ShutDown();
		}

		LOG4CPLUS_TRACE(log, "deconstruct a JSEvaluator object.");
	}


	Context * JSEvaluator::newContext(const std::string &sessionid, Context *const parent)
	{
		//LOG4CPLUS_DEBUG(log, sessionid << " new a JsContext,parent="<< parent);
		std::lock_guard<std::mutex>lck(m_mtx);
		Context * cx = new env::JsContext(this->m_jsrt, sessionid, this, parent);
		m_contexts.push_back(cx);
		LOG4CPLUS_TRACE(log, "push context:" << cx << " contexts size " << m_contexts.size());
		return cx;

	}
	void JSEvaluator::deleteContext(Context * const cx)
	{
		std::lock_guard<std::mutex>lck(m_mtx);
		m_contexts.remove(cx);
		delete cx;
		LOG4CPLUS_TRACE(log, "remove context:" << cx << " contexts size " << m_contexts.size());
	}

	bool JSEvaluator::hasContext()
	{
		std::lock_guard<std::mutex>lck(m_mtx);
		return !m_contexts.empty();
	}


	static void reportError(::JSContext *cx, const char *message, JSErrorReport *report) {

		const JsContext * This = (JsContext *)JS_GetContextPrivate(cx);

		// Get exception object before printing and clearing exception.
		JS::RootedValue exception(cx);
		if (JS_IsExceptionPending(cx))
			JS_GetPendingException(cx, &exception);

		if (!report) {
			LOG4CPLUS_ERROR(This->log, This->m_strSessionID << "," << message);
			return;
		}

		std::stringstream ss;
		ss << (report->filename ? report->filename : "<no filename="">")
			<< ":" << report->lineno << ":" << report->column << " ";

		if (JSREPORT_IS_WARNING(report->flags)) {
			ss << (JSREPORT_IS_STRICT(report->flags) ? "strict " : "") << "warning: ";
		}

		LOG4CPLUS_ERROR(This->log, This->m_strSessionID << "," << ss.str());

		if (message)
			LOG4CPLUS_ERROR(This->log, This->m_strSessionID << "," << message);


		if (const char16_t* linebuf = report->linebuf()) {
			size_t n = report->linebufLength();

			std::string buf;
			for (size_t i = 0; i < n; i++)
				buf.push_back(static_cast<char>(linebuf[i]));

			LOG4CPLUS_ERROR(This->log, This->m_strSessionID << "," << buf);

			//// linebuf usually ends with a newline. If not, add one here.
			//if (n == 0 || linebuf[n - 1] != '\n')
			//	fputc('\n', file);


			n = report->tokenOffset();
			buf.clear();
			for (size_t i = 0, j = 0; i < n; i++) {
				if (linebuf[i] == '\t') {
					for (size_t k = (j + 8) & ~7; j < k; j++)
						buf.push_back('.');
					continue;
				}
				buf.push_back('.');
				j++;
			}
			buf.push_back('^');
			LOG4CPLUS_ERROR(This->log, This->m_strSessionID << "," << buf);
		}
	}
}
}
