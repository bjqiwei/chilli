#ifndef _COMMON_TIMER_HEADER_
#define _COMMON_TIMER_HEADER_
#include <queue>
#include <sys/timeb.h>
#include "lock.h"
#include "Csemaphore.h"

#ifndef INFINITE
#define  INFINITE  (0x7fffffffffffffff)
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

	//定时器超时通知接口
	class CTimerNotify
	{
	public:
		virtual void OnTimerExpired(unsigned long timerId, const std::string & attr) = 0;
	};

	// 定时器
	class FSM_EXPORT TimerServer{
	private:
		//定时器对象。
		class  Timer{
		public:
			//生成一个定时器对象，时间间隔，定时器id，
			Timer( unsigned long timerId, unsigned long interval, const std::string & attr):
			  m_nTimerId(timerId),m_interval(interval),m_attr(attr)
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
			unsigned long getTimerId(){return m_nTimerId;};
			const std::string & getAttr(){ return m_attr;};
		private:
			const unsigned long m_nTimerId;
			const std::string m_attr;
			const unsigned long m_interval;
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
	private:
		//定时器队列
		typedef std::priority_queue<Timer *,std::vector<Timer *>, TimerComp> TIMER_QUEUE;
		TIMER_QUEUE m_timer; 
		struct thread_data td;
		helper::CLock m_timerLock;
		helper::CSemaphore m_semaphore;
		CTimerNotify& m_Observer;
	public:
		TimerServer(CTimerNotify& observer): m_Observer(observer){
			StartTimerThread();
		}

		virtual ~TimerServer(){
#ifdef WIN32
			TerminateThread(td.thread_hnd,0);
#else
			pthread_cancel(td.thread_id);
			pthread_join(td.thread_id, NULL);
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

		unsigned long GenerateTimerID()
		{
			static unsigned long index = 0;
			index++;
			if (index == 0 || index == 0xFFFFFFFF)
				index = 1;
			return index;
		}

#ifdef WIN32
		static unsigned int __stdcall TimerThreadProc( void *pParam ){
#else
		static void *  TimerThreadProc( void *pParam ){
#endif
			TimerServer * This = static_cast<TimerServer *>(pParam);
			time_t millisec = INFINITE;
#ifndef WIN32
			pthread_setcanceltype(PTHREAD_CANCEL_ENABLE,NULL);
			pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
#endif

			while(1)
			{
				bool wResult = This->m_semaphore.Wait(millisec);

				if (!wResult)
				{
					This->m_timerLock.Lock();
					while(!This->m_timer.empty()){
						Timer * timer = This->m_timer.top();

						millisec = This->m_timer.top()->getInterval();
						//LOG4CPLUS_DEBUG(log,"timer event . interval=" << millisec );
						if (millisec > 0){
							break;
						}

						This->m_Observer.OnTimerExpired(timer->getTimerId(), timer->getAttr());
						
						This->m_timer.pop();
						delete timer;
					}
					This->m_timerLock.Unlock();
				}
				else{
			
					This->m_timerLock.Lock();
					if (!This->m_timer.empty())
					{
						millisec = This->m_timer.top()->getInterval();
					}else{
						millisec = INFINITE;
					}
					This->m_timerLock.Unlock();
				}

			}
		return NULL;
		}

	public:
		unsigned long SetTimer(unsigned long delay, const std::string & attr){

			unsigned long timerId = GenerateTimerID();
			Timer * _timer = new Timer(timerId, delay,attr);
			this->m_timerLock.Lock();
			m_timer.push(_timer);
			this->m_timerLock.Unlock();
			m_semaphore.Post();
			return timerId;
		}

		void RemoveTimer(unsigned long timerID){

			helper::AutoLock auLock(&m_timerLock);
			TIMER_QUEUE temp;
			m_timer.swap(temp);
			while(!temp.empty()){
				Timer * timer = temp.top();
				temp.pop();
				if (timer->getTimerId() != timerID){
					m_timer.push(timer);
				}
			}
			m_semaphore.Post();
		}

	};
}//end namespace helper
#endif//end timer header