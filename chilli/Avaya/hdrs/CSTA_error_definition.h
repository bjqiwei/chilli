/*************************************************************/
/* Copyright (C) 2010 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/
/* Generated for: Avaya Inc., Basking Ridge, NJ - license 7175 for Windows */
/* Abstract syntax: CSTA_error_definition */
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

#ifndef OSS_CSTA_error_definition
#define OSS_CSTA_error_definition

#include "ossship.h"

#ifndef OSS_INT32
#define OSS_INT32 int
#endif /* OSS_INT32 */


typedef enum CSTAUniversalFailure_t {
    genericUnspecified = 0,
    genericOperation = 1,
    requestIncompatibleWithObject = 2,
    valueOutOfRange = 3,
    objectNotKnown = 4,
    invalidCallingDevice = 5,
    invalidCalledDevice = 6,
    invalidForwardingDestination = 7,
    privilegeViolationOnSpecifiedDevice = 8,
    privilegeViolationOnCalledDevice = 9,
    privilegeViolationOnCallingDevice = 10,
    invalidCstaCallIdentifier = 11,
    invalidCstaDeviceIdentifier = 12,
    invalidCstaConnectionIdentifier = 13,
    invalidDestination = 14,
    invalidFeature = 15,
    invalidAllocationState = 16,
    invalidCrossRefId = 17,
    invalidObjectType = 18,
    securityViolation = 19,
    genericStateIncompatibility = 21,
    invalidObjectState = 22,
    invalidConnectionIdForActiveCall = 23,
    noActiveCall = 24,
    noHeldCall = 25,
    noCallToClear = 26,
    noConnectionToClear = 27,
    noCallToAnswer = 28,
    noCallToComplete = 29,
    genericSystemResourceAvailability = 31,
    serviceBusy = 32,
    resourceBusy = 33,
    resourceOutOfService = 34,
    networkBusy = 35,
    networkOutOfService = 36,
    overallMonitorLimitExceeded = 37,
    conferenceMemberLimitExceeded = 38,
    genericSubscribedResourceAvailability = 41,
    objectMonitorLimitExceeded = 42,
    externalTrunkLimitExceeded = 43,
    outstandingRequestLimitExceeded = 44,
    genericPerformanceManagement = 51,
    performanceLimitExceeded = 52,
    unspecifiedSecurityError = 60,
    sequenceNumberViolated = 61,
    timeStampViolated = 62,
    pacViolated = 63,
    sealViolated = 64,
    genericUnspecifiedRejection = 70,
    genericOperationRejection = 71,
    duplicateInvocationRejection = 72,
    unrecognizedOperationRejection = 73,
    mistypedArgumentRejection = 74,
    resourceLimitationRejection = 75,
    acsHandleTerminationRejection = 76,
    serviceTerminationRejection = 77,
    requestTimeoutRejection = 78,
    requestsOnDeviceExceededRejection = 79,
    unrecognizedApduRejection = 80,
    mistypedApduRejection = 81,
    badlyStructuredApduRejection = 82,
    initiatorReleasingRejection = 83,
    unrecognizedLinkedidRejection = 84,
    linkedResponseUnexpectedRejection = 85,
    unexpectedChildOperationRejection = 86,
    mistypedResultRejection = 87,
    unrecognizedErrorRejection = 88,
    unexpectedErrorRejection = 89,
    mistypedParameterRejection = 90,
    nonStandard = 100
} CSTAUniversalFailure_t;

#endif /* OSS_CSTA_error_definition */
