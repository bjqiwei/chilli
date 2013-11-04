#ifndef _MISSCALL_H_
#define _MISSCALL_H_

#ifdef __cplusplus
extern "C" {
#endif

#define DJSSM_CALL_GENERATE			0x01	// 呼叫发起
#define DJSSM_CALL_CONNECT			0x02	// 通话建立
#define DJSSM_CALL_DISCONNECT		0x03	// 通话断开
#define DJSSM_CALL_INFO				0x04	// 呼叫信息
#define DJSSM_CALL_INFO_ACM			0x05	// 收到ACM消息
	
#define FORCE_MODE					0x01	// 强制重连

// TUP遇忙信号
#define CALLEE_SLB					0x1E	// 被叫市话忙	
#define CALLEE_SSB					0x65	// 被叫忙
#define CALLEE_STB					0x2E	// 被叫长话忙

#define CALLEE_LOS					0x85	// 线路退出服务
#define CALLEE_CGC					0x25	// 电路群拥塞
#define CALLEE_ADI					0x45	// 地址不全
#define CALLEE_SEC					0x15	// 交换设备拥塞
#define CALLEE_UNN					0x75	// 未分配号码信号
#define CALLEE_SST					0x95	// 特别信号音
#define CALLEE_EUM					0xF5	// 后向建立不成功（扩充）

// TUP拆线信号
#define CALLINF_CLF					0x46	// 前向拆线
#define CALLINF_CBK					0x36	// 后向拆线

// ISUP呼叫释放原因值
enum CAUSE_VALUE
{
	RSN_UNALLOCATED_NUMBER = 0x01,		//空号
	RSN_NORMAL_CALL_CLEARING = 0x10,	//正常的呼叫清除
	RSN_USER_BUSY = 0x11,				//用户忙
	RSN_NO_USER_RESPONDING = 0x12,		//无用户响应，超时没有收到ACM
	RSN_USER_ALERTING_NO_ANSWER = 0x13, //被叫无应答，超时未摘机
	RSN_CALL_REJECTED = 0x15,			//呼叫拒绝
	RSN_INCOMPLETE_NUMBER = 0x1c,		//不完整的号码
	RSN_NORMAL_NO_SET = 0x1f,			//正常，未规定
	RSN_NO_CIRCUIT_CHANNELAVAILABLE = 0x22, //无可用的电路
	RSN_REQUESTEDCIRCUIT_CHANNEL_NOTAVAILABLE = 0x2c, //请求的电路不可用
	RSN_RECOVERY_ON_TIME_EXPIRY = 0x66,	//定时器超时恢复

	RSN_LOCAL_RLC = 0x20,				//本地释放电路
	RSN_RECEIVE_RSC = 0x21,				//电路复原
};

#define ERR_DMSU_SOCKFAIL			1000//-1		// 创建到DMSU连接socket失败
#define ERR_DMSU_CONNECTFAIL		2000//-2		// 连接DMSU失败
#define ERR_DMSU_INITRPARSERFAIL	-3		// 初始化消息解析队列失败
#define ERR_DMSU_INITFRAGMENTFAIL	-4		// 初始化数据交换队列失败
#define ERR_DMSU_INITRECVFAIL		-5		// 初始化接收队列失败
#define ERR_DMSU_STARTRECVTFAIL		-6		// 启动接收线程失败
#define ERR_DMSU_STARTHEARTTFAIL	-7		// 启动心跳线程失败
#define ERR_DMSU_STARTPARSERTFAIL   -8		// 启动解析线程失败
#define ERR_DMSU_NOTEXISTS			-9		// 连接不存
#define ERR_DMSU_CONNECTIONOK		-10		// 当前连接正常
	
#define ERR_EVT_NODATA				-1		// 没有接收到数据
#define ERR_EVT_GETDATAFAIL			-2		// 获取数据失败
#define ERR_EVT_DATANOTENOUGH		-3		// 数据长度不足
#define ERR_EVT_NOTEXISTS			-4		// 连接不存在
#define ERR_EVT_DISCONNECT			-5		// 到DMSU的连接断开



typedef struct tagSockInfo
{
	char Addr[16];
	unsigned short Port;
	unsigned long BufSize;
	unsigned long RecvBufSize;
	unsigned char UnitID;
}tSockInfo, *ptSockInfo;

typedef struct tagMonEvt
{
	char caller_id[32];			// 主叫号码
	char callee_id[32];			// 被叫号码
	char original_callee_id[32];// 原被叫号码
	unsigned char Event;		// 事件指示码
	unsigned char LocalPcmID;	// 本地获得信令数据PCM号
	unsigned char pcm;			// 信令数据描述中继号
	unsigned char chn;			// 信令数据描述时隙号
	unsigned char Protocol;		// 协议类型
	unsigned char SubProtocol;	// 协议子类型 
	unsigned int ToneID;		// 保留字
	unsigned char ReleaseReason;// 拆线原因值
	unsigned char MsgType;		// 消息类型
	long DPC;
	long OPC; 	
	int DataLen;					 // 原始包长度
	unsigned char OriginalData[300]; // 原始包 CR20061116_01
}tMonEvt, *ptMonEvt;

/////////////////////////////////////////////////////////////////////////
// 系统状态信息 CR20061116_02
//

/////////////////////////////////////////////////////////////////////////
// 信息掩码
#define SYS_INFO_BUFFER				00		// 消息队列信息

/////////////////////////////////////////////////////////////////////////
// 出错提示
#define SYS_NOT_EXISTS				-1		// 指定的DMSU设备不存在
#define SYS_MAX_INFO_LEN			128		// 信息内容最大长度

/////////////////////////////////////////////////////////////////////////
// 结构定义
typedef struct tagSysBufInfo{
	unsigned char BuffID;
	int BufSize;
	int InUse;	
}tSysBufInfo, *ptSysBufInfo;

typedef struct tagSysState
{
	unsigned char sysID;						// 返回信息类属资源
	unsigned char infoLen;						// 信息长度
	unsigned char info[SYS_MAX_INFO_LEN];		// 信息内容
}tSysState, *ptSysState;

// end CR20061116_02

//////////////////////////////////////////////////////////////////////////// 
// 设置原始信令包传送方式  CR20061116_01

// 解析掩码
const unsigned char  PRO_TRANS		 = 0x00;	// 透传
const unsigned char  PRO_PARSER		 = 0x01;	// 解析
const unsigned char  PRO_BOTH		 = 0x02;	// 解析并传送

// 操作掩码
const unsigned char  PRO_ADD		 = 0x00;	// 添加
const unsigned char  PRO_REMOVE		 = 0x01;	// 移除
const unsigned char  PRO_MODIFY		 = 0x02;	// 修改

// 协议工作模式
typedef struct tagProtocolMode
{
	unsigned char Protocol;
	unsigned char WorkMode;
}tProtocolMode, *ptProtocolMode;

// END CR20061116_01

// CR20070830_001
typedef struct tagDMSU_LOG
{
	int LogType;
	long Param1;
}DMSU_LOG, *PDMSU_LOG;

void DJSSM_ExitSystem();
int DJSSM_InitSystem();
int DJSSM_CreateDMSUConnection(const tSockInfo &_sockinfo);
int DJSSM_CreateDMSUConnectoin_A(ptSockInfo _pSockInfo);
int DJSSM_GetEvent(unsigned char _ClienIndex, tMonEvt * const _moniEvt);
int DJSSM_ReConnectDMSU(int _Index, int _Mode = 0);

int DJSSM_GetSystemState(unsigned char _ClientIndex, unsigned char _infoMask, tSysState * const _sysState);// CR20061116_02
int DJSSM_CfgProtocol(unsigned char _ClientIndex, tProtocolMode * const _WorkMode, unsigned char op);// CR20061116_01
int DJSSM_CfgDMSULog(unsigned char _ClientIndex, DMSU_LOG _DMSULog);// CR20061116_01
#ifdef __cplusplus
}
#endif

#endif // #ifndef _MISSCALL_H_