#include "StdAfx.h"
#include "DevModule.h"
#include <process.h>
#include <log4cplus/loggingmacros.h>
#include <common/xmlHelper.h>
#include "../model/Extension.h"

namespace chilli{
namespace model{

helper::CEventBuffer<std::string> DevModule::recEvtBuffer;

DevModule::DevModule(void)
{
	log = log4cplus::Logger::getInstance("chilli.abstract.DevModule");
	LOG4CPLUS_DEBUG(log,"new a DevModule object.");
}


DevModule::~DevModule(void)
{
	LOG4CPLUS_DEBUG(log,"destruction a DevModule object.");
}


void DevModule::addEventToBuffer(std::string strContent)
{
	recEvtBuffer.addData(strContent);
}

//unsigned int DevModule::ThreadProc( void *pParam )
//{
//	static log4cplus::Logger log = log4cplus::Logger::getInstance("chilli.ShDev.ShDevModule.ThreadProc");
//	DWORD rv;
//	std::string strEvent;
//	while(1)
//	{
//		rv = WaitForSingleObject(recEvtBuffer.semaphore,INFINITE);
//		switch (rv) {
//		case WAIT_OBJECT_0:
//			strEvent = recEvtBuffer.getData();
//			if (strEvent.compare("quit") == 0){
//				_endthreadex(0);
//			}else{
//				LOG4CPLUS_TRACE(log,"WaitForSingleObject, Receive an event to processing event=" << strEvent);
//				helper::xml::CXmlParseHelper xmlParse(strEvent);
//				
//				//xmlNodePtr xCttNode = Interpreter::getXmlChildNode(xrootNode,"content");
//				std::string _dest = xmlParse.getRootProp("dest");
//				chilli::model::ExtensionPtr extPtr = NULL;
//				for (unsigned i =0 ; i< m_ExtensionVector.size(); i++)
//				{
//					if (m_ExtensionVector.at(i)->getExtensionNumber().compare(_dest) == 0){
//						extPtr = m_ExtensionVector.at(i);
//						break;
//					}
//				}
//				if (extPtr != NULL)
//				{
//					//fsm::TriggerEvent evt(xmlParse.getRootProp(xmlParse.getRootName()),
//						//xmlParse.getChildContent("data"),0);
//					//extPtr->_event_data = xmlParse.getChildContent("data");
//					if (xmlParse.getChildContent("data").compare("S_CALL_RINGING") == 0)
//					{ 
//						//extPtr->m_CalleeId = xmlParse.getChildContent("Callee");
//						//extPtr->m_CallerId = xmlParse.getChildContent("Caller");
//					}else if (xmlParse.getChildContent("data").compare("S_CALL_STANDBY") == 0)
//					{
//						//extPtr->m_CalleeId = "";
//						//extPtr->m_CallerId = "";
//						//extPtr->m_PendingReason = "";
//					}
//					else if (xmlParse.getChildContent("data").compare("S_CALL_PENDING") == 0)
//					{
//						//extPtr->m_PendingReason = xmlParse.getChildContent("reason");
//					}
//					else if (xmlParse.getRootProp("cmd").compare("playFile") == 0)
//					{
//						//extPtr->_event_data = xmlParse.getChildContent("file");
//					}
//					//extPtr->pushEvent(evt);
//				}
//			}
//			break;
//
//		case WAIT_TIMEOUT:
//			LOG4CPLUS_ERROR(log,"WaitForSingleObject, wait timeout.");
//			break;
//
//		case WAIT_FAILED:
//			LOG4CPLUS_ERROR(log,"WaitForSingleObject, wait failed.error=" << GetLastError());
//			break;
//		default:
//			LOG4CPLUS_WARN(log,"WaitForSingleObject, unknow single.");
//			break;
//		}
//	}
//}

}
}
