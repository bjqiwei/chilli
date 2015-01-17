//---------------------------------------------------------------------------

	//                                      lock.h

	//---------------------------------------------------------------------------
#ifndef _LOCK_HEADER_
#define _LOCK_HEADER_
#pragma once

#ifdef WIN32
#include <Windows.h>
#include <process.h>
#else  // POSIX - linux
#include <pthread.h>
#endif
namespace helper{
class CLock
{
public:
#ifdef WIN32
	CLock()        { InitializeCriticalSection(&m_CriticalSection);           }
	~CLock()       { DeleteCriticalSection(&m_CriticalSection);               }
	int Lock()     { EnterCriticalSection(&m_CriticalSection); return true;   }
	bool TryLock() { return TryEnterCriticalSection(&m_CriticalSection) == TRUE;}
	int Unlock()   { LeaveCriticalSection(&m_CriticalSection); return true;   }
#else// POSIX - linux
	CLock()        { pthread_mutex_init(&m_Mutex, NULL);}
	virtual ~CLock()       { pthread_mutex_destroy(&m_Mutex);   }
	int Lock()     { int nRetCode = pthread_mutex_lock(&m_Mutex);      return (nRetCode == 0); }
	bool TryLock() { return  pthread_mutex_trylock(&m_Mutex) == EBUSY;}
	int Unlock()   { int nRetCode = pthread_mutex_unlock(&m_Mutex);    return (nRetCode == 0); }
#endif
private:
#ifdef WIN32
	CRITICAL_SECTION m_CriticalSection;
#else
	pthread_mutex_t m_Mutex;
#endif
private:
	CLock(const CLock &);
	CLock& operator =(const CLock &);

};// end of lock class

class AutoLock
{
public:
	explicit AutoLock(CLock* lock):m_lock(lock)
	{
		m_lock->Lock();
	}
	virtual ~AutoLock()
	{
		m_lock->Unlock();
	}
private:
	CLock * m_lock;
	AutoLock(const AutoLock &);
	AutoLock & operator=(const AutoLock &);
};
}//end namespace helper
#endif // end header file
