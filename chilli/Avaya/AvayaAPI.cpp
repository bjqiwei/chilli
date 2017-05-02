#include "AvayaAPI.h"
#include <atomic>
#include "../Dynamiclibrary.h"


namespace AvayaAPI {
	static std::atomic_ulong  g_Reference = 0;

	Proc_acsOpenStream acsOpenStream = nullptr;
	Proc_acsCloseStream acsCloseStream = nullptr;
	Proc_acsAbortStream acsAbortStream = nullptr;
	Proc_acsFlushEventQueue acsFlushEventQueue = nullptr;
	Proc_acsGetEventPoll acsGetEventPoll = nullptr;
	Proc_acsGetEventBlock acsGetEventBlock = nullptr;
#if defined ( TSLIB_WINDOWS_32 )
	Proc_acsEventNotify acsEventNotify = nullptr;
	Proc_acsSetESR acsSetESR = nullptr;
#elif defined ( TSLIB_LINUX )
	Proc_acsGetFile acsGetFile = nullptr;
#endif
	Proc_acsEnumServerNames acsEnumServerNames = nullptr;
	Proc_acsQueryAuthInfo acsQueryAuthInfo = nullptr;
	Proc_acsGetServerID acsGetServerID = nullptr;
	Proc_acsSetHeartbeatInterval acsSetHeartbeatInterval = nullptr;
	Proc_acsReturnCodeString acsReturnCodeString = nullptr;
	Proc_acsReturnCodeVerboseString acsReturnCodeVerboseString = nullptr;
	Proc_acsErrorString acsErrorString = nullptr;
	Proc_cstaErrorString cstaErrorString = nullptr;
	Proc_cstaAlternateCall cstaAlternateCall = nullptr;
	Proc_cstaAnswerCall cstaAnswerCall = nullptr;
	Proc_cstaCallCompletion cstaCallCompletion = nullptr;
	Proc_cstaClearCall cstaClearCall = nullptr;
	Proc_cstaClearConnection cstaClearConnection = nullptr;
	Proc_cstaConferenceCall cstaConferenceCall = nullptr;
	Proc_cstaConsultationCall cstaConsultationCall = nullptr;
	Proc_cstaDeflectCall cstaDeflectCall = nullptr;
	Proc_cstaGroupPickupCall cstaGroupPickupCall = nullptr;
	Proc_cstaHoldCall cstaHoldCall = nullptr;
	Proc_cstaMakeCall cstaMakeCall = nullptr;
	Proc_cstaMakePredictiveCall cstaMakePredictiveCall = nullptr;
	Proc_cstaPickupCall cstaPickupCall = nullptr;
	Proc_cstaReconnectCall cstaReconnectCall = nullptr;
	Proc_cstaRetrieveCall cstaRetrieveCall = nullptr;
	Proc_cstaTransferCall cstaTransferCall = nullptr;
	Proc_cstaSetMsgWaitingInd cstaSetMsgWaitingInd = nullptr;
	Proc_cstaSetDoNotDisturb cstaSetDoNotDisturb = nullptr;
	Proc_cstaSetForwarding cstaSetForwarding = nullptr;
	Proc_cstaSetAgentState cstaSetAgentState = nullptr;
	Proc_cstaQueryMsgWaitingInd cstaQueryMsgWaitingInd = nullptr;
	Proc_cstaQueryDoNotDisturb cstaQueryDoNotDisturb = nullptr;
	Proc_cstaQueryForwarding cstaQueryForwarding = nullptr;
	Proc_cstaQueryAgentState cstaQueryAgentState = nullptr;
	Proc_cstaQueryLastNumber cstaQueryLastNumber = nullptr;
	Proc_cstaQueryDeviceInfo cstaQueryDeviceInfo = nullptr;
	Proc_cstaMonitorDevice cstaMonitorDevice = nullptr;
	Proc_cstaMonitorCall cstaMonitorCall = nullptr;
	Proc_cstaMonitorCallsViaDevice cstaMonitorCallsViaDevice = nullptr;
	Proc_cstaChangeMonitorFilter cstaChangeMonitorFilter = nullptr;
	Proc_cstaMonitorStop cstaMonitorStop = nullptr;
	Proc_cstaSnapshotCallReq cstaSnapshotCallReq = nullptr;
	Proc_cstaSnapshotDeviceReq cstaSnapshotDeviceReq = nullptr;
	Proc_cstaRouteRegisterReq cstaRouteRegisterReq = nullptr;
	Proc_cstaRouteRegisterCancel cstaRouteRegisterCancel = nullptr;
	Proc_cstaRouteSelect cstaRouteSelect = nullptr;
	Proc_cstaRouteEnd cstaRouteEnd = nullptr;
	Proc_cstaRouteSelectInv cstaRouteSelectInv = nullptr;
	Proc_cstaRouteEndInv cstaRouteEndInv = nullptr;
	Proc_cstaEscapeService cstaEscapeService = nullptr;
	Proc_cstaEscapeServiceConf cstaEscapeServiceConf = nullptr;
	Proc_cstaSendPrivateEvent cstaSendPrivateEvent = nullptr;
	Proc_cstaSysStatReq cstaSysStatReq = nullptr;
	Proc_cstaSysStatStart cstaSysStatStart = nullptr;
	Proc_cstaSysStatStop cstaSysStatStop = nullptr;
	Proc_cstaChangeSysStatFilter cstaChangeSysStatFilter = nullptr;
	Proc_cstaSysStatReqConf cstaSysStatReqConf = nullptr;
	Proc_cstaSysStatEvent cstaSysStatEvent = nullptr;
	Proc_cstaGetAPICaps cstaGetAPICaps = nullptr;
	Proc_cstaGetDeviceList cstaGetDeviceList = nullptr;
	Proc_cstaQueryCallMonitor cstaQueryCallMonitor = nullptr;
	Proc_attMakeVersionString attMakeVersionString = nullptr;
	Proc_encodePrivate encodePrivate = nullptr;
	Proc_attPrivateData attPrivateData = nullptr;
	Proc_attClearConnection attClearConnection = nullptr;
	Proc_attConsultationCall attConsultationCall = nullptr;
	Proc_attMakeCall attMakeCall = nullptr;
	Proc_attDirectAgentCall attDirectAgentCall = nullptr;
	Proc_attMakePredictiveCall attMakePredictiveCall = nullptr;
	Proc_attSupervisorAssistCall attSupervisorAssistCall = nullptr;
	Proc_attReconnectCall attReconnectCall = nullptr;
	Proc_attSendDTMFTone attSendDTMFTone = nullptr;
	Proc_attSetAgentState attSetAgentState = nullptr;
	Proc_attQueryAcdSplit attQueryAcdSplit = nullptr;
	Proc_attQueryAgentLogin attQueryAgentLogin = nullptr;
	Proc_attQueryAgentState attQueryAgentState = nullptr;
	Proc_attQueryCallClassifier attQueryCallClassifier = nullptr;
	Proc_attQueryDeviceName attQueryDeviceName = nullptr;
	Proc_attQueryStationStatus attQueryStationStatus = nullptr;
	Proc_attQueryTimeOfDay attQueryTimeOfDay = nullptr;
	Proc_attQueryTrunkGroup attQueryTrunkGroup = nullptr;
	Proc_attMonitorFilter attMonitorFilter = nullptr;
	Proc_attMonitorStopOnCall attMonitorStopOnCall = nullptr;
	Proc_attRouteSelect attRouteSelect = nullptr;
	Proc_attSysStat attSysStat = nullptr;
	Proc_attSingleStepConferenceCall attSingleStepConferenceCall = nullptr;
	Proc_attSelectiveListeningHold attSelectiveListeningHold = nullptr;
	Proc_attSelectiveListeningRetrieve attSelectiveListeningRetrieve = nullptr;
	Proc_attSetAgentStateExt attSetAgentStateExt = nullptr;
	Proc_attSetBillRate attSetBillRate = nullptr;
	Proc_attQueryUCID attQueryUCID = nullptr;
	Proc_attSetAdviceOfCharge attSetAdviceOfCharge = nullptr;
	Proc_attSendDTMFToneExt attSendDTMFToneExt = nullptr;
	Proc_attMonitorFilterExt attMonitorFilterExt = nullptr;
	Proc_attV6SetAgentState attV6SetAgentState = nullptr;
	Proc_attV6MakeCall attV6MakeCall = nullptr;
	Proc_attV6ClearConnection attV6ClearConnection = nullptr;
	Proc_attV6ConsultationCall attV6ConsultationCall = nullptr;
	Proc_attV6DirectAgentCall attV6DirectAgentCall = nullptr;
	Proc_attV6MakePredictiveCall attV6MakePredictiveCall = nullptr;
	Proc_attV6SupervisorAssistCall attV6SupervisorAssistCall = nullptr;
	Proc_attV6ReconnectCall attV6ReconnectCall = nullptr;
	Proc_attV6RouteSelect attV6RouteSelect = nullptr;
	Proc_attV7RouteSelect attV7RouteSelect = nullptr;
	Proc_attSingleStepTransferCall attSingleStepTransferCall = nullptr;
	Proc_attMonitorCallsViaDevice attMonitorCallsViaDevice = nullptr;
	Proc_initATTPrivate initATTPrivate = nullptr;
	Proc_addATTPrivate addATTPrivate = nullptr;
	Proc_getATTPrivate getATTPrivate = nullptr;

