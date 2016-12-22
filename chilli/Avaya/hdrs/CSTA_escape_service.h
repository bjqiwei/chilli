/*************************************************************/
/* Copyright (C) 2010 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/
/* Generated for: Avaya Inc., Basking Ridge, NJ - license 7175 for Windows */
/* Abstract syntax: CSTA_escape_service */
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

#ifndef OSS_CSTA_escape_service
#define OSS_CSTA_escape_service

#include "ossship.h"

#ifndef OSS_INT32
#define OSS_INT32 int
#endif /* OSS_INT32 */

#include "CSTA_error_definition.h"


typedef struct CSTAEscapeSvc_t {
    Nulltype        null;
} CSTAEscapeSvc_t;

typedef struct CSTAEscapeSvcConfEvent_t {
    Nulltype        null;
} CSTAEscapeSvcConfEvent_t;

typedef struct CSTAEscapeSvcReqEvent_t {
    Nulltype        null;
} CSTAEscapeSvcReqEvent_t;

typedef struct CSTAEscapeSvcReqConf_t {
    CSTAUniversalFailure_t errorValue;
} CSTAEscapeSvcReqConf_t;

#endif /* OSS_CSTA_escape_service */
