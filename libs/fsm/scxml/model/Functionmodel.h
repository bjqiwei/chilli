#pragma once
#ifndef _FSM_MODEL_FUNCTIONMODEL_HEADER_
#define _FSM_MODEL_FUNCTIONMODEL_HEADER_
#include "Action.h"
#include <log4cplus/logger.h>
#include <string>
#include <libxml/tree.h>

namespace fsm{
namespace model{


class Functionmodel :
	public Action
{
public:
	Functionmodel(xmlNodePtr node, const std::string & session, const std::string &filename);
	virtual ~Functionmodel(void);
	virtual void execute(fsm::Context * ctx);
private:
	xmlNodePtr node;
	log4cplus::Logger log;
	std::string m_strSession;
	std::string m_strFilename;
};
}// end namespace fsm
}// end namespace model
#endif //end head file
