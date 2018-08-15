/*************************************************************/
/* Copyright (C) 2010 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/
/* Generated for: Avaya Inc., Basking Ridge, NJ - license 7175 for Windows */
/* Abstract syntax: csta_asn_tbl */
/* Created: Fri Sep 17 13:50:29 2010 */
/* ASN.1 compiler version: 7.0 */
/* Code generated for runtime version 7.0 or later */
/* Target operating system: Windows NT/Windows 9x */
/* Target machine type: Intel x86 */
/* C compiler options required: -Zp8 (Microsoft) */
/* ASN.1 compiler options and file names specified:
 * -headerfile cticstadefs.h -noshortennames -nouniquepdu -externalname
 * csta_asn_tbl -noconstraints -charintegers -shippable -splitheaders
 * -compat v4.1.3
 * C:\Program Files\OSS\ossasn1\win32\7.0.0\asn1dflt\asn1dflt.ms.zp8 pdu.dir
 * csta_common.asn csta.asn
 */

#ifndef OSS_csta_asn_tbl
#define OSS_csta_asn_tbl

#include   "CSTA_event_causes.h"
#include   "CSTA_device_identifiers.h"
#include   "CSTA_call_connection_identifiers.h"
#include   "CSTA_connection_states.h"
#include   "CSTA_status_reporting.h"
#include   "CSTA_error_definition.h"
#include   "CSTA_device_feature_types.h"
#include   "CSTA_alternate_call.h"
#include   "CSTA_answer_call.h"
#include   "CSTA_call_completion.h"
#include   "CSTA_clear_call.h"
#include   "CSTA_clear_connection.h"
#include   "CSTA_conference_call.h"
#include   "CSTA_consultation_call.h"
#include   "CSTA_deflect_call.h"
#include   "CSTA_pickup_call.h"
#include   "CSTA_group_pickup_call.h"
#include   "CSTA_hold_call.h"
#include   "CSTA_make_call.h"
#include   "CSTA_make_predictive_call.h"
#include   "CSTA_query_device.h"
#include   "CSTA_reconnect_call.h"
#include   "CSTA_retrieve_call.h"
#include   "CSTA_set_feature.h"
#include   "CSTA_transfer_call.h"
#include   "CSTA_event_report_definitions.h"
#include   "CSTA_call_cleared_event.h"
#include   "CSTA_conferenced_event.h"
#include   "CSTA_connection_cleared_event.h"
#include   "CSTA_delivered_event.h"
#include   "CSTA_diverted_event.h"
#include   "CSTA_established_event.h"
#include   "CSTA_failed_event.h"
#include   "CSTA_held_event.h"
#include   "CSTA_network_reached_event.h"
#include   "CSTA_originated_event.h"
#include   "CSTA_queued_event.h"
#include   "CSTA_retrieved_event.h"
#include   "CSTA_service_initiated_event.h"
#include   "CSTA_transferred_event.h"
#include   "CSTA_call_information_event.h"
#include   "CSTA_do_not_disturb_event.h"
#include   "CSTA_forwarding_event.h"
#include   "CSTA_message_waiting_event.h"
#include   "CSTA_logged_on_event.h"
#include   "CSTA_logged_off_event.h"
#include   "CSTA_not_ready_event.h"
#include   "CSTA_ready_event.h"
#include   "CSTA_work_not_ready_event.h"
#include   "CSTA_work_ready_event.h"
#include   "CSTA_route_register.h"
#include   "CSTA_route_register_cancel.h"
#include   "CSTA_route_request.h"
#include   "CSTA_route_select_request.h"
#include   "CSTA_re_route_request.h"
#include   "CSTA_route_used_request.h"
#include   "CSTA_route_end_event.h"
#include   "CSTA_route_end_request.h"
#include   "CSTA_escape_service.h"
#include   "CSTA_private_event.h"
#include   "CSTA_back_in_service_event.h"
#include   "CSTA_out_of_service_event.h"
#include   "CSTA_system_status.h"
#include   "CSTA_monitor_start.h"
#include   "CSTA_change_monitor_filter.h"
#include   "CSTA_monitor_stop.h"
#include   "CSTA_snapshot_call.h"
#include   "CSTA_snapshot_device.h"
#include   "CSTA_control_services.h"
#include   "CSTA_route_request_extended.h"
#include   "CSTA_route_used_request_extended.h"
#include   "CSTA_route_select_request_invoke.h"
#include   "CSTA_route_end_request_invoke.h"

