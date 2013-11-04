#include "Script.h"
#include <xmlHelper.h>

namespace fsm
{
namespace model
{


	Script::Script(xmlNodePtr xNode):node(xNode)
	{
		//log = log4cplus::Logger::getInstance("fsm.model.script");
		this->content =  xmlHelper::XStr(xmlNodeGetContent(node)).strForm();
	}

	//std::string &Script::getContent()
	//{
	//	return content;
	//}
	void Script::execute(fsm::Evaluator * evl,fsm::Context * ctx)
	{
		evl->eval(ctx,this->content,node->line);
	}
}
}

