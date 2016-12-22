/*************************************************************/
/* Copyright (C) 2010 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/
/* Generated for: Avaya Inc., Basking Ridge, NJ - license 7175 for Windows */
/* Abstract syntax: CSTA_device_feature_types */
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

#ifndef OSS_CSTA_device_feature_types
#define OSS_CSTA_device_feature_types

#include "ossship.h"

#ifndef OSS_INT32
#define OSS_INT32 int
#endif /* OSS_INT32 */

#include "CSTA_device_identifiers.h"


typedef char            AccountInfo_t[32];

typedef char            AgentID_t[32];

typedef DeviceID_t      AgentGroup_t;

typedef char            AgentPassword_t[32];

typedef char            AuthCode_t[32];

typedef enum ForwardingType_t {
    fwdImmediate = 0,
    fwdBusy = 1,
    fwdNoAns = 2,
    fwdBusyInt = 3,
    fwdBusyExt = 4,
    fwdNoAnsInt = 5,
    fwdNoAnsExt = 6
} ForwardingType_t;

typedef struct ForwardingInfo_t {
    ForwardingType_t forwardingType;
    unsigned char   forwardingOn;
    DeviceID_t      forwardDN;
} ForwardingInfo_t;

typedef struct ListForwardParameters_t {
    unsigned short  count;
    ForwardingInfo_t param[7];
} ListForwardParameters_t;

typedef enum SelectValue_t {
    svNormal = 0,
    svLeastCost = 1,
    svEmergency = 2,
    svAcd = 3,
    svUserDefined = 4
} SelectValue_t;

typedef struct SetUpValues_t {
    unsigned int    length;
    unsigned char   *value;
} SetUpValues_t;

typedef short           RetryValue_t;
#define                     noListAvailable -1
#define                     noCountAvailable -2

typedef long            RoutingCrossRefID_t;

typedef long            RouteRegisterReqID_t;

#endif /* OSS_CSTA_device_feature_types */
