#pragma once
#ifndef _FSM_MODEL_FUNCTIONMODEL_HEADER_
#define _FSM_MODEL_FUNCTIONMODEL_HEADER_
#include "Action.h"
#include <string>


namespace fsm{
namespace model{


class Functionmodel :
	public Action
{
public:
	Functionmodel(xmlNodePtr node, const std::string & session, const std::string &filename);
	virtual ~Functionmodel(void);
	virtual void execute(fsm::Context * ctx);
	virtual bool isEnabledCondition(fsm::Context * ctx);
private:
};
}// end namespace fsm
}// end namespace model
#endif //end head file
