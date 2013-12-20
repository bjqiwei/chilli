#include "Function.h"
#include <log4cplus/loggingmacros.h>
#include "../../xmlHelper.h"
#include "../SCXMLHelper.h"

namespace fsm{
namespace model{

Function::Function(xmlNodePtr xNode ,const std::string & session, const std::string & filename):
node(xNode),m_strSession(session),m_strFileName(filename)
{
	m_strContent = xmlHelper::XStr(xmlNodeGetContent(node)).strForm();;
	log = log4cplus::Logger::getInstance("StateMachine.model.Function");
}

void Function::execute(fsm::Context * ctx)
{
	LOG4CPLUS_TRACE(log,m_strSession << ",define a function script is:" << m_strContent);
	if (!SCXMLHelper::isStringEmpty(m_strContent))
	{
		ctx->CompileScript(m_strContent,m_strFileName,node->line);
	}
}

Function::~Function(void)
{
}

}// end namespace model
}// end namespace fsm
