#pragma once
#ifndef _SCXML_SCINSTANCE_HEADER_
#define _SCXML_SCINSTANCE_HEADER_

//#pragma warning(disable:4800)
#include "..\config.h"
#include <string>
#include <list>

#include <log4cplus/logger.h>
#include "../common/Timer.h"

namespace fsm
{


	/// <summary>
	/// 状态机执行模块，包括脚本解析器和上下文的维护。
	/// 
	/// 
	/// </summary>
	class Context;
	class Evaluator;
	typedef  void * ContextKey;

	class FSM_EXPORT SMInstance:public helper::TimerServer
	{
	private:
		/// <summary>
		/// The <code>Map</code> of <code>Context</code>s per
		/// </summary>
		mutable std::map<ContextKey, Context *>contexts;//正在使用的Script 上下文
		mutable std::list<Context *>removedContexts;//已经不使用的Script 上下文

		/// <summary>
		/// The evaluator for expressions.
		/// </summary>
		mutable std::vector<Evaluator *>evaluator;//Script 虚拟机

		log4cplus::Logger log;
	private:
		virtual Evaluator *getEvaluator() const;
	public:
		SMInstance(helper::CTimerNotify* observer);
		virtual ~SMInstance();


		//virtual void setEvaluator(Evaluator *const evaluator);

		virtual  Context *getRootContext() const ;

		//virtual void setRootContext(Context *const context);

		virtual Context * getContext(ContextKey xNode) const;
		virtual void removeContext(ContextKey xNode);

		virtual Context *lookupContext(ContextKey xNode);

		virtual void setContext(ContextKey xNode, Context *const context);
	private:


	};
}
#endif //end head file