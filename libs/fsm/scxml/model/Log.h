#pragma once
#ifndef _FSM_MODEL_LOG_HEADER_
#define  _FSM_MODEL_LOG_HEADER_

#include <string>
#include "Action.h"

namespace fsm
{
	namespace model
	{
		/// </summary>
		class  Log :public Action
		{
		private:
			std::string m_strExpr;
			std::string m_strLevel;
			std::string m_Type;

		public:
			Log(xmlNodePtr xNode,const std::string &sessionid,const std::string &filename);
			virtual ~Log(){};
			const std::string & getExpr() const;
			const std::string & getLevel() const;
			virtual  void execute(Context * ctx);
		};


	}
}

#endif //end scxml.model.script header
