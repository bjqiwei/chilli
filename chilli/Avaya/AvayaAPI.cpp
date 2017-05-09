#include "AvayaAPI.h"
#include <atomic>
#include "../Dynamiclibrary.h"


#if defined ( TSLIB_WINDOWS_32 )
#define TSAPIPROC           RetCode_t (pascal *
#elif defined ( TSLIB_LINUX )
#define TSAPIPROC           RetCode_t
#endif

//CSTA32

#ifdef __cplusplus
extern "C"
{
#endif  

	typedef TSAPIPROC Proc_acsOpenStream)(ACSHandle_t                     FAR *acsHandle,
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


	typedef TSAPIPROC Proc_acsCloseStream)(ACSHandle_t                     acsHandle,
	InvokeID_t                      invokeID,
		CONST_PARAM PrivateData_t   FAR *priv);


	typedef TSAPIPROC Proc_acsAbortStream)(ACSHandle_t                     acsHandle,
	CONST_PARAM PrivateData_t   FAR *priv);


	typedef TSAPIPROC Proc_acsFlushEventQueue)(ACSHandle_t                 acsHandle);


	typedef TSAPIPROC Proc_acsGetEventPoll)(ACSHandle_t                 acsHandle,
	void                    FAR *eventBuf,
		unsigned short          FAR *eventBufSize,
		PrivateData_t           FAR *privData,
		unsigned short          FAR *numEvents);


	typedef TSAPIPROC Proc_acsGetEventBlock)(ACSHandle_t                 acsHandle,
	void                    FAR *eventBuf,
		unsigned short          FAR *eventBufSize,
		PrivateData_t           FAR *privData,
		unsigned short          FAR *numEvents);

	/* 32-bit Windows-specific prototypes */

#if defined ( TSLIB_WINDOWS_32 )

	typedef TSAPIPROC Proc_acsEventNotify)(ACSHandle_t acsHandle, HWND hwnd, UINT msg, Boolean notifyAll);


	typedef TSAPIPROC Proc_acsSetESR)(ACSHandle_t     acsHandle,
	void            (far pascal *esr)(unsigned long esrParam),
		unsigned long   esrParam,
		Boolean         notifyAll);

	typedef Boolean(*EnumServerNamesCB) (char  *serverName,
		unsigned long lParam);

	/* Linux-specific prototypes */

#elif defined ( TSLIB_LINUX )

	typedef TSAPIPROC Proc_acsGetFile)(ACSHandle_t acsHandle);

	typedef Boolean(*EnumServerNamesCB) (char *serverName,
		unsigned long lParam);

#endif


	typedef TSAPIPROC Proc_acsEnumServerNames)(StreamType_t        streamType,
	EnumServerNamesCB   userCB,
		unsigned long       lParam);



	typedef TSAPIPROC Proc_acsQueryAuthInfo)(CONST_PARAM ServerID_t      FAR *serverID,
	ACSAuthInfo_t               FAR *authInfo);


	typedef TSAPIPROC Proc_acsGetServerID)(ACSHandle_t         acsHandle,
	ServerID_t          *serverID);

	typedef TSAPIPROC Proc_acsSetHeartbeatInterval)(ACSHandle_t             acsHandle,
	InvokeID_t              invokeID,
		unsigned short          heartbeatInterval,
		PrivateData_t           *privData);

	typedef const char *
		(*Proc_acsReturnCodeString)(RetCode_t returnCode);

	typedef const char *
		(*Proc_acsReturnCodeVerboseString)(RetCode_t returnCode);

	typedef const char *
		(*Proc_acsErrorString)(ACSUniversalFailure_t error);

#ifdef __cplusplus
}
#endif 

#ifdef __cplusplus
extern "C"
{
#endif

	/* Utility functions */

	typedef const char *
		(*Proc_cstaErrorString)(CSTAUniversalFailure_t error);

	/* Basic Call Control Services */

	typedef TSAPIPROC Proc_cstaAlternateCall)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM ConnectionID_t	FAR	*activeCall,
		CONST_PARAM ConnectionID_t	FAR	*otherCall,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaAnswerCall)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM ConnectionID_t	FAR	*alertingCall,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaCallCompletion)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		Feature_t						feature,
		CONST_PARAM ConnectionID_t	FAR	*call,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaClearCall)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM ConnectionID_t	FAR	*call,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaClearConnection)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM ConnectionID_t	FAR	*call,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaConferenceCall)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM ConnectionID_t	FAR	*heldCall,
		CONST_PARAM ConnectionID_t	FAR	*activeCall,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaConsultationCall)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM ConnectionID_t	FAR	*activeCall,
		CONST_PARAM DeviceID_t		FAR	*calledDevice,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaDeflectCall)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM ConnectionID_t	FAR	*deflectCall,
		CONST_PARAM DeviceID_t		FAR	*calledDevice,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaGroupPickupCall)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM ConnectionID_t	FAR	*deflectCall,
		CONST_PARAM DeviceID_t		FAR	*pickupDevice,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaHoldCall)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM ConnectionID_t	FAR	*activeCall,
		Boolean							reservation,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaMakeCall)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM DeviceID_t		FAR	*callingDevice,
		CONST_PARAM DeviceID_t		FAR	*calledDevice,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaMakePredictiveCall)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM DeviceID_t		FAR	*callingDevice,
		CONST_PARAM DeviceID_t		FAR	*calledDevice,
		AllocationState_t				allocationState,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaPickupCall)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM ConnectionID_t	FAR	*deflectCall,
		CONST_PARAM DeviceID_t		FAR	*calledDevice,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaReconnectCall)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM ConnectionID_t	FAR	*activeCall,
		CONST_PARAM ConnectionID_t	FAR	*heldCall,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaRetrieveCall)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM ConnectionID_t	FAR	*heldCall,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaTransferCall)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM ConnectionID_t	FAR	*heldCall,
		CONST_PARAM ConnectionID_t	FAR	*activeCall,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	/* Telephony Supplementary Services */

	typedef TSAPIPROC Proc_cstaSetMsgWaitingInd)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM DeviceID_t		FAR	*device,
		Boolean							messages,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaSetDoNotDisturb)(ACSHandle_t						acsHandle,
	InvokeID_t					invokeID,
		CONST_PARAM DeviceID_t		FAR	*device,
		Boolean							doNotDisturb,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaSetForwarding)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM DeviceID_t		FAR	*device,
		ForwardingType_t				forwardingType,
		Boolean							forwardingOn,
		CONST_PARAM DeviceID_t		FAR	*forwardingDestination,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaSetAgentState)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM DeviceID_t		FAR	*device,
		AgentMode_t						agentMode,
		CONST_PARAM AgentID_t		FAR	*agentID,
		CONST_PARAM AgentGroup_t	FAR	*agentGroup,
		CONST_PARAM AgentPassword_t	FAR	*agentPassword,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaQueryMsgWaitingInd)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM DeviceID_t		FAR	*device,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaQueryDoNotDisturb)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM DeviceID_t		FAR	*device,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaQueryForwarding)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM DeviceID_t		FAR	*device,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaQueryAgentState)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM DeviceID_t		FAR	*device,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaQueryLastNumber)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM DeviceID_t		FAR	*device,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaQueryDeviceInfo)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM DeviceID_t		FAR	*device,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	/* Monitor Services */

	typedef TSAPIPROC Proc_cstaMonitorDevice)(ACSHandle_t							acsHandle,
	InvokeID_t							invokeID,
		CONST_PARAM DeviceID_t			FAR	*deviceID,
		CONST_PARAM CSTAMonitorFilter_t	FAR	*monitorFilter,
		CONST_PARAM PrivateData_t		FAR	*privateData);


	typedef TSAPIPROC Proc_cstaMonitorCall)(ACSHandle_t							acsHandle,
	InvokeID_t							invokeID,
		CONST_PARAM ConnectionID_t		FAR	*call,
		CONST_PARAM CSTAMonitorFilter_t	FAR	*monitorFilter,
		CONST_PARAM PrivateData_t		FAR	*privateData);


	typedef TSAPIPROC Proc_cstaMonitorCallsViaDevice)(ACSHandle_t							acsHandle,
	InvokeID_t							invokeID,
		CONST_PARAM DeviceID_t			FAR	*deviceID,
		CONST_PARAM CSTAMonitorFilter_t	FAR	*monitorFilter,
		CONST_PARAM PrivateData_t		FAR	*privateData);


	typedef TSAPIPROC Proc_cstaChangeMonitorFilter)(ACSHandle_t							acsHandle,
	InvokeID_t							invokeID,
		CSTAMonitorCrossRefID_t				monitorCrossRefID,
		CONST_PARAM CSTAMonitorFilter_t	FAR	*filterlist,
		CONST_PARAM PrivateData_t		FAR	*privateData);


	typedef TSAPIPROC Proc_cstaMonitorStop)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CSTAMonitorCrossRefID_t			monitorCrossRefID,
		CONST_PARAM PrivateData_t	FAR	*privateData);

	/* Snapshot Services */

	typedef TSAPIPROC Proc_cstaSnapshotCallReq)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM ConnectionID_t	FAR	*snapshotObj,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaSnapshotDeviceReq)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM DeviceID_t		FAR	*snapshotObj,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	/* Routing Services */

	typedef TSAPIPROC Proc_cstaRouteRegisterReq)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM DeviceID_t		FAR	*routingDevice,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaRouteRegisterCancel)(ACSHandle_t					acsHandle,
	InvokeID_t					invokeID,
		RouteRegisterReqID_t		routeRegisterReqID,
		CONST_PARAM PrivateData_t	FAR	*privateData);

	/* Release 1 calls, w/o invokeID, for backward compatibility */

	typedef TSAPIPROC Proc_cstaRouteSelect)(ACSHandle_t						acsHandle,
	RouteRegisterReqID_t			routeRegisterReqID,
		RoutingCrossRefID_t				routingCrossRefID,
		CONST_PARAM DeviceID_t		FAR	*routeSelected,
		RetryValue_t					remainRetry,
		CONST_PARAM SetUpValues_t	FAR *setupInformation,
		Boolean							routeUsedReq,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaRouteEnd)(ACSHandle_t						acsHandle,
	RouteRegisterReqID_t			routeRegisterReqID,
		RoutingCrossRefID_t				routingCrossRefID,
		CSTAUniversalFailure_t			errorValue,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	/* Release 2 calls, with invokeID */

	typedef TSAPIPROC Proc_cstaRouteSelectInv)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		RouteRegisterReqID_t			routeRegisterReqID,
		RoutingCrossRefID_t				routingCrossRefID,
		CONST_PARAM DeviceID_t		FAR	*routeSelected,
		RetryValue_t					remainRetry,
		CONST_PARAM SetUpValues_t	FAR *setupInformation,
		Boolean							routeUsedReq,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaRouteEndInv)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		RouteRegisterReqID_t			routeRegisterReqID,
		RoutingCrossRefID_t				routingCrossRefID,
		CSTAUniversalFailure_t			errorValue,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	/* Escape Services */

	typedef TSAPIPROC Proc_cstaEscapeService)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaEscapeServiceConf)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CSTAUniversalFailure_t			error,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaSendPrivateEvent)(ACSHandle_t						acsHandle,
	CONST_PARAM PrivateData_t	FAR	*privateData);


	/* Maintenance Services */

	typedef TSAPIPROC Proc_cstaSysStatReq)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaSysStatStart)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		SystemStatusFilter_t			statusFilter,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaSysStatStop)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaChangeSysStatFilter)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		SystemStatusFilter_t			statusFilter,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaSysStatReqConf)(ACSHandle_t						acsHandle,
	InvokeID_t						invokeID,
		SystemStatus_t					systemStatus,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaSysStatEvent)(ACSHandle_t						acsHandle,
	SystemStatus_t					systemStatus,
		CONST_PARAM PrivateData_t	FAR	*privateData);


	typedef TSAPIPROC Proc_cstaGetAPICaps)(ACSHandle_t acsHandle, InvokeID_t invokeID);


	typedef TSAPIPROC Proc_cstaGetDeviceList)(ACSHandle_t	acsHandle,
	InvokeID_t	invokeID,
		long		index,
		CSTALevel_t	level);


	typedef TSAPIPROC Proc_cstaQueryCallMonitor)(ACSHandle_t acsHandle, InvokeID_t invokeID);


