//*****************************************************************************
//Copyright(c)  :  DONJIN CORPORTAION  All Rights Reserved                       
//FileName      :  ITPMsgPublic.h                                                              
//Version       :  1.1                                                              
//Author        :  兰骏                                                             
//DateTime      :  2005-06-30 15:00                                           
//Description  :   ITP系统公共消息和消息包数据结构定义单元(需要和其他进程进行通讯)                                                               
//*****************************************************************************
//*****************************************************************************
//Version       :  1.1.1
//mender        :  兰骏
//DateTime      :  2005-10-28 09:00  
//Description  :   增加ITP系统界面和其他模块的消息包                                                             
//*****************************************************************************
//*****************************************************************************
//Version       :  1.1.2
//mender        :  兰骏
//DateTime      :  2005-11-04 11:00  
//Description  :   增加ITP通讯消息包头特殊字段的定义                                                          
//*****************************************************************************



#ifndef _ITPMSGPUBLIC_H
#define _ITPMSGPUBLIC_H


#include "ITPDataDefine.h"

//通讯包特殊字段的定义
#define PKG_EXTEND_NORMAL     0x00
#define PKG_EXTEND_ERROR      0x01
#define PKG_EXTEND_CONFIG     0x02
#define PKG_EXTEND_INTERFACE  0x03
// 用于双机备份时区分包的发送方向
#define PKG_EXTEND_UPPER	  0x04		// 上级模块包
#define PKG_EXTEND_LOWER	  0x05		// 下级模块包
//通讯消息包头

typedef struct
{
	DJ_U8	m_u8PkgFlag;	// 包标志: 0xa5,0x5a
	DJ_U8	m_u8PkgExtend;	// 包扩展位
	
	DJ_U16	m_u16DataLen;	//不定长数据长度

    //GUID的组成部分
	struct ITP_GUID_tag
	{
	    DJ_U8   m_u8ModuleType;  //模块类型
	    DJ_U8   m_u8MainFuncId;  //主功能ID      
	    DJ_U8   m_u8SubFuncId;   //子功能ID
	    DJ_U8   m_u8UnitId;      //单元ID 
	    DJ_U16  m_u16ChanId;     //通道ID
	}ITP_GUID;

	DJ_U16 m_u16Reserve;     //保留字段

}PKG_HEAD_STRUCT, *PPKG_HEAD_STRUCT;

#define PKG_HEAD_LEN  sizeof(PKG_HEAD_STRUCT)

enum PACKAGE_TYPE
{
	PKG_CMD = 0x5A,         // 命令数据包
	PKG_EVT = 0xA5          // 事件数据包
};

//************配置管理模块消息包*****************


//模块状态定义
/*说明:
模块状态由一个DJ_U16类型定义，例如DJ_U16 u16ModuleStates
其中bit0 = 1,表示模块已经初始化, bit0 = 0 表示模块未初始化或已释放
其中bit1 = 1,表示模块已经启动  , bit1 = 0 表示模块已经停止
其中bit2 = 1,表示模块全部关联  , bit2 = 0 表示模块还有部分或全部未关联
其中bit3 = 1,表示模块已被监视  , bit3 = 0 表示模块未被监视
其中bit4 = 1,表示模块已经连接  , bit4 = 0 表示模块断开连接
其中bit5 = 1,表示模块正在停止  , 
其中bit6 = 1,表示模块正在运行  , bit6 = 0,表示模块没有运行  , 
其他9个bit位暂时没有用到

*/

#define MODULE_INIT     0x01    //模块已初始化
#define MODULE_START    0x02    //模块已启动
#define MODULE_RELATE   0x04    //模块已全部被其上级模块关联
#define MODULE_MONITOR  0x08    //模块已被监视
#define MODULE_CONNECT  0x10    //模块已连接
#define MODULE_STOPPING 0x20    //模块正在停止
#define MODULE_ISTUNING 0x40    //正在运行模块
#define MODULE_SETSTANDBY 0x80    //需要设置主从模块

enum
{
	ITP_REPORT_MODSTATE_NORMAL    = 0x0,
	ITP_REPORT_MODSTATE_COMMBAD   = 0x1,
};

//心跳包数据
typedef struct 
{
	DJ_U32	m_u32time;
	DJ_U32	m_u32date;
	DJ_U16  m_u16ModuleStates;
	DJ_U8   m_u8HotState;
	DJ_U8   m_u8HotWorkState;
}ITP_HEART_TIME,*PITP_HEART_TIME;

//传送给DSP的主从信息

#define MAX_IP_NUM 5

typedef struct
{
	DJ_U8    m_u8IPNum;                          //IP 数目
	DJ_U8    m_u8Reverse[3];      
	DJ_U32   m_u32IPAddress[MAX_IP_NUM];      //主模块的IP组
}ITP_DSP_HOTSTANDBY_INFO, *PITP_DSP_HOTSTANDBY_INFO;


