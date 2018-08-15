/* vi/vim directives (for compatibility with Visual Studio editing) */
/* ex: set tabstop=4: */

/***********************************************************/
/* Copyright (C) 2001-2010 Avaya Inc.  All rights reserved.*/
/***********************************************************/
/*
 *  attpriv.h    ATT Private Defines
 *
 *  Header File Dependencies
 *   	acs.h
 *   	csta.h
 *
 */

#ifndef ATT_PRIV__H
#define ATT_PRIV__H

/* platform-dependent definitions */
#include "tsplatfm.h"

/* structure definitions for AT&T private messages */
#include "attpdefs.h"


#define ATT_MAX_PRIVATE_DATA    1024    /* Max size of encoded private data */
#define ATT_MAX_USER_INFO       129     /* Max user to user length          */
#define ATT_MAX_UUI_SIZE        96      /* Max supported V6 user to user length */
#define ATTV5_MAX_UUI_SIZE      32      /* Max supported V5 user to user length */
#define ATT_MAX_USER_CODE       25      /* Max length of user entered code  */
#define ATT_MAX_RECEIVERS       5       /* Max receivers for touch tones    */
#define ATT_MAX_PARTIES_ON_CALL 6       /* Max parties on a call            */
#define ATT_MAX_AGENT_EXT       10      /* Max agent extensions for query   */
#define ATT_MAX_TONES           33      /* Max touch tones sent             */
#define ATT_MAX_PROVIDED_CODE   25      /* Max size of user provided code   */
#define ATT_MAX_ENTERED_DIGITS  ATT_MAX_USER_CODE


/*
 * The following two defines are the vendor sent back in private data.
 * If there is a change, MAX_VENDOR_LENGTH may need to change; please make
 * sure the longest string is used.
 */

#define ATT_VENDOR_STRING   "AT&T Definity G3"
#define ECS_VENDOR_STRING   "ECS"
#define MAX_VENDOR_LENGTH   17          /* 16 + 1 for NULL terminator.
                                         * Cannot be bigger than 32 bytes */

/*
 * Changing ATTPRIV_MAX_HEAP may affect backward compatiblity of the TSAPI
 * client library with applications that are compiled using an earlier version
 * of the SDK.
 */

#if defined( TSLIB_WINDOWS_32 )
#define ATTPRIV_MAX_HEAP    512
#else
#define ATTPRIV_MAX_HEAP    1024
#endif

#define ATT_NULL_UCID       "00000000000000000000" /* indicates no universal call ID */

	/*
	 * ATT Private Data Structure
	 *  Structure large enough to hold all ATT encoded
	 *  private data sent and received via the Private Data
	 *  Parameter for TSAPI function calls.
	 */

typedef struct ATTPrivateData_t {
	char            vendor[32];
	unsigned short  length;
	char            data[ATT_MAX_PRIVATE_DATA];
} ATTPrivateData_t;


typedef unsigned short ATTEventType_t;

	/*
	 * ATT Private Data Event Structure
	 * ATT Event structure created by the ATT Private Data
	 * decoding functions.
	 */

