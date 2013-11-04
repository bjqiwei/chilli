#include "Event.h"
#include "Script.h"
#include "Log.h"
#include "Transition.h"
#include <regex>

namespace fsm
{
namespace model
{

	Event::Event(xmlNodePtr xNode):node(xNode)
	{
		log = log4cplus::Logger::getInstance("fsm.model.event");
		m_strCond = xmlHelper::getXmlNodeAttributesValue(node,"cond");
		m_strEvent = xmlHelper::getXmlNodeAttributesValue(node,"event");
		m_bCond = true;
	}

	std::string &Event::getCond()
	{
		return m_strCond;
	}

	std::string &Event::getEvent()
	{
		return m_strEvent ;
	}
	
	void Event::execute(fsm::Evaluator * evl,fsm::Context * ctx)
	{
		m_bCond = evl->evalCond(ctx,this->getCond(),node->line);
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
			std::regex regPattern(m_strEvent);
			if (!std::regex_match(strEventName,regPattern))
			{
				return false;
			}
		}
		return true;
	}



	bool Event::isEnabledCondition() const
	{
		return m_bCond;
	}
}
}
