#include "Timer.h"
#include "../../common/xmlHelper.h"

namespace fsm{
namespace model{

	Timer::Timer(xmlNodePtr xNode,const std::string &session,const std::string & filename)
		:Action(xNode, session, filename)
	{
		log = log4cplus::Logger::getInstance("fsm.model.Timer");
		log.setAppendName("." + m_strSession);
		this->id = helper::xml::getXmlNodeAttributesValue(m_node,"id");
		this->idexpr = helper::xml::getXmlNodeAttributesValue(m_node,"idexpr");
		this->interval = helper::xml::getXmlNodeAttributesValue(m_node,"interval");
		this->intervalexpr = helper::xml::getXmlNodeAttributesValue(m_node, "intervalexpr");
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
		if (!interval.empty()){
			try {
				return std::stoul(interval);
			}
			catch (...)
			{
				return 0;
			}
		}
		if (jsonInterval.isInt()){
			return jsonInterval.asInt();
		}
		else if (jsonInterval.isUInt()){
			return jsonInterval.asUInt();
		}
		else if (jsonInterval.isDouble())
		{
			return jsonInterval.asDouble();
		}
		return 0;
	}

	const std::string& Timer::getIntervalExpr()const
	{
		return intervalexpr;
	}

	void Timer::execute(fsm::Context * ctx)
	{
		if (ctx && id.empty()){
			Json::Value jsonid = ctx->eval(idexpr,m_strFileName,m_node->line);
			if (jsonid.isString() || jsonid.isBool() || jsonid.isNull()){
				id = jsonid.asString();
			}
		}
		if (ctx && interval.empty()){
			jsonInterval = ctx->eval(intervalexpr, m_strFileName, m_node->line);
		}
	}

}
}