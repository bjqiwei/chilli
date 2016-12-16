#include "Scriptmodel.h"
#include <log4cplus/loggingmacros.h>
#include "Script.h"

namespace fsm{
namespace model{


Scriptmodel::Scriptmodel(xmlNodePtr xnode,const std::string &session, const std::string &filename):
	Action(xnode, session, filename)
{
	log = log4cplus::Logger::getInstance("fsm.model.Scriptmodel");
}

void Scriptmodel::execute(fsm::Context * ctx){
	//LOG4CPLUS_TRACE(log,m_strSession << ",execute starting...");
	if (m_node == NULL) return;
	bool bFindData = false;
	for (xmlNodePtr funNode = m_node->children ; funNode !=  NULL; funNode = funNode->next)
	{
		if(funNode->type != XML_ELEMENT_NODE ||
			!xmlStrEqual(funNode->name, BAD_CAST("script")))
			continue;
		bFindData = true;
		model::Script script(funNode,m_strSession,m_strFileName);
		script.execute(ctx);
	}
	if (!bFindData)
	{
		LOG4CPLUS_WARN(log, m_strSession << ",not find data element in this Scriptmodel.");
	}
	//LOG4CPLUS_TRACE(log,m_strSession << ",execute end.");
}

bool Scriptmodel::isEnabledCondition(fsm::Context * ctx)
{
	return true;
}

Scriptmodel::~Scriptmodel(void)
{
}
}//end namespace model
}// end namespace fsm
