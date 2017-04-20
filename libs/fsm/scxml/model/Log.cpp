#include "Log.h"
#include "../../common/xmlHelper.h"
#include <log4cplus/loggingmacros.h>

using namespace helper::xml;
namespace fsm{
namespace model{
	Log::Log(xmlNodePtr xNode,const std::string &sessionid,const std::string &filename)
		:Action(xNode, sessionid, filename)
	{
		log = log4cplus::Logger::getInstance("fsm.model.Log");
		m_strExpr =  XStr(xmlNodeGetContent(m_node)).strForm();
		m_Type = getXmlNodeAttributesValue(m_node,"type");
		m_strLevel = getXmlNodeAttributesValue(m_node,"level");
	}
	void Log::execute(Context * ctx)
	{

		if (ctx && m_Type.compare("script") == 0) { 
			Json::Value jsonval = ctx->eval(m_strExpr, m_strFileName, m_node->line/*,m_node*/);
			if (jsonval.isString() || jsonval.isBool() || jsonval.isNull()){
				m_strExpr = jsonval.asString();
			}
			else if (jsonval.isInt()){
				m_strExpr = std::to_string(jsonval.asInt());
			}
			else if (jsonval.isUInt()){
				m_strExpr = std::to_string(jsonval.asUInt());
			}
			else if (jsonval.isDouble()){
				m_strExpr = std::to_string(jsonval.asDouble());
			}
		}

		if (m_strLevel.compare("trace") == 0){
			LOG4CPLUS_TRACE(log, m_strSession << m_strFileName << ":" << m_node->line << "," << m_strExpr);
		}
		else if (m_strLevel.compare("debug") == 0){
			LOG4CPLUS_DEBUG(log, m_strSession << m_strFileName << ":" << m_node->line << "," << m_strExpr);
		}
		else if (m_strLevel.compare("info") == 0){
			LOG4CPLUS_INFO(log, m_strSession << m_strFileName << ":" << m_node->line << "," << m_strExpr);
		}
		else if (m_strLevel.compare("warn") == 0){
			LOG4CPLUS_WARN(log, m_strSession << m_strFileName << ":" << m_node->line << "," << m_strExpr);
		}
		else if (m_strLevel.compare("error") == 0){
			LOG4CPLUS_ERROR(log,m_strSession << m_strFileName << ":" << m_node->line << "," << m_strExpr);
		}
		else if (m_strLevel.compare("fatal") == 0){
			LOG4CPLUS_FATAL(log, m_strSession << m_strFileName << ":" << m_node->line << "," << m_strExpr);
		}
		else{

			LOG4CPLUS_INFO(log, m_strSession << m_strFileName << ":" << m_node->line << "," << m_strExpr);
		}
	}
	const std::string & Log::getExpr() const
	{
		return m_strExpr;
	}
	const std::string & Log::getLevel() const
	{
		return m_strLevel;
	}

}
}