	static Dynamiclibrary CSTA32("CSTA32.DLL");
	static Dynamiclibrary ATTPRV32("ATTPRV32.DLL");

	const char * cstaAgentStateString(AgentState_t agentState)
	{
		switch (agentState)
		{
		case AgentState_t::agNotReady: return "NotReady";
		case AgentState_t::agNull: return "Null";
		case AgentState_t::agReady: return "Ready";
		case AgentState_t::agWorkNotReady: return "WorkNotReady";
		case AgentState_t::agWorkReady: return "WorkReady";
		default: return "";
		}
	}

	const char * cstaAPICapsString(uint32_t api)
	{
		static CSTAGetAPICapsConfEvent_t event;
		short * begin = (short *)&event;
		
		if (&event.alternateCall - begin == api) return "alternateCall";
		if (&event.answerCall - begin == api) return "answerCall";
		if (&event.callCompletion - begin == api) return "callCompletion";
		if (&event.clearCall - begin == api) return "clearCall";
		if (&event.clearConnection - begin == api) return "clearConnection";
		if (&event.conferenceCall - begin == api) return "conferenceCall";
		if (&event.consultationCall - begin == api) return "consultationCall";
		if (&event.deflectCall - begin == api) return "deflectCall";
		if (&event.pickupCall - begin == api) return "pickupCall";
		if (&event.groupPickupCall - begin == api) return "groupPickupCall";
		if (&event.holdCall - begin == api) return "holdCall";
		if (&event.makeCall - begin == api) return "makeCall";
		if (&event.makePredictiveCall - begin == api) return "makePredictiveCall";
		if (&event.queryMwi - begin == api) return "queryMwi";
		if (&event.queryDnd - begin == api) return "queryDnd";
		if (&event.queryFwd - begin == api) return "queryFwd";
		if (&event.queryAgentState - begin == api) return "queryAgentState";
		if (&event.queryLastNumber - begin == api) return "queryLastNumber";
		if (&event.queryDeviceInfo - begin == api) return "queryDeviceInfo";
		if (&event.reconnectCall - begin == api) return "reconnectCall";
		if (&event.retrieveCall - begin == api) return "retrieveCall";
		if (&event.setMwi - begin == api) return "setMwi";
		if (&event.setDnd - begin == api) return "setDnd";
		if (&event.setFwd - begin == api) return "setFwd";
		if (&event.setAgentState - begin == api) return "setAgentState";
		if (&event.transferCall - begin == api) return "transferCall";
		if (&event.eventReport - begin == api) return "eventReport";
		if (&event.callClearedEvent - begin == api) return "callClearedEvent";
		if (&event.conferencedEvent - begin == api) return "conferencedEvent";
		if (&event.connectionClearedEvent - begin == api) return "connectionClearedEvent";
		if (&event.deliveredEvent - begin == api) return "deliveredEvent";
		if (&event.divertedEvent - begin == api) return "divertedEvent";
		if (&event.establishedEvent - begin == api) return "establishedEvent";
		if (&event.failedEvent - begin == api) return "failedEvent";
		if (&event.heldEvent - begin == api) return "heldEvent";
		if (&event.networkReachedEvent - begin == api) return "networkReachedEvent";
		if (&event.originatedEvent - begin == api) return "originatedEvent";
		if (&event.queuedEvent - begin == api) return "queuedEvent";
		if (&event.retrievedEvent - begin == api) return "retrievedEvent";
		if (&event.serviceInitiatedEvent - begin == api) return "serviceInitiatedEvent";
		if (&event.transferredEvent - begin == api) return "transferredEvent";
		if (&event.callInformationEvent - begin == api) return "callInformationEvent";
		if (&event.doNotDisturbEvent - begin == api) return "doNotDisturbEvent";
		if (&event.forwardingEvent - begin == api) return "forwardingEvent";
		if (&event.messageWaitingEvent - begin == api) return "messageWaitingEvent";
		if (&event.loggedOnEvent - begin == api) return "loggedOnEvent";
		if (&event.loggedOffEvent - begin == api) return "loggedOffEvent";
		if (&event.notReadyEvent - begin == api) return "notReadyEvent";
		if (&event.readyEvent - begin == api) return "readyEvent";
		if (&event.workNotReadyEvent - begin == api) return "workNotReadyEvent";
		if (&event.workReadyEvent - begin == api) return "workReadyEvent";
		if (&event.backInServiceEvent - begin == api) return "backInServiceEvent";
		if (&event.outOfServiceEvent - begin == api) return "outOfServiceEvent";
		if (&event.privateEvent - begin == api) return "privateEvent";
		if (&event.routeRequestEvent - begin == api) return "routeRequestEvent";
		if (&event.reRoute - begin == api) return "reRoute";
		if (&event.routeSelect - begin == api) return "routeSelect";
		if (&event.routeUsedEvent - begin == api) return "routeUsedEvent";
		if (&event.routeEndEvent - begin == api) return "routeEndEvent";
		if (&event.monitorDevice - begin == api) return "monitorDevice";
		if (&event.monitorCall - begin == api) return "monitorCall";
		if (&event.monitorCallsViaDevice - begin == api) return "monitorCallsViaDevice";
		if (&event.changeMonitorFilter - begin == api) return "changeMonitorFilter";
		if (&event.monitorStop - begin == api) return "monitorStop";
		if (&event.monitorEnded - begin == api) return "monitorEnded";
		if (&event.snapshotDeviceReq - begin == api) return "snapshotDeviceReq";
		if (&event.snapshotCallReq - begin == api) return "snapshotCallReq";
		if (&event.escapeService - begin == api) return "escapeService";
		if (&event.privateStatusEvent - begin == api) return "privateStatusEvent";
		if (&event.escapeServiceEvent - begin == api) return "escapeServiceEvent";
		if (&event.escapeServiceConf - begin == api) return "escapeServiceConf";
		if (&event.sendPrivateEvent - begin == api) return "sendPrivateEvent";
		if (&event.sysStatReq - begin == api) return "sysStatReq";
		if (&event.sysStatStart - begin == api) return "sysStatStart";
		if (&event.sysStatStop - begin == api) return "sysStatStop";
		if (&event.changeSysStatFilter - begin == api) return "changeSysStatFilter";
		if (&event.sysStatReqEvent - begin == api) return "sysStatReqEvent";
		if (&event.sysStatReqConf - begin == api) return "sysStatReqConf";
		if (&event.sysStatEvent - begin == api) return "sysStatEvent";
		return "";
	}

