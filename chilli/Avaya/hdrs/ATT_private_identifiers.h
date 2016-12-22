/*************************************************************/
/* Copyright (C) 2010 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/
/* Generated for: Avaya Inc., Basking Ridge, NJ - license 7175 for Windows */
/* Abstract syntax: ATT_private_identifiers */
/* Created: Fri Sep 17 13:50:20 2010 */
/* ASN.1 compiler version: 7.0 */
/* Code generated for runtime version 7.0 or later */
/* Target operating system: Windows NT/Windows 9x */
/* Target machine type: Intel x86 */
/* C compiler options required: -Zp8 (Microsoft) */
/* ASN.1 compiler options and file names specified:
 * -headerfile ctipdefs.h -noshortennames -nouniquepdu -externalname
 * att_asn_tbl -noconstraints -charintegers -shippable -splitheaders
 * -compat v4.1.3
 * C:\Program Files\OSS\ossasn1\win32\7.0.0\asn1dflt\asn1dflt.ms.zp8
 * attpriv.asn csta_common.asn
 */

#ifndef OSS_ATT_private_identifiers
#define OSS_ATT_private_identifiers

#include "ossship.h"

#ifndef OSS_INT32
#define OSS_INT32 int
#endif /* OSS_INT32 */

#include "CSTA_event_causes.h"
#include "CSTA_connection_states.h"
#include "CSTA_status_reporting.h"
#include "CSTA_call_connection_identifiers.h"
#include "CSTA_device_identifiers.h"


typedef enum ATTUUIProtocolType_t {
    uuiNone = -1,
    uuiUserSpecific = 0,
    uuiIa5Ascii = 4
} ATTUUIProtocolType_t;

typedef struct ATTV5UserToUserInfo_t {
    ATTUUIProtocolType_t type;
    struct {
        unsigned short  length;
        unsigned char   value[33];
    } data;
} ATTV5UserToUserInfo_t;

typedef enum ATTInterflow_t {
    laiNoInterflow = -1,
    laiAllInterflow = 0,
    laiThresholdInterflow = 1,
    laiVectoringInterflow = 2
} ATTInterflow_t;

typedef enum ATTPriority_t {
    laiNotInQueue = 0,
    laiLow = 1,
    laiMedium = 2,
    laiHigh = 3,
    laiTop = 4
} ATTPriority_t;

typedef struct ATTV4LookaheadInfo_t {
    ATTInterflow_t  type;
    ATTPriority_t   priority;
    short           hours;
    short           minutes;
    short           seconds;
    DeviceID_t      sourceVDN;
} ATTV4LookaheadInfo_t;

typedef enum ATTUserEnteredCodeType_t {
    ueNone = -1,
    ueAny = 0,
    ueLoginDigits = 2,
    ueCallPrompter = 5,
    ueDataBaseProvided = 17,
    ueToneDetector = 32
} ATTUserEnteredCodeType_t;

typedef enum ATTUserEnteredCodeIndicator_t {
    ueCollect = 0,
    ueEntered = 1
} ATTUserEnteredCodeIndicator_t;

typedef struct ATTUserEnteredCode_t {
    ATTUserEnteredCodeType_t type;
    ATTUserEnteredCodeIndicator_t indicator;
    char            data[25];
    DeviceID_t      collectVDN;
} ATTUserEnteredCode_t;

typedef struct ATTV4ConnIDList_t {
    unsigned short  count;
    ConnectionID_t  party[5];
} ATTV4ConnIDList_t;

typedef enum ATTProgressLocation_t {
    plNone = -1,
    plUser = 0,
    plPubLocal = 1,
    plPubRemote = 4,
    plPrivRemote = 5
} ATTProgressLocation_t;

typedef enum ATTProgressDescription_t {
    pdNone = -1,
    pdCallOffIsdn = 1,
    pdDestNotIsdn = 2,
    pdOrigNotIsdn = 3,
    pdCallOnIsdn = 4,
    pdInband = 8
} ATTProgressDescription_t;

typedef enum ATTWorkMode_t {
    wmNone = -1,
    wmAuxWork = 1,
    wmAftcalWk = 2,
    wmAutoIn = 3,
    wmManualIn = 4
} ATTWorkMode_t;

typedef enum ATTTalkState_t {
    tsOnCall = 0,
    tsIdle = 1
} ATTTalkState_t;

typedef enum ATTExtensionClass_t {
    ecVdn = 0,
    ecAcdSplit = 1,
    ecAnnouncement = 2,
    ecData = 4,
    ecAnalog = 5,
    ecProprietary = 6,
    ecBri = 7,
    ecCti = 8,
    ecLogicalAgent = 9,
    ecOther = 10
} ATTExtensionClass_t;

typedef enum ATTAnswerTreat_t {
    atNoTreatment = 0,
    atNone = 1,
    atDrop = 2,
    atConnect = 3
} ATTAnswerTreat_t;

typedef unsigned char   ATTMwiApplication_t;
#define                     atCti 0x10
#define                     atLwc 0x08
#define                     atPropmgt 0x04
#define                     atVoice 0x02
#define                     atMcs 0x01

typedef unsigned char   ATTV4PrivateFilter_t;
#define                     attV4EnteredDigitsFilter 0x80

typedef struct ATTV4SnapshotCall_t {
    unsigned short  count;
    CSTASnapshotCallResponseInfo_t info[6];
} ATTV4SnapshotCall_t;

typedef enum ATTLocalCallState_t {
    attCsInitiated = 1,
    attCsAlerting = 2,
    attCsConnected = 3,
    attCsHeld = 4,
    attCsBridged = 5,
    attCsOther = 6
} ATTLocalCallState_t;

typedef struct ATTSnapshotDevice_t {
    ConnectionID_t  call;
    ATTLocalCallState_t state;
} ATTSnapshotDevice_t;

typedef enum ATTCollectCodeType_t {
    ucNone = 0,
    ucToneDetector = 32
} ATTCollectCodeType_t;

typedef enum ATTProvidedCodeType_t {
    upNone = 0,
    upDataBaseProvided = 17
} ATTProvidedCodeType_t;

typedef struct ATTUserProvidedCode_t {
    ATTProvidedCodeType_t type;
    char            data[25];
} ATTUserProvidedCode_t;

typedef enum ATTSpecificEvent_t {
    seAnswer = 11,
    seDisconnect = 4
} ATTSpecificEvent_t;

typedef struct ATTUserCollectCode_t {
    ATTCollectCodeType_t type;
    short           digitsToBeCollected;
    short           timeout;
    ConnectionID_t  collectParty;
    ATTSpecificEvent_t specificEvent;
} ATTUserCollectCode_t;

typedef enum ATTDropResource_t {
    drNone = -1,
    drCallClassifier = 0,
    drToneGenerator = 1
} ATTDropResource_t;

typedef struct ATTV5ClearConnection_t {
    ATTDropResource_t dropResource;
    ATTV5UserToUserInfo_t userInfo;
} ATTV5ClearConnection_t;

