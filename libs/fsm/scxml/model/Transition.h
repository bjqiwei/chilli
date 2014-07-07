#pragma once
#ifndef _FSM_MODEL_TRANSITION_HEADER_
#define _FSM_MODEL_TRANSITION_HEADER_

#include <string>
#include <vector>
#include <libxml/tree.h>
#include "Action.h"
#include <log4cplus/logger.h>

namespace fsm
{
namespace model
{
	class Transition :public Action
	{

	private:
		std::string m_strTarget;
	public:
		Transition(xmlNodePtr xNode,const std::string &session,const std::string &filename);

		const std::string &getTarget()const;
		virtual  void execute(fsm::Context * ctx);
	};
}
}
#endif //end transition header