	const char * cstaConnectionIDDeviceTypeString(ConnectionID_Device_t type)
	{
		switch (type)
		{
		case staticId: return "staticId";
		case dynamicId: return "dynamicId";
		default:return "";
		}
	}

	ConnectionID_Device_t cstaStringConnectionIDDevice(const std::string & type)
	{
		if (type == "staticId")
			return staticId;
		else if (type == "dynamicId")
			return dynamicId;
		else
			return staticId;
	}

	const char * cstaLocalConnectionStateString(LocalConnectionState_t localState)
	{
		switch (localState)
		{
		case csNone: return "None";
		case csNull: return "Null";
		case csInitiate:return "Initiate";
		case csAlerting:return "Alerting";
		case csConnect: return "Connect";
		case csHold:return "Hold";
		case csQueued:return "Queued";
		case csFail:return "Fail";
		default:return "";
		}
		
	}

	const char * cstaEventCauseString(CSTAEventCause_t cause)
	{
		switch (cause)
		{
		case ecNone: return "None";
		case ecActiveMonitor: return "ActiveMonitor";
		case ecAlternate:return "Alternate";
		case ecBusy: return "Busy";
		case ecCallBack: return "CallBack";
		case ecCallCancelled: return "CallCancelled";
		case ecCallForwardAlways: return "CallForwardAlways";
		case ecCallForwardBusy: return "CallForwardBusy";
		case ecCallForwardNoAnswer: return "CallForwardNoAnswer";
		case ecCallForward: return "CallForward";
		case ecCallNotAnswered: return "CallNotAnswered";
		case ecCallPickup: return "CallPickup";
		case ecCampOn: return "CampOn";
		case ecDestNotObtainable: return "DestNotObtainable";
		case ecDoNotDisturb: return "DoNotDisturb";
		case ecIncompatibleDestination: return "IncompatibleDestination";
		case ecInvalidAccountCode: return "InvalidAccountCode";
		case ecKeyConference: return "KeyConference";
		case ecLockout: return "Lockout";
		case ecMaintenance: return "Maintenance";
		case ecNetworkCongestion: return "NetworkCongestion";
		case ecNetworkNotObtainable: return "NetworkNotObtainable";
		case ecNewCall: return "NewCall";
		case ecNoAvailableAgents: return "NoAvailableAgents";
		case ecOverride: return "Override";
		case ecPark: return "Park";
		case ecOverflow: return "Overflow";
		case ecRecall: return "Recall";
		case ecRedirected: return "Redirected";
		case ecReorderTone: return "ReorderTone";
		case ecResourcesNotAvailable: return "ResourcesNotAvailable";
		case ecSilentMonitor: return "SilentMonitor";
		case ecTransfer: return "Transfer";
		case ecTrunksBusy: return "TrunksBusy";
		case ecVoiceUnitInitiator: return "VoiceUnitInitiator";
		case ecNetworkSignal: return "NetworkSignal";
		case ecSingleStepTransfer: return "SingleStepTransfer";
		case ecAlertTimeExpired: return "AlertTimeExpired";
		case ecDestOutOfOrder: return "DestOutOfOrder";
		case ecNotSupportedBearerService: return "NotSupportedBearerService";
		case ecUnassignedNumber: return "UnassignedNumber";
		case ecIncompatibleBearerService: return "IncompatibleBearerService";
		default: return "";
		}
	}

