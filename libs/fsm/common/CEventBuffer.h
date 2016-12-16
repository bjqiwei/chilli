#pragma once
#ifndef _CEVENTBUFFER_HEADER_
#define _CEVENTBUFFER_HEADER_
#include <list>
#include <mutex>
#include <condition_variable>
#include <stdexcept>

#ifndef INFINITE
#define INFINITE -1
#endif

namespace helper{

template<class T>
class CEventBuffer
{
public:
	explicit CEventBuffer(unsigned long maxBuffer = 1024*1024*1024):MAXBUFFER(maxBuffer){
	}
	virtual ~CEventBuffer(void){}

	bool Put(const T &data){
		std::unique_lock<std::mutex> lck(m_mtx);
		if (m_dataBuffer.size() > MAXBUFFER){
			std::logic_error ex("CEventBuffer size Exceed max buffer.");
			throw  std::exception(ex);
		}
		this->m_dataBuffer.push_back(data);
		this->m_cv.notify_one();
		return true;
	}

	bool Get(T& data, long long dwMilliseconeds = INT32_MAX)
	{
		std::unique_lock<std::mutex> lck(m_mtx);
		
		bool result = this->m_cv.wait_for(lck, std::chrono::milliseconds(dwMilliseconeds), [&]()->bool{ return !this->m_dataBuffer.empty(); });
		
		if (result){
			data = m_dataBuffer.front();
			m_dataBuffer.pop_front();
		}
		
		return result;
	}
	unsigned long size()
	{
		std::unique_lock<std::mutex> lck(m_mtx);
		return m_dataBuffer.size();
	}
private:
	std::list<T> m_dataBuffer; 
	std::mutex m_mtx;
	std::condition_variable m_cv;
	const unsigned long MAXBUFFER;
};// end CEventBuffer class
}//end namespace helper
#endif // end header file
