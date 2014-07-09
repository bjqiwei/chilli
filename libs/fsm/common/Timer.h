#ifndef _COMMON_TIMER_HEADER_
#define _COMMON_TIMER_HEADER_
#include <queue>
#include <sys/timeb.h>
#include "lock.h"
#if  defined(WIN32)
#include <Windows.h>
#include <process.h>
#else
typedef int HANDLE; 
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>
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


	// 定时器
	class TimerServer{
	private:
		//定时器对象。
		class  Timer{
		public:
			//生成一个定时器对象，时间间隔，定时器id，
			Timer( long interval,const std::string &strTimerId):
			  m_strTimerId(strTimerId),m_interval(interval)
			  {
				  ftime(&m_startTime);
			  }
			  virtual ~Timer(){};

			  time_t getInterval() const{
				  struct timeb currTime;
				  ftime(&currTime);
				  time_t  i = m_interval - ((currTime.time-m_startTime.time)*1000 + currTime.millitm-m_startTime.millitm);
				  return i > 0?i:0;
			  };

		public:
			const std::string m_strTimerId;
		private:
			const long m_interval;
			struct timeb m_startTime;
			Timer & operator=( const Timer & );
		};
		class TimerComp{
		public:
			bool operator() (const Timer * const A, const Timer * const B)
			{
				return (A->getInterval()  > B->getInterval());
			}

		};
	public:
		typedef void (*TimerFunction)(const std::string &); 
		TimerFunction timerFunction;
	private:
		//定时器队列
		typedef std::priority_queue<Timer *,std::vector<Timer *>, TimerComp> TIMER_QUEUE;
		TIMER_QUEUE m_timer; 
		struct thread_data td;
		helper::CLock m_timerLock;
#ifdef WIN32
		HANDLE sem;
#else
		sem_private sem;
#endif
	public:
		TimerServer():timerFunction(NULL){
#ifdef WIN32
			sem = CreateSemaphore(NULL, 0, LONG_MAX, NULL);
#else
			int rc;
			sem = new sem_private_struct();
			if((rc = pthread_mutex_init(&(sem->mutex), NULL)))
			{
				delete sem;
				return ;
			}

			if((rc = pthread_cond_init(&(sem->condition), NULL)))
			{
				pthread_mutex_destroy( &(sem->mutex) );
				delete sem;
				return ;
			}

			sem->semCount = 0;
#endif
			StartTimerThread();
		}

		virtual ~TimerServer(){
#ifdef WIN32
			TerminateThread(td.thread_hnd,0);
			CloseHandle(sem);
#else
			pthread_cancel(td.thread_id);
			pthread_join(td.thread_id, NULL);
			pthread_mutex_destroy(&(sem->mutex));
			pthread_cond_destroy(&(sem->condition));
			delete sem;
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
#else
		static void *  TimerThreadProc( void *pParam ){
#endif
			TimerServer * This = static_cast<TimerServer *>(pParam);

#ifdef WIN32
			time_t millisec = INFINITE;
			DWORD rv;
			while(true)
			{
				rv = WaitForSingleObject(This->sem, millisec);
#else
			#define  INFINITE  (0x7fffffffffffffff)
			time_t millisec = INFINITE;
			pthread_setcanceltype(PTHREAD_CANCEL_ENABLE,NULL);
			pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
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
				pthread_mutex_lock(&(This->sem->mutex));
				while (This->sem->semCount <= 0)
				{
					rv = pthread_cond_timedwait(&(This->sem->condition), &(This->sem->mutex), &tm);
					if (rv && (errno != EINTR) )
						break;
				}
				if(rv == 0)This->sem->semCount--;
				pthread_mutex_unlock(&(This->sem->mutex));

#endif
				switch (rv) {
#ifdef WIN32
					case WAIT_TIMEOUT:
#else// WIN32
					case ETIMEDOUT:
#endif 
					This->m_timerLock.Lock();
					while(!This->m_timer.empty()){
						Timer * timer = This->m_timer.top();

						millisec = This->m_timer.top()->getInterval();
						//LOG4CPLUS_DEBUG(log,"timer event . interval=" << millisec );
						if (millisec > 0){
							break;
						}
					

						if (This->timerFunction != NULL)
						{
							This->timerFunction(timer->m_strTimerId);
						}
						This->m_timer.pop();
						delete timer;
					}
					This->m_timerLock.Unlock();
#ifdef WIN32
				case WAIT_OBJECT_0:
#else// WIN32
				case 0:
#endif				
					This->m_timerLock.Lock();
					if (!This->m_timer.empty())
					{
						millisec = This->m_timer.top()->getInterval();
					}else{
						millisec = INFINITE;
					}
					This->m_timerLock.Unlock();
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

	public:
		void SetTimer(int interval, const std::string & strTimerId ){

			Timer * _timer = new Timer(interval, strTimerId);
			this->m_timerLock.Lock();
			m_timer.push(_timer);
			this->m_timerLock.Unlock();
#ifdef WIN32
			ReleaseSemaphore(sem, 1, NULL);
#else
			pthread_mutex_lock(&(sem->mutex));
			sem->semCount ++;
			pthread_cond_signal(&(sem->condition));
			pthread_mutex_unlock(&(sem->mutex));
			
#endif
		}

	};
}//end namespace helper
#endif//end timer header