	const char * cstaDeviceIDStatusString(DeviceIDStatus_t deviceIDStatus)
	{
		switch (deviceIDStatus)
		{
		case idProvided: return "Provided";
		case idNotKnown: return "NotKnown";
		case idNotRequired: return "NotRequired";
		default: return "";
		}
	}

	const char * cstaDeviceIDTypeString(DeviceIDType_t deviceIDType)
	{
		switch (deviceIDType)
		{
		case deviceIdentifier: return "deviceIdentifier";
			break;
		case implicitPublic: return "implicitPublic";
			break;
		case explicitPublicUnknown: return "explicitPublicUnknown";
			break;
		case explicitPublicInternational: return "explicitPublicInternational";
			break;
		case explicitPublicNational: return "explicitPublicNational";
			break;
		case explicitPublicNetworkSpecific: return "explicitPublicNetworkSpecific";
			break;
		case explicitPublicSubscriber: return "explicitPublicSubscriber";
			break;
		case explicitPublicAbbreviated: return "explicitPublicAbbreviated";
			break;
		case implicitPrivate: return "implicitPrivate";
			break;
		case explicitPrivateUnknown: return "explicitPrivateUnknown";
			break;
		case explicitPrivateLevel3RegionalNumber: return "explicitPrivateLevel3RegionalNumber";
			break;
		case explicitPrivateLevel2RegionalNumber: return "explicitPrivateLevel2RegionalNumber";
			break;
		case explicitPrivateLevel1RegionalNumber: return "explicitPrivateLevel1RegionalNumber";
			break;
		case explicitPrivatePtnSpecificNumber: return "explicitPrivatePtnSpecificNumber";
			break;
		case explicitPrivateLocalNumber: return "explicitPrivateLocalNumber";
			break;
		case explicitPrivateAbbreviated: return "explicitPrivateAbbreviated";
			break;
		case otherPlan: return "otherPlan";
			break;
		case trunkIdentifier: return "trunkIdentifier";
			break;
		case trunkGroupIdentifier: return "trunkGroupIdentifier";
			break;
		default: return "";
			break;
		}
	}