typedef struct  ATTEvent_t
{
	ATTEventType_t eventType;
	union
	{
		/* private data version 9 */
		ATTHeldEvent_t                              heldEvent;
		ATTSingleStepConferenceCallConfEvent_t      ssconference;
		ATTSelectiveListeningHoldConfEvent_t        slhold;
		ATTSelectiveListeningRetrieveConfEvent_t    slretrieve;
		ATTSendDTMFToneConfEvent_t                  sendDTMFTone;
		ATTQueryAcdSplitConfEvent_t                 queryAcdSplit;
		ATTQueryAgentLoginConfEvent_t               queryAgentLogin;
		ATTQueryAgentLoginResp_t                    queryAgentLoginResp;
		ATTQueryAgentStateConfEvent_t               queryAgentState;
		ATTQueryCallClassifierConfEvent_t           queryCallClassifier;
		ATTQueryDeviceInfoConfEvent_t               queryDeviceInfo;
		ATTQueryDeviceNameConfEvent_t               queryDeviceName;
		ATTQueryMwiConfEvent_t                      queryMwi;
		ATTQueryStationStatusConfEvent_t            queryStationStatus;
		ATTQueryTodConfEvent_t                      queryTod;
		ATTQueryTgConfEvent_t                       queryTg;
		ATTQueryAgentMeasurementsConfEvent_t        queryAgentMeas;
		ATTQuerySplitSkillMeasurementsConfEvent_t   querySplitSkillMeas;
		ATTQueryTrunkGroupMeasurementsConfEvent_t   queryTrunkGroupMeas;
		ATTQueryVdnMeasurementsConfEvent_t          queryVdnMeas;
		ATTSnapshotDeviceConfEvent_t                snapshotDevice;
		ATTMonitorConfEvent_t                       monitorStart;
		ATTMonitorCallConfEvent_t                   monitorCallStart;
		ATTMonitorStopOnCallConfEvent_t             monitorStopOnCall;
		ATTCallClearedEvent_t                       callClearedEvent;
		ATTConferencedEvent_t                       conferencedEvent;
		ATTConnectionClearedEvent_t                 connectionClearedEvent;
		ATTDeliveredEvent_t                         deliveredEvent;
		ATTEnteredDigitsEvent_t                     enteredDigitsEvent;
		ATTEstablishedEvent_t                       establishedEvent;
		ATTLoggedOnEvent_t                          loggedOnEvent;
		ATTNetworkReachedEvent_t                    networkReachedEvent;
		ATTOriginatedEvent_t                        originatedEvent;
		ATTTransferredEvent_t                       transferredEvent;
		ATTRouteRequestEvent_t                      routeRequest;
		ATTRouteUsedEvent_t                         routeUsed;
		ATTLinkStatusEvent_t                        linkStatus;
		ATTGetAPICapsConfEvent_t                    getAPICaps;
		ATTServiceInitiatedEvent_t                  serviceInitiated;
		ATTChargeAdviceEvent_t                      chargeAdviceEvent;
		ATTSetBillRateConfEvent_t                   setBillRate;
		ATTQueryUcidConfEvent_t                     queryUCID;
		ATTLoggedOffEvent_t                         loggedOffEvent;
		ATTConsultationCallConfEvent_t              consultationCall;
		ATTConferenceCallConfEvent_t                conferenceCall;
		ATTMakeCallConfEvent_t                      makeCall;
		ATTMakePredictiveCallConfEvent_t            makePredictiveCall;
		ATTTransferCallConfEvent_t                  transferCall;
		ATTSetAdviceOfChargeConfEvent_t             setAdviceOfCharge;
		ATTSetAgentStateConfEvent_t                 setAgentState;
		ATTQueuedEvent_t                            queuedEvent;
		ATTDivertedEvent_t                          divertedEvent;
		ATTFailedEvent_t                            failedEvent;
		ATTSnapshotCallConfEvent_t                  snapshotCallConf;
		ATTSingleStepTransferCallConfEvent_t        ssTransferCallConf;

		/*
		 * The following private data version 3 events have been superceded
		 * by new events in private data version 4.
		 */
		ATTV3ConferencedEvent_t             v3conferencedEvent;
		ATTV3DeliveredEvent_t               v3deliveredEvent;
		ATTV3EstablishedEvent_t             v3establishedEvent;
		ATTV3TransferredEvent_t             v3transferredEvent;
		ATTV3LinkStatusEvent_t              v3linkStatus;

		/*
		 * The following private data version 4 events have been superceded
		 * by new events in private data version 5.
		 */
		ATTV4QueryDeviceInfoConfEvent_t     v4queryDeviceInfo;
		ATTV4GetAPICapsConfEvent_t          v4getAPICaps;
		ATTV4SnapshotDeviceConfEvent_t      v4snapshotDevice;
		ATTV4ConferencedEvent_t             v4conferencedEvent;
		ATTV4DeliveredEvent_t               v4deliveredEvent;
		ATTV4EstablishedEvent_t             v4establishedEvent;
		ATTV4TransferredEvent_t             v4transferredEvent;
		ATTV4LinkStatusEvent_t              v4linkStatus;
		ATTV4RouteRequestEvent_t            v4routeRequest;
		ATTV4QueryAgentStateConfEvent_t     v4queryAgentState;
		ATTV4QueryDeviceNameConfEvent_t     v4queryDeviceName;
		ATTV4MonitorConfEvent_t             v4monitorStart;
		ATTV4MonitorCallConfEvent_t         v4monitorCallStart;
		ATTV4NetworkReachedEvent_t          v4networkReachedEvent;

		/*
		 * The following private data version 5 events have been superceded
		 * by new events in private data version 6.
		 */
		ATTV5QueryAgentStateConfEvent_t     v5queryAgentState;
		ATTV5RouteRequestEvent_t            v5routeRequest;
		ATTV5TransferredEvent_t             v5transferredEvent;
		ATTV5ConferencedEvent_t             v5conferencedEvent;
		ATTV5ConnectionClearedEvent_t       v5connectionClearedEvent;
		ATTV5OriginatedEvent_t              v5originatedEvent;
		ATTV5EstablishedEvent_t             v5establishedEvent;
		ATTV5DeliveredEvent_t               v5deliveredEvent;

		/*
		 * The following private data version 6 events have been superceded
		 * by new events in private data version 7.
		 */
		ATTV6NetworkReachedEvent_t          v6networkReachedEvent;
		ATTV6ConferencedEvent_t             v6conferencedEvent;
		ATTV6DeliveredEvent_t               v6deliveredEvent;
		ATTV6EstablishedEvent_t             v6establishedEvent;
		ATTV6TransferredEvent_t             v6transferredEvent;
		ATTV6QueryDeviceNameConfEvent_t     v6queryDeviceName;
		ATTV6GetAPICapsConfEvent_t          v6getAPICaps;
		ATTV6ConnectionClearedEvent_t       v6connectionClearedEvent;
		ATTV6RouteRequestEvent_t            v6routeRequest;

		/*
		 * The following private data version 7 event has been superceded
		 * by a new event in private data version 8.
		 */
		ATTV7FailedEvent_t                  v7failedEvent;

		/*
		 * The following private data version 8 events have been superceded
		 * by new events in private data version 9.
		 */
		ATTV8OriginatedEvent_t                  v8originatedEvent;
		ATTV8ServiceInitiatedEvent_t            v8serviceInitiated;
		ATTV8SingleStepTransferCallConfEvent_t  v8ssTransferCallConf;

		/* events received by the G3PD */

		ATTClearConnection_t                clearConnectionReq;
		ATTConsultationCall_t               consultationCallReq;
		ATTMakeCall_t                       makeCallReq;
		ATTDirectAgentCall_t                directAgentCallReq;
		ATTMakePredictiveCall_t             makePredictiveCallReq;
		ATTSupervisorAssistCall_t           supervisorAssistCallReq;
		ATTReconnectCall_t                  reconnectCallReq;
		ATTSendDTMFTone_t                   sendDTMFToneReq;
		ATTSingleStepConferenceCall_t       ssconferenceReq;
		ATTSelectiveListeningHold_t         slholdReq;
		ATTSelectiveListeningRetrieve_t     slretrieveReq;
		ATTSetAgentState_t                  setAgentStateReq;
		ATTQueryAgentState_t                queryAgentStateReq;
		ATTQueryAcdSplit_t                  queryAcdSplitReq;
		ATTQueryAgentLogin_t                queryAgentLoginReq;
		ATTQueryCallClassifier_t            queryCallClassifierReq;
		ATTQueryDeviceName_t                queryDeviceNameReq;
		ATTQueryStationStatus_t             queryStationStatusReq;
		ATTQueryTod_t                       queryTodReq;
		ATTQueryTg_t                        queryTgReq;
		ATTQueryAgentMeasurements_t         queryAgentMeasReq;
		ATTQuerySplitSkillMeasurements_t    querySplitSkillMeasReq;
		ATTQueryTrunkGroupMeasurements_t    queryTrunkGroupMeasReq;
		ATTQueryVdnMeasurements_t           queryVdnMeasReq;
		ATTMonitorFilter_t                  monitorFilterReq;
		ATTMonitorStopOnCall_t              monitorStopOnCallReq;
		ATTRouteSelect_t                    routeSelectReq;
		ATTSysStat_t                        sysStatReq;
		ATTSetBillRate_t                    setBillRateReq;
		ATTQueryUcid_t                      queryUCIDReq;
		ATTSetAdviceOfCharge_t              adviceOfChargeReq;
		ATTSingleStepTransferCall_t         ssTransferCallReq;
		ATTMonitorCallsViaDevice_t          monitorCallsViaDeviceReq;

		/* private data version 4 */
		ATTV4SendDTMFTone_t                 v4sendDTMFToneReq;
		ATTV4SetAgentState_t                v4setAgentStateReq;
		ATTV4MonitorFilter_t                v4monitorFilterReq;

		/* private data version 5 */
		ATTV5SetAgentState_t                v5setAgentStateReq;
		ATTV5ClearConnection_t              v5clearConnectionReq;
		ATTV5ConsultationCall_t             v5consultationCallReq;
		ATTV5MakeCall_t                     v5makeCallReq;
		ATTV5DirectAgentCall_t              v5directAgentCallReq;
		ATTV5MakePredictiveCall_t           v5makePredictiveCallReq;
		ATTV5SupervisorAssistCall_t         v5supervisorAssistCallReq;
		ATTV5ReconnectCall_t                v5reconnectCallReq;
		ATTV5RouteSelect_t                  v5routeSelectReq;

		/* private data version 6 */
		ATTV6RouteSelect_t                  v6routeSelectReq;

    } u;
    char    heap[ATTPRIV_MAX_HEAP];

} ATTEvent_t;

