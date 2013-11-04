#pragma once
#ifndef _FSM_MODEL_SCRIPT_HEADER_
#define  _FSM_MODEL_SCRIPT_HEADER_

#include <string>
#include <libxml/tree.h>
#include "Action.h"


namespace fsm
{
namespace model
{
	/// </summary>
	class  Script :public Action
	{
	private:
		//log4cplus::Logger log;
		xmlNodePtr node;
		std::string content;
	public:
		Script(xmlNodePtr xNode);
		/*std::string &getContent();*/
		virtual  void execute(Evaluator * evl,Context * ctx);
	};


}
}

#endif //end scxml.model.script header