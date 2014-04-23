#pragma once
#ifndef _FSM_MODEL_LOG_HEADER_
#define  _FSM_MODEL_LOG_HEADER_

#include <string>
#include <libxml/tree.h>
#include "Action.h"
#include <log4cplus/logger.h>


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
			std::string m_Type;
			std::string m_strSession;
			std::string m_strFilename;
			log4cplus::Logger log;
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
