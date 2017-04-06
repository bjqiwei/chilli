#pragma once
#include <acs.h>
#include <csta.h>
#include <attpriv.h>
#include <cstdint>
#include <json/json.h>

#if defined ( TSLIB_WINDOWS_32 )
#define TSAPIPROC           RetCode_t (pascal *
#elif defined ( TSLIB_LINUX )
#define TSAPIPROC           RetCode_t
#endif

namespace AvayaAPI{
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
	//ATTPRV32

	extern Proc_acsOpenStream acsOpenStream;
	extern Proc_acsCloseStream acsCloseStream;
	extern Proc_acsAbortStream acsAbortStream;
	extern Proc_acsFlushEventQueue acsFlushEventQueue;
	extern Proc_acsGetEventPoll acsGetEventPoll;
	extern Proc_acsGetEventBlock acsGetEventBlock;
#if defined ( TSLIB_WINDOWS_32 )
	extern Proc_acsEventNotify acsEventNotify;
	extern Proc_acsSetESR acsSetESR;
#elif defined ( TSLIB_LINUX )
	extern Proc_acsGetFile acsGetFile;
#endif
	extern Proc_acsEnumServerNames acsEnumServerNames;
	extern Proc_acsQueryAuthInfo acsQueryAuthInfo;
	extern Proc_acsGetServerID acsGetServerID;
	extern Proc_acsSetHeartbeatInterval acsSetHeartbeatInterval;
	extern Proc_acsReturnCodeString acsReturnCodeString;
	extern Proc_acsReturnCodeVerboseString acsReturnCodeVerboseString;
	extern Proc_acsErrorString acsErrorString;
	extern Proc_cstaErrorString cstaErrorString;
	extern Proc_cstaAlternateCall cstaAlternateCall;
	extern Proc_cstaAnswerCall cstaAnswerCall;
	extern Proc_cstaCallCompletion cstaCallCompletion;
	extern Proc_cstaClearCall cstaClearCall;
	extern Proc_cstaClearConnection cstaClearConnection;
	extern Proc_cstaConferenceCall cstaConferenceCall;
	extern Proc_cstaConsultationCall cstaConsultationCall;
	extern Proc_cstaDeflectCall cstaDeflectCall;
	extern Proc_cstaGroupPickupCall cstaGroupPickupCall;
	extern Proc_cstaHoldCall cstaHoldCall;
	extern Proc_cstaMakeCall cstaMakeCall;
	extern Proc_cstaMakePredictiveCall cstaMakePredictiveCall;
	extern Proc_cstaPickupCall cstaPickupCall;
	extern Proc_cstaReconnectCall cstaReconnectCall;
	extern Proc_cstaRetrieveCall cstaRetrieveCall;
	extern Proc_cstaTransferCall cstaTransferCall;
	extern Proc_cstaSetMsgWaitingInd cstaSetMsgWaitingInd;
	extern Proc_cstaSetDoNotDisturb cstaSetDoNotDisturb;
	extern Proc_cstaSetForwarding cstaSetForwarding;
	extern Proc_cstaSetAgentState cstaSetAgentState;
	extern Proc_cstaQueryMsgWaitingInd cstaQueryMsgWaitingInd;
	extern Proc_cstaQueryDoNotDisturb cstaQueryDoNotDisturb;
	extern Proc_cstaQueryForwarding cstaQueryForwarding;
	extern Proc_cstaQueryAgentState cstaQueryAgentState;
	extern Proc_cstaQueryLastNumber cstaQueryLastNumber;
	extern Proc_cstaQueryDeviceInfo cstaQueryDeviceInfo;
	extern Proc_cstaMonitorDevice cstaMonitorDevice;
	extern Proc_cstaMonitorCall cstaMonitorCall;
	extern Proc_cstaMonitorCallsViaDevice cstaMonitorCallsViaDevice;
	extern Proc_cstaChangeMonitorFilter cstaChangeMonitorFilter;
	extern Proc_cstaMonitorStop cstaMonitorStop;
	extern Proc_cstaSnapshotCallReq cstaSnapshotCallReq;
	extern Proc_cstaSnapshotDeviceReq cstaSnapshotDeviceReq;
	extern Proc_cstaRouteRegisterReq cstaRouteRegisterReq;
	extern Proc_cstaRouteRegisterCancel cstaRouteRegisterCancel;
	extern Proc_cstaRouteSelect cstaRouteSelect;
	extern Proc_cstaRouteEnd cstaRouteEnd;
	extern Proc_cstaRouteSelectInv cstaRouteSelectInv;
	extern Proc_cstaRouteEndInv cstaRouteEndInv;
	extern Proc_cstaEscapeService cstaEscapeService;
	extern Proc_cstaEscapeServiceConf cstaEscapeServiceConf;
	extern Proc_cstaSendPrivateEvent cstaSendPrivateEvent;
	extern Proc_cstaSysStatReq cstaSysStatReq;
	extern Proc_cstaSysStatStart cstaSysStatStart;
	extern Proc_cstaSysStatStop cstaSysStatStop;
	extern Proc_cstaChangeSysStatFilter cstaChangeSysStatFilter;
	extern Proc_cstaSysStatReqConf cstaSysStatReqConf;
	extern Proc_cstaSysStatEvent cstaSysStatEvent;
	extern Proc_cstaGetAPICaps cstaGetAPICaps;
	extern Proc_cstaGetDeviceList cstaGetDeviceList;
	extern Proc_cstaQueryCallMonitor cstaQueryCallMonitor;
	extern Proc_attMakeVersionString attMakeVersionString;
	extern Proc_encodePrivate encodePrivate;
	extern Proc_attPrivateData attPrivateData;
	extern Proc_attClearConnection attClearConnection;
	extern Proc_attConsultationCall attConsultationCall;
	extern Proc_attMakeCall attMakeCall;
	extern Proc_attDirectAgentCall attDirectAgentCall;
	extern Proc_attMakePredictiveCall attMakePredictiveCall;
	extern Proc_attSupervisorAssistCall attSupervisorAssistCall;
	extern Proc_attReconnectCall attReconnectCall;
	extern Proc_attSendDTMFTone attSendDTMFTone;
	extern Proc_attSetAgentState attSetAgentState;
	extern Proc_attQueryAcdSplit attQueryAcdSplit;
	extern Proc_attQueryAgentLogin attQueryAgentLogin;
	extern Proc_attQueryAgentState attQueryAgentState;
	extern Proc_attQueryCallClassifier attQueryCallClassifier;
	extern Proc_attQueryDeviceName attQueryDeviceName;
	extern Proc_attQueryStationStatus attQueryStationStatus;
	extern Proc_attQueryTimeOfDay attQueryTimeOfDay;
	extern Proc_attQueryTrunkGroup attQueryTrunkGroup;
	extern Proc_attMonitorFilter attMonitorFilter;
	extern Proc_attMonitorStopOnCall attMonitorStopOnCall;
	extern Proc_attRouteSelect attRouteSelect;
	extern Proc_attSysStat attSysStat;
	extern Proc_attSingleStepConferenceCall attSingleStepConferenceCall;
	extern Proc_attSelectiveListeningHold attSelectiveListeningHold;
	extern Proc_attSelectiveListeningRetrieve attSelectiveListeningRetrieve;
	extern Proc_attSetAgentStateExt attSetAgentStateExt;
	extern Proc_attSetBillRate attSetBillRate;
	extern Proc_attQueryUCID attQueryUCID;
	extern Proc_attSetAdviceOfCharge attSetAdviceOfCharge;
	extern Proc_attSendDTMFToneExt attSendDTMFToneExt;
	extern Proc_attMonitorFilterExt attMonitorFilterExt;
	extern Proc_attV6SetAgentState attV6SetAgentState;
	extern Proc_attV6MakeCall attV6MakeCall;
	extern Proc_attV6ClearConnection attV6ClearConnection;
	extern Proc_attV6ConsultationCall attV6ConsultationCall;
	extern Proc_attV6DirectAgentCall attV6DirectAgentCall;
	extern Proc_attV6MakePredictiveCall attV6MakePredictiveCall;
	extern Proc_attV6SupervisorAssistCall attV6SupervisorAssistCall;
	extern Proc_attV6ReconnectCall attV6ReconnectCall;
	extern Proc_attV6RouteSelect attV6RouteSelect;
	extern Proc_attV7RouteSelect attV7RouteSelect;
	extern Proc_attSingleStepTransferCall attSingleStepTransferCall;
	extern Proc_attMonitorCallsViaDevice attMonitorCallsViaDevice;
	extern Proc_initATTPrivate initATTPrivate;
	extern Proc_addATTPrivate addATTPrivate;
	extern Proc_getATTPrivate getATTPrivate;

	const char * cstaAgentStateString(AgentState_t agentState);
	const char * cstaAPICapsString(uint32_t api);
	const char * cstaDeviceTypeString(ConnectionID_Device_t type);
	const char * cstaLocalConnectionStateString(LocalConnectionState_t localState);
	const char * cstaEventCauseString(CSTAEventCause_t cause);
	Json::Value  cstaConnectionIDJson(ConnectionID_t connectionId);
	const char * cstaDeviceIDStatusString(DeviceIDStatus_t deviceIDStatus);
	const char * cstaDeviceIDTypeString(DeviceIDType_t deviceIDType);
	bool InitAvayaAPI();
	bool UnInitAvayaAPI();
}

