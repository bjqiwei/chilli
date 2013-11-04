#pragma once
#ifndef _FSM_MODEL_EVENT_HEADER_
#define _FSM_MODEL_EVENT_HEADER_

#include <string>
#include <vector>
#include <xmlHelper.h>
#include <log4cplus/logger.h>
#include "Action.h"

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

		std::string &getCond();
		std::string &getEvent();
		
	public:
		Event(xmlNodePtr xNode);
		bool isEnabledEvent(const string& strEventName) const ;
		bool isEnabledCondition()const;
		virtual void execute(fsm::Evaluator * evl,fsm::Context * ctx);
	};
}
}
#endif //end event haed file