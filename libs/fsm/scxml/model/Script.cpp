#include "Script.h"
#include "../../common/xmlHelper.h"
#include <log4cplus/loggingmacros.h>

namespace fsm
{
namespace model
{


	Script::Script(xmlNodePtr xNode,const std::string &session,const std::string & filename):Action(xNode, session ,filename)
	{
		log = log4cplus::Logger::getInstance("fsm.model.Script");
		log.setAppendName("." + m_strSession);
		log.setAppendName("." + m_strSession);
		this->m_content =  helper::xml::XStr(xmlNodeGetContent(m_node)).strForm();
		this->m_fileName = helper::xml::XStr(xmlGetProp(m_node,BAD_CAST"src")).strForm();
	}

	//std::string &Script::getContent()
	//{
	//	return content;
	//}
	void Script::execute(fsm::Context * ctx)
	{
		if (ctx == NULL) return ;

		if (!m_fileName.empty()){
			LOG4CPLUS_TRACE(log, ",script file is:" << m_fileName);
			ctx->ExecuteFile(m_fileName);
		}
		else if (!m_content.empty()){
			LOG4CPLUS_TRACE(log, ",execute script is:" << m_content);
			ctx->eval(m_content,m_strFileName,m_node->line/*,m_node*/);
		}
	}
}
}

