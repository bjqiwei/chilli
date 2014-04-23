#pragma once
#ifndef _FSM_MODEL_SCRIPT_HEADER_
#define  _FSM_MODEL_SCRIPT_HEADER_

#include <string>
#include <libxml/tree.h>
#include "Action.h"
#include <log4cplus/logger.h>


namespace fsm
{
namespace model
{
	/// </summary>
	class  Script :public Action
	{
	private:
		//TLogFile * log;
		xmlNodePtr node;
		std::string content;
		std::string m_strSession;
		std::string m_strFilename;
		log4cplus::Logger log;
	public:
		Script(xmlNodePtr xNode,const std::string &session,const std::string & filename);
		/*std::string &getContent();*/
		virtual  void execute(Context * ctx);
	};


}
}

#endif //end scxml.model.script header