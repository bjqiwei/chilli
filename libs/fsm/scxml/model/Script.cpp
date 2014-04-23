#include "Script.h"
#include "../../common/xmlHelper.h"

namespace fsm
{
namespace model
{


	Script::Script(xmlNodePtr xNode,const std::string &session,const std::string & filename):node(xNode),
		m_strSession(session),m_strFilename(filename)
	{
		log = log4cplus::Logger::getInstance("fsm.model.Script");
		this->content =  helper::xml::XStr(xmlNodeGetContent(node)).strForm();
	}

	//std::string &Script::getContent()
	//{
	//	return content;
	//}
	void Script::execute(fsm::Context * ctx)
	{
		ctx->eval(this->content,m_strFilename,node->line,node);
	}
}
}

