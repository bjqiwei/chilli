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
				const char * avayaAgentId = child->Attribute("avayaAgentId");
				const char * avayaPassword = child->Attribute("avayaPassword");
				const char * avayaExtension = child->Attribute("avayaExtension");

				num = num ? num : "";
				sm = sm ? sm : "";
				password = password ? password : "";
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
							AvayaAPI::cstaGetDeviceList(m_lAcsHandle, ++m_ulInvokeID, -1, CSTA_DEVICE_DEVICE_MONITOR);

							Json::Value event;
							event["event"] = "ACS_OPEN_STREAM_CONF";
							event["status"] = 0;
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
							LOG4CPLUS_INFO(log, "alternateCall:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.alternateCall);
							LOG4CPLUS_INFO(log, "answerCall:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.answerCall);
							LOG4CPLUS_INFO(log, "callCompletion:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.callCompletion);
							LOG4CPLUS_INFO(log, "clearCall:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.clearCall);
							LOG4CPLUS_INFO(log, "clearConnection:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.clearConnection);
							LOG4CPLUS_INFO(log, "conferenceCall:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.conferenceCall);
							LOG4CPLUS_INFO(log, "consultationCall:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.consultationCall);
							LOG4CPLUS_INFO(log, "deflectCall:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.deflectCall);
							LOG4CPLUS_INFO(log, "pickupCall:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.pickupCall);
							LOG4CPLUS_INFO(log, "groupPickupCall:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.groupPickupCall);
							LOG4CPLUS_INFO(log, "holdCall:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.holdCall);
							LOG4CPLUS_INFO(log, "makeCall:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.makeCall);
							LOG4CPLUS_INFO(log, "makePredictiveCall:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.makePredictiveCall);
							LOG4CPLUS_INFO(log, "queryMwi:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.queryMwi);
							LOG4CPLUS_INFO(log, "queryDnd:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.queryDnd);
							LOG4CPLUS_INFO(log, "queryFwd:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.queryFwd);
							LOG4CPLUS_INFO(log, "queryAgentState:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.queryAgentState);
							LOG4CPLUS_INFO(log, "queryLastNumber:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.queryLastNumber);
							LOG4CPLUS_INFO(log, "queryDeviceInfo:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.queryDeviceInfo);
							LOG4CPLUS_INFO(log, "reconnectCall:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.reconnectCall);
							LOG4CPLUS_INFO(log, "retrieveCall:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.retrieveCall);
							LOG4CPLUS_INFO(log, "setMwi:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.setMwi);
							LOG4CPLUS_INFO(log, "setDnd:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.setDnd);
							LOG4CPLUS_INFO(log, "setFwd:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.setFwd);
							LOG4CPLUS_INFO(log, "setAgentState:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.setAgentState);
							LOG4CPLUS_INFO(log, "transferCall:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.transferCall);
							LOG4CPLUS_INFO(log, "eventReport:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.eventReport);
							LOG4CPLUS_INFO(log, "callClearedEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.callClearedEvent);
							LOG4CPLUS_INFO(log, "conferencedEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.conferencedEvent);
							LOG4CPLUS_INFO(log, "connectionClearedEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.connectionClearedEvent);
							LOG4CPLUS_INFO(log, "deliveredEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.deliveredEvent);
							LOG4CPLUS_INFO(log, "divertedEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.divertedEvent);
							LOG4CPLUS_INFO(log, "establishedEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.establishedEvent);
							LOG4CPLUS_INFO(log, "failedEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.failedEvent);
							LOG4CPLUS_INFO(log, "heldEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.heldEvent);
							LOG4CPLUS_INFO(log, "networkReachedEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.networkReachedEvent);
							LOG4CPLUS_INFO(log, "originatedEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.originatedEvent);
							LOG4CPLUS_INFO(log, "queuedEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.queuedEvent);
							LOG4CPLUS_INFO(log, "retrievedEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.retrievedEvent);
							LOG4CPLUS_INFO(log, "serviceInitiatedEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.serviceInitiatedEvent);
							LOG4CPLUS_INFO(log, "transferredEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.transferredEvent);
							LOG4CPLUS_INFO(log, "callInformationEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.callInformationEvent);
							LOG4CPLUS_INFO(log, "doNotDisturbEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.doNotDisturbEvent);
							LOG4CPLUS_INFO(log, "forwardingEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.forwardingEvent);
							LOG4CPLUS_INFO(log, "messageWaitingEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.messageWaitingEvent);
							LOG4CPLUS_INFO(log, "loggedOnEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.loggedOnEvent);
							LOG4CPLUS_INFO(log, "loggedOffEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.loggedOffEvent);
							LOG4CPLUS_INFO(log, "notReadyEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.notReadyEvent);
							LOG4CPLUS_INFO(log, "readyEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.readyEvent);
							LOG4CPLUS_INFO(log, "workNotReadyEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.workNotReadyEvent);
							LOG4CPLUS_INFO(log, "workReadyEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.workReadyEvent);
							LOG4CPLUS_INFO(log, "backInServiceEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.backInServiceEvent);
							LOG4CPLUS_INFO(log, "outOfServiceEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.outOfServiceEvent);
							LOG4CPLUS_INFO(log, "privateEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.privateEvent);
							LOG4CPLUS_INFO(log, "routeRequestEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.routeRequestEvent);
							LOG4CPLUS_INFO(log, "reRoute:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.reRoute);
							LOG4CPLUS_INFO(log, "routeSelect:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.routeSelect);
							LOG4CPLUS_INFO(log, "routeUsedEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.routeUsedEvent);
							LOG4CPLUS_INFO(log, "routeEndEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.routeEndEvent);
							LOG4CPLUS_INFO(log, "monitorDevice:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.monitorDevice);
							LOG4CPLUS_INFO(log, "monitorCall:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.monitorCall);
							LOG4CPLUS_INFO(log, "monitorCallsViaDevice:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.monitorCallsViaDevice);
							LOG4CPLUS_INFO(log, "changeMonitorFilter:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.changeMonitorFilter);
							LOG4CPLUS_INFO(log, "monitorStop:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.monitorStop);
							LOG4CPLUS_INFO(log, "monitorEnded:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.monitorEnded);
							LOG4CPLUS_INFO(log, "snapshotDeviceReq:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.snapshotDeviceReq);
							LOG4CPLUS_INFO(log, "snapshotCallReq:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.snapshotCallReq);
							LOG4CPLUS_INFO(log, "escapeService:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.escapeService);
							LOG4CPLUS_INFO(log, "privateStatusEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.privateStatusEvent);
							LOG4CPLUS_INFO(log, "escapeServiceEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.escapeServiceEvent);
							LOG4CPLUS_INFO(log, "escapeServiceConf:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.escapeServiceConf);
							LOG4CPLUS_INFO(log, "sendPrivateEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.sendPrivateEvent);
							LOG4CPLUS_INFO(log, "sysStatReq:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.sysStatReq);
							LOG4CPLUS_INFO(log, "sysStatStart:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.sysStatStart);
							LOG4CPLUS_INFO(log, "sysStatStop:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.sysStatStop);
							LOG4CPLUS_INFO(log, "changeSysStatFilter:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.changeSysStatFilter);
							LOG4CPLUS_INFO(log, "sysStatReqEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.sysStatReqEvent);
							LOG4CPLUS_INFO(log, "sysStatReqConf:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.sysStatReqConf);
							LOG4CPLUS_INFO(log, "sysStatEvent:" << cstaEvent.event.cstaConfirmation.u.getAPICaps.sysStatEvent);
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
							event["event"] = this->m_InvokeID2Event[invokeId];
							event["status"] = 0;
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
							LOG4CPLUS_DEBUG(log, "agentState:" << agentState);
							Json::Value event;
							event["extension"] = this->m_InvokeID2Extension[invokeId];
							event["event"] = this->m_InvokeID2Event[invokeId];
							event["status"] = agentState;
							event["agentState"] = AvayaAPI::cstaAgentStateString(agentState);
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
							event["event"] = this->m_InvokeID2Event[invokeId];
							event["status"] = error;
							event["reason"] = AvayaAPI::cstaErrorString(error);
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













