#ifndef __ITP_SIGNAL_MONITOR_H__
#define __ITP_SIGNAL_MONITOR_H__

///////////////////////////////////////////////////////////////////////////////
enum ITP_SIGMonitor_EventType        // 信令监控事件定义
{	
	SMON_EVT_Call_Generate  =  0x01, // 呼叫发起
    SMON_EVT_Call_Connect   =  0x02, // 呼叫连接
	SMON_EVT_Call_Disconnect=  0x03, // 呼叫断开
	SMON_EVT_Call_Info      =  0x04, // 呼叫信息
	SMON_Evt_Gen_Signal_Info=  0x05, // 信令信息
	SMON_Evt_Raw_Signal_Info=  0x06, // 原始信息
};


enum ITP_SIGMonitor_Protocol         // 信令监控协议定义
{	
	SMON_Protocol_ISDN      = 0x01,  // ISDN信令
	SMON_Protocol_SS7       = 0x02,  // 七号信令
	SMON_Protocol_N64K      = 0x03,  // N64K
};


enum ITP_SIGMonitor_SI               // 业务表示语定义
{	
	SMON_SI_SCCP = 0x03,             // SCCP
    SMON_SI_TUP  = 0x04,             // TUP
	SMON_SI_ISUP = 0x05,             // ISUP
};


enum ITP_SIGMonitor_ISUP_MsgType     // 信令监控消息定义
{	
	SMON_ISUP_ACM = 0x06,		     // 地址全消息
	SMON_ISUP_ANM = 0x09,		     // 应答消息
	
	SMON_ISUP_CON = 0x07,		     // 接续消息
	
	SMON_ISUP_INF = 0x04,		     // 信息消息
	SMON_ISUP_IAM = 0x01,		     // 初始地址消息
	
	SMON_ISUP_REL = 0x0C,		     // 释放消息
	SMON_ISUP_RLC = 0x10,		     // 释放完成消息
	
	SMON_ISUP_SAM = 0x02,		     // 后续地址消息
	
	//
	SMON_ISUP_CPG = 0x2C,		     // 呼叫进展消息
	SMON_ISUP_CQR = 0x2B,		     // 电路群询问响应消息
	SMON_ISUP_GRA = 0x29,		     // 电路群复原证实消息
	SMON_ISUP_CFN = 0x2F,		     // 混淆消息
	
	SMON_ISUP_COT = 0x05,		     // 导通消息
	SMON_ISUP_FRJ = 0x21,		     // 性能拒绝消息
	
	SMON_ISUP_INR = 0x03,		     // 信息请求消息	
	
	SMON_ISUP_USR = 0x2D,		     // 用户至用户消息
	SMON_ISUP_FOT = 0x08,		     // 前向传递消息
	
	SMON_ISUP_RES = 0x0E,		     // 恢复消息
	SMON_ISUP_SUS = 0x0D,		     // 暂停消息
	
	SMON_ISUP_BLO = 0x13,		     // 闭塞消息
	SMON_ISUP_BLA = 0x15,		     // 闭塞证实消息
	SMON_ISUP_CCR = 0x11,		     // 导通检验请求消息
	SMON_ISUP_LPA = 0x24,		     // 环路确认消息
	SMON_ISUP_OLM = 0x30,		     // 过负荷消息
	SMON_ISUP_RSC = 0x12,		     // 电路复原消息
	SMON_ISUP_UBL = 0x14,		     // 解除闭塞消息
	SMON_ISUP_UBA = 0x16,		     // 解除闭塞证实消息
	SMON_ISUP_UCIC= 0x2E,		     // 未装备电路识别码消息
	
	SMON_ISUP_CGB = 0x18,		     // 电路群闭塞消息
	SMON_ISUP_CGBA= 0x1A,		     // 电路群闭塞证实消息
	SMON_ISUP_CGU = 0x19,		     // 电路群闭塞解除消息
	SMON_ISUP_CGUA= 0x1B,		     // 电路群闭塞解除证实消息
	
	SMON_ISUP_GRS = 0x17,		     // 电路群复原消息
	SMON_ISUP_CQM = 0x2A,		     // 电路群询问消息
	
	SMON_ISUP_FAA = 0x20,		     // 性能接受消息
	SMON_ISUP_FAR = 0x1F,		     // 性能请求消息
	
	SMON_ISUP_PAM = 0x28,		     // 传递消息
	