#ifdef __cplusplus
}
#endif

//CSTA32

//ATTPRV32
#ifdef __cplusplus
extern "C"
{
#endif

	typedef TSAPIPROC Proc_attMakeVersionString)(CONST_PARAM char FAR *	requestedVersion,
	char FAR *				supportedVersion);

	/********* ATT Private Data Encoding Function *******/
	typedef TSAPIPROC Proc_encodePrivate)(int						pdunum,
	CONST_PARAM void FAR *	pdu,
		ATTPrivateData_t FAR *	priv);

	/********* ATT Private Data Decoding Function *******/

	typedef TSAPIPROC Proc_attPrivateData)(CONST_PARAM ATTPrivateData_t FAR *	privateData,
	ATTEvent_t FAR *					eventBuffer);


	/********* ATT Private Data Encoding Functions *******/

	typedef TSAPIPROC Proc_attClearConnection)(ATTPrivateData_t FAR *					privateData,
	ATTDropResource_t						dropResource,
		CONST_PARAM ATTV5UserToUserInfo_t FAR *	userInfo);


	typedef TSAPIPROC Proc_attConsultationCall)(ATTPrivateData_t FAR *					privateData,
	CONST_PARAM DeviceID_t FAR *			destRoute,
		Boolean									priorityCalling,
		CONST_PARAM ATTV5UserToUserInfo_t FAR *	userInfo);


	typedef TSAPIPROC Proc_attMakeCall)(ATTPrivateData_t FAR *					privateData,
	CONST_PARAM DeviceID_t FAR *			destRoute,
		Boolean									priorityCalling,
		CONST_PARAM ATTV5UserToUserInfo_t	FAR *	userInfo);


	typedef TSAPIPROC Proc_attDirectAgentCall)(ATTPrivateData_t FAR *					privateData,
	CONST_PARAM DeviceID_t FAR *			split,
		Boolean									priorityCalling,
		CONST_PARAM ATTV5UserToUserInfo_t	FAR *	userInfo);


	typedef TSAPIPROC Proc_attMakePredictiveCall)(ATTPrivateData_t FAR *					privateData,
	Boolean									priorityCalling,
		short									maxRings,
		ATTAnswerTreat_t						answerTreat,
		CONST_PARAM DeviceID_t FAR *			destRoute,
		CONST_PARAM ATTV5UserToUserInfo_t FAR *	userInfo);


	typedef TSAPIPROC Proc_attSupervisorAssistCall)(ATTPrivateData_t FAR *					privateData,
	CONST_PARAM DeviceID_t FAR *			split,
		CONST_PARAM ATTV5UserToUserInfo_t FAR *	userInfo);


	typedef TSAPIPROC Proc_attReconnectCall)(ATTPrivateData_t FAR *					privateData,
	ATTDropResource_t						dropResource,
		CONST_PARAM ATTV5UserToUserInfo_t	FAR *	userInfo);


	typedef TSAPIPROC Proc_attSendDTMFTone)(ATTPrivateData_t FAR *				privateData,
	CONST_PARAM ConnectionID_t FAR *	sender,
		CONST_PARAM ATTV4ConnIDList_t FAR *	receivers,
		CONST_PARAM char FAR *				tones,
		short								toneDuration,
		short								pauseDuration);


	typedef TSAPIPROC Proc_attSetAgentState)(ATTPrivateData_t FAR *	privateData,
	ATTWorkMode_t			workMode);


	typedef TSAPIPROC Proc_attQueryAcdSplit)(ATTPrivateData_t	FAR *		privateData,
	CONST_PARAM DeviceID_t FAR *	device);


	typedef TSAPIPROC Proc_attQueryAgentLogin)(ATTPrivateData_t FAR *			privateData,
	CONST_PARAM DeviceID_t FAR *	device);


	typedef TSAPIPROC Proc_attQueryAgentState)(ATTPrivateData_t FAR *			privateData,
	CONST_PARAM DeviceID_t FAR *	device);


	typedef TSAPIPROC Proc_attQueryCallClassifier)(ATTPrivateData_t	FAR * privateData);


	typedef TSAPIPROC Proc_attQueryDeviceName)(ATTPrivateData_t FAR *			privateData,
	CONST_PARAM DeviceID_t FAR *	device);

	typedef TSAPIPROC Proc_attQueryStationStatus)(ATTPrivateData_t FAR *			privateData,
	CONST_PARAM DeviceID_t FAR *	device);


	typedef TSAPIPROC Proc_attQueryTimeOfDay)(ATTPrivateData_t FAR *privateData);


	typedef TSAPIPROC Proc_attQueryTrunkGroup)(ATTPrivateData_t FAR *			privateData,
	CONST_PARAM DeviceID_t FAR *	device);


	typedef TSAPIPROC Proc_attMonitorFilter)(ATTPrivateData_t FAR *		privateData,
	ATTV4PrivateFilter_t		privateFilter);


	typedef TSAPIPROC Proc_attMonitorStopOnCall)(ATTPrivateData_t FAR *				privateData,
	CSTAMonitorCrossRefID_t				monitorCrossRefID,
		CONST_PARAM ConnectionID_t FAR *	call);


	typedef TSAPIPROC Proc_attRouteSelect)(ATTPrivateData_t FAR *					privateData,
	CONST_PARAM DeviceID_t FAR *			callingDevice,
		CONST_PARAM DeviceID_t FAR *			directAgentCallSplit,
		Boolean									priorityCalling,
		CONST_PARAM DeviceID_t FAR *			destRoute,
		CONST_PARAM ATTUserCollectCode_t FAR *	collectCode,
		CONST_PARAM ATTUserProvidedCode_t FAR *	userProvidedCode,
		CONST_PARAM ATTV5UserToUserInfo_t FAR *	userInfo);


	typedef TSAPIPROC Proc_attSysStat)(ATTPrivateData_t FAR *	privateData,
	Boolean					linkStatusReq);


	typedef TSAPIPROC Proc_attSingleStepConferenceCall)(ATTPrivateData_t FAR *			privateData,
	CONST_PARAM ConnectionID_t FAR *activeCall,
		CONST_PARAM DeviceID_t FAR *	deviceToBeJoin,
		ATTParticipationType_t			participationType,
		Boolean							alertDestination);


	typedef TSAPIPROC Proc_attSelectiveListeningHold)(ATTPrivateData_t FAR *			privateData,
	CONST_PARAM ConnectionID_t FAR *	subjectConnection,
		Boolean								allParties,
		CONST_PARAM ConnectionID_t FAR *	selectedParty);


	typedef TSAPIPROC Proc_attSelectiveListeningRetrieve)(ATTPrivateData_t FAR *		privateData,
	CONST_PARAM ConnectionID_t FAR *	subjectConnection,
		Boolean								allParties,
		CONST_PARAM ConnectionID_t FAR *	selectedParty);


	typedef TSAPIPROC Proc_attSetAgentStateExt)(ATTPrivateData_t FAR*	privateData,
	ATTWorkMode_t			workMode,
		long					reasonCode);


	typedef TSAPIPROC Proc_attSetBillRate)(ATTPrivateData_t FAR *				privateData,
	CONST_PARAM ConnectionID_t FAR *	call,
		ATTBillType_t						billType,
		float								billRate);


	typedef TSAPIPROC Proc_attQueryUCID)(ATTPrivateData_t FAR *				privateData,
	CONST_PARAM ConnectionID_t FAR *	call);


	typedef TSAPIPROC Proc_attSetAdviceOfCharge)(ATTPrivateData_t FAR * privateData, Boolean flag);


	typedef TSAPIPROC Proc_attSendDTMFToneExt)(ATTPrivateData_t FAR *				privateData,
	CONST_PARAM ConnectionID_t FAR *	sender,
		CONST_PARAM ATTConnIDList_t FAR *	receivers,
		CONST_PARAM char FAR *				tones,
		short								toneDuration,
		short								pauseDuration);


	typedef TSAPIPROC Proc_attMonitorFilterExt)(ATTPrivateData_t	FAR *	privateData,
	ATTPrivateFilter_t			privateFilter);

	/* V6 Private Data */

	typedef TSAPIPROC Proc_attV6SetAgentState)(ATTPrivateData_t FAR*	privateData,
	ATTWorkMode_t			workMode,
		long					reasonCode,
		Boolean					enablePending);

	typedef TSAPIPROC Proc_attV6MakeCall)(ATTPrivateData_t FAR *				privateData,
	CONST_PARAM DeviceID_t FAR *			destRoute,
		Boolean									priorityCalling,
		CONST_PARAM ATTUserToUserInfo_t	FAR *	userInfo);

	typedef TSAPIPROC Proc_attV6ClearConnection)(ATTPrivateData_t FAR *				privateData,
	ATTDropResource_t						dropResource,
		CONST_PARAM ATTUserToUserInfo_t FAR *	userInfo);

	typedef TSAPIPROC Proc_attV6ConsultationCall)(ATTPrivateData_t FAR *				privateData,
	CONST_PARAM DeviceID_t FAR *			destRoute,
		Boolean									priorityCalling,
		CONST_PARAM ATTUserToUserInfo_t FAR *	userInfo);

	typedef TSAPIPROC Proc_attV6DirectAgentCall)(ATTPrivateData_t FAR *				privateData,
	CONST_PARAM DeviceID_t FAR *			split,
		Boolean									priorityCalling,
		CONST_PARAM ATTUserToUserInfo_t	FAR *	userInfo);

	typedef TSAPIPROC Proc_attV6MakePredictiveCall)(ATTPrivateData_t FAR *				privateData,
	Boolean									priorityCalling,
		short									maxRings,
		ATTAnswerTreat_t						answerTreat,
		CONST_PARAM DeviceID_t FAR *			destRoute,
		CONST_PARAM ATTUserToUserInfo_t FAR *	userInfo);

	typedef TSAPIPROC Proc_attV6SupervisorAssistCall)(ATTPrivateData_t FAR *				privateData,
	CONST_PARAM DeviceID_t FAR *			split,
		CONST_PARAM ATTUserToUserInfo_t FAR *	userInfo);

	typedef TSAPIPROC Proc_attV6ReconnectCall)(ATTPrivateData_t FAR *					privateData,
	ATTDropResource_t						dropResource,
		CONST_PARAM ATTUserToUserInfo_t	FAR *	userInfo);

	typedef TSAPIPROC Proc_attV6RouteSelect)(ATTPrivateData_t FAR *				privateData,
	CONST_PARAM DeviceID_t FAR *			callingDevice,
		CONST_PARAM DeviceID_t FAR *			directAgentCallSplit,
		Boolean									priorityCalling,
		CONST_PARAM DeviceID_t FAR *			destRoute,
		CONST_PARAM ATTUserCollectCode_t FAR *	collectCode,
		CONST_PARAM ATTUserProvidedCode_t FAR *	userProvidedCode,
		CONST_PARAM ATTUserToUserInfo_t FAR *	userInfo);

	typedef TSAPIPROC Proc_attV7RouteSelect)(ATTPrivateData_t FAR *				privateData,
	CONST_PARAM DeviceID_t FAR *			callingDevice,
		CONST_PARAM DeviceID_t FAR *			directAgentCallSplit,
		Boolean									priorityCalling,
		CONST_PARAM DeviceID_t FAR *			destRoute,
		CONST_PARAM ATTUserCollectCode_t FAR *	collectCode,
		CONST_PARAM ATTUserProvidedCode_t FAR *	userProvidedCode,
		CONST_PARAM ATTUserToUserInfo_t FAR *	userInfo,
		CONST_PARAM ATTRedirectType_t			networkredirect);

	typedef TSAPIPROC Proc_attSingleStepTransferCall)(ATTPrivateData_t FAR *	privateData,
	CONST_PARAM ConnectionID_t FAR *	activeCall,
		CONST_PARAM DeviceID_t FAR *		transferredTo);

	typedef TSAPIPROC Proc_attMonitorCallsViaDevice)(ATTPrivateData_t FAR *	privateData,
	ATTPrivateFilter_t		privateFilter,
		Boolean					flowPredictiveCallEvents);


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
extern "C"
{
#endif

#if defined _MSDOS || defined __MSDOS__
#define FPEXPORT	__far __pascal __export
#else
#define FPEXPORT
#endif

	typedef void
		FPEXPORT
		(*Proc_initATTPrivate)(PrivateData_t FAR *priv);

	typedef void
		FPEXPORT
		(*Proc_addATTPrivate)(UINT16 itemTag, void FAR *itemPtr, PrivateData_t FAR *priv);

	typedef void *
		FPEXPORT
		(*Proc_getATTPrivate)(UINT16 tag, PrivateData_t FAR *priv, UINT16 occ);

#ifdef __cplusplus
}
#endif

