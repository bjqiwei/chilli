/* Copyright (C) 2004-2010 Avaya Inc.  All rights reserved. */

#ifndef ATTPDEFS
#define ATTPDEFS

#include "ctipdefs.h"

#define FIRST_PRIV_TYPE 1
#define ATTV5_CLEAR_CONNECTION 1
#define ATTV5_CONSULTATION_CALL 2
#define ATTV5_MAKE_CALL 3
#define ATTV5_DIRECT_AGENT_CALL 4
#define ATTV5_MAKE_PREDICTIVE_CALL 5
#define ATTV5_SUPERVISOR_ASSIST_CALL 6
#define ATTV5_RECONNECT_CALL 7
#define ATTV4_SENDDTMF_TONE 8
#define ATT_SENDDTMF_TONE_CONF 9
#define ATTV4_SET_AGENT_STATE 10
#define ATT_QUERY_ACD_SPLIT 11
#define ATT_QUERY_ACD_SPLIT_CONF 12
#define ATT_QUERY_AGENT_LOGIN 13
#define ATT_QUERY_AGENT_LOGIN_CONF 14
#define ATT_QUERY_AGENT_LOGIN_RESP 15
#define ATT_QUERY_AGENT_STATE 16
#define ATTV4_QUERY_AGENT_STATE_CONF 17
#define ATT_QUERY_CALL_CLASSIFIER 18
#define ATT_QUERY_CALL_CLASSIFIER_CONF 19
#define ATTV4_QUERY_DEVICE_INFO_CONF 20
#define ATT_QUERY_MWI_CONF 21
#define ATT_QUERY_STATION_STATUS 22
#define ATT_QUERY_STATION_STATUS_CONF 23
#define ATT_QUERY_TOD 24
#define ATT_QUERY_TOD_CONF 25
#define ATT_QUERY_TG 26
#define ATT_QUERY_TG_CONF 27
#define ATTV4_SNAPSHOT_DEVICE_CONF 28
#define ATTV4_MONITOR_FILTER 29
#define ATTV4_MONITOR_CONF 30
#define ATT_MONITOR_STOP_ON_CALL 31
#define ATT_MONITOR_STOP_ON_CALL_CONF 32
#define ATTV4_MONITOR_CALL_CONF 33
#define ATT_CALL_CLEARED 34
#define ATTV3_CONFERENCED 35
#define ATTV5_CONNECTION_CLEARED 36
#define ATTV3_DELIVERED 37
#define ATT_ENTERED_DIGITS 38
#define ATTV3_ESTABLISHED 39
#define ATTV4_NETWORK_REACHED 40
#define ATTV3_TRANSFERRED 41
#define ATTV4_ROUTE_REQUEST 42
#define ATTV5_ROUTE_SELECT 43
#define ATT_ROUTE_USED 44
#define ATT_SYS_STAT 45
#define ATTV3_LINK_STATUS 46
#define ATTV5_ORIGINATED 47
#define ATT_LOGGED_ON 48
#define ATT_QUERY_DEVICE_NAME 49
#define ATTV4_QUERY_DEVICE_NAME_CONF 50
#define ATT_QUERY_AGENT_MEASUREMENTS 51
#define ATT_QUERY_AGENT_MEASUREMENTS_CONF 52
#define ATT_QUERY_SPLIT_SKILL_MEASUREMENTS 53
#define ATT_QUERY_SPLIT_SKILL_MEASUREMENTS_CONF 54
#define ATT_QUERY_TRUNK_GROUP_MEASUREMENTS 55
#define ATT_QUERY_TRUNK_GROUP_MEASUREMENTS_CONF 56
#define ATT_QUERY_VDN_MEASUREMENTS 57
#define ATT_QUERY_VDN_MEASUREMENTS_CONF 58
#define ATTV4_CONFERENCED 59
#define ATTV4_DELIVERED 60
#define ATTV4_ESTABLISHED 61
#define ATTV4_TRANSFERRED 62
#define ATTV4_LINK_STATUS 63
#define ATTV4_GETAPI_CAPS_CONF 64
#define ATT_SINGLE_STEP_CONFERENCE_CALL 65
#define ATT_SINGLE_STEP_CONFERENCE_CALL_CONF 66
#define ATT_SELECTIVE_LISTENING_HOLD 67
#define ATT_SELECTIVE_LISTENING_HOLD_CONF 68
#define ATT_SELECTIVE_LISTENING_RETRIEVE 69
#define ATT_SELECTIVE_LISTENING_RETRIEVE_CONF 70
#define ATT_SENDDTMF_TONE 71
#define ATT_SNAPSHOT_DEVICE_CONF 72
#define ATT_LINK_STATUS 73
#define ATT_SET_BILL_RATE 74
#define ATT_SET_BILL_RATE_CONF 75
#define ATT_QUERY_UCID 76
#define ATT_QUERY_UCID_CONF 77
#define ATTV5_CONFERENCED 78
#define ATT_LOGGED_OFF 79
#define ATTV5_DELIVERED 80
#define ATTV5_ESTABLISHED 81
#define ATTV5_TRANSFERRED 82
#define ATTV5_ROUTE_REQUEST 83
#define ATT_CONSULTATION_CALL_CONF 84
#define ATT_MAKE_CALL_CONF 85
#define ATT_MAKE_PREDICTIVE_CALL_CONF 86
#define ATTV5_SET_AGENT_STATE 87
#define ATTV5_QUERY_AGENT_STATE_CONF 88
#define ATTV6_QUERY_DEVICE_NAME_CONF 89
#define ATT_CONFERENCE_CALL_CONF 90
#define ATT_TRANSFER_CALL_CONF 91
#define ATT_MONITOR_FILTER 92
#define ATT_MONITOR_CONF 93
#define ATT_MONITOR_CALL_CONF 94
#define ATTV8_SERVICE_INITIATED 95
#define ATT_CHARGE_ADVICE 96
#define ATTV6_GETAPI_CAPS_CONF 97
#define ATT_QUERY_DEVICE_INFO_CONF 98
#define ATT_SET_ADVICE_OF_CHARGE 99
#define ATT_SET_ADVICE_OF_CHARGE_CONF 100
#define ATTV6_NETWORK_REACHED 101
#define ATT_SET_AGENT_STATE 102
#define ATT_SET_AGENT_STATE_CONF 103
#define ATT_QUERY_AGENT_STATE_CONF 104
#define ATTV6_ROUTE_REQUEST 105
#define ATTV6_TRANSFERRED 106
#define ATTV6_CONFERENCED 107
#define ATT_CLEAR_CONNECTION 108
#define ATT_CONSULTATION_CALL 109
#define ATT_MAKE_CALL 110
#define ATT_DIRECT_AGENT_CALL 111
#define ATT_MAKE_PREDICTIVE_CALL 112
#define ATT_SUPERVISOR_ASSIST_CALL 113
#define ATT_RECONNECT_CALL 114
#define ATTV6_CONNECTION_CLEARED 115
#define ATTV6_ROUTE_SELECT 116
#define ATTV6_DELIVERED 117
#define ATTV6_ESTABLISHED 118
#define ATTV8_ORIGINATED 119
#define ATT_QUERY_DEVICE_NAME_CONF 125
#define ATT_ROUTE_SELECT 126
#define ATT_GETAPI_CAPS_CONF 127
#define ATT_DELIVERED 128
#define ATT_ESTABLISHED 129
#define ATT_QUEUED 130
#define ATT_ROUTE_REQUEST 131
#define ATT_TRANSFERRED 132
#define ATT_CONFERENCED 133
#define ATT_CONNECTION_CLEARED 134
#define ATT_DIVERTED 135
#define ATT_NETWORK_REACHED 136
#define ATTV7_FAILED 137
#define ATT_SNAPSHOT_CALL_CONF 138
#define ATT_RESERVED_PDU_139 139
#define ATT_RESERVED_PDU_140 140
#define ATT_FAILED 141
#define ATT_SINGLE_STEP_TRANSFER_CALL 142
#define ATTV8_SINGLE_STEP_TRANSFER_CALL_CONF 143
#define ATT_MONITOR_CALLS_VIA_DEVICE 144
#define ATT_ORIGINATED 145
#define ATT_HELD 146
#define ATT_SERVICE_INITIATED 147
#define ATT_SINGLE_STEP_TRANSFER_CALL_CONF 148
#define LAST_PRIV_TYPE ATT_SINGLE_STEP_TRANSFER_CALL_CONF

