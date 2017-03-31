#include "AvayaExtension.h"
#include "TSAPIModule.h"
#include <log4cplus/loggingmacros.h>
#include <scxml/TriggerEvent.h>
#include "AvayaAPI.h"

namespace chilli {
namespace Avaya {

	AvayaExtension::AvayaExtension(TSAPIModule * model, const std::string &ext, const std::string &smFileName)
		:m_model(model), ExtensionImp(model, ext, smFileName)
	{
		std::string logName = "AvayaExtension.";
		log = log4cplus::Logger::getInstance(logName.append(m_ExtNumber));
	}

	AvayaExtension::~AvayaExtension() {
	}

	void AvayaExtension::fireSend(const std::string &strContent, const void * param)
	{
		LOG4CPLUS_TRACE(log, " recive a Send event from stateMachine:" << strContent);
		bool bHandled = false;
		this->processSend(strContent, param, bHandled);
		if (!bHandled) {
			ExtensionImp::processSend(strContent, param, bHandled);
		}
	}

	void AvayaExtension::processSend(const std::string & strContent, const void * param, bool & bHandled)
	{

		Json::Value jsonEvent;
		Json::Reader jsonReader;
		if (jsonReader.parse(strContent, jsonEvent)) {
			std::string eventName;
			std::string typeName;

			if (jsonEvent["type"].isString()) {
				typeName = jsonEvent["type"].asString();
			}

			if (typeName != "cmd") {
				return;
			}

			if (jsonEvent["event"].isString()) {
				eventName = jsonEvent["event"].asString();
			}

			if (eventName == "MonitorDevice")
			{
				const char* deviceId = nullptr;

				if (jsonEvent["param"]["deviceId"].isString())
					deviceId = jsonEvent["param"]["deviceId"].asCString();

				CSTAMonitorFilter_t noFilter;
				noFilter.agent = 0;
				noFilter.call = 0;
				noFilter.maintenance = 0;

				uint32_t uInvodeId = ++(m_model->m_ulInvokeID);
				RetCode_t nRetCode = AvayaAPI::cstaMonitorDevice(m_model->m_lAcsHandle,
					uInvodeId,
					(DeviceID_t *)deviceId,
					&noFilter,
					NULL);

				if (nRetCode != ACSPOSITIVE_ACK) {
					LOG4CPLUS_ERROR(log, "cstaMonitorDevice:" << AvayaAPI::acsReturnCodeString(nRetCode));
					Json::Value event;
					event["extension"] = this->m_ExtNumber;
					event["event"] = "MonitorDevice";
					event["status"] = nRetCode;
					event["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
					model::EventType_t evt(event.toStyledString());
					m_model->PushEvent(evt);
				}
				else {
					m_model->m_InvokeID2Extension[uInvodeId] = this->m_ExtNumber;
					m_model->m_InvokeID2Event[uInvodeId] = "MonitorDevice";
				}
				bHandled = true;
			}
			else if (eventName == "MonitorStop")
			{
				CSTAMonitorCrossRefID_t monitorId = 0;

				if (jsonEvent["param"]["monitorId"].isInt())
					monitorId = jsonEvent["param"]["monitorId"].asInt();


				uint32_t uInvodeId = ++(m_model->m_ulInvokeID);
				RetCode_t nRetCode = AvayaAPI::cstaMonitorStop(m_model->m_lAcsHandle,
					uInvodeId,
					monitorId,
					NULL);

				if (nRetCode != ACSPOSITIVE_ACK) {
					LOG4CPLUS_ERROR(log, "cstaMonitorStop:" << AvayaAPI::acsReturnCodeString(nRetCode));
					Json::Value event;
					event["extension"] = this->m_ExtNumber;
					event["event"] = "MonitorStop";
					event["status"] = nRetCode;
					event["reason"] = AvayaAPI::acsReturnCodeString(nRetCode);
					model::EventType_t evt(event.toStyledString());
					m_model->PushEvent(evt);
				}
				else {
					m_model->m_InvokeID2Extension[uInvodeId] = this->m_ExtNumber;
					m_model->m_InvokeID2Event[uInvodeId] = "MonitorStop";
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