#include "stdafx.h"
#include "Extension.h"
#include <scxml/env/JSContext.h>
#include "../Device/DevModule.h"
#include <log4cplus/loggingmacros.h>

namespace chilli{
namespace abstract{

Extension::Extension(void):m_xmlConfigNodePtr(NULL),m_bEnable(false),NewConfig(false),SendInterface("extension"){
	log = log4cplus::Logger::getInstance("chilli.abstract.Extension");
	stateMachie.setLog(log);
}


Extension::~Extension(void){

}

bool Extension::setExtensionNumber(std::string &number)
{
	LOG4CPLUS_DEBUG(log,"set ExtensionNumber="<<number);
	log4cplus::tostringstream tss;
	tss <<log.getName() << "." << number;
	log = log4cplus::Logger::getInstance(tss.str());
	stateMachie.setLog(log);
	this->m_strExtensionNumber = number;
	return true;
}

bool Extension::setEnable(std::string &strEnable)
{
	strEnable = strEnable.substr(0,1);
	this->m_bEnable = atoi(strEnable.c_str()) == 0 ? false:true;
	LOG4CPLUS_DEBUG(log,"set "<< m_strExtensionNumber <<":, enable="  <<strEnable);
	return true;
}

bool Extension::setEnable(bool nEnable)
{
	this->m_bEnable = nEnable;
	return true;
}

bool Extension::setXmlConfigNode(xmlNodePtr xNodePtr)
{
	if (xNodePtr == NULL)
	{
		LOG4CPLUS_ERROR(log,"set extension xml config extenion="
			<< m_strExtensionNumber<<
			" parameter is null. ");
		return false;
	}
	this->m_xmlConfigNodePtr = xNodePtr;
	LOG4CPLUS_DEBUG(log,"set extension xml config.");
	return true;
}

const std::string & Extension::getExtensionNumber(){
	return m_strExtensionNumber;
}
int Extension::getChannelID()
{
	return -1;
}

void Extension::pushEvent(fsm::TriggerEvent &evt){
	stateMachie.pushEvent(evt);
}

bool Extension::setStateMachineFile(std::string smFile)
{
	this->_stateMachieFile = smFile;
	LOG4CPLUS_DEBUG(log, " state machine file="  <<smFile);
	return true;
}

bool Extension::ParserConfig(void)
{
	if (m_xmlConfigNodePtr == NULL)
	{
		LOG4CPLUS_ERROR(log,"xmlConfigNode is null.");
		return false;
	}
	this->setExtensionNumber(helper::xml::getXmlNodeAttributesValue(m_xmlConfigNodePtr,"ExtensionNumber"));
	this->setStateMachineFile(helper::xml::getXmlNodeAttributesValue(m_xmlConfigNodePtr,"StateMachine"));
	this->setEnable(helper::xml::getXmlNodeAttributesValue(m_xmlConfigNodePtr,"Enable"));
	return true;
}

const std::string Extension::getStateID()
{
	return stateMachie.getCurrentStateID();
}

bool Extension::isIdle()
{
	return (getStateID().compare("idle") == 0) || (getStateID().compare("init") == 0) ;
}
bool Extension::Init(void)
{
	stateMachie.addSendImplement(this);
	stateMachie.addSendImplement(&this->acdEvtDis);
	//stateMachie.setscInstance(&DevModule::scInstance);
	stateMachie.Init(_stateMachieFile);
	stateMachie.setName(this->m_strExtensionNumber);

	return true;
}

void Extension::go(){
	stateMachie.go();
}

}
}
