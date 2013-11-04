#include "StdAfx.h"
#include "ShExtension.h"
#include "../model/GlobalObject.h"
#include "ShDevModule.h"
#include <scxml/env/JSContext.h>


namespace chilli{
namespace ShDev{

ShExtension::ShExtension(void)
{
	this->log = log4cplus::Logger::getInstance("chilli.ShDev.Extension");
	LOG4CPLUS_DEBUG(log,"new a extension object.");
}



ShExtension::~ShExtension(void)
{
	LOG4CPLUS_DEBUG(log,"destruction a extension object.");
}

bool ShExtension::ParserConfig(void)
{
	if(chilli::abstract::Extension::ParserConfig())
	{
		this->setType(fsm::xmlHelper::getXmlNodeAttributesValue(m_xmlConfigNodePtr,"Type"));
		return true;
	}
	return false;
}

bool ShExtension::setType(std::string strType)
{
	if (this->nType != ShDevModule::getDeviceTypeByName(strType))
	{
		LOG4CPLUS_ERROR(log,"the type set not match the device type:"<<strType << ",set UnEnable.");
		this->m_bEnable = false;
		return false;
	}
	LOG4CPLUS_DEBUG(log,"set type="<<strType);
	return true;
}
void ShExtension::setType(int _type)
{
	return ShChannel::setType(_type);
}

int ShExtension::getChannelID()
{
	return ShChannel::getChannelID();
}
bool ShExtension::Init(void)
{
	stateMachie.setscInstance(&chilli::abstract::DevModule::scInstance);
	return Extension::Init();
}



void ShExtension::fireSend(const std::string &strContent)
{
	LOG4CPLUS_TRACE(log," recive a Send event from stateMachine:" << strContent);
	processCmd(strContent);
}

int ShExtension::processCmd(const std::string& strCmd)
{
	fsm::xmlHelper::xmlDocumentPtr xDocPtr = xmlParseMemory(strCmd.c_str(),strCmd.length());
	if (xDocPtr._xDocPtr == NULL)
	{
		LOG4CPLUS_ERROR(log," Convert a string to xml error was encountered,string="<<strCmd);
		return -1;
	}
	xmlNodePtr xrootNode = xmlDocGetRootElement(xDocPtr._xDocPtr);
	//xmlNodePtr xCttNode = Interpreter::getXmlChildNode(xrootNode,"content");
	std::string _cmd = fsm::xmlHelper::getXmlNodeAttributesValue(xrootNode,"cmd");
	if (_cmd.compare("autoSendDialTone") == 0)
	{
		std::string strParaValue = fsm::xmlHelper::getXmlChildNodeValue(xrootNode,"enable");
		this->AutoSendDialTone(atoi(strParaValue.c_str()));
	}else if (_cmd.compare("reloadConfig") == 0)
	{
		this->reload();
	}
	else if (_cmd.compare("answer") == 0)
	{
		this->Answer();
	}
	else if (_cmd.compare("playFile") == 0)
	{
		this->PlayFile(fsm::xmlHelper::getXmlChildNodeValue(xrootNode,"file"));
	}
	else if (_cmd.compare("hangUp") == 0)
	{
		this->HangUp();
	}
	return 0;
}

int ShExtension::processEvent(const std::string& strEvent)
{
	fsm::xmlHelper::xmlDocumentPtr xDocPtr = xmlParseMemory(strEvent.c_str(),strEvent.length());
	if (xDocPtr._xDocPtr == NULL)
	{
		LOG4CPLUS_ERROR(log," Convert a string to xml error was encountered,string="<<strEvent);
		return -1;
	}
	xmlNodePtr xrootNode = xmlDocGetRootElement(xDocPtr._xDocPtr);
	if (xrootNode == NULL){
		LOG4CPLUS_ERROR(log, ": Convert a string to xml error was encountered,string="<<strEvent);
		return -1;
	}

	std::string _event = fsm::xmlHelper::getXmlNodeAttributesValue(xrootNode,"event");
	this->_event_data = fsm::xmlHelper::getXmlNodeAttributesValue(xrootNode,"from");
	fsm::TriggerEvent evt(_event,this->_event_data,0);
	LOG4CPLUS_INFO(log,  " Recived a event,"<<"from " <<  this->_event_data << "event=" << evt.ToString());
	stateMachie.pushEvent(evt);
	return 0;
}

bool ShExtension::processTransfer(std::string strEvent,std::string from)
{
	abstract::DevModule::recEvtBuffer.addData(strEvent);
	return true;
}

bool ShExtension::addAcdEvent(const std::string& strEvent)
{
	abstract::DevModule::recEvtBuffer.addData(strEvent);
	return true;
}

}
}
