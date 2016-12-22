/* Copyright (C) 2004-2010 Avaya Inc.  All rights reserved. */

#ifndef CSTADEFS_H
#define CSTADEFS_H

#include "tsplatfm.h"
#include "cticstadefs.h"

/* CSTA Event Types */
#define CSTA_ALTERNATE_CALL 1
#define CSTA_ALTERNATE_CALL_CONF 2
#define CSTA_ANSWER_CALL 3
#define CSTA_ANSWER_CALL_CONF 4
#define CSTA_CALL_COMPLETION 5
#define CSTA_CALL_COMPLETION_CONF 6
#define CSTA_CLEAR_CALL 7
#define CSTA_CLEAR_CALL_CONF 8
#define CSTA_CLEAR_CONNECTION 9
#define CSTA_CLEAR_CONNECTION_CONF 10
#define CSTA_CONFERENCE_CALL 11
#define CSTA_CONFERENCE_CALL_CONF 12
#define CSTA_CONSULTATION_CALL 13
#define CSTA_CONSULTATION_CALL_CONF 14
#define CSTA_DEFLECT_CALL 15
#define CSTA_DEFLECT_CALL_CONF 16
#define CSTA_PICKUP_CALL 17
#define CSTA_PICKUP_CALL_CONF 18
#define CSTA_GROUP_PICKUP_CALL 19
#define CSTA_GROUP_PICKUP_CALL_CONF 20
#define CSTA_HOLD_CALL 21
#define CSTA_HOLD_CALL_CONF 22
#define CSTA_MAKE_CALL 23
#define CSTA_MAKE_CALL_CONF 24
#define CSTA_MAKE_PREDICTIVE_CALL 25
#define CSTA_MAKE_PREDICTIVE_CALL_CONF 26
#define CSTA_QUERY_MWI 27
#define CSTA_QUERY_MWI_CONF 28
#define CSTA_QUERY_DND 29
#define CSTA_QUERY_DND_CONF 30
#define CSTA_QUERY_FWD 31
#define CSTA_QUERY_FWD_CONF 32
#define CSTA_QUERY_AGENT_STATE 33
#define CSTA_QUERY_AGENT_STATE_CONF 34
#define CSTA_QUERY_LAST_NUMBER 35
#define CSTA_QUERY_LAST_NUMBER_CONF 36
#define CSTA_QUERY_DEVICE_INFO 37
#define CSTA_QUERY_DEVICE_INFO_CONF 38
#define CSTA_RECONNECT_CALL 39
#define CSTA_RECONNECT_CALL_CONF 40
#define CSTA_RETRIEVE_CALL 41
#define CSTA_RETRIEVE_CALL_CONF 42
#define CSTA_SET_MWI 43
#define CSTA_SET_MWI_CONF 44
#define CSTA_SET_DND 45
#define CSTA_SET_DND_CONF 46
#define CSTA_SET_FWD 47
#define CSTA_SET_FWD_CONF 48
#define CSTA_SET_AGENT_STATE 49
#define CSTA_SET_AGENT_STATE_CONF 50
#define CSTA_TRANSFER_CALL 51
#define CSTA_TRANSFER_CALL_CONF 52
#define CSTA_UNIVERSAL_FAILURE_CONF 53
#define CSTA_CALL_CLEARED 54
#define CSTA_CONFERENCED 55
#define CSTA_CONNECTION_CLEARED 56
#define CSTA_DELIVERED 57
#define CSTA_DIVERTED 58
#define CSTA_ESTABLISHED 59
#define CSTA_FAILED 60
#define CSTA_HELD 61
#define CSTA_NETWORK_REACHED 62
#define CSTA_ORIGINATED 63
#define CSTA_QUEUED 64
#define CSTA_RETRIEVED 65
#define CSTA_SERVICE_INITIATED 66
#define CSTA_TRANSFERRED 67
#define CSTA_CALL_INFORMATION 68
#define CSTA_DO_NOT_DISTURB 69
#define CSTA_FORWARDING 70
#define CSTA_MESSAGE_WAITING 71
#define CSTA_LOGGED_ON 72
#define CSTA_LOGGED_OFF 73
#define CSTA_NOT_READY 74
#define CSTA_READY 75
#define CSTA_WORK_NOT_READY 76
#define CSTA_WORK_READY 77
#define CSTA_ROUTE_REGISTER_REQ 78
#define CSTA_ROUTE_REGISTER_REQ_CONF 79
#define CSTA_ROUTE_REGISTER_CANCEL 80
#define CSTA_ROUTE_REGISTER_CANCEL_CONF 81
#define CSTA_ROUTE_REGISTER_ABORT 82
#define CSTA_ROUTE_REQUEST 83
#define CSTA_ROUTE_SELECT_REQUEST 84
#define CSTA_RE_ROUTE_REQUEST 85
#define CSTA_ROUTE_USED 86
#define CSTA_ROUTE_END 87
#define CSTA_ROUTE_END_REQUEST 88
#define CSTA_ESCAPE_SVC 89
#define CSTA_ESCAPE_SVC_CONF 90
#define CSTA_ESCAPE_SVC_REQ 91
#define CSTA_ESCAPE_SVC_REQ_CONF 92
#define CSTA_PRIVATE 93
#define CSTA_PRIVATE_STATUS 94
#define CSTA_SEND_PRIVATE 95
#define CSTA_BACK_IN_SERVICE 96
#define CSTA_OUT_OF_SERVICE 97
#define CSTA_REQ_SYS_STAT 98
#define CSTA_SYS_STAT_REQ_CONF 99
#define CSTA_SYS_STAT_START 100
#define CSTA_SYS_STAT_START_CONF 101
#define CSTA_SYS_STAT_STOP 102
#define CSTA_SYS_STAT_STOP_CONF 103
#define CSTA_CHANGE_SYS_STAT_FILTER 104
#define CSTA_CHANGE_SYS_STAT_FILTER_CONF 105
#define CSTA_SYS_STAT 106
#define CSTA_SYS_STAT_ENDED 107
#define CSTA_SYS_STAT_REQ 108
#define CSTA_REQ_SYS_STAT_CONF 109
#define CSTA_SYS_STAT_EVENT_SEND 110
#define CSTA_MONITOR_DEVICE 111
#define CSTA_MONITOR_CALL 112
#define CSTA_MONITOR_CALLS_VIA_DEVICE 113
#define CSTA_MONITOR_CONF 114
#define CSTA_CHANGE_MONITOR_FILTER 115
#define CSTA_CHANGE_MONITOR_FILTER_CONF 116
#define CSTA_MONITOR_STOP 117
#define CSTA_MONITOR_STOP_CONF 118
#define CSTA_MONITOR_ENDED 119
#define CSTA_SNAPSHOT_CALL 120
#define CSTA_SNAPSHOT_CALL_CONF 121
#define CSTA_SNAPSHOT_DEVICE 122
#define CSTA_SNAPSHOT_DEVICE_CONF 123
#define CSTA_GETAPI_CAPS 124
#define CSTA_GETAPI_CAPS_CONF 125
#define CSTA_GET_DEVICE_LIST 126
#define CSTA_GET_DEVICE_LIST_CONF 127
#define CSTA_QUERY_CALL_MONITOR 128
#define CSTA_QUERY_CALL_MONITOR_CONF 129
#define CSTA_ROUTE_REQUEST_EXT 130
#define CSTA_ROUTE_USED_EXT 131
#define CSTA_ROUTE_SELECT_INV_REQUEST 132
#define CSTA_ROUTE_END_INV_REQUEST 133

