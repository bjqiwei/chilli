#pragma once
#ifndef _FSM_MODEL_FUNCTION_HEADER_
#define _FSM_MODEL_FUNCTION_HEADER_
#include "Action.h"
#include <string>


namespace fsm{
namespace model{

class Function :public Action
{
public:
	Function(xmlNodePtr node ,const std::string & session, const std::string & filename);
	virtual ~Function(void);
	virtual void execute(fsm::Context * ctx);
	virtual bool isEnabledCondition(fsm::Context * ctx);
private:
	std::string m_strContent;
	std::string m_fileName;

};
}// end namespace model
}// end namespace fsm
#endif // end head file
