
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

	log4cplus::Logger SCInstance::log = log4cplus::Logger::getInstance("fsm.SCInstance");
	SCInstance::SCInstance():timerFunction(NULL)
	{
		LOG4CPLUS_DEBUG(log,"new fsm.SCInstance object...");
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
		LOG4CPLUS_DEBUG(log , "destruction fsm.SCInstance object...");
#ifdef WIN32
		TerminateThread(td.thread_hnd,0);
		CloseHandle(timerTheradSemaphore);
#else
		pthread_cancel(td.thread_id);
		pthread_mutex_destroy(&(timerTheradSemaphore->mutex));
		pthread_cond_destroy(&(timerTheradSemaphore->condition));
		delete timerTheradSemaphore;
#endif
		
		contexts.clear();

		removedContexts.clear();
		//if (rootContext) delete rootContext;
		for (std::vector<Evaluator *>::iterator it = evaluator.begin(); it != evaluator.end(); ++it)
		{
			delete *it;
		}

			
		LOG4CPLUS_DEBUG(log , "destruction fsm.SCInstance object.");
	}
	Evaluator *SCInstance::getEvaluator()const
	{
		LOG4CPLUS_DEBUG(log,"getEvaluator,evaluator vector size="<< evaluator.size());
		for (std::vector<Evaluator *>::iterator it = evaluator.begin(); it != evaluator.end(); ++it)
		{
			if((*it)->hasContext()){
				LOG4CPLUS_DEBUG(log,"find a evaluator " << *it);
				return *it;
			}
		}
		
		Evaluator * evl = NULL;
		try
		{
			LOG4CPLUS_INFO(log,"not find idle evaluator ,new a JSEvaluator.");
			evl = new env::JSEvaluator();
			evaluator.push_back(evl);
			return evl;
		}
			
		catch (...)
		{
			throw;
		}
		return NULL;
	}

	//void SCInstance::setEvaluator(Evaluator *const evaluator)
	//{
	//	if (evaluator) delete evaluator;
	//	this->evaluator = evaluator;
	//}

	Context *SCInstance::getRootContext()const
	{
		/*if (getEvaluator() != 0)
		{
			if (contexts[0] == 0)
			{
				contexts[0] = getEvaluator()->newContext(NULL);
			}
			return contexts[0];
		}*/
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
		std::map<xmlNodePtr,Context *>::iterator it = contexts.find(xNode);
		if (it != contexts.end())
		{
			context = it->second;
			//LOG4CPLUS_DEBUG(log,"find the context "  << context <<" by key:" << xNode);
		}
		
		if (context == NULL && xNode != NULL)
		{
			if (!removedContexts.empty())
			{
				context = removedContexts.front();
				removedContexts.pop_front();
				LOG4CPLUS_DEBUG(log,"find a context " << context << " in the removedContext set. still has " << removedContexts.size());
			}
			

			if (context == NULL)
			{
				Evaluator * evl = getEvaluator();
				context = evl->newContext(NULL);
			}
			
			//xmlNodePtr parent = xNode->parent;
			//if (parent == 0 || parent->type == XML_DOCUMENT_NODE)
			//{// docroot
			//	LOG4CPLUS_DEBUG(log,"not find  context by id=" << xNode << ",serch parent context,parent id=NULL");
			//	//context = getEvaluator()->newContext(getRootContext());
			//}
			//else
			//{
			//	LOG4CPLUS_DEBUG(log,"not find  context by id=" << xNode << ",serch parent context,parent id=" << parent);
			//	context = getEvaluator()->newContext(getContext(parent));
			//}
			contexts[xNode] = context;
		}
		return context;
	}
	void SCInstance::removeContext(xmlNodePtr xNode)
	{
		std::map<xmlNodePtr,Context *>::iterator it = contexts.find(xNode);
		if (it != contexts.end())
		{
			LOG4CPLUS_DEBUG(log,"removeing context " << it->second);
			//delete contexts[xNode];

			removedContexts.push_back(it->second);
			it->second->reset();
			contexts.erase(it);
			LOG4CPLUS_DEBUG(log,"remove from contexts to removedContexts,contexts size " << contexts.size() << " add  removedContexts size " << removedContexts.size());
		}
		
		LOG4CPLUS_DEBUG(log,"context size:" << contexts.size());
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
		unsigned long millisec = INFINITE;
		HANDLE semaphore = scInstance->timerTheradSemaphore;
		DWORD rv;
		while(1)
		{
			rv = WaitForSingleObject(semaphore,millisec);
#else
#define  MAXLONGLONG  (0x7fffffffffffffff)
		long long millisec = MAXLONGLONG;
		pthread_setcanceltype(PTHREAD_CANCEL_ENABLE,NULL);
		pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
		sem_private semaphore = scInstance->timerTheradSemaphore;
		int rv;
		while(1)
		{
			struct timespec tm;
			struct timeb tp;

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
				LOG4CPLUS_DEBUG(log,"set cond_timewait . interval=" << millisec );
				rv = pthread_cond_timedwait(&(semaphore->condition), &(semaphore->mutex), &tm);
				if (rv && (errno != EINTR) )
					break;
			}
			if(rv == 0)semaphore->semCount--;
			pthread_mutex_unlock(&(semaphore->mutex));
			//LOG4CPLUS_TRACE(log,"pthread_cond_timewait finished.");
#endif
			switch (rv) {
#ifdef WIN32
				case WAIT_TIMEOUT:
#else// WIN32
				case ETIMEDOUT:
#endif 
				scInstance->m_timerLock.Lock();
				while(!scInstance->m_timer.empty()){
					fsm::Timer * timer = scInstance->m_timer.top();

					millisec = scInstance->m_timer.top()->getInterval();
					//LOG4CPLUS_DEBUG(log,"timer event . interval=" << millisec );
					if (millisec > 0){
						break;
					}
					
					std::string strContent = timer->execute();

					if (scInstance->timerFunction != NULL)
					{
						scInstance->timerFunction(strContent);
					}else if (scInstance->timerFunction == NULL)
					{
						LOG4CPLUS_ERROR(log,"timer event callback function is empty. event=" << strContent);
					}
					scInstance->m_timer.pop();
					delete timer;
					
				}
				/*for (std::priority_queue<fsm::Timer *,vector<fsm::Timer *>,fsm::Timer>::iterator iter =scInstance->m_timer.begin();iter != scInstance->m_timer.end();)
				{
					if ((*iter)->valid == false)
					{
						delete (*iter);
						scInstance->m_timer.erase(iter++);
					}else
						iter++;
				}
			
				for (std::priority_queue<fsm::Timer *,vector<fsm::Timer *>,fsm::Timer>::iterator iter =scInstance->m_timer.begin();iter != scInstance->m_timer.end(); iter++)
				{
					std::string strContent = (*iter)->Step();
		
					if (scInstance->timerFunction != NULL && !SCXMLHelper::isStringEmpty(strContent))
					{
						scInstance->timerFunction(strContent);
					}else if (scInstance->timerFunction == NULL && !SCXMLHelper::isStringEmpty(strContent))
					{
						LOG4CPLUS_ERROR(log,"timer event callback function is empty. event=" << strContent);
					}
				}*/
				scInstance->m_timerLock.Unlock();
#ifdef WIN32
			case WAIT_OBJECT_0:
#else// WIN32
			case 0:
#endif 

				if (!scInstance->m_timer.empty())
				{
					millisec = scInstance->m_timer.top()->getInterval();
					continue;
				}else{
					millisec = MAXLONGLONG;
					continue;
				}
				LOG4CPLUS_DEBUG(log,"ResumeThread.");
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

	void SCInstance::AddTimer(Timer * _timer)
	{
		this->m_timerLock.Lock();
		m_timer.push(_timer);
#ifdef WIN32
		ReleaseSemaphore(timerTheradSemaphore, 1, NULL);
#else
		pthread_mutex_lock(&(timerTheradSemaphore->mutex));
		timerTheradSemaphore->semCount ++;
		pthread_cond_signal(&(timerTheradSemaphore->condition));
		pthread_mutex_unlock(&(timerTheradSemaphore->mutex));
#endif
		this->m_timerLock.Unlock();
	}
}

