#include "Function.h"
#include <log4cplus/loggingmacros.h>
#include "../../xmlHelper.h"

namespace fsm{
namespace model{

Function::Function(xmlNodePtr xNode ,const std::string & session, const std::string & filename):
node(xNode),m_strSession(session),m_strFileName(filename)
{
	m_strContent = xmlHelper::XStr(xmlNodeGetContent(node)).strForm();
	m_fileName = xmlHelper::XStr(xmlGetProp(node,BAD_CAST"src")).strForm();
	log = log4cplus::Logger::getInstance("fsm.model.Function");
}

void Function::execute(fsm::Context * ctx)
{
	if (ctx == NULL){
		LOG4CPLUS_WARN(log,"Context is null.");
		return ;
	}

	if (!m_fileName.empty()){
		LOG4CPLUS_TRACE(log,m_strSession << ",define a function script is:" << m_fileName);
		ctx->ExecuteFile(m_fileName);
	}
	else if (!m_strContent.empty()){
		LOG4CPLUS_TRACE(log,m_strSession << ",define a function script is:" << m_strContent);
		ctx->CompileScript(m_strContent,m_strFileName,node->line,node);
	}
}

Function::~Function(void)
{
}

}// end namespace model
}// end namespace fsm
