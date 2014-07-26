#pragma once
#ifndef _FSM_MODEL_RAISE_HEADER_
#define _FSM_MODEL_RAISE_HEADER_

#include <libxml/tree.h>
#include "Action.h"

namespace fsm
{
	namespace model
	{

		class Raise :public Action
		{
		public:
			Raise(xmlNodePtr xNode,const std::string &session,const std::string & filename);
			virtual ~Raise(void);

			virtual void execute(fsm::Context * ctx); 
			const std::string &getEvent()const;
		private:
			std::string m_strEvent;
		};
	
	}//end namespace model
}//end namespace fsm
#endif//end header file

