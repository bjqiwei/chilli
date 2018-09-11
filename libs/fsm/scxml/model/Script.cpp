#include "Script.h"
#include <log4cplus/loggingmacros.h>

namespace fsm
{
namespace model
{


	Script::Script(const std::string & filename, uint32_t lineno):Action(filename, lineno)
	{
	}


	const std::string &Script::getContent()const
	{
		return m_content;
	}

	void Script::setContext(const std::string & context)
	{
		this->m_content = context;
	}

	void Script::setFileName(const std::string & fileName)
	{
		this->m_scriptFileName = fileName;
	}
	void Script::execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId)const
	{
		if (ctx == NULL) return ;

		if (!m_scriptFileName.empty()){
			LOG4CPLUS_TRACE(log, "." + m_strSession, ",script file is:" << m_scriptFileName);
			ctx->ExecuteFile(m_scriptFileName);
		}
		else if (!m_content.empty()){
			LOG4CPLUS_TRACE(log, "." + m_strSession, ",execute script is:" << m_content);
			ctx->eval(m_content,m_strFileName, m_lineNo/*,m_node*/);
		}
	}
}
}