namespace AvayaAPI {
	static std::atomic_ulong  g_Reference = 0;

	Proc_acsOpenStream m_acsOpenStream = nullptr;
	Proc_acsCloseStream m_acsCloseStream = nullptr;
	Proc_acsAbortStream m_acsAbortStream = nullptr;
	Proc_acsFlushEventQueue m_acsFlushEventQueue = nullptr;
	Proc_acsGetEventPoll m_acsGetEventPoll = nullptr;
	Proc_acsGetEventBlock m_acsGetEventBlock = nullptr;
#if defined ( TSLIB_WINDOWS_32 )
	Proc_acsEventNotify m_acsEventNotify = nullptr;
	Proc_acsSetESR m_acsSetESR = nullptr;
#elif defined ( TSLIB_LINUX )
	Proc_acsGetFile m_acsGetFile = nullptr;
#endif
	Proc_acsEnumServerNames m_acsEnumServerNames = nullptr;
	Proc_acsQueryAuthInfo m_acsQueryAuthInfo = nullptr;
	Proc_acsGetServerID m_acsGetServerID = nullptr;
	Proc_acsSetHeartbeatInterval m_acsSetHeartbeatInterval = nullptr;
	Proc_acsReturnCodeString m_acsReturnCodeString = nullptr;
	Proc_acsReturnCodeVerboseString m_acsReturnCodeVerboseString = nullptr;
	Proc_acsErrorString m_acsErrorString = nullptr;
	Proc_cstaErrorString m_cstaErrorString = nullptr;
	Proc_cstaAlternateCall m_cstaAlternateCall = nullptr;
	Proc_cstaAnswerCall m_cstaAnswerCall = nullptr;
	Proc_cstaCallCompletion m_cstaCallCompletion = nullptr;
	Proc_cstaClearCall m_cstaClearCall = nullptr;
	Proc_cstaClearConnection m_cstaClearConnection = nullptr;
	Proc_cstaConferenceCall m_cstaConferenceCall = nullptr;
	Proc_cstaConsultationCall m_cstaConsultationCall = nullptr;
	Proc_cstaDeflectCall m_cstaDeflectCall = nullptr;
	Proc_cstaGroupPickupCall m_cstaGroupPickupCall = nullptr;
	Proc_cstaHoldCall m_cstaHoldCall = nullptr;
	Proc_cstaMakeCall m_cstaMakeCall = nullptr;
	Proc_cstaMakePredictiveCall m_cstaMakePredictiveCall = nullptr;
	Proc_cstaPickupCall m_cstaPickupCall = nullptr;
	Proc_cstaReconnectCall m_cstaReconnectCall = nullptr;
	Proc_cstaRetrieveCall m_cstaRetrieveCall = nullptr;
	Proc_cstaTransferCall m_cstaTransferCall = nullptr;
	Proc_cstaSetMsgWaitingInd m_cstaSetMsgWaitingInd = nullptr;
	Proc_cstaSetDoNotDisturb m_cstaSetDoNotDisturb = nullptr;
	Proc_cstaSetForwarding m_cstaSetForwarding = nullptr;
	Proc_cstaSetAgentState m_cstaSetAgentState = nullptr;
	Proc_cstaQueryMsgWaitingInd m_cstaQueryMsgWaitingInd = nullptr;
	Proc_cstaQueryDoNotDisturb m_cstaQueryDoNotDisturb = nullptr;
	Proc_cstaQueryForwarding m_cstaQueryForwarding = nullptr;
	Proc_cstaQueryAgentState m_cstaQueryAgentState = nullptr;
	Proc_cstaQueryLastNumber m_cstaQueryLastNumber = nullptr;
	Proc_cstaQueryDeviceInfo m_cstaQueryDeviceInfo = nullptr;
	Proc_cstaMonitorDevice m_cstaMonitorDevice = nullptr;
	Proc_cstaMonitorCall m_cstaMonitorCall = nullptr;
	Proc_cstaMonitorCallsViaDevice m_cstaMonitorCallsViaDevice = nullptr;
	Proc_cstaChangeMonitorFilter m_cstaChangeMonitorFilter = nullptr;
	Proc_cstaMonitorStop m_cstaMonitorStop = nullptr;
	Proc_cstaSnapshotCallReq m_cstaSnapshotCallReq = nullptr;
	Proc_cstaSnapshotDeviceReq m_cstaSnapshotDeviceReq = nullptr;
	Proc_cstaRouteRegisterReq m_cstaRouteRegisterReq = nullptr;
	Proc_cstaRouteRegisterCancel m_cstaRouteRegisterCancel = nullptr;
	Proc_cstaRouteSelect m_cstaRouteSelect = nullptr;
	Proc_cstaRouteEnd m_cstaRouteEnd = nullptr;
	Proc_cstaRouteSelectInv m_cstaRouteSelectInv = nullptr;
	Proc_cstaRouteEndInv m_cstaRouteEndInv = nullptr;
	Proc_cstaEscapeService m_cstaEscapeService = nullptr;
	Proc_cstaEscapeServiceConf m_cstaEscapeServiceConf = nullptr;
	Proc_cstaSendPrivateEvent m_cstaSendPrivateEvent = nullptr;
	Proc_cstaSysStatReq m_cstaSysStatReq = nullptr;
	Proc_cstaSysStatStart m_cstaSysStatStart = nullptr;
	Proc_cstaSysStatStop m_cstaSysStatStop = nullptr;
	Proc_cstaChangeSysStatFilter m_cstaChangeSysStatFilter = nullptr;
	Proc_cstaSysStatReqConf m_cstaSysStatReqConf = nullptr;
	Proc_cstaSysStatEvent m_cstaSysStatEvent = nullptr;
	Proc_cstaGetAPICaps m_cstaGetAPICaps = nullptr;
	Proc_cstaGetDeviceList m_cstaGetDeviceList = nullptr;
	Proc_cstaQueryCallMonitor m_cstaQueryCallMonitor = nullptr;
	Proc_attMakeVersionString m_attMakeVersionString = nullptr;
	Proc_encodePrivate m_encodePrivate = nullptr;
	Proc_attPrivateData m_attPrivateData = nullptr;
	Proc_attClearConnection m_attClearConnection = nullptr;
	Proc_attConsultationCall m_attConsultationCall = nullptr;
	Proc_attMakeCall m_attMakeCall = nullptr;
	Proc_attDirectAgentCall m_attDirectAgentCall = nullptr;
	Proc_attMakePredictiveCall m_attMakePredictiveCall = nullptr;
	Proc_attSupervisorAssistCall m_attSupervisorAssistCall = nullptr;
	Proc_attReconnectCall m_attReconnectCall = nullptr;
	Proc_attSendDTMFTone m_attSendDTMFTone = nullptr;
	Proc_attSetAgentState m_attSetAgentState = nullptr;
	Proc_attQueryAcdSplit m_attQueryAcdSplit = nullptr;
	Proc_attQueryAgentLogin m_attQueryAgentLogin = nullptr;
	Proc_attQueryAgentState m_attQueryAgentState = nullptr;
	Proc_attQueryCallClassifier m_attQueryCallClassifier = nullptr;
	Proc_attQueryDeviceName m_attQueryDeviceName = nullptr;
	Proc_attQueryStationStatus m_attQueryStationStatus = nullptr;
	Proc_attQueryTimeOfDay m_attQueryTimeOfDay = nullptr;
	Proc_attQueryTrunkGroup m_attQueryTrunkGroup = nullptr;
	Proc_attMonitorFilter m_attMonitorFilter = nullptr;
	Proc_attMonitorStopOnCall m_attMonitorStopOnCall = nullptr;
	Proc_attRouteSelect m_attRouteSelect = nullptr;
	Proc_attSysStat m_attSysStat = nullptr;
	Proc_attSingleStepConferenceCall m_attSingleStepConferenceCall = nullptr;
	Proc_attSelectiveListeningHold m_attSelectiveListeningHold = nullptr;
	Proc_attSelectiveListeningRetrieve m_attSelectiveListeningRetrieve = nullptr;
	Proc_attSetAgentStateExt m_attSetAgentStateExt = nullptr;
	Proc_attSetBillRate m_attSetBillRate = nullptr;
	Proc_attQueryUCID m_attQueryUCID = nullptr;
	Proc_attSetAdviceOfCharge m_attSetAdviceOfCharge = nullptr;
	Proc_attSendDTMFToneExt m_attSendDTMFToneExt = nullptr;
	Proc_attMonitorFilterExt m_attMonitorFilterExt = nullptr;
	Proc_attV6SetAgentState m_attV6SetAgentState = nullptr;
	Proc_attV6MakeCall m_attV6MakeCall = nullptr;
	Proc_attV6ClearConnection m_attV6ClearConnection = nullptr;
	Proc_attV6ConsultationCall m_attV6ConsultationCall = nullptr;
	Proc_attV6DirectAgentCall m_attV6DirectAgentCall = nullptr;
	Proc_attV6MakePredictiveCall m_attV6MakePredictiveCall = nullptr;
	Proc_attV6SupervisorAssistCall m_attV6SupervisorAssistCall = nullptr;
	Proc_attV6ReconnectCall m_attV6ReconnectCall = nullptr;
	Proc_attV6RouteSelect m_attV6RouteSelect = nullptr;
	Proc_attV7RouteSelect m_attV7RouteSelect = nullptr;
	Proc_attSingleStepTransferCall m_attSingleStepTransferCall = nullptr;
	Proc_attMonitorCallsViaDevice m_attMonitorCallsViaDevice = nullptr;
	Proc_initATTPrivate m_initATTPrivate = nullptr;
	Proc_addATTPrivate m_addATTPrivate = nullptr;
	Proc_getATTPrivate m_getATTPrivate = nullptr;

