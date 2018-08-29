#pragma once
#include "../Evaluator.h"
#include <log4cplus/logger.h>

#ifdef XP_WIN
# include <direct.h>
# include <process.h>
#endif
#include <errno.h>
#include <fcntl.h>
#if defined(XP_WIN)
# include <io.h>     /* for isatty() */
#endif
#include <locale.h>
#if defined(MALLOC_H)
# include MALLOC_H    /* for malloc_usable_size, malloc_size, _msize */
#endif
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef XP_UNIX
# include <sys/mman.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
#endif

#include "jsapi.h"
#include "jsprf.h"
#include "jstypes.h"

#ifdef XP_WIN
# include "jswin.h"
#endif
#include "jswrapper.h"

#include "js/Debug.h"
#include "js/GCAPI.h"
#include "js/Initialization.h"
#include "js/StructuredClone.h"
#include "js/TrackedOptimizationInfo.h"
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
