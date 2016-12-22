/*************************************************************/
/* Copyright (C) 2010 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/
/* Generated for: Avaya Inc., Basking Ridge, NJ - license 7175 for Windows */
/* Abstract syntax: CSTA_query_device */
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

#ifndef OSS_CSTA_query_device
#define OSS_CSTA_query_device

#include "ossship.h"

#ifndef OSS_INT32
#define OSS_INT32 int
#endif /* OSS_INT32 */

#include "CSTA_device_feature_types.h"
#include "CSTA_device_identifiers.h"


typedef struct CSTAQueryMwi_t {
    DeviceID_t      device;
} CSTAQueryMwi_t;

typedef struct CSTAQueryMwiConfEvent_t {
    unsigned char   messages;
} CSTAQueryMwiConfEvent_t;

typedef struct CSTAQueryDnd_t {
    DeviceID_t      device;
} CSTAQueryDnd_t;

typedef struct CSTAQueryDndConfEvent_t {
    unsigned char   doNotDisturb;
} CSTAQueryDndConfEvent_t;

typedef struct CSTAQueryFwd_t {
    DeviceID_t      device;
} CSTAQueryFwd_t;

typedef struct CSTAQueryFwdConfEvent_t {
    ListForwardParameters_t forward;
} CSTAQueryFwdConfEvent_t;

typedef struct CSTAQueryAgentState_t {
    DeviceID_t      device;
} CSTAQueryAgentState_t;

typedef enum AgentState_t {
    agNotReady = 0,
    agNull = 1,
    agReady = 2,
    agWorkNotReady = 3,
    agWorkReady = 4
} AgentState_t;

typedef struct CSTAQueryAgentStateConfEvent_t {
    AgentState_t    agentState;
} CSTAQueryAgentStateConfEvent_t;

typedef struct CSTAQueryLastNumber_t {
    DeviceID_t      device;
} CSTAQueryLastNumber_t;

typedef struct CSTAQueryLastNumberConfEvent_t {
    DeviceID_t      lastNumber;
} CSTAQueryLastNumberConfEvent_t;

typedef struct CSTAQueryDeviceInfo_t {
    DeviceID_t      device;
} CSTAQueryDeviceInfo_t;

typedef enum DeviceType_t {
    dtStation = 0,
    dtLine = 1,
    dtButton = 2,
    dtAcd = 3,
    dtTrunk = 4,
    dtOperator = 5,
    dtStationGroup = 16,
    dtLineGroup = 17,
    dtButtonGroup = 18,
    dtAcdGroup = 19,
    dtTrunkGroup = 20,
    dtOperatorGroup = 21,
    dtOther = 255
} DeviceType_t;

typedef unsigned char   DeviceClass_t;
#define                     dcVoice 0x80
#define                     dcData 0x40
#define                     dcImage 0x20
#define                     dcOther 0x10

typedef struct CSTAQueryDeviceInfoConfEvent_t {
    DeviceID_t      device;
    DeviceType_t    deviceType;
    DeviceClass_t   deviceClass;
} CSTAQueryDeviceInfoConfEvent_t;

#endif /* OSS_CSTA_query_device */
