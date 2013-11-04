#include "Timer.h"
#include "scxml/SCXMLHelper.h"
#include <xmlHelper.h>

namespace fsm{
namespace model{

	Timer::Timer(xmlNodePtr xNode):node(xNode)
	{
		log = log4cplus::Logger::getInstance("fsm.model.Timer");
		this->id = fsm::xmlHelper::getXmlNodeAttributesValue(node,"id");
		this->idexpr = fsm::xmlHelper::getXmlNodeAttributesValue(node,"idexpr");
		this->interval = fsm::xmlHelper::getXmlNodeAttributesValue(node,"interval");
	}
	Timer::~Timer(){

	}
	std::string& Timer::getId()
	{
		return id;
	}

	std::string& Timer::getIdExpr()
	{
		return idexpr;
	}

	unsigned int Timer::getInterval()
	{
		return atoi(interval.c_str());
	}

	void Timer::execute(fsm::Evaluator * evl,fsm::Context * ctx)
	{

		if (SCXMLHelper::isStringEmpty(id)){
			id = evl->eval(ctx,idexpr,node->line);
		}
	}
}
}