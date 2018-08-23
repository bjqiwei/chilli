#pragma once
#ifndef _FSM_ENV_JSEVALUATOR_HEADER_
#define _FSM_ENV_JSEVALUATOR_HEADER_
#include "../Evaluator.h"
#include <log4cplus/logger.h>
#include <mutex>
#include "mozilla/ArrayUtils.h"
#include "mozilla/Atomics.h"
#include "mozilla/DebugOnly.h"
#include "mozilla/GuardObjects.h"
#include "mozilla/PodOperations.h"

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
		

	class jsexception : public std::runtime_error {
	public:
		jsexception(const char * what, const char * file, uint32_t line, uint32_t column) :std::runtime_error(what),m_file(file?file:""),m_line(line),m_column(column)
		{

		}
		~jsexception()
		{

		}
		std::string m_file;
		uint32_t m_line;
		uint32_t m_column;
	};
	/// <summary>
	/// Evaluator implementation enabling use of JS expressions 
	/// 
	/// </summary>
	class JSEvaluator : public Evaluator
	{

	private:
			::JSRuntime *m_jsrt = nullptr;
			log4cplus::Logger log;
			std::mutex m_mtx;
	public:

		JSEvaluator(); 
		virtual ~JSEvaluator();

		virtual Context * newContext(const std::string &sessionid, Context *const parent) override;

		virtual void deleteContext(Context * const cx) override;

		virtual bool hasContext() override;

	};
}
}

#endif //end head file