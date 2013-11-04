//*****************************************************************************
//Copyright(c)  :  DONJIN CORPORTAION  All Rights Reserved                       
//FileName      :  ITPDataDefine.h                                                              
//Version       :  1.0                                                              
//Author        :  兰骏                                                             
//DateTime      :  2005-03-22 10:00                                           
//Description   :  实现ITP系统跨平台数据类型定义       
//Revision:20060225: 增加DSP平台数据类型定义(	廖永坤)                                                         
//Revision:20060425: 修改了DSP平台的SOCKET类型定义(	钟晓晖)                                                         
//*****************************************************************************

#ifndef _ITPDATADEFINE_H
#define _ITPDATADEFINE_H

//数据基本类型定义

typedef unsigned char     DJ_U8;
typedef char              DJ_S8;
typedef unsigned short    DJ_U16;
typedef short             DJ_S16;
#ifdef	CHIP_DM642
typedef	unsigned int	  DJ_U32;
typedef int				  DJ_S32;
#else
typedef unsigned long     DJ_U32;
typedef long              DJ_S32;
#endif

#ifdef WIN32
//typedef unsigned _int64   DJ_U64;
//typedef _int64            DJ_S64;
#else 
#ifdef	CHIP_DM642
typedef	unsigned long	DJ_U40;
typedef long			DJ_S40;
typedef double 			DJ_U64;
typedef double         	DJ_S64;
#else
typedef unsigned long long DJ_U64;
typedef long long         DJ_S64;
typedef int              BOOL;
#endif
#endif

typedef void              DJ_Void;
typedef void*             DJ_HANDLE;

typedef float    DJ_F32;
typedef double   DJ_F64;

#ifdef CHIP_DM642
typedef SOCKET  DJ_SOCKET; 		// modified by zxh at 20060425
#else
typedef unsigned int  DJ_SOCKET; 
#endif

typedef int              DJ_SI32;
typedef unsigned int     DJ_UI32;

#ifndef		CHIP_DM642
#define  TRUE    1
#define  FALSE   0
#endif

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#define ACS_MAX_FILE_NAME_LEN        128
#define ACS_MAX_FILE_NUM             8

typedef DJ_S32  RetCode_t;
typedef DJ_U32  ACSHandle_t;
typedef DJ_S32  InvokeID_t;
typedef DJ_S8   LoginID_t;
typedef DJ_S32  EventClass_t;
typedef DJ_S32  EventType_t;
typedef DJ_S32  ACSConfirmation_t;
typedef DJ_S8   CallNum_t;
typedef DJ_S32  AcsCmdTye_t;

typedef DJ_S32  FlowType_t;
typedef DJ_S32  FlowChannel_t;
typedef DJ_S16  DeviceMain_t;
typedef DJ_S16  DeviceSub_t;
typedef DJ_S16  DeviceGroup_t;
typedef DJ_S8   ModuleID_t;
typedef DJ_S16  ChannelID_t;
typedef DJ_S8   ParmName_t;
typedef DJ_S32  ParmSize_t;
typedef DJ_S32  Version_t;
typedef DJ_Void * Nulltype;
typedef DJ_S32  ACSUniversalFailure_t;
typedef DJ_S8   PlayCont_t;
typedef DJ_S8   FilePath_t;

typedef DJ_S32  Acs_Evt_State_t;
typedef DJ_S32  Acs_Evt_ErrCode_t;
typedef DJ_S8   Acs_MediaProc_Dtmf_t;

#endif

