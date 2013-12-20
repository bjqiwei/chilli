#include "Event.h"
#include "Script.h"
#include "Log.h"
#include "Transition.h"
#ifdef WIN32
#include <regex>
#endif

namespace fsm
{
namespace model
{

	Event::Event(xmlNodePtr xNode,const std::string &session,const std::string &filename):node(xNode),m_bCond(true),
		m_strSession(session),
		m_strFilename(filename),cx(NULL)
	{
		m_strCond = xmlHelper::getXmlNodeAttributesValue(node,"cond");
		m_strEvent = xmlHelper::getXmlNodeAttributesValue(node,"event");
		m_bCond = true;
	}

	const std::string &Event::getCond()
	{
		return m_strCond;
	}

	const std::string &Event::getEvent()
	{
		return m_strEvent ;
	}
	
	void Event::execute(fsm::Context * ctx)
	{
		cx = ctx;
		
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

	bool Event::isEnabledEvent(const string& strEventName) const 
	{
		using namespace xmlHelper;
		
		if (m_strEvent.empty()) {

		} else {
#ifdef WIN32
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



	bool Event::isEnabledCondition() 
	{
		if (!this->getCond().empty() && cx){
			return cx->evalCond(this->getCond(),m_strFilename,node->line);
		}
		return m_bCond;
	}
}
}
