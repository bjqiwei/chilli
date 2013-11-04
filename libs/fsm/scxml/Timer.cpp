#include "Timer.h"
#include "TriggerEvent.h"
#include <xmlHelper.h>


namespace fsm{
	Timer::Timer(int interval,std::string ext,std::string &strTimerId):
		m_ext(ext),m_interval(interval),m_strTimerId(strTimerId)
	{
		Start();
	}

	Timer::~Timer(){

	}
	void Timer::Start()
	{
		valid = true;
		m_startTime = clock();
	}
	std::string Timer::Step()
	{
		if (!valid){
			return "";
		}
		clock_t currTime;
		currTime = clock();

		if (currTime-m_startTime >= m_interval)
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
		this->m_interval = other.m_interval;
		this->m_startTime = other.m_startTime;
		this->m_strTimerId = other.m_strTimerId;
		this->m_ext = other.m_ext;
		this->valid = other.valid;
		return *this;
	}
	
}