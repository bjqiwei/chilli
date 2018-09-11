#pragma once

#include <string>
#include "Action.h"



namespace   fsm{
namespace model{

	class  Sleep:public Action{
	public:
		Sleep(const std::string &filename, uint32_t lineno);
		virtual ~Sleep();
		uint32_t getInterval() const;
		void setInterval(const std::string & interval);
		virtual  void execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId) const override;

	private:
		std::string m_Interval;
	};
}
}