/* SDBLevel_t values */
#define ACS_AND_CSTA_CHECKING           acsAndCstaChecking
#define ACS_ONLY                        acsOnly
#define NO_SDB_CHECKING                 noSdbChecking

/* AgentState_t values */
#define AG_NOT_READY                    agNotReady
#define AG_NULL                         agNull
#define AG_READY                        agReady
#define AG_WORK_NOT_READY               agWorkNotReady
#define AG_WORK_READY                   agWorkReady

/* AgentMode_t values */
#define AM_LOG_IN                       amLogIn
#define AM_LOG_OUT                      amLogOut
#define AM_NOT_READY                    amNotReady
#define AM_READY                        amReady
#define AM_WORK_NOT_READY               amWorkNotReady
#define AM_WORK_READY                   amWorkReady

/* AllocationState_t values */
#define AS_CALL_DELIVERED               asCallDelivered
#define AS_CALL_ESTABLISHED             asCallEstablished

/* CSTAUniversalFailure_t values */
#define ACS_HANDLE_TERMINATION_REJECTION acsHandleTerminationRejection
#define BADLY_STRUCTURED_APDU_REJECTION badlyStructuredApduRejection
#define CONFERENCE_MEMBER_LIMIT_EXCEEDED conferenceMemberLimitExceeded
#define DUPLICATE_INVOCATION_REJECTION duplicateInvocationRejection
#define EXTERNAL_TRUNK_LIMIT_EXCEEDED externalTrunkLimitExceeded
#define GENERIC_OPERATION genericOperation
#define GENERIC_OPERATION_REJECTION genericOperationRejection
#define GENERIC_PERFORMANCE_MANAGEMENT genericPerformanceManagement
#define GENERIC_STATE_INCOMPATIBILITY genericStateIncompatibility
#define GENERIC_SUBSCRIBED_RESOURCE_AVAILABILITY genericSubscribedResourceAvailability
#define GENERIC_SYSTEM_RESOURCE_AVAILABILITY genericSystemResourceAvailability
#define GENERIC_UNSPECIFIED genericUnspecified
#define GENERIC_UNSPECIFIED_REJECTION genericUnspecifiedRejection
#define INITIATOR_RELEASING_REJECTION initiatorReleasingRejection
#define INVALID_ALLOCATION_STATE invalidAllocationState
#define INVALID_CALLED_DEVICE invalidCalledDevice
#define INVALID_CALLING_DEVICE invalidCallingDevice
#define INVALID_CONNECTION_ID_FOR_ACTIVE_CALL invalidConnectionIdForActiveCall
#define INVALID_CROSS_REF_ID invalidCrossRefId
#define INVALID_CSTA_CALL_IDENTIFIER invalidCstaCallIdentifier
#define INVALID_CSTA_CONNECTION_IDENTIFIER invalidCstaConnectionIdentifier
#define INVALID_CSTA_DEVICE_IDENTIFIER invalidCstaDeviceIdentifier
#define INVALID_DESTINATION invalidDestination
#define INVALID_FEATURE invalidFeature
#define INVALID_FORWARDING_DESTINATION invalidForwardingDestination
#define INVALID_OBJECT_STATE invalidObjectState
#define INVALID_OBJECT_TYPE invalidObjectType
#define LINKED_RESPONSE_UNEXPECTED_REJECTION linkedResponseUnexpectedRejection
#define MISTYPED_APDU_REJECTION mistypedApduRejection
#define MISTYPED_ARGUMENT_REJECTION mistypedArgumentRejection
#define MISTYPED_PARAMETER_REJECTION mistypedParameterRejection
#define MISTYPED_RESULT_REJECTION mistypedResultRejection
#define NETWORK_BUSY networkBusy
#define NETWORK_OUT_OF_SERVICE networkOutOfService
#define NON_STANDARD nonStandard
#define NO_ACTIVE_CALL noActiveCall
#define NO_CALL_TO_ANSWER noCallToAnswer
#define NO_CALL_TO_CLEAR noCallToClear
#define NO_CALL_TO_COMPLETE noCallToComplete
#define NO_CONNECTION_TO_CLEAR noConnectionToClear
#define NO_HELD_CALL noHeldCall
#define OBJECT_MONITOR_LIMIT_EXCEEDED objectMonitorLimitExceeded
#define OBJECT_NOT_KNOWN objectNotKnown
#define OUTSTANDING_REQUEST_LIMIT_EXCEEDED outstandingRequestLimitExceeded
#define OVERALL_MONITOR_LIMIT_EXCEEDED overallMonitorLimitExceeded
#define PAC_VIOLATED pacViolated
#define PERFORMANCE_LIMIT_EXCEEDED performanceLimitExceeded
#define PRIVILEGE_VIOLATION_ON_CALLED_DEVICE privilegeViolationOnCalledDevice
#define PRIVILEGE_VIOLATION_ON_CALLING_DEVICE privilegeViolationOnCallingDevice
#define PRIVILEGE_VIOLATION_ON_SPECIFIED_DEVICE privilegeViolationOnSpecifiedDevice
#define REQUEST_INCOMPATIBLE_WITH_OBJECT requestIncompatibleWithObject
#define REQUEST_TIMEOUT_REJECTION requestTimeoutRejection
#define REQUESTS_ON_DEVICE_EXCEEDED_REJECTION requestsOnDeviceExceededRejection
#define RESOURCE_BUSY resourceBusy
#define RESOURCE_LIMITATION_REJECTION resourceLimitationRejection
#define RESOURCE_OUT_OF_SERVICE resourceOutOfService
#define SEAL_VIOLATED sealViolated
#define SECURITY_VIOLATION securityViolation
#define SEQUENCE_NUMBER_VIOLATED sequenceNumberViolated
#define SERVICE_BUSY serviceBusy
#define SERVICE_TERMINATION_REJECTION serviceTerminationRejection
#define TIME_STAMP_VIOLATED timeStampViolated
#define UNEXPECTED_CHILD_OPERATION_REJECTION unexpectedChildOperationRejection
#define UNEXPECTED_ERROR_REJECTION unexpectedErrorRejection
#define UNRECOGNIZED_APDU_REJECTION unrecognizedApduRejection
#define UNRECOGNIZED_ERROR_REJECTION unrecognizedErrorRejection
#define UNRECOGNIZED_LINKEDID_REJECTION unrecognizedLinkedidRejection
#define UNRECOGNIZED_OPERATION_REJECTION unrecognizedOperationRejection
#define UNSPECIFIED_SECURITY_ERROR unspecifiedSecurityError
#define VALUE_OUT_OF_RANGE valueOutOfRange

