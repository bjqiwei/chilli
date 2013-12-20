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
		OnEntry(xmlNodePtr xNode,const std::string &session,const std::string & filename):_node(xNode),
		m_strSession(session),m_strFilename(filename){};
		~OnEntry(){};

		virtual void execute(fsm::Context * ctx); 
	private: 
		xmlNodePtr _node;
		std::string m_strSession;
		std::string m_strFilename;
	};
}
}
#endif // end head file