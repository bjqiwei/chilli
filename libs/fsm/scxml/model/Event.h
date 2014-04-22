#pragma once
#ifndef _FSM_MODEL_EVENT_HEADER_
#define _FSM_MODEL_EVENT_HEADER_

#include "Action.h"
#include <log4cplus/logger.h>

namespace fsm
{
namespace model
{

	class Event:public Action
	{

	private:
		xmlNodePtr node;
		log4cplus::Logger log;
		std::string m_strCond;
		std::string m_strEvent;
		bool m_bCond;
		std::string m_strSession;
		std::string m_strFilename;
		fsm::Context * cx;

		const std::string &getCond();
		const std::string &getEvent();
		
	public:
		Event(xmlNodePtr xNode,const std::string &session,const std::string &filename);
		bool isEnabledEvent(const std::string& strEventName) const ;
		bool isEnabledCondition();
		virtual void execute(fsm::Context * ctx);
	};
}
}
#endif //end event haed file