/* UUI Protocol Types */
#define UUI_NONE uuiNone
#define UUI_USER_SPECIFIC uuiUserSpecific
#define UUI_IA5_ASCII uuiIa5Ascii

/* Lookahead Interflow Types */
#define LAI_NO_INTERFLOW laiNoInterflow
#define LAI_ALL_INTERFLOW laiAllInterflow
#define LAI_THRESHOLD_INTERFLOW laiThresholdInterflow
#define LAI_VECTORING_INTERFLOW laiVectoringInterflow
#define LAI_NOT_IN_QUEUE laiNotInQueue
#define LAI_LOW laiLow
#define LAI_MEDIUM laiMedium
#define LAI_HIGH laiHigh
#define LAI_TOP laiTop

/* User Entered Code Types */
#define UE_NONE ueNone
#define UE_ANY ueAny
#define UE_LOGIN_DIGITS ueLoginDigits
#define UE_CALL_PROMPTER ueCallPrompter
#define UE_DATA_BASE_PROVIDED ueDataBaseProvided
#define UE_TONE_DETECTOR ueToneDetector
#define UE_COLLECT ueCollect
#define UE_ENTERED ueEntered

/* Progress Locations */
#define PL_NONE plNone
#define PL_USER plUser
#define PL_PUB_LOCAL plPubLocal
#define PL_PUB_REMOTE plPubRemote
#define PL_PRIV_REMOTE plPrivRemote