typedef struct ATTV5ConsultationCall_t {
    DeviceID_t      destRoute;
    unsigned char   priorityCalling;
    ATTV5UserToUserInfo_t userInfo;
} ATTV5ConsultationCall_t;

typedef struct ATTV5MakeCall_t {
    DeviceID_t      destRoute;
    unsigned char   priorityCalling;
    ATTV5UserToUserInfo_t userInfo;
} ATTV5MakeCall_t;

typedef struct ATTV5DirectAgentCall_t {
    DeviceID_t      split;
    unsigned char   priorityCalling;
    ATTV5UserToUserInfo_t userInfo;
} ATTV5DirectAgentCall_t;

typedef struct ATTV5MakePredictiveCall_t {
    unsigned char   priorityCalling;
    short           maxRings;
    ATTAnswerTreat_t answerTreat;
    DeviceID_t      destRoute;
    ATTV5UserToUserInfo_t userInfo;
} ATTV5MakePredictiveCall_t;

typedef struct ATTV5SupervisorAssistCall_t {
    DeviceID_t      split;
    ATTV5UserToUserInfo_t userInfo;
} ATTV5SupervisorAssistCall_t;

typedef struct ATTV5ReconnectCall_t {
    ATTDropResource_t dropResource;
    ATTV5UserToUserInfo_t userInfo;
} ATTV5ReconnectCall_t;

typedef struct ATTV4SendDTMFTone_t {
    ConnectionID_t  sender;
    ATTV4ConnIDList_t receivers;
    char            tones[33];
    short           toneDuration;
    short           pauseDuration;
} ATTV4SendDTMFTone_t;

typedef struct ATTSendDTMFToneConfEvent_t {
    Nulltype        null;
} ATTSendDTMFToneConfEvent_t;

typedef struct ATTV4SetAgentState_t {
    ATTWorkMode_t   workMode;
} ATTV4SetAgentState_t;

typedef struct ATTQueryAcdSplit_t {
    DeviceID_t      device;
} ATTQueryAcdSplit_t;

typedef struct ATTQueryAcdSplitConfEvent_t {
    short           availableAgents;
    short           callsInQueue;
    short           agentsLoggedIn;
} ATTQueryAcdSplitConfEvent_t;

typedef struct ATTQueryAgentLogin_t {
    DeviceID_t      device;
} ATTQueryAgentLogin_t;

typedef long            ATTPrivEventCrossRefID_t;

typedef struct ATTQueryAgentLoginConfEvent_t {
    ATTPrivEventCrossRefID_t privEventCrossRefID;
} ATTQueryAgentLoginConfEvent_t;

typedef struct ATTQueryAgentLoginResp_t {
    ATTPrivEventCrossRefID_t privEventCrossRefID;
    struct {
        unsigned short  count;
        DeviceID_t      device[10];
    } list;
} ATTQueryAgentLoginResp_t;

typedef struct ATTQueryAgentState_t {
    DeviceID_t      split;
} ATTQueryAgentState_t;

typedef struct ATTV4QueryAgentStateConfEvent_t {
    ATTWorkMode_t   workMode;
    ATTTalkState_t  talkState;
} ATTV4QueryAgentStateConfEvent_t;

typedef struct ATTQueryCallClassifier_t {
    Nulltype        null;
} ATTQueryCallClassifier_t;

typedef struct ATTQueryCallClassifierConfEvent_t {
    short           numAvailPorts;
    short           numInUsePorts;
} ATTQueryCallClassifierConfEvent_t;

typedef struct ATTV4QueryDeviceInfoConfEvent_t {
    ATTExtensionClass_t extensionClass;
} ATTV4QueryDeviceInfoConfEvent_t;

typedef struct ATTQueryMwiConfEvent_t {
    ATTMwiApplication_t applicationType;
} ATTQueryMwiConfEvent_t;

typedef struct ATTQueryStationStatus_t {
    DeviceID_t      device;
} ATTQueryStationStatus_t;

typedef struct ATTQueryStationStatusConfEvent_t {
    unsigned char   stationStatus;
} ATTQueryStationStatusConfEvent_t;

typedef struct ATTQueryTod_t {
    Nulltype        null;
} ATTQueryTod_t;

typedef struct ATTQueryTodConfEvent_t {
    short           year;
    short           month;
    short           day;
    short           hour;
    short           minute;
    short           second;
} ATTQueryTodConfEvent_t;

typedef struct ATTQueryTg_t {
    DeviceID_t      device;
} ATTQueryTg_t;

typedef struct ATTQueryTgConfEvent_t {
    short           idleTrunks;
    short           usedTrunks;
} ATTQueryTgConfEvent_t;

typedef struct ATTV4SnapshotDeviceConfEvent_t {
    unsigned short  count;
    ATTSnapshotDevice_t snapshotDevice[6];
} ATTV4SnapshotDeviceConfEvent_t;

typedef struct ATTV4MonitorFilter_t {
    ATTV4PrivateFilter_t privateFilter;
} ATTV4MonitorFilter_t;

typedef struct ATTV4MonitorConfEvent_t {
    ATTV4PrivateFilter_t usedFilter;
} ATTV4MonitorConfEvent_t;

typedef struct ATTMonitorStopOnCall_t {
    CSTAMonitorCrossRefID_t monitorCrossRefID;
    ConnectionID_t  call;
} ATTMonitorStopOnCall_t;

typedef struct ATTMonitorStopOnCallConfEvent_t {
    Nulltype        null;
} ATTMonitorStopOnCallConfEvent_t;

typedef struct ATTV4MonitorCallConfEvent_t {
    ATTV4PrivateFilter_t usedFilter;
    ATTV4SnapshotCall_t snapshotCall;
} ATTV4MonitorCallConfEvent_t;

typedef enum ATTReasonCode_t {
    arNone = 0,
    arAnswerNormal = 1,
    arAnswerTimed = 2,
    arAnswerVoiceEnergy = 3,
    arAnswerMachineDetected = 4,
    arSitReorder = 5,
    arSitNoCircuit = 6,
    arSitIntercept = 7,
    arSitVacantCode = 8,
    arSitIneffectiveOther = 9,
    arSitUnknown = 10,
    arInQueue = 11,
    arServiceObserver = 12
} ATTReasonCode_t;

typedef enum ATTReasonForCallInfo_t {
    orNone = 0,
    orConsultation = 1,
    orConferenced = 2,
    orTransferred = 3,
    orNewCall = 4
} ATTReasonForCallInfo_t;

typedef struct ATTV4OriginalCallInfo_t {
    ATTReasonForCallInfo_t reason;
    CallingDeviceID_t callingDevice;
    CalledDeviceID_t calledDevice;
    DeviceID_t      trunk;
    DeviceID_t      trunkMember;
    ATTV4LookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTV5UserToUserInfo_t userInfo;
} ATTV4OriginalCallInfo_t;

typedef struct ATTCallClearedEvent_t {
    ATTReasonCode_t reason;
} ATTCallClearedEvent_t;

