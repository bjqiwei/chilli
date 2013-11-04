//*****************************************************************************
//Copyright(c)  :  DONJIN CORPORTAION  All Rights Reserved                       
//FileName      :  ITPMainModCallBack.h
//Version       :  1.1                                                              
//Author        :  hewei                                                             
//DateTime      :  2006-05-08 15:00                                           
//Description  :   ITP主控程序回调接口定义文件
//*****************************************************************************

#ifndef _ITPMAINMODCALLBACK_H
#define _ITPMAINMODCALLBACK_H

#include "ITPDataDefine.h"
#include "ITPMsgPublic.h"
//#include "ITPLogManager.h"

#define ITP_MANAGE_MODULE_NUM                       1      // 配置管理模块数目
#define ITP_MAX_MOD_TYPE_NUM                        128    // 最大模块数
#define ITP_MAX_UNIT_NUM                            128    // 最大UNIT数目
#define ITP_MAX_CH_NUM                              128    // 最大通道数目

/************************************************************************/
/*功能描述:    获取本模块的UnitID                                       */
/*输入参数:    无                                                       */
/*输出参数:    无                                                       */
/*返回值  :    模块UnitID                                               */
typedef DJ_U8     (*PFUNC_GETSELFUNITID)();
/************************************************************************/

/************************************************************************/
/*功能描述:    获取本模块的运行状态                                     */
/*输入参数:    无                                                       */
/*输出参数:    无                                                       */
/*返回值  :                                                             */
/*             0x01    //模块已初始化                                   */ 
/*             0x02    //模块已启动                                     */
/*             0x04    //模块已全部被其上级模块关联                     */ 
/*             0x08    //模块已被监视                                   */
/*             0x10    //模块已连接                                     */
/*             0x20    //模块正在停止                                   */ 
/*             0x40    //正在运行模块                                   */
typedef DJ_U32    (*PFUNC_GETMODSTATE)();
/************************************************************************/

/************************************************************************/
/*功能描述:    向其他模块发送数据包                                     */
/*输入参数:                                                             */
/*             u8ModType: 目的模块类型                                  */
/*             u8UnitId : 目的模块UnitID                                */
/*             pData    : 发送的ITP数据,包含ITP包头                     */
/*输出参数:    无                                                       */
/*返回值  :    0:成功; -1:失败                                          */
typedef DJ_S32    (*PFUNC_SENDPACK)(DJ_U8 u8ModType,DJ_U8 u8UnitId,PPKG_HEAD_STRUCT pData);
/************************************************************************/
/************************************************************************/
/*功能描述:    向其他模块发送数据包                                     */
/*输入参数:                                                             */
/*             u8ModType: 目的模块类型                                  */
/*             u8UnitId : 目的模块UnitID                                */
/*             pData    : 发送的ITP数据,包含ITP包头                     */
/*             u8Flag   : 消息包发送方向			                    */
/*输出参数:    无                                                       */
/*返回值  :    0:成功; -1:失败                                          */
typedef DJ_S32    (*PFUNC_SENDPACKEX)(DJ_U8 u8ModType,DJ_U8 u8UnitId,PPKG_HEAD_STRUCT pData, DJ_U8 u8Flag);
/************************************************************************/
/************************************************************************/
/*功能描述:    向其他模块重发送数据包                                   */
/*输入参数:                                                             */
/*             u8ModType: 目的模块类型                                  */
/*             u8UnitId : 目的模块UnitID                                */
/*             pData    : 发送的ITP数据,包含ITP包头                     */
/*输出参数:    无                                                       */
/*返回值  :    0:成功; -1:失败                                          */
typedef DJ_S32    (*PFUNC_RESENDPACK)(DJ_U8 u8ModType,DJ_U8 u8UnitId,PPKG_HEAD_STRUCT pData);
/************************************************************************/

/************************************************************************/
/*功能描述:    获取指定模块的IP和port                                   */
/*输入参数:                                                             */
/*             u8ModType: 模块类型                                      */
/*             u8UnitId:  模块的UnitID                                  */
/*输出参数:    s8IPAddr:  返回的模块IP                                  */
/*返回值:      -1:失败; >0: 模块port                                    */
typedef DJ_S32    (*PFUNC_GETMODIPPORT)(DJ_U8 u8ModType,DJ_U8 u8UnitId,DJ_S8 * s8IPAddr);
/************************************************************************/

/************************************************************************/
/*功能描述:    获取本模块的ini文件名                                    */
/*输入参数:    无                                                       */
/*输出参数:    s8IniFile: 返回的ini文件名                               */
/*返回值:      0:成功; -1:失败                                          */
typedef DJ_S32    (*PFUNC_GETMODINIFILE)(DJ_S8 * s8IniFile);
/************************************************************************/

