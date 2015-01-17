//---------------------------------------------------------------------------

//                                      semaphore.h

//---------------------------------------------------------------------------
#ifndef _CSEMAPHORE_HEADER_
#define _CSEMAPHORE_HEADER_
#pragma once

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

namespace helper{
	class CSemaphore
	{
	public:
		CSemaphore(){
#ifdef WIN32
			sem = CreateSemaphore(NULL, 0, LONG_MAX, NULL);
#else // POSIX - linux
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
		}

		~CSemaphore()
		{
#ifdef WIN32
			CloseHandle(sem);
#else // POSIX - linux
			pthread_mutex_destroy(&(sem->mutex));
			pthread_cond_destroy(&(sem->condition));
			delete sem;
#endif
		}
#ifndef INFINITE
#define  INFINITE  (0x7fffffffffffffff)
#endif
		bool Wait(time_t millisec = INFINITE){
#ifdef WIN32
			return (WAIT_OBJECT_0 == ::WaitForSingleObject(this->sem, millisec)); 
#else// POSIX - linux
			struct timespec tm;
			struct timeb tp;
			int rv;

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
			pthread_mutex_lock(&(this->sem->mutex));
			while (this->sem->semCount <= 0)
			{
				rv = pthread_cond_timedwait(&(this->sem->condition), &(this->sem->mutex), &tm);
				if (rv && (errno != EINTR) )
					break;
			}
			if(rv == 0)this->sem->semCount--;
			pthread_mutex_unlock(&(this->sem->mutex));
			return (0 == rv); 
#endif
		}
		void Post(unsigned long count = 1) { 
#ifdef WIN32
			ReleaseSemaphore(sem, count, NULL);
#else // POSIX - linux
			pthread_mutex_lock(&(sem->mutex));
			sem->semCount += count;
			pthread_cond_signal(&(sem->condition));
			pthread_mutex_unlock(&(sem->mutex));
#endif
		}
	private:
#ifdef WIN32
		HANDLE sem;
#else // POSIX - linux
		sem_private sem;
#endif
	private:
		CSemaphore(const CSemaphore &);
		CSemaphore& operator =(const CSemaphore &);

	};// end of CSemaphore class

}//end namespace helper
#endif // end header file