typedef struct ATTV3ConferencedEvent_t {
    ATTV4OriginalCallInfo_t originalCallInfo;
} ATTV3ConferencedEvent_t;

typedef struct ATTV5ConnectionClearedEvent_t {
    ATTV5UserToUserInfo_t userInfo;
} ATTV5ConnectionClearedEvent_t;

typedef enum ATTDeliveredType_t {
    deliveredToAcd = 1,
    deliveredToStation = 2,
    deliveredOther = 3
} ATTDeliveredType_t;

typedef struct ATTV3DeliveredEvent_t {
    ATTDeliveredType_t deliveredType;
    DeviceID_t      trunk;
    DeviceID_t      trunkMember;
    DeviceID_t      split;
    ATTV4LookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTV5UserToUserInfo_t userInfo;
    ATTReasonCode_t reason;
    ATTV4OriginalCallInfo_t originalCallInfo;
} ATTV3DeliveredEvent_t;

typedef struct ATTEnteredDigitsEvent_t {
    ConnectionID_t  connection;
    char            digits[25];
    LocalConnectionState_t localConnectionInfo;
    CSTAEventCause_t cause;
} ATTEnteredDigitsEvent_t;

typedef struct ATTV3EstablishedEvent_t {
    DeviceID_t      trunk;
    DeviceID_t      trunkMember;
    DeviceID_t      split;
    ATTV4LookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTV5UserToUserInfo_t userInfo;
    ATTReasonCode_t reason;
    ATTV4OriginalCallInfo_t originalCallInfo;
} ATTV3EstablishedEvent_t;

typedef struct ATTV4NetworkReachedEvent_t {
    ATTProgressLocation_t progressLocation;
    ATTProgressDescription_t progressDescription;
} ATTV4NetworkReachedEvent_t;

typedef struct ATTV3TransferredEvent_t {
    ATTV4OriginalCallInfo_t originalCallInfo;
} ATTV3TransferredEvent_t;

typedef struct ATTV4RouteRequestEvent_t {
    DeviceID_t      trunk;
    ATTV4LookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTV5UserToUserInfo_t userInfo;
} ATTV4RouteRequestEvent_t;

typedef struct ATTV5RouteSelect_t {
    DeviceID_t      callingDevice;
    DeviceID_t      directAgentCallSplit;
    unsigned char   priorityCalling;
    DeviceID_t      destRoute;
    ATTUserCollectCode_t collectCode;
    ATTUserProvidedCode_t userProvidedCode;
    ATTV5UserToUserInfo_t userInfo;
} ATTV5RouteSelect_t;

typedef struct ATTRouteUsedEvent_t {
    DeviceID_t      destRoute;
} ATTRouteUsedEvent_t;

typedef struct ATTSysStat_t {
    unsigned char   linkStatusReq;
} ATTSysStat_t;

typedef enum ATTLinkState_t {
    lsLinkUnavail = 0,
    lsLinkUp = 1,
    lsLinkDown = 2
} ATTLinkState_t;

typedef struct ATTLinkStatus_t {
    short           linkID;
    ATTLinkState_t  linkState;
} ATTLinkStatus_t;

typedef struct ATTV3LinkStatusEvent_t {
    unsigned short  count;
    ATTLinkStatus_t linkStatus[4];
} ATTV3LinkStatusEvent_t;

typedef struct ATTV5OriginatedEvent_t {
    DeviceID_t      logicalAgent;
    ATTV5UserToUserInfo_t userInfo;
} ATTV5OriginatedEvent_t;

typedef struct ATTLoggedOnEvent_t {
    ATTWorkMode_t   workMode;
} ATTLoggedOnEvent_t;

typedef enum ATTDeviceType_t {
    attDtUnknown = 0,
    attDtAcdSplit = 1,
    attDtAnnouncement = 2,
    attDtData = 3,
    attDtLogicalAgent = 4,
    attDtStation = 5,
    attDtTrunkAccessCode = 6,
    attDtVdn = 7,
    attDtOther = 8
} ATTDeviceType_t;

typedef struct ATTQueryDeviceName_t {
    DeviceID_t      device;
} ATTQueryDeviceName_t;

typedef struct ATTV4QueryDeviceNameConfEvent_t {
    ATTDeviceType_t deviceType;
    DeviceID_t      device;
    char            name[16];
} ATTV4QueryDeviceNameConfEvent_t;

typedef enum ATTAgentTypeID_t {
    extensionId = 0,
    logicalId = 1
} ATTAgentTypeID_t;

typedef enum ATTSplitSkill_t {
    splitSkillNone = -1,
    splitSkillAll = 0,
    splitSkill1 = 1,
    splitSkill2 = 2,
    splitSkill3 = 3,
    splitSkill4 = 4
} ATTSplitSkill_t;

typedef short           ATTInterval_t;
#define                     intvCurrent -1
#define                     intvDay -2
#define                     intvLast -3

typedef struct ATTAgentMeasurements_t {
    long            acdCalls;
    char            extension[6];
    char            name[16];
    unsigned char   state;
    long            avgACDTalkTime;
    long            avgExtensionTime;
    long            callRate;
    short           elapsedTime;
    long            extensionCalls;
    long            extensionIncomingCalls;
    long            extensionOutgoingCalls;
    long            shiftACDCalls;
    long            shiftAvgACDTalkTime;
    short           splitAcceptableSvcLevel;
    long            splitACDCalls;
    long            splitAfterCallSessions;
    short           splitAgentsAvailable;
    short           splitAgentsInAfterCall;
    short           splitAgentsInAux;
    short           splitAgentsInOther;
    short           splitAgentsOnACDCalls;
    short           splitAgentsOnExtCalls;
    short           splitAgentsStaffed;
    long            splitAvgACDTalkTime;
    long            splitAvgAfterCallTime;
    short           splitAvgSpeedOfAnswer;
    short           splitAvgTimeToAbandon;
    long            splitCallRate;
    long            splitCallsAbandoned;
    long            splitCallsFlowedIn;
    long            splitCallsFlowedOut;
    short           splitCallsWaiting;
    char            splitName[16];
    short           splitNumber;
    char            splitExtension[6];
    char            splitObjective[6];
    short           splitOldestCallWaiting;
    unsigned char   splitPercentInSvcLevel;
    long            splitTotalACDTalkTime;
    long            splitTotalAfterCallTime;
    long            splitTotalAuxTime;
    long            timeAgentEnteredState;
    long            totalACDTalkTime;
    long            totalAfterCallTime;
    long            totalAuxTime;
    long            totalAvailableTime;
    long            totalHoldTime;
    long            totalStaffedTime;
    long            totalACDCallTime;
    long            avgACDCallTime;
} ATTAgentMeasurements_t;

