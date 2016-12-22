/*************************************************************/
/* Copyright (C) 2010 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/
/* Generated for: Avaya Inc., Basking Ridge, NJ - license 7175 for Windows */
/* Abstract syntax: acs_asn_tbl */
/* Created: Fri Sep 17 13:50:17 2010 */
/* ASN.1 compiler version: 7.0 */
/* Code generated for runtime version 7.0 or later */
/* Target operating system: Windows NT/Windows 9x */
/* Target machine type: Intel x86 */
/* C compiler options required: -Zp8 (Microsoft) */
/* ASN.1 compiler options and file names specified:
 * -headerfile ctiacsdefs.h -noshortennames -nouniquepdu -externalname
 * acs_asn_tbl -noconstraints -shippable -compat v4.1.3
 * C:\Program Files\OSS\ossasn1\win32\7.0.0\asn1dflt\asn1dflt.ms.zp8 acs.asn
 */

#ifndef OSS_acs_asn_tbl
#define OSS_acs_asn_tbl

#include "ossship.h"

#ifndef OSS_INT32
#define OSS_INT32 int
#endif /* OSS_INT32 */

#define          ACSOpenStream_t_PDU 1
#define          ACSOpenStreamConfEvent_t_PDU 2
#define          ACSCloseStream_t_PDU 3
#define          ACSCloseStreamConfEvent_t_PDU 4
#define          ACSAbortStream_t_PDU 5
#define          ACSUniversalFailureConfEvent_t_PDU 6
#define          ACSUniversalFailureEvent_t_PDU 7
#define          ACSKeyRequest_t_PDU 8
#define          ACSKeyReply_t_PDU 9
#define          ACSNameSrvRequest_t_PDU 10
#define          ACSNameSrvReply_t_PDU 11
#define          ACSAuthReply_t_PDU 12
#define          ACSAuthReplyTwo_t_PDU 13
#define          ACSSetHeartbeatInterval_t_PDU 14
#define          ACSSetHeartbeatIntervalConfEvent_t_PDU 15
#define          ACSClientHeartbeatEvent_t_PDU 16
#define          ACSReservedPDU17_t_PDU 17
#define          ACSReservedPDU18_t_PDU 18
#define          ACSReservedPDU19_t_PDU 19
#define          ACSReservedPDU20_t_PDU 20

typedef enum StreamType_t {
    stCsta = 1,
    stOam = 2,
    stDirectory = 3,
    stNmsrv = 4,
    stReserved5 = 5
} StreamType_t;

typedef char            ServerID_t[49];

typedef char            LoginID_t[49];

typedef struct CryptPasswd_t {
    unsigned short  length;
    unsigned char   value[47];
} CryptPasswd_t;

typedef char            AppName_t[21];

typedef enum Level_t {
    acsLevel1 = 1,
    acsLevel2 = 2,
    acsLevel3 = 3,
    acsLevel4 = 4
} Level_t;

typedef char            Version_t[21];

typedef struct ACSOpenStream_t {
    StreamType_t    streamType;
    ServerID_t      serverID;
    LoginID_t       loginID;
    CryptPasswd_t   cryptPass;
    AppName_t       applicationName;
    Level_t         level;
    Version_t       apiVer;
    Version_t       libVer;
    Version_t       tsrvVer;
} ACSOpenStream_t;

typedef struct ACSOpenStreamConfEvent_t {
    Version_t       apiVer;
    Version_t       libVer;
    Version_t       tsrvVer;
    Version_t       drvrVer;
} ACSOpenStreamConfEvent_t;

typedef struct ACSCloseStream_t {
    Nulltype        null;
} ACSCloseStream_t;

typedef struct ACSCloseStreamConfEvent_t {
    Nulltype        null;
} ACSCloseStreamConfEvent_t;

typedef struct ACSAbortStream_t {
    Nulltype        null;
} ACSAbortStream_t;

