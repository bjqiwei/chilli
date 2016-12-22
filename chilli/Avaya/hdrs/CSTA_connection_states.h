/*************************************************************/
/* Copyright (C) 2010 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/
/* Generated for: Avaya Inc., Basking Ridge, NJ - license 7175 for Windows */
/* Abstract syntax: CSTA_connection_states */
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

#ifndef OSS_CSTA_connection_states
#define OSS_CSTA_connection_states

#include "ossship.h"

#ifndef OSS_INT32
#define OSS_INT32 int
#endif /* OSS_INT32 */

#include "CSTA_device_identifiers.h"
#include "CSTA_call_connection_identifiers.h"


typedef struct Connection_t {
    ConnectionID_t  party;
    SubjectDeviceID_t staticDevice;
} Connection_t;

typedef struct ConnectionList_t {
    unsigned int    count;
    Connection_t    *connection;
} ConnectionList_t;

typedef enum LocalConnectionState_t {
    csNone = -1,
    csNull = 0,
    csInitiate = 1,
    csAlerting = 2,
    csConnect = 3,
    csHold = 4,
    csQueued = 5,
    csFail = 6
} LocalConnectionState_t;

#endif /* OSS_CSTA_connection_states */