//从备份config server向主备份config server发送模块信息结构
typedef struct
{
    DJ_U8        m_u8ModuleType;     //模块类型
	DJ_U8        m_u8UnitID;         //模块的单元ID
	DJ_U8        m_u8Reverse[2];
	
    DJ_U32       m_u32IPAddress;
	DJ_U32       m_u32Port;
}CONFIG_MODULE_STRUCT,*PCONFIG_MODULE_STRUCT;


//主备份config server向模块发送切换消息
typedef struct
{
	DJ_U8       m_u8HOTState;    //设置对方的主从, 0 从模块 ，1 主模块
	DJ_U8       m_u8RetVal;      //设置是否成功  1 失败  1 成功
	DJ_U8       m_u8HotWorkState; //本机机器工作状态
    DJ_U8       m_u8Reverse;
}CONFIG_HOTSTANDBY_STRUCT,*PCONFIG_HOTSTANDBY_STRUCT;


typedef struct 
{
	DJ_U8  m_u8ExceptionType;	//模块异常类型  0：通讯异常，1：内部逻辑异常
	DJ_U8  m_u8ModuleType;		//断开模块类型
	DJ_U8  m_u8UnitID;			//断开模块ID
	DJ_U32 m_u32IPAddress;		//断开模块IP

}ITP_MODULE_EXCEPTION,*PITP_MODULE_EXCEPTION;

typedef struct
{
	DJ_U16       m_u16ModState;   //模块异常类型  0：无异常，1：通讯异常，2：内部逻辑异常
	DJ_U8        m_u8ModuleType;   //断开模块类型
	DJ_U8        m_u8UnitID;       //断开模块ID
	DJ_U32       m_u32IPAddress;   //断开模块IP
}ITP_MODSTATE_REPORT,*PITP_MODSTATE_REPORT;

//关联模块数据
//系统关联信息(关联模块信息)

typedef struct
{
	DJ_U8	m_u8ModuleType;			//模块类型
    DJ_U8   m_u8UnitID;				//模块单元ID
	DJ_U16  m_u16Port;				//模块连接的端口号
    DJ_U32  m_u32IPAddress;			//模块IP地址
}ITP_MODULE_ADDR,*PITP_MODULE_ADDR;


typedef struct
{
	DJ_U8	m_u8ModuleType;			//模块类型
    DJ_U8   m_u8UnitID;				//模块单元ID
	DJ_U16  m_u16Port;				//模块连接的端口号
    DJ_U32  m_u32IPAddress;			//模块IP地址
	DJ_U32  m_u32RelateFlag;        //连接方向
}ITP_MODULE_RELATE_ADDR,*PITP_MODULE_RELATE_ADDR;

typedef struct
{
	DJ_S8         m_s8Username[32]; // 授权用户
	DJ_S8         m_s8Password[32]; // 授权密码	
}ITP_MOD_VALIDITY_DATA,*PITP_MOD_VALIDITY_DATA;

//监控模块数据包
typedef struct
{
	DJ_U8	m_u8ModuleType;      //模块类型
    DJ_U8   m_u8UnitID;          //模块单元ID
	DJ_U16  m_u16ChanID;         //模块通道号
	DJ_U16	m_u16DebugLevel;     //模块监控级别
    DJ_U16  m_u16UdpPort;        //模块连接的UDP端口号
    DJ_U32  m_u32IPAddress;      //模块IP地址
	DJ_U32	m_u32Reserved;       //保留字段
}ITP_MONITOR_ADDR,*PITP_MONITOR_ADDR;

#define MAX_MACADDR_STR_LEN     0x14     //网卡地址字符串长度最大值
#define MAX_MODULENAME_STR_LEN	0x10     //模块名字符串长度最大值
#define MAX_ERRMSG_LEN          0x60     //错误信息字符串长度最大值

//界面和配置管理之间的消息包
typedef struct
{
    DJ_U8       m_u8ModuleType;       //模块类型
    DJ_U8       m_u8UnitID;           //单元ID
    DJ_U8		m_u8IsEnable;         //是否使能模块 0:不使能; 1:使能
    DJ_U8       m_u8DSPType;          //DSP类型
    DJ_U16      m_u16ModuleStates;    //模块状态
    DJ_S8       m_s8ModuleName[MAX_MODULENAME_STR_LEN]; //模块名
    DJ_S8       m_s8pMACAddress[MAX_MACADDR_STR_LEN];  //网卡地址，非DSP为全0
    DJ_U32      m_u32Version;         //模块版本名
    DJ_U32      m_u32IPAddress;       //IP地址
    DJ_U32      m_u32Port;            //服务端口
	DJ_U32      m_u32Param;           //保留参数
}ITP_MODULE_STRUCT,*PITP_MODULE_STRUCT;