#ifndef CSTAAlternateCall_t_PDU
#define          CSTAAlternateCall_t_PDU 1
#endif
#ifndef CSTAAlternateCallConfEvent_t_PDU
#define          CSTAAlternateCallConfEvent_t_PDU 2
#endif
#ifndef CSTAAnswerCall_t_PDU
#define          CSTAAnswerCall_t_PDU 3
#endif
#ifndef CSTAAnswerCallConfEvent_t_PDU
#define          CSTAAnswerCallConfEvent_t_PDU 4
#endif
#ifndef CSTACallCompletion_t_PDU
#define          CSTACallCompletion_t_PDU 5
#endif
#ifndef CSTACallCompletionConfEvent_t_PDU
#define          CSTACallCompletionConfEvent_t_PDU 6
#endif
#ifndef CSTAClearCall_t_PDU
#define          CSTAClearCall_t_PDU 7
#endif
#ifndef CSTAClearCallConfEvent_t_PDU
#define          CSTAClearCallConfEvent_t_PDU 8
#endif
#ifndef CSTAClearConnection_t_PDU
#define          CSTAClearConnection_t_PDU 9
#endif
#ifndef CSTAClearConnectionConfEvent_t_PDU
#define          CSTAClearConnectionConfEvent_t_PDU 10
#endif
#ifndef CSTAConferenceCall_t_PDU
#define          CSTAConferenceCall_t_PDU 11
#endif
#ifndef CSTAConferenceCallConfEvent_t_PDU
#define          CSTAConferenceCallConfEvent_t_PDU 12
#endif
#ifndef CSTAConsultationCall_t_PDU
#define          CSTAConsultationCall_t_PDU 13
#endif
#ifndef CSTAConsultationCallConfEvent_t_PDU
#define          CSTAConsultationCallConfEvent_t_PDU 14
#endif
#ifndef CSTADeflectCall_t_PDU
#define          CSTADeflectCall_t_PDU 15
#endif
#ifndef CSTADeflectCallConfEvent_t_PDU
#define          CSTADeflectCallConfEvent_t_PDU 16
#endif
#ifndef CSTAPickupCall_t_PDU
#define          CSTAPickupCall_t_PDU 17
#endif
#ifndef CSTAPickupCallConfEvent_t_PDU
#define          CSTAPickupCallConfEvent_t_PDU 18
#endif
#ifndef CSTAGroupPickupCall_t_PDU
#define          CSTAGroupPickupCall_t_PDU 19
#endif
#ifndef CSTAGroupPickupCallConfEvent_t_PDU
#define          CSTAGroupPickupCallConfEvent_t_PDU 20
#endif
#ifndef CSTAHoldCall_t_PDU
#define          CSTAHoldCall_t_PDU 21
#endif
#ifndef CSTAHoldCallConfEvent_t_PDU
#define          CSTAHoldCallConfEvent_t_PDU 22
#endif
#ifndef CSTAMakeCall_t_PDU
#define          CSTAMakeCall_t_PDU 23
#endif
#ifndef CSTAMakeCallConfEvent_t_PDU
#define          CSTAMakeCallConfEvent_t_PDU 24
#endif
#ifndef CSTAMakePredictiveCall_t_PDU
#define          CSTAMakePredictiveCall_t_PDU 25
#endif
#ifndef CSTAMakePredictiveCallConfEvent_t_PDU
#define          CSTAMakePredictiveCallConfEvent_t_PDU 26
#endif
#ifndef CSTAQueryMwi_t_PDU
#define          CSTAQueryMwi_t_PDU 27
#endif
#ifndef CSTAQueryMwiConfEvent_t_PDU
#define          CSTAQueryMwiConfEvent_t_PDU 28
#endif
#ifndef CSTAQueryDnd_t_PDU
#define          CSTAQueryDnd_t_PDU 29
#endif
#ifndef CSTAQueryDndConfEvent_t_PDU
#define          CSTAQueryDndConfEvent_t_PDU 30
#endif
#ifndef CSTAQueryFwd_t_PDU
#define          CSTAQueryFwd_t_PDU 31
#endif
#ifndef CSTAQueryFwdConfEvent_t_PDU
#define          CSTAQueryFwdConfEvent_t_PDU 32
#endif
#ifndef CSTAQueryAgentState_t_PDU
#define          CSTAQueryAgentState_t_PDU 33
#endif
#ifndef CSTAQueryAgentStateConfEvent_t_PDU
#define          CSTAQueryAgentStateConfEvent_t_PDU 34
#endif
#ifndef CSTAQueryLastNumber_t_PDU
#define          CSTAQueryLastNumber_t_PDU 35
#endif
#ifndef CSTAQueryLastNumberConfEvent_t_PDU
#define          CSTAQueryLastNumberConfEvent_t_PDU 36
#endif
#ifndef CSTAQueryDeviceInfo_t_PDU
#define          CSTAQueryDeviceInfo_t_PDU 37
#endif
#ifndef CSTAQueryDeviceInfoConfEvent_t_PDU
#define          CSTAQueryDeviceInfoConfEvent_t_PDU 38
#endif
#ifndef CSTAReconnectCall_t_PDU
#define          CSTAReconnectCall_t_PDU 39
#endif
#ifndef CSTAReconnectCallConfEvent_t_PDU
#define          CSTAReconnectCallConfEvent_t_PDU 40
#endif
#ifndef CSTARetrieveCall_t_PDU
#define          CSTARetrieveCall_t_PDU 41
#endif
#ifndef CSTARetrieveCallConfEvent_t_PDU
#define          CSTARetrieveCallConfEvent_t_PDU 42
#endif
#ifndef CSTASetMwi_t_PDU
#define          CSTASetMwi_t_PDU 43
#endif
#ifndef CSTASetMwiConfEvent_t_PDU
#define          CSTASetMwiConfEvent_t_PDU 44
#endif
#ifndef CSTASetDnd_t_PDU
#define          CSTASetDnd_t_PDU 45
#endif
#ifndef CSTASetDndConfEvent_t_PDU
#define          CSTASetDndConfEvent_t_PDU 46
#endif
#ifndef CSTASetFwd_t_PDU
#define          CSTASetFwd_t_PDU 47
#endif
#ifndef CSTASetFwdConfEvent_t_PDU
#define          CSTASetFwdConfEvent_t_PDU 48
#endif
#ifndef CSTASetAgentState_t_PDU
#define          CSTASetAgentState_t_PDU 49
#endif
#ifndef CSTASetAgentStateConfEvent_t_PDU
#define          CSTASetAgentStateConfEvent_t_PDU 50
#endif
#ifndef CSTATransferCall_t_PDU
#define          CSTATransferCall_t_PDU 51
#endif
#ifndef CSTATransferCallConfEvent_t_PDU
#define          CSTATransferCallConfEvent_t_PDU 52
#endif
#ifndef CSTAUniversalFailureConfEvent_t_PDU
#define          CSTAUniversalFailureConfEvent_t_PDU 53
#endif
#ifndef CSTACallClearedEvent_t_PDU
#define          CSTACallClearedEvent_t_PDU 54
#endif
#ifndef CSTAConferencedEvent_t_PDU
#define          CSTAConferencedEvent_t_PDU 55
#endif
#ifndef CSTAConnectionClearedEvent_t_PDU
#define          CSTAConnectionClearedEvent_t_PDU 56
#endif
#ifndef CSTADeliveredEvent_t_PDU
#define          CSTADeliveredEvent_t_PDU 57
#endif
#ifndef CSTADivertedEvent_t_PDU
#define          CSTADivertedEvent_t_PDU 58
#endif
#ifndef CSTAEstablishedEvent_t_PDU
#define          CSTAEstablishedEvent_t_PDU 59
#endif
#ifndef CSTAFailedEvent_t_PDU
#define          CSTAFailedEvent_t_PDU 60
#endif
#ifndef CSTAHeldEvent_t_PDU
#define          CSTAHeldEvent_t_PDU 61
#endif
#ifndef CSTANetworkReachedEvent_t_PDU
#define          CSTANetworkReachedEvent_t_PDU 62
#endif
#ifndef CSTAOriginatedEvent_t_PDU
#define          CSTAOriginatedEvent_t_PDU 63
#endif
#ifndef CSTAQueuedEvent_t_PDU
#define          CSTAQueuedEvent_t_PDU 64
#endif
#ifndef CSTARetrievedEvent_t_PDU
#define          CSTARetrievedEvent_t_PDU 65
#endif
#ifndef CSTAServiceInitiatedEvent_t_PDU
#define          CSTAServiceInitiatedEvent_t_PDU 66
#endif
#ifndef CSTATransferredEvent_t_PDU
#define          CSTATransferredEvent_t_PDU 67
#endif
#ifndef CSTACallInformationEvent_t_PDU
#define          CSTACallInformationEvent_t_PDU 68
#endif
#ifndef CSTADoNotDisturbEvent_t_PDU
#define          CSTADoNotDisturbEvent_t_PDU 69
#endif
#ifndef CSTAForwardingEvent_t_PDU
#define          CSTAForwardingEvent_t_PDU 70
#endif
#ifndef CSTAMessageWaitingEvent_t_PDU
#define          CSTAMessageWaitingEvent_t_PDU 71
#endif
#ifndef CSTALoggedOnEvent_t_PDU
#define          CSTALoggedOnEvent_t_PDU 72
#endif
#ifndef CSTALoggedOffEvent_t_PDU
#define          CSTALoggedOffEvent_t_PDU 73
#endif
#ifndef CSTANotReadyEvent_t_PDU
#define          CSTANotReadyEvent_t_PDU 74
#endif
#ifndef CSTAReadyEvent_t_PDU
#define          CSTAReadyEvent_t_PDU 75
#endif
#ifndef CSTAWorkNotReadyEvent_t_PDU
#define          CSTAWorkNotReadyEvent_t_PDU 76
#endif
#ifndef CSTAWorkReadyEvent_t_PDU
#define          CSTAWorkReadyEvent_t_PDU 77
#endif
#ifndef CSTARouteRegisterReq_t_PDU
#define          CSTARouteRegisterReq_t_PDU 78
#endif
#ifndef CSTARouteRegisterReqConfEvent_t_PDU
#define          CSTARouteRegisterReqConfEvent_t_PDU 79
#endif
#ifndef CSTARouteRegisterCancel_t_PDU
#define          CSTARouteRegisterCancel_t_PDU 80
#endif
#ifndef CSTARouteRegisterCancelConfEvent_t_PDU
#define          CSTARouteRegisterCancelConfEvent_t_PDU 81
#endif
#ifndef CSTARouteRegisterAbortEvent_t_PDU
#define          CSTARouteRegisterAbortEvent_t_PDU 82
#endif
#ifndef CSTARouteRequestEvent_t_PDU
#define          CSTARouteRequestEvent_t_PDU 83
#endif
#ifndef CSTARouteSelectRequest_t_PDU
#define          CSTARouteSelectRequest_t_PDU 84
#endif
#ifndef CSTAReRouteRequest_t_PDU
#define          CSTAReRouteRequest_t_PDU 85
#endif
#ifndef CSTARouteUsedEvent_t_PDU
#define          CSTARouteUsedEvent_t_PDU 86
#endif
#ifndef CSTARouteEndEvent_t_PDU
#define          CSTARouteEndEvent_t_PDU 87
#endif
#ifndef CSTARouteEndRequest_t_PDU
#define          CSTARouteEndRequest_t_PDU 88
#endif
#ifndef CSTAEscapeSvc_t_PDU
#define          CSTAEscapeSvc_t_PDU 89
#endif
#ifndef CSTAEscapeSvcConfEvent_t_PDU
#define          CSTAEscapeSvcConfEvent_t_PDU 90
#endif
#ifndef CSTAEscapeSvcReqEvent_t_PDU
#define          CSTAEscapeSvcReqEvent_t_PDU 91
#endif
#ifndef CSTAEscapeSvcReqConf_t_PDU
#define          CSTAEscapeSvcReqConf_t_PDU 92
#endif
#ifndef CSTAPrivateEvent_t_PDU
#define          CSTAPrivateEvent_t_PDU 93
#endif
#ifndef CSTAPrivateStatusEvent_t_PDU
#define          CSTAPrivateStatusEvent_t_PDU 94
#endif
#ifndef CSTASendPrivateEvent_t_PDU
#define          CSTASendPrivateEvent_t_PDU 95
#endif
#ifndef CSTABackInServiceEvent_t_PDU
#define          CSTABackInServiceEvent_t_PDU 96
#endif
#ifndef CSTAOutOfServiceEvent_t_PDU
#define          CSTAOutOfServiceEvent_t_PDU 97
#endif
#ifndef CSTAReqSysStat_t_PDU
#define          CSTAReqSysStat_t_PDU 98
#endif
#ifndef CSTASysStatReqConfEvent_t_PDU
#define          CSTASysStatReqConfEvent_t_PDU 99
#endif
#ifndef CSTASysStatStart_t_PDU
#define          CSTASysStatStart_t_PDU 100
#endif
#ifndef CSTASysStatStartConfEvent_t_PDU
#define          CSTASysStatStartConfEvent_t_PDU 101
#endif
#ifndef CSTASysStatStop_t_PDU
#define          CSTASysStatStop_t_PDU 102
#endif
#ifndef CSTASysStatStopConfEvent_t_PDU
#define          CSTASysStatStopConfEvent_t_PDU 103
#endif
#ifndef CSTAChangeSysStatFilter_t_PDU
#define          CSTAChangeSysStatFilter_t_PDU 104
#endif
#ifndef CSTAChangeSysStatFilterConfEvent_t_PDU
#define          CSTAChangeSysStatFilterConfEvent_t_PDU 105
#endif
#ifndef CSTASysStatEvent_t_PDU
#define          CSTASysStatEvent_t_PDU 106
#endif
#ifndef CSTASysStatEndedEvent_t_PDU
#define          CSTASysStatEndedEvent_t_PDU 107
#endif
#ifndef CSTASysStatReqEvent_t_PDU
#define          CSTASysStatReqEvent_t_PDU 108
#endif
#ifndef CSTAReqSysStatConf_t_PDU
#define          CSTAReqSysStatConf_t_PDU 109
#endif
#ifndef CSTASysStatEventSend_t_PDU
#define          CSTASysStatEventSend_t_PDU 110
#endif
#ifndef CSTAMonitorDevice_t_PDU
#define          CSTAMonitorDevice_t_PDU 111
#endif
#ifndef CSTAMonitorCall_t_PDU
#define          CSTAMonitorCall_t_PDU 112
#endif
#ifndef CSTAMonitorCallsViaDevice_t_PDU
#define          CSTAMonitorCallsViaDevice_t_PDU 113
#endif
#ifndef CSTAMonitorConfEvent_t_PDU
#define          CSTAMonitorConfEvent_t_PDU 114
#endif
#ifndef CSTAChangeMonitorFilter_t_PDU
#define          CSTAChangeMonitorFilter_t_PDU 115
#endif
#ifndef CSTAChangeMonitorFilterConfEvent_t_PDU
#define          CSTAChangeMonitorFilterConfEvent_t_PDU 116
#endif
#ifndef CSTAMonitorStop_t_PDU
#define          CSTAMonitorStop_t_PDU 117
#endif
#ifndef CSTAMonitorStopConfEvent_t_PDU
#define          CSTAMonitorStopConfEvent_t_PDU 118
#endif
#ifndef CSTAMonitorEndedEvent_t_PDU
#define          CSTAMonitorEndedEvent_t_PDU 119
#endif
#ifndef CSTASnapshotCall_t_PDU
#define          CSTASnapshotCall_t_PDU 120
#endif
#ifndef CSTASnapshotCallConfEvent_t_PDU
#define          CSTASnapshotCallConfEvent_t_PDU 121
#endif
#ifndef CSTASnapshotDevice_t_PDU
#define          CSTASnapshotDevice_t_PDU 122
#endif
#ifndef CSTASnapshotDeviceConfEvent_t_PDU
#define          CSTASnapshotDeviceConfEvent_t_PDU 123
#endif
#ifndef CSTAGetAPICaps_t_PDU
#define          CSTAGetAPICaps_t_PDU 124
#endif
#ifndef CSTAGetAPICapsConfEvent_t_PDU
#define          CSTAGetAPICapsConfEvent_t_PDU 125
#endif
#ifndef CSTAGetDeviceList_t_PDU
#define          CSTAGetDeviceList_t_PDU 126
#endif
#ifndef CSTAGetDeviceListConfEvent_t_PDU
#define          CSTAGetDeviceListConfEvent_t_PDU 127
#endif
#ifndef CSTAQueryCallMonitor_t_PDU
#define          CSTAQueryCallMonitor_t_PDU 128
#endif
#ifndef CSTAQueryCallMonitorConfEvent_t_PDU
#define          CSTAQueryCallMonitorConfEvent_t_PDU 129
#endif
#ifndef CSTARouteRequestExtEvent_t_PDU
#define          CSTARouteRequestExtEvent_t_PDU 130
#endif
#ifndef CSTARouteUsedExtEvent_t_PDU
#define          CSTARouteUsedExtEvent_t_PDU 131
#endif
#ifndef CSTARouteSelectInvRequest_t_PDU
#define          CSTARouteSelectInvRequest_t_PDU 132
#endif
#ifndef CSTARouteEndInvRequest_t_PDU
#define          CSTARouteEndInvRequest_t_PDU 133
#endif
#endif /* OSS_csta_asn_tbl */