/* LocalConnectionState_t values */
#define CS_ALERTING                     csAlerting
#define CS_CONNECT                      csConnect
#define CS_FAIL                         csFail
#define CS_HOLD                         csHold
#define CS_INITIATE                     csInitiate
#define CS_NONE                         csNone
#define CS_NULL                         csNull
#define CS_QUEUED                       csQueued

/* CSTALevel_t values */
#define CSTA_AWAY_WORK_TOP              cstaAwayWorkTop
#define CSTA_CALL_CALL_MONITOR          cstaCallCallMonitor
#define CSTA_CALL_CONTROL               cstaCallControl
#define CSTA_CALL_DEVICE_MONITOR        cstaCallDeviceMonitor
#define CSTA_DEVICE_DEVICE_MONITOR      cstaDeviceDeviceMonitor
#define CSTA_HOME_WORK_TOP              cstaHomeWorkTop
#define CSTA_ROUTING                    cstaRouting

/* DeviceIDType_t values */
#define DEVICE_IDENTIFIER deviceIdentifier
#define EXPLICIT_PRIVATE_ABBREVIATED    explicitPrivateAbbreviated
#define EXPLICIT_PRIVATE_LEVEL1_REGIONAL_NUMBER explicitPrivateLevel1RegionalNumber
#define EXPLICIT_PRIVATE_LEVEL2_REGIONAL_NUMBER explicitPrivateLevel2RegionalNumber
#define EXPLICIT_PRIVATE_LEVEL3_REGIONAL_NUMBER explicitPrivateLevel3RegionalNumber
#define EXPLICIT_PRIVATE_LOCAL_NUMBER   explicitPrivateLocalNumber
#define EXPLICIT_PRIVATE_PTN_SPECIFIC_NUMBER explicitPrivatePtnSpecificNumber
#define EXPLICIT_PRIVATE_UNKNOWN        explicitPrivateUnknown
#define EXPLICIT_PUBLIC_ABBREVIATED     explicitPublicAbbreviated
#define EXPLICIT_PUBLIC_INTERNATIONAL   explicitPublicInternational
#define EXPLICIT_PUBLIC_NATIONAL        explicitPublicNational
#define EXPLICIT_PUBLIC_NETWORK_SPECIFIC explicitPublicNetworkSpecific
#define EXPLICIT_PUBLIC_SUBSCRIBER      explicitPublicSubscriber
#define EXPLICIT_PUBLIC_UNKNOWN         explicitPublicUnknown
#define IMPLICIT_PRIVATE                implicitPrivate
#define IMPLICIT_PUBLIC                 implicitPublic
#define OTHER_PLAN                      otherPlan
#define TRUNK_GROUP_IDENTIFIER          trunkGroupIdentifier
#define TRUNK_IDENTIFIER                trunkIdentifier

