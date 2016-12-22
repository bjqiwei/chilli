/*************************************************************/
/* Copyright (C) 2010 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/
/* Generated for: Avaya Inc., Basking Ridge, NJ - license 7175 for Windows */
/* Abstract syntax: CSTA_status_reporting */
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

#ifndef OSS_CSTA_status_reporting
#define OSS_CSTA_status_reporting

#include "ossship.h"

#ifndef OSS_INT32
#define OSS_INT32 int
#endif /* OSS_INT32 */

#include "CSTA_device_identifiers.h"
#include "CSTA_call_connection_identifiers.h"
#include "CSTA_connection_states.h"


typedef long            CSTAMonitorCrossRefID_t;

typedef unsigned short  CSTACallFilter_t;
#define                     cfCallCleared 0x8000
#define                     cfConferenced 0x4000
#define                     cfConnectionCleared 0x2000
#define                     cfDelivered 0x1000
#define                     cfDiverted 0x0800
#define                     cfEstablished 0x0400
#define                     cfFailed 0x0200
#define                     cfHeld 0x0100
#define                     cfNetworkReached 0x0080
#define                     cfOriginated 0x0040
#define                     cfQueued 0x0020
#define                     cfRetrieved 0x0010
#define                     cfServiceInitiated 0x0008
#define                     cfTransferred 0x0004

typedef unsigned char   CSTAFeatureFilter_t;
#define                     ffCallInformation 0x80
#define                     ffDoNotDisturb 0x40
#define                     ffForwarding 0x20
#define                     ffMessageWaiting 0x10

typedef unsigned char   CSTAAgentFilter_t;
#define                     afLoggedOn 0x80
#define                     afLoggedOff 0x40
#define                     afNotReady 0x20
#define                     afReady 0x10
#define                     afWorkNotReady 0x08
#define                     afWorkReady 0x04

typedef unsigned char   CSTAMaintenanceFilter_t;
#define                     mfBackInService 0x80
#define                     mfOutOfService 0x40

typedef struct CSTAMonitorFilter_t {
    CSTACallFilter_t call;
    CSTAFeatureFilter_t feature;
    CSTAAgentFilter_t agent;
    CSTAMaintenanceFilter_t maintenance;
    long            privateFilter;
} CSTAMonitorFilter_t;

typedef struct CSTACallState_t {
    unsigned int    count;
    LocalConnectionState_t *state;
} CSTACallState_t;

typedef struct CSTASnapshotDeviceResponseInfo_t {
    ConnectionID_t  callIdentifier;
    CSTACallState_t localCallState;
} CSTASnapshotDeviceResponseInfo_t;

typedef struct CSTASnapshotDeviceData_t {
    unsigned int    count;
    CSTASnapshotDeviceResponseInfo_t *info;
} CSTASnapshotDeviceData_t;

typedef struct CSTASnapshotCallResponseInfo_t {
    SubjectDeviceID_t deviceOnCall;
    ConnectionID_t  callIdentifier;
    LocalConnectionState_t localConnectionState;
} CSTASnapshotCallResponseInfo_t;

typedef struct CSTASnapshotCallData_t {
    unsigned int    count;
    CSTASnapshotCallResponseInfo_t *info;
} CSTASnapshotCallData_t;

#endif /* OSS_CSTA_status_reporting */