typedef enum ACSUniversalFailure_t {
    tserverStreamFailed = 0,
    tserverNoThread = 1,
    tserverBadDriverId = 2,
    tserverDeadDriver = 3,
    tserverMessageHighWaterMark = 4,
    tserverFreeBufferFailed = 5,
    tserverSendToDriver = 6,
    tserverReceiveFromDriver = 7,
    tserverRegistrationFailed = 8,
    tserverSpxFailed = 9,
    tserverTrace = 10,
    tserverNoMemory = 11,
    tserverEncodeFailed = 12,
    tserverDecodeFailed = 13,
    tserverBadConnection = 14,
    tserverBadPdu = 15,
    tserverNoVersion = 16,
    tserverEcbMaxExceeded = 17,
    tserverNoEcbs = 18,
    tserverNoSdb = 19,
    tserverNoSdbCheckNeeded = 20,
    tserverSdbCheckNeeded = 21,
    tserverBadSdbLevel = 22,
    tserverBadServerid = 23,
    tserverBadStreamType = 24,
    tserverBadPasswordOrLogin = 25,
    tserverNoUserRecord = 26,
    tserverNoDeviceRecord = 27,
    tserverDeviceNotOnList = 28,
    tserverUsersRestrictedHome = 30,
    tserverNoAwaypermission = 31,
    tserverNoHomepermission = 32,
    tserverNoAwayWorktop = 33,
    tserverBadDeviceRecord = 34,
    tserverDeviceNotSupported = 35,
    tserverInsufficientPermission = 36,
    tserverNoResourceTag = 37,
    tserverInvalidMessage = 38,
    tserverExceptionList = 39,
    tserverNotOnOamList = 40,
    tserverPbxIdNotInSdb = 41,
    tserverUserLicensesExceeded = 42,
    tserverOamDropConnection = 43,
    tserverNoVersionRecord = 44,
    tserverOldVersionRecord = 45,
    tserverBadPacket = 46,
    tserverOpenFailed = 47,
    tserverOamInUse = 48,
    tserverDeviceNotOnHomeList = 49,
    tserverDeviceNotOnCallControlList = 50,
    tserverDeviceNotOnAwayList = 51,
    tserverDeviceNotOnRouteList = 52,
    tserverDeviceNotOnMonitorDeviceList = 53,
    tserverDeviceNotOnMonitorCallDeviceList = 54,
    tserverNoCallCallMonitorPermission = 55,
    tserverHomeDeviceListEmpty = 56,
    tserverCallControlListEmpty = 57,
    tserverAwayListEmpty = 58,
    tserverRouteListEmpty = 59,
    tserverMonitorDeviceListEmpty = 60,
    tserverMonitorCallDeviceListEmpty = 61,
    tserverUserAtHomeWorktop = 62,
    tserverDeviceListEmpty = 63,
    tserverBadGetDeviceLevel = 64,
    tserverDriverUnregistered = 65,
    tserverNoAcsStream = 66,
    tserverDropOam = 67,
    tserverEcbTimeout = 68,
    tserverBadEcb = 69,
    tserverAdvertiseFailed = 70,
    tserverNetwareFailure = 71,
    tserverTdiQueueFault = 72,
    tserverDriverCongestion = 73,
    tserverNoTdiBuffers = 74,
    tserverOldInvokeid = 75,
    tserverHwmarkToLarge = 76,
    tserverSetEcbToLow = 77,
    tserverNoRecordInFile = 78,
    tserverEcbOverdue = 79,
    tserverBadPwEncryption = 80,
    tserverBadTservProtocol = 81,
    tserverBadDriverProtocol = 82,
    tserverBadTransportType = 83,
    tserverPduVersionMismatch = 84,
    tserverVersionMismatch = 85,
    tserverLicenseMismatch = 86,
    tserverBadAttributeList = 87,
    tserverBadTlistType = 88,
    tserverBadProtocolFormat = 89,
    tserverOldTslib = 90,
    tserverBadLicenseFile = 91,
    tserverNoPatches = 92,
    tserverSystemError = 93,
    tserverOamListEmpty = 94,
    tserverTcpFailed = 95,
    tserverSpxDisabled = 96,
    tserverTcpDisabled = 97,
    tserverRequiredModulesNotLoaded = 98,
    tserverTransportInUseByOam = 99,
    tserverNoNdsOamPermission = 100,
    tserverOpenSdbLogFailed = 101,
    tserverInvalidLogSize = 102,
    tserverWriteSdbLogFailed = 103,
    tserverNtFailure = 104,
    tserverLoadLibFailed = 105,
    tserverInvalidDriver = 106,
    tserverRegistryError = 107,
    tserverDuplicateEntry = 108,
    tserverDriverLoaded = 109,
    tserverDriverNotLoaded = 110,
    tserverNoLogonPermission = 111,
    tserverAccountDisabled = 112,
    tserverNoNetlogon = 113,
    tserverAcctRestricted = 114,
    tserverInvalidLogonTime = 115,
    tserverInvalidWorkstation = 116,
    tserverAcctLockedOut = 117,
    tserverPasswordExpired = 118,
    tserverInvalidHeartbeatInterval = 119,
    driverDuplicateAcshandle = 1000,
    driverInvalidAcsRequest = 1001,
    driverAcsHandleRejection = 1002,
    driverInvalidClassRejection = 1003,
    driverGenericRejection = 1004,
    driverResourceLimitation = 1005,
    driverAcshandleTermination = 1006,
    driverLinkUnavailable = 1007,
    driverOamInUse = 1008
} ACSUniversalFailure_t;

