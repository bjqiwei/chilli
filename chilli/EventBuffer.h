#pragma once
#ifndef _EVENTBUFFER_HEADER_
#define _EVENTBUFFER_HEADER_
#include <deque>
#include <Windows.h>
#include <log4cplus/logger.h>

namespace chilli{

class EventBuffer
{
public:
	EventBuffer(void);
	virtual ~EventBuffer(void);

	void addData(std::string strData);
	std::string  getData();
	unsigned int size();
	HANDLE semaphore;
private:
	std::deque<std::string> m_strBuffer; 
	CRITICAL_SECTION csection;
	log4cplus::Logger log;
	static const unsigned int MAXBUFFER = 1024*16;
};
}
#endif