typedef struct ATTSplitSkillMeasurements_t {
    short           acceptableSvcLevel;
    long            acdCalls;
    long            afterCallSessions;
    short           agentsAvailable;
    short           agentsInAfterCall;
    short           agentsInAux;
    short           agentsInOther;
    short           onACDCalls;
    short           agentsOnExtensionCalls;
    short           agentsStaffed;
    long            avgACDTalkTime;
    long            afterCallTime;
    short           avgSpeedOfAnswer;
    short           avgTimeToAbandon;
    long            callRate;
    long            callsAbandoned;
    long            callsFlowedIn;
    long            callsFlowedOut;
    short           callsWaiting;
    short           oldestCallWaiting;
    unsigned char   percentInSvcLevel;
    char            name[16];
    char            extension[6];
    short           number;
    char            objective[6];
    long            totalAfterCallTime;
    long            totalAuxTime;
    long            totalACDTalkTime;
} ATTSplitSkillMeasurements_t;

typedef struct ATTTrunkGroupMeasurements_t {
    long            avgIncomingCallTime;
    long            avgOutgoingCallTime;
    long            incomingAbandonedCalls;
    long            incomingCalls;
    long            incomingUsage;
    short           numberOfTrunks;
    long            outgoingCalls;
    long            outgoingCompletedCalls;
    long            outgoingUsage;
    unsigned char   percentAllTrunksBusy;
    unsigned char   percentTrunksMaintBusy;
    char            trunkGroupName[16];
    short           trunkGroupNumber;
    short           trunksInUse;
    short           trunksMaintBusy;
} ATTTrunkGroupMeasurements_t;

typedef struct ATTVdnMeasurements_t {
    short           acceptableSvcLevel;
    long            acdCalls;
    long            avgACDTalkTime;
    short           avgSpeedOfAnswer;
    short           avgTimeToAbandon;
    long            callsAbandoned;
    long            callsFlowedOut;
    long            callsForcedBusyDisc;
    long            callsOffered;
    short           callsWaiting;
    long            callsNonACD;
    short           oldestCallWaiting;
    unsigned char   percentInSvcLevel;
    long            totalACDTalkTime;
    char            extension[6];
    char            name[16];
} ATTVdnMeasurements_t;

typedef struct ATTAgentMeasurementsPresent_t {
    unsigned char   allMeasurements;
    unsigned char   acdCalls;
    unsigned char   extension;
    unsigned char   name;
    unsigned char   state;
    unsigned char   avgACDTalkTime;
    unsigned char   avgExtensionTime;
    unsigned char   callRate;
    unsigned char   elapsedTime;
    unsigned char   extensionCalls;
    unsigned char   extensionIncomingCalls;
    unsigned char   extensionOutgoingCalls;
    unsigned char   shiftACDCalls;
    unsigned char   shiftAvgACDTalkTime;
    unsigned char   splitAcceptableSvcLevel;
    unsigned char   splitACDCalls;
    unsigned char   splitAfterCallSessions;
    unsigned char   splitAgentsAvailable;
    unsigned char   splitAgentsInAfterCall;
    unsigned char   splitAgentsInAux;
    unsigned char   splitAgentsInOther;
    unsigned char   splitAgentsOnACDCalls;
    unsigned char   splitAgentsOnExtCalls;
    unsigned char   splitAgentsStaffed;
    unsigned char   splitAvgACDTalkTime;
    unsigned char   splitAvgAfterCallTime;
    unsigned char   splitAvgSpeedOfAnswer;
    unsigned char   splitAvgTimeToAbandon;
    unsigned char   splitCallRate;
    unsigned char   splitCallsAbandoned;
    unsigned char   splitCallsFlowedIn;
    unsigned char   splitCallsFlowedOut;
    unsigned char   splitCallsWaiting;
    unsigned char   splitName;
    unsigned char   splitNumber;
    unsigned char   splitExtension;
    unsigned char   splitObjective;
    unsigned char   splitOldestCallWaiting;
    unsigned char   splitPercentInSvcLevel;
    unsigned char   splitTotalACDTalkTime;
    unsigned char   splitTotalAfterCallTime;
    unsigned char   splitTotalAuxTime;
    unsigned char   timeAgentEnteredState;
    unsigned char   totalACDTalkTime;
    unsigned char   totalAfterCallTime;
    unsigned char   totalAuxTime;
    unsigned char   totalAvailableTime;
    unsigned char   totalHoldTime;
    unsigned char   totalStaffedTime;
    unsigned char   totalACDCallTime;
    unsigned char   avgACDCallTime;
} ATTAgentMeasurementsPresent_t;

typedef struct ATTSplitSkillMeasurementsPresent_t {
    unsigned char   allMeasurements;
    unsigned char   acceptableSvcLevel;
    unsigned char   acdCalls;
    unsigned char   afterCallSessions;
    unsigned char   agentsAvailable;
    unsigned char   agentsInAfterCall;
    unsigned char   agentsInAux;
    unsigned char   agentsInOther;
    unsigned char   onACDCalls;
    unsigned char   agentsOnExtensionCalls;
    unsigned char   agentsStaffed;
    unsigned char   avgACDTalkTime;
    unsigned char   afterCallTime;
    unsigned char   avgSpeedOfAnswer;
    unsigned char   avgTimeToAbandon;
    unsigned char   callRate;
    unsigned char   callsAbandoned;
    unsigned char   callsFlowedIn;
    unsigned char   callsFlowedOut;
    unsigned char   callsWaiting;
    unsigned char   oldestCallWaiting;
    unsigned char   percentInSvcLevel;
    unsigned char   name;
    unsigned char   extension;
    unsigned char   number;
    unsigned char   objective;
    unsigned char   totalAfterCallTime;
    unsigned char   totalAuxTime;
    unsigned char   totalACDTalkTime;
} ATTSplitSkillMeasurementsPresent_t;

typedef struct ATTTrunkGroupMeasurementsPresent_t {
    unsigned char   allMeasurements;
    unsigned char   avgIncomingCallTime;
    unsigned char   avgOutgoingCallTime;
    unsigned char   incomingAbandonedCalls;
    unsigned char   incomingCalls;
    unsigned char   incomingUsage;
    unsigned char   numberOfTrunks;
    unsigned char   outgoingCalls;
    unsigned char   outgoingCompletedCalls;
    unsigned char   outgoingUsage;
    unsigned char   percentAllTrunksBusy;
    unsigned char   percentTrunksMaintBusy;
    unsigned char   trunkGroupName;
    unsigned char   trunkGroupNumber;
    unsigned char   trunksInUse;
    unsigned char   trunksMaintBusy;
} ATTTrunkGroupMeasurementsPresent_t;

typedef struct ATTVdnMeasurementsPresent_t {
    unsigned char   allMeasurements;
    unsigned char   acceptableSvcLevel;
    unsigned char   acdCalls;
    unsigned char   avgACDTalkTime;
    unsigned char   avgSpeedOfAnswer;
    unsigned char   avgTimeToAbandon;
    unsigned char   callsAbandoned;
    unsigned char   callsFlowedOut;
    unsigned char   callsForcedBusyDisc;
    unsigned char   callsOffered;
    unsigned char   callsWaiting;
    unsigned char   callsNonACD;
    unsigned char   oldestCallWaiting;
    unsigned char   percentInSvcLevel;
    unsigned char   totalACDTalkTime;
    unsigned char   extension;
    unsigned char   name;
} ATTVdnMeasurementsPresent_t;

