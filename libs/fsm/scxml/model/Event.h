#pragma once
#ifndef _FSM_MODEL_EVENT_HEADER_
#define _FSM_MODEL_EVENT_HEADER_

#include "Action.h"

namespace fsm
{
namespace model
{

	class Event:public Action
	{

	private:
		std::string m_strEvent;
		const std::string &getEvent();
		
	public:
		Event(xmlNodePtr xNode,const std::string &session,const std::string &filename);
		bool isEnabledEvent(const std::string& strEventName) const ;
		virtual void execute(fsm::Context * ctx);
	};
}
}
#endif //end event haed file