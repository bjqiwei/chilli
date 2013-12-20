#include "Script.h"
#include "../../xmlHelper.h"

namespace fsm
{
namespace model
{


	Script::Script(xmlNodePtr xNode,const std::string &session,const std::string & filename):node(xNode),
		m_strSession(session),m_strFilename(filename)
	{
		//log = TLogFile *::getInstance("fsm.model.script");
		this->content =  xmlHelper::XStr(xmlNodeGetContent(node)).strForm();
	}

	//std::string &Script::getContent()
	//{
	//	return content;
	//}
	void Script::execute(fsm::Context * ctx)
	{
		ctx->eval(this->content,m_strFilename,node->line);
	}
}
}