/************************************************************************/
/*功能描述:    获取其他模块的UnitID                                     */
/*输入参数:    无                                                       */
/*输出参数:    无                                                       */
/*返回值  :    模块UnitID                                               */
typedef DJ_U8     (*PFUNC_GETMODUNITID)(DJ_SOCKET);
/************************************************************************/

/************************************************************************/
/*功能描述:    获取指定模块的所有UnitID                                     */
/*输入参数:    无                                                       */
/*输出参数:    无                                                       */
/*返回值  :    模块UnitID                                               */
typedef DJ_U8     (*PFUNC_GETMODALLUNITID)(DJ_U8 u8ModType,DJ_U8 u8UnitID[]);
/************************************************************************/

/************************************************************************/
/*功能描述:    判断是否写入日志                                         */
/*输入参数:    无                                                       */
/*输出参数:    无                                                       */
/*返回值  :    0:  success,1: failure                                   */
typedef DJ_S32    (*PFUNC_IS_LOG_OUT)( DJ_U8 u8ModType, DJ_U8 u8ModUnitID, DJ_U8 u8LogLevel );
/************************************************************************/

/************************************************************************/
/*功能描述:    判断是否写入ITPCOM日志                                   */
/*输入参数:    无                                                       */
/*输出参数:    无                                                       */
/*返回值  :    0:  success,1: failure                                   */
typedef DJ_S32    (*PFUNC_IS_COM_LOG_OUT)( DJ_U8 u8ModType, DJ_U8 u8ModUnitID, PPKG_HEAD_STRUCT pHead );
/************************************************************************/

/************************************************************************/
/*功能描述:    写入二进制日志                                           */
/*输入参数:    无                                                       */
/*输出参数:    无                                                       */
/*返回值  :    0:  success,1: failure                                   */
typedef DJ_S32    (*PFUNC_LOG_OUT)( DJ_U8 u8Level, DJ_U8 u8DType, DJ_U8 u8DSType, DJ_U8 u8UnitID, DJ_U16 u16ChID, DJ_U8 u8MsgType, DJ_U8 u8ErrCode, DJ_U8 * pu8DataBuf, DJ_U32 u32DataLen );

/************************************************************************/
/*功能描述:    写入字符串日志                                           */
/*输入参数:    无                                                       */
/*输出参数:    无                                                       */
/*返回值  :    0:  success,1: failure                                   */
typedef DJ_S32    (*PFUNC_LOG_OUT_STR)( DJ_U8 u8Level, DJ_U8 u8DType, DJ_U8 u8DSType, DJ_U8 u8UnitID, DJ_U16 u16ChID , const DJ_S8 *format,... );


//define ITPLog Interface
typedef DJ_S32    (*PLOG_INIT)( DJ_Void* pCallBack, DJ_U8 u8LogType, DJ_U8 u8ModuleType, DJ_U8 u8ModuleUnitNo, DJ_S8 *pIniPath );
typedef DJ_S32    (*PLOG_RLS)( );

typedef DJ_S32    (*PLOG_GETCFG)( DJ_U32 u32CmdType, DJ_U8 *pu8Buf, DJ_U32 *pu32BufSize );
typedef DJ_S32    (*PLOG_SETCFG)( DJ_U32 u32CmdType, DJ_U8 *pu8Buf, DJ_U32 u32BufSize, DJ_U8 u8IsWriteIni );
typedef DJ_S32    (*PLOG_SETMSG)( DJ_Void *pMsgInfo );

typedef DJ_S32    (*PFUNC_LOGMOD_UPDATE_CFG)( const DJ_Void *pLogCfgInfo, DJ_U32 u32LogCfgInfoSize );

/************************************************************************/
/*功能描述:    获取指定模块的主从模块信息                               */
/*输入参数:    u8Master: 0代表从模块　1代表主模块                       */
/*			   u8UnitID: 从模块标识					                    */
/*			   u8HBMode: 热备模式: 0:单机模式，1: 热备模式              */
/*输出参数:    无                                                       */
/*返回值  :    模块UnitID                                               */
//typedef DJ_S32    (*PFUNC_GETMASTER)(DJ_U8 *u8Master,DJ_U8 *u8UnitID, DJ_U8* u8HBMode );
typedef DJ_S32    (*PFUNC_GETMASTER)(DJ_U8 *u8Master,DJ_U8 *u8UnitID );


