#pragma once
#include <acs.h>
#include <csta.h>
#include <attpriv.h>
#include <cstdint>
#include <json/config.h>
#include <json/json.h>

namespace AvayaAPI{


	TSAPI acsOpenStream(ACSHandle_t                     FAR *acsHandle,
			InvokeIDType_t                  invokeIDType,
			InvokeID_t                      invokeID,
			StreamType_t                    streamType,
			CONST_PARAM ServerID_t      FAR *serverID,
			CONST_PARAM LoginID_t       FAR *loginID,
			CONST_PARAM Passwd_t        FAR *passwd,
			CONST_PARAM AppName_t       FAR *applicationName,
			Level_t                         acsLevelReq,
			CONST_PARAM Version_t       FAR *apiVer,
			unsigned short                  sendQSize,
			unsigned short                  sendExtraBufs,
			unsigned short                  recvQSize,
			unsigned short                  recvExtraBufs,
			CONST_PARAM PrivateData_t   FAR *priv);


	TSAPI acsCloseStream(ACSHandle_t                     acsHandle,
			InvokeID_t                      invokeID,
			CONST_PARAM PrivateData_t   FAR *priv);


	TSAPI acsAbortStream(ACSHandle_t                     acsHandle,
			CONST_PARAM PrivateData_t   FAR *priv);


	TSAPI acsFlushEventQueue(ACSHandle_t                 acsHandle);


	TSAPI acsGetEventPoll(ACSHandle_t                 acsHandle,
			void                    FAR *eventBuf,
			unsigned short          FAR *eventBufSize,
			PrivateData_t           FAR *privData,
			unsigned short          FAR *numEvents);


	TSAPI acsGetEventBlock(ACSHandle_t                 acsHandle,
			void                    FAR *eventBuf,
			unsigned short          FAR *eventBufSize,
			PrivateData_t           FAR *privData,
			unsigned short          FAR *numEvents);

	/* 32-bit Windows-specific prototypes */

#if defined ( TSLIB_WINDOWS_32 )

	TSAPI acsEventNotify(ACSHandle_t acsHandle, HWND hwnd, UINT msg, Boolean notifyAll);


	TSAPI acsSetESR(ACSHandle_t     acsHandle,
			void            (far pascal *esr)(unsigned long esrParam),
			unsigned long   esrParam,
			Boolean         notifyAll);

	typedef Boolean(*EnumServerNamesCB) (char  *serverName,
		unsigned long lParam);

	/* Linux-specific prototypes */

#elif defined ( TSLIB_LINUX )

	TSAPI acsGetFile(ACSHandle_t acsHandle);

	typedef Boolean(*EnumServerNamesCB) (char *serverName,
		unsigned long lParam);

#endif


	TSAPI acsEnumServerNames(StreamType_t        streamType,
			EnumServerNamesCB   userCB,
			unsigned long       lParam);



	TSAPI acsQueryAuthInfo(CONST_PARAM ServerID_t      FAR *serverID,
			ACSAuthInfo_t               FAR *authInfo);


	TSAPI acsGetServerID(ACSHandle_t         acsHandle,
			ServerID_t          *serverID);

	TSAPI acsSetHeartbeatInterval(ACSHandle_t             acsHandle,
			InvokeID_t              invokeID,
			unsigned short          heartbeatInterval,
			PrivateData_t           *privData);

	const char * acsReturnCodeString(RetCode_t returnCode);

	const char * acsReturnCodeVerboseString(RetCode_t returnCode);

	const char * acsErrorString(ACSUniversalFailure_t error);

	const char * cstaErrorString(CSTAUniversalFailure_t error);

	/* Basic Call Control Services */

