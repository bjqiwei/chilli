
#include "SCInstance.h"
#include "env/JSEvaluator.h"
#include <log4cplus/loggingmacros.h>
#ifdef WIN32
#include <process.h>
#include <Windows.h>
#else
#include <errno.h>
#include <semaphore.h>
#include <sys/timeb.h>

#endif

namespace fsm
{

	log4cplus::Logger SCInstance::log = log4cplus::Logger::getInstance("SCInstance");
	SCInstance::SCInstance():evaluator(NULL),timerFunction(NULL)
	{
		
#ifdef WIN32
		timerTheradSemaphore = CreateSemaphore(NULL, 0, LONG_MAX, NULL);
		if (NULL == timerTheradSemaphore){
			LOG4CPLUS_ERROR(log,"Structure SCInstance encountered an error,error=" << GetLastError());
		}
#else
		int rc;
		timerTheradSemaphore = new sem_private_struct();
		if((rc = pthread_mutex_init(&(timerTheradSemaphore->mutex), NULL)))
		{
			delete timerTheradSemaphore;
			LOG4CPLUS_ERROR(log,"Structure SCInstance encountered an error,error=" << errno);
			return ;
		}

		if((rc = pthread_cond_init(&(timerTheradSemaphore->condition), NULL)))
		{
			pthread_mutex_destroy( &(timerTheradSemaphore->mutex) );
			delete timerTheradSemaphore;
			LOG4CPLUS_ERROR(log,"Structure SCInstance encountered an error,error=" << errno);
			return ;
		}

		timerTheradSemaphore->semCount = 0;
#endif
		StartTimerThread();
		LOG4CPLUS_DEBUG(log,"new fsm.SCInstance object.");
	}

	SCInstance::~SCInstance()
	{
#ifdef WIN32
		ReleaseSemaphore(timerTheradSemaphore, 1, NULL);
#else
		pthread_mutex_lock(&(timerTheradSemaphore->mutex));
		timerTheradSemaphore->semCount ++;
		pthread_cond_signal(&(timerTheradSemaphore->condition));
		pthread_mutex_unlock(&(timerTheradSemaphore->mutex));
#endif
		
		for (std::map<xmlNodePtr,Context*>::const_iterator it = contexts.begin();
			it != contexts.end(); it++)
		{
			delete it->second;
		}
		contexts.clear();
		//if (rootContext) delete rootContext;
		if (evaluator) delete evaluator;
#ifdef WIN32
		CloseHandle(td.thread_hnd);
#endif

		LOG4CPLUS_DEBUG(log , "destruction fsm.SCInstance object.");
	}
	Evaluator *SCInstance::getEvaluator()const
	{
		if (evaluator == NULL)
		{
			try
			{
				LOG4CPLUS_INFO(log,"evaluator is null ,new a JSEvaluator.");
				evaluator = new env::JSEvaluator();
			}
			
			catch (...)
			{
				throw;
			}
		}
		return evaluator;
	}

	//void SCInstance::setEvaluator(Evaluator *const evaluator)
	//{
	//	if (evaluator) delete evaluator;
	//	this->evaluator = evaluator;
	//}

	Context *SCInstance::getRootContext()const
	{
		if (getEvaluator() != 0)
		{
			if (contexts[0] == 0)
			{
				contexts[0] = getEvaluator()->newContext(NULL);
			}
			return contexts[0];
		}
		return NULL;
	}

	//void SCInstance::setRootContext(Context *const context)
	//{
	//	if (rootContext) delete rootContext;
	//
	//	this->rootContext = context;
	//}

	Context *SCInstance::getContext(xmlNodePtr xNode)const
	{
		Context *context =NULL ; 
		if (contexts.count(xNode) > 0)
		{
			context=contexts[xNode];
			//LOG4CPLUS_DEBUG(log,"find a context by id=" << xNode);
		}
		if (context == NULL && xNode != NULL)
		{
			
			xmlNodePtr parent = xNode->parent;
			if (parent == 0 || parent->type == XML_DOCUMENT_NODE)
			{// docroot
				LOG4CPLUS_DEBUG(log,"not find  context by id=" << xNode << ",serch parent context,parent id=NULL");
				context = getEvaluator()->newContext(getRootContext());
			}
			else
			{
				LOG4CPLUS_DEBUG(log,"not find  context by id=" << xNode << ",serch parent context,parent id=" << parent);
				context = getEvaluator()->newContext(getContext(parent));
			}
			contexts[xNode] = context;
		}
		return context;
	}
	void SCInstance::removeContext(xmlNodePtr xNode)
	{
		if (contexts.count(xNode) > 0 && contexts[xNode] != NULL)
		{
			delete contexts[xNode];
		}
		contexts.erase(xNode);
	}
	Context *SCInstance::lookupContext(xmlNodePtr xNode)
	{
		if (contexts.count(xNode) > 0)
		{
			return contexts[xNode];
		}
		return NULL;
	}