/* function prototypes */

#ifdef __cplusplus
extern "C"
{
#endif

TSAPI
attMakeVersionString(	CONST_PARAM char FAR *	requestedVersion,
						char FAR *				supportedVersion);

/********* ATT Private Data Encoding Function *******/
TSAPI
encodePrivate(	int						pdunum,
				CONST_PARAM void FAR *	pdu,
				ATTPrivateData_t FAR *	priv);

/********* ATT Private Data Decoding Function *******/

TSAPI
attPrivateData(	CONST_PARAM ATTPrivateData_t FAR *	privateData,
				ATTEvent_t FAR *					eventBuffer);


/********* ATT Private Data Encoding Functions *******/

TSAPI
attClearConnection(	ATTPrivateData_t FAR *					privateData,
					ATTDropResource_t						dropResource,
					CONST_PARAM ATTV5UserToUserInfo_t FAR *	userInfo);


TSAPI
attConsultationCall(ATTPrivateData_t FAR *					privateData,
					CONST_PARAM DeviceID_t FAR *			destRoute,
					Boolean									priorityCalling,
					CONST_PARAM ATTV5UserToUserInfo_t FAR *	userInfo);


TSAPI
attMakeCall(ATTPrivateData_t FAR *					privateData,
			CONST_PARAM DeviceID_t FAR *			destRoute,
			Boolean									priorityCalling,
			CONST_PARAM ATTV5UserToUserInfo_t	FAR *	userInfo);


TSAPI
attDirectAgentCall(	ATTPrivateData_t FAR *					privateData,
					CONST_PARAM DeviceID_t FAR *			split,
					Boolean									priorityCalling,
					CONST_PARAM ATTV5UserToUserInfo_t	FAR *	userInfo);


TSAPI
attMakePredictiveCall(	ATTPrivateData_t FAR *					privateData,
						Boolean									priorityCalling,
						short									maxRings,
						ATTAnswerTreat_t						answerTreat,
						CONST_PARAM DeviceID_t FAR *			destRoute,
						CONST_PARAM ATTV5UserToUserInfo_t FAR *	userInfo);


TSAPI
attSupervisorAssistCall(ATTPrivateData_t FAR *					privateData,
						CONST_PARAM DeviceID_t FAR *			split,
						CONST_PARAM ATTV5UserToUserInfo_t FAR *	userInfo);


TSAPI
attReconnectCall(	ATTPrivateData_t FAR *					privateData,
					ATTDropResource_t						dropResource,
					CONST_PARAM ATTV5UserToUserInfo_t	FAR *	userInfo);


TSAPI
attSendDTMFTone(ATTPrivateData_t FAR *				privateData,
				CONST_PARAM ConnectionID_t FAR *	sender,
				CONST_PARAM ATTV4ConnIDList_t FAR *	receivers,
				CONST_PARAM char FAR *				tones,
				short								toneDuration,
				short								pauseDuration);


TSAPI
attSetAgentState(	ATTPrivateData_t FAR *	privateData,
					ATTWorkMode_t			workMode);


TSAPI
attQueryAcdSplit(	ATTPrivateData_t	FAR *		privateData,
					CONST_PARAM DeviceID_t FAR *	device);


TSAPI
attQueryAgentLogin(	ATTPrivateData_t FAR *			privateData,
					CONST_PARAM DeviceID_t FAR *	device);


TSAPI
attQueryAgentState(	ATTPrivateData_t FAR *			privateData,
					CONST_PARAM DeviceID_t FAR *	device);


TSAPI
attQueryCallClassifier(ATTPrivateData_t	FAR * privateData);


TSAPI
attQueryDeviceName(	ATTPrivateData_t FAR *			privateData,
					CONST_PARAM DeviceID_t FAR *	device);

TSAPI
attQueryStationStatus(	ATTPrivateData_t FAR *			privateData,
						CONST_PARAM DeviceID_t FAR *	device);


TSAPI
attQueryTimeOfDay(ATTPrivateData_t FAR *privateData);


TSAPI
attQueryTrunkGroup(	ATTPrivateData_t FAR *			privateData,
					CONST_PARAM DeviceID_t FAR *	device);


TSAPI
attMonitorFilter (	ATTPrivateData_t FAR *		privateData,
					ATTV4PrivateFilter_t		privateFilter);


TSAPI
attMonitorStopOnCall (	ATTPrivateData_t FAR *				privateData,
						CSTAMonitorCrossRefID_t				monitorCrossRefID,
						CONST_PARAM ConnectionID_t FAR *	call);


TSAPI
attRouteSelect(	ATTPrivateData_t FAR *					privateData,
				CONST_PARAM DeviceID_t FAR *			callingDevice,
				CONST_PARAM DeviceID_t FAR *			directAgentCallSplit,
				Boolean									priorityCalling,
				CONST_PARAM DeviceID_t FAR *			destRoute,
				CONST_PARAM ATTUserCollectCode_t FAR *	collectCode,
				CONST_PARAM ATTUserProvidedCode_t FAR *	userProvidedCode,
				CONST_PARAM ATTV5UserToUserInfo_t FAR *	userInfo);


TSAPI
attSysStat (ATTPrivateData_t FAR *	privateData,
			Boolean					linkStatusReq);


TSAPI
attSingleStepConferenceCall(ATTPrivateData_t FAR *			privateData,
							CONST_PARAM ConnectionID_t FAR *activeCall,
							CONST_PARAM DeviceID_t FAR *	deviceToBeJoin,
							ATTParticipationType_t			participationType,
							Boolean							alertDestination);


TSAPI
attSelectiveListeningHold(ATTPrivateData_t FAR *			privateData,
						CONST_PARAM ConnectionID_t FAR *	subjectConnection,
						Boolean								allParties,
						CONST_PARAM ConnectionID_t FAR *	selectedParty);


TSAPI
attSelectiveListeningRetrieve(ATTPrivateData_t FAR *		privateData,
						CONST_PARAM ConnectionID_t FAR *	subjectConnection,
						Boolean								allParties,
						CONST_PARAM ConnectionID_t FAR *	selectedParty);


TSAPI
attSetAgentStateExt (ATTPrivateData_t FAR*	privateData,
					ATTWorkMode_t			workMode,
					long					reasonCode);


TSAPI
attSetBillRate(ATTPrivateData_t FAR *				privateData,
				CONST_PARAM ConnectionID_t FAR *	call,
				ATTBillType_t						billType,
				float								billRate);


TSAPI
attQueryUCID(ATTPrivateData_t FAR *				privateData,
			CONST_PARAM ConnectionID_t FAR *	call);


TSAPI
attSetAdviceOfCharge( ATTPrivateData_t FAR * privateData, Boolean flag);


TSAPI
attSendDTMFToneExt(ATTPrivateData_t FAR *				privateData,
					CONST_PARAM ConnectionID_t FAR *	sender,
					CONST_PARAM ATTConnIDList_t FAR *	receivers,
					CONST_PARAM char FAR *				tones,
					short								toneDuration,
					short								pauseDuration);


TSAPI
attMonitorFilterExt (ATTPrivateData_t	FAR *	privateData,
					ATTPrivateFilter_t			privateFilter);

/* V6 Private Data */

TSAPI
attV6SetAgentState (ATTPrivateData_t FAR*	privateData,
					ATTWorkMode_t			workMode,
					long					reasonCode,
					Boolean					enablePending);

TSAPI
attV6MakeCall(ATTPrivateData_t FAR *				privateData,
			CONST_PARAM DeviceID_t FAR *			destRoute,
			Boolean									priorityCalling,
			CONST_PARAM ATTUserToUserInfo_t	FAR *	userInfo);

TSAPI
attV6ClearConnection(	ATTPrivateData_t FAR *				privateData,
					ATTDropResource_t						dropResource,
					CONST_PARAM ATTUserToUserInfo_t FAR *	userInfo);

TSAPI
attV6ConsultationCall(ATTPrivateData_t FAR *				privateData,
					CONST_PARAM DeviceID_t FAR *			destRoute,
					Boolean									priorityCalling,
					CONST_PARAM ATTUserToUserInfo_t FAR *	userInfo);

TSAPI
attV6DirectAgentCall(	ATTPrivateData_t FAR *				privateData,
					CONST_PARAM DeviceID_t FAR *			split,
					Boolean									priorityCalling,
					CONST_PARAM ATTUserToUserInfo_t	FAR *	userInfo);

TSAPI
attV6MakePredictiveCall(	ATTPrivateData_t FAR *				privateData,
						Boolean									priorityCalling,
						short									maxRings,
						ATTAnswerTreat_t						answerTreat,
						CONST_PARAM DeviceID_t FAR *			destRoute,
						CONST_PARAM ATTUserToUserInfo_t FAR *	userInfo);

TSAPI
attV6SupervisorAssistCall(ATTPrivateData_t FAR *				privateData,
						CONST_PARAM DeviceID_t FAR *			split,
						CONST_PARAM ATTUserToUserInfo_t FAR *	userInfo);

TSAPI
attV6ReconnectCall(	ATTPrivateData_t FAR *					privateData,
					ATTDropResource_t						dropResource,
					CONST_PARAM ATTUserToUserInfo_t	FAR *	userInfo);

TSAPI
attV6RouteSelect(	ATTPrivateData_t FAR *				privateData,
				CONST_PARAM DeviceID_t FAR *			callingDevice,
				CONST_PARAM DeviceID_t FAR *			directAgentCallSplit,
				Boolean									priorityCalling,
				CONST_PARAM DeviceID_t FAR *			destRoute,
				CONST_PARAM ATTUserCollectCode_t FAR *	collectCode,
				CONST_PARAM ATTUserProvidedCode_t FAR *	userProvidedCode,
				CONST_PARAM ATTUserToUserInfo_t FAR *	userInfo);

TSAPI
attV7RouteSelect(	ATTPrivateData_t FAR *				privateData,
				CONST_PARAM DeviceID_t FAR *			callingDevice,
				CONST_PARAM DeviceID_t FAR *			directAgentCallSplit,
				Boolean									priorityCalling,
				CONST_PARAM DeviceID_t FAR *			destRoute,
				CONST_PARAM ATTUserCollectCode_t FAR *	collectCode,
				CONST_PARAM ATTUserProvidedCode_t FAR *	userProvidedCode,
				CONST_PARAM ATTUserToUserInfo_t FAR *	userInfo,
				CONST_PARAM ATTRedirectType_t			networkredirect);

TSAPI
attSingleStepTransferCall(ATTPrivateData_t FAR *	privateData,
				CONST_PARAM ConnectionID_t FAR *	activeCall,
				CONST_PARAM DeviceID_t FAR *		transferredTo);

TSAPI
attMonitorCallsViaDevice(	ATTPrivateData_t FAR *	privateData,
							ATTPrivateFilter_t		privateFilter,
							Boolean					flowPredictiveCallEvents);


#ifdef __cplusplus
}
#endif