	static Dynamiclibrary CSTA32("CSTA32.DLL");
	static Dynamiclibrary ATTPRV32("ATTPRV32.DLL");

	const char * cstaErrorString(CSTAUniversalFailure_t error)
	{
		if (m_cstaErrorString) {
			return m_cstaErrorString(error);
		}
		static std::string err;
		err = std::to_string(error);
		return err.c_str();
	}

	TSAPI cstaAlternateCall(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM ConnectionID_t * activeCall, CONST_PARAM ConnectionID_t * otherCall, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaAlternateCall(acsHandle, invokeID, activeCall, otherCall, privateData);
	}

	TSAPI cstaAnswerCall(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM ConnectionID_t * alertingCall, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaAnswerCall(acsHandle, invokeID, alertingCall, privateData);
	}

	TSAPI cstaCallCompletion(ACSHandle_t acsHandle, InvokeID_t invokeID, Feature_t feature, CONST_PARAM ConnectionID_t * call, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaCallCompletion(acsHandle, invokeID, feature, call, privateData);
	}

	TSAPI cstaClearCall(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM ConnectionID_t * call, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaClearCall(acsHandle, invokeID, call, privateData);
	}

	TSAPI cstaClearConnection(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM ConnectionID_t * call, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaClearConnection(acsHandle, invokeID, call, privateData);
	}

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
			m_acsOpenStream = (Proc_acsOpenStream)CSTA32.GetFunction("acsOpenStream");
			m_acsCloseStream = (Proc_acsCloseStream)CSTA32.GetFunction("acsCloseStream");
			m_acsAbortStream = (Proc_acsAbortStream)CSTA32.GetFunction("acsAbortStream");
			m_acsFlushEventQueue = (Proc_acsFlushEventQueue)CSTA32.GetFunction("acsFlushEventQueue");
			m_acsGetEventPoll = (Proc_acsGetEventPoll)CSTA32.GetFunction("acsGetEventPoll");
			m_acsGetEventBlock = (Proc_acsGetEventBlock)CSTA32.GetFunction("acsGetEventBlock");
#if defined ( TSLIB_WINDOWS_32 )
			m_acsEventNotify = (Proc_acsEventNotify)CSTA32.GetFunction("acsEventNotify");
			m_acsSetESR = (Proc_acsSetESR)CSTA32.GetFunction("acsSetESR");
#elif defined ( TSLIB_LINUX )
			m_acsGetFile = (Proc_acsGetFile)CSTA32.GetFunction("acsGetFile");
#endif
			m_acsEnumServerNames = (Proc_acsEnumServerNames)CSTA32.GetFunction("acsEnumServerNames");
			m_acsQueryAuthInfo = (Proc_acsQueryAuthInfo)CSTA32.GetFunction("acsQueryAuthInfo");
			m_acsGetServerID = (Proc_acsGetServerID)CSTA32.GetFunction("acsGetServerID");
			m_acsSetHeartbeatInterval = (Proc_acsSetHeartbeatInterval)CSTA32.GetFunction("acsSetHeartbeatInterval");
			m_acsReturnCodeString = (Proc_acsReturnCodeString)CSTA32.GetFunction("acsReturnCodeString");
			m_acsReturnCodeVerboseString = (Proc_acsReturnCodeVerboseString)CSTA32.GetFunction("acsReturnCodeVerboseString");
			m_acsErrorString = (Proc_acsErrorString)CSTA32.GetFunction("acsErrorString");
			m_cstaErrorString = (Proc_cstaErrorString)CSTA32.GetFunction("cstaErrorString");
			m_cstaAlternateCall = (Proc_cstaAlternateCall)CSTA32.GetFunction("cstaAlternateCall");
			m_cstaAnswerCall = (Proc_cstaAnswerCall)CSTA32.GetFunction("cstaAnswerCall");
			m_cstaCallCompletion = (Proc_cstaCallCompletion)CSTA32.GetFunction("cstaCallCompletion");
			m_cstaClearCall = (Proc_cstaClearCall)CSTA32.GetFunction("cstaClearCall");
			m_cstaClearConnection = (Proc_cstaClearConnection)CSTA32.GetFunction("cstaClearConnection");
			m_cstaConferenceCall = (Proc_cstaConferenceCall)CSTA32.GetFunction("cstaConferenceCall");
			m_cstaConsultationCall = (Proc_cstaConsultationCall)CSTA32.GetFunction("cstaConsultationCall");
			m_cstaDeflectCall = (Proc_cstaDeflectCall)CSTA32.GetFunction("cstaDeflectCall");
			m_cstaGroupPickupCall = (Proc_cstaGroupPickupCall)CSTA32.GetFunction("cstaGroupPickupCall");
			m_cstaHoldCall = (Proc_cstaHoldCall)CSTA32.GetFunction("cstaHoldCall");
			m_cstaMakeCall = (Proc_cstaMakeCall)CSTA32.GetFunction("cstaMakeCall");
			m_cstaMakePredictiveCall = (Proc_cstaMakePredictiveCall)CSTA32.GetFunction("cstaMakePredictiveCall");
			m_cstaPickupCall = (Proc_cstaPickupCall)CSTA32.GetFunction("cstaPickupCall");
			m_cstaReconnectCall = (Proc_cstaReconnectCall)CSTA32.GetFunction("cstaReconnectCall");
			m_cstaRetrieveCall = (Proc_cstaRetrieveCall)CSTA32.GetFunction("cstaRetrieveCall");
			m_cstaTransferCall = (Proc_cstaTransferCall)CSTA32.GetFunction("cstaTransferCall");
			m_cstaSetMsgWaitingInd = (Proc_cstaSetMsgWaitingInd)CSTA32.GetFunction("cstaSetMsgWaitingInd");
			m_cstaSetDoNotDisturb = (Proc_cstaSetDoNotDisturb)CSTA32.GetFunction("cstaSetDoNotDisturb");
			m_cstaSetForwarding = (Proc_cstaSetForwarding)CSTA32.GetFunction("cstaSetForwarding");
			m_cstaSetAgentState = (Proc_cstaSetAgentState)CSTA32.GetFunction("cstaSetAgentState");
			m_cstaQueryMsgWaitingInd = (Proc_cstaQueryMsgWaitingInd)CSTA32.GetFunction("cstaQueryMsgWaitingInd");
			m_cstaQueryDoNotDisturb = (Proc_cstaQueryDoNotDisturb)CSTA32.GetFunction("cstaQueryDoNotDisturb");
			m_cstaQueryForwarding = (Proc_cstaQueryForwarding)CSTA32.GetFunction("cstaQueryForwarding");
			m_cstaQueryAgentState = (Proc_cstaQueryAgentState)CSTA32.GetFunction("cstaQueryAgentState");
			m_cstaQueryLastNumber = (Proc_cstaQueryLastNumber)CSTA32.GetFunction("cstaQueryLastNumber");
			m_cstaQueryDeviceInfo = (Proc_cstaQueryDeviceInfo)CSTA32.GetFunction("cstaQueryDeviceInfo");
			m_cstaMonitorDevice = (Proc_cstaMonitorDevice)CSTA32.GetFunction("cstaMonitorDevice");
			m_cstaMonitorCall = (Proc_cstaMonitorCall)CSTA32.GetFunction("cstaMonitorCall");
			m_cstaMonitorCallsViaDevice = (Proc_cstaMonitorCallsViaDevice)CSTA32.GetFunction("cstaMonitorCallsViaDevice");
			m_cstaChangeMonitorFilter = (Proc_cstaChangeMonitorFilter)CSTA32.GetFunction("cstaChangeMonitorFilter");
			m_cstaMonitorStop = (Proc_cstaMonitorStop)CSTA32.GetFunction("cstaMonitorStop");
			m_cstaSnapshotCallReq = (Proc_cstaSnapshotCallReq)CSTA32.GetFunction("cstaSnapshotCallReq");
			m_cstaSnapshotDeviceReq = (Proc_cstaSnapshotDeviceReq)CSTA32.GetFunction("cstaSnapshotDeviceReq");
			m_cstaRouteRegisterReq = (Proc_cstaRouteRegisterReq)CSTA32.GetFunction("cstaRouteRegisterReq");
			m_cstaRouteRegisterCancel = (Proc_cstaRouteRegisterCancel)CSTA32.GetFunction("cstaRouteRegisterCancel");
			m_cstaRouteSelect = (Proc_cstaRouteSelect)CSTA32.GetFunction("cstaRouteSelect");
			m_cstaRouteEnd = (Proc_cstaRouteEnd)CSTA32.GetFunction("cstaRouteEnd");
			m_cstaRouteSelectInv = (Proc_cstaRouteSelectInv)CSTA32.GetFunction("cstaRouteSelectInv");
			m_cstaRouteEndInv = (Proc_cstaRouteEndInv)CSTA32.GetFunction("cstaRouteEndInv");
			m_cstaEscapeService = (Proc_cstaEscapeService)CSTA32.GetFunction("cstaEscapeService");
			m_cstaEscapeServiceConf = (Proc_cstaEscapeServiceConf)CSTA32.GetFunction("cstaEscapeServiceConf");
			m_cstaSendPrivateEvent = (Proc_cstaSendPrivateEvent)CSTA32.GetFunction("cstaSendPrivateEvent");
			m_cstaSysStatReq = (Proc_cstaSysStatReq)CSTA32.GetFunction("cstaSysStatReq");
			m_cstaSysStatStart = (Proc_cstaSysStatStart)CSTA32.GetFunction("cstaSysStatStart");
			m_cstaSysStatStop = (Proc_cstaSysStatStop)CSTA32.GetFunction("cstaSysStatStop");
			m_cstaChangeSysStatFilter = (Proc_cstaChangeSysStatFilter)CSTA32.GetFunction("cstaChangeSysStatFilter");
			m_cstaSysStatReqConf = (Proc_cstaSysStatReqConf)CSTA32.GetFunction("cstaSysStatReqConf");
			m_cstaSysStatEvent = (Proc_cstaSysStatEvent)CSTA32.GetFunction("cstaSysStatEvent");
			m_cstaGetAPICaps = (Proc_cstaGetAPICaps)CSTA32.GetFunction("cstaGetAPICaps");
			m_cstaGetDeviceList = (Proc_cstaGetDeviceList)CSTA32.GetFunction("cstaGetDeviceList");
			m_cstaQueryCallMonitor = (Proc_cstaQueryCallMonitor)CSTA32.GetFunction("cstaQueryCallMonitor");
			
