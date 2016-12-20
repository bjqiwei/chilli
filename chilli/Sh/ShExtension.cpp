#include "ShExtension.h"
#include "ShAPI.h"
#include <log4cplus/loggingmacros.h>


namespace chilli{
namespace ShDev{

using namespace SHAPI;

ShExtension::ShExtension(const std::string &ext, const std::string &smFileName)
	:Extension(ext, smFileName), m_ExtNumber(ext)
{
	this->log = log4cplus::Logger::getInstance("chilli.ShDev.Extension");
	LOG4CPLUS_DEBUG(log,"new a extension object.");
}



ShExtension::~ShExtension(void)
{
	LOG4CPLUS_DEBUG(log,"destruction a extension object.");
}

const std::string & ShExtension::getExtensionNumber() const
{
	// TODO: insert return statement here
	return m_ExtNumber;
}

void ShExtension::setSessionId(const std::string & sessinId)
{
	m_SessionId = sessinId;
}

const std::string & ShExtension::getSessionId()
{
	// TODO: insert return statement here
	return m_SessionId;
}

int ShExtension::pushEvent(const std::string & evt)
{
	Json::Value jsonEvent;
	Json::Reader jsonReader;
	if (jsonReader.parse(evt, jsonEvent)) {
		std::string eventName;
		std::string _from;
		if (jsonEvent["event"].isString()) {
			eventName = jsonEvent["event"].asString();
		}

		if (jsonEvent["from"].isString()) {
			_from = jsonEvent["from"].asString();
		}


		fsm::TriggerEvent evt(eventName, _from);
		LOG4CPLUS_INFO(log, " Recived a event," << "from " << _from << "event=" << evt.ToString());
		m_SM->pushEvent(evt);

	}
	else {
		LOG4CPLUS_ERROR(log, __FUNCTION__ ",event:" << evt << " not json data.");
	}

	return 0;
}

bool ShExtension::setType(const std::string & strType)
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



void ShExtension::fireSend(const std::string &strContent, const void * param)
{
	LOG4CPLUS_TRACE(log," recive a Send event from stateMachine:" << strContent);
}


int ShExtension::Answer()
{
	return SsmPickup(ch);
}
int ShExtension::PlayFile(const std::string  & file)
{
	return SsmPlayFile(ch,file.c_str(),-1,0,0xFFFFFFFF);
}
int ShExtension::HangUp(){
	return SsmHangup(ch);
}
}
}