//错误包数据
typedef struct
{
    DJ_S32      m_s32ErrorCode;
    DJ_S8       m_s8pErrMsg[MAX_ERRMSG_LEN];
}ITP_ERROR_STRUCT,*PITP_ERROR_STRUCT;

//配置管理发送给VOIP模块，No2IP配置成功通知消息
typedef struct
{
    DJ_U8       m_u8ExcuteResult;
	DJ_U8       m_u8Reserve[7];
	
}ITP_ADDIP_OK_NOTIFY_STRUCT, *PITP_ADDIP_OK_NOTIFY_STRUCT;

//配置管理发送给FLOW模块，告知备机已经正常工作的通知消息
typedef struct
{
    DJ_U8       m_u8WorkSate;            //0:工作异常; 1: 工作正常
	DJ_U8       m_u8Reserve[7];          //保留
	
}ITP_SLAVE_WORK_NOTIFY_STRUCT, *PITP_SLAVE_WORK_NOTIFY_STRUCT;


/* new snmp content - add by liangyu 20110706 - begin */
//**************************************
//ITP配置管理模块获取SNMP内容的消息包

//读通道状态结果（cfgSrv和流程）
typedef struct
{
	DJ_U16 m_u8UnitID;				//单元ID
	DJ_U16 m_uReserved;				//保留
	DJ_U32 m_u16State[128];			//DSP的所有通道状态
	DJ_U8 m_u8DeviceSubType[128];	//DSP的设备子类型
}ITP_CH_STATE_RESULT,*PITP_CH_STATE_RESULT;

//读Q931状态结果（cfgSrv和Q931）
typedef struct
{
	DJ_U16 m_u8UnitID;				//单元ID
	DJ_U16 m_u8PcmNum;				//PCM号
	DJ_U8 m_u8LinkState[4];			//连接状态,参照DEF文件
	DJ_U8 m_u8RestartFlag[4];		//重连标志
}ITP_Q931_STATE_RESULT,*PITP_Q931_STATE_RESULT;

//主机状态结果（cfgSrv和proxy）
typedef struct
{
	DJ_U32 m_u32CpuIdle[8];			//空闲CPU
	DJ_U32 m_u32MemFree;			//空闲内存
	DJ_U32 m_u32SwapFree;			//空闲交换
	DJ_U32 m_u32HDFree;				//空闲硬盘
}ITP_PC_STATE_RESULT,*PITP_PC_STATE_RESULT;

//mainmod下级连接关系结果（cfgSrv和mainmod）
typedef struct
{
	DJ_U8	m_u8ModuleType;			//模块类型
    DJ_U8   m_u8UnitID;				//模块单元ID
	DJ_U8	m_u8RelateIndex;		//模块的关联号,0-255
	DJ_U8	m_u8RelateState;		//连接状态,0:正常,1:断开
}ITP_MAINMOD_DOWNRELATE_RESULT,*PITP_MAINMOD_DOWNRELATE_RESULT;
/* new snmp content - add by liangyu 20110706 - end */

//**************************************
//ITP配置界面和其他模块的消息包


//根节点标识
#define ITP_ROOT_NODE      0x01

//节点类型，如果无此节点，则返回NODE_NONE
#define NODE_NONE       0x00
#define NODE_PARENT     0x01     //分支配置
#define NODE_RDONLY     0x02     //只读配置
#define NODE_RDWR       0x03     //可读写配置
#define NODE_SHOWONLY   0x04     //只读列表配置
#define NODE_RDWR_TABLE 0x05     //可读写列表配置 

//节点定义信息
typedef struct
{
	DJ_U8       m_u8NodeType;
	DJ_S8       m_s8ConfigName[31];
	DJ_S8       m_s8ConfigFileName[32];
	DJ_S32      m_s32NodeMsgCode;
    DJ_S32      m_s32ConfigNum;  
}ITP_INTERFACE_NODE_DATA,*PITP_INTERFACE_NODE_DATA;


//子节点标识列表
typedef struct
{
	DJ_U8       m_u8NodeType;
	DJ_S8       m_s8ConfigName[31];
	DJ_S32      m_s32NodeMsgCode;
}ITP_INTERFACE_SUBNODE_DATA,*PITP_INTERFACE_SUBNODE_DATA;


//读写节点数据
typedef struct
{
	DJ_S32      m_s32IsWriteini;
	DJ_S32      m_s32NodeMsgCode;
	DJ_U16      m_u16FisrtData;
	DJ_U16      m_u16DataNum;
}ITP_INTERFACE_DONE_DATA,*PITP_INTERFACE_DONE_DATA;


