/*************************************************************/
/* Copyright (C) 2010 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/
/* Generated for: Avaya Inc., Basking Ridge, NJ - license 7175 for Windows */
/* Abstract syntax: att_asn_tbl */
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

#ifndef OSS_att_asn_tbl
#define OSS_att_asn_tbl

#include   "ATT_private_identifiers.h"
#include   "CSTA_event_causes.h"
#include   "CSTA_device_identifiers.h"
#include   "CSTA_call_connection_identifiers.h"
#include   "CSTA_connection_states.h"
#include   "CSTA_status_reporting.h"

#ifndef ATTV5ClearConnection_t_PDU
#define          ATTV5ClearConnection_t_PDU 1
#endif
#ifndef ATTV5ConsultationCall_t_PDU
#define          ATTV5ConsultationCall_t_PDU 2
#endif
#ifndef ATTV5MakeCall_t_PDU
#define          ATTV5MakeCall_t_PDU 3
#endif
#ifndef ATTV5DirectAgentCall_t_PDU
#define          ATTV5DirectAgentCall_t_PDU 4
#endif
#ifndef ATTV5MakePredictiveCall_t_PDU
#define          ATTV5MakePredictiveCall_t_PDU 5
#endif
#ifndef ATTV5SupervisorAssistCall_t_PDU
#define          ATTV5SupervisorAssistCall_t_PDU 6
#endif
#ifndef ATTV5ReconnectCall_t_PDU
#define          ATTV5ReconnectCall_t_PDU 7
#endif
#ifndef ATTV4SendDTMFTone_t_PDU
#define          ATTV4SendDTMFTone_t_PDU 8
#endif
#ifndef ATTSendDTMFToneConfEvent_t_PDU
#define          ATTSendDTMFToneConfEvent_t_PDU 9
#endif
#ifndef ATTV4SetAgentState_t_PDU
#define          ATTV4SetAgentState_t_PDU 10
#endif
#ifndef ATTQueryAcdSplit_t_PDU
#define          ATTQueryAcdSplit_t_PDU 11
#endif
#ifndef ATTQueryAcdSplitConfEvent_t_PDU
#define          ATTQueryAcdSplitConfEvent_t_PDU 12
#endif
#ifndef ATTQueryAgentLogin_t_PDU
#define          ATTQueryAgentLogin_t_PDU 13
#endif
#ifndef ATTQueryAgentLoginConfEvent_t_PDU
#define          ATTQueryAgentLoginConfEvent_t_PDU 14
#endif
#ifndef ATTQueryAgentLoginResp_t_PDU
#define          ATTQueryAgentLoginResp_t_PDU 15
#endif
#ifndef ATTQueryAgentState_t_PDU
#define          ATTQueryAgentState_t_PDU 16
#endif
#ifndef ATTV4QueryAgentStateConfEvent_t_PDU
#define          ATTV4QueryAgentStateConfEvent_t_PDU 17
#endif
#ifndef ATTQueryCallClassifier_t_PDU
#define          ATTQueryCallClassifier_t_PDU 18
#endif
#ifndef ATTQueryCallClassifierConfEvent_t_PDU
#define          ATTQueryCallClassifierConfEvent_t_PDU 19
#endif
#ifndef ATTV4QueryDeviceInfoConfEvent_t_PDU
#define          ATTV4QueryDeviceInfoConfEvent_t_PDU 20
#endif
#ifndef ATTQueryMwiConfEvent_t_PDU
#define          ATTQueryMwiConfEvent_t_PDU 21
#endif
#ifndef ATTQueryStationStatus_t_PDU
#define          ATTQueryStationStatus_t_PDU 22
#endif
#ifndef ATTQueryStationStatusConfEvent_t_PDU
#define          ATTQueryStationStatusConfEvent_t_PDU 23
#endif
#ifndef ATTQueryTod_t_PDU
#define          ATTQueryTod_t_PDU 24
#endif
#ifndef ATTQueryTodConfEvent_t_PDU
#define          ATTQueryTodConfEvent_t_PDU 25
#endif
#ifndef ATTQueryTg_t_PDU
#define          ATTQueryTg_t_PDU 26
#endif
#ifndef ATTQueryTgConfEvent_t_PDU
#define          ATTQueryTgConfEvent_t_PDU 27
#endif
#ifndef ATTV4SnapshotDeviceConfEvent_t_PDU
#define          ATTV4SnapshotDeviceConfEvent_t_PDU 28
#endif
#ifndef ATTV4MonitorFilter_t_PDU
#define          ATTV4MonitorFilter_t_PDU 29
#endif
#ifndef ATTV4MonitorConfEvent_t_PDU
#define          ATTV4MonitorConfEvent_t_PDU 30
#endif
#ifndef ATTMonitorStopOnCall_t_PDU
#define          ATTMonitorStopOnCall_t_PDU 31
#endif
#ifndef ATTMonitorStopOnCallConfEvent_t_PDU
#define          ATTMonitorStopOnCallConfEvent_t_PDU 32
#endif
#ifndef ATTV4MonitorCallConfEvent_t_PDU
#define          ATTV4MonitorCallConfEvent_t_PDU 33
#endif
#ifndef ATTCallClearedEvent_t_PDU
#define          ATTCallClearedEvent_t_PDU 34
#endif
#ifndef ATTV3ConferencedEvent_t_PDU
#define          ATTV3ConferencedEvent_t_PDU 35
#endif
#ifndef ATTV5ConnectionClearedEvent_t_PDU
#define          ATTV5ConnectionClearedEvent_t_PDU 36
#endif
#ifndef ATTV3DeliveredEvent_t_PDU
#define          ATTV3DeliveredEvent_t_PDU 37
#endif
#ifndef ATTEnteredDigitsEvent_t_PDU
#define          ATTEnteredDigitsEvent_t_PDU 38
#endif
#ifndef ATTV3EstablishedEvent_t_PDU
#define          ATTV3EstablishedEvent_t_PDU 39
#endif
#ifndef ATTV4NetworkReachedEvent_t_PDU
#define          ATTV4NetworkReachedEvent_t_PDU 40
#endif
#ifndef ATTV3TransferredEvent_t_PDU
#define          ATTV3TransferredEvent_t_PDU 41
#endif
#ifndef ATTV4RouteRequestEvent_t_PDU
#define          ATTV4RouteRequestEvent_t_PDU 42
#endif
#ifndef ATTV5RouteSelect_t_PDU
#define          ATTV5RouteSelect_t_PDU 43
#endif
#ifndef ATTRouteUsedEvent_t_PDU
#define          ATTRouteUsedEvent_t_PDU 44
#endif
#ifndef ATTSysStat_t_PDU
#define          ATTSysStat_t_PDU 45
#endif
#ifndef ATTV3LinkStatusEvent_t_PDU
#define          ATTV3LinkStatusEvent_t_PDU 46
#endif
#ifndef ATTV5OriginatedEvent_t_PDU
#define          ATTV5OriginatedEvent_t_PDU 47
#endif
#ifndef ATTLoggedOnEvent_t_PDU
#define          ATTLoggedOnEvent_t_PDU 48
#endif
#ifndef ATTQueryDeviceName_t_PDU
#define          ATTQueryDeviceName_t_PDU 49
#endif
#ifndef ATTV4QueryDeviceNameConfEvent_t_PDU
#define          ATTV4QueryDeviceNameConfEvent_t_PDU 50
#endif
#ifndef ATTQueryAgentMeasurements_t_PDU
#define          ATTQueryAgentMeasurements_t_PDU 51
#endif
#ifndef ATTQueryAgentMeasurementsConfEvent_t_PDU
#define          ATTQueryAgentMeasurementsConfEvent_t_PDU 52
#endif
#ifndef ATTQuerySplitSkillMeasurements_t_PDU
#define          ATTQuerySplitSkillMeasurements_t_PDU 53
#endif
#ifndef ATTQuerySplitSkillMeasurementsConfEvent_t_PDU
#define          ATTQuerySplitSkillMeasurementsConfEvent_t_PDU 54
#endif
#ifndef ATTQueryTrunkGroupMeasurements_t_PDU
#define          ATTQueryTrunkGroupMeasurements_t_PDU 55
#endif
#ifndef ATTQueryTrunkGroupMeasurementsConfEvent_t_PDU
#define          ATTQueryTrunkGroupMeasurementsConfEvent_t_PDU 56
#endif
#ifndef ATTQueryVdnMeasurements_t_PDU
#define          ATTQueryVdnMeasurements_t_PDU 57
#endif
#ifndef ATTQueryVdnMeasurementsConfEvent_t_PDU
#define          ATTQueryVdnMeasurementsConfEvent_t_PDU 58
#endif
#ifndef ATTV4ConferencedEvent_t_PDU
#define          ATTV4ConferencedEvent_t_PDU 59
#endif
#ifndef ATTV4DeliveredEvent_t_PDU
#define          ATTV4DeliveredEvent_t_PDU 60
#endif
#ifndef ATTV4EstablishedEvent_t_PDU
#define          ATTV4EstablishedEvent_t_PDU 61
#endif
#ifndef ATTV4TransferredEvent_t_PDU
#define          ATTV4TransferredEvent_t_PDU 62
#endif
#ifndef ATTV4LinkStatusEvent_t_PDU
#define          ATTV4LinkStatusEvent_t_PDU 63
#endif
#ifndef ATTV4GetAPICapsConfEvent_t_PDU
#define          ATTV4GetAPICapsConfEvent_t_PDU 64
#endif
#ifndef ATTSingleStepConferenceCall_t_PDU
#define          ATTSingleStepConferenceCall_t_PDU 65
#endif
#ifndef ATTSingleStepConferenceCallConfEvent_t_PDU
#define          ATTSingleStepConferenceCallConfEvent_t_PDU 66
#endif
#ifndef ATTSelectiveListeningHold_t_PDU
#define          ATTSelectiveListeningHold_t_PDU 67
#endif
#ifndef ATTSelectiveListeningHoldConfEvent_t_PDU
#define          ATTSelectiveListeningHoldConfEvent_t_PDU 68
#endif
#ifndef ATTSelectiveListeningRetrieve_t_PDU
#define          ATTSelectiveListeningRetrieve_t_PDU 69
#endif
#ifndef ATTSelectiveListeningRetrieveConfEvent_t_PDU
#define          ATTSelectiveListeningRetrieveConfEvent_t_PDU 70
#endif
#ifndef ATTSendDTMFTone_t_PDU
#define          ATTSendDTMFTone_t_PDU 71
#endif
#ifndef ATTSnapshotDeviceConfEvent_t_PDU
#define          ATTSnapshotDeviceConfEvent_t_PDU 72
#endif
#ifndef ATTLinkStatusEvent_t_PDU
#define          ATTLinkStatusEvent_t_PDU 73
#endif
#ifndef ATTSetBillRate_t_PDU
#define          ATTSetBillRate_t_PDU 74
#endif
#ifndef ATTSetBillRateConfEvent_t_PDU
#define          ATTSetBillRateConfEvent_t_PDU 75
#endif
#ifndef ATTQueryUcid_t_PDU
#define          ATTQueryUcid_t_PDU 76
#endif
#ifndef ATTQueryUcidConfEvent_t_PDU
#define          ATTQueryUcidConfEvent_t_PDU 77
#endif
#ifndef ATTV5ConferencedEvent_t_PDU
#define          ATTV5ConferencedEvent_t_PDU 78
#endif
#ifndef ATTLoggedOffEvent_t_PDU
#define          ATTLoggedOffEvent_t_PDU 79
#endif
#ifndef ATTV5DeliveredEvent_t_PDU
#define          ATTV5DeliveredEvent_t_PDU 80
#endif
#ifndef ATTV5EstablishedEvent_t_PDU
#define          ATTV5EstablishedEvent_t_PDU 81
#endif
#ifndef ATTV5TransferredEvent_t_PDU
#define          ATTV5TransferredEvent_t_PDU 82
#endif
#ifndef ATTV5RouteRequestEvent_t_PDU
#define          ATTV5RouteRequestEvent_t_PDU 83
#endif
#ifndef ATTConsultationCallConfEvent_t_PDU
#define          ATTConsultationCallConfEvent_t_PDU 84
#endif
#ifndef ATTMakeCallConfEvent_t_PDU
#define          ATTMakeCallConfEvent_t_PDU 85
#endif
#ifndef ATTMakePredictiveCallConfEvent_t_PDU
#define          ATTMakePredictiveCallConfEvent_t_PDU 86
#endif
#ifndef ATTV5SetAgentState_t_PDU
#define          ATTV5SetAgentState_t_PDU 87
#endif
#ifndef ATTV5QueryAgentStateConfEvent_t_PDU
#define          ATTV5QueryAgentStateConfEvent_t_PDU 88
#endif
#ifndef ATTV6QueryDeviceNameConfEvent_t_PDU
#define          ATTV6QueryDeviceNameConfEvent_t_PDU 89
#endif
#ifndef ATTConferenceCallConfEvent_t_PDU
#define          ATTConferenceCallConfEvent_t_PDU 90
#endif
#ifndef ATTTransferCallConfEvent_t_PDU
#define          ATTTransferCallConfEvent_t_PDU 91
#endif
#ifndef ATTMonitorFilter_t_PDU
#define          ATTMonitorFilter_t_PDU 92
#endif
#ifndef ATTMonitorConfEvent_t_PDU
#define          ATTMonitorConfEvent_t_PDU 93
#endif
#ifndef ATTMonitorCallConfEvent_t_PDU
#define          ATTMonitorCallConfEvent_t_PDU 94
#endif
#ifndef ATTV8ServiceInitiatedEvent_t_PDU
#define          ATTV8ServiceInitiatedEvent_t_PDU 95
#endif
#ifndef ATTChargeAdviceEvent_t_PDU
#define          ATTChargeAdviceEvent_t_PDU 96
#endif
#ifndef ATTV6GetAPICapsConfEvent_t_PDU
#define          ATTV6GetAPICapsConfEvent_t_PDU 97
#endif
#ifndef ATTQueryDeviceInfoConfEvent_t_PDU
#define          ATTQueryDeviceInfoConfEvent_t_PDU 98
#endif
#ifndef ATTSetAdviceOfCharge_t_PDU
#define          ATTSetAdviceOfCharge_t_PDU 99
#endif
#ifndef ATTSetAdviceOfChargeConfEvent_t_PDU
#define          ATTSetAdviceOfChargeConfEvent_t_PDU 100
#endif
#ifndef ATTV6NetworkReachedEvent_t_PDU
#define          ATTV6NetworkReachedEvent_t_PDU 101
#endif
#ifndef ATTSetAgentState_t_PDU
#define          ATTSetAgentState_t_PDU 102
#endif
#ifndef ATTSetAgentStateConfEvent_t_PDU
#define          ATTSetAgentStateConfEvent_t_PDU 103
#endif
#ifndef ATTQueryAgentStateConfEvent_t_PDU
#define          ATTQueryAgentStateConfEvent_t_PDU 104
#endif
#ifndef ATTV6RouteRequestEvent_t_PDU
#define          ATTV6RouteRequestEvent_t_PDU 105
#endif
#ifndef ATTV6TransferredEvent_t_PDU
#define          ATTV6TransferredEvent_t_PDU 106
#endif
#ifndef ATTV6ConferencedEvent_t_PDU
#define          ATTV6ConferencedEvent_t_PDU 107
#endif
#ifndef ATTClearConnection_t_PDU
#define          ATTClearConnection_t_PDU 108
#endif
#ifndef ATTConsultationCall_t_PDU
#define          ATTConsultationCall_t_PDU 109
#endif
#ifndef ATTMakeCall_t_PDU
#define          ATTMakeCall_t_PDU 110
#endif
#ifndef ATTDirectAgentCall_t_PDU
#define          ATTDirectAgentCall_t_PDU 111
#endif
#ifndef ATTMakePredictiveCall_t_PDU
#define          ATTMakePredictiveCall_t_PDU 112
#endif
#ifndef ATTSupervisorAssistCall_t_PDU
#define          ATTSupervisorAssistCall_t_PDU 113
#endif
#ifndef ATTReconnectCall_t_PDU
#define          ATTReconnectCall_t_PDU 114
#endif
#ifndef ATTV6ConnectionClearedEvent_t_PDU
#define          ATTV6ConnectionClearedEvent_t_PDU 115
#endif
#ifndef ATTV6RouteSelect_t_PDU
#define          ATTV6RouteSelect_t_PDU 116
#endif
#ifndef ATTV6DeliveredEvent_t_PDU
#define          ATTV6DeliveredEvent_t_PDU 117
#endif
#ifndef ATTV6EstablishedEvent_t_PDU
#define          ATTV6EstablishedEvent_t_PDU 118
#endif
#ifndef ATTV8OriginatedEvent_t_PDU
#define          ATTV8OriginatedEvent_t_PDU 119
#endif
#ifndef Reserved_t_PDU
#define          Reserved_t_PDU 120
#endif
#ifndef Reserved2_t_PDU
#define          Reserved2_t_PDU 121
#endif
#ifndef Reserved3_t_PDU
#define          Reserved3_t_PDU 122
#endif
#ifndef Reserved4_t_PDU
#define          Reserved4_t_PDU 123
#endif
#ifndef Reserved5_t_PDU
#define          Reserved5_t_PDU 124
#endif
#ifndef ATTQueryDeviceNameConfEvent_t_PDU
#define          ATTQueryDeviceNameConfEvent_t_PDU 125
#endif
#ifndef ATTRouteSelect_t_PDU
#define          ATTRouteSelect_t_PDU 126
#endif
#ifndef ATTGetAPICapsConfEvent_t_PDU
#define          ATTGetAPICapsConfEvent_t_PDU 127
#endif
#ifndef ATTDeliveredEvent_t_PDU
#define          ATTDeliveredEvent_t_PDU 128
#endif
#ifndef ATTEstablishedEvent_t_PDU
#define          ATTEstablishedEvent_t_PDU 129
#endif
#ifndef ATTQueuedEvent_t_PDU
#define          ATTQueuedEvent_t_PDU 130
#endif
#ifndef ATTRouteRequestEvent_t_PDU
#define          ATTRouteRequestEvent_t_PDU 131
#endif
#ifndef ATTTransferredEvent_t_PDU
#define          ATTTransferredEvent_t_PDU 132
#endif
#ifndef ATTConferencedEvent_t_PDU
#define          ATTConferencedEvent_t_PDU 133
#endif
#ifndef ATTConnectionClearedEvent_t_PDU
#define          ATTConnectionClearedEvent_t_PDU 134
#endif
#ifndef ATTDivertedEvent_t_PDU
#define          ATTDivertedEvent_t_PDU 135
#endif
#ifndef ATTNetworkReachedEvent_t_PDU
#define          ATTNetworkReachedEvent_t_PDU 136
#endif
#ifndef ATTV7FailedEvent_t_PDU
#define          ATTV7FailedEvent_t_PDU 137
#endif
#ifndef ATTSnapshotCallConfEvent_t_PDU
#define          ATTSnapshotCallConfEvent_t_PDU 138
#endif
#ifndef ATTReservedPDU139_t_PDU
#define          ATTReservedPDU139_t_PDU 139
#endif
#ifndef ATTReservedPDU140_t_PDU
#define          ATTReservedPDU140_t_PDU 140
#endif
#ifndef ATTFailedEvent_t_PDU
#define          ATTFailedEvent_t_PDU 141
#endif
#ifndef ATTSingleStepTransferCall_t_PDU
#define          ATTSingleStepTransferCall_t_PDU 142
#endif
#ifndef ATTV8SingleStepTransferCallConfEvent_t_PDU
#define          ATTV8SingleStepTransferCallConfEvent_t_PDU 143
#endif
#ifndef ATTMonitorCallsViaDevice_t_PDU
#define          ATTMonitorCallsViaDevice_t_PDU 144
#endif
#ifndef ATTOriginatedEvent_t_PDU
#define          ATTOriginatedEvent_t_PDU 145
#endif
#ifndef ATTHeldEvent_t_PDU
#define          ATTHeldEvent_t_PDU 146
#endif
#ifndef ATTServiceInitiatedEvent_t_PDU
#define          ATTServiceInitiatedEvent_t_PDU 147
#endif
#ifndef ATTSingleStepTransferCallConfEvent_t_PDU
#define          ATTSingleStepTransferCallConfEvent_t_PDU 148
#endif
#endif /* OSS_att_asn_tbl */
