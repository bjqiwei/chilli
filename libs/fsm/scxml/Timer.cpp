#include "Timer.h"
#include "TriggerEvent.h"
#include "../xmlHelper.h"
#include <log4cplus/loggingmacros.h>


namespace fsm{
	Timer::Timer(int interval,std::string ext,std::string &strTimerId):
		m_ext(ext),m_strTimerId(strTimerId),m_interval(interval)
	{
		Start();
		log = log4cplus::Logger::getInstance("fsm.timer");
		LOG4CPLUS_TRACE(log,"construct a timer object.");
	}

	Timer::~Timer(){
		LOG4CPLUS_TRACE(log,"deconstruct a timer object.");
	}
	void Timer::Start()
	{
		valid = true;
		ftime(&m_startTime);
	}
	std::string Timer::Step()
	{
		if (!valid){
			return "";
		}
		struct timeb currTime;
		ftime(&currTime);

		//LOG4CPLUS_TRACE(log,"after the " << (currTime.time-m_startTime.time)*1000 + currTime.millitm-m_startTime.millitm << " millisec from start time.");
		if (((currTime.time-m_startTime.time)*1000 + currTime.millitm-m_startTime.millitm) >= m_interval)
		{
			valid = false;
			xmlHelper::CXmlDocmentHelper xmlHelper;
			xmlHelper.setRootNode("event");
			xmlHelper.newRootProp("id",m_strTimerId);
			xmlHelper.newRootProp("from",m_ext);
			xmlHelper.newRootProp("dest",m_ext);
			xmlHelper.newRootProp("event","timer");
			
			xmlHelper.addChild("data",m_strTimerId);
			return xmlHelper.getContent();
		}
		return "";
	}

	Timer & Timer::operator=( Timer & other)
	{
		LOG4CPLUS_TRACE(log,"construct a timer from other object.");
		this->m_interval = other.m_interval;
		this->m_startTime = other.m_startTime;
		this->m_strTimerId = other.m_strTimerId;
		this->m_ext = other.m_ext;
		this->valid = other.valid;
		return *this;
	}
	
}