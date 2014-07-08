#pragma once
#ifndef _FSM_MODEL_ONEXIT_HEADER_
#define _FSM_MODEL_ONEXIT_HEADER_
#include "Action.h"
#include <libxml/tree.h>


namespace fsm
{
namespace model
{

	class OnExit : public Action
	{

	public:
		OnExit(xmlNodePtr xNode,const std::string &session,const std::string & filename)
			:Action(xNode, session, filename){};
		~OnExit(){};
		virtual void execute(fsm::Context * ctx);
		virtual bool isEnabledCondition(fsm::Context * ctx);
	private: 

	};


}
}
#endif // end head file