typedef struct ATTQueryAgentMeasurements_t {
    DeviceID_t      agentID;
    ATTAgentTypeID_t typeID;
    ATTSplitSkill_t splitSkill;
    ATTAgentMeasurementsPresent_t requestItems;
    ATTInterval_t   interval;
} ATTQueryAgentMeasurements_t;

typedef struct ATTQueryAgentMeasurementsConfEvent_t {
    ATTAgentMeasurementsPresent_t returnedItems;
    ATTAgentMeasurements_t values;
} ATTQueryAgentMeasurementsConfEvent_t;

typedef struct ATTQuerySplitSkillMeasurements_t {
    DeviceID_t      device;
    ATTSplitSkillMeasurementsPresent_t requestItems;
    ATTInterval_t   interval;
} ATTQuerySplitSkillMeasurements_t;

typedef struct ATTQuerySplitSkillMeasurementsConfEvent_t {
    ATTSplitSkillMeasurementsPresent_t returnedItems;
    ATTSplitSkillMeasurements_t values;
} ATTQuerySplitSkillMeasurementsConfEvent_t;

typedef struct ATTQueryTrunkGroupMeasurements_t {
    DeviceID_t      device;
    ATTTrunkGroupMeasurementsPresent_t requestItems;
    ATTInterval_t   interval;
} ATTQueryTrunkGroupMeasurements_t;

typedef struct ATTQueryTrunkGroupMeasurementsConfEvent_t {
    ATTTrunkGroupMeasurementsPresent_t returnedItems;
    ATTTrunkGroupMeasurements_t values;
} ATTQueryTrunkGroupMeasurementsConfEvent_t;

typedef struct ATTQueryVdnMeasurements_t {
    DeviceID_t      device;
    ATTVdnMeasurementsPresent_t requestItems;
    ATTInterval_t   interval;
} ATTQueryVdnMeasurements_t;

typedef struct ATTQueryVdnMeasurementsConfEvent_t {
    ATTVdnMeasurementsPresent_t returnedItems;
    ATTVdnMeasurements_t values;
} ATTQueryVdnMeasurementsConfEvent_t;

typedef struct ATTV4ConferencedEvent_t {
    ATTV4OriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
} ATTV4ConferencedEvent_t;

typedef struct ATTV4DeliveredEvent_t {
    ATTDeliveredType_t deliveredType;
    DeviceID_t      trunk;
    DeviceID_t      trunkMember;
    DeviceID_t      split;
    ATTV4LookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTV5UserToUserInfo_t userInfo;
    ATTReasonCode_t reason;
    ATTV4OriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
} ATTV4DeliveredEvent_t;

typedef struct ATTV4EstablishedEvent_t {
    DeviceID_t      trunk;
    DeviceID_t      trunkMember;
    DeviceID_t      split;
    ATTV4LookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTV5UserToUserInfo_t userInfo;
    ATTReasonCode_t reason;
    ATTV4OriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
} ATTV4EstablishedEvent_t;

typedef struct ATTV4TransferredEvent_t {
    ATTV4OriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
} ATTV4TransferredEvent_t;

typedef struct ATTV4LinkStatusEvent_t {
    unsigned short  count;
    ATTLinkStatus_t linkStatus[8];
} ATTV4LinkStatusEvent_t;

typedef struct ATTV4GetAPICapsConfEvent_t {
    char            switchVersion[16];
    unsigned char   sendDTMFTone;
    unsigned char   enteredDigitsEvent;
    unsigned char   queryDeviceName;
    unsigned char   queryAgentMeas;
    unsigned char   querySplitSkillMeas;
    unsigned char   queryTrunkGroupMeas;
    unsigned char   queryVdnMeas;
    unsigned char   reserved1;
    unsigned char   reserved2;
} ATTV4GetAPICapsConfEvent_t;

typedef enum ATTParticipationType_t {
    ptActive = 1,
    ptSilent = 0
} ATTParticipationType_t;

typedef char            ATTUCID_t[64];

typedef struct ATTSingleStepConferenceCall_t {
    ConnectionID_t  activeCall;
    DeviceID_t      deviceToBeJoin;
    ATTParticipationType_t participationType;
    unsigned char   alertDestination;
} ATTSingleStepConferenceCall_t;

typedef struct ATTSingleStepConferenceCallConfEvent_t {
    ConnectionID_t  newCall;
    ConnectionList_t connList;
    ATTUCID_t       ucid;
} ATTSingleStepConferenceCallConfEvent_t;

typedef struct ATTSelectiveListeningHold_t {
    ConnectionID_t  subjectConnection;
    unsigned char   allParties;
    ConnectionID_t  selectedParty;
} ATTSelectiveListeningHold_t;

typedef struct ATTSelectiveListeningHoldConfEvent_t {
    Nulltype        null;
} ATTSelectiveListeningHoldConfEvent_t;

typedef struct ATTSelectiveListeningRetrieve_t {
    ConnectionID_t  subjectConnection;
    unsigned char   allParties;
    ConnectionID_t  selectedParty;
} ATTSelectiveListeningRetrieve_t;

typedef struct ATTSelectiveListeningRetrieveConfEvent_t {
    Nulltype        null;
} ATTSelectiveListeningRetrieveConfEvent_t;

typedef struct ATTUnicodeDeviceID {
    unsigned short  count;
    short           value[64];
} ATTUnicodeDeviceID;

typedef struct ATTLookaheadInfo_t {
    ATTInterflow_t  type;
    ATTPriority_t   priority;
    short           hours;
    short           minutes;
    short           seconds;
    DeviceID_t      sourceVDN;
    ATTUnicodeDeviceID uSourceVDN;
} ATTLookaheadInfo_t;

typedef struct ATTCallOriginatorInfo_t {
    unsigned char   hasInfo;
    short           callOriginatorType;
} ATTCallOriginatorInfo_t;

typedef struct ATTV5OriginalCallInfo_t {
    ATTReasonForCallInfo_t reason;
    CallingDeviceID_t callingDevice;
    CalledDeviceID_t calledDevice;
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
    ATTLookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTV5UserToUserInfo_t userInfo;
    ATTUCID_t       ucid;
    ATTCallOriginatorInfo_t callOriginatorInfo;
    unsigned char   flexibleBilling;
} ATTV5OriginalCallInfo_t;

typedef struct ATTConnIDList_t {
    unsigned int    count;
    ConnectionID_t  *pParty;
} ATTConnIDList_t;

typedef struct ATTSendDTMFTone_t {
    ConnectionID_t  sender;
    ATTConnIDList_t receivers;
    char            tones[33];
    short           toneDuration;
    short           pauseDuration;
} ATTSendDTMFTone_t;

