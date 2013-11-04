#include "OnEntry.h"
#include "Script.h"
#include "Log.h"
#include "Transition.h"

namespace fsm{
namespace model{
	void OnEntry::execute(fsm::Evaluator * evl,fsm::Context * ctx)
	{
		if (_node == NULL) return;

		for (xmlNodePtr exeNode = _node->children ; exeNode !=  NULL; exeNode = exeNode->next)
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
			else if(exeNode->type == XML_ELEMENT_NODE &&
				xmlStrEqual(exeNode->name, BAD_CAST("transition"))){
					model::Transition tst(exeNode);
					tst.execute(evl,ctx);
					break;
			}
		}
	}
}
}