/* Progress Descriptions */
#define PD_NONE pdNone
#define PD_CALL_OFF_ISDN pdCallOffIsdn
#define PD_DEST_NOT_ISDN pdDestNotIsdn
#define PD_ORIG_NOT_ISDN pdOrigNotIsdn
#define PD_CALL_ON_ISDN pdCallOnIsdn
#define PD_INBAND pdInband

/* Agent Work Modes */
#define WM_NONE wmNone
#define WM_AUX_WORK wmAuxWork
#define WM_AFTCAL_WK wmAftcalWk
#define WM_AUTO_IN wmAutoIn
#define WM_MANUAL_IN wmManualIn

/* Talk States */
#define TS_ON_CALL tsOnCall
#define TS_IDLE tsIdle

/* Extension Classes */
#define EC_VDN ecVdn
#define EC_ACD_SPLIT ecAcdSplit
#define EC_ANNOUNCEMENT ecAnnouncement
#define EC_DATA ecData
#define EC_ANALOG ecAnalog
#define EC_PROPRIETARY ecProprietary
#define EC_BRI ecBri
#define EC_CTI ecCti
#define EC_LOGICAL_AGENT ecLogicalAgent
#define EC_OTHER ecOther

/* Answer Treatment Types */
#define AT_NO_TREATMENT atNoTreatment
#define AT_NONE atNone
#define AT_DROP atDrop
#define AT_CONNECT atConnect

/* Local Call States */
#define ATT_CS_INITIATED attCsInitiated
#define ATT_CS_ALERTING attCsAlerting
#define ATT_CS_CONNECTED attCsConnected
#define ATT_CS_HELD attCsHeld
#define ATT_CS_BRIDGED attCsBridged
#define ATT_CS_OTHER attCsOther

/* Collect Code Types */
#define UC_NONE ucNone
#define UC_TONE_DETECTOR ucToneDetector

/* Provided Code Types */
#define UP_NONE upNone
#define UP_DATA_BASE_PROVIDED upDataBaseProvided

/* Specific Events */
#define SE_ANSWER seAnswer
#define SE_DISCONNECT seDisconnect

/* Drop Resource Types */
#define DR_NONE drNone
#define DR_CALL_CLASSIFIER drCallClassifier
#define DR_TONE_GENERATOR drToneGenerator

