//---------------------------------------------------------------------------

	//                                      lock.h

	//---------------------------------------------------------------------------
#ifndef _LOCK_HEADER_
#define _LOCK_HEADER_
#pragma once

#ifdef WIN32
#include <Windows.h>
#include <process.h>
namespace fsm{
class CLock
{
public:
	CLock()        { InitializeCriticalSection(&m_CriticalSection);           }
	~CLock()       { DeleteCriticalSection(&m_CriticalSection);               }
	int Lock()     { EnterCriticalSection(&m_CriticalSection); return true;   }
	int Unlock()   { LeaveCriticalSection(&m_CriticalSection); return true;   }

private:
	CRITICAL_SECTION m_CriticalSection;
private:
	CLock(const CLock &);
	void operator =(const CLock &);

};
}// end namespace fsm

#else   // POSIX - linux

#include <pthread.h>
namespace fsm{
class CLock
{
public:
	CLock()        { pthread_mutex_init(&m_Mutex, NULL);}
	~CLock()       { pthread_mutex_destroy(&m_Mutex);   }

	int Lock()     { int nRetCode = pthread_mutex_lock(&m_Mutex);      return (nRetCode == 0); }

	int Unlock()   { int nRetCode = pthread_mutex_unlock(&m_Mutex);    return (nRetCode == 0); }

private:
	pthread_mutex_t m_Mutex;
private:
	CLock(const CLock &);
	void operator =(const CLock &);
};
}//end namespace fsm
#endif //end class

#endif // end header define