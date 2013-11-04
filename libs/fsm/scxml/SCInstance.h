#pragma once
#ifndef _SCXML_SCINSTANCE_HEADER_
#define _SCXML_SCINSTANCE_HEADER_
#include "Evaluator.h"
#include "Context.h"
#include "model/Datamodel.h"
#include "SCXMLHelper.h"
#pragma warning(disable:4800)
#include <jsapi.h>
#include <string>
#include <map>
#include <set>
#include <list>
#include "Timer.h"




namespace fsm
{
	//thread data Including thread handle and thread id
	struct thread_data {
		HANDLE thread_hnd;
		unsigned thread_id;
	};

	/// <summary>
	/// 状态机执行模块，包括脚本解析器和上下文的维护。
	/// 
	/// 
	/// </summary>

	class FSM_EXPORT SCInstance
	{
	private:
		/// <summary>
		/// The <code>Map</code> of <code>Context</code>s per
		/// <code>TransitionTarget</code>.
		/// </summary>
		mutable std::map<xmlNodePtr,Context *>contexts;

		/// <summary>
		/// The evaluator for expressions.
		/// </summary>
		mutable Evaluator *evaluator;

		/// <summary>
		/// The root context.
		/// </summary>
		//mutable Context *rootContext;
		log4cplus::Logger log;
		mutable JSClass *global_cls;
		JSFunctionSpec * functions;
	public:
		SCInstance();
		virtual ~SCInstance();

		virtual Evaluator *getEvaluator() const;

		//virtual void setEvaluator(Evaluator *const evaluator);

		virtual  Context *getRootContext(log4cplus::Logger log) const ;

		//virtual void setRootContext(Context *const context);

		virtual Context * getContext(xmlNodePtr xNode,log4cplus::Logger log) const;
		virtual void removeContext(xmlNodePtr xNode);

		virtual Context *lookupContext(xmlNodePtr xNode);

		virtual void setContext(xmlNodePtr xNode, Context *const context);
		void setLog(log4cplus::Logger log);
		void StartTimerThread();
		void AddTimer(fsm::Timer _timer);
		typedef void (*addEvent)(std::string); 
		addEvent addEventFunction;
	private:
		static unsigned int __stdcall TimerThreadProc( void *pParam );
		HANDLE timerTheradSemaphore;

		//定时器队列
		std::list<fsm::Timer >m_timer; 

		thread_data td;

		//临界资源
		CRITICAL_SECTION csection;
	};
}
#endif //end head file