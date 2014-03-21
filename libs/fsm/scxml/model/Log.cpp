#include "Log.h"
#include "../../xmlHelper.h"
#include <log4cplus/loggingmacros.h>

using namespace fsm::xmlHelper;
namespace fsm{
namespace model{
	Log::Log(xmlNodePtr xNode,const std::string &sessionid,const std::string &filename):node(xNode),m_strSession(sessionid),
	m_strFilename(filename)
	{
		m_strExpr =  XStr(xmlNodeGetContent(node)).strForm();
		m_Type = getXmlNodeAttributesValue(node,"type");
		m_strLevel = getXmlNodeAttributesValue(node,"level");
		log = log4cplus::Logger::getInstance("StateMachine.Log");
	}
	void Log::execute(Context * ctx)
	{
		if(ctx && m_Type.compare("script") == 0)
			m_strExpr = ctx->eval(m_strExpr,m_strFilename,node->line,node);

		if (m_strLevel.compare("trace") == 0){
			LOG4CPLUS_TRACE(log, m_strSession << "," << m_strExpr);
		}
		else if (m_strLevel.compare("debug") == 0){
			LOG4CPLUS_DEBUG(log, m_strSession << "," << m_strExpr);
		}
		else if (m_strLevel.compare("info") == 0){
			LOG4CPLUS_INFO(log, m_strSession << "," << m_strExpr);
		}
		else if (m_strLevel.compare("warn") == 0){
			LOG4CPLUS_WARN(log, m_strSession << "," << m_strExpr);
		}
		else if (m_strLevel.compare("error") == 0){
			LOG4CPLUS_ERROR(log,m_strSession << "," << m_strExpr);
		}
		else if (m_strLevel.compare("fatal") == 0){
			LOG4CPLUS_FATAL(log, m_strSession << "," << m_strExpr);
		}
		else{

			LOG4CPLUS_INFO(log, m_strSession << "," << m_strExpr);
		}
	}
	std::string & Log::getExpr()
	{
		return m_strExpr;
	}
	std::string & Log::getLevel()
	{
		return m_strLevel;
	}
}
}