/************************************************************************/
/************************************************************************/
/*功能描述:    主从状态切换回调函数			                            */
/*输入参数:    无												        */
/*													                    */
/*输出参数:    无                                                       */
/*返回值  :    无			                                            */
typedef void    (*PFUNC_STANDBYNOTIFY)();
typedef struct
{
	PLOG_INIT                m_pLog_Init;       //日志库初始化函数指针
	PLOG_RLS                 m_pLog_Rls;        //日志库释放函数指针
	PLOG_GETCFG              m_pLog_GetCfg;     //获取日志模块配置信息函数指针
	PLOG_SETCFG              m_pLog_SetCfg;     //设置日志模块配置信息函数指针
	PLOG_SETMSG              m_pLog_SetMsg;     //往Log模块设置参数
	
	PFUNC_IS_LOG_OUT         m_pLog_IsOut;      //普通日志是否输出函数指针
	PFUNC_IS_COM_LOG_OUT     m_pLog_IsComOut;   //ITPCOM日志是否输出函数指针
	PFUNC_LOG_OUT_STR        m_pLog_OutStr;     //字符串日志输出函数指针
	PFUNC_LOG_OUT            m_pLog_Out;        //二进制日志输出函数指针 

    DJ_U8*                   m_pRef[4];         //reserve
    
}ITP_LOG_CALLBACK, *PITP_LOG_CALLBACK;


/************************************************************************/

//回调接口函数指针
typedef struct
{
	PFUNC_GETSELFUNITID        m_pGetSelfUnitId;
	PFUNC_GETMODSTATE          m_pGetModState;
	PFUNC_SENDPACK             m_pSendPack;
	PFUNC_SENDPACKEX           m_pSendPackEx;
	PFUNC_GETMASTER		       m_pGetMaster;
	PFUNC_RESENDPACK           m_pReSendPack;
	PFUNC_GETMODIPPORT         m_pGetModIpPort;
	PFUNC_GETMODINIFILE        m_pGetModIniFile;
	PFUNC_GETMODUNITID         m_pGetModUnitID;
	PFUNC_GETMODALLUNITID      m_pGetModAllUnitID;
	PFUNC_STANDBYNOTIFY	       m_pStandbyNotify;
	PFUNC_IS_LOG_OUT           m_pIsLogOut;
	PFUNC_IS_COM_LOG_OUT       m_pIsCOMLogOut;
	PFUNC_LOG_OUT              m_pLogOut;
	PFUNC_LOG_OUT_STR          m_pLogOutStr;
	PFUNC_LOGMOD_UPDATE_CFG    m_pLogUpateCfg;
	PFUNC_LOGMOD_UPDATE_CFG    m_pITPCOMLogUpateCfg;
	
	DJ_U8*                     m_pFuncRef[11];
	
}ITP_MOD_CALLBACK,*PITP_MOD_CALLBACK;

extern ITP_MOD_CALLBACK      g_ITPCallBack;
extern ITP_LOG_CALLBACK      g_ITPLogCallBack;


/////////////////////////////////////////////////////////////////
//日志模块原始接口
#define   ITPLGInit          g_ITPLogCallBack.m_pLog_Init
#define   ITPLGRls           g_ITPLogCallBack.m_pLog_Rls
#define   ITPLGIsOut         g_ITPLogCallBack.m_pLog_IsOut
#define   ITPLGIsComOut      g_ITPLogCallBack.m_pLog_IsComOut
#define   ITPLGOutStr        g_ITPLogCallBack.m_pLog_OutStr
#define   ITPLGOut           g_ITPLogCallBack.m_pLog_Out
#define   ITPLGGetCfg        g_ITPLogCallBack.m_pLog_GetCfg
#define   ITPLGSetCfg        g_ITPLogCallBack.m_pLog_SetCfg
#define   ITPLGSetMsg        g_ITPLogCallBack.m_pLog_SetMsg

/////////////////////////////////////////////////////////////////
//回调接口
#define   GetSelfUnitId      g_ITPCallBack.m_pGetSelfUnitId
#define   GetModState        g_ITPCallBack.m_pGetModState
#define   SendPack           g_ITPCallBack.m_pSendPack
#define   SendPackEx       g_ITPCallBack.m_pSendPackEx
#define   GetMaster        g_ITPCallBack.m_pGetMaster
#define   ReSendPack         g_ITPCallBack.m_pReSendPack
#define   GetModIpPort       g_ITPCallBack.m_pGetModIpPort
#define   GetModIniFile      g_ITPCallBack.m_pGetModIniFile
#define   GetModUnitID       g_ITPCallBack.m_pGetModUnitID
#define   GetModAllUnitID    g_ITPCallBack.m_pGetModAllUnitID
#define	  OnStandbyNotify  g_ITPCallBack.m_pStandbyNotify
#define	  KGIsLogOut         g_ITPCallBack.m_pIsLogOut
#define	  KGIsComLogOut      g_ITPCallBack.m_pIsCOMLogOut
#define	  KGLogOut           g_ITPCallBack.m_pLogOut
#define	  KGLogOutStr        g_ITPCallBack.m_pLogOutStr

#endif
