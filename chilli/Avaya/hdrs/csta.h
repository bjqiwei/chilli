/* vi/vim directives (for compatibility with Visual Studio editing) */
/* ex: set tabstop=4: */

/***********************************************************/
/* Copyright (C) 2008 Avaya Inc.  All rights reserved.     */
/***********************************************************/
/*
 *  csta.h    CSTA Events Defines
 *
 *  Header File Dependencies
 *   	cstadefs.h, acs.h
 *
 */

#ifndef	CSTA_H
#define	CSTA_H

/* platform-dependent definitions */
#include "tsplatfm.h"

/* structure definitions for CSTA messages */
#include "cstadefs.h"

/* This is the version for the CSTA API that should be used in
 * the call to acsOpenStream().
 */
#define CSTA_API_VERSION        "TS2"	/* Current version number of CSTA API */


/* defines for CSTA event classes */

#define	CSTAREQUEST			3
#define	CSTAUNSOLICITED		4
#define	CSTACONFIRMATION	5
#define	CSTAEVENTREPORT		6


#define CSTA_MAX_GET_DEVICE	20	/* Maximum number of devices
								 * a CSTAGetDevice call can
								 * return
								 */

typedef struct
{
	InvokeID_t	invokeID;
	union
	{
		CSTARouteRequestEvent_t		routeRequest;
		CSTARouteRequestExtEvent_t	routeRequestExt;
		CSTAReRouteRequest_t		reRouteRequest;
		CSTAEscapeSvcReqEvent_t		escapeSvcReqeust;
		CSTASysStatReqEvent_t		sysStatRequest;
	} u;
} CSTARequestEvent;

typedef struct
{
	union
	{
		CSTARouteRegisterAbortEvent_t   registerAbort;
		CSTARouteUsedEvent_t			routeUsed;
		CSTARouteUsedExtEvent_t			routeUsedExt;
		CSTARouteEndEvent_t				routeEnd;
		CSTAPrivateEvent_t				privateEvent;
		CSTASysStatEvent_t				sysStat;
		CSTASysStatEndedEvent_t			sysStatEnded;
	}u;
} CSTAEventReport;

typedef struct
{
	CSTAMonitorCrossRefID_t		monitorCrossRefId;
	union
	{
		CSTACallClearedEvent_t			callCleared;
		CSTAConferencedEvent_t			conferenced;
		CSTAConnectionClearedEvent_t	connectionCleared;
		CSTADeliveredEvent_t			delivered;
		CSTADivertedEvent_t				diverted;
		CSTAEstablishedEvent_t			established;
		CSTAFailedEvent_t				failed;
		CSTAHeldEvent_t					held;
		CSTANetworkReachedEvent_t		networkReached;
		CSTAOriginatedEvent_t			originated;
		CSTAQueuedEvent_t				queued;
		CSTARetrievedEvent_t			retrieved;
		CSTAServiceInitiatedEvent_t		serviceInitiated;
		CSTATransferredEvent_t			transferred;
		CSTACallInformationEvent_t		callInformation;
		CSTADoNotDisturbEvent_t			doNotDisturb;
		CSTAForwardingEvent_t			forwarding;
		CSTAMessageWaitingEvent_t		messageWaiting;
		CSTALoggedOnEvent_t				loggedOn;
		CSTALoggedOffEvent_t			loggedOff;
		CSTANotReadyEvent_t				notReady;
		CSTAReadyEvent_t				ready;
		CSTAWorkNotReadyEvent_t			workNotReady;
		CSTAWorkReadyEvent_t			workReady;
		CSTABackInServiceEvent_t		backInService;
		CSTAOutOfServiceEvent_t			outOfService;
		CSTAPrivateStatusEvent_t		privateStatus;
		CSTAMonitorEndedEvent_t  		monitorEnded;
	} u;

} CSTAUnsolicitedEvent;

