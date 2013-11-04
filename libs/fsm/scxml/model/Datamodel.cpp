#include "Datamodel.h"
#include "Data.h"

namespace fsm
{
namespace model
{

	Datamodel::Datamodel(xmlNodePtr xNode):node(xNode){}


	void Datamodel::execute(fsm::Evaluator * evl,fsm::Context * ctx){
		if (node == 0) return;

		for (xmlNodePtr dataNode = node->children ; dataNode !=  NULL; dataNode = dataNode->next)
		{
			if(dataNode->type != XML_ELEMENT_NODE ||
				!xmlStrEqual(dataNode->name, BAD_CAST("data")))
				continue;
			model::Data datum(dataNode);
			datum.execute(evl,ctx);
		}
	}
}
}