typedef struct ATTSnapshotDeviceConfEvent_t {
    unsigned int    count;
    ATTSnapshotDevice_t *pSnapshotDevice;
} ATTSnapshotDeviceConfEvent_t;

typedef struct ATTLinkStatusEvent_t {
    unsigned int    count;
    ATTLinkStatus_t *pLinkStatus;
} ATTLinkStatusEvent_t;

typedef enum ATTBillType_t {
    btNewRate = 16,
    btFlatRate = 17,
    btPremiumCharge = 18,
    btPremiumCredit = 19,
    btFreeCall = 24
} ATTBillType_t;

typedef struct ATTSetBillRate_t {
    ConnectionID_t  call;
    ATTBillType_t   billType;
    float           billRate;
} ATTSetBillRate_t;

typedef struct ATTSetBillRateConfEvent_t {
    Nulltype        null;
} ATTSetBillRateConfEvent_t;

typedef struct ATTQueryUcid_t {
    ConnectionID_t  call;
} ATTQueryUcid_t;

typedef struct ATTQueryUcidConfEvent_t {
    ATTUCID_t       ucid;
} ATTQueryUcidConfEvent_t;

typedef struct ATTV5ConferencedEvent_t {
    ATTV5OriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
    ATTUCID_t       ucid;
} ATTV5ConferencedEvent_t;

typedef struct ATTLoggedOffEvent_t {
    long            reasonCode;
} ATTLoggedOffEvent_t;

typedef struct ATTV5DeliveredEvent_t {
    ATTDeliveredType_t deliveredType;
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
    DeviceID_t      split;
    ATTLookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTV5UserToUserInfo_t userInfo;
    ATTReasonCode_t reason;
    ATTV5OriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
    ATTUCID_t       ucid;
    ATTCallOriginatorInfo_t callOriginatorInfo;
    unsigned char   flexibleBilling;
} ATTV5DeliveredEvent_t;

typedef struct ATTV5EstablishedEvent_t {
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
    DeviceID_t      split;
    ATTLookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTV5UserToUserInfo_t userInfo;
    ATTReasonCode_t reason;
    ATTV5OriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
    ATTUCID_t       ucid;
    ATTCallOriginatorInfo_t callOriginatorInfo;
    unsigned char   flexibleBilling;
} ATTV5EstablishedEvent_t;

typedef struct ATTV5TransferredEvent_t {
    ATTV5OriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
    ATTUCID_t       ucid;
} ATTV5TransferredEvent_t;

typedef struct ATTV5RouteRequestEvent_t {
    DeviceID_t      trunkGroup;
    ATTLookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTV5UserToUserInfo_t userInfo;
    ATTUCID_t       ucid;
    ATTCallOriginatorInfo_t callOriginatorInfo;
    unsigned char   flexibleBilling;
} ATTV5RouteRequestEvent_t;

typedef unsigned char   ATTPrivateFilter_t;
#define                     attEnteredDigitsFilter 0x80
#define                     attChargeAdviceFilter 0x40

typedef struct ATTConsultationCallConfEvent_t {
    ATTUCID_t       ucid;
} ATTConsultationCallConfEvent_t;

typedef struct ATTMakeCallConfEvent_t {
    ATTUCID_t       ucid;
} ATTMakeCallConfEvent_t;

typedef struct ATTMakePredictiveCallConfEvent_t {
    ATTUCID_t       ucid;
} ATTMakePredictiveCallConfEvent_t;

typedef struct ATTV5SetAgentState_t {
    ATTWorkMode_t   workMode;
    long            reasonCode;
} ATTV5SetAgentState_t;

typedef struct ATTV5QueryAgentStateConfEvent_t {
    ATTWorkMode_t   workMode;
    ATTTalkState_t  talkState;
    long            reasonCode;
} ATTV5QueryAgentStateConfEvent_t;

typedef struct ATTV6QueryDeviceNameConfEvent_t {
    ATTDeviceType_t deviceType;
    DeviceID_t      device;
    DeviceID_t      name;
    ATTUnicodeDeviceID uname;
} ATTV6QueryDeviceNameConfEvent_t;

typedef struct ATTConferenceCallConfEvent_t {
    ATTUCID_t       ucid;
} ATTConferenceCallConfEvent_t;

typedef struct ATTTransferCallConfEvent_t {
    ATTUCID_t       ucid;
} ATTTransferCallConfEvent_t;

typedef struct ATTMonitorFilter_t {
    ATTPrivateFilter_t privateFilter;
} ATTMonitorFilter_t;

typedef struct ATTMonitorConfEvent_t {
    ATTPrivateFilter_t usedFilter;
} ATTMonitorConfEvent_t;

typedef struct ATTSnapshotCall_t {
    unsigned int    count;
    CSTASnapshotCallResponseInfo_t *pInfo;
} ATTSnapshotCall_t;

typedef struct ATTMonitorCallConfEvent_t {
    ATTPrivateFilter_t usedFilter;
    ATTSnapshotCall_t snapshotCall;
} ATTMonitorCallConfEvent_t;

typedef struct ATTV8ServiceInitiatedEvent_t {
    ATTUCID_t       ucid;
} ATTV8ServiceInitiatedEvent_t;

typedef enum ATTChargeType_t {
    ctIntermediateCharge = 1,
    ctFinalCharge = 2,
    ctSplitCharge = 3
} ATTChargeType_t;

typedef enum ATTChargeError_t {
    ceNone = 0,
    ceNoFinalCharge = 1,
    ceLessFinalCharge = 2,
    ceChargeTooLarge = 3,
    ceNetworkBusy = 4
} ATTChargeError_t;

typedef struct ATTChargeAdviceEvent_t {
    ConnectionID_t  connection;
    DeviceID_t      calledDevice;
    DeviceID_t      chargingDevice;
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
    ATTChargeType_t chargeType;
    long            charge;
    ATTChargeError_t error;
} ATTChargeAdviceEvent_t;

typedef struct ATTV6GetAPICapsConfEvent_t {
    char            switchVersion[16];
    unsigned char   sendDTMFTone;
    unsigned char   enteredDigitsEvent;
    unsigned char   queryDeviceName;
    unsigned char   queryAgentMeas;
    unsigned char   querySplitSkillMeas;
    unsigned char   queryTrunkGroupMeas;
    unsigned char   queryVdnMeas;
    unsigned char   singleStepConference;
    unsigned char   selectiveListeningHold;
    unsigned char   selectiveListeningRetrieve;
    unsigned char   setBillingRate;
    unsigned char   queryUCID;
    unsigned char   chargeAdviceEvent;
    unsigned char   reserved1;
    unsigned char   reserved2;
} ATTV6GetAPICapsConfEvent_t;

typedef struct ATTQueryDeviceInfoConfEvent_t {
    ATTExtensionClass_t extensionClass;
    ATTExtensionClass_t associatedClass;
    DeviceID_t      associatedDevice;
} ATTQueryDeviceInfoConfEvent_t;

typedef struct ATTSetAdviceOfCharge_t {
    unsigned char   featureFlag;
} ATTSetAdviceOfCharge_t;

