#include "Timer.h"
#include "../../common/xmlHelper.h"

namespace fsm{
namespace model{

	Timer::Timer(xmlNodePtr xNode,const std::string &session,const std::string & filename)
		:Action(xNode, session, filename)
	{
		log = log4cplus::Logger::getInstance("fsm.model.Timer");
		this->id = helper::xml::getXmlNodeAttributesValue(m_node,"id");
		this->idexpr = helper::xml::getXmlNodeAttributesValue(m_node,"idexpr");
		this->interval = helper::xml::getXmlNodeAttributesValue(m_node,"interval");
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
			Json::Value jsonid = ctx->eval(idexpr,m_strFileName,m_node->line);
			if (jsonid.isString() || jsonid.isBool() || jsonid.isNull()){
				id = jsonid.asString();
			}
		}
	}

}
}