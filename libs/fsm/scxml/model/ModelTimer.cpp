#include "ModelTimer.h"
#include "../SCXMLHelper.h"
#include "../../xmlHelper.h"

namespace fsm{
namespace model{

	Timer::Timer(xmlNodePtr xNode,const std::string &session,const std::string & filename):node(xNode),
		m_strSession(session),m_strFilename(filename)
	{
		log = log4cplus::Logger::getInstance("StateMachine.model.Timer");
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

	void Timer::execute(fsm::Context * ctx)
	{

		if (SCXMLHelper::isStringEmpty(id)){
			id = ctx->eval(idexpr,m_strFilename,node->line);
		}
	}
}
}