	bool InitAvayaAPI() {
		if (g_Reference.fetch_add(1) == 0) {
			if (!CSTA32.Open()){
				return false;
			}
			acsOpenStream = (Proc_acsOpenStream)CSTA32.GetFunction("acsOpenStream");
			acsCloseStream = (Proc_acsCloseStream)CSTA32.GetFunction("acsCloseStream");
			acsAbortStream = (Proc_acsAbortStream)CSTA32.GetFunction("acsAbortStream");
			acsFlushEventQueue = (Proc_acsFlushEventQueue)CSTA32.GetFunction("acsFlushEventQueue");
			acsGetEventPoll = (Proc_acsGetEventPoll)CSTA32.GetFunction("acsGetEventPoll");
			acsGetEventBlock = (Proc_acsGetEventBlock)CSTA32.GetFunction("acsGetEventBlock");
#if defined ( TSLIB_WINDOWS_32 )
			acsEventNotify = (Proc_acsEventNotify)CSTA32.GetFunction("acsEventNotify");
			acsSetESR = (Proc_acsSetESR)CSTA32.GetFunction("acsSetESR");
#elif defined ( TSLIB_LINUX )
			acsGetFile = (Proc_acsGetFile)CSTA32.GetFunction("acsGetFile");
#endif
			acsEnumServerNames = (Proc_acsEnumServerNames)CSTA32.GetFunction("acsEnumServerNames");
			acsQueryAuthInfo = (Proc_acsQueryAuthInfo)CSTA32.GetFunction("acsQueryAuthInfo");
			acsGetServerID = (Proc_acsGetServerID)CSTA32.GetFunction("acsGetServerID");
			acsSetHeartbeatInterval = (Proc_acsSetHeartbeatInterval)CSTA32.GetFunction("acsSetHeartbeatInterval");
			acsReturnCodeString = (Proc_acsReturnCodeString)CSTA32.GetFunction("acsReturnCodeString");
			acsReturnCodeVerboseString = (Proc_acsReturnCodeVerboseString)CSTA32.GetFunction("acsReturnCodeVerboseString");
			acsErrorString = (Proc_acsErrorString)CSTA32.GetFunction("acsErrorString");
			cstaErrorString = (Proc_cstaErrorString)CSTA32.GetFunction("cstaErrorString");
			cstaAlternateCall = (Proc_cstaAlternateCall)CSTA32.GetFunction("cstaAlternateCall");
			cstaAnswerCall = (Proc_cstaAnswerCall)CSTA32.GetFunction("cstaAnswerCall");
			cstaCallCompletion = (Proc_cstaCallCompletion)CSTA32.GetFunction("cstaCallCompletion");
			cstaClearCall = (Proc_cstaClearCall)CSTA32.GetFunction("cstaClearCall");
			cstaClearConnection = (Proc_cstaClearConnection)CSTA32.GetFunction("cstaClearConnection");
			cstaConferenceCall = (Proc_cstaConferenceCall)CSTA32.GetFunction("cstaConferenceCall");
			cstaConsultationCall = (Proc_cstaConsultationCall)CSTA32.GetFunction("cstaConsultationCall");
			cstaDeflectCall = (Proc_cstaDeflectCall)CSTA32.GetFunction("cstaDeflectCall");
			cstaGroupPickupCall = (Proc_cstaGroupPickupCall)CSTA32.GetFunction("cstaGroupPickupCall");
			cstaHoldCall = (Proc_cstaHoldCall)CSTA32.GetFunction("cstaHoldCall");
			cstaMakeCall = (Proc_cstaMakeCall)CSTA32.GetFunction("cstaMakeCall");
			cstaMakePredictiveCall = (Proc_cstaMakePredictiveCall)CSTA32.GetFunction("cstaMakePredictiveCall");
			cstaPickupCall = (Proc_cstaPickupCall)CSTA32.GetFunction("cstaPickupCall");
			cstaReconnectCall = (Proc_cstaReconnectCall)CSTA32.GetFunction("cstaReconnectCall");
			cstaRetrieveCall = (Proc_cstaRetrieveCall)CSTA32.GetFunction("cstaRetrieveCall");
			cstaTransferCall = (Proc_cstaTransferCall)CSTA32.GetFunction("cstaTransferCall");
			cstaSetMsgWaitingInd = (Proc_cstaSetMsgWaitingInd)CSTA32.GetFunction("cstaSetMsgWaitingInd");
			cstaSetDoNotDisturb = (Proc_cstaSetDoNotDisturb)CSTA32.GetFunction("cstaSetDoNotDisturb");
			cstaSetForwarding = (Proc_cstaSetForwarding)CSTA32.GetFunction("cstaSetForwarding");
			cstaSetAgentState = (Proc_cstaSetAgentState)CSTA32.GetFunction("cstaSetAgentState");
			cstaQueryMsgWaitingInd = (Proc_cstaQueryMsgWaitingInd)CSTA32.GetFunction("cstaQueryMsgWaitingInd");
			cstaQueryDoNotDisturb = (Proc_cstaQueryDoNotDisturb)CSTA32.GetFunction("cstaQueryDoNotDisturb");
			cstaQueryForwarding = (Proc_cstaQueryForwarding)CSTA32.GetFunction("cstaQueryForwarding");
			cstaQueryAgentState = (Proc_cstaQueryAgentState)CSTA32.GetFunction("cstaQueryAgentState");
			cstaQueryLastNumber = (Proc_cstaQueryLastNumber)CSTA32.GetFunction("cstaQueryLastNumber");
			cstaQueryDeviceInfo = (Proc_cstaQueryDeviceInfo)CSTA32.GetFunction("cstaQueryDeviceInfo");
			cstaMonitorDevice = (Proc_cstaMonitorDevice)CSTA32.GetFunction("cstaMonitorDevice");
			cstaMonitorCall = (Proc_cstaMonitorCall)CSTA32.GetFunction("cstaMonitorCall");
			cstaMonitorCallsViaDevice = (Proc_cstaMonitorCallsViaDevice)CSTA32.GetFunction("cstaMonitorCallsViaDevice");
			cstaChangeMonitorFilter = (Proc_cstaChangeMonitorFilter)CSTA32.GetFunction("cstaChangeMonitorFilter");
			cstaMonitorStop = (Proc_cstaMonitorStop)CSTA32.GetFunction("cstaMonitorStop");
			cstaSnapshotCallReq = (Proc_cstaSnapshotCallReq)CSTA32.GetFunction("cstaSnapshotCallReq");
			cstaSnapshotDeviceReq = (Proc_cstaSnapshotDeviceReq)CSTA32.GetFunction("cstaSnapshotDeviceReq");
			cstaRouteRegisterReq = (Proc_cstaRouteRegisterReq)CSTA32.GetFunction("cstaRouteRegisterReq");
			cstaRouteRegisterCancel = (Proc_cstaRouteRegisterCancel)CSTA32.GetFunction("cstaRouteRegisterCancel");
			cstaRouteSelect = (Proc_cstaRouteSelect)CSTA32.GetFunction("cstaRouteSelect");
			cstaRouteEnd = (Proc_cstaRouteEnd)CSTA32.GetFunction("cstaRouteEnd");
			cstaRouteSelectInv = (Proc_cstaRouteSelectInv)CSTA32.GetFunction("cstaRouteSelectInv");
			cstaRouteEndInv = (Proc_cstaRouteEndInv)CSTA32.GetFunction("cstaRouteEndInv");
			cstaEscapeService = (Proc_cstaEscapeService)CSTA32.GetFunction("cstaEscapeService");
			cstaEscapeServiceConf = (Proc_cstaEscapeServiceConf)CSTA32.GetFunction("cstaEscapeServiceConf");
			cstaSendPrivateEvent = (Proc_cstaSendPrivateEvent)CSTA32.GetFunction("cstaSendPrivateEvent");
			cstaSysStatReq = (Proc_cstaSysStatReq)CSTA32.GetFunction("cstaSysStatReq");
			cstaSysStatStart = (Proc_cstaSysStatStart)CSTA32.GetFunction("cstaSysStatStart");
			cstaSysStatStop = (Proc_cstaSysStatStop)CSTA32.GetFunction("cstaSysStatStop");
			cstaChangeSysStatFilter = (Proc_cstaChangeSysStatFilter)CSTA32.GetFunction("cstaChangeSysStatFilter");
			cstaSysStatReqConf = (Proc_cstaSysStatReqConf)CSTA32.GetFunction("cstaSysStatReqConf");
			cstaSysStatEvent = (Proc_cstaSysStatEvent)CSTA32.GetFunction("cstaSysStatEvent");
			cstaGetAPICaps = (Proc_cstaGetAPICaps)CSTA32.GetFunction("cstaGetAPICaps");
			cstaGetDeviceList = (Proc_cstaGetDeviceList)CSTA32.GetFunction("cstaGetDeviceList");
			cstaQueryCallMonitor = (Proc_cstaQueryCallMonitor)CSTA32.GetFunction("cstaQueryCallMonitor");
			
			if (!ATTPRV32.Open()) {
				return false;
			}

			attMakeVersionString = (Proc_attMakeVersionString)ATTPRV32.GetFunction("attMakeVersionString");
			encodePrivate = (Proc_encodePrivate)ATTPRV32.GetFunction("encodePrivate");
			attPrivateData = (Proc_attPrivateData)ATTPRV32.GetFunction("attPrivateData");
			attClearConnection = (Proc_attClearConnection)ATTPRV32.GetFunction("attClearConnection");
			attConsultationCall = (Proc_attConsultationCall)ATTPRV32.GetFunction("attConsultationCall");
			attMakeCall = (Proc_attMakeCall)ATTPRV32.GetFunction("attMakeCall");
			attDirectAgentCall = (Proc_attDirectAgentCall)ATTPRV32.GetFunction("attDirectAgentCall");
			attMakePredictiveCall = (Proc_attMakePredictiveCall)ATTPRV32.GetFunction("attMakePredictiveCall");
			attSupervisorAssistCall = (Proc_attSupervisorAssistCall)ATTPRV32.GetFunction("attSupervisorAssistCall");
			attReconnectCall = (Proc_attReconnectCall)ATTPRV32.GetFunction("attReconnectCall");
			attSendDTMFTone = (Proc_attSendDTMFTone)ATTPRV32.GetFunction("attSendDTMFTone");
			attSetAgentState = (Proc_attSetAgentState)ATTPRV32.GetFunction("attSetAgentState");
			attQueryAcdSplit = (Proc_attQueryAcdSplit)ATTPRV32.GetFunction("attQueryAcdSplit");
			attQueryAgentLogin = (Proc_attQueryAgentLogin)ATTPRV32.GetFunction("attQueryAgentLogin");
			attQueryAgentState = (Proc_attQueryAgentState)ATTPRV32.GetFunction("attQueryAgentState");
			attQueryCallClassifier = (Proc_attQueryCallClassifier)ATTPRV32.GetFunction("attQueryCallClassifier");
			attQueryDeviceName = (Proc_attQueryDeviceName)ATTPRV32.GetFunction("attQueryDeviceName");
			attQueryStationStatus = (Proc_attQueryStationStatus)ATTPRV32.GetFunction("attQueryStationStatus");
			attQueryTimeOfDay = (Proc_attQueryTimeOfDay)ATTPRV32.GetFunction("attQueryTimeOfDay");
			attQueryTrunkGroup = (Proc_attQueryTrunkGroup)ATTPRV32.GetFunction("attQueryTrunkGroup");
			attMonitorFilter = (Proc_attMonitorFilter)ATTPRV32.GetFunction("attMonitorFilter");
			attMonitorStopOnCall = (Proc_attMonitorStopOnCall)ATTPRV32.GetFunction("attMonitorStopOnCall");
			attRouteSelect = (Proc_attRouteSelect)ATTPRV32.GetFunction("attRouteSelect");
			attSysStat = (Proc_attSysStat)ATTPRV32.GetFunction("attSysStat");
			attSingleStepConferenceCall = (Proc_attSingleStepConferenceCall)ATTPRV32.GetFunction("attSingleStepConferenceCall");
			attSelectiveListeningHold = (Proc_attSelectiveListeningHold)ATTPRV32.GetFunction("attSelectiveListeningHold");
			attSelectiveListeningRetrieve = (Proc_attSelectiveListeningRetrieve)ATTPRV32.GetFunction("attSelectiveListeningRetrieve");
			attSetAgentStateExt = (Proc_attSetAgentStateExt)ATTPRV32.GetFunction("attSetAgentStateExt");
			attSetBillRate = (Proc_attSetBillRate)ATTPRV32.GetFunction("attSetBillRate");
			attQueryUCID = (Proc_attQueryUCID)ATTPRV32.GetFunction("attQueryUCID");
			attSetAdviceOfCharge = (Proc_attSetAdviceOfCharge)ATTPRV32.GetFunction("attSetAdviceOfCharge");
			attSendDTMFToneExt = (Proc_attSendDTMFToneExt)ATTPRV32.GetFunction("attSendDTMFToneExt");
			attMonitorFilterExt = (Proc_attMonitorFilterExt)ATTPRV32.GetFunction("attMonitorFilterExt");
			attV6SetAgentState = (Proc_attV6SetAgentState)ATTPRV32.GetFunction("attV6SetAgentState");
			attV6MakeCall = (Proc_attV6MakeCall)ATTPRV32.GetFunction("attV6MakeCall");
			attV6ClearConnection = (Proc_attV6ClearConnection)ATTPRV32.GetFunction("attV6ClearConnection");
			attV6ConsultationCall = (Proc_attV6ConsultationCall)ATTPRV32.GetFunction("attV6ConsultationCall");
			attV6DirectAgentCall = (Proc_attV6DirectAgentCall)ATTPRV32.GetFunction("attV6DirectAgentCall");
			attV6MakePredictiveCall = (Proc_attV6MakePredictiveCall)ATTPRV32.GetFunction("attV6MakePredictiveCall");
			attV6SupervisorAssistCall = (Proc_attV6SupervisorAssistCall)ATTPRV32.GetFunction("attV6SupervisorAssistCall");
			attV6ReconnectCall = (Proc_attV6ReconnectCall)ATTPRV32.GetFunction("attV6ReconnectCall");
			attV6RouteSelect = (Proc_attV6RouteSelect)ATTPRV32.GetFunction("attV6RouteSelect");
			attV7RouteSelect = (Proc_attV7RouteSelect)ATTPRV32.GetFunction("attV7RouteSelect");
			attSingleStepTransferCall = (Proc_attSingleStepTransferCall)ATTPRV32.GetFunction("attSingleStepTransferCall");
			attMonitorCallsViaDevice = (Proc_attMonitorCallsViaDevice)ATTPRV32.GetFunction("attMonitorCallsViaDevice");
			initATTPrivate = (Proc_initATTPrivate)ATTPRV32.GetFunction("initATTPrivate");
			addATTPrivate = (Proc_addATTPrivate)ATTPRV32.GetFunction("addATTPrivate");
			getATTPrivate = (Proc_getATTPrivate)ATTPRV32.GetFunction("getATTPrivate");
		}
		return true;
	}

