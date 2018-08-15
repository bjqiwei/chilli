/*************************************************************/
/* Copyright (C) 2010 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/
/* Generated for: Avaya Inc., Basking Ridge, NJ - license 7175 for Windows */
/* Abstract syntax: CSTA_control_services */
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

#ifndef OSS_CSTA_control_services
#define OSS_CSTA_control_services

#include "ossship.h"

#ifndef OSS_INT32
#define OSS_INT32 int
#endif /* OSS_INT32 */

#include "CSTA_device_identifiers.h"


typedef struct CSTAGetAPICaps_t {
    Nulltype        null;
} CSTAGetAPICaps_t;

typedef struct CSTAGetAPICapsConfEvent_t {
    short           alternateCall;
    short           answerCall;
    short           callCompletion;
    short           clearCall;
    short           clearConnection;
    short           conferenceCall;
    short           consultationCall;
    short           deflectCall;
    short           pickupCall;
    short           groupPickupCall;
    short           holdCall;
    short           makeCall;
    short           makePredictiveCall;
    short           queryMwi;
    short           queryDnd;
    short           queryFwd;
    short           queryAgentState;
    short           queryLastNumber;
    short           queryDeviceInfo;
    short           reconnectCall;
    short           retrieveCall;
    short           setMwi;
    short           setDnd;
    short           setFwd;
    short           setAgentState;
    short           transferCall;
    short           eventReport;
    short           callClearedEvent;
    short           conferencedEvent;
    short           connectionClearedEvent;
    short           deliveredEvent;
    short           divertedEvent;
    short           establishedEvent;
    short           failedEvent;
    short           heldEvent;
    short           networkReachedEvent;
    short           originatedEvent;
    short           queuedEvent;
    short           retrievedEvent;
    short           serviceInitiatedEvent;
    short           transferredEvent;
    short           callInformationEvent;
    short           doNotDisturbEvent;
    short           forwardingEvent;
    short           messageWaitingEvent;
    short           loggedOnEvent;
    short           loggedOffEvent;
    short           notReadyEvent;
    short           readyEvent;
    short           workNotReadyEvent;
    short           workReadyEvent;
    short           backInServiceEvent;
    short           outOfServiceEvent;
    short           privateEvent;
    short           routeRequestEvent;
    short           reRoute;
    short           routeSelect;
    short           routeUsedEvent;
    short           routeEndEvent;
    short           monitorDevice;
    short           monitorCall;
    short           monitorCallsViaDevice;
    short           changeMonitorFilter;
    short           monitorStop;
    short           monitorEnded;
    short           snapshotDeviceReq;
    short           snapshotCallReq;
    short           escapeService;
    short           privateStatusEvent;
    short           escapeServiceEvent;
    short           escapeServiceConf;
    short           sendPrivateEvent;
    short           sysStatReq;
    short           sysStatStart;
    short           sysStatStop;
    short           changeSysStatFilter;
    short           sysStatReqEvent;
    short           sysStatReqConf;
    short           sysStatEvent;
} CSTAGetAPICapsConfEvent_t;

typedef enum CSTALevel_t {
    cstaHomeWorkTop = 1,
    cstaAwayWorkTop = 2,
    cstaDeviceDeviceMonitor = 3,
    cstaCallDeviceMonitor = 4,
    cstaCallControl = 5,
    cstaRouting = 6,
    cstaCallCallMonitor = 7
} CSTALevel_t;

typedef enum SDBLevel_t {
    noSdbChecking = -1,
    acsOnly = 1,
    acsAndCstaChecking = 0
} SDBLevel_t;

typedef struct CSTAGetDeviceList_t {
    long            index;
    CSTALevel_t     level;
} CSTAGetDeviceList_t;

typedef struct DeviceList_t {
    unsigned short  count;
    DeviceID_t      device[20];
} DeviceList_t;

typedef struct CSTAGetDeviceListConfEvent_t {
    SDBLevel_t      driverSdbLevel;
    CSTALevel_t     level;
    long            index;
    DeviceList_t    devList;
} CSTAGetDeviceListConfEvent_t;

typedef struct CSTAQueryCallMonitor_t {
    Nulltype        null;
} CSTAQueryCallMonitor_t;

typedef struct CSTAQueryCallMonitorConfEvent_t {
    unsigned char   callMonitor;
} CSTAQueryCallMonitorConfEvent_t;

#endif /* OSS_CSTA_control_services */
