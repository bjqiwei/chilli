#include "stdafx.h"
#include "IVRModule.h"
#include <scxml/env/JSContext.h>
#include <scxml/env/JSEvaluator.h>
#include <scxml/SCXMLHelper.h>
#include <scxml/TriggerEvent.h>
#include "../Sh/ShDevModule.h"
#include <xmlHelper.h>
#include <process.h>

namespace chilli{
namespace IVR
{
	std::vector<IVRExtensionPtr> IVRModule::m_ExtensionVector;
	chilli::EventBuffer IVRModule::recEvtBuffer;
	fsm::SCInstance IVRModule::scInstance;;

	IVRModule::IVRModule(void)
	{
		log =log4cplus::Logger::getInstance("chilli.IVR.IVRModule");
		scInstance.setLog(log);
		scInstance.addEventFunction = addEventToBuffer;
		LOG4CPLUS_DEBUG(log,"new a IVRModule object.");
	}


	IVRModule::~IVRModule(void)
	{
		recEvtBuffer.addData("quit");
		for (unsigned int i =0; i < m_ExtensionVector.size(); i++)
		{
			delete m_ExtensionVector.at(i);
		}
		LOG4CPLUS_DEBUG(log,"destruction a IVRModule object.");
	}
	bool IVRModule::Init(xmlNodePtr xNodePtr)
	{
		setConfigNode(xNodePtr);
		return Init();
	}

	bool IVRModule::Init(void)
	{
		this->ParserConfig();

		for (unsigned int i =0 ; i< m_ExtensionVector.size(); i++)
		{
			if (m_ExtensionVector.at(i))
			{
				m_ExtensionVector.at(i)->Init();
			}
		}
		LOG4CPLUS_DEBUG(log,"IVRModule device init ok.");
		return true;
	}

	int IVRModule::Close(void)
	{
		recEvtBuffer.addData("quit");
		CloseHandle(td.thread_hnd);
		LOG4CPLUS_DEBUG(log,"Close a IVRModule device");
		return 0;
	}

	bool IVRModule::reloadConfig(xmlNodePtr xNode)
	{
		setConfigNode(xNode);
		for (unsigned int i =0 ; i< m_ExtensionVector.size(); i++)
		{
			m_ExtensionVector.at(i)->setIsNewConfig(true);
			//m_ExtensionVector.at(i)->m_bEnable = false;
		}
		this->ParserConfig();
		return true;
	}	

	

	bool IVRModule::ParserConfig(void)
	{
		if (this->m_xmlConfigNodePtr == NULL)
		{
			LOG4CPLUS_WARN(log,"xmlConfigNode is null.");
			return false;
		}
		xmlNodePtr xConfigNode = fsm::xmlHelper::getXmlChildNode(m_xmlConfigNodePtr,"config");
		if (xConfigNode == NULL)
		{
			LOG4CPLUS_WARN(log,"xmlConfigNode is null.");
			return false;
		}

		for (unsigned int i =0; i < m_ExtensionVector.size(); i++)
		{
			m_ExtensionVector.at(i)->setIsNewConfig(true);
		}
		m_ExtensionVector.clear();

		xmlNodePtr xExtsNode = fsm::xmlHelper::getXmlChildNode(xConfigNode,"IVRExtensions");
		if(xExtsNode)
		{
			for(xmlNodePtr xExtNode = xExtsNode->children; xExtNode != NULL; xExtNode=xExtNode->next)
			{
				if (!chilli::abstract::Extension::isExtConfigNode(xExtNode)) continue;
				IVRExtensionPtr ptrExt = new IVRExtension();
				m_ExtensionVector.push_back(ptrExt);
				ptrExt->setXmlConfigNode(xExtNode);	
			}
			for (unsigned int i =0 ; i< m_ExtensionVector.size(); i++)
			{
				if (m_ExtensionVector.at(i))
				{
					m_ExtensionVector.at(i)->ParserConfig();
				}
			}
		}
		return true;
	}


