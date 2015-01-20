#include "StdAfx.h"
#include "ACDModule.h"
#include "..\model\GlobalObject.h"
#include "..\ivr\IVRModule.h"
#include "..\Sh\ShDevModule.h"
#include <process.h>
#include <regex>
#include <libxml/tree.h>
#include <log4cplus/loggingmacros.h>


namespace chilli{
namespace ACD{

std::vector<xmlNodePtr> ACDModule::m_DialPlanVector;

std::vector<VD::GroupPtr> ACDModule::m_GroupVec;
chilli::EventBuffer ACDModule::recEvtBuffer;
fsm::SMInstance ACDModule::smInstance;

ACDModule::ACDModule(void)
{
	log =log4cplus::Logger::getInstance("chilli.ACD.ACDModule");
	LOG4CPLUS_DEBUG(log,"new a ACD object.");
}


ACDModule::~ACDModule(void)
{
	recEvtBuffer.addData("quit");

	for(unsigned int i =0 ; i < m_DialPlanVector.size(); i ++)
		xmlFreeNode( m_DialPlanVector.at(i));

	for(unsigned int i =0 ; i < m_GroupVec.size(); i ++)
		delete m_GroupVec.at(i);

	LOG4CPLUS_DEBUG(log,"destruction a ACD object.");
}


bool ACDModule::Init(xmlNodePtr xNode)
{
	return Init();
}


bool ACDModule::Init(void)
{
	this->ParserConfig();
	chilli::Global::m_ExtMap.clear();
	for (unsigned int i =0 ; i < chilli::IVR::IVRModule::getExtVec().size() ; i++ )
	{
		if(chilli::Global::m_ExtMap.count(chilli::IVR::IVRModule::getExtVec().at(i)->getExtensionNumber()))
		{
			LOG4CPLUS_ERROR(log,"extension number:" <<chilli::IVR::IVRModule::getExtVec().at(i)->getExtensionNumber() << 
				", Already Exist.");
		}
		else
			chilli::Global::m_ExtMap[chilli::IVR::IVRModule::getExtVec().at(i)->getExtensionNumber()] 
				= chilli::IVR::IVRModule::getExtVec().at(i);
	}

	for (unsigned int i =0 ; i < chilli::ShDev::ShDevModule::getExtVec().size() ; i++ )
	{
		if(chilli::Global::m_ExtMap.count(chilli::ShDev::ShDevModule::getExtVec().at(i)->getExtensionNumber()))
		{
			LOG4CPLUS_ERROR(log,"extension number:" <<chilli::ShDev::ShDevModule::getExtVec().at(i)->getExtensionNumber() << 
				", Already Exist.");
		}
		else
			chilli::Global::m_ExtMap[chilli::ShDev::ShDevModule::getExtVec().at(i)->getExtensionNumber()] 
				= chilli::ShDev::ShDevModule::getExtVec().at(i);
	}

	for (unsigned int i =0 ; i < m_GroupVec.size() ; i++ )
	{
		if(chilli::Global::m_ExtMap.count(m_GroupVec.at(i)->getExtensionNumber()))
		{
			LOG4CPLUS_ERROR(log,"extension number:" <<m_GroupVec.at(i)->getExtensionNumber() << 
				", Already Exist.");
		}
		else{
			chilli::Global::m_ExtMap[m_GroupVec.at(i)->getExtensionNumber()]=m_GroupVec.at(i);
			m_GroupVec.at(i)->Init();
		}
	}

	LOG4CPLUS_DEBUG(log,"ACD device init ok.");
	return true;
}

bool ACDModule::ParserConfig(void)
{
	if (this->m_xmlConfigNodePtr == NULL)
	{
		LOG4CPLUS_WARN(log,"xmlConfigNode is null.");
		return false;
	}
	for(unsigned int i =0 ; i < m_DialPlanVector.size(); i ++)
		xmlFreeNode( m_DialPlanVector.at(i));
	m_DialPlanVector.clear();

	xmlNodePtr xDialplanNode = helper::xml::getXmlChildNode(m_xmlConfigNodePtr,"dialplan");
	if (xDialplanNode == NULL) LOG4CPLUS_WARN(log,"DialPlan Node is null.");
	else{
		for(xmlNodePtr xExtNode = xDialplanNode->children; xExtNode != NULL; xExtNode=xExtNode->next)
		{
			if (!abstract::Extension::isExtConfigNode(xExtNode)) continue;
			xmlNodePtr xNode = xmlCopyNode(xExtNode,1);
			m_DialPlanVector.push_back(xNode);
		}
	}

	xmlNodePtr xConfNode = helper::xml::getXmlChildNode(m_xmlConfigNodePtr,"config");
	xmlNodePtr xGroupsNode = helper::xml::getXmlChildNode(xConfNode,"groups");

	for (std::vector<VD::GroupPtr>::const_iterator it = m_GroupVec.begin();
		it != m_GroupVec.end(); it++)
	{
		delete *it;
	}
	m_GroupVec.clear();

	if (xGroupsNode == NULL)	LOG4CPLUS_WARN(log,"Groups Node is null.");
	else
		for(xmlNodePtr xGpNode = xGroupsNode->children; xGpNode != NULL; xGpNode=xGpNode->next)
		{
			if (!VD::Group::isGroupConfigNode(xGpNode)) continue;
			VD::GroupPtr gpPtr = new VD::Group();
			gpPtr->setXmlConfigNode(xGpNode);
			gpPtr->ParserConfig();
			m_GroupVec.push_back(gpPtr);
		}

	return true;
}

void ACDModule::DisplayEventInfo ( std::string strEvent )
{
	LOG4CPLUS_INFO(log," Recive a event,event=" << strEvent);
}

int ACDModule::Close(void)
{
	CloseHandle(td.thread_hnd);
	recEvtBuffer.addData("quit");
	LOG4CPLUS_DEBUG(log,"Close a ACD device");
	return 0;
}

void ACDModule::Start()
{
	for(unsigned int i =0; i < m_GroupVec.size(); i++){
		m_GroupVec.at(i)->go();
	}

	td.thread_hnd = (HANDLE)_beginthreadex(NULL,0,ThreadProc,NULL,0,&td.thread_id);

	if (!td.thread_hnd){
		LOG4CPLUS_ERROR(log,"_beginthreadex() failed;error no.=" << GetLastError());
	}else{
		LOG4CPLUS_INFO(log,"_beginthreadex() ok;thread_id=" << td.thread_id);
	}
	return ;
}
bool ACDModule::reloadConfig(xmlNodePtr xNode)
{
	return Init(xNode);
}

void ACDModule::addEventToBuffer(std::string strContent)
{
	recEvtBuffer.addData(strContent);
}

unsigned int ACDModule::ThreadProc( void *pParam )
{
	static log4cplus::Logger log = log4cplus::Logger::getInstance("chilli.ACD.Thread");
	DWORD rv;
	std::string strEvent;
	while(1)
	{
		rv = WaitForSingleObject(recEvtBuffer.semaphore,INFINITE);
		switch (rv) {
		case WAIT_OBJECT_0:
			strEvent = recEvtBuffer.getData();
			if (strEvent.compare("quit") == 0){
				_endthreadex(0);
			}else{
				LOG4CPLUS_WARN(log,"WaitForSingleObject, wait a event to processing event=" <<
					strEvent);
				EvtHandler(strEvent);
			}
			break;

		case WAIT_TIMEOUT:
			LOG4CPLUS_ERROR(log,"WaitForSingleObject, wait timeout.");
			break;

		case WAIT_FAILED:
			LOG4CPLUS_ERROR(log,"WaitForSingleObject, wait failed.error=" << GetLastError());
			break;
		default:
			LOG4CPLUS_WARN(log,"WaitForSingleObject, unknow single.");
			break;
		}
	}
}
xmlNodePtr ACDModule::isMatched(xmlNodePtr xExtNode,std::string strEvent)
{
	helper::xml::CXmlDocumentPtr _xmlDocPtr = xmlParseMemory(strEvent.c_str(),strEvent.length());
	xmlNodePtr _eventNode = xmlDocGetRootElement(_xmlDocPtr._xDocPtr);
	if (_eventNode == NULL)
	{
		LOG4CPLUS_WARN(log,"recive one event,parse document error. event =" <<strEvent );
		return NULL;
	}
	xmlNodePtr xCndNode = helper::xml::getXmlChildNode(xExtNode,"condition");
	if (xCndNode == NULL)
	{
		LOG4CPLUS_WARN(log,"recive one event,not found condition node. extension name=" 
			<< helper::xml::getXmlNodeAttributesValue(xExtNode,"name")  );
		return NULL;
	}

	std::string strField = helper::xml::getXmlNodeAttributesValue(xCndNode,"field");
	std::string strExpression = helper::xml::getXmlNodeAttributesValue(xCndNode,"expression");
	std::string strExpValue = helper::xml::getXmlNodeAttributesValue(_eventNode,strField);

	if (strExpValue.empty()) return NULL;

	std::regex regPattern(strExpValue);
	if (!std::regex_match(strExpValue,regPattern))
	{
		return NULL;
	}
	return xCndNode;
}

int ACDModule::processTransfer(xmlNodePtr xAppNode ,std::string strEvent)
{
	std::string strDestNum = helper::xml::getXmlNodeAttributesValue(xAppNode,"data");
	std::map<std::string , chilli::abstract::ExtensionPtr>::iterator it 
		= chilli::Global::m_ExtMap.find(strDestNum);
	if (it != chilli::Global::m_ExtMap.end())
	{
		//it->second->processTransfer(strEvent,"");
		LOG4CPLUS_WARN(log, "no found the dest number:" << strDestNum);
	}
	else{
		LOG4CPLUS_WARN(log, "no found the dest number:" << strDestNum);
	}
	return 0;
}

int ACDModule::EvtHandler(const std::string& strEvent)
{
	static log4cplus::Logger log = log4cplus::Logger::getInstance("chilli.ACD.EvtHandler");
	
	helper::xml::CXmlParseHelper xmlParse(strEvent);
	

	//std::string _event = Interpreter::getXmlNodeAttributesValue(xrootNode,"event");
	
	/*if (_event.compare("transfer") == 0)
	{*/
		std::string dest = xmlParse.getRootProp("dest");
		if(chilli::Global::m_ExtMap.count(dest) > 0)
		{
			chilli::Global::m_ExtMap[dest]->addAcdEvent(strEvent);
			return 1;
		}
		else{
			LOG4CPLUS_ERROR(log,"not find  destination:" << dest);
		}
	//}

	LOG4CPLUS_WARN(log,"recive one event,extension is Out of range. event =" <<strEvent );

	return 0;
}


int ACDModule::processActions(xmlNodePtr xCondNode,std::string strEvent)
{
	xmlNodePtr xActNode = helper::xml::getXmlChildNode(xCondNode,"action");
	std::string strApp = helper::xml::getXmlNodeAttributesValue(xActNode,"application");

	if (strApp.compare("transfer") == 0){
		return processTransfer(xActNode ,strEvent);
	}
	else{
		LOG4CPLUS_WARN(log,strApp << " program is not implemented.");
	}

	return 0;
}

}
}