/* Reason Codes */
#define AR_NONE arNone
#define AR_ANSWER_NORMAL arAnswerNormal
#define AR_ANSWER_TIMED arAnswerTimed
#define AR_ANSWER_VOICE_ENERGY arAnswerVoiceEnergy
#define AR_ANSWER_MACHINE_DETECTED arAnswerMachineDetected
#define AR_SIT_REORDER arSitReorder
#define AR_SIT_NO_CIRCUIT arSitNoCircuit
#define AR_SIT_INTERCEPT arSitIntercept
#define AR_SIT_VACANT_CODE arSitVacantCode
#define AR_SIT_INEFFECTIVE_OTHER arSitIneffectiveOther
#define AR_SIT_UNKNOWN arSitUnknown
#define AR_IN_QUEUE arInQueue
#define AR_SERVICE_OBSERVER arServiceObserver

/* Reasons for Original Call Info */
#define OR_NONE orNone
#define OR_CONSULTATION orConsultation
#define OR_CONFERENCED orConferenced
#define OR_TRANSFERRED orTransferred
#define OR_NEW_CALL orNewCall

/* Delivered Event Types */
#define DELIVERED_TO_ACD deliveredToAcd
#define DELIVERED_TO_STATION deliveredToStation
#define DELIVERED_OTHER deliveredOther

/* Link States */
#define LS_LINK_UNAVAIL lsLinkUnavail
#define LS_LINK_UP lsLinkUp
#define LS_LINK_DOWN lsLinkDown

/* Device Types */
#define ATT_DT_UNKNOWN attDtUnknown
#define ATT_DT_ACD_SPLIT attDtAcdSplit
#define ATT_DT_ANNOUNCEMENT attDtAnnouncement
#define ATT_DT_DATA attDtData
#define ATT_DT_LOGICAL_AGENT attDtLogicalAgent
#define ATT_DT_STATION attDtStation
#define ATT_DT_TRUNK_ACCESS_CODE attDtTrunkAccessCode
#define ATT_DT_VDN attDtVdn
#define ATT_DT_OTHER attDtOther

/* Agent ID Types */
#define EXTENSION_ID extensionId
#define LOGICAL_ID logicalId

/* Split Skills */
#define SPLIT_SKILL_NONE splitSkillNone
#define SPLIT_SKILL_ALL splitSkillAll
#define SPLIT_SKILL1 splitSkill1
#define SPLIT_SKILL2 splitSkill2
#define SPLIT_SKILL3 splitSkill3
#define SPLIT_SKILL4 splitSkill4

/* Participation Types */
#define PT_ACTIVE ptActive
#define PT_SILENT ptSilent

/* Bill Types */
#define BT_NEW_RATE btNewRate
#define BT_FLAT_RATE btFlatRate
#define BT_PREMIUM_CHARGE btPremiumCharge
#define BT_PREMIUM_CREDIT btPremiumCredit
#define BT_FREE_CALL btFreeCall

/* Charge Types */
#define CT_INTERMEDIATE_CHARGE ctIntermediateCharge
#define CT_FINAL_CHARGE ctFinalCharge
#define CT_SPLIT_CHARGE ctSplitCharge

/* Charge Error Types */
#define CE_NONE ceNone
#define CE_NO_FINAL_CHARGE ceNoFinalCharge
#define CE_LESS_FINAL_CHARGE ceLessFinalCharge
#define CE_CHARGE_TOO_LARGE ceChargeTooLarge
#define CE_NETWORK_BUSY ceNetworkBusy

/* Private Filter Flags for ATTV4PrivateFilter_t */
#define ATT_V4_ENTERED_DIGITS_FILTER 0x80

/* Private Filter Flags for ATTPrivateFilter_t */
#define ATT_ENTERED_DIGITS_FILTER 0x80
#define ATT_CHARGE_ADVICE_FILTER 0x40

/* Message Waiting Indicator Application Types */
#define AT_MCS 0x01
#define AT_VOICE 0x02
#define AT_PROPMGT 0x04
#define AT_LWC 0x08
#define AT_CTI 0x10

#define ATTUnicodeDeviceID_t ATTUnicodeDeviceID

/* Redirection Types */
#define VDN vdn
#define NETWORK network

/* Maximum number of trunks in an ATTTrunkList_t */
#define MAX_TRUNKS 5

/* Consult Modes */
#define ATT_CM_NONE attCmNone
#define ATT_CM_CONSULTATION attCmConsultation
#define ATT_CM_TRANSFER attCmTransfer
#define ATT_CM_CONFERENCE attCmConference
#define ATT_CM_NOT_PROVIDED attCmNotProvided

#endif
