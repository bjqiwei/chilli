#pragma once
#ifndef _FSM_MODEL_SCRIPT_HEADER_
#define  _FSM_MODEL_SCRIPT_HEADER_

#include <string>
#include "Action.h"


namespace fsm
{
namespace model
{
	/// </summary>
	class  Script :public Action
	{
	private:
		//TLogFile * log;
		std::string m_content;
		std::string m_fileName;

	public:
		Script(xmlNodePtr xNode,const std::string &session,const std::string & filename);
		/*std::string &getContent();*/
		virtual  void execute(Context * ctx);
	};


}
}

#endif //end scxml.model.script header