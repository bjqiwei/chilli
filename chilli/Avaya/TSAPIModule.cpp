#include "TSAPIModule.h"
#include "AvayaAgent.h"
#include "AvayaExtension.h"
#include <log4cplus/loggingmacros.h>
#include <memory>
#include "../tinyxml2/tinyxml2.h"

// TSAPIModule

namespace chilli {
	namespace Avaya {

		using namespace AvayaAPI;
		// Constructor of the TSAPIModule 
		TSAPIModule::TSAPIModule(const std::string & id):ProcessModule(id)
		{
			log = log4cplus::Logger::getInstance("chilli.TSAPIModule");
			LOG4CPLUS_DEBUG(log, "Constuction a module.");
		}

		// Destructor of TSAPIModule
		// Destroying the handle for the stream
		TSAPIModule::~TSAPIModule()
		{
			if (m_bRunning) {
				Stop();
			}

			for (auto & it : m_Extensions) {
				g_Extensions.erase(it.first);
			}

			LOG4CPLUS_DEBUG(log, "Destruction a module.");
		}

		int TSAPIModule::Start()
		{
			if (!m_bRunning) {
				m_bRunning = true;
				for (auto & it : m_Extensions) {
					it.second->Start();
				}

				if (!InitAvayaAPI())
					return -1;

				m_thread = std::thread(&TSAPIModule::run, this);
			}
			else {
				LOG4CPLUS_WARN(log, "already running for this module.");
			}
			return 0;
		}

		int TSAPIModule::Stop()
		{
			if (m_bRunning) {
				m_bRunning = false;
				for (auto & it : m_Extensions) {
					it.second->Stop();
				}

				if (m_thread.joinable()) {

					bool ret = CloseStream();
					m_thread.join();
					UnInitAvayaAPI();
					return ret;
				}
			}
			return 0;
		}

