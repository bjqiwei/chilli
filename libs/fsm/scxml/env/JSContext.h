#pragma once
#ifndef _FSM_ENV_JSCONTEXT_HEADER_
#define _FSM_ENV_JSCONTEXT_HEADER_
#include "../Context.h"
#include "mozilla/ArrayUtils.h"
#include "mozilla/Atomics.h"
#include "mozilla/DebugOnly.h"
#include "mozilla/GuardObjects.h"
#include "mozilla/mozalloc.h"
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