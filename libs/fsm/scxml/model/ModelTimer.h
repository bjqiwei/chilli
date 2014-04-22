#pragma once
#ifndef _SCXML_MODEL_TIMER_HEADER_
#define  _SCXML_MODEL_TIMER_HEADER_

#include <string>
#include <log4cplus/logger.h>
#include "Action.h"



namespace   fsm{
namespace model{

	class  Timer:public Action{
	public:
		Timer(xmlNodePtr node,const std::string &session,const std::string & filename);
		virtual ~Timer();

		const std::string& getId();
		const std::string& getIdExpr();
		unsigned int getInterval();

		virtual  void execute(fsm::Context * ctx);
	private:
		log4cplus::Logger log;
		xmlNodePtr node;
		std::string id;
		std::string idexpr;
		std::string interval;
		std::string m_strSession;
		std::string m_strFilename;
	};
}
}
#endif // end timer header