		bool TSAPIModule::LoadConfig(const std::string & configContext)
		{
			using namespace tinyxml2;
			tinyxml2::XMLDocument config;
			if (config.Parse(configContext.c_str()) != XMLError::XML_SUCCESS)
			{
				LOG4CPLUS_ERROR(log, "load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
				return false;
			}

			XMLElement * avaya = config.FirstChildElement("Avaya");
			// tsapi link
			XMLElement * tsapi = avaya->FirstChildElement("TSAPI");
			if (tsapi != nullptr) {
				XMLElement* LinkElement = tsapi->FirstChildElement("TLink");
				if (LinkElement != nullptr) {
					m_ServiceID = LinkElement->GetText() ? LinkElement->GetText() : "";
				}
				else {
					LOG4CPLUS_ERROR(log, "configure file not find TLink element in the TSAPI element.");
					return false;
				}

				XMLElement* UserIDElement = tsapi->FirstChildElement("UserID");
				if (UserIDElement != nullptr) {
					m_UserID = UserIDElement->GetText() ? UserIDElement->GetText() : "";
				}
				else {
					LOG4CPLUS_ERROR(log, "configure file not find UserID element in the TSAPI element.");
					return false;
				}
				XMLElement* PasswordElement = tsapi->FirstChildElement("Password");
				if (PasswordElement != nullptr) {
					m_Password = PasswordElement->GetText() ? PasswordElement->GetText() : "";
				}
				else {
					LOG4CPLUS_ERROR(log, "configure file not find Password element in the TSAPI element.");
					return false;
				}

			}
			// agents 
			XMLElement * agents = avaya->FirstChildElement("Agents");
			
			for (XMLElement *child = agents->FirstChildElement("Agent");
				child != nullptr;
				child = child->NextSiblingElement("Agent"))
			{

				const char * num = child->Attribute("ExtensionNumber");
				const char * sm = child->Attribute("StateMachine");
				const char * password = child->Attribute("password");
				const char * extension = child->Attribute("Extension");
				const char * avayaAgentId = child->Attribute("avayaAgentId");
				const char * avayaPassword = child->Attribute("avayaPassword");
				const char * avayaExtension = child->Attribute("avayaExtension");

				num = num ? num : "";
				sm = sm ? sm : "";
				password = password ? password : "";
				extension = extension ? extension : "";
				avayaAgentId = avayaAgentId ? avayaAgentId : "";
				avayaPassword = avayaPassword ? avayaPassword : "";
				avayaExtension = avayaExtension ? avayaExtension : "";

				if (this->g_Extensions.find(num) == this->g_Extensions.end())
				{
					model::ExtensionPtr ext(new AvayaAgent(this, num, sm));
					this->g_Extensions[num] = ext;
					this->m_Extensions[num] = ext;
					ext->setVar("_agent.AgentId", num);
					ext->setVar("_agent.Password", password);
					ext->setVar("_agent.Extension", extension);
					ext->setVar("_avaya.AgentId", avayaAgentId);
					ext->setVar("_avaya.Password", avayaPassword);
					ext->setVar("_avaya.Extension", avayaExtension);
				}
				else {
					LOG4CPLUS_ERROR(log, "alredy had agent:" << num);
				}
			}

			
			// extensions 
			XMLElement * extensions = avaya->FirstChildElement("Extensions");

			for (XMLElement *child = extensions->FirstChildElement("Extension");
				child != nullptr;
				child = child->NextSiblingElement("Extension"))
			{

				const char * num = child->Attribute("ExtensionNumber");
				const char * sm = child->Attribute("StateMachine");
				const char * avayaExtension = child->Attribute("avayaExtension");

				num = num ? num : "";
				sm = sm ? sm : "";
				avayaExtension = avayaExtension ? avayaExtension : "";

				if (this->g_Extensions.find(num) == this->g_Extensions.end())
				{
					model::ExtensionPtr ext(new AvayaExtension(this, num, sm));
					this->g_Extensions[num] = ext;
					this->m_Extensions[num] = ext;
					ext->setVar("_extension.Extension", num);
					ext->setVar("_avaya.Extension", avayaExtension);
				}
				else {
					LOG4CPLUS_ERROR(log, "alredy had agent:" << num);
				}
			}

			return true;
		}

		const model::ExtensionMap & TSAPIModule::GetExtension()
		{
			// TODO: insert return statement here
			return m_Extensions;
		}

		void TSAPIModule::fireSend(const std::string & strContent, const void * param)
		{
			LOG4CPLUS_DEBUG(log, strContent);
			LOG4CPLUS_WARN(log, "fireSend not implement.");
		}

		bool TSAPIModule::OpenStream(const char * serverID, const char * loginID, const char * password)
		{
			bool bResult = false;

			strcpy_s(m_stPrivateData.vendor, "VERSION");
			m_stPrivateData.data[0] = PRIVATE_DATA_ENCODING;

			if (AvayaAPI::attMakeVersionString("2-8", &(m_stPrivateData.data[1])) > 0)
			{
				m_stPrivateData.length = (unsigned short)strlen(&m_stPrivateData.data[1]) + 2;
			}
			else
			{
				m_stPrivateData.length = 0;
			}

			RetCode_t nRetCode = AvayaAPI::acsOpenStream(&m_lAcsHandle			// Handle for ACS Stream 
				, APP_GEN_ID			// APP_GEN_ID indicates Application generated invokeID's
				, m_ulInvokeID  // By default 1
				, ST_CSTA
				, (ServerID_t *)(serverID)  // AE Server Name
				, (LoginID_t *)(loginID)	// CTI LoginID
				, (Passwd_t *)(password)  // CTI LoginID password
				, (AppName_t *)"CHILLI-SERVER"
				, ACS_LEVEL1
				, (Version_t *) "TS1-2" // private Data version in use 8 in our case
				, 10
				, 5
				, 50
				, 5
				, (PrivateData_t *)&m_stPrivateData); // private Data.

			// no conf events are being processed yet, so don't wait for it yet...

			// set up event notification on this acs stream


			if (nRetCode < 0) {
				LOG4CPLUS_ERROR(log, "acsOpenStream:" << AvayaAPI::acsReturnCodeString(nRetCode));
				bResult = false;
			}
			else {
				bResult = true;
			}

			return (bResult);
		}// end of openStream function


		// Closind the ACS Stream
		// As invokeID is generated by Application.
		// invokeID used in this function is the last invokeID used for the application.
		bool TSAPIModule::CloseStream()
		{
			bool bReturnValue = false;
			// If acsCloseStream() method is used then we will get confirmation or failure event, 
			// however in this case we do not want to receive confirmation event as our application
			// is going to exit.
			RetCode_t nRetCode = AvayaAPI::acsCloseStream(m_lAcsHandle, ++m_ulInvokeID, NULL);


			// If acsAbortStream() method is used we will not receive confirmation or failure event,
			// which is appropriate in this case as our application is getting closed.
			//RetCode_t nRetCode = acsAbortStream(m_lAcsHandle, NULL);

			if (nRetCode < 0) {
				LOG4CPLUS_ERROR(log, "acsCloseStream:" << AvayaAPI::acsReturnCodeString(nRetCode));
			}
			else {
				bReturnValue = true;
			}
			return bReturnValue;
		}


		void TSAPIModule::run()
		{
			CSTAEvent_t cstaEvent; // CSTA event buffer required for reteriving the Event Structure
			unsigned short usEventBufSize; // CSTA event buffer size

			LOG4CPLUS_INFO(log, "Starting...");

			while (m_bRunning) {

				bool ret = OpenStream(m_ServiceID.c_str(), m_UserID.c_str(), m_Password.c_str());

				usEventBufSize = sizeof(CSTAEvent_t);
				m_stPrivateData.length = ATT_MAX_PRIVATE_DATA;

				while (m_bRunning) {
					// Method for retrieving the entire response event structure

					RetCode_t nRetCode = AvayaAPI::acsGetEventBlock(m_lAcsHandle, (void *)&cstaEvent, &usEventBufSize,
						(PrivateData_t *)&m_stPrivateData, NULL);

					// If there is error retriveing Event Structure 
					// further processing can not proceed, exit
					while (nRetCode == ACSERR_UBUFSMALL) {

						std::shared_ptr<char> EventPtr(new char[usEventBufSize]);
						nRetCode = AvayaAPI::acsGetEventBlock(m_lAcsHandle, EventPtr.get(), &usEventBufSize,
							(PrivateData_t *)&m_stPrivateData, NULL);

						memcpy(&cstaEvent, EventPtr.get(), sizeof(cstaEvent));
					}

					if (nRetCode < 0) {
						LOG4CPLUS_ERROR(log, "acsGetEventBlock:" << AvayaAPI::acsReturnCodeString(nRetCode));
						std::this_thread::sleep_for(std::chrono::seconds(1));
						break;
					}

					// Check for event type.
					switch (cstaEvent.eventHeader.eventClass)
					{
					case ACSCONFIRMATION: {
						switch (cstaEvent.eventHeader.eventType)
						{
						case ACS_OPEN_STREAM_CONF: {
							ServerID_t svrId;
							if (AvayaAPI::acsGetServerID(m_lAcsHandle, &svrId) == ACSPOSITIVE_ACK)
								LOG4CPLUS_INFO(log, "Open ServerID:" << svrId);

							LOG4CPLUS_INFO(log, "ACS_OPEN_STREAM_CONF.");
							LOG4CPLUS_INFO(log, "API Version:" << cstaEvent.event.acsConfirmation.u.acsopen.apiVer);
							LOG4CPLUS_INFO(log, "Lib Version:" << cstaEvent.event.acsConfirmation.u.acsopen.libVer);
							LOG4CPLUS_INFO(log, "Tsrv Version:" << cstaEvent.event.acsConfirmation.u.acsopen.tsrvVer);
							LOG4CPLUS_INFO(log, "Drv Version:" << cstaEvent.event.acsConfirmation.u.acsopen.drvrVer);

							AvayaAPI::cstaGetAPICaps(m_lAcsHandle, ++m_ulInvokeID);
							AvayaAPI::cstaQueryCallMonitor(m_lAcsHandle, ++m_ulInvokeID);
							AvayaAPI::cstaGetDeviceList(m_lAcsHandle, ++m_ulInvokeID, -1, CSTA_CALL_DEVICE_MONITOR);

							Json::Value event;
							event["event"] = "ACS_OPEN_STREAM_CONF";
							event["OpenStream"] = Json::objectValue;
							event["OpenStream"]["status"] = 0;
							model::EventType_t evt(event.toStyledString());
							for (auto &it: this->m_Extensions){
								it.second->pushEvent(evt);
							}
						}
												   break;
						case ACS_CLOSE_STREAM_CONF: {
							LOG4CPLUS_INFO(log, "ACS_CLOSE_STREAM_CONF.");
							goto end;
						}
													break;
						case ACS_UNIVERSAL_FAILURE_CONF: {
							LOG4CPLUS_INFO(log, "ACS_UNIVERSAL_FAILURE_CONF:" << AvayaAPI::acsErrorString(cstaEvent.event.acsConfirmation.u.failureEvent.error));
						}
														 break;
						default: {
							LOG4CPLUS_WARN(log, "Unknown ACSCONFIRMATION eventType:" << cstaEvent.eventHeader.eventType);
						}
								 break;
						}
					}// end of inner switch
										  break;
					case ACSUNSOLICITED: {
						switch (cstaEvent.eventHeader.eventType) {
						case ACS_UNIVERSAL_FAILURE: {
							LOG4CPLUS_INFO(log, "ACS_UNIVERSAL_FAILURE:" << AvayaAPI::acsErrorString(cstaEvent.event.acsUnsolicited.u.failureEvent.error));
						}
													break;
						default: {
							LOG4CPLUS_WARN(log, "Unknown ACSUNSOLICITED eventType:" << cstaEvent.eventHeader.eventType);
						}
								 break;
						}
					}
										 break;
					case CSTACONFIRMATION: {
						uint32_t invokeId = cstaEvent.event.cstaConfirmation.invokeID;
						switch (cstaEvent.eventHeader.eventType)
						{
						case CSTA_GETAPI_CAPS_CONF: {
							LOG4CPLUS_INFO(log, "CSTA_GETAPI_CAPS_CONF.");
							CSTAGetAPICapsConfEvent_t apiCaps = cstaEvent.event.cstaConfirmation.u.getAPICaps;
							for (uint32_t i = 0; i < sizeof(apiCaps) / sizeof(apiCaps.alternateCall); i++)
							{
								LOG4CPLUS_DEBUG(log, AvayaAPI::cstaAPICapsString(i) << ":"<< ((short *)&apiCaps)[i]);
							}
						}
													break;
						case CSTA_QUERY_CALL_MONITOR_CONF: {
							LOG4CPLUS_INFO(log, "CSTA_QUERY_CALL_MONITOR_CONF:" << (int)cstaEvent.event.cstaConfirmation.u.queryCallMonitor.callMonitor);
						}
														   break;
						case CSTA_GET_DEVICE_LIST_CONF: {
							LOG4CPLUS_DEBUG(log, "driverSdbLevel:" << cstaEvent.event.cstaConfirmation.u.getDeviceList.driverSdbLevel);
							short count = cstaEvent.event.cstaConfirmation.u.getDeviceList.devList.count;
							DeviceID_t * devices = cstaEvent.event.cstaConfirmation.u.getDeviceList.devList.device;
							for (int i = 0; i < count; i++) {
								LOG4CPLUS_DEBUG(log, devices[i]);
							}

						}
														break;
						case CSTA_ALTERNATE_CALL_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_ALTERNATE_CALL_CONF");
						}
													   break;
						case CSTA_ANSWER_CALL_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_ANSWER_CALL_CONF");
						}
													break;
						case CSTA_CALL_COMPLETION_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_CALL_COMPLETION_CONF");
						}
														break;
						case CSTA_CLEAR_CALL_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_CLEAR_CALL_CONF");
						}
												   break;
						case CSTA_CLEAR_CONNECTION_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_CLEAR_CONNECTION_CONF");
						}
														 break;
						case CSTA_CONFERENCE_CALL_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_CONFERENCE_CALL_CONF:");
							ConnectionID_t newCall = cstaEvent.event.cstaConfirmation.u.conferenceCall.newCall;
							LOG4CPLUS_DEBUG(log, "newCall:" << newCall.callID
								<< "," << newCall.deviceID << "," << newCall.devIDType);
							ConnectionList_t connList = cstaEvent.event.cstaConfirmation.u.conferenceCall.connList;
							for (int i = 0; i < connList.count; i++) {
								ConnectionID_t party = connList.connection[i].party;
								LOG4CPLUS_DEBUG(log, "party[" << i << "]:" << party.callID
									<< "," << party.deviceID << "," << party.devIDType);
							}
						}
														break;
						case CSTA_CONSULTATION_CALL_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_CONSULTATION_CALL_CONF:");
							ConnectionID_t newCall = cstaEvent.event.cstaConfirmation.u.consultationCall.newCall;
							LOG4CPLUS_DEBUG(log, "newCall:" << newCall.callID
								<< "," << newCall.deviceID << "," << newCall.devIDType);
						}
														  break;
						case CSTA_DEFLECT_CALL_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_DEFLECT_CALL_CONF");
						}
													 break;
						case CSTA_GROUP_PICKUP_CALL_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_GROUP_PICKUP_CALL_CONF");
						}
														  break;
						case CSTA_HOLD_CALL_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_HOLD_CALL_CONF");
						}
												  break;
						case CSTA_MAKE_CALL_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_MAKE_CALL_CONF:");
							ConnectionID_t newCall = cstaEvent.event.cstaConfirmation.u.makeCall.newCall;
							LOG4CPLUS_DEBUG(log, "newCall:" << newCall.callID
								<< "," << newCall.deviceID << "," << newCall.devIDType);
						}
												  break;
						case CSTA_MAKE_PREDICTIVE_CALL_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_MAKE_PREDICTIVE_CALL_CONF:");
							ConnectionID_t newCall = cstaEvent.event.cstaConfirmation.u.makePredictiveCall.newCall;
							LOG4CPLUS_DEBUG(log, "newCall:" << newCall.callID
								<< "," << newCall.deviceID << "," << newCall.devIDType);
						}
															 break;
						case CSTA_PICKUP_CALL_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_PICKUP_CALL_CONF");
						}
													break;
						case CSTA_RECONNECT_CALL_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_RECONNECT_CALL_CONF");
						}
													   break;
						case CSTA_RETRIEVE_CALL_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_RETRIEVE_CALL_CONF");
						}
													  break;
						case CSTA_TRANSFER_CALL_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_TRANSFER_CALL_CONF");
							ConnectionID_t newCall = cstaEvent.event.cstaConfirmation.u.transferCall.newCall;
							LOG4CPLUS_DEBUG(log, "newCall:" << newCall.callID
								<< "," << newCall.deviceID << "," << newCall.devIDType);
							ConnectionList_t connList = cstaEvent.event.cstaConfirmation.u.transferCall.connList;
							for (int i = 0; i < connList.count; i++) {
								ConnectionID_t party = connList.connection[i].party;
								LOG4CPLUS_DEBUG(log, "party[" << i << "]:" << party.callID
									<< "," << party.deviceID << "," << party.devIDType);
							}
						}
													  break;
						case CSTA_SET_MWI_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_SET_MWI_CONF");
						}
												break;
						case CSTA_SET_DND_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_SET_DND_CONF");
						}
												break;
						case CSTA_SET_FWD_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_SET_FWD_CONF");
						}
												break;
						case CSTA_SET_AGENT_STATE_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_SET_AGENT_STATE_CONF");
							Json::Value event;
							event["extension"] = this->m_InvokeID2Extension[invokeId];
							std::string eventName = this->m_InvokeID2Event[invokeId];
							event["event"] = eventName;
							event[eventName] = Json::objectValue;
							event[eventName]["status"] = 0;
							model::EventType_t evt(event.toStyledString());
							this->PushEvent(evt);
						}
														break;
						case CSTA_QUERY_MWI_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_QUERY_MWI_CONF:");
							LOG4CPLUS_DEBUG(log, "messages:" << (bool)cstaEvent.event.cstaConfirmation.u.queryMwi.messages);
						}
												  break;
						case CSTA_QUERY_DND_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_QUERY_DND_CONF");
							LOG4CPLUS_DEBUG(log, "doNotDisturb:" << (bool)cstaEvent.event.cstaConfirmation.u.queryDnd.doNotDisturb);
						}
												  break;
						case CSTA_QUERY_FWD_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_QUERY_FWD_CONF");
							CSTAQueryFwdConfEvent_t queryFwd = cstaEvent.event.cstaConfirmation.u.queryFwd;
							ListForwardParameters_t forward = queryFwd.forward;
							for (int i = 0; i < forward.count; i++) {
								LOG4CPLUS_DEBUG(log, "fwd[" << i << "]:" << forward.param[i].forwardingType
									<< "," << forward.param[i].forwardingOn
									<< "," << forward.param[i].forwardDN);
							}
						}
												  break;
						case CSTA_QUERY_AGENT_STATE_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_QUERY_AGENT_STATE_CONF:");
							AgentState_t agentState = cstaEvent.event.cstaConfirmation.u.queryAgentState.agentState;
							LOG4CPLUS_DEBUG(log, "agentState:" << AvayaAPI::cstaAgentStateString(agentState));
							Json::Value event;
							event["extension"] = this->m_InvokeID2Extension[invokeId];
							std::string eventName = this->m_InvokeID2Event[invokeId];
							event["event"] = eventName;
							event[eventName] = Json::objectValue;
							event[eventName]["agentState"] = AvayaAPI::cstaAgentStateString(agentState);
							model::EventType_t evt(event.toStyledString());
							this->PushEvent(evt);
						}
														  break;
						case CSTA_QUERY_LAST_NUMBER_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_QUERY_LAST_NUMBER_CONF:");
							LOG4CPLUS_DEBUG(log, "lastNumber:" << cstaEvent.event.cstaConfirmation.u.queryLastNumber.lastNumber);
						}
														  break;
						case CSTA_QUERY_DEVICE_INFO_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_QUERY_DEVICE_INFO_CONF:");
							CSTAQueryDeviceInfoConfEvent_t queryDeviceInfo = cstaEvent.event.cstaConfirmation.u.queryDeviceInfo;
							LOG4CPLUS_DEBUG(log, "queryDeviceInfo,device:" << queryDeviceInfo.device << ",deviceClass:" << queryDeviceInfo.deviceClass << ",deviceType:" << queryDeviceInfo.deviceType);
						}
														  break;
						case CSTA_UNIVERSAL_FAILURE_CONF: {
							CSTAUniversalFailure_t error = cstaEvent.event.cstaConfirmation.u.universalFailure.error;
							LOG4CPLUS_WARN(log, "CSTA_UNIVERSAL_FAILURE_CONF:" << AvayaAPI::cstaErrorString(error));
							Json::Value event;
							event["extension"] = this->m_InvokeID2Extension[invokeId];
							std::string eventName = this->m_InvokeID2Event[invokeId];
							event["event"] = eventName;
							event[eventName]["status"] = error;
							event[eventName]["reason"] = AvayaAPI::cstaErrorString(error);
							model::EventType_t evt(event.toStyledString());
							this->PushEvent(evt);
						}
														  break;
						case CSTA_MONITOR_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_MONITOR_CONF");
							CSTAMonitorCrossRefID_t monitorId = cstaEvent.event.cstaConfirmation.u.monitorStart.monitorCrossRefID;

							this->m_monitorID2Extension[monitorId] = this->m_InvokeID2Extension[invokeId];

							Json::Value event;
							event["extension"] = this->m_InvokeID2Extension[invokeId];
							std::string eventName = this->m_InvokeID2Event[invokeId];
							event["event"] = eventName;
							event[eventName]["status"] = 0;
							event[eventName]["monitorId"] = monitorId;
							model::EventType_t evt(event.toStyledString());
							this->PushEvent(evt);
						}
								  break;
						case CSTA_MONITOR_STOP_CONF: {
							LOG4CPLUS_DEBUG(log, "CSTA_MONITOR_STOP_CONF");
							Json::Value event;
							event["extension"] = this->m_InvokeID2Extension[invokeId];
							std::string eventName = this->m_InvokeID2Event[invokeId];
							event["event"] = eventName;
							event[eventName]["status"] = 0;
							model::EventType_t evt(event.toStyledString());
							this->PushEvent(evt);
						}
													 break;
						default: {
							LOG4CPLUS_WARN(log, "Unknown CSTACONFIRMATION eventType:" << cstaEvent.eventHeader.eventType);
						}
								 break;
						}
						m_InvokeID2Event.erase(invokeId);
						m_InvokeID2Extension.erase(invokeId);
					}// end of ctsaconfirmation
										   break;
					case CSTAUNSOLICITED: {
						switch (cstaEvent.eventHeader.eventType) {
						case CSTA_MONITOR_ENDED: {
							CSTAMonitorCrossRefID_t monitorId = cstaEvent.event.cstaUnsolicited.monitorCrossRefId;
							CSTAEventCause_t cause = cstaEvent.event.cstaUnsolicited.u.monitorEnded.cause;
							LOG4CPLUS_DEBUG(log, "CSTA_MONITOR_ENDED" );
							Json::Value event;
							event["extension"] = this->m_monitorID2Extension[monitorId];
							event["monitorId"] = monitorId;
							event["event"] = "MONITOR_ENDED";
							event["MONITOR_ENDED"]["cause"] = cause;
							model::EventType_t evt(event.toStyledString());
							this->PushEvent(evt);
							this->m_monitorID2Extension.erase(monitorId);

						}
												 break;
						case CSTA_CALL_CLEARED: {
							LOG4CPLUS_WARN(log, "CSTA_CALL_CLEARED");
						}
												break;
						case CSTA_CONNECTION_CLEARED: {
							LOG4CPLUS_DEBUG(log, "CSTA_CONNECTION_CLEARED");

							CSTAMonitorCrossRefID_t monitorId = cstaEvent.event.cstaUnsolicited.monitorCrossRefId;
							CSTAConnectionClearedEvent_t	connectionCleared = cstaEvent.event.cstaUnsolicited.u.connectionCleared;
	
							Json::Value event;
							event["extension"] = this->m_monitorID2Extension[monitorId];
							event["monitorId"] = monitorId;
							event["event"] = "CONNECTION_CLEARED";
							event["connectionCleared"]["localConnect"] = AvayaAPI::cstaLocalConnectionStateString(connectionCleared.localConnectionInfo);
							event["connectionCleared"]["connection"] = AvayaAPI::cstaConnectionIDJson(connectionCleared.droppedConnection);
							event["connectionCleared"]["cause"] = AvayaAPI::cstaEventCauseString(connectionCleared.cause);


							model::EventType_t evt(event.toStyledString());
							this->PushEvent(evt);
						}
													  break;
						case CSTA_DELIVERED: {
							LOG4CPLUS_DEBUG(log, "CSTA_DELIVERED");

							CSTAMonitorCrossRefID_t monitorId = cstaEvent.event.cstaUnsolicited.monitorCrossRefId;
							
							const char *called = cstaEvent.event.cstaUnsolicited.u.delivered.calledDevice.deviceID;
							const char *calling = cstaEvent.event.cstaUnsolicited.u.delivered.callingDevice.deviceID;
							const char *alerting = cstaEvent.event.cstaUnsolicited.u.delivered.alertingDevice.deviceID;
							LocalConnectionState_t localConnect = cstaEvent.event.cstaUnsolicited.u.delivered.localConnectionInfo;

							ConnectionID_t connection = cstaEvent.event.cstaUnsolicited.u.delivered.connection;

							Json::Value event;
							event["extension"] = this->m_monitorID2Extension[monitorId];
							event["monitorId"] = monitorId;
							event["event"] = "DELIVERED";
							event["delivered"]["called"] = called;
							event["delivered"]["alerting"] = alerting;
							event["delivered"]["calling"] = calling;
							event["delivered"]["localConnect"] = AvayaAPI::cstaLocalConnectionStateString(localConnect);

							event["delivered"]["connection"] = AvayaAPI::cstaConnectionIDJson(connection);

							model::EventType_t evt(event.toStyledString());
							this->PushEvent(evt);

						}
													  break;
						case CSTA_ESTABLISHED: {
							LOG4CPLUS_DEBUG(log, "CSTA_ESTABLISHED");

							CSTAMonitorCrossRefID_t monitorId = cstaEvent.event.cstaUnsolicited.monitorCrossRefId;
							const char *called = cstaEvent.event.cstaUnsolicited.u.established.calledDevice.deviceID;
							const char *answering = cstaEvent.event.cstaUnsolicited.u.established.answeringDevice.deviceID;
							const char *calling = cstaEvent.event.cstaUnsolicited.u.established.callingDevice.deviceID;
							CSTAEventCause_t cause = cstaEvent.event.cstaUnsolicited.u.established.cause;
							ConnectionID_t connection = cstaEvent.event.cstaUnsolicited.u.established.establishedConnection;

							LocalConnectionState_t localConnect = cstaEvent.event.cstaUnsolicited.u.established.localConnectionInfo;

							Json::Value event;
							event["extension"] = this->m_monitorID2Extension[monitorId];
							event["monitorId"] = monitorId;
							event["event"] = "ESTABLISHED";
							event["established"]["localConnect"] = AvayaAPI::cstaLocalConnectionStateString(localConnect);
							event["established"]["connection"] = AvayaAPI::cstaConnectionIDJson(connection);
							event["established"]["cause"] = AvayaAPI::cstaEventCauseString(cause);
							event["established"]["calling"] = calling;
							event["established"]["called"] = called;
							event["established"]["answering"] = answering;

							model::EventType_t evt(event.toStyledString());
							this->PushEvent(evt);

						}
											   break;
						default: {
							LOG4CPLUS_WARN(log, "Unknown CSTAUNSOLICITED eventType:" << cstaEvent.eventHeader.eventType);
						}
								 break;
						}
					}// end of CSTAUNSOLICITED Events
										  break;
					default: {
						LOG4CPLUS_WARN(log, "Unknown eventClass:" << cstaEvent.eventHeader.eventClass);
					}
							 break;
					}// end of outer switch
				}
			}
		end:
			LOG4CPLUS_INFO(log, "Stoped.");
			log4cplus::threadCleanup();
		}
	}
}













