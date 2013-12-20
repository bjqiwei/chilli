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
		std::string m_strSession;
		std::string m_strFilename;
		fsm::Context * cx;
	public:
		Transition(xmlNodePtr xNode,const std::string &session,const std::string &filename);

		std::string &getCond();
		std::string &getTarget();
		bool isEnabledCondition();
		virtual  void execute(fsm::Context * ctx);
	};
}
}
#endif //end transition header