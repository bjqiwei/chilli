#pragma once
#ifndef _FSM_MODEL_FUNCTION_HEADER_
#define _FSM_MODEL_FUNCTION_HEADER_
#include "Action.h"
#include <log4cplus/logger.h>
#include <string>
#include <libxml/tree.h>

namespace fsm{
namespace model{

class Function :public Action
{
public:
	Function(xmlNodePtr node ,const std::string & session, const std::string & filename);
	virtual ~Function(void);
	virtual void execute(fsm::Context * ctx);
private:
	xmlNodePtr node;
	std::string m_strContent;
	std::string m_fileName;
	std::string m_strSession;
	std::string m_strFileName;
	log4cplus::Logger log;
};
}// end namespace model
}// end namespace fsm
#endif // end head file
