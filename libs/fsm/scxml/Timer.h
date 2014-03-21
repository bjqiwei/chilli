#pragma once
#ifndef _SCXML_TIMER_HEADER_
#define _SCXML_TIMER_HEADER_
#include <string>
#include <ctime>
#include <log4cplus/logger.h>
#include <sys/timeb.h>
#include "config.h"


namespace   fsm{

	//定时器对象，在状态机中实现定时器的功能。
	class FSM_EXPORT Timer{
	public:
		//生成一个定时器对象，时间间隔，定时器扩展参数，定时器id，
		Timer( int interval,const std::string &ext,const std::string &strTimerId);
		virtual ~Timer();
		//开始计时
		void Start();
		//执行一次，计算定时器是否到时。
		std::string execute();
		unsigned long long getInterval() const{
			struct timeb currTime;
			ftime(&currTime);
			long long i = m_interval - ((currTime.time-m_startTime.time)*1000 + currTime.millitm-m_startTime.millitm);
			return i > 0?i:0;
		};


		//重载=
		Timer & operator=( Timer & other);
	

	private:
		std::string m_ext;
		std::string m_strTimerId;
		int m_interval;
		struct timeb m_startTime;
		log4cplus::Logger log;
	};
	class TimerComp{
	public:
		bool operator() (const Timer * const A, const Timer * const B)
		{
			return (A->getInterval()  > B->getInterval());
		}

	};
}
#endif // end timer header