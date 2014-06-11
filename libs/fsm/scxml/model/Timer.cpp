#include "Timer.h"
#include "../../common/xmlHelper.h"

namespace fsm{
namespace model{

	Timer::Timer(xmlNodePtr xNode,const std::string &session,const std::string & filename):node(xNode),
		m_strSession(session),m_strFilename(filename)
	{
		log = log4cplus::Logger::getInstance("fsm.model.Timer");
		this->id = helper::xml::getXmlNodeAttributesValue(node,"id");
		this->idexpr = helper::xml::getXmlNodeAttributesValue(node,"idexpr");
		this->interval = helper::xml::getXmlNodeAttributesValue(node,"interval");
	}
	Timer::~Timer(){

	}
	const std::string& Timer::getId()const
	{
		return id;
	}

	const std::string& Timer::getIdExpr()const
	{
		return idexpr;
	}

	unsigned int Timer::getInterval()
	{
		return atoi(interval.c_str());
	}

	void Timer::execute(fsm::Context * ctx)
	{

		if (ctx && id.empty()){
			id = ctx->eval(idexpr,m_strFilename,node->line,node);
		}
	}
}
}