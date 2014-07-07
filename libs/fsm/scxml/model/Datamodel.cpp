#include "Datamodel.h"
#include "Data.h"
#include <log4cplus/loggingmacros.h>

namespace fsm
{
namespace model
{

	Datamodel::Datamodel(xmlNodePtr xNode,const std::string &session,const std::string &filename):Action(xNode, session, filename)
	{
		log = log4cplus::Logger::getInstance("fsm.model.Datamodel");
	}


	void Datamodel::execute(fsm::Context * ctx){
		//LOG4CPLUS_TRACE(log,m_strSession << ",execute starting...");
		if (node == 0) return;
		bool bFindData = false;
		for (xmlNodePtr dataNode = node->children ; dataNode !=  NULL; dataNode = dataNode->next)
		{
			if(dataNode->type != XML_ELEMENT_NODE ||
				!xmlStrEqual(dataNode->name, BAD_CAST("data")))
				continue;
			bFindData = true;
			model::Data datum(dataNode,m_strSession,m_strFileName);
			datum.execute(ctx);
		}
		if (!bFindData)
		{
			LOG4CPLUS_WARN(log,"not find data element in this datamodel.");
		}
		//LOG4CPLUS_TRACE(log,m_strSession << ",execute end.");
	}
}
}

