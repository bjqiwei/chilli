#include "ShExtension.h"
#include "ShDevModule.h"
#include <log4cplus/loggingmacros.h>


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
	//if(chilli::model::Extension::LoadConfig())
	//{
	//	//this->setType(helper::xml::getXmlNodeAttributesValue(m_xmlConfigNodePtr,"Type"));
	//	return true;
	//}
	return false;
}

bool ShExtension::setType(std::string strType)
{
	/*if (this->nType != ShDevModule::getDeviceTypeByName(strType))
	{
		LOG4CPLUS_ERROR(log,"the type set not match the device type:"<<strType << ",set UnEnable.");
		this->m_bEnable = false;
		return false;
	}*/
	LOG4CPLUS_DEBUG(log,"set type="<<strType);
	return true;
}
void ShExtension::setType(int _type)
{
	return ;
}

int ShExtension::getChannelID()
{
	return -1;
}



void ShExtension::fireSend(const std::string &strContent)
{
	LOG4CPLUS_TRACE(log," recive a Send event from stateMachine:" << strContent);
}


bool ShExtension::processTransfer(std::string strEvent,std::string from)
{
	//recEvtBuffer.addData(strEvent);
	return true;
}

bool ShExtension::addAcdEvent(const std::string& strEvent)
{
	//recEvtBuffer.addData(strEvent);
	return true;
}

int ShExtension::Answer()
{
	return SsmPickup(ch);
}
int ShExtension::PlayFile(std::string file)
{
	return SsmPlayFile(ch,file.c_str(),-1,0,0xFFFFFFFF);
}
int ShExtension::HangUp(){
	return SsmHangup(ch);
}
}
}