	bool UnInitAvayaAPI()
	{
		if (g_Reference.fetch_sub(1) == 1) {
			acsOpenStream = nullptr;
			acsCloseStream = nullptr;
			acsAbortStream = nullptr;
			acsFlushEventQueue = nullptr;
			acsGetEventPoll = nullptr;
			acsGetEventBlock = nullptr;
#if defined ( TSLIB_WINDOWS_32 )
			acsEventNotify = nullptr;
			acsSetESR = nullptr;
#elif defined ( TSLIB_LINUX )
			acsGetFile = nullptr;
#endif
			acsEnumServerNames = nullptr;
			acsQueryAuthInfo = nullptr;
			acsGetServerID = nullptr;
			acsSetHeartbeatInterval = nullptr;
			acsReturnCodeString = nullptr;
			acsReturnCodeVerboseString = nullptr;
			acsErrorString = nullptr;
			cstaErrorString = nullptr;
			cstaAlternateCall = nullptr;
			cstaAnswerCall = nullptr;
			cstaCallCompletion = nullptr;
			cstaClearCall = nullptr;
			cstaClearConnection = nullptr;
			cstaConferenceCall = nullptr;
			cstaConsultationCall = nullptr;
			cstaDeflectCall = nullptr;
			cstaGroupPickupCall = nullptr;
			cstaHoldCall = nullptr;
			cstaMakeCall = nullptr;
			cstaMakePredictiveCall = nullptr;
			cstaPickupCall = nullptr;
			cstaReconnectCall = nullptr;
			cstaRetrieveCall = nullptr;
			cstaTransferCall = nullptr;
			cstaSetMsgWaitingInd = nullptr;
			cstaSetDoNotDisturb = nullptr;
			cstaSetForwarding = nullptr;
			cstaSetAgentState = nullptr;
			cstaQueryMsgWaitingInd = nullptr;
			cstaQueryDoNotDisturb = nullptr;
			cstaQueryForwarding = nullptr;
			cstaQueryAgentState = nullptr;
			cstaQueryLastNumber = nullptr;
			cstaQueryDeviceInfo = nullptr;
			cstaMonitorDevice = nullptr;
			cstaMonitorCall = nullptr;
			cstaMonitorCallsViaDevice = nullptr;
			cstaChangeMonitorFilter = nullptr;
			cstaMonitorStop = nullptr;
			cstaSnapshotCallReq = nullptr;
			cstaSnapshotDeviceReq = nullptr;
			cstaRouteRegisterReq = nullptr;
			cstaRouteRegisterCancel = nullptr;
			cstaRouteSelect = nullptr;
			cstaRouteEnd = nullptr;
			cstaRouteSelectInv = nullptr;
			cstaRouteEndInv = nullptr;
			cstaEscapeService = nullptr;
			cstaEscapeServiceConf = nullptr;
			cstaSendPrivateEvent = nullptr;
			cstaSysStatReq = nullptr;
			cstaSysStatStart = nullptr;
			cstaSysStatStop = nullptr;
			cstaChangeSysStatFilter = nullptr;
			cstaSysStatReqConf = nullptr;
			cstaSysStatEvent = nullptr;
			cstaGetAPICaps = nullptr;
			cstaGetDeviceList = nullptr;
			cstaQueryCallMonitor = nullptr;
			attMakeVersionString = nullptr;
			encodePrivate = nullptr;
			attPrivateData = nullptr;
			attClearConnection = nullptr;
			attConsultationCall = nullptr;
			attMakeCall = nullptr;
			attDirectAgentCall = nullptr;
			attMakePredictiveCall = nullptr;
			attSupervisorAssistCall = nullptr;
			attReconnectCall = nullptr;
			attSendDTMFTone = nullptr;
			attSetAgentState = nullptr;
			attQueryAcdSplit = nullptr;
			attQueryAgentLogin = nullptr;
			attQueryAgentState = nullptr;
			attQueryCallClassifier = nullptr;
			attQueryDeviceName = nullptr;
			attQueryStationStatus = nullptr;
			attQueryTimeOfDay = nullptr;
			attQueryTrunkGroup = nullptr;
			attMonitorFilter = nullptr;
			attMonitorStopOnCall = nullptr;
			attRouteSelect = nullptr;
			attSysStat = nullptr;
			attSingleStepConferenceCall = nullptr;
			attSelectiveListeningHold = nullptr;
			attSelectiveListeningRetrieve = nullptr;
			attSetAgentStateExt = nullptr;
			attSetBillRate = nullptr;
			attQueryUCID = nullptr;
			attSetAdviceOfCharge = nullptr;
			attSendDTMFToneExt = nullptr;
			attMonitorFilterExt = nullptr;
			attV6SetAgentState = nullptr;
			attV6MakeCall = nullptr;
			attV6ClearConnection = nullptr;
			attV6ConsultationCall = nullptr;
			attV6DirectAgentCall = nullptr;
			attV6MakePredictiveCall = nullptr;
			attV6SupervisorAssistCall = nullptr;
			attV6ReconnectCall = nullptr;
			attV6RouteSelect = nullptr;
			attV7RouteSelect = nullptr;
			attSingleStepTransferCall = nullptr;
			attMonitorCallsViaDevice = nullptr;
			initATTPrivate = nullptr;
			addATTPrivate = nullptr;
			getATTPrivate = nullptr;

			//ATTPRV32.Close();
			//CSTA32.Close();
		}
		
		return true;
	}
}

Json::Value AvayaAPI::cstaConnectionIDJson(ConnectionID_t connectionId)
{
	const char * deviceID = connectionId.deviceID;
	ConnectionID_Device_t devIDType = connectionId.devIDType;
	int32_t callID = connectionId.callID;

	Json::Value connection;
	connection["deviceID"] = deviceID;
	connection["devIDType"] = cstaConnectionIDDeviceTypeString(devIDType);
	connection["callID"] = callID;
	return connection;
}