/*
 * This section of the header file contains obsolete private data
 * version 1 definitions, for backward compatibility.  These functions
 * should not be used with private data version 2 and later.
 */

/*		AT&T private data templates		*/

/*
	data member of PrivateData_t partitioned into N tagged items

                |<- 1st item->|   |<- 2nd item->|   |<- 3rd item->|
     _______________________________________________________________
    |   |   |   |   |         |   |   |         |   |   |         |
    |enc| N |tag|len|  value  |tag|len|  value  |tag|len|  value  | ...
    |___|___|___|___|_________|___|___|_________|___|___|_________|_
    | 2 | 2 | 2 |    len*     | 2 |    len*     | 2 |    len*     |

	(*) value is padded to even boundary
	Intel (lo/hi) byte order is used
*/

typedef unsigned char	UINT8;
typedef unsigned short	UINT16;

/*	tags for data types */

#define	ATT_PRIV_UEC	1	/* user entered code */

/*	G3 CSTA user entered code */

#define MAX_USER_CODE	24  /* current max is 24 */
#define MAX_VDN			9

typedef struct UserEnteredCode_t
{
	UINT16	size;					/* sizeof(UserEnteredCode_t) */

	UINT8	type;					/* type of user code */

	UINT8	timeout;				/* timeout interval 0-63 (not used) */

	UINT8	indicator;				/* collect/collected indication */

	char	data[MAX_USER_CODE+1];	/* NULL terminated string of digits */

	char	collectVDN[MAX_VDN+1];	/* NULL terminated string of digits */

} UserEnteredCode_t;


/* function prototypes */

#ifdef __cplusplus
extern "C"
{
#endif

#if defined _MSDOS || defined __MSDOS__
 #define FPEXPORT	__far __pascal __export
#else
 #define FPEXPORT
#endif

void
FPEXPORT
initATTPrivate (PrivateData_t FAR *priv);

void
FPEXPORT
addATTPrivate (UINT16 itemTag, void FAR *itemPtr, PrivateData_t FAR *priv);

void *
FPEXPORT
getATTPrivate (UINT16 tag, PrivateData_t FAR *priv, UINT16 occ);

#ifdef __cplusplus
}
#endif

#endif
