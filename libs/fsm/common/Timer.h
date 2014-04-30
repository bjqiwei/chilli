#ifndef _COMMON_TIMER_HEADER_
#define _COMMON_TIMER_HEADER_
#include <queue>
#include <sys/timeb.h>
#include "lock.h"
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

//thread data Including thread handle and thread id
struct thread_data {
	HANDLE thread_hnd;
#ifdef WIN32 
	unsigned thread_id;
#else
	pthread_t thread_id;
#endif
};

namespace helper{
	//定时器对象。
	class  Timer{
	public:
		//生成一个定时器对象，时间间隔，定时器id，
		Timer( int interval,const std::string &strTimerId):
		  m_strTimerId(strTimerId),m_interval(interval)
		  {
			  ftime(&m_startTime);
		  }
		virtual ~Timer(){};

		unsigned long long getInterval() const{
			struct timeb currTime;
			ftime(&currTime);
			long long i = m_interval - ((currTime.time-m_startTime.time)*1000 + currTime.millitm-m_startTime.millitm);
			return i > 0?i:0;
		};

	public:
		const std::string m_strTimerId;
	private:
		const int m_interval;
		struct timeb m_startTime;
	};
	class TimerComp{
	public:
		bool operator() (const Timer * const A, const Timer * const B)
		{
			return (A->getInterval()  > B->getInterval());
		}

	};

	// 定时器
	class TimerServer{
	public:
		TimerServer():timerFunction(NULL){
#ifdef WIN32
			timerTheradSemaphore = CreateSemaphore(NULL, 0, LONG_MAX, NULL);
#else
			int rc;
			timerTheradSemaphore = new sem_private_struct();
			if((rc = pthread_mutex_init(&(timerTheradSemaphore->mutex), NULL)))
			{
				delete timerTheradSemaphore;
				return ;
			}

			if((rc = pthread_cond_init(&(timerTheradSemaphore->condition), NULL)))
			{
				pthread_mutex_destroy( &(timerTheradSemaphore->mutex) );
				delete timerTheradSemaphore;
				return ;
			}

			timerTheradSemaphore->semCount = 0;
#endif
			StartTimerThread();
		}

		virtual ~TimerServer(){
#ifdef WIN32
			TerminateThread(td.thread_hnd,0);
			CloseHandle(timerTheradSemaphore);
#else
			pthread_cancel(td.thread_id);
			pthread_mutex_destroy(&(timerTheradSemaphore->mutex));
			pthread_cond_destroy(&(timerTheradSemaphore->condition));
			delete timerTheradSemaphore;
#endif
		}
	private:
		void StartTimerThread(){
#ifdef WIN32
			td.thread_hnd = (HANDLE)_beginthreadex(NULL,0,TimerThreadProc,this,0,&td.thread_id);
#else
			td.thread_hnd = pthread_create(&td.thread_id,NULL,(void*(*)(void*))TimerThreadProc,this);
#endif
		}
#ifdef WIN32
		static unsigned int __stdcall TimerThreadProc( void *pParam ){

			TimerServer * timerInstance = (TimerServer *)pParam;

	#ifdef WIN32
			unsigned long millisec = INFINITE;
			HANDLE semaphore = timerInstance->timerTheradSemaphore;
			DWORD rv;
			while(1)
			{
				rv = WaitForSingleObject(semaphore,millisec);
	#else
	#define  MAXLONGLONG  (0x7fffffffffffffff)
			long long millisec = MAXLONGLONG;
			pthread_setcanceltype(PTHREAD_CANCEL_ENABLE,NULL);
			pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
			sem_private semaphore = smInstance->timerTheradSemaphore;
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
					timerInstance->m_timerLock.Lock();
					while(!timerInstance->m_timer.empty()){
						Timer * timer = timerInstance->m_timer.top();

						millisec = smInstance->m_timer.top()->getInterval();
						//LOG4CPLUS_DEBUG(log,"timer event . interval=" << millisec );
						if (millisec > 0){
							break;
						}
					
						std::string strContent = timer->execute();

						if (timerInstance->timerFunction != NULL)
						{
							timerInstance->timerFunction(strContent);
						}
						timerInstance->m_timer.pop();
						delete timer;
					}
					timerInstance->m_timerLock.Unlock();
	#ifdef WIN32
				case WAIT_OBJECT_0:
	#else// WIN32
				case 0:
	#endif 

					if (!timerInstance->m_timer.empty())
					{
						millisec = timerInstance->m_timer.top()->getInterval();
						continue;
					}else{
						millisec = MAXLONGLONG;
						continue;
					}

					break;
	#ifdef WIN32
				case WAIT_FAILED:
	#else
				case EINVAL:
				case EPERM:
	#endif	
					break;
				default:
					break;
				}
			}
		return NULL;
		}
		HANDLE timerTheradSemaphore;
#else
		static void *  TimerThreadProc( void *pParam );
		sem_private timerTheradSemaphore;
#endif

		void SetTimer(Timer * _timer){
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

		typedef void (*TimerFunction)(const std::string &); 
		TimerFunction timerFunction;
	private:
		//定时器队列
		typedef std::priority_queue<Timer *,std::vector<Timer *>, TimerComp> TIMER_QUEUE;
		TIMER_QUEUE m_timer; 

		struct thread_data td;

		helper::CLock m_timerLock;
	};
}//end namespace helper
#endif//end timer header