#include "Agent.h"
#include <log4cplus/loggingmacros.h>
#include <json/json.h>
#include "../model/ConnectAdapter.h"

namespace chilli{
namespace Agent{


Agent::Agent(const std::string &ext, const std::string &smFileName) 
	:Extension(ext, smFileName), m_ExtNumber(ext)
{
	std::string logName= "Agent.";
	log = log4cplus::Logger::getInstance(logName.append(m_ExtNumber));
	LOG4CPLUS_DEBUG(log,"new a Agent object.");
}

Agent::~Agent(){
	LOG4CPLUS_DEBUG(log,"destruction a Agent object.");
}


const std::string & Agent::getExtensionNumber() const
{
	return m_ExtNumber;
}


void Agent::setSessionId(const std::string & sessinId)
{
	this->m_SessionId = sessinId;
}

const std::string & Agent::getSessionId()
{
	return this->m_SessionId;
}


int Agent::Answer()
{
	LOG4CPLUS_WARN(log, "not implement.");
	return 0;
}

int Agent::PlayFile(const std::string &fileName)
{
	LOG4CPLUS_WARN(log, "not implement.");
	return 0;
}

int Agent::HangUp()
{
	LOG4CPLUS_WARN(log, "not implement.");
	return 0;
}

void Agent::fireSend(const std::string & strContent,const void * param)
{
	LOG4CPLUS_DEBUG(log," recive a Send event from stateMachine:" << strContent);
	Json::Value jsonData;
	Json::Reader jsonReader;
	if (jsonReader.parse(strContent, jsonData)) {
		if (jsonData["type"].asString() == "response" && jsonData["dest"].asString() == "client")
		{
			Json::FastWriter writer;
			std::string sendData = writer.write(jsonData["param"]);
			model::ConnectAdapter::Send(m_curConnectId, sendData.c_str(), sendData.length());

			if (jsonData["param"]["type"].isString() && jsonData["param"]["type"].asString() == "logon") {
				if (jsonData["param"]["status"].isString() && jsonData["param"]["status"].asString() == "0")
				{
					//登陆成功
					model::ConnectAdapter::Close(m_ConnectId); //关闭原有连接
					m_ConnectId = m_curConnectId;//更新为当前连接
					model::ConnectAdapter::SetExtension(m_ConnectId, this->getExtensionNumber());//为当前连接设置坐席工号
				}
				else {
					//登陆失败
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
					model::ConnectAdapter::Close(m_curConnectId);
				}
			}
		}
		else if (jsonData["type"].asString() == "notify" && jsonData["dest"].asString() == "client")
		{
			Json::FastWriter writer;
			std::string sendData = writer.write(jsonData["param"]);
			model::ConnectAdapter::Send(m_ConnectId, sendData.c_str(), sendData.length());
		}
	}
	
	else {
		LOG4CPLUS_ERROR(log, strContent << " not json data.");
	}
}

int Agent::pushEvent(const model::EventType_t & Event)
{

	this->m_curConnectId = Event.connect;
	Json::Value jsonEvent;
	Json::Reader jsonReader;
	if (jsonReader.parse(Event.event, jsonEvent)){
		std::string eventName;

		if (jsonEvent["event"].isString()){
			eventName = jsonEvent["event"].asString();
		}

		fsm::TriggerEvent evt(eventName);

		for (auto & it : jsonEvent.getMemberNames()) {
			evt.addVars(it, jsonEvent[it]);
		}

		LOG4CPLUS_INFO(log, " Recived a event," << Event.event);
		m_SM->pushEvent(evt);

	}
	else{
		LOG4CPLUS_ERROR(log, ",event:" << Event.event << " not json data.");
	}

	return 0;
}

}
}