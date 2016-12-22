/* Copyright (C) 2001-2010 Avaya Inc.  All rights reserved. */

/*
 * 
 *  acs.h    ACS Events Defines
 *
 *  Header File Dependencies
 *      tsplatfm.h
 *      acsdefs.h
 *
 */

#ifndef ACS_H
#define ACS_H

/* platform-dependent definitions */
#include "tsplatfm.h"

#if defined ( TSLIB_WINDOWS_32 )
  #include <windows.h>
#endif


/* SAP advertising for CSTA streams from the Tserver */
#define TSERV_SAP_CSTA         0x0559   /* For CSTA TServers */

/* SAP advertising number client uses to find the Tserver is the same number
 * which has first been byte swapped.
 */
#define CLIENT_SAP_CSTA        0x5905  /* For CSTA Clients */

/* SAP advertising for Name Server Queries */
#define TSERV_SAP_NMSRV        0x055B  /* For Name Services on Tsrv */

/* SAP advertising number client uses to find the Name Server is the same number
 * which has first been byte swapped.
 */
#define CLIENT_SAP_NMSRV       0x5B05  /* For Name Service Clients */

typedef _Int    RetCode_t;

/* structure definitions for ACS messages */
#include <acsdefs.h>

#define ACSPOSITIVE_ACK              0  /* The function was successful */

/* Error Codes */

#define ACSERR_APIVERDENIED         -1  /* This return indicates that the 
                                         * API Version requested is invalid
                                         * and not supported by the
                                         * existing API Client Library.
                                         */

#define ACSERR_BADPARAMETER         -2  /* One or more of the parameters is
                                         * invalid
                                         */

#define ACSERR_DUPSTREAM            -3  /* This return indicates that an
                                         * ACS Stream is already established
                                         * with the requested Server.
                                         */

#define ACSERR_NODRIVER             -4  /* This error return value indicates 
                                         * that no API Client Library Driver
                                         * was found or installed on the
                                         * system.
                                         */

#define ACSERR_NOSERVER             -5  /* This indicates that the requested 
                                         * Server is not present in the
                                         * network.
                                         */

#define ACSERR_NORESOURCE           -6  /* This return value indicates that 
                                         * there are insufficient resources
                                         * to open a ACS Stream.
                                         */

#define ACSERR_UBUFSMALL            -7  /* The user buffer size was smaller 
                                         * than the size of the next available
                                         * event.
                                         */

#define ACSERR_NOMESSAGE            -8  /* There were no messages available to 
                                         * return to the application.
                                         */

#define ACSERR_UNKNOWN              -9  /* The ACS Stream has encountered
                                         * an unspecified error.
                                         */

#define ACSERR_BADHDL              -10  /* The ACS Handle is invalid */

#define ACSERR_STREAM_FAILED       -11  /* The ACS Stream has failed
                                         * due to network problems.
                                         * No further operations are
                                         * possible on this stream.
                                         */

#define ACSERR_NOBUFFERS           -12  /* There were not enough buffers 
                                         * available to place an outgoing
                                         * message on the send queue.
                                         * No message has been sent.
                                         */

#define ACSERR_QUEUE_FULL          -13  /* The send queue is full. 
                                         * No message has been sent.
                                         */

#define ACSERR_SSL_INIT_FAILED     -14  /* This return value indicates that a
                                         * stream could not be opened because
                                         * initialization of the OpenSSL library
                                         * failed.
                                         */

#define ACSERR_SSL_CONNECT_FAILED  -15  /* This return value indicates that a
                                         * stream could not be opened because
                                         * the SSL connection failed.
                                         */

#define ACSERR_SSL_FQDN_MISMATCH   -16  /* This return value indicates that a
                                         * stream could not be opened because
                                         * during the SSL handshake, the fully
                                         * qualified domain name (FQDN) in the
                                         * server certificate did not match the
                                         * expected FQDN.
                                         */

typedef unsigned long InvokeID_t;

typedef enum {
    APP_GEN_ID,     /* application will provide invokeIDs; any 4-byte value is legal */
    LIB_GEN_ID      /* library will generate invokeIDs in the range 1-32767 */
} InvokeIDType_t;


typedef unsigned short  EventClass_t;

/* defines for ACS event classes */

#define ACSREQUEST          0
#define ACSUNSOLICITED      1
#define ACSCONFIRMATION     2

typedef unsigned short  EventType_t;   /* event types are defined in acs.h and csta.h */

typedef struct 
{
    ACSHandle_t     acsHandle;
    EventClass_t    eventClass;
    EventType_t     eventType;

} ACSEventHeader_t;


typedef struct 
{
    union 
    {
        ACSUniversalFailureEvent_t  failureEvent;

        /* future types to be defined here */
    } u;

} ACSUnsolicitedEvent;

#define ACS_MAX_HEAP    1024

