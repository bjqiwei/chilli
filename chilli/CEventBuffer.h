#pragma once
#ifndef _CEVENTBUFFER_HEADER_
#define _CEVENTBUFFER_HEADER_
#include <deque>
#include <stdexcept>
#include "lock.h"
#include "Csemaphore.h"

namespace helper{

template<class T>
class CEventBuffer
{
public:
	CEventBuffer(unsigned long maxBuffer = 1024*1024*1024):MAXBUFFER(maxBuffer){}
	virtual ~CEventBuffer(void){}

	bool addData(const T &data){
		helper::AutoLock auLock(&m_lock);
		if (m_dataBuffer.size() > MAXBUFFER){
			std::logic_error ex("CEventBuffer size Exceed max buffer.");
			throw  std::exception(ex);
		}
		this->m_dataBuffer.push_back(data);
		this->m_sem.Post();
		return true;
	}

	bool getData(T& data, unsigned long dwMilliseconeds = INFINITE)
	{
		bool result =false;
		if(this->m_sem.Wait(dwMilliseconeds)){
			helper::AutoLock auLock(&m_lock);
			if (m_dataBuffer.size() > 0)
			{
				data = m_dataBuffer.front();
				m_dataBuffer.pop_front();
				result = true;
			}
		}
		
		return result;
	}
	unsigned long size()
	{
		helper::AutoLock auLock(&m_lock);
		return m_dataBuffer.size();
	}
private:
	std::deque<T> m_dataBuffer; 
	helper::CLock m_lock;
	helper::CSemaphore m_sem;
	const unsigned long MAXBUFFER;
};// end CEventBuffer class
}//end namespace helper
#endif // end header file