	TSAPI cstaAlternateCall(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM ConnectionID_t	FAR	*activeCall,
			CONST_PARAM ConnectionID_t	FAR	*otherCall,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaAnswerCall(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM ConnectionID_t	FAR	*alertingCall,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaCallCompletion(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			Feature_t						feature,
			CONST_PARAM ConnectionID_t	FAR	*call,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaClearCall(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM ConnectionID_t	FAR	*call,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaClearConnection(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM ConnectionID_t	FAR	*call,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaConferenceCall(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM ConnectionID_t	FAR	*heldCall,
			CONST_PARAM ConnectionID_t	FAR	*activeCall,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaConsultationCall(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM ConnectionID_t	FAR	*activeCall,
			CONST_PARAM DeviceID_t		FAR	*calledDevice,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaDeflectCall(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM ConnectionID_t	FAR	*deflectCall,
			CONST_PARAM DeviceID_t		FAR	*calledDevice,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaGroupPickupCall(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM ConnectionID_t	FAR	*deflectCall,
			CONST_PARAM DeviceID_t		FAR	*pickupDevice,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaHoldCall(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM ConnectionID_t	FAR	*activeCall,
			Boolean							reservation,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaMakeCall(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM DeviceID_t		FAR	*callingDevice,
			CONST_PARAM DeviceID_t		FAR	*calledDevice,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaMakePredictiveCall(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM DeviceID_t		FAR	*callingDevice,
			CONST_PARAM DeviceID_t		FAR	*calledDevice,
			AllocationState_t				allocationState,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaPickupCall(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM ConnectionID_t	FAR	*deflectCall,
			CONST_PARAM DeviceID_t		FAR	*calledDevice,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaReconnectCall(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM ConnectionID_t	FAR	*activeCall,
			CONST_PARAM ConnectionID_t	FAR	*heldCall,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaRetrieveCall(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM ConnectionID_t	FAR	*heldCall,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaTransferCall(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM ConnectionID_t	FAR	*heldCall,
			CONST_PARAM ConnectionID_t	FAR	*activeCall,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	/* Telephony Supplementary Services */

	TSAPI cstaSetMsgWaitingInd(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM DeviceID_t		FAR	*device,
			Boolean							messages,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaSetDoNotDisturb(ACSHandle_t						acsHandle,
			InvokeID_t					invokeID,
			CONST_PARAM DeviceID_t		FAR	*device,
			Boolean							doNotDisturb,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaSetForwarding(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM DeviceID_t		FAR	*device,
			ForwardingType_t				forwardingType,
			Boolean							forwardingOn,
			CONST_PARAM DeviceID_t		FAR	*forwardingDestination,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaSetAgentState(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM DeviceID_t		FAR	*device,
			AgentMode_t						agentMode,
			CONST_PARAM AgentID_t		FAR	*agentID,
			CONST_PARAM AgentGroup_t	FAR	*agentGroup,
			CONST_PARAM AgentPassword_t	FAR	*agentPassword,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaQueryMsgWaitingInd(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM DeviceID_t		FAR	*device,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaQueryDoNotDisturb(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM DeviceID_t		FAR	*device,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaQueryForwarding(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM DeviceID_t		FAR	*device,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaQueryAgentState(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM DeviceID_t		FAR	*device,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaQueryLastNumber(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM DeviceID_t		FAR	*device,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaQueryDeviceInfo(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM DeviceID_t		FAR	*device,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	/* Monitor Services */

	TSAPI cstaMonitorDevice(ACSHandle_t							acsHandle,
			InvokeID_t							invokeID,
			CONST_PARAM DeviceID_t			FAR	*deviceID,
			CONST_PARAM CSTAMonitorFilter_t	FAR	*monitorFilter,
			CONST_PARAM PrivateData_t		FAR	*privateData);


	TSAPI cstaMonitorCall(ACSHandle_t							acsHandle,
			InvokeID_t							invokeID,
			CONST_PARAM ConnectionID_t		FAR	*call,
			CONST_PARAM CSTAMonitorFilter_t	FAR	*monitorFilter,
			CONST_PARAM PrivateData_t		FAR	*privateData);


	TSAPI cstaMonitorCallsViaDevice(ACSHandle_t							acsHandle,
			InvokeID_t							invokeID,
			CONST_PARAM DeviceID_t			FAR	*deviceID,
			CONST_PARAM CSTAMonitorFilter_t	FAR	*monitorFilter,
			CONST_PARAM PrivateData_t		FAR	*privateData);


	TSAPI cstaChangeMonitorFilter(ACSHandle_t							acsHandle,
			InvokeID_t							invokeID,
			CSTAMonitorCrossRefID_t				monitorCrossRefID,
			CONST_PARAM CSTAMonitorFilter_t	FAR	*filterlist,
			CONST_PARAM PrivateData_t		FAR	*privateData);


	TSAPI cstaMonitorStop(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CSTAMonitorCrossRefID_t			monitorCrossRefID,
			CONST_PARAM PrivateData_t	FAR	*privateData);

	/* Snapshot Services */

	TSAPI cstaSnapshotCallReq(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM ConnectionID_t	FAR	*snapshotObj,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaSnapshotDeviceReq(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM DeviceID_t		FAR	*snapshotObj,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	/* Routing Services */

	TSAPI cstaRouteRegisterReq(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM DeviceID_t		FAR	*routingDevice,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaRouteRegisterCancel(ACSHandle_t					acsHandle,
			InvokeID_t					invokeID,
			RouteRegisterReqID_t		routeRegisterReqID,
			CONST_PARAM PrivateData_t	FAR	*privateData);

	/* Release 1 calls, w/o invokeID, for backward compatibility */

	TSAPI cstaRouteSelect(ACSHandle_t						acsHandle,
			RouteRegisterReqID_t			routeRegisterReqID,
			RoutingCrossRefID_t				routingCrossRefID,
			CONST_PARAM DeviceID_t		FAR	*routeSelected,
			RetryValue_t					remainRetry,
			CONST_PARAM SetUpValues_t	FAR *setupInformation,
			Boolean							routeUsedReq,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaRouteEnd(ACSHandle_t						acsHandle,
			RouteRegisterReqID_t			routeRegisterReqID,
			RoutingCrossRefID_t				routingCrossRefID,
			CSTAUniversalFailure_t			errorValue,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	/* Release 2 calls, with invokeID */

	TSAPI cstaRouteSelectInv(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			RouteRegisterReqID_t			routeRegisterReqID,
			RoutingCrossRefID_t				routingCrossRefID,
			CONST_PARAM DeviceID_t		FAR	*routeSelected,
			RetryValue_t					remainRetry,
			CONST_PARAM SetUpValues_t	FAR *setupInformation,
			Boolean							routeUsedReq,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaRouteEndInv(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			RouteRegisterReqID_t			routeRegisterReqID,
			RoutingCrossRefID_t				routingCrossRefID,
			CSTAUniversalFailure_t			errorValue,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	/* Escape Services */

	TSAPI cstaEscapeService(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaEscapeServiceConf(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CSTAUniversalFailure_t			error,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaSendPrivateEvent(ACSHandle_t						acsHandle,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	/* Maintenance Services */

	TSAPI cstaSysStatReq(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaSysStatStart(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			SystemStatusFilter_t			statusFilter,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaSysStatStop(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaChangeSysStatFilter(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			SystemStatusFilter_t			statusFilter,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaSysStatReqConf(ACSHandle_t						acsHandle,
			InvokeID_t						invokeID,
			SystemStatus_t					systemStatus,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaSysStatEvent(ACSHandle_t						acsHandle,
			SystemStatus_t					systemStatus,
			CONST_PARAM PrivateData_t	FAR	*privateData);


	TSAPI cstaGetAPICaps(ACSHandle_t acsHandle, InvokeID_t invokeID);


	TSAPI cstaGetDeviceList(ACSHandle_t	acsHandle,
			InvokeID_t	invokeID,
			long		index,
			CSTALevel_t	level);


	TSAPI cstaQueryCallMonitor(ACSHandle_t acsHandle, InvokeID_t invokeID);

	TSAPI attMakeVersionString(CONST_PARAM char FAR *	requestedVersion,
			char FAR *				supportedVersion);

	/********* ATT Private Data Encoding Function *******/
	TSAPI encodePrivate(int						pdunum,
			CONST_PARAM void FAR *	pdu,
			ATTPrivateData_t FAR *	priv);

	/********* ATT Private Data Decoding Function *******/

	TSAPI attPrivateData(CONST_PARAM ATTPrivateData_t FAR *	privateData,
			ATTEvent_t FAR *					eventBuffer);


	/********* ATT Private Data Encoding Functions *******/

	TSAPI attClearConnection(ATTPrivateData_t FAR *					privateData,
			ATTDropResource_t						dropResource,
			CONST_PARAM ATTV5UserToUserInfo_t FAR *	userInfo);


	TSAPI attConsultationCall(ATTPrivateData_t FAR *					privateData,
			CONST_PARAM DeviceID_t FAR *			destRoute,
			Boolean									priorityCalling,
			CONST_PARAM ATTV5UserToUserInfo_t FAR *	userInfo);


	TSAPI attMakeCall(ATTPrivateData_t FAR *					privateData,
			CONST_PARAM DeviceID_t FAR *			destRoute,
			Boolean									priorityCalling,
			CONST_PARAM ATTV5UserToUserInfo_t	FAR *	userInfo);


	TSAPI attDirectAgentCall(ATTPrivateData_t FAR *					privateData,
			CONST_PARAM DeviceID_t FAR *			split,
			Boolean									priorityCalling,
			CONST_PARAM ATTV5UserToUserInfo_t	FAR *	userInfo);


	TSAPI attMakePredictiveCall(ATTPrivateData_t FAR *					privateData,
			Boolean									priorityCalling,
			short									maxRings,
			ATTAnswerTreat_t						answerTreat,
			CONST_PARAM DeviceID_t FAR *			destRoute,
			CONST_PARAM ATTV5UserToUserInfo_t FAR *	userInfo);


	TSAPI attSupervisorAssistCall(ATTPrivateData_t FAR *					privateData,
			CONST_PARAM DeviceID_t FAR *			split,
			CONST_PARAM ATTV5UserToUserInfo_t FAR *	userInfo);


	TSAPI attReconnectCall(ATTPrivateData_t FAR *					privateData,
			ATTDropResource_t						dropResource,
			CONST_PARAM ATTV5UserToUserInfo_t	FAR *	userInfo);


	TSAPI attSendDTMFTone(ATTPrivateData_t FAR *				privateData,
			CONST_PARAM ConnectionID_t FAR *	sender,
			CONST_PARAM ATTV4ConnIDList_t FAR *	receivers,
			CONST_PARAM char FAR *				tones,
			short								toneDuration,
			short								pauseDuration);


	TSAPI attSetAgentState(ATTPrivateData_t FAR *	privateData,
			ATTWorkMode_t			workMode);


	TSAPI attQueryAcdSplit(ATTPrivateData_t	FAR *		privateData,
			CONST_PARAM DeviceID_t FAR *	device);


	TSAPI attQueryAgentLogin(ATTPrivateData_t FAR *			privateData,
			CONST_PARAM DeviceID_t FAR *	device);


	TSAPI attQueryAgentState(ATTPrivateData_t FAR *			privateData,
			CONST_PARAM DeviceID_t FAR *	device);


	TSAPI attQueryCallClassifier(ATTPrivateData_t	FAR * privateData);


	TSAPI attQueryDeviceName(ATTPrivateData_t FAR *			privateData,
			CONST_PARAM DeviceID_t FAR *	device);

	TSAPI attQueryStationStatus(ATTPrivateData_t FAR *			privateData,
			CONST_PARAM DeviceID_t FAR *	device);


	TSAPI attQueryTimeOfDay(ATTPrivateData_t FAR *privateData);


	TSAPI attQueryTrunkGroup(ATTPrivateData_t FAR *			privateData,
			CONST_PARAM DeviceID_t FAR *	device);


	TSAPI attMonitorFilter(ATTPrivateData_t FAR *		privateData,
			ATTV4PrivateFilter_t		privateFilter);


	TSAPI attMonitorStopOnCall(ATTPrivateData_t FAR *				privateData,
			CSTAMonitorCrossRefID_t				monitorCrossRefID,
			CONST_PARAM ConnectionID_t FAR *	call);


	TSAPI attRouteSelect(ATTPrivateData_t FAR *					privateData,
			CONST_PARAM DeviceID_t FAR *			callingDevice,
			CONST_PARAM DeviceID_t FAR *			directAgentCallSplit,
			Boolean									priorityCalling,
			CONST_PARAM DeviceID_t FAR *			destRoute,
			CONST_PARAM ATTUserCollectCode_t FAR *	collectCode,
			CONST_PARAM ATTUserProvidedCode_t FAR *	userProvidedCode,
			CONST_PARAM ATTV5UserToUserInfo_t FAR *	userInfo);


	TSAPI attSysStat(ATTPrivateData_t FAR *	privateData,
			Boolean					linkStatusReq);


	TSAPI attSingleStepConferenceCall(ATTPrivateData_t FAR *			privateData,
			CONST_PARAM ConnectionID_t FAR *activeCall,
			CONST_PARAM DeviceID_t FAR *	deviceToBeJoin,
			ATTParticipationType_t			participationType,
			Boolean							alertDestination);


	TSAPI attSelectiveListeningHold(ATTPrivateData_t FAR *			privateData,
			CONST_PARAM ConnectionID_t FAR *	subjectConnection,
			Boolean								allParties,
			CONST_PARAM ConnectionID_t FAR *	selectedParty);


	TSAPI attSelectiveListeningRetrieve(ATTPrivateData_t FAR *		privateData,
			CONST_PARAM ConnectionID_t FAR *	subjectConnection,
			Boolean								allParties,
			CONST_PARAM ConnectionID_t FAR *	selectedParty);


	TSAPI attSetAgentStateExt(ATTPrivateData_t FAR*	privateData,
			ATTWorkMode_t			workMode,
			long					reasonCode);


	TSAPI attSetBillRate(ATTPrivateData_t FAR *				privateData,
			CONST_PARAM ConnectionID_t FAR *	call,
			ATTBillType_t						billType,
			float								billRate);


	TSAPI attQueryUCID(ATTPrivateData_t FAR *				privateData,
			CONST_PARAM ConnectionID_t FAR *	call);


	TSAPI attSetAdviceOfCharge(ATTPrivateData_t FAR * privateData, Boolean flag);


	TSAPI attSendDTMFToneExt(ATTPrivateData_t FAR *				privateData,
			CONST_PARAM ConnectionID_t FAR *	sender,
			CONST_PARAM ATTConnIDList_t FAR *	receivers,
			CONST_PARAM char FAR *				tones,
			short								toneDuration,
			short								pauseDuration);


	TSAPI attMonitorFilterExt(ATTPrivateData_t	FAR *	privateData,
			ATTPrivateFilter_t			privateFilter);

	/* V6 Private Data */

	TSAPI attV6SetAgentState(ATTPrivateData_t FAR*	privateData,
			ATTWorkMode_t			workMode,
			long					reasonCode,
			Boolean					enablePending);

	TSAPI attV6MakeCall(ATTPrivateData_t FAR *				privateData,
			CONST_PARAM DeviceID_t FAR *			destRoute,
			Boolean									priorityCalling,
			CONST_PARAM ATTUserToUserInfo_t	FAR *	userInfo);

	TSAPI attV6ClearConnection(ATTPrivateData_t FAR *				privateData,
			ATTDropResource_t						dropResource,
			CONST_PARAM ATTUserToUserInfo_t FAR *	userInfo);

	TSAPI attV6ConsultationCall(ATTPrivateData_t FAR *				privateData,
			CONST_PARAM DeviceID_t FAR *			destRoute,
			Boolean									priorityCalling,
			CONST_PARAM ATTUserToUserInfo_t FAR *	userInfo);

	TSAPI attV6DirectAgentCall(ATTPrivateData_t FAR *				privateData,
			CONST_PARAM DeviceID_t FAR *			split,
			Boolean									priorityCalling,
			CONST_PARAM ATTUserToUserInfo_t	FAR *	userInfo);

	TSAPI attV6MakePredictiveCall(ATTPrivateData_t FAR *				privateData,
			Boolean									priorityCalling,
			short									maxRings,
			ATTAnswerTreat_t						answerTreat,
			CONST_PARAM DeviceID_t FAR *			destRoute,
			CONST_PARAM ATTUserToUserInfo_t FAR *	userInfo);

	TSAPI attV6SupervisorAssistCall(ATTPrivateData_t FAR *				privateData,
			CONST_PARAM DeviceID_t FAR *			split,
			CONST_PARAM ATTUserToUserInfo_t FAR *	userInfo);

	TSAPI attV6ReconnectCall(ATTPrivateData_t FAR *					privateData,
			ATTDropResource_t						dropResource,
			CONST_PARAM ATTUserToUserInfo_t	FAR *	userInfo);

	TSAPI attV6RouteSelect(ATTPrivateData_t FAR *				privateData,
			CONST_PARAM DeviceID_t FAR *			callingDevice,
			CONST_PARAM DeviceID_t FAR *			directAgentCallSplit,
			Boolean									priorityCalling,
			CONST_PARAM DeviceID_t FAR *			destRoute,
			CONST_PARAM ATTUserCollectCode_t FAR *	collectCode,
			CONST_PARAM ATTUserProvidedCode_t FAR *	userProvidedCode,
			CONST_PARAM ATTUserToUserInfo_t FAR *	userInfo);

	TSAPI attV7RouteSelect(ATTPrivateData_t FAR *				privateData,
			CONST_PARAM DeviceID_t FAR *			callingDevice,
			CONST_PARAM DeviceID_t FAR *			directAgentCallSplit,
			Boolean									priorityCalling,
			CONST_PARAM DeviceID_t FAR *			destRoute,
			CONST_PARAM ATTUserCollectCode_t FAR *	collectCode,
			CONST_PARAM ATTUserProvidedCode_t FAR *	userProvidedCode,
			CONST_PARAM ATTUserToUserInfo_t FAR *	userInfo,
			CONST_PARAM ATTRedirectType_t			networkredirect);

	TSAPI attSingleStepTransferCall(ATTPrivateData_t FAR *	privateData,
			CONST_PARAM ConnectionID_t FAR *	activeCall,
			CONST_PARAM DeviceID_t FAR *		transferredTo);

	TSAPI attMonitorCallsViaDevice(ATTPrivateData_t FAR *	privateData,
			ATTPrivateFilter_t		privateFilter,
			Boolean					flowPredictiveCallEvents);

	void initATTPrivate(PrivateData_t FAR *priv);

	void addATTPrivate(UINT16 itemTag, void FAR *itemPtr, PrivateData_t FAR *priv);

	void *getATTPrivate(UINT16 tag, PrivateData_t FAR *priv, UINT16 occ);

	const char * cstaAgentStateString(AgentState_t agentState);
	const char * cstaAPICapsString(uint32_t api);
	const char * cstaConnectionIDDeviceTypeString(ConnectionID_Device_t type);
	ConnectionID_Device_t cstaStringConnectionIDDevice(const std::string & type);
	const char * cstaLocalConnectionStateString(LocalConnectionState_t localState);
	const char * cstaEventCauseString(CSTAEventCause_t cause);
	Json::Value  cstaConnectionIDJson(ConnectionID_t connectionId);
	const char * cstaDeviceIDStatusString(DeviceIDStatus_t deviceIDStatus);
	const char * cstaDeviceIDTypeString(DeviceIDType_t deviceIDType);
	bool InitAvayaAPI();
	bool UnInitAvayaAPI();
}