	SMON_ISUP_UPT = 0x34,		     // 用户部分测试
	SMON_ISUP_UPA = 0x35,		     // 用户部分可利用
	
	SMON_ISUP_FAC = 0x33,		     // 性能消息
	SMON_ISUP_NRM = 0x32,		     // 网络资源管理
	SMON_ISUP_IDR = 0x36,		     // 识别请求
	SMON_ISUP_IRS = 0x37,		     // 识别响应
	SMON_ISUP_SGM = 0x38,		     // 分段
	
	SMON_ISUP_CRG = 0x31,		     // 计费信息
	SMON_ISUP_OPR = 0xFE,		     // 话务员消息
	SMON_ISUP_MPM = 0xFD,		     // 计次脉冲
	SMON_ISUP_CCL = 0xFC,		     // 主叫挂机
};


enum ITP_SIGMonitor_TUP_MsgType      // 信令监控消息定义
{	
	SMON_TUP_IAM = 0x11,             // 初始地址消息
	SMON_TUP_IAI = 0x21,             // 带有附加信息的初始地址消息
	SMON_TUP_SAM = 0x31,             // 后续地址消息
	SMON_TUP_SAO = 0x41,             // 带有一个地址信号的后续地址消息	
	
	SMON_TUP_ACM = 0x14,             // 地址收全消息
	
	SMON_TUP_SEC = 0x15,             // 交换设备拥塞信号
	SMON_TUP_CGC = 0x25,             // 电路群拥塞信号
	SMON_TUP_NNC = 0x35,             // 国家网拥塞信号
	SMON_TUP_ADI = 0x45,             // 地址不全信号
	SMON_TUP_CFL = 0x55,             // 呼叫故障信号
	SMON_TUP_SSB = 0x65,             // 用户忙信号
	SMON_TUP_UNN = 0x75,             // 空号
	SMON_TUP_LOS = 0x85,             // 线路不工作信号
	SMON_TUP_SST = 0x95,             // 发送专用信息音信号
	SMON_TUP_ACB = 0xA5,             // 接入拒绝信号
	SMON_TUP_DPN = 0xB5,             // 不提供数字通路信号
	SMON_TUP_MPR = 0xC5,             // 误播中继前缀
	
	SMON_TUP_SLB = 0x1E,             // 用户市忙信号
	SMON_TUP_STB = 0x2E,             // 用户长忙信号
	
	SMON_TUP_ANU = 0x06,             // 应答信号，计费未说明
	SMON_TUP_ANC = 0x16,             // 应答信号、收费
	SMON_TUP_ANN = 0x26,             // 应答信号、免费
	SMON_TUP_CBK = 0x36,             // 挂机信号
	SMON_TUP_CLF = 0x46,             // 拆线信号	
	
	SMON_TUP_RLG = 0x17,             // 释放监护信号	
	
	SMON_TUP_GSM = 0x12,             // 一般前向建立信息消息
	
	//
	SMON_TUP_COT = 0x32,             // 导通信号
	SMON_TUP_CCF = 0x42,             // 导通故障信号
		
	SMON_TUP_GRQ = 0x13,             // 一般请求消息			
	
	SMON_TUP_CHG = 0x24,             // 计费消息
		
	SMON_TUP_EUM = 0xF5,             // 扩充的后向建立不成功消息
			
	SMON_TUP_RAN = 0x56,             // 再应答信号
	SMON_TUP_FOT = 0x66,             // 前向转移信号
	SMON_TUP_CCL = 0x76,             // 主叫用户挂机信号
	
	SMON_TUP_BLO = 0x27,             // 闭塞信号
	SMON_TUP_BLA = 0x37,             // 闭塞证实信号
	SMON_TUP_UBL = 0x47,             // 解除闭塞信号
	SMON_TUP_UBA = 0x57,             // 解除闭塞证实信号
	SMON_TUP_CCR = 0x67,             // 请求导通检验信号
	SMON_TUP_RSC = 0x77,             // 电路复原信号
		
