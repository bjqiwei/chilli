#pragma once
#ifndef _FSM_MODEL_SCRIPTMODEL_HEADER_
#define _FSM_MODEL_SCRIPTMODEL_HEADER_
#include "Action.h"
#include <string>


namespace fsm{
namespace model{


class Scriptmodel :
	public Action
{
public:
	Scriptmodel(xmlNodePtr node, const std::string & session, const std::string &filename);
	virtual ~Scriptmodel(void);
	virtual void execute(fsm::Context * ctx);
	virtual bool isEnabledCondition(fsm::Context * ctx);
private:
};
}// end namespace fsm
}// end namespace model
#endif //end head file