			if (!ATTPRV32.Open()) {
				return false;
			}

			m_attMakeVersionString = (Proc_attMakeVersionString)ATTPRV32.GetFunction("attMakeVersionString");
			m_encodePrivate = (Proc_encodePrivate)ATTPRV32.GetFunction("encodePrivate");
			m_attPrivateData = (Proc_attPrivateData)ATTPRV32.GetFunction("attPrivateData");
			m_attClearConnection = (Proc_attClearConnection)ATTPRV32.GetFunction("attClearConnection");
			m_attConsultationCall = (Proc_attConsultationCall)ATTPRV32.GetFunction("attConsultationCall");
			m_attMakeCall = (Proc_attMakeCall)ATTPRV32.GetFunction("attMakeCall");
			m_attDirectAgentCall = (Proc_attDirectAgentCall)ATTPRV32.GetFunction("attDirectAgentCall");
			m_attMakePredictiveCall = (Proc_attMakePredictiveCall)ATTPRV32.GetFunction("attMakePredictiveCall");
			m_attSupervisorAssistCall = (Proc_attSupervisorAssistCall)ATTPRV32.GetFunction("attSupervisorAssistCall");
			m_attReconnectCall = (Proc_attReconnectCall)ATTPRV32.GetFunction("attReconnectCall");
			m_attSendDTMFTone = (Proc_attSendDTMFTone)ATTPRV32.GetFunction("attSendDTMFTone");
			m_attSetAgentState = (Proc_attSetAgentState)ATTPRV32.GetFunction("attSetAgentState");
			m_attQueryAcdSplit = (Proc_attQueryAcdSplit)ATTPRV32.GetFunction("attQueryAcdSplit");
			m_attQueryAgentLogin = (Proc_attQueryAgentLogin)ATTPRV32.GetFunction("attQueryAgentLogin");
			m_attQueryAgentState = (Proc_attQueryAgentState)ATTPRV32.GetFunction("attQueryAgentState");
			m_attQueryCallClassifier = (Proc_attQueryCallClassifier)ATTPRV32.GetFunction("attQueryCallClassifier");
			m_attQueryDeviceName = (Proc_attQueryDeviceName)ATTPRV32.GetFunction("attQueryDeviceName");
			m_attQueryStationStatus = (Proc_attQueryStationStatus)ATTPRV32.GetFunction("attQueryStationStatus");
			m_attQueryTimeOfDay = (Proc_attQueryTimeOfDay)ATTPRV32.GetFunction("attQueryTimeOfDay");
			m_attQueryTrunkGroup = (Proc_attQueryTrunkGroup)ATTPRV32.GetFunction("attQueryTrunkGroup");
			m_attMonitorFilter = (Proc_attMonitorFilter)ATTPRV32.GetFunction("attMonitorFilter");
			m_attMonitorStopOnCall = (Proc_attMonitorStopOnCall)ATTPRV32.GetFunction("attMonitorStopOnCall");
			m_attRouteSelect = (Proc_attRouteSelect)ATTPRV32.GetFunction("attRouteSelect");
			m_attSysStat = (Proc_attSysStat)ATTPRV32.GetFunction("attSysStat");
			m_attSingleStepConferenceCall = (Proc_attSingleStepConferenceCall)ATTPRV32.GetFunction("attSingleStepConferenceCall");
			m_attSelectiveListeningHold = (Proc_attSelectiveListeningHold)ATTPRV32.GetFunction("attSelectiveListeningHold");
			m_attSelectiveListeningRetrieve = (Proc_attSelectiveListeningRetrieve)ATTPRV32.GetFunction("attSelectiveListeningRetrieve");
			m_attSetAgentStateExt = (Proc_attSetAgentStateExt)ATTPRV32.GetFunction("attSetAgentStateExt");
			m_attSetBillRate = (Proc_attSetBillRate)ATTPRV32.GetFunction("attSetBillRate");
			m_attQueryUCID = (Proc_attQueryUCID)ATTPRV32.GetFunction("attQueryUCID");
			m_attSetAdviceOfCharge = (Proc_attSetAdviceOfCharge)ATTPRV32.GetFunction("attSetAdviceOfCharge");
			m_attSendDTMFToneExt = (Proc_attSendDTMFToneExt)ATTPRV32.GetFunction("attSendDTMFToneExt");
			m_attMonitorFilterExt = (Proc_attMonitorFilterExt)ATTPRV32.GetFunction("attMonitorFilterExt");
			m_attV6SetAgentState = (Proc_attV6SetAgentState)ATTPRV32.GetFunction("attV6SetAgentState");
			m_attV6MakeCall = (Proc_attV6MakeCall)ATTPRV32.GetFunction("attV6MakeCall");
			m_attV6ClearConnection = (Proc_attV6ClearConnection)ATTPRV32.GetFunction("attV6ClearConnection");
			m_attV6ConsultationCall = (Proc_attV6ConsultationCall)ATTPRV32.GetFunction("attV6ConsultationCall");
			m_attV6DirectAgentCall = (Proc_attV6DirectAgentCall)ATTPRV32.GetFunction("attV6DirectAgentCall");
			m_attV6MakePredictiveCall = (Proc_attV6MakePredictiveCall)ATTPRV32.GetFunction("attV6MakePredictiveCall");
			m_attV6SupervisorAssistCall = (Proc_attV6SupervisorAssistCall)ATTPRV32.GetFunction("attV6SupervisorAssistCall");
			m_attV6ReconnectCall = (Proc_attV6ReconnectCall)ATTPRV32.GetFunction("attV6ReconnectCall");
			m_attV6RouteSelect = (Proc_attV6RouteSelect)ATTPRV32.GetFunction("attV6RouteSelect");
			m_attV7RouteSelect = (Proc_attV7RouteSelect)ATTPRV32.GetFunction("attV7RouteSelect");
			m_attSingleStepTransferCall = (Proc_attSingleStepTransferCall)ATTPRV32.GetFunction("attSingleStepTransferCall");
			m_attMonitorCallsViaDevice = (Proc_attMonitorCallsViaDevice)ATTPRV32.GetFunction("attMonitorCallsViaDevice");
			m_initATTPrivate = (Proc_initATTPrivate)ATTPRV32.GetFunction("initATTPrivate");
			m_addATTPrivate = (Proc_addATTPrivate)ATTPRV32.GetFunction("addATTPrivate");
			m_getATTPrivate = (Proc_getATTPrivate)ATTPRV32.GetFunction("getATTPrivate");
		}
		return true;
	}

	bool UnInitAvayaAPI()
	{
		if (g_Reference.fetch_sub(1) == 1) {
			m_acsOpenStream = nullptr;
			m_acsCloseStream = nullptr;
			m_acsAbortStream = nullptr;
			m_acsFlushEventQueue = nullptr;
			m_acsGetEventPoll = nullptr;
			m_acsGetEventBlock = nullptr;
#if defined ( TSLIB_WINDOWS_32 )
			m_acsEventNotify = nullptr;
			m_acsSetESR = nullptr;
#elif defined ( TSLIB_LINUX )
			m_acsGetFile = nullptr;
#endif
			m_acsEnumServerNames = nullptr;
			m_acsQueryAuthInfo = nullptr;
			m_acsGetServerID = nullptr;
			m_acsSetHeartbeatInterval = nullptr;
			m_acsReturnCodeString = nullptr;
			m_acsReturnCodeVerboseString = nullptr;
			m_acsErrorString = nullptr;
			m_cstaErrorString = nullptr;
			m_cstaAlternateCall = nullptr;
			m_cstaAnswerCall = nullptr;
			m_cstaCallCompletion = nullptr;
			m_cstaClearCall = nullptr;
			m_cstaClearConnection = nullptr;
			m_cstaConferenceCall = nullptr;
			m_cstaConsultationCall = nullptr;
			m_cstaDeflectCall = nullptr;
			m_cstaGroupPickupCall = nullptr;
			m_cstaHoldCall = nullptr;
			m_cstaMakeCall = nullptr;
			m_cstaMakePredictiveCall = nullptr;
			m_cstaPickupCall = nullptr;
			m_cstaReconnectCall = nullptr;
			m_cstaRetrieveCall = nullptr;
			m_cstaTransferCall = nullptr;
			m_cstaSetMsgWaitingInd = nullptr;
			m_cstaSetDoNotDisturb = nullptr;
			m_cstaSetForwarding = nullptr;
			m_cstaSetAgentState = nullptr;
			m_cstaQueryMsgWaitingInd = nullptr;
			m_cstaQueryDoNotDisturb = nullptr;
			m_cstaQueryForwarding = nullptr;
			m_cstaQueryAgentState = nullptr;
			m_cstaQueryLastNumber = nullptr;
			m_cstaQueryDeviceInfo = nullptr;
			m_cstaMonitorDevice = nullptr;
			m_cstaMonitorCall = nullptr;
			m_cstaMonitorCallsViaDevice = nullptr;
			m_cstaChangeMonitorFilter = nullptr;
			m_cstaMonitorStop = nullptr;
			m_cstaSnapshotCallReq = nullptr;
			m_cstaSnapshotDeviceReq = nullptr;
			m_cstaRouteRegisterReq = nullptr;
			m_cstaRouteRegisterCancel = nullptr;
			m_cstaRouteSelect = nullptr;
			m_cstaRouteEnd = nullptr;
			m_cstaRouteSelectInv = nullptr;
			m_cstaRouteEndInv = nullptr;
			m_cstaEscapeService = nullptr;
			m_cstaEscapeServiceConf = nullptr;
			m_cstaSendPrivateEvent = nullptr;
			m_cstaSysStatReq = nullptr;
			m_cstaSysStatStart = nullptr;
			m_cstaSysStatStop = nullptr;
			m_cstaChangeSysStatFilter = nullptr;
			m_cstaSysStatReqConf = nullptr;
			m_cstaSysStatEvent = nullptr;
			m_cstaGetAPICaps = nullptr;
			m_cstaGetDeviceList = nullptr;
			m_cstaQueryCallMonitor = nullptr;
			m_attMakeVersionString = nullptr;
			m_encodePrivate = nullptr;
			m_attPrivateData = nullptr;
			m_attClearConnection = nullptr;
			m_attConsultationCall = nullptr;
			m_attMakeCall = nullptr;
			m_attDirectAgentCall = nullptr;
			m_attMakePredictiveCall = nullptr;
			m_attSupervisorAssistCall = nullptr;
			m_attReconnectCall = nullptr;
			m_attSendDTMFTone = nullptr;
			m_attSetAgentState = nullptr;
			m_attQueryAcdSplit = nullptr;
			m_attQueryAgentLogin = nullptr;
			m_attQueryAgentState = nullptr;
			m_attQueryCallClassifier = nullptr;
			m_attQueryDeviceName = nullptr;
			m_attQueryStationStatus = nullptr;
			m_attQueryTimeOfDay = nullptr;
			m_attQueryTrunkGroup = nullptr;
			m_attMonitorFilter = nullptr;
			m_attMonitorStopOnCall = nullptr;
			m_attRouteSelect = nullptr;
			m_attSysStat = nullptr;
			m_attSingleStepConferenceCall = nullptr;
			m_attSelectiveListeningHold = nullptr;
			m_attSelectiveListeningRetrieve = nullptr;
			m_attSetAgentStateExt = nullptr;
			m_attSetBillRate = nullptr;
			m_attQueryUCID = nullptr;
			m_attSetAdviceOfCharge = nullptr;
			m_attSendDTMFToneExt = nullptr;
			m_attMonitorFilterExt = nullptr;
			m_attV6SetAgentState = nullptr;
			m_attV6MakeCall = nullptr;
			m_attV6ClearConnection = nullptr;
			m_attV6ConsultationCall = nullptr;
			m_attV6DirectAgentCall = nullptr;
			m_attV6MakePredictiveCall = nullptr;
			m_attV6SupervisorAssistCall = nullptr;
			m_attV6ReconnectCall = nullptr;
			m_attV6RouteSelect = nullptr;
			m_attV7RouteSelect = nullptr;
			m_attSingleStepTransferCall = nullptr;
			m_attMonitorCallsViaDevice = nullptr;
			m_initATTPrivate = nullptr;
			m_addATTPrivate = nullptr;
			m_getATTPrivate = nullptr;

			//ATTPRV32.Close();
			//CSTA32.Close();
		}
		
		return true;
	}
	TSAPI cstaConferenceCall(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM ConnectionID_t * heldCall, CONST_PARAM ConnectionID_t * activeCall, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaConferenceCall(acsHandle,invokeID, heldCall, activeCall, privateData);
	}
	TSAPI cstaConsultationCall(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM ConnectionID_t * activeCall, CONST_PARAM DeviceID_t * calledDevice, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaConsultationCall(acsHandle, invokeID, activeCall, calledDevice, privateData);
	}
	TSAPI cstaDeflectCall(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM ConnectionID_t * deflectCall, CONST_PARAM DeviceID_t * calledDevice, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaDeflectCall(acsHandle, invokeID, deflectCall, calledDevice, privateData);
	}
	TSAPI cstaGroupPickupCall(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM ConnectionID_t * deflectCall, CONST_PARAM DeviceID_t * pickupDevice, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaGroupPickupCall(acsHandle, invokeID, deflectCall, pickupDevice, privateData);
	}
	TSAPI cstaHoldCall(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM ConnectionID_t * activeCall, Boolean reservation, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaHoldCall(acsHandle, invokeID, activeCall, reservation, privateData);
	}
	TSAPI cstaMakeCall(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM DeviceID_t * callingDevice, CONST_PARAM DeviceID_t * calledDevice, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaMakeCall(acsHandle, invokeID, callingDevice, calledDevice, privateData);
	}
	TSAPI cstaMakePredictiveCall(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM DeviceID_t * callingDevice, CONST_PARAM DeviceID_t * calledDevice, AllocationState_t allocationState, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaMakePredictiveCall(acsHandle, invokeID, callingDevice, calledDevice, allocationState, privateData);
	}
	TSAPI cstaPickupCall(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM ConnectionID_t * deflectCall, CONST_PARAM DeviceID_t * calledDevice, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaPickupCall(acsHandle, invokeID, deflectCall, calledDevice, privateData);
	}
	TSAPI cstaReconnectCall(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM ConnectionID_t * activeCall, CONST_PARAM ConnectionID_t * heldCall, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaReconnectCall(acsHandle, invokeID, activeCall, heldCall, privateData);
	}
	TSAPI cstaRetrieveCall(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM ConnectionID_t * heldCall, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaRetrieveCall(acsHandle, invokeID, heldCall, privateData);
	}
	TSAPI cstaTransferCall(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM ConnectionID_t * heldCall, CONST_PARAM ConnectionID_t * activeCall, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaTransferCall(acsHandle, invokeID, heldCall, activeCall, privateData);
	}
	TSAPI cstaSetMsgWaitingInd(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM DeviceID_t * device, Boolean messages, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaSetMsgWaitingInd(acsHandle, invokeID, device, messages, privateData);
	}
	TSAPI cstaSetDoNotDisturb(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM DeviceID_t * device, Boolean doNotDisturb, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaSetDoNotDisturb(acsHandle, invokeID, device, doNotDisturb, privateData);
	}
	TSAPI cstaSetForwarding(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM DeviceID_t * device, ForwardingType_t forwardingType, Boolean forwardingOn, CONST_PARAM DeviceID_t * forwardingDestination, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaSetForwarding(acsHandle, invokeID, device, forwardingType, forwardingOn, forwardingDestination, privateData);
	}
	TSAPI cstaSetAgentState(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM DeviceID_t * device, AgentMode_t agentMode, CONST_PARAM AgentID_t * agentID, CONST_PARAM AgentGroup_t * agentGroup, CONST_PARAM AgentPassword_t * agentPassword, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaSetAgentState(acsHandle, invokeID, device, agentMode, agentID, agentGroup, agentPassword, privateData);
	}
	TSAPI cstaQueryMsgWaitingInd(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM DeviceID_t * device, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaQueryMsgWaitingInd(acsHandle, invokeID, device, privateData);
	}
	TSAPI cstaQueryDoNotDisturb(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM DeviceID_t * device, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaQueryDoNotDisturb(acsHandle, invokeID, device, privateData);
	}
	TSAPI cstaQueryForwarding(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM DeviceID_t * device, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaQueryForwarding(acsHandle, invokeID, device, privateData);
	}
	TSAPI cstaQueryAgentState(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM DeviceID_t * device, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaQueryAgentState(acsHandle,invokeID,device,privateData);
	}
	TSAPI cstaQueryLastNumber(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM DeviceID_t * device, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaQueryLastNumber(acsHandle, invokeID, device, privateData);
	}
	TSAPI cstaQueryDeviceInfo(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM DeviceID_t * device, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaQueryDeviceInfo(acsHandle, invokeID, device, privateData);
	}
	TSAPI cstaMonitorDevice(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM DeviceID_t * deviceID, CONST_PARAM CSTAMonitorFilter_t * monitorFilter, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaMonitorDevice(acsHandle, invokeID, deviceID, monitorFilter, privateData);
	}
	TSAPI cstaMonitorCall(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM ConnectionID_t * call, CONST_PARAM CSTAMonitorFilter_t * monitorFilter, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaMonitorCall(acsHandle, invokeID, call, monitorFilter, privateData);
	}
	TSAPI cstaMonitorCallsViaDevice(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM DeviceID_t * deviceID, CONST_PARAM CSTAMonitorFilter_t * monitorFilter, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaMonitorCallsViaDevice(acsHandle, invokeID, deviceID, monitorFilter, privateData);
	}
	TSAPI cstaChangeMonitorFilter(ACSHandle_t acsHandle, InvokeID_t invokeID, CSTAMonitorCrossRefID_t monitorCrossRefID, CONST_PARAM CSTAMonitorFilter_t * filterlist, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaChangeMonitorFilter(acsHandle, invokeID, monitorCrossRefID, filterlist, privateData);
	}
	TSAPI cstaMonitorStop(ACSHandle_t acsHandle, InvokeID_t invokeID, CSTAMonitorCrossRefID_t monitorCrossRefID, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaMonitorStop(acsHandle, invokeID, monitorCrossRefID, privateData);
	}
	TSAPI cstaSnapshotCallReq(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM ConnectionID_t * snapshotObj, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaSnapshotCallReq(acsHandle, invokeID, snapshotObj, privateData);
	}
	TSAPI cstaSnapshotDeviceReq(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM DeviceID_t * snapshotObj, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaSnapshotDeviceReq(acsHandle, invokeID, snapshotObj, privateData);
	}
	TSAPI cstaRouteRegisterReq(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM DeviceID_t * routingDevice, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaRouteRegisterReq(acsHandle, invokeID, routingDevice, privateData);
	}
	TSAPI cstaRouteRegisterCancel(ACSHandle_t acsHandle, InvokeID_t invokeID, RouteRegisterReqID_t routeRegisterReqID, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaRouteRegisterCancel(acsHandle, invokeID, routeRegisterReqID, privateData);
	}
	TSAPI cstaRouteSelect(ACSHandle_t acsHandle, RouteRegisterReqID_t routeRegisterReqID, RoutingCrossRefID_t routingCrossRefID, CONST_PARAM DeviceID_t * routeSelected, RetryValue_t remainRetry, CONST_PARAM SetUpValues_t * setupInformation, Boolean routeUsedReq, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaRouteSelect(acsHandle, routeRegisterReqID, routingCrossRefID, routeSelected, remainRetry, setupInformation, routeUsedReq, privateData);
	}
	TSAPI cstaRouteEnd(ACSHandle_t acsHandle, RouteRegisterReqID_t routeRegisterReqID, RoutingCrossRefID_t routingCrossRefID, CSTAUniversalFailure_t errorValue, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaRouteEnd(acsHandle, routeRegisterReqID, routingCrossRefID, errorValue, privateData);
	}
	TSAPI cstaRouteSelectInv(ACSHandle_t acsHandle, InvokeID_t invokeID, RouteRegisterReqID_t routeRegisterReqID, RoutingCrossRefID_t routingCrossRefID, CONST_PARAM DeviceID_t * routeSelected, RetryValue_t remainRetry, CONST_PARAM SetUpValues_t * setupInformation, Boolean routeUsedReq, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaRouteSelectInv(acsHandle, invokeID, routeRegisterReqID, routingCrossRefID, routeSelected, remainRetry, setupInformation, routeUsedReq, privateData);
	}
	TSAPI cstaRouteEndInv(ACSHandle_t acsHandle, InvokeID_t invokeID, RouteRegisterReqID_t routeRegisterReqID, RoutingCrossRefID_t routingCrossRefID, CSTAUniversalFailure_t errorValue, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaRouteEndInv(acsHandle, invokeID, routeRegisterReqID, routingCrossRefID, errorValue, privateData);
	}
	TSAPI cstaEscapeService(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaEscapeService(acsHandle, invokeID, privateData);
	}
	TSAPI cstaEscapeServiceConf(ACSHandle_t acsHandle, InvokeID_t invokeID, CSTAUniversalFailure_t error, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaEscapeServiceConf(acsHandle, invokeID, error, privateData);
	}
	TSAPI cstaSendPrivateEvent(ACSHandle_t acsHandle, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaSendPrivateEvent(acsHandle, privateData);
	}
	TSAPI cstaSysStatReq(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaSysStatReq(acsHandle, invokeID, privateData);
	}
	TSAPI cstaSysStatStart(ACSHandle_t acsHandle, InvokeID_t invokeID, SystemStatusFilter_t statusFilter, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaSysStatStart(acsHandle, invokeID, statusFilter, privateData);
	}
	TSAPI cstaSysStatStop(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaSysStatStop(acsHandle, invokeID, privateData);
	}
	TSAPI cstaChangeSysStatFilter(ACSHandle_t acsHandle, InvokeID_t invokeID, SystemStatusFilter_t statusFilter, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaChangeSysStatFilter(acsHandle, invokeID, statusFilter, privateData);
	}
	TSAPI cstaSysStatReqConf(ACSHandle_t acsHandle, InvokeID_t invokeID, SystemStatus_t systemStatus, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaSysStatReqConf(acsHandle, invokeID, systemStatus, privateData);
	}
	TSAPI cstaSysStatEvent(ACSHandle_t acsHandle, SystemStatus_t systemStatus, CONST_PARAM PrivateData_t * privateData)
	{
		return m_cstaSysStatEvent(acsHandle, systemStatus, privateData);
	}
	TSAPI cstaGetAPICaps(ACSHandle_t acsHandle, InvokeID_t invokeID)
	{
		return m_cstaGetAPICaps(acsHandle, invokeID);
	}
	TSAPI cstaGetDeviceList(ACSHandle_t acsHandle, InvokeID_t invokeID, long index, CSTALevel_t level)
	{
		return m_cstaGetDeviceList(acsHandle, invokeID, index, level);
	}
	TSAPI cstaQueryCallMonitor(ACSHandle_t acsHandle, InvokeID_t invokeID)
	{
		return m_cstaQueryCallMonitor(acsHandle, invokeID);
	}
	TSAPI attMakeVersionString(CONST_PARAM char * requestedVersion, char * supportedVersion)
	{
		return m_attMakeVersionString(requestedVersion, supportedVersion);
	}
	TSAPI encodePrivate(int pdunum, CONST_PARAM void * pdu, ATTPrivateData_t * priv)
	{
		return m_encodePrivate(pdunum, pdu, priv);
	}
	TSAPI attPrivateData(CONST_PARAM ATTPrivateData_t * privateData, ATTEvent_t * eventBuffer)
	{
		return m_attPrivateData(privateData, eventBuffer);
	}
	TSAPI attClearConnection(ATTPrivateData_t * privateData, ATTDropResource_t dropResource, CONST_PARAM ATTV5UserToUserInfo_t * userInfo)
	{
		return m_attClearConnection(privateData, dropResource, userInfo);
	}
	TSAPI attConsultationCall(ATTPrivateData_t * privateData, CONST_PARAM DeviceID_t * destRoute, Boolean priorityCalling, CONST_PARAM ATTV5UserToUserInfo_t * userInfo)
	{
		return m_attConsultationCall(privateData, destRoute, priorityCalling, userInfo);
	}
	TSAPI attMakeCall(ATTPrivateData_t * privateData, CONST_PARAM DeviceID_t * destRoute, Boolean priorityCalling, CONST_PARAM ATTV5UserToUserInfo_t * userInfo)
	{
		return m_attMakeCall(privateData, destRoute, priorityCalling, userInfo);
	}
	TSAPI attDirectAgentCall(ATTPrivateData_t * privateData, CONST_PARAM DeviceID_t * split, Boolean priorityCalling, CONST_PARAM ATTV5UserToUserInfo_t * userInfo)
	{
		return m_attDirectAgentCall(privateData, split, priorityCalling, userInfo);
	}
	TSAPI attMakePredictiveCall(ATTPrivateData_t * privateData, Boolean priorityCalling, short maxRings, ATTAnswerTreat_t answerTreat, CONST_PARAM DeviceID_t * destRoute, CONST_PARAM ATTV5UserToUserInfo_t * userInfo)
	{
		return m_attMakePredictiveCall(privateData, priorityCalling, maxRings, answerTreat, destRoute, userInfo);
	}
	TSAPI attSupervisorAssistCall(ATTPrivateData_t * privateData, CONST_PARAM DeviceID_t * split, CONST_PARAM ATTV5UserToUserInfo_t * userInfo)
	{
		return m_attSupervisorAssistCall(privateData, split, userInfo);
	}
	TSAPI attReconnectCall(ATTPrivateData_t * privateData, ATTDropResource_t dropResource, CONST_PARAM ATTV5UserToUserInfo_t * userInfo)
	{
		return m_attReconnectCall(privateData, dropResource, userInfo);
	}
	TSAPI attSendDTMFTone(ATTPrivateData_t * privateData, CONST_PARAM ConnectionID_t * sender, CONST_PARAM ATTV4ConnIDList_t * receivers, CONST_PARAM char * tones, short toneDuration, short pauseDuration)
	{
		return m_attSendDTMFTone(privateData, sender, receivers, tones, toneDuration, pauseDuration);
	}
	TSAPI attSetAgentState(ATTPrivateData_t * privateData, ATTWorkMode_t workMode)
	{
		return m_attSetAgentState(privateData, workMode);
	}
	TSAPI attQueryAcdSplit(ATTPrivateData_t * privateData, CONST_PARAM DeviceID_t * device)
	{
		return m_attQueryAcdSplit(privateData, device);
	}
	TSAPI attQueryAgentLogin(ATTPrivateData_t * privateData, CONST_PARAM DeviceID_t * device)
	{
		return m_attQueryAgentLogin(privateData, device);
	}
	TSAPI attQueryAgentState(ATTPrivateData_t * privateData, CONST_PARAM DeviceID_t * device)
	{
		return m_attQueryAgentState(privateData, device);
	}
	TSAPI attQueryCallClassifier(ATTPrivateData_t * privateData)
	{
		return m_attQueryCallClassifier(privateData);
	}
	TSAPI attQueryDeviceName(ATTPrivateData_t * privateData, CONST_PARAM DeviceID_t * device)
	{
		return m_attQueryDeviceName(privateData, device);
	}
	TSAPI attQueryStationStatus(ATTPrivateData_t * privateData, CONST_PARAM DeviceID_t * device)
	{
		return m_attQueryStationStatus(privateData, device);
	}
	TSAPI attQueryTimeOfDay(ATTPrivateData_t * privateData)
	{
		return m_attQueryTimeOfDay(privateData);
	}
	TSAPI attQueryTrunkGroup(ATTPrivateData_t * privateData, CONST_PARAM DeviceID_t * device)
	{
		return m_attQueryTrunkGroup(privateData, device);
	}
	TSAPI attMonitorFilter(ATTPrivateData_t * privateData, ATTV4PrivateFilter_t privateFilter)
	{
		return m_attMonitorFilter(privateData, privateFilter);
	}
	TSAPI attMonitorStopOnCall(ATTPrivateData_t * privateData, CSTAMonitorCrossRefID_t monitorCrossRefID, CONST_PARAM ConnectionID_t * call)
	{
		return m_attMonitorStopOnCall(privateData, monitorCrossRefID, call);
	}
	TSAPI attRouteSelect(ATTPrivateData_t * privateData, CONST_PARAM DeviceID_t * callingDevice, CONST_PARAM DeviceID_t * directAgentCallSplit, Boolean priorityCalling, CONST_PARAM DeviceID_t * destRoute, CONST_PARAM ATTUserCollectCode_t * collectCode, CONST_PARAM ATTUserProvidedCode_t * userProvidedCode, CONST_PARAM ATTV5UserToUserInfo_t * userInfo)
	{
		return m_attRouteSelect(privateData, callingDevice, directAgentCallSplit, priorityCalling, destRoute, collectCode, userProvidedCode, userInfo);
	}
	TSAPI attSysStat(ATTPrivateData_t * privateData, Boolean linkStatusReq)
	{
		return m_attSysStat(privateData, linkStatusReq);
	}
	TSAPI attSingleStepConferenceCall(ATTPrivateData_t * privateData, CONST_PARAM ConnectionID_t * activeCall, CONST_PARAM DeviceID_t * deviceToBeJoin, ATTParticipationType_t participationType, Boolean alertDestination)
	{
		return m_attSingleStepConferenceCall(privateData, activeCall, deviceToBeJoin, participationType, alertDestination);
	}
	TSAPI attSelectiveListeningHold(ATTPrivateData_t * privateData, CONST_PARAM ConnectionID_t * subjectConnection, Boolean allParties, CONST_PARAM ConnectionID_t * selectedParty)
	{
		return m_attSelectiveListeningHold(privateData, subjectConnection, allParties, selectedParty);
	}
	TSAPI attSelectiveListeningRetrieve(ATTPrivateData_t * privateData, CONST_PARAM ConnectionID_t * subjectConnection, Boolean allParties, CONST_PARAM ConnectionID_t * selectedParty)
	{
		return m_attSelectiveListeningRetrieve(privateData, subjectConnection, allParties, selectedParty);
	}
	TSAPI attSetAgentStateExt(ATTPrivateData_t * privateData, ATTWorkMode_t workMode, long reasonCode)
	{
		return m_attSetAgentStateExt(privateData, workMode, reasonCode);
	}
	TSAPI attSetBillRate(ATTPrivateData_t * privateData, CONST_PARAM ConnectionID_t * call, ATTBillType_t billType, float billRate)
	{
		return m_attSetBillRate(privateData, call, billType, billRate);
	}
	TSAPI attQueryUCID(ATTPrivateData_t * privateData, CONST_PARAM ConnectionID_t * call)
	{
		return m_attQueryUCID(privateData, call);
	}
	TSAPI attSetAdviceOfCharge(ATTPrivateData_t * privateData, Boolean flag)
	{
		return m_attSetAdviceOfCharge(privateData, flag);
	}
	TSAPI attSendDTMFToneExt(ATTPrivateData_t * privateData, CONST_PARAM ConnectionID_t * sender, CONST_PARAM ATTConnIDList_t * receivers, CONST_PARAM char * tones, short toneDuration, short pauseDuration)
	{
		return m_attSendDTMFToneExt(privateData, sender, receivers, tones, toneDuration, pauseDuration);
	}
	TSAPI attMonitorFilterExt(ATTPrivateData_t * privateData, ATTPrivateFilter_t privateFilter)
	{
		return m_attMonitorFilterExt(privateData, privateFilter);
	}
	TSAPI attV6SetAgentState(ATTPrivateData_t * privateData, ATTWorkMode_t workMode, long reasonCode, Boolean enablePending)
	{
		return m_attV6SetAgentState(privateData, workMode, reasonCode, enablePending);
	}
	TSAPI attV6MakeCall(ATTPrivateData_t * privateData, CONST_PARAM DeviceID_t * destRoute, Boolean priorityCalling, CONST_PARAM ATTUserToUserInfo_t * userInfo)
	{
		return m_attV6MakeCall(privateData, destRoute, priorityCalling, userInfo);
	}
	TSAPI attV6ClearConnection(ATTPrivateData_t * privateData, ATTDropResource_t dropResource, CONST_PARAM ATTUserToUserInfo_t * userInfo)
	{
		return m_attV6ClearConnection(privateData, dropResource, userInfo);
	}
	TSAPI attV6ConsultationCall(ATTPrivateData_t * privateData, CONST_PARAM DeviceID_t * destRoute, Boolean priorityCalling, CONST_PARAM ATTUserToUserInfo_t * userInfo)
	{
		return m_attV6ConsultationCall(privateData, destRoute, priorityCalling, userInfo);
	}
	TSAPI attV6DirectAgentCall(ATTPrivateData_t * privateData, CONST_PARAM DeviceID_t * split, Boolean priorityCalling, CONST_PARAM ATTUserToUserInfo_t * userInfo)
	{
		return m_attV6DirectAgentCall(privateData, split, priorityCalling, userInfo);
	}
	TSAPI attV6MakePredictiveCall(ATTPrivateData_t * privateData, Boolean priorityCalling, short maxRings, ATTAnswerTreat_t answerTreat, CONST_PARAM DeviceID_t * destRoute, CONST_PARAM ATTUserToUserInfo_t * userInfo)
	{
		return m_attV6MakePredictiveCall(privateData, priorityCalling, maxRings, answerTreat, destRoute, userInfo);
	}
	TSAPI attV6SupervisorAssistCall(ATTPrivateData_t * privateData, CONST_PARAM DeviceID_t * split, CONST_PARAM ATTUserToUserInfo_t * userInfo)
	{
		return m_attV6SupervisorAssistCall(privateData, split, userInfo);
	}
	TSAPI attV6ReconnectCall(ATTPrivateData_t * privateData, ATTDropResource_t dropResource, CONST_PARAM ATTUserToUserInfo_t * userInfo)
	{
		return m_attV6ReconnectCall(privateData, dropResource, userInfo);
	}
	TSAPI attV6RouteSelect(ATTPrivateData_t * privateData, CONST_PARAM DeviceID_t * callingDevice, CONST_PARAM DeviceID_t * directAgentCallSplit, Boolean priorityCalling, CONST_PARAM DeviceID_t * destRoute, CONST_PARAM ATTUserCollectCode_t * collectCode, CONST_PARAM ATTUserProvidedCode_t * userProvidedCode, CONST_PARAM ATTUserToUserInfo_t * userInfo)
	{
		return m_attV6RouteSelect(privateData, callingDevice, directAgentCallSplit, priorityCalling, destRoute, collectCode, userProvidedCode, userInfo);
	}
	TSAPI attV7RouteSelect(ATTPrivateData_t * privateData, CONST_PARAM DeviceID_t * callingDevice, CONST_PARAM DeviceID_t * directAgentCallSplit, Boolean priorityCalling, CONST_PARAM DeviceID_t * destRoute, CONST_PARAM ATTUserCollectCode_t * collectCode, CONST_PARAM ATTUserProvidedCode_t * userProvidedCode, CONST_PARAM ATTUserToUserInfo_t * userInfo, CONST_PARAM ATTRedirectType_t networkredirect)
	{
		return m_attV7RouteSelect(privateData, callingDevice, directAgentCallSplit, priorityCalling, destRoute, collectCode, userProvidedCode, userInfo, networkredirect);
	}
	TSAPI attSingleStepTransferCall(ATTPrivateData_t * privateData, CONST_PARAM ConnectionID_t * activeCall, CONST_PARAM DeviceID_t * transferredTo)
	{
		return m_attSingleStepTransferCall(privateData, activeCall, transferredTo);
	}
	TSAPI attMonitorCallsViaDevice(ATTPrivateData_t * privateData, ATTPrivateFilter_t privateFilter, Boolean flowPredictiveCallEvents)
	{
		return m_attMonitorCallsViaDevice(privateData, privateFilter, flowPredictiveCallEvents);
	}
	void initATTPrivate(PrivateData_t * priv)
	{
		return m_initATTPrivate(priv);
	}
	void addATTPrivate(UINT16 itemTag, void * itemPtr, PrivateData_t * priv)
	{
		return m_addATTPrivate(itemTag, itemPtr, priv);
	}
	void * getATTPrivate(UINT16 tag, PrivateData_t * priv, UINT16 occ)
	{
		return m_getATTPrivate(tag, priv, occ);
	}
	TSAPI acsOpenStream(ACSHandle_t * acsHandle, InvokeIDType_t invokeIDType, InvokeID_t invokeID, StreamType_t streamType, CONST_PARAM ServerID_t * serverID, CONST_PARAM LoginID_t * loginID, CONST_PARAM Passwd_t * passwd, CONST_PARAM AppName_t * applicationName, Level_t acsLevelReq, CONST_PARAM Version_t * apiVer, unsigned short sendQSize, unsigned short sendExtraBufs, unsigned short recvQSize, unsigned short recvExtraBufs, CONST_PARAM PrivateData_t * priv)
	{
		return m_acsOpenStream(acsHandle, invokeIDType, invokeID, streamType, serverID, loginID, passwd, applicationName, acsLevelReq, apiVer, sendQSize, sendExtraBufs, recvQSize, recvExtraBufs, priv);
	}
	TSAPI acsCloseStream(ACSHandle_t acsHandle, InvokeID_t invokeID, CONST_PARAM PrivateData_t * priv)
	{
		return m_acsCloseStream(acsHandle, invokeID, priv);
	}
	TSAPI acsAbortStream(ACSHandle_t acsHandle, CONST_PARAM PrivateData_t * priv)
	{
		return m_acsAbortStream(acsHandle, priv);
	}
	TSAPI acsFlushEventQueue(ACSHandle_t acsHandle)
	{
		return m_acsFlushEventQueue(acsHandle);
	}
	TSAPI acsGetEventPoll(ACSHandle_t acsHandle, void * eventBuf, unsigned short * eventBufSize, PrivateData_t * privData, unsigned short * numEvents)
	{
		return m_acsGetEventPoll(acsHandle, eventBuf, eventBufSize, privData, numEvents);
	}
	TSAPI acsGetEventBlock(ACSHandle_t acsHandle, void * eventBuf, unsigned short * eventBufSize, PrivateData_t * privData, unsigned short * numEvents)
	{
		return m_acsGetEventBlock(acsHandle, eventBuf, eventBufSize, privData, numEvents);
	}
