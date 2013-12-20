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
		Timer( int interval,std::string ext,std::string &strTimerId);
		virtual ~Timer();
		//开始计时
		void Start();
		//执行一次，计算定时器是否到时。
		std::string Step();

		//定时器是否可用
		bool valid;

		//重载=
		Timer & operator=( Timer & other);
	private:
		std::string m_ext;
		std::string m_strTimerId;
		int m_interval;
		struct timeb m_startTime;
		log4cplus::Logger log;
	};
}
#endif // end timer header