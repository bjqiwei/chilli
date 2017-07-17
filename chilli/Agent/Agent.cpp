#include "Agent.h"
#include <log4cplus/loggingmacros.h>
#include <json/json.h>
#include "../model/ConnectAdapter.h"
#include "../model/ProcessModule.h"

namespace chilli{
namespace Agent{


Agent::Agent(model::ProcessModule * model, const std::string &ext, const std::string &smFileName) 
	:Extension(model, ext, smFileName)
{
	std::string logName= "Agent.";
	log = log4cplus::Logger::getInstance(logName.append(m_ExtNumber));
	LOG4CPLUS_DEBUG(log,"new a Agent object.");
}

Agent::~Agent(){
	LOG4CPLUS_DEBUG(log,"destruction a Agent object.");
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

void Agent::processSend(const std::string & strContent, const void * param, bool & bHandled)
{
	Json::Value jsonData;
	Json::Reader jsonReader;
	if (jsonReader.parse(strContent, jsonData)) {
		if (jsonData["dest"].asString() == "client")
		{
			if (jsonData["type"].asString() == "response")
			{

				Json::FastWriter writer;
				std::string sendData = writer.write(jsonData["param"]);
				model::ConnectAdapter::Send(m_curConnectId, sendData.c_str(), sendData.length());

				if (jsonData["param"]["type"].isString() && jsonData["param"]["type"].asString() == "logon") {
					if (jsonData["param"]["status"].isInt() && jsonData["param"]["status"].asInt() == 0)
					{
						//登陆成功
						model::ConnectAdapter::SetExtension(m_ConnectId, "");//删除原有连接坐席号
						model::ConnectAdapter::Close(m_ConnectId); //关闭原有连接
						m_ConnectId = m_curConnectId;//更新为当前连接
						model::ConnectAdapter::SetExtension(m_ConnectId, this->getExtNumber());//为当前连接设置坐席工号
					}
					else {
						//登陆失败
						std::this_thread::sleep_for(std::chrono::milliseconds(1));
						//model::ConnectAdapter::Close(m_curConnectId);
					}
				}
				bHandled = true;
			}
			else if (jsonData["type"].asString() == "notify")
			{
				Json::FastWriter writer;
				std::string sendData = writer.write(jsonData["param"]);
				model::ConnectAdapter::Send(m_ConnectId, sendData.c_str(), sendData.length());
				bHandled = true;

				if (jsonData["param"]["type"].isString() && jsonData["param"]["type"].asString() == "kick") {
					//踢出坐席
					model::ConnectAdapter::SetExtension(m_ConnectId, "");//删除原有连接坐席号
				}
				
			}
		}
		else {
			jsonData["param"]["from"] = m_ExtNumber;
			jsonData["param"]["extension"] = jsonData["dest"];
			jsonData["param"]["event"] = jsonData["event"];
			jsonData["param"]["type"] = jsonData["type"];
			chilli::model::EventType_t  sendData(jsonData["param"]);
			this->m_model->PushEvent(sendData);
			bHandled = true;
		}
	}

	else {
		LOG4CPLUS_ERROR(log, strContent << " not json data.");
	}
}

void Agent::fireSend(const std::string & strContent,const void * param)
{
	LOG4CPLUS_TRACE(log, "fireSend:" << strContent);
	bool bHandled = false;
	processSend(strContent, param, bHandled);
}

int Agent::pushEvent(const model::EventType_t & Event)
{

	if (Event.connect != 0)
		this->m_curConnectId = Event.connect;

	return Extension::pushEvent(Event);
}

}
}