#if defined ( TSLIB_WINDOWS_32 )
	TSAPI acsEventNotify(ACSHandle_t acsHandle, HWND hwnd, UINT msg, Boolean notifyAll)
	{
		return m_acsEventNotify(acsHandle, hwnd, msg, notifyAll);
	}
	TSAPI acsSetESR(ACSHandle_t acsHandle, void (far pascal *esr)(unsigned long esrParam), unsigned long esrParam, Boolean notifyAll)
	{
		return m_acsSetESR(acsHandle, esr, esrParam, notifyAll);
	}
#elif defined ( TSLIB_LINUX )
	TSAPI acsGetFile(ACSHandle_t acsHandle)
	{
		return m_acsGetFile(acsHandle);
	}
#endif
	TSAPI acsEnumServerNames(StreamType_t streamType, EnumServerNamesCB userCB, unsigned long lParam)
	{
		return m_acsEnumServerNames(streamType, userCB, lParam);
	}
	TSAPI acsQueryAuthInfo(CONST_PARAM ServerID_t * serverID, ACSAuthInfo_t * authInfo)
	{
		return m_acsQueryAuthInfo(serverID, authInfo);
	}
	TSAPI acsGetServerID(ACSHandle_t acsHandle, ServerID_t * serverID)
	{
		return m_acsGetServerID(acsHandle, serverID);
	}
	TSAPI acsSetHeartbeatInterval(ACSHandle_t acsHandle, InvokeID_t invokeID, unsigned short heartbeatInterval, PrivateData_t * privData)
	{
		return m_acsSetHeartbeatInterval(acsHandle, invokeID, heartbeatInterval, privData);
	}
	const char * acsReturnCodeString(RetCode_t returnCode)
	{
		return m_acsReturnCodeString(returnCode);
	}
	const char * acsReturnCodeVerboseString(RetCode_t returnCode)
	{
		return m_acsReturnCodeVerboseString(returnCode);
	}
	const char * acsErrorString(ACSUniversalFailure_t error)
	{
		return m_acsErrorString(error);
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