typedef struct
{
	InvokeID_t	invokeID;
	union
	{
		CSTAAlternateCallConfEvent_t		alternateCall;
		CSTAAnswerCallConfEvent_t			answerCall;
		CSTACallCompletionConfEvent_t		callCompletion;
		CSTAClearCallConfEvent_t			clearCall;
		CSTAClearConnectionConfEvent_t    	clearConnection;
		CSTAConferenceCallConfEvent_t		conferenceCall;
		CSTAConsultationCallConfEvent_t		consultationCall;
		CSTADeflectCallConfEvent_t			deflectCall;
		CSTAPickupCallConfEvent_t			pickupCall;
		CSTAGroupPickupCallConfEvent_t		groupPickupCall;
		CSTAHoldCallConfEvent_t				holdCall;
		CSTAMakeCallConfEvent_t				makeCall;
		CSTAMakePredictiveCallConfEvent_t 	makePredictiveCall;
		CSTAQueryMwiConfEvent_t				queryMwi;
		CSTAQueryDndConfEvent_t				queryDnd;
		CSTAQueryFwdConfEvent_t				queryFwd;
		CSTAQueryAgentStateConfEvent_t		queryAgentState;
		CSTAQueryLastNumberConfEvent_t		queryLastNumber;
		CSTAQueryDeviceInfoConfEvent_t		queryDeviceInfo;
		CSTAReconnectCallConfEvent_t		reconnectCall;
		CSTARetrieveCallConfEvent_t			retrieveCall;
		CSTASetMwiConfEvent_t				setMwi;
		CSTASetDndConfEvent_t				setDnd;
		CSTASetFwdConfEvent_t				setFwd;
		CSTASetAgentStateConfEvent_t		setAgentState;
		CSTATransferCallConfEvent_t			transferCall;
		CSTAUniversalFailureConfEvent_t		universalFailure;
		CSTAMonitorConfEvent_t				monitorStart;
		CSTAChangeMonitorFilterConfEvent_t	changeMonitorFilter;
		CSTAMonitorStopConfEvent_t			monitorStop;
		CSTASnapshotDeviceConfEvent_t		snapshotDevice;
		CSTASnapshotCallConfEvent_t			snapshotCall;
		CSTARouteRegisterReqConfEvent_t		routeRegister;
		CSTARouteRegisterCancelConfEvent_t	routeCancel;
		CSTAEscapeSvcConfEvent_t			escapeService;
		CSTASysStatReqConfEvent_t			sysStatReq;
		CSTASysStatStartConfEvent_t			sysStatStart;
		CSTASysStatStopConfEvent_t			sysStatStop;
		CSTAChangeSysStatFilterConfEvent_t	changeSysStatFilter;
		CSTAGetAPICapsConfEvent_t			getAPICaps;
		CSTAGetDeviceListConfEvent_t		getDeviceList;
		CSTAQueryCallMonitorConfEvent_t		queryCallMonitor;

	} u;

} CSTAConfirmationEvent;

#define CSTA_MAX_HEAP	1024


typedef struct
{
	ACSEventHeader_t	eventHeader;
	union
	{
		ACSUnsolicitedEvent		acsUnsolicited;
		ACSConfirmationEvent	acsConfirmation;
		CSTARequestEvent		cstaRequest;
		CSTAUnsolicitedEvent	cstaUnsolicited;
		CSTAConfirmationEvent	cstaConfirmation;
		CSTAEventReport			cstaEventReport;
	} event;
	char	heap[CSTA_MAX_HEAP];
} CSTAEvent_t;


/* function prototypes */

