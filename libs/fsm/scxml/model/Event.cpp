#include "Event.h"
#include "../../common/xmlHelper.h"
#ifdef WIN32
#include <regex>
#endif

namespace fsm
{
namespace model
{

	Event::Event(xmlNodePtr xNode,const std::string &session,const std::string &filename):Action(xNode, session,filename)
	{
		log = log4cplus::Logger::getInstance("fsm.model.Event");
		m_strEvent = helper::xml::getXmlNodeAttributesValue(node,"event");
	}

	const std::string &Event::getEvent()
	{
		return m_strEvent ;
	}
	
	void Event::execute(fsm::Context * ctx)
	{
		
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
			else if(exeNode->type == XML_ELEMENT_NODE &&
				xmlStrEqual(exeNode->name, BAD_CAST("transition"))){
					model::Transition tst(exeNode);
					tst.execute(evl,ctx);
					break;
			}
		}*/
	}

	bool Event::isEnabledEvent(const std::string& strEventName) const 
	{
		
		if (m_strEvent.empty()) {

		} else {
#ifdef USEDREGEX
			std::regex regPattern(m_strEvent);
			if (!std::regex_match(strEventName,regPattern))
			{
				return false;
			}
#else
			return strEventName.find(m_strEvent) != std::string::npos;
#endif
		}
		return true;
	}

}
}
