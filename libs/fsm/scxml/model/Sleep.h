#pragma once
#ifndef _SCXML_MODEL_SLEEP_HEADER_
#define  _SCXML_MODEL_SLEEP_HEADER_

#include <string>
#include "Action.h"



namespace   fsm{
namespace model{

	class  Sleep:public Action{
	public:
		Sleep(xmlNodePtr node,const std::string &session,const std::string & filename);
		virtual ~Sleep();
		unsigned int getInterval();
		virtual  void execute(fsm::Context * ctx);

	private:
		std::string interval;
	};
}
}
#endif // end sleep header