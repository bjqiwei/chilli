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
		OnEntry(xmlNodePtr xNode,const std::string &session,const std::string & filename)
			:Action(xNode, session, filename){};
		~OnEntry(){};

		virtual void execute(fsm::Context * ctx); 
		virtual bool isEnabledCondition(fsm::Context * ctx);
	private: 
	};
}
}
#endif // end head file