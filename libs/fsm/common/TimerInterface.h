#pragma once
#include "../config.h"

namespace helper {

	//定时器超时通知接口

	class FSM_EXPORT OnTimerInterface
	{
	public:
		OnTimerInterface() {}

	public:

		/// <summary>
		/// Send this message to the target.
		/// </summary>

		virtual void OnTimer(unsigned long timerId, const std::string & attr, void * userdata) = 0;

	};
}