#ifdef __cplusplus
extern "C"
{
#endif

/* Utility functions */

const char *
cstaErrorString(CSTAUniversalFailure_t error);

/* Basic Call Control Services */

TSAPI
cstaAlternateCall (	ACSHandle_t						acsHandle,
					InvokeID_t						invokeID,
					CONST_PARAM ConnectionID_t	FAR	*activeCall,
					CONST_PARAM ConnectionID_t	FAR	*otherCall,
					CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaAnswerCall (ACSHandle_t						acsHandle,
				InvokeID_t						invokeID,
				CONST_PARAM ConnectionID_t	FAR	*alertingCall,
				CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaCallCompletion (ACSHandle_t						acsHandle,
					InvokeID_t						invokeID,
					Feature_t						feature,
					CONST_PARAM ConnectionID_t	FAR	*call,
					CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaClearCall (	ACSHandle_t						acsHandle,
				InvokeID_t						invokeID,
				CONST_PARAM ConnectionID_t	FAR	*call,
				CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaClearConnection (	ACSHandle_t						acsHandle,
						InvokeID_t						invokeID,
						CONST_PARAM ConnectionID_t	FAR	*call,
						CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaConferenceCall (ACSHandle_t						acsHandle,
					InvokeID_t						invokeID,
					CONST_PARAM ConnectionID_t	FAR	*heldCall,
					CONST_PARAM ConnectionID_t	FAR	*activeCall,
					CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaConsultationCall (	ACSHandle_t						acsHandle,
						InvokeID_t						invokeID,
						CONST_PARAM ConnectionID_t	FAR	*activeCall,
						CONST_PARAM DeviceID_t		FAR	*calledDevice,
						CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaDeflectCall (	ACSHandle_t						acsHandle,
					InvokeID_t						invokeID,
					CONST_PARAM ConnectionID_t	FAR	*deflectCall,
					CONST_PARAM DeviceID_t		FAR	*calledDevice,
					CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaGroupPickupCall (	ACSHandle_t						acsHandle,
						InvokeID_t						invokeID,
						CONST_PARAM ConnectionID_t	FAR	*deflectCall,
						CONST_PARAM DeviceID_t		FAR	*pickupDevice,
						CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaHoldCall (	ACSHandle_t						acsHandle,
				InvokeID_t						invokeID,
				CONST_PARAM ConnectionID_t	FAR	*activeCall,
				Boolean							reservation,
				CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaMakeCall (	ACSHandle_t						acsHandle,
				InvokeID_t						invokeID,
				CONST_PARAM DeviceID_t		FAR	*callingDevice,
				CONST_PARAM DeviceID_t		FAR	*calledDevice,
				CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaMakePredictiveCall (ACSHandle_t						acsHandle,
						InvokeID_t						invokeID,
						CONST_PARAM DeviceID_t		FAR	*callingDevice,
						CONST_PARAM DeviceID_t		FAR	*calledDevice,
						AllocationState_t				allocationState,
						CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaPickupCall (	ACSHandle_t						acsHandle,
					InvokeID_t						invokeID,
					CONST_PARAM ConnectionID_t	FAR	*deflectCall,
					CONST_PARAM DeviceID_t		FAR	*calledDevice,
					CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaReconnectCall (	ACSHandle_t						acsHandle,
					InvokeID_t						invokeID,
					CONST_PARAM ConnectionID_t	FAR	*activeCall,
					CONST_PARAM ConnectionID_t	FAR	*heldCall,
					CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaRetrieveCall (	ACSHandle_t						acsHandle,
					InvokeID_t						invokeID,
					CONST_PARAM ConnectionID_t	FAR	*heldCall,
					CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaTransferCall (	ACSHandle_t						acsHandle,
					InvokeID_t						invokeID,
					CONST_PARAM ConnectionID_t	FAR	*heldCall,
					CONST_PARAM ConnectionID_t	FAR	*activeCall,
					CONST_PARAM PrivateData_t	FAR	*privateData);


/* Telephony Supplementary Services */

TSAPI
cstaSetMsgWaitingInd (	ACSHandle_t						acsHandle,
						InvokeID_t						invokeID,
						CONST_PARAM DeviceID_t		FAR	*device,
						Boolean							messages,
						CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaSetDoNotDisturb (	ACSHandle_t						acsHandle,
						InvokeID_t					invokeID,
						CONST_PARAM DeviceID_t		FAR	*device,
						Boolean							doNotDisturb,
						CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaSetForwarding (	ACSHandle_t						acsHandle,
					InvokeID_t						invokeID,
					CONST_PARAM DeviceID_t		FAR	*device,
					ForwardingType_t				forwardingType,
					Boolean							forwardingOn,
					CONST_PARAM DeviceID_t		FAR	*forwardingDestination,
					CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaSetAgentState (	ACSHandle_t						acsHandle,
					InvokeID_t						invokeID,
					CONST_PARAM DeviceID_t		FAR	*device,
					AgentMode_t						agentMode,
					CONST_PARAM AgentID_t		FAR	*agentID,
					CONST_PARAM AgentGroup_t	FAR	*agentGroup,
					CONST_PARAM AgentPassword_t	FAR	*agentPassword,
					CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaQueryMsgWaitingInd (ACSHandle_t						acsHandle,
						InvokeID_t						invokeID,
						CONST_PARAM DeviceID_t		FAR	*device,
						CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaQueryDoNotDisturb (	ACSHandle_t						acsHandle,
						InvokeID_t						invokeID,
						CONST_PARAM DeviceID_t		FAR	*device,
						CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaQueryForwarding (	ACSHandle_t						acsHandle,
						InvokeID_t						invokeID,
						CONST_PARAM DeviceID_t		FAR	*device,
						CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaQueryAgentState (	ACSHandle_t						acsHandle,
						InvokeID_t						invokeID,
						CONST_PARAM DeviceID_t		FAR	*device,
						CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaQueryLastNumber (	ACSHandle_t						acsHandle,
						InvokeID_t						invokeID,
						CONST_PARAM DeviceID_t		FAR	*device,
						CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaQueryDeviceInfo (	ACSHandle_t						acsHandle,
						InvokeID_t						invokeID,
						CONST_PARAM DeviceID_t		FAR	*device,
						CONST_PARAM PrivateData_t	FAR	*privateData);


/* Monitor Services */

TSAPI
cstaMonitorDevice (	ACSHandle_t							acsHandle,
					InvokeID_t							invokeID,
					CONST_PARAM DeviceID_t			FAR	*deviceID,
					CONST_PARAM CSTAMonitorFilter_t	FAR	*monitorFilter,
					CONST_PARAM PrivateData_t		FAR	*privateData);


TSAPI
cstaMonitorCall (	ACSHandle_t							acsHandle,
					InvokeID_t							invokeID,
					CONST_PARAM ConnectionID_t		FAR	*call,
					CONST_PARAM CSTAMonitorFilter_t	FAR	*monitorFilter,
					CONST_PARAM PrivateData_t		FAR	*privateData);


TSAPI
cstaMonitorCallsViaDevice (	ACSHandle_t							acsHandle,
							InvokeID_t							invokeID,
							CONST_PARAM DeviceID_t			FAR	*deviceID,
							CONST_PARAM CSTAMonitorFilter_t	FAR	*monitorFilter,
							CONST_PARAM PrivateData_t		FAR	*privateData);


TSAPI
cstaChangeMonitorFilter (	ACSHandle_t							acsHandle,
							InvokeID_t							invokeID,
							CSTAMonitorCrossRefID_t				monitorCrossRefID,
							CONST_PARAM CSTAMonitorFilter_t	FAR	*filterlist,
							CONST_PARAM PrivateData_t		FAR	*privateData);


TSAPI
cstaMonitorStop (	ACSHandle_t						acsHandle,
					InvokeID_t						invokeID,
					CSTAMonitorCrossRefID_t			monitorCrossRefID,
					CONST_PARAM PrivateData_t	FAR	*privateData);

/* Snapshot Services */

TSAPI
cstaSnapshotCallReq (	ACSHandle_t						acsHandle,
						InvokeID_t						invokeID,
						CONST_PARAM ConnectionID_t	FAR	*snapshotObj,
						CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaSnapshotDeviceReq (	ACSHandle_t						acsHandle,
						InvokeID_t						invokeID,
						CONST_PARAM DeviceID_t		FAR	*snapshotObj,
						CONST_PARAM PrivateData_t	FAR	*privateData);


/* Routing Services */

TSAPI
cstaRouteRegisterReq (	ACSHandle_t						acsHandle,
						InvokeID_t						invokeID,
						CONST_PARAM DeviceID_t		FAR	*routingDevice,
						CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaRouteRegisterCancel (	ACSHandle_t					acsHandle,
							InvokeID_t					invokeID,
							RouteRegisterReqID_t		routeRegisterReqID,
							CONST_PARAM PrivateData_t	FAR	*privateData);

	/* Release 1 calls, w/o invokeID, for backward compatibility */

TSAPI
cstaRouteSelect (	ACSHandle_t						acsHandle,
					RouteRegisterReqID_t			routeRegisterReqID,
					RoutingCrossRefID_t				routingCrossRefID,
					CONST_PARAM DeviceID_t		FAR	*routeSelected,
					RetryValue_t					remainRetry,
					CONST_PARAM SetUpValues_t	FAR *setupInformation,
					Boolean							routeUsedReq,
					CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaRouteEnd (	ACSHandle_t						acsHandle,
				RouteRegisterReqID_t			routeRegisterReqID,
				RoutingCrossRefID_t				routingCrossRefID,
				CSTAUniversalFailure_t			errorValue,
				CONST_PARAM PrivateData_t	FAR	*privateData);


	/* Release 2 calls, with invokeID */

TSAPI
cstaRouteSelectInv (ACSHandle_t						acsHandle,
					InvokeID_t						invokeID,
					RouteRegisterReqID_t			routeRegisterReqID,
					RoutingCrossRefID_t				routingCrossRefID,
					CONST_PARAM DeviceID_t		FAR	*routeSelected,
					RetryValue_t					remainRetry,
					CONST_PARAM SetUpValues_t	FAR *setupInformation,
					Boolean							routeUsedReq,
					CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaRouteEndInv (	ACSHandle_t						acsHandle,
					InvokeID_t						invokeID,
					RouteRegisterReqID_t			routeRegisterReqID,
					RoutingCrossRefID_t				routingCrossRefID,
					CSTAUniversalFailure_t			errorValue,
					CONST_PARAM PrivateData_t	FAR	*privateData);


/* Escape Services */

TSAPI
cstaEscapeService (	ACSHandle_t						acsHandle,
					InvokeID_t						invokeID,
					CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaEscapeServiceConf (	ACSHandle_t						acsHandle,
						InvokeID_t						invokeID,
						CSTAUniversalFailure_t			error,
						CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaSendPrivateEvent (	ACSHandle_t						acsHandle,
						CONST_PARAM PrivateData_t	FAR	*privateData);


/* Maintenance Services */

TSAPI
cstaSysStatReq (ACSHandle_t						acsHandle,
				InvokeID_t						invokeID,
				CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaSysStatStart (	ACSHandle_t						acsHandle,
					InvokeID_t						invokeID,
					SystemStatusFilter_t			statusFilter,
					CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaSysStatStop (	ACSHandle_t						acsHandle,
					InvokeID_t						invokeID,
					CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaChangeSysStatFilter (	ACSHandle_t						acsHandle,
							InvokeID_t						invokeID,
							SystemStatusFilter_t			statusFilter,
							CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaSysStatReqConf (ACSHandle_t						acsHandle,
					InvokeID_t						invokeID,
					SystemStatus_t					systemStatus,
					CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaSysStatEvent (	ACSHandle_t						acsHandle,
					SystemStatus_t					systemStatus,
					CONST_PARAM PrivateData_t	FAR	*privateData);


TSAPI
cstaGetAPICaps (ACSHandle_t acsHandle, InvokeID_t invokeID);


TSAPI
cstaGetDeviceList (	ACSHandle_t	acsHandle,
					InvokeID_t	invokeID,
				    long		index,
				    CSTALevel_t	level);


TSAPI
cstaQueryCallMonitor (ACSHandle_t acsHandle, InvokeID_t invokeID);


#ifdef __cplusplus
}
#endif


#endif

