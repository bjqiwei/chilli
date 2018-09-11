#include "Sleep.h"
#include <thread>
#include <log4cplus/loggingmacros.h>

namespace fsm{
namespace model{

	Sleep::Sleep(const std::string &filename, uint32_t lineno)
		:Action(filename, lineno)
	{

	}
	Sleep::~Sleep(){

	}

	uint32_t Sleep::getInterval()const
	{
		if (!m_Interval.empty()) {
			try {
				return std::stoul(m_Interval);
			}
			catch (...)
			{
				return 0;
			}
		}
		return 0;
	}

	void Sleep::setInterval(const std::string & interval)
	{
		this->m_Interval = interval;
	}

	void Sleep::execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId)const
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(getInterval()));
	}

}
}