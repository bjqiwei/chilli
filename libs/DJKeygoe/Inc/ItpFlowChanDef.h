//*****************************************************************************
//Copyright(c)  :  DONJIN CORPORTAION  All Rights Reserved                       
//FileName      :  ItpFlowChanDef.h
//Version       :  1.1                                                              
//Author        :  hewei                                                             
//DateTime      :  2005-07-20 15:00                                           
//Description  :   ITP流程执行模块头文件
//*****************************************************************************

#ifndef _ITPFLOWCHANDEF_H
#define _ITPFLOWCHANDEF_H

#include "ITPMsgPublic.h"
#include "ITPMainModCallBack.h"
#include "DJAcsDataDef.h"
 
#define ITP_MAX_MOD_TYPE_NUM           128    // 最大模块数
#define ITP_MAX_RELATEMOD_NUM          64     //最大关联模块数
#define ITP_MAX_SYSFUNC_NUM            32     //流程模块系统函数接口个数
#define ITP_MAX_DLLFUNC_NUM            4      //流程动态库接口函数个数
#define ITP_FLOW_MAX_FLOWNAME_LEN      40     //流程名最大长度          
#define ITP_FLOW_MAX_FLOWNAME_LEN      40     //流程名最大长度          
#define ITP_FLOW_MAX_INTERNAME_LEN     120    //用户自定义结构名最大长度


#ifndef MAX_PATH
#define MAX_PATH                       260
#endif

#define ITP_MAX_BINDRES_NUM            256     //流程通道绑定的最大资源个数
#define ITP_MAX_BINDTIMER_NUM          64     //流程通道绑定的最大定时器个数
#define ITP_FLOW_SHOW_INFO_SIZE        40     //用户显示状态缓存长度
#define ITP_FLOW_SHOW_INFO_NUM         3      //用户显示状态缓存个数

typedef struct _tagITP_FLOW_INFO ITP_FLOW_INFO,*PITP_FLOW_INFO;
typedef struct _tagITP_FLOW_CHAN ITP_FLOW_CHAN,*PITP_FLOW_CHAN;
typedef struct _tagITP_RES_CHAN  ITP_RES_CHAN, *PITP_RES_CHAN;
typedef struct _tagITP_FLOW_TIMER ITP_FLOW_TIMER, *PITP_FLOW_TIMER;

typedef DJ_S32 (*PTIMERFUNC)(DJ_S32 *);

enum ITP_RESOPEN_TYPE
{
    ITP_RESOPEN_FREE = 0,
    ITP_RESOPEN_LISTEN,
	ITP_RESOPEN_EXCLUDE,
};

//流程信息结构
typedef struct _tagITP_FLOW_INFO
{
    DJ_U32     m_u32FlowIndex;                          //流程标号
    DJ_S8      m_s8FlowName[ITP_FLOW_MAX_FLOWNAME_LEN]; //流程名
    DJ_S8      m_s8DllName[MAX_PATH];                   //动态库名	
    DJ_U32     m_u32StartState;                         //流程使能状态
    DJ_U32     m_u32LoadState;                          //流程加载状态
    DJ_U32*    m_hdlDllHandle;                          //流程动态库句柄
    DJ_U32*    m_hdlDllFunc[ITP_MAX_DLLFUNC_NUM];       //流程动态库接口函数指针
    DJ_U16     m_u16FlowChanNum;                        //该动态库对应的副本个数
	DJ_U16     m_u16Resrv;
    PITP_FLOW_CHAN *m_PITPFlowChan;                     //该动态库对应的副本表
}ITP_FLOW_INFO,*PITP_FLOW_INFO;