typedef struct ATTSetAdviceOfChargeConfEvent_t {
    Nulltype        null;
} ATTSetAdviceOfChargeConfEvent_t;

typedef struct ATTV6NetworkReachedEvent_t {
    ATTProgressLocation_t progressLocation;
    ATTProgressDescription_t progressDescription;
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
} ATTV6NetworkReachedEvent_t;

typedef struct ATTSetAgentState_t {
    ATTWorkMode_t   workMode;
    long            reasonCode;
    unsigned char   enablePending;
} ATTSetAgentState_t;

typedef struct ATTSetAgentStateConfEvent_t {
    unsigned char   isPending;
} ATTSetAgentStateConfEvent_t;

typedef struct ATTQueryAgentStateConfEvent_t {
    ATTWorkMode_t   workMode;
    ATTTalkState_t  talkState;
    long            reasonCode;
    ATTWorkMode_t   pendingWorkMode;
    long            pendingReasonCode;
} ATTQueryAgentStateConfEvent_t;

typedef struct ATTUserToUserInfo_t {
    ATTUUIProtocolType_t type;
    struct {
        unsigned short  length;
        unsigned char   value[129];
    } data;
} ATTUserToUserInfo_t;

typedef struct ATTV6RouteRequestEvent_t {
    DeviceID_t      trunkGroup;
    ATTLookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTUserToUserInfo_t userInfo;
    ATTUCID_t       ucid;
    ATTCallOriginatorInfo_t callOriginatorInfo;
    unsigned char   flexibleBilling;
    DeviceID_t      trunkMember;
} ATTV6RouteRequestEvent_t;

typedef struct ATTV6OriginalCallInfo_t {
    ATTReasonForCallInfo_t reason;
    CallingDeviceID_t callingDevice;
    CalledDeviceID_t calledDevice;
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
    ATTLookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTUserToUserInfo_t userInfo;
    ATTUCID_t       ucid;
    ATTCallOriginatorInfo_t callOriginatorInfo;
    unsigned char   flexibleBilling;
} ATTV6OriginalCallInfo_t;

typedef struct ATTTrunkInfo_t {
    ConnectionID_t  connection;
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
} ATTTrunkInfo_t;

typedef struct ATTTrunkList_t {
    unsigned short  count;
    ATTTrunkInfo_t  trunks[5];
} ATTTrunkList_t;

typedef struct ATTV6TransferredEvent_t {
    ATTV6OriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
    ATTUCID_t       ucid;
    ATTTrunkList_t  trunkList;
} ATTV6TransferredEvent_t;

typedef struct ATTV6ConferencedEvent_t {
    ATTV6OriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
    ATTUCID_t       ucid;
    ATTTrunkList_t  trunkList;
} ATTV6ConferencedEvent_t;

typedef struct ATTClearConnection_t {
    ATTDropResource_t dropResource;
    ATTUserToUserInfo_t userInfo;
} ATTClearConnection_t;

typedef struct ATTConsultationCall_t {
    DeviceID_t      destRoute;
    unsigned char   priorityCalling;
    ATTUserToUserInfo_t userInfo;
} ATTConsultationCall_t;

typedef struct ATTMakeCall_t {
    DeviceID_t      destRoute;
    unsigned char   priorityCalling;
    ATTUserToUserInfo_t userInfo;
} ATTMakeCall_t;

typedef struct ATTDirectAgentCall_t {
    DeviceID_t      split;
    unsigned char   priorityCalling;
    ATTUserToUserInfo_t userInfo;
} ATTDirectAgentCall_t;

typedef struct ATTMakePredictiveCall_t {
    unsigned char   priorityCalling;
    short           maxRings;
    ATTAnswerTreat_t answerTreat;
    DeviceID_t      destRoute;
    ATTUserToUserInfo_t userInfo;
} ATTMakePredictiveCall_t;

typedef struct ATTSupervisorAssistCall_t {
    DeviceID_t      split;
    ATTUserToUserInfo_t userInfo;
} ATTSupervisorAssistCall_t;

typedef struct ATTReconnectCall_t {
    ATTDropResource_t dropResource;
    ATTUserToUserInfo_t userInfo;
} ATTReconnectCall_t;

typedef struct ATTV6ConnectionClearedEvent_t {
    ATTUserToUserInfo_t userInfo;
} ATTV6ConnectionClearedEvent_t;

typedef struct ATTV6RouteSelect_t {
    DeviceID_t      callingDevice;
    DeviceID_t      directAgentCallSplit;
    unsigned char   priorityCalling;
    DeviceID_t      destRoute;
    ATTUserCollectCode_t collectCode;
    ATTUserProvidedCode_t userProvidedCode;
    ATTUserToUserInfo_t userInfo;
} ATTV6RouteSelect_t;

typedef struct ATTV6DeliveredEvent_t {
    ATTDeliveredType_t deliveredType;
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
    DeviceID_t      split;
    ATTLookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTUserToUserInfo_t userInfo;
    ATTReasonCode_t reason;
    ATTV6OriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
    ATTUCID_t       ucid;
    ATTCallOriginatorInfo_t callOriginatorInfo;
    unsigned char   flexibleBilling;
} ATTV6DeliveredEvent_t;

typedef struct ATTV6EstablishedEvent_t {
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
    DeviceID_t      split;
    ATTLookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTUserToUserInfo_t userInfo;
    ATTReasonCode_t reason;
    ATTV6OriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
    ATTUCID_t       ucid;
    ATTCallOriginatorInfo_t callOriginatorInfo;
    unsigned char   flexibleBilling;
} ATTV6EstablishedEvent_t;

typedef struct ATTV8OriginatedEvent_t {
    DeviceID_t      logicalAgent;
    ATTUserToUserInfo_t userInfo;
} ATTV8OriginatedEvent_t;

typedef struct Reserved_t {
    struct {
        unsigned short  length;
        unsigned char   value[32];
    } data;
} Reserved_t;

typedef struct Reserved2_t {
    struct {
        unsigned short  length;
        unsigned char   value[32];
    } data;
} Reserved2_t;

typedef struct Reserved3_t {
    struct {
        unsigned short  length;
        unsigned char   value[32];
    } data;
} Reserved3_t;

typedef struct Reserved4_t {
    Nulltype        null;
} Reserved4_t;

typedef struct Reserved5_t {
    long            data;
} Reserved5_t;

typedef struct DeviceHistoryEntry_t {
    DeviceID_t      olddeviceID;
    CSTAEventCause_t cause;
    ConnectionID_t  oldconnectionID;
} DeviceHistoryEntry_t;

typedef struct DeviceHistory_t {
    unsigned int    count;
    DeviceHistoryEntry_t *deviceHistoryList;
} DeviceHistory_t;

