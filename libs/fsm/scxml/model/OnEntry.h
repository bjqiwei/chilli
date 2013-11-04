#pragma once
#ifndef _FSM_MODEL_ONENTRY_HEADER_
#define _FSM_MODEL_ONENTRY_HEADER_

#include <libxml/tree.h>
#include "Action.h"

namespace fsm
{
namespace model
{
	
	class OnEntry :public Action
	{
		
	public:
		OnEntry(xmlNodePtr xNode):_node(xNode){};
		~OnEntry(){};

		virtual void execute(fsm::Evaluator * evl,fsm::Context * ctx); 
	private: 
		xmlNodePtr _node;
	};
}
}
#endif // end head file