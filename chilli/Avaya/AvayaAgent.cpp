#include "AvayaAgent.h"
#include "TSAPIModule.h"
#include <log4cplus/loggingmacros.h>
#include <json/json.h>
#include "AvayaAPI.h"

namespace chilli{
namespace Avaya{


AvayaAgent::AvayaAgent(TSAPIModule * model, const std::string &ext, const std::string &smFileName)
	:m_model(model), Agent(model, ext, smFileName)
{

}

AvayaAgent::~AvayaAgent(){

}

void AvayaAgent::fireSend(const std::string & strContent,const void * param)
{
	//LOG4CPLUS_DEBUG(log," recive a Send event from stateMachine:" << strContent);
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
		std::string typeName;

		if (jsonEvent["type"].isString()) {
			typeName = jsonEvent["type"].asString();
		}

		if (typeName != "cmd"){
			return;
		}

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
				event["AgentLogin"]["status"] = nRetCode;
				event["AgentLogin"]["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
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
				event["AgentLogout"]["status"] = nRetCode;
				event["AgentLogout"]["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
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
				event["AgentGetState"]["status"] = nRetCode;
				event["AgentGetState"]["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
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
				event["AgentSetFree"]["status"] = nRetCode;
				event["AgentSetFree"]["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
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
				event["AgentSetBusy"]["status"] = nRetCode;
				event["AgentSetBusy"]["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
				model::EventType_t evt(event.toStyledString());
				m_model->PushEvent(evt);
			}
			else {
				m_model->m_InvokeID2Extension[uInvodeId] = this->m_ExtNumber;
				m_model->m_InvokeID2Event[uInvodeId] = "AgentSetBusy";
			}
			bHandled = true;
		}
		else if (eventName == "ClearConnection")
		{
			ConnectionID_t connection;

			Json::Value jsonConnection = jsonEvent["param"]["connection"];
			if (jsonConnection["callID"].isInt())
				connection.callID = jsonConnection["callID"].asInt();

			if (jsonConnection["devIDType"].isString())
				connection.devIDType = AvayaAPI::cstaStringConnectionIDDevice(jsonConnection["devIDType"].asString());

			if (jsonConnection["deviceID"].isString())
				strncpy(connection.deviceID,jsonConnection["deviceID"].asCString(),sizeof(DeviceID_t));


			uint32_t uInvodeId = ++(m_model->m_ulInvokeID);
			RetCode_t nRetCode = AvayaAPI::cstaClearConnection(m_model->m_lAcsHandle,
				uInvodeId,
				&connection,
				NULL);

			if (nRetCode != ACSPOSITIVE_ACK) {
				LOG4CPLUS_ERROR(log, "cstaClearConnection:" << AvayaAPI::acsReturnCodeString(nRetCode));
				Json::Value event;
				event["extension"] = this->m_ExtNumber;
				event["event"] = "ClearConnection";
				event["ClearConnection"]["status"] = nRetCode;
				event["ClearConnection"]["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
				model::EventType_t evt(event.toStyledString());
				m_model->PushEvent(evt);
			}
			else {
				m_model->m_InvokeID2Extension[uInvodeId] = this->m_ExtNumber;
				m_model->m_InvokeID2Event[uInvodeId] = "ClearConnection";
			}
			bHandled = true;
		}
		else if (eventName == "ClearCall")
		{
			ConnectionID_t connection;

			Json::Value jsonConnection = jsonEvent["param"]["connection"];
			if (jsonConnection["callID"].isInt())
				connection.callID = jsonConnection["callID"].asInt();

			if (jsonConnection["devIDType"].isString())
				connection.devIDType = AvayaAPI::cstaStringConnectionIDDevice(jsonConnection["devIDType"].asString());

			if (jsonConnection["deviceID"].isString())
				strncpy(connection.deviceID, jsonConnection["deviceID"].asCString(),sizeof(DeviceID_t));


			uint32_t uInvodeId = ++(m_model->m_ulInvokeID);
			RetCode_t nRetCode = AvayaAPI::cstaClearCall(m_model->m_lAcsHandle,
				uInvodeId,
				&connection,
				NULL);

			if (nRetCode != ACSPOSITIVE_ACK) {
				LOG4CPLUS_ERROR(log, "cstaClearCall:" << AvayaAPI::acsReturnCodeString(nRetCode));
				Json::Value event;
				event["extension"] = this->m_ExtNumber;
				event["event"] = "ClearCall";
				event["ClearCall"]["status"] = nRetCode;
				event["ClearCall"]["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
				model::EventType_t evt(event.toStyledString());
				m_model->PushEvent(evt);
			}
			else {
				m_model->m_InvokeID2Extension[uInvodeId] = this->m_ExtNumber;
				m_model->m_InvokeID2Event[uInvodeId] = "ClearCall";
			}
			bHandled = true;
		}
		else if (eventName == "AnswerCall")
		{
			ConnectionID_t connection;

			Json::Value jsonConnection = jsonEvent["param"]["connection"];
			if (jsonConnection["callID"].isInt())
				connection.callID = jsonConnection["callID"].asInt();

			if (jsonConnection["devIDType"].isString())
				connection.devIDType = AvayaAPI::cstaStringConnectionIDDevice(jsonConnection["devIDType"].asString());

			if (jsonConnection["deviceID"].isString())
				strncpy(connection.deviceID, jsonConnection["deviceID"].asCString(),sizeof(DeviceID_t));


			uint32_t uInvodeId = ++(m_model->m_ulInvokeID);
			RetCode_t nRetCode = AvayaAPI::cstaAnswerCall(m_model->m_lAcsHandle,
				uInvodeId,
				&connection,
				NULL);

			if (nRetCode != ACSPOSITIVE_ACK) {
				LOG4CPLUS_ERROR(log, "cstaAnswerCall:" << AvayaAPI::acsReturnCodeString(nRetCode));
				Json::Value event;
				event["extension"] = this->m_ExtNumber;
				event["event"] = "AnswerCall";
				event["AnswerCall"]["status"] = nRetCode;
				event["AnswerCall"]["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
				model::EventType_t evt(event.toStyledString());
				m_model->PushEvent(evt);
			}
			else {
				m_model->m_InvokeID2Extension[uInvodeId] = this->m_ExtNumber;
				m_model->m_InvokeID2Event[uInvodeId] = "AnswerCall";
			}
			bHandled = true;
		}
		else if (eventName == "MakeCall")
		{
			DeviceID_t calling = "";
			DeviceID_t called = "";

			if (jsonEvent["param"]["calling"].isString())
				strncpy(calling, jsonEvent["param"]["calling"].asCString(), sizeof(calling));
			
			if (jsonEvent["param"]["called"].isString())
				strncpy(called, jsonEvent["param"]["called"].asCString(), sizeof(called));


			uint32_t uInvodeId = ++(m_model->m_ulInvokeID);
			RetCode_t nRetCode = AvayaAPI::cstaMakeCall(m_model->m_lAcsHandle,
				uInvodeId,
				&calling,
				&called,
				NULL);

			if (nRetCode != ACSPOSITIVE_ACK) {
				LOG4CPLUS_ERROR(log, "cstaMakeCall:" << AvayaAPI::acsReturnCodeString(nRetCode));
				Json::Value event;
				event["extension"] = this->m_ExtNumber;
				event["event"] = "MakeCall";
				event["MakeCall"]["status"] = nRetCode;
				event["MakeCall"]["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
				model::EventType_t evt(event.toStyledString());
				m_model->PushEvent(evt);
			}
			else {
				m_model->m_InvokeID2Extension[uInvodeId] = this->m_ExtNumber;
				m_model->m_InvokeID2Event[uInvodeId] = "MakeCall";
			}
			bHandled = true;
		}
		else if (eventName == "HoldCall")
		{
			ConnectionID_t connection;

			Json::Value jsonConnection = jsonEvent["param"]["connection"];
			if (jsonConnection["callID"].isInt())
				connection.callID = jsonConnection["callID"].asInt();

			if (jsonConnection["devIDType"].isString())
				connection.devIDType = AvayaAPI::cstaStringConnectionIDDevice(jsonConnection["devIDType"].asString());

			if (jsonConnection["deviceID"].isString())
				strncpy(connection.deviceID, jsonConnection["deviceID"].asCString(),sizeof(DeviceID_t));


			uint32_t uInvodeId = ++(m_model->m_ulInvokeID);
			RetCode_t nRetCode = AvayaAPI::cstaHoldCall(m_model->m_lAcsHandle,
				uInvodeId,
				&connection,
				false,
				NULL);

			if (nRetCode != ACSPOSITIVE_ACK) {
				LOG4CPLUS_ERROR(log, "cstaHoldCall:" << AvayaAPI::acsReturnCodeString(nRetCode));
				Json::Value event;
				event["extension"] = this->m_ExtNumber;
				event["event"] = "HoldCall";
				event["HoldCall"]["status"] = nRetCode;
				event["HoldCall"]["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
				model::EventType_t evt(event.toStyledString());
				m_model->PushEvent(evt);
			}
			else {
				m_model->m_InvokeID2Extension[uInvodeId] = this->m_ExtNumber;
				m_model->m_InvokeID2Event[uInvodeId] = "HoldCall";
			}
			bHandled = true;
		}
		else if (eventName == "RetrieveCall")
		{
			ConnectionID_t connection;

			Json::Value jsonConnection = jsonEvent["param"]["connection"];
			if (jsonConnection["callID"].isInt())
				connection.callID = jsonConnection["callID"].asInt();

			if (jsonConnection["devIDType"].isString())
				connection.devIDType = AvayaAPI::cstaStringConnectionIDDevice(jsonConnection["devIDType"].asString());

			if (jsonConnection["deviceID"].isString())
				strncpy(connection.deviceID, jsonConnection["deviceID"].asCString(),sizeof(DeviceID_t));


			uint32_t uInvodeId = ++(m_model->m_ulInvokeID);
			RetCode_t nRetCode = AvayaAPI::cstaRetrieveCall(m_model->m_lAcsHandle,
				uInvodeId,
				&connection,
				NULL);

			if (nRetCode != ACSPOSITIVE_ACK) {
				LOG4CPLUS_ERROR(log, "cstaRetrieveCall:" << AvayaAPI::acsReturnCodeString(nRetCode));
				Json::Value event;
				event["extension"] = this->m_ExtNumber;
				event["event"] = "RetrieveCall";
				event["RetrieveCall"]["status"] = nRetCode;
				event["RetrieveCall"]["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
				model::EventType_t evt(event.toStyledString());
				m_model->PushEvent(evt);
			}
			else {
				m_model->m_InvokeID2Extension[uInvodeId] = this->m_ExtNumber;
				m_model->m_InvokeID2Event[uInvodeId] = "RetrieveCall";
			}
			bHandled = true;
		}
		else if (eventName == "ConsultationCall")
		{
			ConnectionID_t connection;
			DeviceID_t called = "";

			Json::Value jsonConnection = jsonEvent["param"]["connection"];
			if (jsonConnection["callID"].isInt())
				connection.callID = jsonConnection["callID"].asInt();

			if (jsonConnection["devIDType"].isString())
				connection.devIDType = AvayaAPI::cstaStringConnectionIDDevice(jsonConnection["devIDType"].asString());

			if (jsonConnection["deviceID"].isString())
				strncpy(connection.deviceID, jsonConnection["deviceID"].asCString(), sizeof(DeviceID_t));

			if (jsonEvent["param"]["called"].isString())
				strncpy(called, jsonEvent["param"]["called"].asCString(), sizeof(DeviceID_t));

			uint32_t uInvodeId = ++(m_model->m_ulInvokeID);
			RetCode_t nRetCode = AvayaAPI::cstaConsultationCall(m_model->m_lAcsHandle,
				uInvodeId,
				&connection,
				&called,
				NULL);

			if (nRetCode != ACSPOSITIVE_ACK) {
				LOG4CPLUS_ERROR(log, "cstaConsultationCall:" << AvayaAPI::acsReturnCodeString(nRetCode));
				Json::Value event;
				event["extension"] = this->m_ExtNumber;
				event["event"] = "ConsultationCall";
				event["ConsultationCall"]["status"] = nRetCode;
				event["ConsultationCall"]["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
				model::EventType_t evt(event.toStyledString());
				m_model->PushEvent(evt);
			}
			else {
				m_model->m_InvokeID2Extension[uInvodeId] = this->m_ExtNumber;
				m_model->m_InvokeID2Event[uInvodeId] = "ConsultationCall";
			}
			bHandled = true;
		}
		else if (eventName == "ReconnectCall")
		{
			ConnectionID_t heldCall;
			ConnectionID_t activeCall;

			Json::Value jsonheldCall = jsonEvent["param"]["heldCall"];
			Json::Value jsonactiveCall = jsonEvent["param"]["activeCall"];

			if (jsonheldCall["callID"].isInt())
				heldCall.callID = jsonheldCall["callID"].asInt();

			if (jsonheldCall["devIDType"].isString())
				heldCall.devIDType = AvayaAPI::cstaStringConnectionIDDevice(jsonheldCall["devIDType"].asString());

			if (jsonheldCall["deviceID"].isString())
				strncpy(heldCall.deviceID, jsonheldCall["deviceID"].asCString(), sizeof(DeviceID_t));


			if (jsonactiveCall["callID"].isInt())
				activeCall.callID = jsonactiveCall["callID"].asInt();

			if (jsonactiveCall["devIDType"].isString())
				activeCall.devIDType = AvayaAPI::cstaStringConnectionIDDevice(jsonactiveCall["devIDType"].asString());

			if (jsonactiveCall["deviceID"].isString())
				strncpy(activeCall.deviceID, jsonactiveCall["deviceID"].asCString(), sizeof(DeviceID_t));

			uint32_t uInvodeId = ++(m_model->m_ulInvokeID);
			RetCode_t nRetCode = AvayaAPI::cstaReconnectCall(m_model->m_lAcsHandle,
				uInvodeId,
				&activeCall,
				&heldCall,
				NULL);

			if (nRetCode != ACSPOSITIVE_ACK) {
				LOG4CPLUS_ERROR(log, "cstaReconnectCall:" << AvayaAPI::acsReturnCodeString(nRetCode));
				Json::Value event;
				event["extension"] = this->m_ExtNumber;
				event["event"] = "ReconnectCall";
				event["ReconnectCall"]["status"] = nRetCode;
				event["ReconnectCall"]["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
				model::EventType_t evt(event.toStyledString());
				m_model->PushEvent(evt);
			}
			else {
				m_model->m_InvokeID2Extension[uInvodeId] = this->m_ExtNumber;
				m_model->m_InvokeID2Event[uInvodeId] = "ReconnectCall";
			}
			bHandled = true;
		}
		else if (eventName == "TransferCall")
		{
			ConnectionID_t heldCall;
			ConnectionID_t activeCall;

			Json::Value jsonheldCall = jsonEvent["param"]["heldCall"];
			Json::Value jsonactiveCall = jsonEvent["param"]["activeCall"];

			if (jsonheldCall["callID"].isInt())
				heldCall.callID = jsonheldCall["callID"].asInt();

			if (jsonheldCall["devIDType"].isString())
				heldCall.devIDType = AvayaAPI::cstaStringConnectionIDDevice(jsonheldCall["devIDType"].asString());

			if (jsonheldCall["deviceID"].isString())
				strncpy(heldCall.deviceID, jsonheldCall["deviceID"].asCString(), sizeof(DeviceID_t));


			if (jsonactiveCall["callID"].isInt())
				activeCall.callID = jsonactiveCall["callID"].asInt();

			if (jsonactiveCall["devIDType"].isString())
				activeCall.devIDType = AvayaAPI::cstaStringConnectionIDDevice(jsonactiveCall["devIDType"].asString());

			if (jsonactiveCall["deviceID"].isString())
				strncpy(activeCall.deviceID, jsonactiveCall["deviceID"].asCString(), sizeof(DeviceID_t));

			uint32_t uInvodeId = ++(m_model->m_ulInvokeID);
			RetCode_t nRetCode = AvayaAPI::cstaTransferCall(m_model->m_lAcsHandle,
				uInvodeId,
				&heldCall,
				&activeCall,
				NULL);

			if (nRetCode != ACSPOSITIVE_ACK) {
				LOG4CPLUS_ERROR(log, "cstaTransferCall:" << AvayaAPI::acsReturnCodeString(nRetCode));
				Json::Value event;
				event["extension"] = this->m_ExtNumber;
				event["event"] = "TransferCall";
				event["TransferCall"]["status"] = nRetCode;
				event["TransferCall"]["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
				model::EventType_t evt(event.toStyledString());
				m_model->PushEvent(evt);
			}
			else {
				m_model->m_InvokeID2Extension[uInvodeId] = this->m_ExtNumber;
				m_model->m_InvokeID2Event[uInvodeId] = "TransferCall";
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