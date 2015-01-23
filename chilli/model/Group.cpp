#include "StdAfx.h"
#include "Group.h"
#include <fsm.h>
#include "..\ACD\ACDModule.h"
#include <log4cplus/loggingmacros.h>



namespace chilli
{
namespace VD{
	
	Group::Group():Extension()
	{
		log = log4cplus::Logger::getInstance("CTI.Group");
		LOG4CPLUS_TRACE(log,"new a Group object.");
	}
	Group::~Group(){
		LOG4CPLUS_TRACE(log,"destruction a extension object.");
	}
	bool Group::Init()
	{
		this->stateMachie.setscInstance(&chilli::ACD::ACDModule::smInstance);
		return Extension::Init();
	}

	bool Group::ParserConfig(void)
	{
		if(chilli::abstract::Extension::ParserConfig())
		{
			for (xmlNodePtr xExtNode = m_xmlConfigNodePtr->children; xExtNode != NULL ; xExtNode = xExtNode->next)
			{
				if (!isExtConfigNode(xExtNode)) continue;
				m_ExtVec.push_back(helper::xml::XStr(xmlNodeGetContent(xExtNode)).strForm());
			}
			return true;
		}
		return false;
	}
	bool Group::processTransfer(std::string strCmd,std::string from)
	{
		using namespace helper::xml;
		for(unsigned int i =0 ; this->m_ExtVec.size(); i++)
		{
			std::map<std::string , chilli::abstract::ExtensionPtr>::iterator it
			= chilli::Global::m_ExtMap.find(m_ExtVec.at(i));
			if (it != chilli::Global::m_ExtMap.end() && it->second->isIdle())
			{
				CXmlDocmentHelper xmlDocHlp;

				xmlDocHlp.setRootNode("event");
				xmlDocHlp.newRootProp("event","deliver");
				xmlDocHlp.newRootProp("from",it->second->getExtensionNumber());
				xmlDocHlp.newRootProp("dest",from.c_str());
				xmlDocHlp.addChild("data",it->second->getExtensionNumber());

				chilli::ACD::ACDModule::recEvtBuffer.addData(xmlDocHlp.getContent());

				
				CXmlParseHelper xmlParse(strCmd);
				xmlParse.setRootAttributesValue("dest",it->second->getExtensionNumber());
				
				return it->second->processTransfer(xmlParse.getContent(),from);
			}
		}

		return true;
	}

	bool Group::addAcdEvent(const std::string& strEvent)
	{
		helper::xml::CXmlParseHelper xmlParse(strEvent);
		
		if (xmlParse.getRootName().compare("cmd") == 0){
			this->processCmd(strEvent);
		}else if (xmlParse.getRootName().compare("event") == 0)
		{
			this->processEvent(strEvent);
		}else{
			LOG4CPLUS_ERROR(log,"not distinguish this msg name:" << xmlParse.getRootName());
		}
		return true;
	}

	int Group::processCmd(const std::string& strCmd)
	{
		using namespace helper::xml;
		CXmlParseHelper xmlParse(strCmd);

		std::string _cmd =xmlParse.getRootProp("cmd");
		std::string from = xmlParse.getRootProp("from");
		if (_cmd.compare("transfer") == 0)
		{
			return processTransfer(strCmd,from);
		}
		return 1;
	}
	int Group::processEvent(const std::string& strEvent)
	{
		LOG4CPLUS_WARN(log, "this fuction processEvent not implement. ");
		return -1;
	}


	void Group::fireSend(const std::string &strContent)
	{
		LOG4CPLUS_TRACE(log," recive a Send event from stateMachine:" << strContent);
		processCmd(strContent);
	}

}
}
