#pragma once
#ifndef _SCXML_SCINSTANCE_HEADER_
#define _SCXML_SCINSTANCE_HEADER_

//#pragma warning(disable:4800)
#include <string>
#include <map>
#include <set>
#include <queue>
#include <list>
#include <vector>

#include <log4cplus\logger.h>
#include <libxml\tree.h>
#include <jsapi.h>

#include "..\config.h"
#include "Context.h"
#include "Evaluator.h"
#include "..\common\Timer.h"

namespace fsm
{


	/// <summary>
	/// 状态机执行模块，包括脚本解析器和上下文的维护。
	/// 
	/// 
	/// </summary>

	class FSM_EXPORT SMInstance:public helper::TimerServer
	{
	private:
		/// <summary>
		/// The <code>Map</code> of <code>Context</code>s per
		/// </summary>
		mutable std::map<xmlNodePtr,Context *>contexts;//正在使用的Script 上下文
		mutable std::list<Context *>removedContexts;//已经不使用的Script 上下文

		/// <summary>
		/// The evaluator for expressions.
		/// </summary>
		mutable std::vector<Evaluator *>evaluator;//Script 虚拟机

		static log4cplus::Logger log;
	private:
		virtual Evaluator *getEvaluator() const;
	public:
		SMInstance();
		virtual ~SMInstance();


		//virtual void setEvaluator(Evaluator *const evaluator);

		virtual  Context *getRootContext() const ;

		//virtual void setRootContext(Context *const context);

		virtual Context * getContext(xmlNodePtr xNode) const;
		virtual void removeContext(xmlNodePtr xNode);

		virtual Context *lookupContext(xmlNodePtr xNode);

		virtual void setContext(xmlNodePtr xNode, Context *const context);
	private:


	};
}
#endif //end head file