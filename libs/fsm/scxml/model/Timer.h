#pragma once
#ifndef _SCXML_MODEL_TIMER_HEADER_
#define  _SCXML_MODEL_TIMER_HEADER_

#include <string>
#include <xmlHelper.h>
#include <scxml/model/Action.h>
#include <log4cplus/logger.h>


namespace   fsm{
namespace model{

	class  Timer:public Action{
	public:
		Timer(xmlNodePtr node);
		virtual ~Timer();

		std::string& getId();
		std::string& getIdExpr();
		unsigned int getInterval();

		virtual  void execute(fsm::Evaluator * evl,fsm::Context * ctx);
	private:
		log4cplus::Logger log;
		xmlNodePtr node;
		std::string id;
		std::string idexpr;
		std::string interval;
	};
}
}
#endif // end timer header