//流程通道结构
typedef struct _tagITP_FLOW_CHAN
{
    DJ_U16           m_u16FlowCurState;           //该流程通道当前状态
    DJ_U16           m_u16FlowInfoIndex;          //该流程通道对应流程类型标记
    DJ_U16           m_u16ChanIndex;              //该流程通道对应通道标记
    DJ_U16           m_u16StartState;             //启动标志,0:禁止;1:使能
	DJ_U16           m_u16BusyState;              //Busy标志,0:Free;1:Busy
    PITP_FLOW_INFO   m_PITPFlowInfo;              //流程信息
    DJ_U16           m_u16CurResNum;              //与此流程通道绑定的当前资源数量
    DJ_S16           m_s16ChanRetCode;            //流程通道返回状态值
	PITP_RES_CHAN    m_PITPResList[ITP_MAX_BINDRES_NUM];//与此流程通道绑定的资源句柄表
    DJ_U16           m_u16CurTimerNum;            //定时器个数
	DJ_U8            m_u8Master;
	DJ_S8            m_s8Rfu;
    PITP_FLOW_TIMER  m_PITPTimerChan[ITP_MAX_BINDTIMER_NUM];//定时器句柄
    DJ_U32*          m_PITPSysFunc[ITP_MAX_SYSFUNC_NUM];    //系统函数指针
    DJ_S8            m_s8InfoBuf[ITP_FLOW_SHOW_INFO_NUM][ITP_FLOW_SHOW_INFO_SIZE];//用户显示状态
	DJ_U8            m_u8RelateModInfo[ITP_MAX_MOD_TYPE_NUM]; //相关的模块
    PPKG_HEAD_STRUCT m_PITPEvtPack;                 //事件包指针
	PPKG_HEAD_STRUCT m_PITPInterEvt;                //流程内部事件包指针
    DJ_U8            *m_PITPFlowExtData;            //流程扩展数据
    DJ_U8            *m_PITPPublicBuf;              //公共使用缓存区
}ITP_FLOW_CHAN,*PITP_FLOW_CHAN;

//资源通道结构
typedef struct _tagITP_RES_CHAN
{
	DJ_U16	 m_u16ChanIndex;        //该通道的通道索引号
    DJ_U8	 m_u8UnitIndex;         //该通道所在模块单元索引号
	DJ_U8	 m_u8ModType;           //该通道所在模块的Module_Type
    DJ_U8	 m_u8FuncType;          //该通道所在模块的Func_Type        
    DJ_U8	 m_u8ChanType;          //该通道的类型，此项仅只有Interface_ch有用
    DJ_S16	 m_s16ChanGroup;        //该通道的组号
    DJ_U8	 m_u8BusyFlag;          //通道忙标志,0:空闲;1:独占打开;2:监听打开
    PITP_FLOW_CHAN  m_PITPFlowChan; //流程通道信息
	PITP_FLOW_CHAN  m_PITPListenFlowChan; //监听流程通道
    DJ_S8    m_s8InfoBuf[ITP_FLOW_SHOW_INFO_NUM][ITP_FLOW_SHOW_INFO_SIZE];//用户显示状态
    DJ_U8    m_u8RelateModInfo[ITP_MAX_RELATEMOD_NUM];     //与该资源相关的模块
	DJ_S8    m_s8MachineId;                                //机箱号ID 
	DJ_S8    m_s8Resrv[ITP_MAX_RELATEMOD_NUM-1];
}ITP_RES_CHAN,*PITP_RES_CHAN;

//定时器结构
typedef struct _tagITP_FLOW_TIMER
{	
    DJ_F64     m_u64Time;              //触发时间
    DJ_U32     m_u32Ticks;             //触发间隔
    DJ_U8      m_u8StartFlag;          //启动标志
	DJ_U8      m_u8Caller;             //调用者:用户DLL或者模块本身
	DJ_U8      m_Resrv[2];
    PITP_FLOW_CHAN  m_PITPFlowChan;   //流程通道指针
    PTIMERFUNC m_PITPTimerFunc;       //定时处理函数
	DJ_U16	   m_u16ChanIndex;        //后续三个定义是为了与流程转换部分的事件参数为资源句柄相一致
    DJ_U8	   m_u8UnitIndex;         //
	DJ_U8	   m_u8ModType;           //
}ITP_FLOW_TIMER,*PITP_FLOW_TIMER;

//流程内自部通讯事件结构
typedef struct
{
	PKG_HEAD_STRUCT  m_PkgHead;                                 //事件包头
	CallID_t         m_SrcCallID;                               //源流程
	CallID_t         m_destCallID;                              //目的流程
	DJ_U32           m_u32CmdType;                              //自定义命令类型
	DJ_U32           m_u32InterNameLen;                         //用户结构名长度
	DJ_S8            m_s8InterName[ITP_FLOW_MAX_INTERNAME_LEN]; //用户结构名
	DJ_U32           m_u32InterDataSize;                        //用户自定义结构大小
}FLOW_INTERDATA_HEAD,*PFLOW_INTERDATA_HEAD;

#endif
