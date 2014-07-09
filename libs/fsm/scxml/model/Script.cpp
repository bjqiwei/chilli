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
		this->content =  helper::xml::XStr(xmlNodeGetContent(node)).strForm();
		this->m_fileName = helper::xml::XStr(xmlGetProp(node,BAD_CAST"src")).strForm();
	}

	//std::string &Script::getContent()
	//{
	//	return content;
	//}
	void Script::execute(fsm::Context * ctx)
	{
		if (ctx == NULL) return ;

		if (!m_fileName.empty()){
			LOG4CPLUS_TRACE(log,m_strSession << ",script file is:" << m_fileName);
			ctx->ExecuteFile(m_fileName);
		}
		else if (!content.empty()){
			LOG4CPLUS_TRACE(log,m_strSession << ",execute script is:" << content);
			ctx->CompileScript(content,m_strFileName,node->line,node);
		}
	}
}
}