/* DeviceType_t values */
#define DT_ACD                          dtAcd
#define DT_ACD_GROUP                    dtAcdGroup
#define DT_BUTTON                       dtButton
#define DT_BUTTON_GROUP                 dtButtonGroup
#define DT_LINE                         dtLine
#define DT_LINE_GROUP                   dtLineGroup
#define DT_OPERATOR                     dtOperator
#define DT_OPERATOR_GROUP               dtOperatorGroup
#define DT_OTHER                        dtOther
#define DT_STATION                      dtStation
#define DT_STATION_GROUP                dtStationGroup
#define DT_TRUNK                        dtTrunk
#define DT_TRUNK_GROUP                  dtTrunkGroup

/* ConnectionID_Device_t values */
#define DYNAMIC_ID                      dynamicId
#define STATIC_ID                       staticId

/* CSTAEventCause_t values */
#define EC_ACTIVE_MONITOR               ecActiveMonitor
#define EC_ALERTTIMEEXPIRED             ecAlertTimeExpired     /* Deprecated */
#define EC_ALERT_TIME_EXPIRED           ecAlertTimeExpired
#define EC_ALTERNATE                    ecAlternate
#define EC_BUSY                         ecBusy
#define EC_CALL_BACK                    ecCallBack
#define EC_CALL_CANCELLED               ecCallCancelled
#define EC_CALL_FORWARD                 ecCallForward
#define EC_CALL_FORWARD_ALWAYS          ecCallForwardAlways
#define EC_CALL_FORWARD_BUSY            ecCallForwardBusy
#define EC_CALL_FORWARD_NO_ANSWER       ecCallForwardNoAnswer
#define EC_CALL_NOT_ANSWERED            ecCallNotAnswered
#define EC_CALL_PICKUP                  ecCallPickup
#define EC_CAMP_ON                      ecCampOn
#define EC_DESTOUTOFORDER               ecDestOutOfOrder       /* Deprecated */
#define EC_DEST_OUT_OF_ORDER            ecDestOutOfOrder
#define EC_DEST_NOT_OBTAINABLE          ecDestNotObtainable
#define EC_DO_NOT_DISTURB               ecDoNotDisturb
#define EC_INCOMPATIBLE_BEARER_SERVICE  ecIncompatibleBearerService
#define EC_INCOMPATIBLE_DESTINATION     ecIncompatibleDestination
#define EC_INVALID_ACCOUNT_CODE         ecInvalidAccountCode
#define EC_KEY_CONFERENCE               ecKeyConference
#define EC_LOCKOUT                      ecLockout
#define EC_MAINTENANCE                  ecMaintenance
#define EC_NETWORKSIGNAL                ecNetworkSignal        /* Deprecated */
#define EC_NETWORK_SIGNAL               ecNetworkSignal
#define EC_NETWORK_CONGESTION           ecNetworkCongestion
#define EC_NETWORK_NOT_OBTAINABLE       ecNetworkNotObtainable
#define EC_NEW_CALL                     ecNewCall
#define EC_NONE                         ecNone
#define EC_NOTSUPPORTEDBEARERSERVICE    ecNotSupportedBearerService
                                                               /* Deprecated */