typedef struct ACSUniversalFailureConfEvent_t {
    ACSUniversalFailure_t error;
} ACSUniversalFailureConfEvent_t;

typedef struct ACSUniversalFailureEvent_t {
    ACSUniversalFailure_t error;
} ACSUniversalFailureEvent_t;

typedef struct ChallengeKey_t {
    unsigned short  length;
    unsigned char   value[8];
} ChallengeKey_t;

typedef struct ACSKeyRequest_t {
    LoginID_t       loginID;
} ACSKeyRequest_t;

typedef struct ACSKeyReply_t {
    long            objectID;
    ChallengeKey_t  key;
} ACSKeyReply_t;

typedef struct ACSNameSrvRequest_t {
    StreamType_t    streamType;
} ACSNameSrvRequest_t;

typedef struct ACSNameAddr_t {
    char            *serverName;
    struct {
        unsigned short  length;
        unsigned char   *value;
    } serverAddr;
} ACSNameAddr_t;

typedef struct ACSNameSrvReply_t {
    ossBoolean      more;
    struct {
        unsigned short  count;
        ACSNameAddr_t   *nameAddr;
    } list;
} ACSNameSrvReply_t;

typedef enum ACSAuthType_t {
    requiresExternalAuth = -1,
    authLoginIdOnly = 0,
    authLoginIdIsDefault = 1,
    needLoginIdAndPasswd = 2,
    anyLoginId = 3
} ACSAuthType_t;

typedef struct ACSAuthInfo_t {
    ACSAuthType_t   authType;
    LoginID_t       authLoginID;
} ACSAuthInfo_t;

typedef struct ACSAuthReply_t {
    long            objectID;
    ChallengeKey_t  key;
    ACSAuthInfo_t   authInfo;
} ACSAuthReply_t;

typedef enum ACSEncodeType_t {
    canUseBinderyEncryption = 1,
    ndsAuthConnid = 2,
    winNtLocal = 3,
    winNtNamedPipe = 4,
    winNtWriteData = 5
} ACSEncodeType_t;

typedef char            WinNTPipe_t[101];

typedef struct ACSAuthReplyTwo_t {
    long            objectID;
    ChallengeKey_t  key;
    ACSAuthInfo_t   authInfo;
    ACSEncodeType_t encodeType;
    WinNTPipe_t     pipe;
} ACSAuthReplyTwo_t;

typedef struct ACSSetHeartbeatInterval_t {
    short           heartbeatInterval;
} ACSSetHeartbeatInterval_t;

typedef struct ACSSetHeartbeatIntervalConfEvent_t {
    short           heartbeatInterval;
} ACSSetHeartbeatIntervalConfEvent_t;

typedef struct ACSClientHeartbeatEvent_t {
    Nulltype        null;
} ACSClientHeartbeatEvent_t;

typedef struct ACSReservedPDU17_t {
    Nulltype        null;
} ACSReservedPDU17_t;

typedef struct ACSReservedPDU18_t {
    char            reservestring[33];
} ACSReservedPDU18_t;

typedef struct ACSReservedPDU19_t {
    char            reservestring[20481];
} ACSReservedPDU19_t;

typedef struct ACSReservedPDU20_t {
    Nulltype        null;
} ACSReservedPDU20_t;

#endif /* OSS_acs_asn_tbl */
