#include "Timer.h"

namespace fsm{
namespace model{

	Timer::Timer(const std::string &filename, uint32_t lineno)
		:Action(filename,lineno)
	{
	}
	Timer::~Timer(){

	}
	const std::string& Timer::getId()const
	{
		return id;
	}

	void Timer::setId(const std::string & id)
	{
		this->id = id;
	}

	const std::string& Timer::getIdExpr()const
	{
		return idexpr;
	}

	void Timer::setIdExpr(const std::string idexpr)
	{
		this->idexpr = idexpr;
	}

	uint64_t Timer::getInterval() const
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

	void Timer::setInterval(const std::string & interval)
	{
		this->interval = interval;
	}

	const std::string& Timer::getIntervalExpr()const
	{
		return intervalexpr;
	}

	void Timer::setIntervalExpr(const std::string & intervalexpr)
	{
		this->intervalexpr = intervalexpr;
	}

	void Timer::execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId)const
	{
		if (ctx && id.empty() && !idexpr.empty()){
			Json::Value jsonid = ctx->eval(idexpr, m_strFileName, m_lineNo);
			if (jsonid.isString() || jsonid.isBool() || jsonid.isNull() || jsonid.isNumeric()){
				const_cast<Timer *>(this)->id = jsonid.asString();
			}
		}
		if (ctx && interval.empty() && !intervalexpr.empty()){
			const_cast<Timer*>(this)->jsonInterval = ctx->eval(intervalexpr, m_strFileName, m_lineNo);
		}
	}

}
}