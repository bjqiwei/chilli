#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <stdexcept>

#ifndef INFINITE
#define INFINITE 0xFFFFFFFF
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
			std::runtime_error ex("CEventBuffer size Exceed max buffer.");
			throw  std::exception(ex);
		}
		this->m_dataBuffer.push(data);
		this->m_cv.notify_one();
		return true;
	}

	bool Get(T& data, uint64_t dwMilliseconeds = INT32_MAX)
	{
		std::unique_lock<std::mutex> lck(m_mtx);
		
		bool result = this->m_cv.wait_for(lck, std::chrono::milliseconds(dwMilliseconeds), [&]()->bool{ return !this->m_dataBuffer.empty(); });
		
		if (result){
			data = m_dataBuffer.front();
			m_dataBuffer.pop();
		}
		
		return result;
	}

	bool Get(std::queue<T> & data, uint64_t dwMilliseconeds = INT32_MAX)
	{
		std::unique_lock<std::mutex> lck(m_mtx);

		bool result = this->m_cv.wait_for(lck, std::chrono::milliseconds(dwMilliseconeds), [&]()->bool { return !this->m_dataBuffer.empty(); });

		if (result) {
			while (!m_dataBuffer.empty()) {
				data.push(m_dataBuffer.front());
				m_dataBuffer.pop();
			}
		}

		return result;
	}

	size_t size()
	{
		std::unique_lock<std::mutex> lck(m_mtx);
		return m_dataBuffer.size();
	}
private:
	std::queue<T> m_dataBuffer; 
	std::mutex m_mtx;
	std::condition_variable m_cv;
	const unsigned long MAXBUFFER;
};// end CEventBuffer class
}//end namespace helper
