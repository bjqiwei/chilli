#include "AvayaAgent.h"
#include "TSAPIModule.h"
#include <log4cplus/loggingmacros.h>
#include <json/json.h>
#include "AvayaAPI.h"

namespace chilli{
namespace Avaya{


AvayaAgent::AvayaAgent(TSAPIModule * model, const std::string &ext, const std::string &smFileName)
	:m_model(model), Agent(ext, smFileName)
{

}

AvayaAgent::~AvayaAgent(){

}

void AvayaAgent::fireSend(const std::string & strContent,const void * param)
{
	LOG4CPLUS_DEBUG(log," recive a Send event from stateMachine:" << strContent);
	bool bHandled = false;
	this->processSend(strContent, param, bHandled);
	if (!bHandled) {
		Agent::processSend(strContent, param, bHandled);
	}
	
}

void AvayaAgent::processSend(const std::string & strContent, const void * param, bool & bHandled)
{
	Json::Value jsonEvent;
	Json::Reader jsonReader;
	if (jsonReader.parse(strContent, jsonEvent)) {
		std::string eventName;

		if (jsonEvent["event"].isString()) {
			eventName = jsonEvent["event"].asString();
		}

		if (eventName == "AgentLogin")
		{
			const char* agentid = nullptr;
			const char* deviceId = nullptr;
			const char* password = nullptr;
			const char* group = nullptr;

			if (jsonEvent["param"]["agentId"].isString())
				agentid = jsonEvent["param"]["agentId"].asCString();

			if (jsonEvent["param"]["deviceId"].isString())
				deviceId = jsonEvent["param"]["deviceId"].asCString();

			if (jsonEvent["param"]["group"].isString())
				group = jsonEvent["param"]["group"].asCString();

			if (jsonEvent["param"]["password"].isString())
				password = jsonEvent["param"]["password"].asCString();


			uint32_t uInvodeId = ++(m_model->m_ulInvokeID);
			RetCode_t nRetCode = AvayaAPI::cstaSetAgentState(m_model->m_lAcsHandle,
				uInvodeId,
				(DeviceID_t *)deviceId,
				amLogIn,
				(AgentID_t *)agentid,
				(AgentGroup_t *)group,
				(AgentPassword_t *)password,
				NULL);
			if (nRetCode != ACSPOSITIVE_ACK) {
				LOG4CPLUS_ERROR(log, "cstaSetAgentState:" << AvayaAPI::acsReturnCodeString(nRetCode));
				Json::Value event;
				event["extension"] = this->m_ExtNumber;
				event["event"] = "AgentLogin";
				event["status"] = nRetCode;
				event["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
				model::EventType_t evt(event.toStyledString());
				m_model->PushEvent(evt);
			}
			else {
				m_model->m_InvokeID2Extension[uInvodeId] = this->m_ExtNumber;
				m_model->m_InvokeID2Event[uInvodeId] = "AgentLogin";
			}
			bHandled = true;
		}
		else if (eventName == "AgentLogout")
		{
			const char* agentid = nullptr;
			const char* deviceId = nullptr;
			const char* password = nullptr;
			const char* group = "";

			if (jsonEvent["param"]["agentId"].isString())
				agentid = jsonEvent["param"]["agentId"].asCString();

			if (jsonEvent["param"]["deviceId"].isString())
				deviceId = jsonEvent["param"]["deviceId"].asCString();

			if (jsonEvent["param"]["group"].isString())
				group = jsonEvent["param"]["group"].asCString();

			if (jsonEvent["param"]["password"].isString())
				password = jsonEvent["param"]["password"].asCString();


			uint32_t uInvodeId = ++(m_model->m_ulInvokeID);
			RetCode_t nRetCode = AvayaAPI::cstaSetAgentState(m_model->m_lAcsHandle,
				uInvodeId,
				(DeviceID_t *)deviceId,
				amLogOut,
				(AgentID_t *)agentid,
				(AgentGroup_t *)group,
				(AgentPassword_t *)password,
				NULL);
			if (nRetCode != ACSPOSITIVE_ACK) {
				LOG4CPLUS_ERROR(log, "cstaSetAgentState:" << AvayaAPI::acsReturnCodeString(nRetCode));
				Json::Value event;
				event["extension"] = this->m_ExtNumber;
				event["event"] = "AgentLogout";
				event["status"] = nRetCode;
				event["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
				model::EventType_t evt(event.toStyledString());
				m_model->PushEvent(evt);
			}
			else {
				m_model->m_InvokeID2Extension[uInvodeId] = this->m_ExtNumber;
				m_model->m_InvokeID2Event[uInvodeId] = "AgentLogout";
			}
			bHandled = true;
		}
		else if (eventName == "AgentGetState")
		{
			const char* deviceId = "";

			if (jsonEvent["param"]["deviceId"].isString())
				deviceId = jsonEvent["param"]["deviceId"].asCString();

			uint32_t uInvodeId = ++(m_model->m_ulInvokeID);
			RetCode_t nRetCode = AvayaAPI::cstaQueryAgentState(m_model->m_lAcsHandle,
				uInvodeId,
				(DeviceID_t *)deviceId,
				NULL);
			if (nRetCode != ACSPOSITIVE_ACK) {
				LOG4CPLUS_ERROR(log, "cstaQueryAgentState:" << AvayaAPI::acsReturnCodeString(nRetCode));
				Json::Value event;
				event["extension"] = this->m_ExtNumber;
				event["event"] = "AgentGetState";
				event["status"] = nRetCode;
				event["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
				model::EventType_t evt(event.toStyledString());
				m_model->PushEvent(evt);
			}
			else {
				m_model->m_InvokeID2Extension[uInvodeId] = this->m_ExtNumber;
				m_model->m_InvokeID2Event[uInvodeId] = "AgentGetState";
			}
			bHandled = true;
		}
		else if (eventName == "AgentSetFree")
		{
			const char* agentid = nullptr;
			const char* deviceId = nullptr;

			if (jsonEvent["param"]["agentId"].isString())
				agentid = jsonEvent["param"]["agentId"].asCString();

			if (jsonEvent["param"]["deviceId"].isString())
				deviceId = jsonEvent["param"]["deviceId"].asCString();


			uint32_t uInvodeId = ++(m_model->m_ulInvokeID);
			RetCode_t nRetCode = AvayaAPI::cstaSetAgentState(m_model->m_lAcsHandle,
				uInvodeId,
				(DeviceID_t *)deviceId,
				amReady,
				(AgentID_t *)agentid,
				(AgentGroup_t *)"",
				(AgentPassword_t *)"",
				NULL);

			if (nRetCode != ACSPOSITIVE_ACK) {
				LOG4CPLUS_ERROR(log, "cstaSetAgentState:" << AvayaAPI::acsReturnCodeString(nRetCode));
				Json::Value event;
				event["extension"] = this->m_ExtNumber;
				event["event"] = "AgentSetFree";
				event["status"] = nRetCode;
				event["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
				model::EventType_t evt(event.toStyledString());
				m_model->PushEvent(evt);
			}
			else {
				m_model->m_InvokeID2Extension[uInvodeId] = this->m_ExtNumber;
				m_model->m_InvokeID2Event[uInvodeId] = "AgentSetFree";
			}
			bHandled = true;
		}
		else if (eventName == "AgentSetBusy")
		{
			const char* agentid = nullptr;
			const char* deviceId = nullptr;

			if (jsonEvent["param"]["agentId"].isString())
				agentid = jsonEvent["param"]["agentId"].asCString();

			if (jsonEvent["param"]["deviceId"].isString())
				deviceId = jsonEvent["param"]["deviceId"].asCString();


			uint32_t uInvodeId = ++(m_model->m_ulInvokeID);
			RetCode_t nRetCode = AvayaAPI::cstaSetAgentState(m_model->m_lAcsHandle,
				uInvodeId,
				(DeviceID_t *)deviceId,
				amNotReady,
				(AgentID_t *)agentid,
				(AgentGroup_t *)"",
				(AgentPassword_t *)"",
				NULL);

			if (nRetCode != ACSPOSITIVE_ACK) {
				LOG4CPLUS_ERROR(log, "cstaSetAgentState:" << AvayaAPI::acsReturnCodeString(nRetCode));
				Json::Value event;
				event["extension"] = this->m_ExtNumber;
				event["event"] = "AgentSetBusy";
				event["status"] = nRetCode;
				event["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
				model::EventType_t evt(event.toStyledString());
				m_model->PushEvent(evt);
			}
			else {
				m_model->m_InvokeID2Extension[uInvodeId] = this->m_ExtNumber;
				m_model->m_InvokeID2Event[uInvodeId] = "AgentSetBusy";
			}
			bHandled = true;
		}
	}
	else {
		LOG4CPLUS_ERROR(log, strContent << " not json data.");
	}
}

}
}