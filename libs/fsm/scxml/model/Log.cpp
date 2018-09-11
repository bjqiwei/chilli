#include "Log.h"
#include <log4cplus/loggingmacros.h>

namespace fsm{
namespace model{
	Log::Log(const std::string &filename, uint32_t lineno)
		:Action(filename,lineno)
	{
	}
	void Log::execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId)const
	{

		if (ctx && m_Type.compare("script") == 0) { 
			Json::Value jsonval = ctx->eval(m_strExpr, m_strFileName, m_lineNo/*,m_node*/);
			if (jsonval.isString() || jsonval.isBool() || jsonval.isNull()){
				const_cast<Log*>(this)->m_strExpr = jsonval.asString();
			}
			else if (jsonval.isInt()){
				const_cast<Log*>(this)->m_strExpr = std::to_string(jsonval.asInt());
			}
			else if (jsonval.isUInt()){
				const_cast<Log*>(this)->m_strExpr = std::to_string(jsonval.asUInt());
			}
			else if (jsonval.isDouble()){
				const_cast<Log*>(this)->m_strExpr = std::to_string(jsonval.asDouble());
			}
			else if (jsonval.isObject())
			{
				const_cast<Log*>(this)->m_strExpr = jsonval.toStyledString();
			}
		}

		if (m_strLevel.compare("trace") == 0){
			LOG4CPLUS_TRACE(log, "." + sessionId,  m_strFileName << ":" << m_lineNo << "," << m_strExpr);
		}
		else if (m_strLevel.compare("debug") == 0){
			LOG4CPLUS_DEBUG(log, "." + sessionId, m_strFileName << ":" << m_lineNo << "," << m_strExpr);
		}
		else if (m_strLevel.compare("info") == 0){
			LOG4CPLUS_INFO(log, "." + sessionId, m_strFileName << ":" << m_lineNo << "," << m_strExpr);
		}
		else if (m_strLevel.compare("warn") == 0){
			LOG4CPLUS_WARN(log, "." + sessionId, m_strFileName << ":" << m_lineNo << "," << m_strExpr);
		}
		else if (m_strLevel.compare("error") == 0){
			LOG4CPLUS_ERROR(log, "." + sessionId, m_strFileName << ":" << m_lineNo << "," << m_strExpr);
		}
		else if (m_strLevel.compare("fatal") == 0){
			LOG4CPLUS_FATAL(log, "." + sessionId, m_strFileName << ":" << m_lineNo << "," << m_strExpr);
		}
		else{

			LOG4CPLUS_INFO(log, "." + sessionId, m_strFileName << ":" << m_lineNo << "," << m_strExpr);
		}
	}
	const std::string & Log::getExpr() const
	{
		return m_strExpr;
	}
	void Log::setExpr(const std::string & expr)
	{
		this->m_strExpr = expr;
	}
	const std::string & Log::getLevel() const
	{
		return m_strLevel;
	}

	void Log::setLevel(const std::string & level)
	{
		this->m_strLevel = level;
	}


	const std::string & Log::getType()const
	{
		return this->m_Type;
	}

	void Log::setType(const std::string & type)
	{
		this->m_Type = type;
	}

}
}
