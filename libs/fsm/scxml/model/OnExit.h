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
		OnExit(xmlNodePtr xNode):node(xNode){};
		~OnExit(){};
		virtual void execute(fsm::Evaluator * evl,fsm::Context * ctx);
	private: 
		xmlNodePtr node ;
	};


}
}
#endif // end head file
