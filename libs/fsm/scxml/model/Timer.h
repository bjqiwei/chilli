#pragma once
#ifndef _SCXML_MODEL_TIMER_HEADER_
#define  _SCXML_MODEL_TIMER_HEADER_

#include <string>
#include "Action.h"



namespace   fsm{
namespace model{

	class  Timer:public Action{
	public:
		Timer(xmlNodePtr node,const std::string &session,const std::string & filename);
		virtual ~Timer();

		const std::string& getId() const;
		const std::string& getIdExpr() const;
		unsigned int getInterval();

		virtual  void execute(fsm::Context * ctx);

	private:
		std::string id;
		std::string idexpr;
		std::string interval;
	};
}
}
#endif // end timer header