#pragma once

#include <string>
#include "Action.h"

namespace fsm
{
namespace model
{
	class Transition :public Action
	{

	private:
		std::string m_strTarget;
	public:
		Transition(const std::string &filename, uint32_t lineno);

		const std::string &getTarget()const;
		void setTarget(const std::string & target);
		virtual  void execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId) const override;
	};
}
}