typedef struct ATTOriginalCallInfo_t {
    ATTReasonForCallInfo_t reason;
    CallingDeviceID_t callingDevice;
    CalledDeviceID_t calledDevice;
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
    ATTLookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTUserToUserInfo_t userInfo;
    ATTUCID_t       ucid;
    ATTCallOriginatorInfo_t callOriginatorInfo;
    unsigned char   flexibleBilling;
    DeviceHistory_t deviceHistory;
} ATTOriginalCallInfo_t;

typedef struct ATTQueryDeviceNameConfEvent_t {
    ATTDeviceType_t deviceType;
    DeviceID_t      device;
    DeviceID_t      name;
    ATTUnicodeDeviceID uname;
} ATTQueryDeviceNameConfEvent_t;

typedef enum ATTRedirectType_t {
    vdn = 0,
    network = 1
} ATTRedirectType_t;

typedef struct ATTRouteSelect_t {
    DeviceID_t      callingDevice;
    DeviceID_t      directAgentCallSplit;
    unsigned char   priorityCalling;
    DeviceID_t      destRoute;
    ATTUserCollectCode_t collectCode;
    ATTUserProvidedCode_t userProvidedCode;
    ATTUserToUserInfo_t userInfo;
    ATTRedirectType_t redirectType;
} ATTRouteSelect_t;

typedef struct ATTGetAPICapsConfEvent_t {
    char            switchVersion[65];
    unsigned char   sendDTMFTone;
    unsigned char   enteredDigitsEvent;
    unsigned char   queryDeviceName;
    unsigned char   queryAgentMeas;
    unsigned char   querySplitSkillMeas;
    unsigned char   queryTrunkGroupMeas;
    unsigned char   queryVdnMeas;
    unsigned char   singleStepConference;
    unsigned char   selectiveListeningHold;
    unsigned char   selectiveListeningRetrieve;
    unsigned char   setBillingRate;
    unsigned char   queryUCID;
    unsigned char   chargeAdviceEvent;
    unsigned char   singleStepTransfer;
    unsigned char   monitorCallsViaDevice;
    unsigned char   devicehistoryCount;
    char            adminSoftwareVersion[256];
    char            softwareVersion[256];
    char            offerType[256];
    char            serverType[256];
} ATTGetAPICapsConfEvent_t;

typedef struct ATTDeliveredEvent_t {
    ATTDeliveredType_t deliveredType;
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
    DeviceID_t      split;
    ATTLookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTUserToUserInfo_t userInfo;
    ATTReasonCode_t reason;
    ATTOriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
    ATTUCID_t       ucid;
    ATTCallOriginatorInfo_t callOriginatorInfo;
    unsigned char   flexibleBilling;
    DeviceHistory_t deviceHistory;
    CalledDeviceID_t distributingVDN;
} ATTDeliveredEvent_t;

typedef struct ATTEstablishedEvent_t {
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
    DeviceID_t      split;
    ATTLookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTUserToUserInfo_t userInfo;
    ATTReasonCode_t reason;
    ATTOriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
    ATTUCID_t       ucid;
    ATTCallOriginatorInfo_t callOriginatorInfo;
    unsigned char   flexibleBilling;
    DeviceHistory_t deviceHistory;
    CalledDeviceID_t distributingVDN;
} ATTEstablishedEvent_t;

typedef struct ATTQueuedEvent_t {
    DeviceHistory_t deviceHistory;
} ATTQueuedEvent_t;

typedef struct ATTRouteRequestEvent_t {
    DeviceID_t      trunkGroup;
    ATTLookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTUserToUserInfo_t userInfo;
    ATTUCID_t       ucid;
    ATTCallOriginatorInfo_t callOriginatorInfo;
    unsigned char   flexibleBilling;
    DeviceID_t      trunkMember;
    DeviceHistory_t deviceHistory;
} ATTRouteRequestEvent_t;

typedef struct ATTTransferredEvent_t {
    ATTOriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
    ATTUCID_t       ucid;
    ATTTrunkList_t  trunkList;
    DeviceHistory_t deviceHistory;
    CalledDeviceID_t distributingVDN;
} ATTTransferredEvent_t;

typedef struct ATTConferencedEvent_t {
    ATTOriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
    ATTUCID_t       ucid;
    ATTTrunkList_t  trunkList;
    DeviceHistory_t deviceHistory;
    CalledDeviceID_t distributingVDN;
} ATTConferencedEvent_t;

typedef struct ATTConnectionClearedEvent_t {
    ATTUserToUserInfo_t userInfo;
    DeviceHistory_t deviceHistory;
} ATTConnectionClearedEvent_t;

typedef struct ATTDivertedEvent_t {
    DeviceHistory_t deviceHistory;
} ATTDivertedEvent_t;

typedef struct ATTNetworkReachedEvent_t {
    ATTProgressLocation_t progressLocation;
    ATTProgressDescription_t progressDescription;
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
    DeviceHistory_t deviceHistory;
} ATTNetworkReachedEvent_t;

typedef struct ATTV7FailedEvent_t {
    DeviceHistory_t deviceHistory;
} ATTV7FailedEvent_t;

typedef struct ATTSnapshotCallConfEvent_t {
    DeviceHistory_t deviceHistory;
} ATTSnapshotCallConfEvent_t;

typedef struct ATTReservedPDU139_t {
    char            placeholder;
} ATTReservedPDU139_t;

typedef struct ATTReservedPDU140_t {
    char            placeholder;
} ATTReservedPDU140_t;

typedef struct ATTFailedEvent_t {
    DeviceHistory_t deviceHistory;
    CallingDeviceID_t callingDevice;
} ATTFailedEvent_t;

typedef struct ATTSingleStepTransferCall_t {
    ConnectionID_t  activeCall;
    DeviceID_t      transferredTo;
} ATTSingleStepTransferCall_t;

typedef struct ATTV8SingleStepTransferCallConfEvent_t {
    ConnectionID_t  transferredCall;
} ATTV8SingleStepTransferCallConfEvent_t;

typedef struct ATTMonitorCallsViaDevice_t {
    ATTPrivateFilter_t privateFilter;
    unsigned char   flowPredictiveCallEvents;
} ATTMonitorCallsViaDevice_t;

typedef enum ATTConsultMode_t {
    attCmNone = 0,
    attCmConsultation = 1,
    attCmTransfer = 2,
    attCmConference = 3,
    attCmNotProvided = 4
} ATTConsultMode_t;

typedef struct ATTOriginatedEvent_t {
    DeviceID_t      logicalAgent;
    ATTUserToUserInfo_t userInfo;
    ATTConsultMode_t consultMode;
} ATTOriginatedEvent_t;

typedef struct ATTHeldEvent_t {
    ATTConsultMode_t consultMode;
} ATTHeldEvent_t;

typedef struct ATTServiceInitiatedEvent_t {
    ATTUCID_t       ucid;
    ATTConsultMode_t consultMode;
} ATTServiceInitiatedEvent_t;

typedef struct ATTSingleStepTransferCallConfEvent_t {
    ConnectionID_t  transferredCall;
    ATTUCID_t       ucid;
} ATTSingleStepTransferCallConfEvent_t;

#endif /* OSS_ATT_private_identifiers */
