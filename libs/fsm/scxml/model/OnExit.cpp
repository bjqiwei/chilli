#include "OnExit.h"


namespace fsm{
namespace model{

	void OnExit::execute(fsm::Context * ctx)
	{
		if (m_node == 0) return;

		/*for (xmlNodePtr exeNode = node->children ; exeNode !=  NULL; exeNode = exeNode->next)
		{
			if(exeNode->type == XML_ELEMENT_NODE &&
				xmlStrEqual(exeNode->name, BAD_CAST("script"))){
					model::Script spt(exeNode);
					spt.execute(evl,ctx);
			}else if(exeNode->type == XML_ELEMENT_NODE &&
				xmlStrEqual(exeNode->name, BAD_CAST("log"))){
					model::Log log(exeNode);
					log.execute(evl,ctx);
			}
		}*/
	}

	bool OnExit::isEnabledCondition(fsm::Context * ctx)
	{
		return true;
	}
}

}