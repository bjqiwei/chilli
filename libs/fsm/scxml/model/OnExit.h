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
		OnExit(xmlNodePtr xNode,const std::string &session,const std::string & filename):node(xNode),
		m_strSession(session),m_strFilename(filename){};
		~OnExit(){};
		virtual void execute(fsm::Context * ctx);
	private: 
		xmlNodePtr node ;
		std::string m_strSession;
		std::string m_strFilename;
	};


}
}
#endif // end head file
