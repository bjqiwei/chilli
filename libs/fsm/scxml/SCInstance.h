#pragma once
#ifndef _SCXML_SCINSTANCE_HEADER_
#define _SCXML_SCINSTANCE_HEADER_
#include "Evaluator.h"
#include "Context.h"
#include "model/Datamodel.h"
#include "SCXMLHelper.h"
//#pragma warning(disable:4800)
#include <jsapi.h>
#include <string>
#include <map>
#include <set>
#include <list>
#include <log.h>
#include "Timer.h"
#include "lock.h"
#include <log4cplus/logger.h>
#if  defined(WIN32)
#include <Windows.h>
#else
typedef int HANDLE; 
#include <pthread.h>

typedef struct 
{
	pthread_mutex_t	mutex;
	pthread_cond_t		condition;
	int			semCount;	
}sem_private_struct, *sem_private;

#endif


namespace fsm
{
	//thread data Including thread handle and thread id
	struct thread_data {
		HANDLE thread_hnd;
#ifdef WIN32 
		unsigned thread_id;
#else
		pthread_t thread_id;
#endif
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
		static log4cplus::Logger log;

	public:
		SCInstance();
		virtual ~SCInstance();

		virtual Evaluator *getEvaluator() const;

		//virtual void setEvaluator(Evaluator *const evaluator);

		virtual  Context *getRootContext() const ;

		//virtual void setRootContext(Context *const context);

		virtual Context * getContext(xmlNodePtr xNode) const;
		virtual void removeContext(xmlNodePtr xNode);

		virtual Context *lookupContext(xmlNodePtr xNode);

		virtual void setContext(xmlNodePtr xNode, Context *const context);

		void StartTimerThread();
		void AddTimer(fsm::Timer & _timer);
		typedef void (*TimerFunction)(std::string); 
		TimerFunction timerFunction;
	private:
#ifdef WIN32
		static unsigned int __stdcall TimerThreadProc( void *pParam );
		HANDLE timerTheradSemaphore;
#else
		static void *  TimerThreadProc( void *pParam );
		sem_private timerTheradSemaphore;
#endif
		

		//定时器队列
		std::list<fsm::Timer >m_timer; 

		struct thread_data td;

		fsm::CLock m_lock;

	};
}
#endif //end head file