typedef struct 
{
    InvokeID_t  invokeID;
    union 
    {
        ACSOpenStreamConfEvent_t            acsopen;
        ACSCloseStreamConfEvent_t           acsclose;
        ACSSetHeartbeatIntervalConfEvent_t  acssetheartbeatinterval;
#ifdef NAMEDAPP
#include "acsnamedappconf.h"
#else
        ACSReservedPDU18_t                  acsReservedPDU18;
        ACSReservedPDU20_t                  acsReservedPDU20;
#endif
        ACSUniversalFailureConfEvent_t      failureEvent;
    } u;

} ACSConfirmationEvent;

typedef struct 
{
    ACSEventHeader_t    eventHeader;
    union 
    {
        ACSUnsolicitedEvent     acsUnsolicited;
        ACSConfirmationEvent    acsConfirmation;
    } event;
    char    heap[ACS_MAX_HEAP];
      
} ACSEvent_t;

typedef char Passwd_t[49];

#define PRIVATE_VENDOR_SIZE 32

typedef struct PrivateData_t {
    char            vendor[PRIVATE_VENDOR_SIZE];
    unsigned short  length;
    char            data[1];    /* actual length determined by application */
} PrivateData_t;

#define PRIVATE_DATA_ENCODING       0

/* function prototypes */

#ifdef __cplusplus
extern "C"
{
#endif  

TSAPI
acsOpenStream ( ACSHandle_t                     FAR *acsHandle,
                InvokeIDType_t                  invokeIDType,
                InvokeID_t                      invokeID,
                StreamType_t                    streamType,
                CONST_PARAM ServerID_t      FAR *serverID,
                CONST_PARAM LoginID_t       FAR *loginID,
                CONST_PARAM Passwd_t        FAR *passwd,
                CONST_PARAM AppName_t       FAR *applicationName,
                Level_t                         acsLevelReq,
                CONST_PARAM Version_t       FAR *apiVer,
                unsigned short                  sendQSize,
                unsigned short                  sendExtraBufs,
                unsigned short                  recvQSize,
                unsigned short                  recvExtraBufs,
                CONST_PARAM PrivateData_t   FAR *priv);


TSAPI
acsCloseStream (ACSHandle_t                     acsHandle,
                InvokeID_t                      invokeID,
                CONST_PARAM PrivateData_t   FAR *priv);


TSAPI
acsAbortStream (ACSHandle_t                     acsHandle,
                CONST_PARAM PrivateData_t   FAR *priv);


TSAPI
acsFlushEventQueue (ACSHandle_t                 acsHandle);


TSAPI
acsGetEventPoll (   ACSHandle_t                 acsHandle,
                    void                    FAR *eventBuf,
                    unsigned short          FAR *eventBufSize,
                    PrivateData_t           FAR *privData,
                    unsigned short          FAR *numEvents);


TSAPI
acsGetEventBlock (  ACSHandle_t                 acsHandle,
                    void                    FAR *eventBuf,
                    unsigned short          FAR *eventBufSize,
                    PrivateData_t           FAR *privData,
                    unsigned short          FAR *numEvents);

/* 32-bit Windows-specific prototypes */

#if defined ( TSLIB_WINDOWS_32 )

TSAPI
acsEventNotify (ACSHandle_t acsHandle, HWND hwnd, UINT msg, Boolean notifyAll);


TSAPI
acsSetESR ( ACSHandle_t     acsHandle,
        void            (far pascal *esr)(unsigned long esrParam),
        unsigned long   esrParam,
        Boolean         notifyAll);

typedef Boolean ( *EnumServerNamesCB) ( char  *serverName,
                                        unsigned long lParam);

/* Linux-specific prototypes */

#elif defined ( TSLIB_LINUX )

TSAPI
acsGetFile (ACSHandle_t acsHandle);

typedef Boolean (* EnumServerNamesCB) ( char *serverName,
                                        unsigned long lParam);

#endif


TSAPI
acsEnumServerNames (StreamType_t        streamType,
                    EnumServerNamesCB   userCB,
                    unsigned long       lParam);



TSAPI
acsQueryAuthInfo (  CONST_PARAM ServerID_t      FAR *serverID,
                    ACSAuthInfo_t               FAR *authInfo);


TSAPI
acsGetServerID (    ACSHandle_t         acsHandle,
                    ServerID_t          *serverID);

TSAPI
acsSetHeartbeatInterval (   ACSHandle_t             acsHandle,
                            InvokeID_t              invokeID,
                            unsigned short          heartbeatInterval,
                            PrivateData_t           *privData);

const char *
acsReturnCodeString(RetCode_t returnCode);

const char *
acsReturnCodeVerboseString(RetCode_t returnCode);

const char *
acsErrorString(ACSUniversalFailure_t error);

#ifdef __cplusplus
}
#endif  

#endif

