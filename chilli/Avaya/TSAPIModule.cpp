#include "TSAPIModule.h"
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
		}

		// Destructor of TSAPIModule
		// Destroying the handle for the stream
		TSAPIModule::~TSAPIModule()
		{
			if (m_thread.joinable()) {
				Stop();
			}
		}

		int TSAPIModule::Start()
		{
			if (!m_thread.joinable()) {

				if (!InitAvayaAPI())
					return false;

				bool ret = OpenStream(m_ServiceID.c_str(), m_UserID.c_str(), m_Password.c_str());
				if (ret) {
					m_thread = std::thread(&TSAPIModule::run, this);
				}
				return ret;
			}
			else {
				LOG4CPLUS_WARN(log, "already running for this module.");
			}
			return true;
		}

		int TSAPIModule::Stop()
		{
			if (m_thread.joinable()) {
				UnInitAvayaAPI();

				bool ret = CloseStream();
				m_thread.join();
				return ret;
			}
			return true;
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

			//extensions 
			XMLElement * extensions = avaya->FirstChildElement("Extensions");
			if (extensions != nullptr) {

				for (XMLElement *child = extensions->FirstChildElement("Extension");
					child != nullptr;
					child = child->NextSiblingElement("Extension"))
				{
					const char * num = child->Attribute("ExtensionNumber");
					const char * sm = child->Attribute("StateMachine");
					num = num ? num : "";
					sm = sm ? sm : "";
					if (this->m_Extensions.find(num) == this->m_Extensions.end())
					{
						model::ExtensionPtr ext(new AvayaExtension(num, sm));
						this->m_Extensions[num] = ext;
					}
					else {
						LOG4CPLUS_ERROR(log, "alredy had extension:" << num);
					}
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
				, (InvokeID_t)m_ulInvokeID  // By default 1
				, ST_CSTA
				, (ServerID_t *)(serverID)  // AE Server Name
				, (LoginID_t *)(loginID)	// CTI LoginID
				, (Passwd_t *)(password)  // CTI LoginID password
				, (AppName_t *)"CCS-SERVER"
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
			usEventBufSize = sizeof(CSTAEvent_t);
			m_stPrivateData.length = ATT_MAX_PRIVATE_DATA;

			// Method for retrieving the entire response event structure

			while (true) {

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
					break;
				}

				// Check for event type.
				switch (cstaEvent.eventHeader.eventClass)
				{
				case ACSCONFIRMATION:
				{
					switch (cstaEvent.eventHeader.eventType)
					{
					case ACS_OPEN_STREAM_CONF:
					{
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
					}
					break;
					case ACS_CLOSE_STREAM_CONF:
					{
						LOG4CPLUS_INFO(log, "ACS_CLOSE_STREAM_CONF.");
						goto end;
					}
					break;
					case ACS_UNIVERSAL_FAILURE_CONF:
					{
						LOG4CPLUS_INFO(log, "ACS_UNIVERSAL_FAILURE_CONF:" << AvayaAPI::acsErrorString(cstaEvent.event.acsConfirmation.u.failureEvent.error));
					}
					break;
					default: {};
					};
				}// end of inner switch
				break;
				case CSTACONFIRMATION:
				{
					switch (cstaEvent.eventHeader.eventType)
					{
					case CSTA_GETAPI_CAPS_CONF:
					{
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
					case CSTA_QUERY_CALL_MONITOR_CONF:
					{
						LOG4CPLUS_INFO(log, "CSTA_QUERY_CALL_MONITOR_CONF:" << (int)cstaEvent.event.cstaConfirmation.u.queryCallMonitor.callMonitor);
					}
					break;
					default: {};
					}
				}// end of ctsaconfirmation
				break;
				case CSTAUNSOLICITED:
				{

				}// end of CSTAUNSOLICITED Events
				break;
				default: {}
				}// end of outer switch
			}
		end:
			LOG4CPLUS_INFO(log, "Stoped.");
			log4cplus::threadCleanup();
		}
	}
}













