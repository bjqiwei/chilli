#pragma once
#ifndef _FSM_MODEL_TRANSITION_HEADER_
#define _FSM_MODEL_TRANSITION_HEADER_

#include <string>
#include <vector>
#include <libxml/tree.h>
#include "Action.h"

namespace fsm
{
namespace model
{
	class Transition :public Action
	{

	private:
		xmlNodePtr node;

		std::string m_strCond;
		std::string m_strTarget;
		bool m_bCond;
	public:
		Transition(xmlNodePtr xNode);

		std::string &getCond();
		std::string &getTarget();
		bool isEnabledCondition()const;
		virtual  void execute(fsm::Evaluator * evl,fsm::Context * ctx);
	};
}
}
#endif //end transition header