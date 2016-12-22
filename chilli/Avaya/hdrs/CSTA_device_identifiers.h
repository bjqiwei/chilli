/*************************************************************/
/* Copyright (C) 2010 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/
/* Generated for: Avaya Inc., Basking Ridge, NJ - license 7175 for Windows */
/* Abstract syntax: CSTA_device_identifiers */
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

#ifndef OSS_CSTA_device_identifiers
#define OSS_CSTA_device_identifiers

#include "ossship.h"

#ifndef OSS_INT32
#define OSS_INT32 int
#endif /* OSS_INT32 */



typedef char            DeviceID_t[64];

typedef enum DeviceIDType_t {
    deviceIdentifier = 0,
    implicitPublic = 20,
    explicitPublicUnknown = 30,
    explicitPublicInternational = 31,
    explicitPublicNational = 32,
    explicitPublicNetworkSpecific = 33,
    explicitPublicSubscriber = 34,
    explicitPublicAbbreviated = 35,
    implicitPrivate = 40,
    explicitPrivateUnknown = 50,
    explicitPrivateLevel3RegionalNumber = 51,
    explicitPrivateLevel2RegionalNumber = 52,
    explicitPrivateLevel1RegionalNumber = 53,
    explicitPrivatePtnSpecificNumber = 54,
    explicitPrivateLocalNumber = 55,
    explicitPrivateAbbreviated = 56,
    otherPlan = 60,
    trunkIdentifier = 70,
    trunkGroupIdentifier = 71
} DeviceIDType_t;

typedef enum DeviceIDStatus_t {
    idProvided = 0,
    idNotKnown = 1,
    idNotRequired = 2
} DeviceIDStatus_t;

typedef struct ExtendedDeviceID_t {
    DeviceID_t      deviceID;
    DeviceIDType_t  deviceIDType;
    DeviceIDStatus_t deviceIDStatus;
} ExtendedDeviceID_t;

typedef ExtendedDeviceID_t CallingDeviceID_t;

typedef ExtendedDeviceID_t CalledDeviceID_t;

typedef ExtendedDeviceID_t SubjectDeviceID_t;

typedef ExtendedDeviceID_t RedirectionDeviceID_t;

#endif /* OSS_CSTA_device_identifiers */