//写节点数据结果
typedef struct
{
	DJ_S32      m_s32NodeMsgCode;
	DJ_S32      m_s32RetCode;
}ITP_INTERFACE_WRDATA_MSG,*PITP_INTERFACE_WRDATA_MSG;

//读节点操作结果
typedef struct
{
	DJ_U8       m_u8NodeType;
	DJ_S8       m_s8ConfigFileName[31];
	DJ_S32      m_s32NodeMsgCode;
	DJ_U16      m_u16FisrtData;
	DJ_U16      m_u16DataNum;
}ITP_INTERFACE_RDATA_MSG,*PITP_INTERFACE_RDATA_MSG;
//**************************************


////ITP配置界面和DSP模块进行固件更新的消息包

#define ERASE_PASSWORD 0x87654321    //DSP FLASH擦除密码
#define MAX_DATA_BLOCK_LENGTH  4000  //写入FLASH数据的最大长度

//读FLASH操作
typedef struct
{
    DJ_U32 m_u32AddrOffset;
	DJ_U32 m_u32ByteNum;
}ITP_FLASH_READ,*PITP_FLASH_READ;

//写FLASH操作
typedef struct
{
    DJ_U32 m_u32AddrOffset;
	DJ_U32 m_u32ByteNum;
	DJ_U8  m_u8pData[MAX_DATA_BLOCK_LENGTH];
}ITP_FLASH_WRITE,*PITP_FLASH_WRITE;

//读FLASH操作结果
typedef struct
{
	DJ_U32 m_u32DataLen;
	DJ_U8  m_u8pData[MAX_DATA_BLOCK_LENGTH];
}ITP_FLASH_READ_MSG,*PITP_FLASH_READ_MSG;

//写FLASH操作结果
typedef struct
{
    DJ_U32 m_u32WriteStates;
	DJ_U32 m_u32CheckSum;
}ITP_FLASH_WRITE_MSG,*PITP_FLASH_WRITE_MSG;
//*******************************************************


//******************媒体处理层消息包定义***********************************
#define   MSG_MEDIA						0x3000

#define   MSG_MEDIA_DEV					MSG_MEDIA + 0x100
#define   MSG_MEDIA_DEV_OPEN			MSG_MEDIA_DEV + 0x001
#define   MSG_MEDIA_DEV_CLOSE			MSG_MEDIA_DEV + 0x002
#define   MSG_MEDIA_DEV_STOP			MSG_MEDIA_DEV + 0x003

#define   MSG_MEDIA_PLAYREC				MSG_MEDIA_DEV + 0x100
#define   MSG_MEDIA_PLAYREC_PLAY		0x001
#define   MSG_MEDIA_PLAYREC_RECORD		0x002

#define   MSG_MEDIA_UT					MSG_MEDIA_PLAYREC + 0x100

#define   MSG_MEDIA_FSK					MSG_MEDIA_UT + 0x100

#define   MSG_MEDIA_EC					MSG_MEDIA_FSK + 0x100

#define   MSG_MEDIA_DTMF				MSG_MEDIA_EC + 0x100

#define   MSG_MEDIA_CA					MSG_MEDIA_DTMF + 0x100

#define   MSG_MEDIA_DIAL				MSG_MEDIA_CA + 0x100

#define   MSG_MEDIA_PARM				MSG_MEDIA_DIAL + 0x100

#define   MSG_MEDIA_CONF				MSG_MEDIA_PARM + 0x100

#define   MSG_MEDIA_MS					MSG_MEDIA_CONF + 0x100
#define   MSG_MEDIA_MS_SEND				MSG_MEDIA_MS + 0x001
#define   MSG_MEDIA_MS_RECV				MSG_MEDIA_MS + 0x002
#define   MSG_MEDIA_MS_VLDRSC			MSG_MEDIA_MS + 0x003



#define   MSG_MEDIA_END               0x3FFF
//**************************************************************************

//**************************************




//**************************************



//消息处理函数
DJ_S32 ITP_Msg_GetDataLen(PPKG_HEAD_STRUCT pPkgHead);
DJ_U8 *ITP_Msg_GetData(PPKG_HEAD_STRUCT pPkgHead);
DJ_S32 ITP_Msg_Init(PPKG_HEAD_STRUCT *ppPkgHead, DJ_S32 s32DataLen);
DJ_Void ITP_Msg_Release(PPKG_HEAD_STRUCT *ppPkgHead);
DJ_S32 ITP_Msg_AttachData(PPKG_HEAD_STRUCT *ppPkgHead,DJ_U8 *u8pData, DJ_S32 s32DataLen);
DJ_Void ITP_Msg_ClearData(PPKG_HEAD_STRUCT pPkgHead);



#endif