	void IVRModule::DisplayEventInfo ( std::string strEvent )
	{
		LOG4CPLUS_INFO(log," Recive a event,event=" << strEvent);
	}

	void IVRModule::addEventToBuffer(std::string strContent)
	{
		recEvtBuffer.addData(strContent);
	}

	int IVRModule::EvtHandler(std::string strEvent)
	{
		fsm::xmlHelper::xmlDocumentPtr _xmlDocPtr = xmlParseMemory(strEvent.c_str(),strEvent.length());
		xmlNodePtr _rootNode = xmlDocGetRootElement(_xmlDocPtr._xDocPtr);
		if (_rootNode == NULL)
		{
			LOG4CPLUS_WARN(log,"recive one event,parse document error. event =" <<strEvent );
			return -1;
		}

		std::string  strExtNumber = fsm::xmlHelper::getXmlNodeAttributesValue(_rootNode,"Extension");
		for (unsigned int i = 0 ; i< m_ExtensionVector.size(); i++)
		{
			if (m_ExtensionVector.at(i)->getExtensionNumber().compare(strExtNumber) == 0)
			{
				return m_ExtensionVector.at(i)->EvtHandler(strEvent);
			}
		}
		
		LOG4CPLUS_WARN(log,"recive one event,extension is Out of range. event =" <<strEvent );
	
		return 0;
	}

	void IVRModule::Start()
	{
		for(unsigned int i =0; i < m_ExtensionVector.size(); i++){
			m_ExtensionVector.at(i)->go();
		}

		td.thread_hnd = (HANDLE)_beginthreadex(NULL,0,ThreadProc,NULL,0,&td.thread_id);

		if (!td.thread_hnd){
			LOG4CPLUS_ERROR(log,"_beginthreadex() failed;error no.=" << GetLastError());
		}else{
			LOG4CPLUS_INFO(log,"_beginthreadex() ok;thread_id=" << td.thread_id);
		}
		return ;
	}
	const std::vector<IVRExtensionPtr> & IVRModule::getExtVec()
	{
		return m_ExtensionVector;
	}



	unsigned int IVRModule::ThreadProc( void *pParam )
	{
		using namespace fsm::xmlHelper;
		static log4cplus::Logger logger = log4cplus::Logger::getInstance("chilli.IVRModule.Thread");
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
					LOG4CPLUS_DEBUG(logger,"WaitForSingleObject, Receive an event to processing event=" <<
						strEvent);

					CXmlParseHelper xmlParse(strEvent);
					std::string _dest = xmlParse.getRootProp("dest");;
					IVRExtensionPtr extPtr = NULL;
					for (unsigned i =0 ; i< m_ExtensionVector.size(); i++)
					{
						if (m_ExtensionVector.at(i)->m_strExtensionNumber.compare(_dest) == 0){
							extPtr = m_ExtensionVector.at(i);
							break;
						}
					}
					if (extPtr)
					{
						if (xmlParse.getRootName().compare("cmd") == 0){
							extPtr->processCmd(strEvent);
						}else if (xmlParse.getRootName().compare("event") == 0)
						{
							extPtr->processEvent(strEvent);
						}else{
							LOG4CPLUS_ERROR(logger,"not distinguish this msg name:" << xmlParse.getRootName());
						}
					}else{
						LOG4CPLUS_ERROR(logger,"not find  destination:" << _dest);
					}
				}
				break;

			case WAIT_TIMEOUT:
				LOG4CPLUS_ERROR(logger,"WaitForSingleObject, wait timeout.");
				break;

			case WAIT_FAILED:
				LOG4CPLUS_ERROR(logger,"WaitForSingleObject, wait failed.error=" << GetLastError());
				break;
			default:
				LOG4CPLUS_WARN(logger,"WaitForSingleObject, unknow single.");
				break;
			}
		}
	}
}
}