#define EC_NOT_SUPPORTED_BEARER_SERVICE ecNotSupportedBearerService
#define EC_NO_AVAILABLE_AGENTS          ecNoAvailableAgents
#define EC_OVERFLOW                     ecOverflow
#define EC_OVERRIDE                     ecOverride
#define EC_PARK                         ecPark
#define EC_RECALL                       ecRecall
#define EC_REDIRECTED                   ecRedirected
#define EC_REORDER_TONE                 ecReorderTone
#define EC_RESOURCES_NOT_AVAILABLE      ecResourcesNotAvailable
#define EC_SILENT_MONITOR               ecSilentMonitor
#define EC_TRANSFER                     ecTransfer
#define EC_TRUNKS_BUSY                  ecTrunksBusy
#define EC_UNASSIGNED_NUMBER            ecUnassignedNumber
#define EC_VOICE_UNIT_INITIATOR         ecVoiceUnitInitiator
#define EC_SINGLE_STEP_TRANSFER         ecSingleStepTransfer

/* Feature_t values */
#define FT_CALL_BACK                    ftCallBack
#define FT_CAMP_ON                      ftCampOn
#define FT_INTRUDE                      ftIntrude

/* ForwardingType_t values */
#define FWD_BUSY                        fwdBusy
#define FWD_BUSY_EXT                    fwdBusyExt
#define FWD_BUSY_INT                    fwdBusyInt
#define FWD_IMMEDIATE                   fwdImmediate
#define FWD_NO_ANS                      fwdNoAns
#define FWD_NO_ANS_EXT                  fwdNoAnsExt
#define FWD_NO_ANS_INT                  fwdNoAnsInt