	SMON_TUP_MGB = 0x18,             // 面向维护的群闭塞消息
	SMON_TUP_MBA = 0x28,             // 面向维护的群闭塞证实消息
	SMON_TUP_MGU = 0x38,             // 面向维护的群解除闭塞消息
	SMON_TUP_MUA = 0x48,             // 面向维护的群解除闭塞证实消息
	SMON_TUP_HGB = 0x58,             // 面向硬件故障的群闭塞消息
	SMON_TUP_HBA = 0x68,             // 面向硬件故障的群闭塞证实消息
	SMON_TUP_HGU = 0x78,             // 面向硬件故障的群解除闭塞消息
	SMON_TUP_HUA = 0x88,             // 面向硬件故障的群解除闭塞证实消息
	SMON_TUP_GRS = 0x98,             // 电路群复原消息
	SMON_TUP_GRA = 0xA8,             // 群复原证实消息
	SMON_TUP_SGB = 0xB8,             // 软件产生的群闭塞消息
	SMON_TUP_SBA = 0xC8,             // 软件产生的群闭塞证实消息
	SMON_TUP_SGU = 0xD8,             // 软件产生的群解除闭塞消息
	SMON_TUP_SUA = 0xE8,             // 软件产生的群解除闭塞证实消息
		
	SMON_TUP_ACC = 0x1A,             // 自动拥塞控制信息消息
		
	SMON_TUP_MPM = 0x2C,             // 计次脉冲消息
		
	SMON_TUP_OPR = 0x1D,             // 话务员信号			
	
	SMON_TUP_MAL = 0x1F,             // 恶意呼叫追查信号
};


enum ITP_SIGMonitor_ISDN_MsgType     // 信令监控消息定义
{
	SMON_ISDN_Alerting        = 0x01,// 提醒
	SMON_ISDN_Call_Proceeding = 0x02,// 呼叫进程
	SMON_ISDN_Connect         = 0x07,// 连接
	SMON_ISDN_Connect_Ack     = 0x0F,// 连接证实
	SMON_ISDN_Progress        = 0x03,// 进展
	SMON_ISDN_Setup           = 0x05,// 建立
	SMON_ISDN_Setup_Ack       = 0x0D,// 建立证实
	
	SMON_ISDN_Resume          = 0x26,// 恢复
	SMON_ISDN_Resume_Ack      = 0x2E,// 恢复证实
	SMON_ISDN_Resume_Reject   = 0x22,// 恢复拒绝
	SMON_ISDN_Suspend         = 0x25,// 暂停
	SMON_ISDN_Suspend_Ack     = 0x2D,// 暂停证实
	SMON_ISDN_Suspend_Reject  = 0x21,// 暂停拒绝
	SMON_ISDN_User_Information= 0x20,// 用户信息
	
	SMON_ISDN_Disconnect      = 0x45,// 拆线
	SMON_ISDN_Release         = 0x4D,// 释放
	SMON_ISDN_Release_Complete= 0x5A,// 释放完成
	SMON_ISDN_Restart         = 0x46,// 重新启动
	SMON_ISDN_Restart_Ack     = 0x4E,// 重启证实
	
	SMON_ISDN_Segment         = 0x60,// 分段
	SMON_ISDN_Congestion_Ctrl = 0x79,// 拥塞控制
	SMON_ISDN_Information     = 0x7B,// 信息
	SMON_ISDN_Notify          = 0x6E,// 通知
	SMON_ISDN_Status          = 0x7D,// 状态
	SMON_ISDN_Status_Enquiry  = 0x75,// 状态询问
};


///////////////////////////////////////////////////////////////////////////////
#define SMON_Evt_Len_But_Raw_Data 128// 事件包除原始数据部分的长度

typedef struct                       // 返回的事件数据结构
{	
	DJ_U8   EventType;               // 事件类型
	DJ_U8   Protocol;                // 协议类型
	DJ_U8   SI;                      // 业务表示
	DJ_U8   MsgType;                 // 信令消息
	
	DJ_S8   Caller_ID[32];           // 主叫号码
	DJ_S8   Called_ID[32];           // 被叫号码
	DJ_S8   OriCalled[32];           // 原始被叫
	
	DJ_U8   DPC[3];                  // 目的点码
	DJ_U8   OPC[3];                  // 原端点码
	DJ_U8   Pcm;                     // CIC_Hig7
	DJ_U8   Chn;                     // CIC_Low5
	
	DJ_U8   ReleaseReason;           // 拆线原因
	DJ_U8   Reserved[14];            // 保留备用
	DJ_U8   Unit_ID;                 // 来源单元
	DJ_U8   Port_ID;                 // 来源端口
	DJ_U8   TS;                      // 来源时隙
	DJ_U16  DataLen;                 // 数据长度
	
	DJ_U8   RAWdata[2048];           // 原始数据
}SMON_EVENT, *PSMON_EVENT;

#endif