	void SCInstance::setContext(xmlNodePtr xNode, Context *const context)
	{
		if (contexts[xNode] != NULL)
		{
			delete contexts[xNode];
		}
		contexts[xNode] = context;
	}

#ifdef WIN32 
	unsigned int SCInstance::TimerThreadProc( void *pParam )
#else
	void * SCInstance::TimerThreadProc( void *pParam )
#endif
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("StateMachine.TimerThread");
		LOG4CPLUS_TRACE(log,"start up thread.");
		SCInstance * scInstance = (SCInstance *)pParam;
#ifdef WIN32
		HANDLE semaphore = scInstance->timerTheradSemaphore;
		DWORD rv;
		while(1)
		{
			rv = WaitForSingleObject(semaphore,10);
			switch (rv) {
			case WAIT_OBJECT_0:{

					CloseHandle(semaphore);
					LOG4CPLUS_INFO(log,"exit timer thread.");
					_endthreadex(0);
					return 0;
				}
				break;
			case WAIT_TIMEOUT:
#else

		sem_private semaphore = scInstance->timerTheradSemaphore;
		int rv;
		while(1)
		{
			struct timespec tm;
			struct timeb tp;
			long millisec = 10;

			ftime( &tp );
			tp.time += millisec/1000;
			tp.millitm += millisec % 1000;
			if( tp.millitm > 999 ){
				tp.millitm -= 1000;
				tp.time++;
			}

			tm.tv_sec = tp.time;
			tm.tv_nsec = tp.millitm*1000000;
			rv = 0;
			pthread_mutex_lock(&(semaphore->mutex));
			while (semaphore->semCount <= 0)
			{
				rv = pthread_cond_timedwait(&(semaphore->condition), &(semaphore->mutex), &tm);
				if (rv && (errno != EINTR) )
					break;
			}
			if(rv == 0)semaphore->semCount--;
			pthread_mutex_unlock(&(semaphore->mutex));
			//LOG4CPLUS_TRACE(log,"pthread_cond_timewait finished.");
			switch(rv){
			case 0:{
					pthread_mutex_destroy(&(semaphore->mutex));
					pthread_cond_destroy(&(semaphore->condition));
					delete semaphore;
					LOG4CPLUS_INFO(log,"exit timer thread.");
					pthread_exit(0);
					return 0;
				   }
				   break;
			case ETIMEDOUT:
#endif
				scInstance->m_lock.Lock();
				for (std::list<Timer>::iterator iter =scInstance->m_timer.begin();iter != scInstance->m_timer.end(); iter++)
				{
					if (iter->valid == false)
					{
						iter = scInstance->m_timer.erase(iter);
						break;
					}
				}
			
				for (std::list<Timer>::iterator iter =scInstance->m_timer.begin();iter != scInstance->m_timer.end(); iter++)
				{
					std::string strContent = iter->Step();
		
					if (scInstance->timerFunction != NULL && !SCXMLHelper::isStringEmpty(strContent))
					{
						scInstance->timerFunction(strContent);
					}else if (scInstance->timerFunction == NULL && !SCXMLHelper::isStringEmpty(strContent))
					{
						LOG4CPLUS_ERROR(log,"timer event callback function is empty. event=" << strContent);
					}
				}
				scInstance->m_lock.Unlock();
				break;
#ifdef WIN32
			case WAIT_FAILED:
				LOG4CPLUS_ERROR(log,"WaitForSingleObject, wait failed.error=" << GetLastError());
#else
			case EINVAL:
			case EPERM:
				LOG4CPLUS_ERROR(log,"WaitForSingleObject, wait failed.error=" << errno);
#endif	
				break;
			default:
				LOG4CPLUS_WARN(log,"WaitForSingleObject, unknow single.");
				break;
			}
		}
		LOG4CPLUS_TRACE(log,"end thread.");
		return NULL;
	}

	void SCInstance::StartTimerThread(){

#ifdef WIN32
		td.thread_hnd = (HANDLE)_beginthreadex(NULL,0,TimerThreadProc,this,0,&td.thread_id);
		if (!td.thread_hnd){
			LOG4CPLUS_ERROR(log,"_beginthreadex() TimerThreadProc failed;error no.=" << GetLastError());
		}else{
			LOG4CPLUS_DEBUG(log,"_beginthreadex() TimerThreadProc ok;thread_id="  << td.thread_id);
		}
#else
		td.thread_hnd = pthread_create(&td.thread_id,NULL,(void*(*)(void*))TimerThreadProc,this);
		if (td.thread_hnd){
			LOG4CPLUS_ERROR(log,"_beginthreadex() TimerThreadProc failed;error no.=" << errno);
		}else{
			LOG4CPLUS_DEBUG(log,"_beginthreadex() TimerThreadProc ok;thread_id="  << td.thread_id);
		}	
#endif
		
	}

	void SCInstance::AddTimer(Timer & _timer)
	{
		this->m_lock.Lock();
		m_timer.push_back(_timer);
		this->m_lock.Unlock();
	}
}

