/*************************************************************/
/* Copyright (C) 2010 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/
/* Generated for: Avaya Inc., Basking Ridge, NJ - license 7175 for Windows */
/* Abstract syntax: CSTA_event_causes */
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

#ifndef OSS_CSTA_event_causes
#define OSS_CSTA_event_causes

#include "ossship.h"

#ifndef OSS_INT32
#define OSS_INT32 int
#endif /* OSS_INT32 */


typedef enum CSTAEventCause_t {
    ecNone = -1,
    ecActiveMonitor = 1,
    ecAlternate = 2,
    ecBusy = 3,
    ecCallBack = 4,
    ecCallCancelled = 5,
    ecCallForwardAlways = 6,
    ecCallForwardBusy = 7,
    ecCallForwardNoAnswer = 8,
    ecCallForward = 9,
    ecCallNotAnswered = 10,
    ecCallPickup = 11,
    ecCampOn = 12,
    ecDestNotObtainable = 13,
    ecDoNotDisturb = 14,
    ecIncompatibleDestination = 15,
    ecInvalidAccountCode = 16,
    ecKeyConference = 17,
    ecLockout = 18,
    ecMaintenance = 19,
    ecNetworkCongestion = 20,
    ecNetworkNotObtainable = 21,
    ecNewCall = 22,
    ecNoAvailableAgents = 23,
    ecOverride = 24,
    ecPark = 25,
    ecOverflow = 26,
    ecRecall = 27,
    ecRedirected = 28,
    ecReorderTone = 29,
    ecResourcesNotAvailable = 30,
    ecSilentMonitor = 31,
    ecTransfer = 32,
    ecTrunksBusy = 33,
    ecVoiceUnitInitiator = 34,
    ecNetworkSignal = 46,
    ecSingleStepTransfer = 52,
    ecAlertTimeExpired = 60,
    ecDestOutOfOrder = 65,
    ecNotSupportedBearerService = 80,
    ecUnassignedNumber = 81,
    ecIncompatibleBearerService = 87
} CSTAEventCause_t;

#endif /* OSS_CSTA_event_causes */
