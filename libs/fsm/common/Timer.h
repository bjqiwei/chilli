#pragma once
#include <queue>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <map>
#include "TimerInterface.h"
#include <iostream>

#ifndef INFINITE
#define  INFINITE  (0xFFFFFFFF)
#endif

//thread data Including thread handle and thread id

namespace helper{

	// 定时器
	class TimerServer{
	private:
		//定时器对象。
		class  Timer{
		public:
			//生成一个定时器对象，时间间隔，定时器id，
			Timer(unsigned long timerId, unsigned long interval, const std::string & attr, OnTimerInterface * fun, void * userdata) :
				m_nTimerId(timerId), m_attr(attr), m_interval(interval), m_TimeOutFuc(fun), m_userdata(userdata)
			{
				m_startTime = std::chrono::steady_clock::now();
			}
			virtual ~Timer(){};

			int64_t getInterval() const {
				std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
				int64_t  i = m_interval - std::chrono::duration_cast<std::chrono::milliseconds>(now - m_startTime).count();
				//std::cout << m_nTimerId << ":" << (i > 0 ? i : 0) << std::endl;
				return i > 0 ? i : 0;
			}
			unsigned long getTimerId(){return m_nTimerId;};
			const std::string & getAttr(){ return m_attr;};
			void * getUserData() { return m_userdata; };
			OnTimerInterface * getFunction() { return m_TimeOutFuc; };
		private:
			const uint64_t m_nTimerId;
			const std::string m_attr;
			const int64_t m_interval;
			std::chrono::steady_clock::time_point m_startTime;
			OnTimerInterface * m_TimeOutFuc = nullptr;
			void * m_userdata;
			Timer & operator=( const Timer & ) = delete;
		};
		class TimerComp{
		public:
			bool operator() (const Timer * const A, const Timer * const B)
			{
				return (A->getInterval() > B->getInterval());
			}

		};
	private:
		//定时器队列
		typedef std::priority_queue<Timer *,std::vector<Timer *>, TimerComp> TIMER_QUEUE;
		TIMER_QUEUE m_timer; 
		std::map<unsigned long, unsigned long> m_rvtimer;

		std::mutex m_mtx;
		std::atomic_bool m_Running;
		std::condition_variable m_cv;
		std::thread m_thread;
	public:
		TimerServer():m_Running(false){
			
		}

		void Start()
		{
			m_Running = true;
			this->m_thread = std::thread(&TimerServer::run, this);
		}

		void Stop() {
			m_Running = false;
			if (m_thread.joinable()) {
				m_cv.notify_one();
				m_thread.join();
			}
		}
		virtual ~TimerServer(){
			Stop();
		}
	private:

		unsigned long GenerateTimerID()
		{
			static unsigned long index = 0;
			index++;
			if (index == 0 || index == 0xFFFFFFFF)
				index = 1;
			return index;
		}

		void run(){
			time_t millisec = INFINITE;

			while(m_Running)
			{
				std::unique_lock<std::mutex> lck(m_mtx);

				std::cv_status stauts = this->m_cv.wait_for(lck, std::chrono::milliseconds(millisec));

				if (stauts == std::cv_status::timeout) {
					while (!this->m_timer.empty()) {
						Timer * timer = this->m_timer.top();

						millisec = timer->getInterval();
						if (millisec > 0) {
							break; //最近的定时器到期时间
						}
						else
							millisec = INFINITE; //假设已经不存在定制器，永远等待。

						this->m_timer.pop();
						if (m_rvtimer.erase(timer->getTimerId()) == 0){
							lck.unlock();
							if (timer->getFunction() != nullptr)
								timer->getFunction()->OnTimer(timer->getTimerId(), timer->getAttr(), timer->getUserData());
							lck.lock();
						}
						delete timer;

					}
				}
				else {
					if (!this->m_timer.empty()){
						millisec = this->m_timer.top()->getInterval();
					}
					else {
						millisec = INFINITE;
					}
				}
			}
		}

	public:
		unsigned long SetTimer(unsigned long delay, const std::string & attr, OnTimerInterface * func, void * userdata){

			unsigned long timerId = GenerateTimerID();
			Timer * _timer = new Timer(timerId, delay, attr, func, userdata);
			std::unique_lock<std::mutex> lck(m_mtx);
			m_timer.push(_timer);
			m_cv.notify_one();
			return timerId;
		}

		void RemoveTimer(unsigned long timerID){

			std::unique_lock<std::mutex> lck(m_mtx);
			m_rvtimer.insert(std::make_pair(timerID, timerID));
		}
	};

}//end namespace helper