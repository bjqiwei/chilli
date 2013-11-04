#pragma once
#ifndef _FSM_MODEL_LOG_HEADER_
#define  _FSM_MODEL_LOG_HEADER_

#include <string>
#include <libxml/tree.h>
#include "Action.h"


namespace fsm
{
	namespace model
	{
		/// </summary>
		class  Log :public Action
		{
		private:
			xmlNodePtr node;
			std::string m_strExpr;
			std::string m_strLevel;
		public:
			Log(xmlNodePtr xNode);
			virtual ~Log(){};
			std::string & getExpr();
			std::string & getLevel();
			virtual  void execute(Evaluator * evl,Context * ctx);
		};


	}
}

#endif //end scxml.model.script header
