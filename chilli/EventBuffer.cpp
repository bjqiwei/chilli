#include "StdAfx.h"
#include "EventBuffer.h"
#include <log4cplus/loggingmacros.h>


namespace chilli
{
EventBuffer::EventBuffer(void){
	log = log4cplus::Logger::getInstance("chilli.EventBuffer.");
	InitializeCriticalSection(&csection);
	semaphore = CreateSemaphore(NULL, 0, LONG_MAX, NULL);
	if (NULL == semaphore){
		LOG4CPLUS_ERROR(log,"Structure EventBuffer encountered an error,error=" << GetLastError());
	}
}

EventBuffer::~EventBuffer(void){
	DeleteCriticalSection(&csection);
	CloseHandle(semaphore);
}

void EventBuffer::addData(std::string strData)
{
	EnterCriticalSection(&csection);
	if (m_strBuffer.size() > MAXBUFFER)
	{
		LOG4CPLUS_WARN(log,"Event buffer size Exceed max buffer." );
		while(m_strBuffer.size() >= MAXBUFFER){
			LOG4CPLUS_ERROR(log,"erase one event=" << m_strBuffer.front());
			m_strBuffer.pop_front();
		}
	}
	this->m_strBuffer.push_back(strData);
	ReleaseSemaphore(semaphore, 1, NULL);
	LeaveCriticalSection(&csection);
	return ;
}
std::string EventBuffer::getData()
{
	EnterCriticalSection(&csection);
	std::string strResult;

	if (m_strBuffer.size() > 0)
	{
		strResult = m_strBuffer.front();
		m_strBuffer.pop_front();
	}
	LeaveCriticalSection(&csection);
	return strResult;
}
unsigned int EventBuffer::size()
{
	return m_strBuffer.size();
}
}