/* DeviceIDStatus_t values */
#define ID_NOT_KNOWN                    idNotKnown
#define ID_NOT_REQUIRED                 idNotRequired
#define ID_PROVIDED                     idProvided

/* SystemStatus_t values */
#define SS_DISABLED                     ssDisabled
#define SS_ENABLED                      ssEnabled
#define SS_INITIALIZING                 ssInitializing
#define SS_MESSAGES_LOST                ssMessagesLost
#define SS_NORMAL                       ssNormal
#define SS_OVERLOAD_IMMINENT            ssOverloadImminent
#define SS_OVERLOAD_REACHED             ssOverloadReached
#define SS_OVERLOAD_RELIEVED            ssOverloadRelieved

/* SelectValue_t values */
#define SV_ACD                          svAcd
#define SV_EMERGENCY                    svEmergency
#define SV_LEAST_COST                   svLeastCost
#define SV_NORMAL                       svNormal
#define SV_USER_DEFINED                 svUserDefined

/* CSTACallFilter_t bit flags */
#define CF_CALL_CLEARED                 0x8000
#define CF_CONFERENCED                  0x4000
#define CF_CONNECTION_CLEARED           0x2000
#define CF_DELIVERED                    0x1000
#define CF_DIVERTED                     0x0800
#define CF_ESTABLISHED                  0x0400
#define CF_FAILED                       0x0200
#define CF_HELD                         0x0100
#define CF_NETWORK_REACHED              0x0080
#define CF_ORIGINATED                   0x0040
#define CF_QUEUED                       0x0020
#define CF_RETRIEVED                    0x0010
#define CF_SERVICE_INITIATED            0x0008
#define CF_TRANSFERRED                  0x0004

/* CSTAFeatureFilter_t bit flags */
#define FF_CALL_INFORMATION             0x80
#define FF_DO_NOT_DISTURB               0x40
#define FF_FORWARDING                   0x20
#define FF_MESSAGE_WAITING              0x10

/* CSTAAgentFilter_t bit flags */
#define AF_LOGGED_ON                    0x80
#define AF_LOGGED_OFF                   0x40
#define AF_NOT_READY                    0x20
#define AF_READY                        0x10
#define AF_WORK_NOT_READY               0x08
#define AF_WORK_READY                   0x04

/* CSTAMaintenanceFilter_t bit flags */
#define MF_BACK_IN_SERVICE              0x80
#define MF_OUT_OF_SERVICE               0x40

/* DeviceClass_t bit flags */
#define	DC_VOICE                        0x80
#define DC_DATA                         0x40
#define DC_IMAGE                        0x20
#define DC_OTHER                        0x10

/* SystemStatusFilter_t bit flags */
#define SF_INITIALIZING                 0x80
#define SF_ENABLED                      0x40
#define SF_NORMAL                       0x20
#define SF_MESSAGES_LOST                0x10
#define SF_DISABLED                     0x08
#define SF_OVERLOAD_IMMINENT            0x04
#define SF_OVERLOAD_REACHED             0x02
#define SF_OVERLOAD_RELIEVED            0x01

#endif
