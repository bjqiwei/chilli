/* Keygoe V3.0.0 */
using System;

namespace DJKeygoe
{
#region ITPDataDefine.h

    using DJ_U8 = Byte;
    using DJ_S8 = SByte;
    using DJ_U16 = UInt16;
    using DJ_S16 = Int16;
    using DJ_U32 = UInt32;
    using DJ_S32 = Int32;
    using DJ_U64 = UInt64;
    using DJ_S64 = Int64;
    //using DJ_Void = Void;
    //using DJ_Void* = Void*;
    //using DJ_F32 = float;
    //using DJ_F64 = double;
    using DJ_UI32 = UInt32;
    using DJ_SI32 = Int32;
    using RetCode_t = Int32;
    using ACSHandle_t = UInt32;
    using InvokeID_t = Int32;
    using LoginID_t = SByte;
    using EventClass_t = Int32;
    using EventType_t = Int32;
    using ACSConfirmation_t = Int32;
    using CallNum_t = SByte;
    using AcsCmdTye_t = Int32;

    using FlowType_t = Int32;
    using FlowChannel_t = Int32;
    using DeviceMain_t = Int16;
    using DeviceSub_t = Int16;
    using DeviceGroup_t = Int16;
    using ModuleID_t = SByte;
    using ChannelID_t = Int16;
    using ParmName_t = SByte;
    using ParmSize_t = Int32;
    using Version_t = Int32;
    //using Nulltype = DJ_Void*;
    using ACSUniversalFailure_t = Int32;
    using PlayCont_t = SByte;
    using FilePath_t = SByte;

    using Acs_Evt_State_t = Int32;
    using Acs_Evt_ErrCode_t = Int32;
    using Acs_MediaProc_Dtmf_t = SByte;
    using DJ_SOCKET = UInt32;

#endregion
    public unsafe class DJKeygoeIncludes
{
#region ITPDataDefine.h
    
    //数据基本类型定义
    public const bool TRUE = true;
    public const bool FALSE = false;
    public const int MAX_PATH = 260;
    public const int ACS_MAX_FILE_NAME_LEN = 128;
    public const int ACS_MAX_FILE_NUM = 8;
    
#endregion

#region DJAcsDevState.h

    public enum DEVICE_CALL_STATE
    {
        /////////////// 通用呼叫状态定义 //////////////////////////////////////////////////////////////////
        DEVICE_COMMON_STATE_START  = 0x0000, // 通用状态开始识别号: TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR
        DCS_FREE  = 0x0001, // 空闲状态(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)
        DCS_LOCAL_BLOCK  = 0x0002, // 本地阻塞(TUP,ISUP)
        DCS_REMOTE_BLOCK  = 0x0003, // 远端阻塞(TUP,ISUP)
        DCS_BLOCK  = 0x0004, // 本地和远端阻塞(ISUP)
        DCS_UNAVAILABLE  = 0x0005, // 不可用(TUP,ISUP,PRI)

        DCS_CALLOUT  = 0x0006, // 开始呼出(TUP,ISUP,PRI,VOIP,ANA_TRK)
        DCS_CALLIN =  0x0007, // 呼叫进入(TUP,ISUP,PRI,VOIP,ANA_TRK)
        DCS_ALERTING  = 0x0008, // 地址收齐对用户振铃等(TUP,ISUP)

        DCS_CONNECT  = 0x0009, // 连通(不分主被叫方式)(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)

        DCS_DISCONNECT =  0x000A, // 收到拆线(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)
        DCS_WAIT_FREE =  0x000B, // 对拆线的响应(TUP,ISUP,PRI,VOIP)

        /////////////// 模块/接口相关呼叫状态定义 /////////////////////////////////////////////////////////
        DEVICE_ESPECIAL_STATE_START =  0x0100,
        // ISUP模块/接口
        DES_ISUP_STATE_START = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_SS7_ISUP << 8), // ISUP特有状态 //
        DES_ISUP_LOCAL_SUSPEND = (DES_ISUP_STATE_START | 0x01), // 本地暂停
        DES_ISUP_REMOTE_SUSPEND = (DES_ISUP_STATE_START | 0x02), // 远端暂停
        DES_ISUP_LOCAL_RESUME = (DES_ISUP_STATE_START | 0x03), // 本地继续
        DES_ISUP_REMOTE_RESUME = (DES_ISUP_STATE_START | 0x04), // 远端继续
        DES_ISUP_RECV_INR = (DES_ISUP_STATE_START | 0x05), // 收到INR信令消息
        DES_ISUP_RECV_INF = (DES_ISUP_STATE_START | 0x06), // 收到INF信令消息
        DES_ISUP_RECV_CQR = (DES_ISUP_STATE_START | 0x07), // 收到CQR信令消息
        DES_ISUP_RECV_USR = (DES_ISUP_STATE_START | 0x08), // 收到USR信令消息
        DES_ISUP_RECV_CPG = (DES_ISUP_STATE_START | 0x09), // 收到CPG信令消息

        // TUP模块/接口
        DES_TUP_STATE_START = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_SS7_TUP << 8),  // TUP 特有状态 //
        DES_TUP_RECV_CCL = (DES_TUP_STATE_START | 0x01),  // 收到CCL信令消息
        DES_TUP_RECV_RAN = (DES_TUP_STATE_START | 0x02),  // 收到RAN信令消息
        DES_TUP_RECV_GSM = (DES_TUP_STATE_START | 0x03),  // 收到GSM信令消息

        DES_SS7_LINK_STATE_START = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_SS7_LINK << 8),    // 
        DES_SS7_LST_CONNECTING = (DES_SS7_LINK_STATE_START | 0x01),
        DES_SS7_LST_ACTIVE = (DES_SS7_LINK_STATE_START | 0x02),
        DES_SS7_LST_FAILED = (DES_SS7_LINK_STATE_START | 0x03),
        DES_SS7_LST_WAITCON = (DES_SS7_LINK_STATE_START | 0x04),
        DES_SS7_LST_SUSPEND = (DES_SS7_LINK_STATE_START | 0x05),

        DES_DSS1_STATE_START = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_DSS1 << 8),      // DSS1 特有状态 //
        DES_DSS1_RESTRAT = (DES_DSS1_STATE_START | 0x01),  // 应用开始的重启动状态
        DES_DSS1_WAIT_CONNECT_ACK = (DES_DSS1_STATE_START | 0x02),  // 等待连接证实
        DES_DSS1_CALLER_RECV_ALERT = (DES_DSS1_STATE_START | 0x03),  //去话方，已接收到提醒消息
        DES_DSS1_CALLER_RECV_CALLPROCESS = (DES_DSS1_STATE_START | 0x04),  //去话方，已接收到呼叫进程消息
        DES_DSS1_CALLER_RECV_SETUP_ACK = (DES_DSS1_STATE_START | 0x05),  //去话方，已接收到建立确认消息
        DES_DSS1_CALLER_WAIT_SETUP_ACK = (DES_DSS1_STATE_START | 0x06),  //去话方，等待建立确认

        // VoIP H.323协议特有状态
        DES_H323_STATE_START = 0x00010100,
        DES_H323_PROCEEDING = (DES_H323_STATE_START + 0x01), // proceeding
        DES_H323_TRANSFERING = (DES_H323_STATE_START + 0x02), // transfering
        DES_H323_ACF = (DES_H323_STATE_START + 0x03), // admission confirm (reserved)
        DES_H323_ARJ = (DES_H323_STATE_START + 0x04), // admission reject (reserved)
        DES_H323_INCOMPADDR = (DES_H323_STATE_START + 0x05), // incomplete address (reserved)
        DES_H323_WAITACK = (DES_H323_STATE_START + 0x06), // wait for address ack (reserved)

        // VoIP SIP协议特有状态
        DES_SIP_STATE_START = 0x00010200,
        DES_SIP_REDIRECTED = (DES_SIP_STATE_START + 0x01),  // call redirected
        DES_SIP_UNAUTH = (DES_SIP_STATE_START + 0x02),  // unauthenticated
        DES_SIP_ACCEPTED = (DES_SIP_STATE_START + 0x03),  // accepted (200 ok sent, waiting ack)
        DES_SIP_REMOTEACCEPT = (DES_SIP_STATE_START + 0x04),  // remote party accepted (reserved)
        DES_SIP_DISCONNECTING = (DES_SIP_STATE_START + 0x05),  // BYE sent
        DES_SIP_TERMINATED = (DES_SIP_STATE_START + 0x06),  // call finished
        DES_SIP_CANCELLED = (DES_SIP_STATE_START + 0x07),  // call cancelled
        DES_SIP_CANCELLING = (DES_SIP_STATE_START + 0x08),  // CANCEL sent
        DES_SIP_TIMEOUT = (DES_SIP_STATE_START + 0x09),  // timeout after 1xx response received (reserved)
        DES_SIP_MSGSENDFAIL = (DES_SIP_STATE_START + 0x0A),  // message send failed

        // ANALOG_TRUNK模块/接口
        DES_ANALOG_TRUNK_STATE_START = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK << 8),         // ANALOG_TRUNK 特有状态
        DES_ANALOG_TRUNK_OFFHOOK = (DES_ANALOG_TRUNK_STATE_START | 0x01),  // 呼出时,摘机
        DES_ANALOG_TRUNK_CALLOUT_FAILURE = (DES_ANALOG_TRUNK_STATE_START | 0x02),  // 呼出失败

        // ANALOG_USER模块/接口
        DES_ANALOG_USER_STATE_START = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER << 8),         // ANALOG_USER 特有状态
        DES_ANALOG_USER_RING = (DES_ANALOG_USER_STATE_START | 0x01),  // 振铃
        DES_ANALOG_USER_OFFHOOK = (DES_ANALOG_USER_STATE_START | 0x02),  // 呼出时,摘机

        DES_DIGITAL_REC_STATE_START = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_DIGITAL_REC << 8),         // 
        DES_DIGITAL_REC_VAD_VOC = (DES_DIGITAL_REC_STATE_START | 0x01),  // 
        DES_DIGITAL_REC_VAD_NON_VOC = (DES_DIGITAL_REC_STATE_START | 0x02),  //

        DES_FAX_START = (XMS_DEVMAIN_TYPE.XMS_DEVMAIN_FAX << 16),  // FAX 特有状态 //
        DES_FAX_OPEN = (DES_FAX_START),      //0  打开
        DES_FAX_CLOSE = (DES_FAX_START | 0x01), //1  关闭
        DES_FAX_RESET = (DES_FAX_START | 0x02), //2  复位

        DES_FAX_SENDFAX_RECVCMD = (DES_FAX_START | 0x10), // 发送传真
        DES_FAX_SENDFAX_START = (DES_FAX_START | 0x11), // 开始发送传真
        DES_FAX_SENDFAX_REMOTESPEC = (DES_FAX_START | 0x12), // 获取远端传真机性能
        DES_FAX_SENDFAX_LOCAL_FINISH = (DES_FAX_START | 0x13), // 设置本地传真格式
        DES_FAX_SENDFAX_SHAKEHAND_END = (DES_FAX_START | 0x14), // 握手信号结束
        DES_FAX_SENDFAX_RESOLVE_START = (DES_FAX_START | 0x15), // 传真数据分解开始
        DES_FAX_SENDFAX_REQUESTPAGEDATA = (DES_FAX_START | 0x16), // 请求页数据
        DES_FAX_SENDFAX_RESOLVE_RESULT = (DES_FAX_START | 0x17), // 页分解结果
        DES_FAX_SENDFAX_SENDDATA = (DES_FAX_START | 0x18), // 设置传真页，发送数据
        DES_FAX_SENDFAX_SENDFINISH = (DES_FAX_START | 0x19), // DSP传真过程结束
        DES_FAX_SENDFAX_USERSTOP = (DES_FAX_START | 0x1A), // 停止传送传真
        DES_FAX_SENDFAX_SENDEND = (DES_FAX_START | 0x1B), // 发送结束

        DES_FAX_RECVFAX_RECVCMD = (DES_FAX_START | 0x30), // 接收传真
        DES_FAX_RECVFAX_START = (DES_FAX_START | 0x31), // 开始接收传真
        DES_FAX_RECVFAX_HANDSHAKE = (DES_FAX_START | 0x32), // 握手结束
        DES_FAX_RECVFAX_RECVDATA_START = (DES_FAX_START | 0x33), // 接收传真数据
        DES_FAX_RECVFAX_BACKPAGESTATE = (DES_FAX_START | 0x34), // 页后状态
        DES_FAX_RECVFAX_RECVDATA_END = (DES_FAX_START | 0x35), // 传真数据接收结束
        DES_FAX_RECVFAX_RE_HANDSHAKE = (DES_FAX_START | 0x36), // 重握手
        DES_FAX_RECVFAX_COMPOSE_START = (DES_FAX_START | 0x37), // 合成开始
        DES_FAX_RECVFAX_COMPOSE_END = (DES_FAX_START | 0x38), // 合成结束
        DES_FAX_RECVFAX_RECVFINISH = (DES_FAX_START | 0x39), // DSP传真过程结束
        DES_FAX_RECVFAX_USERSTOP = (DES_FAX_START | 0x3A), // StopFax
        DES_FAX_RECVFAX_RECVEND = (DES_FAX_START | 0x3B), // 接收结束
    };

    public enum XMS_DEVICE_ATRUNK_CALLOUT_REASON
    {
        XMS_ATRUNK_CALLOUT_SUCC = 1, //
        XMS_ATRUNK_CALLOUT_WAIDAILTONE_TIMEOUT = 2, //
        XMS_ATRUNK_CALLOUT_RING_TIMEOUT = 3, //
        XMS_ATRUNK_CALLOUT_BUSY = 4, //
    };

    public enum XMS_DEVICE_CLEAR_CALL_CAUSE                         //挂机原因定义
    {
        XMS_CC_ReasonUnspecified = 0,   //原因未指定
        XMS_CC_UnallocatedNumber = 1,   //未分配的号码
        XMS_CC_NoRouteToSpecifiedTransitNetwork = 2,   //无路由到指定的转接网
        XMS_CC_NoRouteToDestination = 3,   //无路由到目的地
        XMS_CC_SendSpecialInformationTone = 4,   //发送专用信息音
        XMS_CC_MisdialledTrunkPrefix = 5,   //误拨长途字管
        XMS_CC_Preemption = 8,   //预占
        XMS_CC_PreemptionCircuitReservedForReuse = 9,   //预占一电路留作再用
        XMS_CC_NormalCallClearing = 16,  //正常的呼叫拆线
        XMS_CC_UserBusy = 17,  //用户忙
        XMS_CC_NoUserResponding = 18,  //用户未响应
        XMS_CC_UserAlertedNoAnswer = 19,  //用户未应答
        XMS_CC_SubscriberAbsent = 20,  //用户缺席
        XMS_CC_CallRejected = 21,  //呼叫拒收
        XMS_CC_NumberChanged = 22,  //号码改变
        XMS_CC_DestinationOutOfOrder = 27,  //目的地不可到达
        XMS_CC_InvalidNumberFormat = 28,  //无效的号码格式
        XMS_CC_FacilityRejected = 29,  //性能拒绝
        XMS_CC_NormalUnspecified = 31,  //正常－未指定
        XMS_CC_NoCircuitChannelAvailable = 34,  //无电路/通路工作
        XMS_CC_NetworkOutOfOrder = 38,  //网络未正常工作
        XMS_CC_TemporaryFailure = 41,  //临时故障
        XMS_CC_SwitchingEquipmentCongestion = 42,  //交换设备拥塞
        XMS_CC_AccessInformationDiscarded = 43,  //接入信息舍弃
        XMS_CC_RequestedCircuitChannelNotAvailable = 44,  //所请求的电路/通路不可用
        XMS_CC_PrecedenceCallBlocked = 46,  //优先呼叫闭塞
        XMS_CC_ResourceUnavailableUnspecified = 47,  //资源不可用－未指定
        XMS_CC_RequestedFacilityNotSubscribed = 50,  //所请求的性能未预定
        XMS_CC_OutgoingCallsBarredWithinCUG = 53,  //CUG中限制去呼叫
        XMS_CC_IncomingCallsBarredWithinCUG = 55,  //CUG中限制来呼叫
        XMS_CC_BearerCapabilityNotAuthorized = 57,  //承载能力无权
        XMS_CC_BearerCapabilityNotPresentlyAvailable = 58,  //承载能力目前不可用
        XMS_CC_ServiceOrOptionNotAvailableUnspecified = 63,  //业务/任选不可用－未指定
        XMS_CC_BearerCapabilityNotImplemented = 65,  //承载能力未实现
        XMS_CC_RequestedFacilityNotImplemented = 69,  //所请求的性能未实现
        XMS_CC_RestrictedDigitalInfoBearerIsAvailable = 70,  //只有受限的数字信息承载能力可用
        XMS_CC_ServiceOrOptionNotImplementedUnspecified = 79,  //业务或任选未实现－未指定
        XMS_CC_UserNotMemberOfCUG = 87,  //被叫用户不是CUG的成员
        XMS_CC_IncompatibleDestination = 88,  //不兼容的目的地
        XMS_CC_NonExistentCUG = 90,  //不存在的CUG
        XMS_CC_InvalidTransitNetworkSelection = 91,  //无效的转接网选择
        XMS_CC_InvalidMessageUnspecified = 95,  //无效的消息，未指定
        XMS_CC_MessageTypeNonExistenOrNotImplemented = 97,  //消息类型不存在或未实现
        XMS_CC_InfElementNonExistentOrNotImplemented = 99,  //参数不存在或未实现
        XMS_CC_RecoveryOnTimerExpiry = 102, //定时器终了时恢复
        XMS_CC_ParameterNonExistentOrNotImplement = 103, //参数不存在或未实现－传递
        XMS_CC_MessageWithUnrecognizedParameter = 110, //消息带有未被识别的参数－舍弃
        XMS_CC_ProtocolErrorUnspecified = 111, //协议错误，未指定
        XMS_CC_InterworkingUnspecified = 127, //互通，未指定

        //
        XMS_CC_DualSeizure = 129, // 同抢
        XMS_CC_RemoteBlock = 130, // 远端阻断
        XMS_CC_RemoteUnblock = 131, // 远端阻断消除
        XMS_CC_ResetCircuit = 132, //
        XMS_CC_LocalBusy = 133, //
    };

    public enum XMS_VOIP_ERRCODE
    {
        XMS_VOIP_ERR_OK = 0,	// command succeed with no error
        XMS_VOIP_ERR_INTERNAL = -1,	// internal error
        XMS_VOIP_ERR_SERVICE_DISABLED = -2,	// service disabled
        XMS_VOIP_ERR_INVALID_CALLID = -3,	// call id invalid
        XMS_VOIP_ERR_UNKNOWN_PROTOCOL = -4,	// call protocol unknown
        XMS_VOIP_ERR_CALL_ACTIVE = -5,	// call is active
        XMS_VOIP_ERR_CALL_FREE = -6,	// call is free
        XMS_VOIP_ERR_SLOT_NOACCESS = -7	// call slot no access
    };

    public enum XMS_VOIP_DISCONNECT_REASON
    {
        XMS_VOIP_DISCONNECT_UNKNOWN = 0x00,	// unknown reason
        XMS_VOIP_DISCONNECT_LOCAL = 0x01,	// local disconnect
        XMS_VOIP_DISCONNECT_REMOTE = 0x02,	// remote disconnect

        // H.323
        XMS_VOIP_DISCONNECT_H323_BUSY = 0x03,	// busy
        XMS_VOIP_DISCONNECT_H323_REJECT = 0x04,	// remote reject
        XMS_VOIP_DISCONNECT_H323_UNREACHABLE = 0x05,	// not reachable

        // SIP
        XMS_VOIP_DISCONNECT_SIP_LOCAL_REJECT = 0x06,	// local reject
        XMS_VOIP_DISCONNECT_SIP_REQUEST_FAILURE = 0x07,	// 4xx response rcvd (not 401 or 407)
        XMS_VOIP_DISCONNECT_SIP_SERVER_FAILURE = 0x08,	// 5xx response rcvd
        XMS_VOIP_DISCONNECT_SIP_GLOBAL_FAILURE = 0x09,	// 6xx response rcvd
        XMS_VOIP_DISCONNECT_SIP_LOCAL_FAILURE = 0x0A,	// local network failure
        XMS_VOIP_DISCONNECT_SIP_TIMEOUT = 0x0B	// time out
    };

    public enum XMS_VOC_DEV_STATE
    {
        XMS_VOC_DEV_STATE_FREE = 0x00,   // device in free state
        XMS_VOC_DEV_STATE_PLAYING = 0x01,   // device in playing state
        XMS_VOC_DEV_STATE_CSPPLAYING = 0x02,   // device in CSPplaying state
        XMS_VOC_DEV_STATE_RECORDING = 0x04,   // device in recording state
        XMS_VOC_DEV_STATE_CSPRECORDING = 0x08,   // device in CSPrecording state
        XMS_VOC_DEV_STATE_PLAYSTOPING = 0x10,   // device in playstoping state
        XMS_VOC_DEV_STATE_CSPPLAYSTOPING = 0x20,   // device in CSPplaystoping state
        XMS_VOC_DEV_STATE_RECORDSTOPING = 0x40,   // device in recordstoping state
        XMS_VOC_DEV_STATE_CSPRECORDSTOPING = 0x80,   // device in CSPrecordstoping state
        XMS_VOC_DEV_STATE_SENDINGIODATA = 0x100,  // device in SENDINGIODATA state
    };

#endregion

#region DJAcsISUPDef.h

    // ISUP信令消息定义(根据需要直接发送部分) /////////////////////////////////////
    public enum XMS_ISUP_Signalling_Message     // ISUP信令消息
    {	
	    ISUP_SM_BLO = 0x13,              // 阻断
    	
	    ISUP_SM_CGB = 0x18,              // 电路群阻断
	    ISUP_SM_CGU = 0x19,              // 电路群阻断消除	
	    ISUP_SM_CPG = 0x2C,              // 呼叫进展
	    ISUP_SM_CQM = 0x2A,              // 电路群问讯
    	
	    ISUP_SM_GRS = 0x17,              // 电路群复原
    	
	    ISUP_SM_INF = 0x04,              // 信息
	    ISUP_SM_INR = 0x03,              // 信息请求
    	
	    ISUP_SM_RES = 0x0E,              // 恢复	
	    ISUP_SM_RSC = 0x12,              // 电路复原
    	
	    ISUP_SM_SAM = 0x02,              // 后续地址
	    ISUP_SM_SGM = 0x38,              // 分段
	    ISUP_SM_SUS = 0x0D,              // 暂停
    	
	    ISUP_SM_UBL = 0x14,              // 阻断消除	
	    ISUP_SM_USR = 0x2D               // 用户至用户信息
    };

    // ISUP信令参数定义 ///////////////////////////////////////////////////////////
    public enum XMS_ISUP_Signalling_Parameter                     // ISUP信令参数
    {
	    ISUP_SP_AccessDeliveryInformation          = 0x2E, // 接入传递信息
	    ISUP_SP_AccessTransport                    = 0x03, // 接入传送
	    ISUP_SP_AutomaticCongestionLevel           = 0x27, // 自动拥塞级
	    ISUP_SP_BackwardCallIndicator              = 0x11, // 后向呼叫指示码
	    ISUP_SP_CallDiversionInformation           = 0x36, // 呼叫转移信息
	    ISUP_SP_CallHistoryInformation             = 0x2D, // 呼叫历史信息
	    ISUP_SP_CallReference                      = 0x01, // 呼叫参考
	    ISUP_SP_CalledPartNumber                   = 0x04, // 被叫用户号码
	    ISUP_SP_CallingPartNumber                  = 0x0A, // 主叫用户号码
	    ISUP_SP_CallingPartCategory                = 0x09, // 主叫用户类别
	    ISUP_SP_CauseIndicator                     = 0x12, // 原因指示码
	    ISUP_SP_CircuitGroupSupervisionIndicator   = 0x15, // 电路群监视消息类型指示码
	    ISUP_SP_CircuitStateIndicator              = 0x26, // 电路状态指示码
	    ISUP_SP_CUGInterlockCode                   = 0x1A, // 闭合用户群相关码
	    ISUP_SP_ConnectedNumber                    = 0x21, // 接续的号码
	    ISUP_SP_ConnectionRequest                  = 0x0D, // 接续请求
	    ISUP_SP_ContitnuityIndicator               = 0x10, // 导通指示码
	    ISUP_SP_EchoControlInformation             = 0x37, // 回声控制信息
	    ISUP_SP_EndOptionalParameter               = 0x00, // 任选参数尾指示码
	    ISUP_SP_EventInformation                   = 0x24, // 事件信息
	    ISUP_SP_FacilityIndicator                  = 0x18, // 功能指示码
	    ISUP_SP_ForwardCallIndicator               = 0x07, // 前向呼叫指示码
	    ISUP_SP_GenericDigit                       = 0x47, // 类属数字
	    ISUP_SP_GenericNotifyIndicator             = 0x2C, // 类属通知指示码
	    ISUP_SP_GenericNumber                      = 0x46, // 类属号码
	    ISUP_SP_GenericReference                   = 0x42, // 类属参考
	    ISUP_SP_InformationIndicator               = 0x0F, // 信息指示码
	    ISUP_SP_InformationRequestIndicator        = 0x0E, // 信息请求指示码
	    ISUP_SP_LocationNumber                     = 0x3F, // 定位号码
	    ISUP_SP_MCIDRequestIndicator               = 0x3B, // MCID请求指示码
	    ISUP_SP_MCIDResponseIndicator              = 0x3C, // MCID响应指示码
	    ISUP_SP_MsgCompatibilityInformation        = 0x38, // 消息兼容性信息
	    ISUP_SP_MlppPrecedence                     = 0x3A, // MLPP优先
	    ISUP_SP_NatureOfConnectionIndicator        = 0x06, // 接续性质指示码
	    ISUP_SP_NetworkSpecificFacility            = 0x2F, // 网络特定功能
	    ISUP_SP_OptBackwardCallIndicator           = 0x29, // 任选后向呼叫指示码
	    ISUP_SP_OptForwardCallIndicator            = 0x08, // 任选前向呼叫指示码
	    ISUP_SP_OriginalCalledNumber               = 0x28, // 原来的被叫号码
	    ISUP_SP_OriginationISCPointCode            = 0x2B, // 始发国际交换中心(ISC)的点码
	    ISUP_SP_ParamCompatibilityInformation      = 0x39, // 参数兼容性信息
	    ISUP_SP_PropagationDelayCounter            = 0x31, // 传播延迟计数器
	    ISUP_SP_RangeState                         = 0x16, // 范围和状态
	    ISUP_SP_RedirectingNumber                  = 0x0B, // 改发号码
	    ISUP_SP_RedirectionInformation             = 0x13, // 改发信息
	    ISUP_SP_RedirectionNumber                  = 0x0C, // 改发号码
	    ISUP_SP_RedirectionRestricition            = 0x40, // 改发号码限制参数
	    ISUP_SP_RemoteOperation                    = 0x32, // 远端操作
	    ISUP_SP_ServiceActivation                  = 0x33, // 业务激活
	    ISUP_SP_SignalPointCode                    = 0x1E, // 信令点编码
	    ISUP_SP_SubsequentNumber                   = 0x05, // 后续号码
	    ISUP_SP_SuspendResumeIndicator             = 0x22, // 暂停/恢复指示码
	    ISUP_SP_TransitNetworkSelection            = 0x23, // 汇接网络选择
	    ISUP_SP_TransmissionMediumRequirement      = 0x02, // 传输媒介要求
	    ISUP_SP_TransmissionMediumRequirementPrime = 0x3E, // 传输媒介要求(基本的)
	    ISUP_SP_TransmissionMediumUsed             = 0x35, // 使用的传输媒介
	    ISUP_SP_UserServiceInformation             = 0x1D, // 用户业务信息
	    ISUP_SP_UserServiceInformationPrime        = 0x30, // 用户业务信息(基本的)
	    ISUP_SP_UserTeleserviceInformation         = 0x34, // 用户终端业务信息
	    ISUP_SP_UserToUserIndicator                = 0x2A, // 用户至用户指示码
	    ISUP_SP_UserToUserInformation              = 0x20, // 用户至用户信息
	    ISUP_SP_MessageParameterAllParse           = 0xFF, // 解析的所有参数(最长255)
	    ISUP_SP_MessageParameterAllRaw             = 0xFE  // 原始的所有参数(最长255)
    };


    // ISUP信令参数数据结构定义 ///////////////////////////////////////////////////
    // 接入传送信息: ISUP_SP_AccessDeliveryInformation ////////////////////////////
    public struct ISUP_spAccessDeliveryInformation
    {
	    public DJ_U8 m_u8AccessDeliveryID;  // 接入传递指示码	
	    public fixed DJ_U8 m_u8Reserved[3];       // 对齐
    };


    // 接入传送: ISUP_SP_AccessTransport //////////////////////////////////////////
    public struct ISUP_spAccessTransport
    {
	    public fixed DJ_U8 m_u8AtpInformation[240];  // 信息单元按4.5/Q.931所述编码

	    public DJ_U8 m_u8AtpLen;               // 参数长度
	    public fixed DJ_U8 m_u8Reserved[3];          // 对齐
    };


    // 自动拥塞级: ISUP_SP_AutomaticCongestionLevel ///////////////////////////////
    public struct ISUP_spAutomaticCongestionLevel
    {	
	    public DJ_U8 m_u8CongestionLevelExceeded;     // 拥塞级超过某个级别
	    public fixed DJ_U8 m_u8Reserved[3];                 // 对齐
    };


    // 后向呼叫指示码: ISUP_SP_BackwardCallIndicator //////////////////////////////
    public struct ISUP_spBackwardCallIndicator
    {	
	    public DJ_U8 m_u8ChargeIndicator;             // 计费指示码
	    public DJ_U8 m_u8CalledStatusIndicator;       // 被叫用户状态指示码
	    public DJ_U8 m_u8CalledCategoryIndicator;     // 被叫用户类别指示码
 	    public DJ_U8 m_u8EndToEndMethodIndicator;     // 端到端方法指示码
    	
	    public DJ_U8 m_u8InterworkingIndicator;       // 互通指示码
	    public DJ_U8 m_u8EndToEndInformationIndicator;// 端到端信息指示码
	    public DJ_U8 m_u8ISDNUserPartIndicator;       // ISDN用户部分指示码
	    public DJ_U8 m_u8HoldingIndicator;            // 保持指示码
	    public DJ_U8 m_u8ISDNAccessIndicator;         // ISDN接入指示码
	    public DJ_U8 m_u8EchoControlDeviceIndicator;  // 回音控制器件指示码
	    public DJ_U8 m_u8SCCPMethodIndicator;         // SCCP方法指示码
	    public DJ_U8 m_u8Reserved;                    // 对齐
    };


    // 呼叫转移信息: ISUP_SP_CallDiversionInformation /////////////////////////////
    public struct ISUP_spCallDiversionInformation
    {	
	    public DJ_U8 m_u8NotificationSubscriptionOptions; // 通知登记任选
	    public DJ_U8 m_u8RedirectingReason;               // 改发原因
	    public fixed DJ_U8 m_u8Reserved[2];                     // 对齐
    };


    // 呼叫历史信息: ISUP_SP_CallHistoryInformation ///////////////////////////////
    public struct ISUP_spCallHistoryInformation
    {	
	    public DJ_U16 m_u16PropagationDelayValue; // 传播时延值
	    public fixed DJ_U8  m_u8Reserved[2];            // 对齐
    };


    // 呼叫参考: ISUP_SP_CallReference ////////////////////////////////////////////
    public struct ISUP_spCallReference
    {	
	    public DJ_U32  m_u32CallIdentity; // 呼叫识别

	    public DJ_U32  m_u32SPcode;       // 点码
	    public fixed DJ_U8   m_u8Reserved[4];   // 备用
    };


    // 被叫用户号码: ISUP_SP_CalledPartNumber /////////////////////////////////////
    public struct ISUP_spCalledPartNumber
    {
	    public DJ_U8 m_u8NatureOfAddressIndicator;  // 地址性质指示码
	    public DJ_U8 m_u8OddEvenIndicator;          // 奇偶指示码
	    public DJ_U8 m_u8NumberingPlanIndicator;    // 号码计划指示
	    public DJ_U8 m_u8InternalNetworkNumberIndicator;// 内部网络号码指示码

	    public fixed DJ_U8 m_u8Reserved[4];               // 备用
    	
 	    public fixed DJ_S8 m_s8AddressSignal[40];         // 地址信号	
    };


    // 主叫用户号码: ISUP_SP_CallingPartNumber ////////////////////////////////////
    public struct ISUP_spCallingPartNumber
    {	
	    public DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质指示码
	    public DJ_U8 m_u8OddEvenIndicator;         // 奇偶指示码
    	
	    public DJ_U8 m_u8Screening;                // 屏蔽
	    public DJ_U8 m_u8AddressPresentationRestrictedIndicator;  // 地址显示指示
	    public DJ_U8 m_u8NumberingPlanIndicator;   // 号码计划指示
	    public DJ_U8 m_u8NumberIncompleteIndicator;// 主叫号码不全指示	
    	
	    public fixed DJ_S8 m_s8AddressSignal[40]; // 地址信号
    	
	    public fixed DJ_U8 m_u8Reserved[2];       // 对齐
    };


    // 主叫用户类别: ISUP_SP_CallingPartCategory //////////////////////////////////
    public struct ISUP_spCallingPartCategory
    {	
	    public DJ_U8 m_u8CallingPartyCategory; // 主叫用户类别
	    public fixed DJ_U8 m_u8Reserved[3];          // 对齐
    };


    // 原因指示码: ISUP_SP_CauseIndicator /////////////////////////////////////////
    public struct ISUP_spCauseIndicator
    {	
	    public DJ_U8 m_u8Location;             // 定位
	    public DJ_U8 m_u8CodindStandard;       // 编码标准
	    public DJ_U8 m_u8ExtensionIndicator1;  // 扩充
    	
	    public DJ_U8 m_u8CauseValue;           // 原因值
	    public DJ_U8 m_u8ExtensionIndicator2;  // 扩充
    	
	    public fixed DJ_U8 m_u8Reserved[2];          // 对齐
    	
	    public fixed DJ_U8 m_u8Diagnose[32];         // 诊断	
	    public DJ_U8 m_u8DiagnoseLen;          // 诊断长度
    };


    // 电路群监视消息类型指示码: ISUP_SP_CircuitGroupSupervisionIndicator /////////
    public struct ISUP_spCircuitGroupSupervisionIndicator
    {
	    public DJ_U8 m_u8CircuitGroupSupervisionIndicator; // 类型指示码
	    public fixed DJ_U8 m_u8Reserved[3]; // 对齐
    };


    // 电路状态指示码: ISUP_SP_CircuitStateIndicator //////////////////////////////
    public struct ISUP_spCircuitStateIndicator
    {	
	    public fixed DJ_U8 m_u8CircuitStateIndicator[32];
    };


    // 闭合用户群相关码: ISUP_SP_CUGInterlockCode /////////////////////////////////
    public struct ISUP_spCUGInterlockCode
    {	
	    public DJ_U8  m_u8NIDigit1;  // 第1个NI数字
	    public DJ_U8  m_u8NIDigit2;  // 第2个NI数字
	    public DJ_U8  m_u8NIDigit3;  // 第3个NI数字
	    public DJ_U8  m_u8NIDigit4;  // 第4个NI数字	
    	
	    public DJ_U16 m_u16BinaryCode; // 二进制码
	    public fixed DJ_U8  m_u8Reserved[2]; // 对齐
    };


    // 接续的号码: ISUP_SP_ConnectedNumber ////////////////////////////////////////
    public struct ISUP_spConnectedNumber
    {	
	    public DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质指示码
	    public DJ_U8 m_u8OddEvenIndicator;         // 奇偶指示码
        
	    public DJ_U8 m_u8ScreeningIndicator;       // 屏蔽指示码
	    public DJ_U8 m_u8AddressPresentationRestrictedIndicator; // 地址显示限制
	    public DJ_U8 m_u8NumberingPlanIndicator;   // 号码计划指示	

	    public fixed DJ_U8 m_u8Reserved[3];              // 备用
    	
	    public fixed DJ_S8 m_s8AddressSignal[40];        // 地址信号	
    };


    // 接续请求: ISUP_SP_ConnectionRequest ////////////////////////////////////////
    public struct ISUP_spConnectionRequest
    {	
	    public DJ_U32 m_u32LocalReference; // 呼叫识别
    	
	    public DJ_U32 m_u32SPcode;         // 点码
    	
	    public  DJ_U8  m_u8ProtocolClass;   // 协议类别
	    public DJ_U8  m_u8Credit;          // 信号量

	    public fixed DJ_U8  m_u8Reserved[2];     // 对齐
    };


    // 导通指示码: ISUP_SP_ContitnuityIndicator ///////////////////////////////////
    public struct ISUP_spContitnuityIndicator
    {	
	    public DJ_U8 m_u8ContinuityIndicator; // 导通指示码
	    public fixed DJ_U8 m_u8Reserved[3]; // 对齐
    };


    // 回声控制信息: ISUP_SP_EchoControlInformation ///////////////////////////////
    public struct ISUP_spEchoControlInformation
    {	
	    public DJ_U8 m_u8OutEchoControlInformationIndicator; // 去话半回声控制响应指示
	    public DJ_U8 m_u8InEchoControlInformationIndicator;  // 来话半回声控制响应指示
	    public DJ_U8 m_u8OutEchoControlRequestIndicator;     // 去话半回声控制请求指示
	    public DJ_U8 m_u8InEchoControlRequestIndicator;      // 来话半回声控制请求指示
    };


    // 事件信息: ISUP_SP_EventInformation /////////////////////////////////////////
    public struct ISUP_spEventInformation
    {
	    public DJ_U8 m_u8EventIndicator; // 事件指示码
	    public DJ_U8 m_u8EventPresentationRestrictedIndicator;// 事件显示限制指示码	
	    public fixed DJ_U8 m_u8Reserved[2]; // 对齐
    };


    // 功能指示码: ISUP_SP_FacilityIndicator //////////////////////////////////////
    public struct ISUP_spFacilityIndicator
    {	
	    public DJ_U8 m_u8FacilityIndicator; // 功能指示码
	    public fixed DJ_U8 m_u8Reserved[3];
    };


    // 前向呼叫指示码: ISUP_SP_ForwardCallIndicator ///////////////////////////////
    public struct ISUP_spForwardCallIndicator
    {	
	    public DJ_U8 m_u8NationalInternatoinalIndicator; // 国内/国际呼叫指示码
	    public DJ_U8 m_u8EndToEndMethodIndicator;        // 端到端方法指示码
	    public DJ_U8 m_u8InterworkingIndicator;          // 互通指示码
	    public DJ_U8 m_u8EndToEndInformationIndicator;   // 端到端信息指示码
	    public DJ_U8 m_u8ISDNUserPartIndicator;          // ISDN用户部分指示码
	    public DJ_U8 m_u8ISDNUserPartPreferenceIndicator;// ISDN用户部分优先指示码
    	
	    public DJ_U8 m_u8ISDNAccessIndicator; // ISDN接入指示码
	    public DJ_U8 m_u8SCCPMethodIndicator; // SCCP方法指示码
    	
	    public fixed DJ_U8 m_u8Reserved[4];         // 备用
    };


    // 类属数字: ISUP_SP_GenericDigit /////////////////////////////////////////////
    public struct ISUP_spGenericDigit
    {	
	    public DJ_U8 m_u8TypeOfDigit;   // 数字类型
	    public DJ_U8 m_u8EncodingScheme;// 编码计划	
    	
	    public fixed DJ_U8 m_u8Digit[32];     // 数字
	    public DJ_U8 m_u8DigitLen;      // 数字长度
    	
	    public DJ_U8 m_u8Reserved;      // 对齐
    };


    // 类属通知指示码: ISUP_SP_GenericNotifyIndicator /////////////////////////////
    public struct ISUP_spGenericNotifyIndicator
    {
	    public DJ_U8 m_u8NotificationIndicator; // 通知指示码
	    public DJ_U8 m_u8ExtensionIndicator;    // 扩充指示码
	    public fixed DJ_U8 m_u8Reserved[2];           // 对齐
    };


    // 类属号码: ISUP_SP_GenericNumber ////////////////////////////////////////////
    public struct ISUP_spGenericNumber
    {	
	    public DJ_U8 m_u8NumberQualifierIndicator;    // 号码限定指示码
    	
	    public DJ_U8 m_u8NatureOfAddressIndicator;// 地址性质指示码
	    public DJ_U8 m_u8OddEvenIndicator;  // 奇偶指示码	
    	
	    public DJ_U8 m_u8ScreeningIndicator;// 屏蔽
	    public DJ_U8 m_u8AddressPresentationRestrictedIndicator; // 显示指示
	    public DJ_U8 m_u8NumberingPlanIndicator;    // 号码计划指示
	    public DJ_U8 m_u8NumberIncompleteIndicator; //	号码不全指示	
    	
	    public fixed DJ_S8 m_s8AddressSignal[40]; // 地址信号
    	
	    public DJ_U8 m_u8Reserved;          // 对齐
    };


    // 类属参考: ISUP_SP_GenericReference /////////////////////////////////////////
    public struct ISUP_spGenericReference
    {
	    public DJ_U8 m_u8ReferenceRestrictedIndicator; // 参考限定指示码
	    public DJ_U8 m_u8ReferenceLength;  // 参考长度	
    	
	    public fixed DJ_U8 m_u8ReferenceCode[4]; // 参考八位组信息

	    public fixed DJ_U8 m_u8Reserved[2];      // 对齐
    };


    // 信息指示码: ISUP_SP_InformationIndicator ///////////////////////////////////
    public struct ISUP_spInformationIndicator
    {	
	    public DJ_U8 m_u8CallingPartyAddressResponseIndicator; // 主叫用户地址响应指示码
	    public DJ_U8 m_u8HoldProvidedIndicator; // 保持提供指示码
    	
	    public DJ_U8 m_u8CallingPartyCategoryResponseIndicator; // 主叫用户类别响应指示码
	    public DJ_U8 m_u8ChargeInformationResponseIndicator;  // 计费信息响应指示码
	    public DJ_U8 m_u8SolicitedInformationIndicator;  // 请求信息指示码
    	
	    public  fixed DJ_U8 m_u8Reserved[3]; // 对齐
    };


    // 信息请示指示码: ISUP_SP_InformationRequestIndicator ////////////////////////
    public struct ISUP_spInformationRequestIndicator
    {	
	    public DJ_U8 m_u8CallingPartyAddressRequestIndicator; // 主叫用户地址请求指示码
	    public DJ_U8 m_u8HoldingIndicator; // 保持指示码
    	
	    public DJ_U8 m_u8CallingPartyCategoryRequestIndicator;// 主叫用户类别请求指示码
	    public DJ_U8 m_u8ChargeInformationRequestIndicator;   // 计费信息请求指示码
    	
	    public DJ_U8 m_u8MaliciousCallIdentificationRequestIndicator; // 恶意呼叫识别
	    public fixed DJ_U8 m_u8Reserved[3];  // 对齐
    };


    // 定位号码: ISUP_SP_LocationNumber ///////////////////////////////////////////
    public struct ISUP_spLocationNumber
    {	
	    public DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质指示码
	    public DJ_U8 m_u8OddEvenIndicator;         // 奇偶指示码

	    public DJ_U8 m_u8ScreeningIndicator;       // 屏蔽指示码
	    public DJ_U8 m_u8AddressPresentationRestrictedIndicator; // 地址显示限制指示码
	    public DJ_U8 m_u8NumberingPlanIndicator;   // 号码计划指示码
	    public DJ_U8 m_u8InternalNetworkNumberIndicator; // 内部网络号码指示码	
    	
	    public fixed DJ_S8 m_s8AddressSignal[40]; // 地址信号

	    public fixed DJ_U8 m_u8Reserved[2]; // 对齐
    };


    // MCID请求指示码: ISUP_SP_MCIDRequestIndicator ///////////////////////////////
    public struct ISUP_spMCIDRequestIndicator
    {	
	    public DJ_U8 m_u8MCIDRequestIndicator; // MCID请求指示码
	    public DJ_U8 m_u8HoldingIndicator;     // 保持指示码
	    public fixed DJ_U8 m_u8Reserved[2]; // 备用
    };


    // MCID 响应指示码: ISUP_SP_MCIDResponseIndicator /////////////////////////////
    public struct ISUP_spMCIDResponseIndicator
    {	
	    public DJ_U8 m_u8MCIDResponseIndicator; // MCID响应指示码
	    public DJ_U8 m_u8HoldProvidedIndicator; // 保持提供指示码
	    public fixed DJ_U8 m_u8Reserved[2]; // 备用
    };


    // 消息兼容性信息: ISUP_SP_MsgCompatibilityInformation ////////////////////////
    public struct ISUP_spMsgCompatibilityInformation
    {	
	    public DJ_U8 m_u8TransitAtIntermediateExchangeIndicator1;// 在中间交换局汇接指示码
	    public DJ_U8 m_u8ReleaseCallIndicator1;      // 释放呼叫指示码
	    public DJ_U8 m_u8SendNotificationIndicator1; // 发送通知指示码
	    public DJ_U8 m_u8DiscardMessageIndicator1;   // 舍弃消息指示码
	    public DJ_U8 m_u8PassOnNotPossibleIndicator1;// 通过不可能指示码
	    public DJ_U8 m_u8ExtensionIndicator1;        // 扩充指示码
	    public fixed DJ_U8 m_u8Reserved1[2];               // 对齐
    	
	    public DJ_U8 m_u8TransitAtIntermediateExchangeIndicator2;// 在中间交换局汇接指示码
	    public DJ_U8 m_u8ReleaseCallIndicator2;      // 释放呼叫指示码
	    public DJ_U8 m_u8SendNotificationIndicator2; // 发送通知指示码
	    public DJ_U8 m_u8DiscardMessageIndicator2;   // 舍弃消息指示码
	    public DJ_U8 m_u8PassOnNotPossibleIndicator2;// 通过不可能指示码
	    public DJ_U8 m_u8ExtensionIndicator2;        // 扩充指示码
	    public fixed DJ_U8 m_u8Reserved2[2];               // 对齐
    };


    // MLPP优先: ISUP_SP_MlppPrecedence ///////////////////////////////////////////
    public struct ISUP_spMlppPrecedence
    {	
	    public DJ_U8  m_u8PrecedenceLevel;  // 优先级	
	    public DJ_U8  m_u8LFB;        // LFB
	    public fixed DJ_U8  m_u8Reserved[2];// 对齐
    	
	    public DJ_U8  m_u8NIDigit1;  // 第1个NI数字
	    public DJ_U8  m_u8NIDigit2;  // 第2个NI数字
	    public DJ_U8  m_u8NIDigit3;  // 第3个NI数字
	    public DJ_U8  m_u8NIDigit4;  // 第4个NI数字	
    	
	    public DJ_U32 m_u32MLPPServiceDomain;
    };


    // 接续性质指示码: ISUP_SP_NatureOfConnectionIndicator ////////////////////////
    public struct ISUP_spNatureOfConnectionIndicator
    {	
	    public DJ_U8 m_u8SatelliteIndicator;        // 卫星指示码
	    public DJ_U8 m_u8ContinuityCheckIndicator;  // 导通检验指示码
	    public DJ_U8 m_u8EchoControlDeviceIndicator;// 回声控制器件指示码
	    public DJ_U8 m_u8Reserved;
    };


    // 网络特定功能: ISUP_SP_NetworkSpecificFacility //////////////////////////////
    public struct ISUP_spNetworkSpecificFacility
    {	
	    public fixed DJ_U8 m_u8NsfInformation[32];  // 参数信息

	    public DJ_U8 m_u8NsfLen;              // 参数长度
	    public fixed DJ_U8 m_u8Reserved[3];         // 对齐	
    };


    // 任选后向呼叫指示码: ISUP_SP_OptBackwardCallIndicator ///////////////////////
    public struct ISUP_spOptBackwardCallIndicator
    {	
	    public DJ_U8 m_u8InBandInformationIndicator;    // 带内信息指示码
	    public DJ_U8 m_u8CallTransferPossibleIndicator; // 呼叫转移可能发送指示码
	    public DJ_U8 m_u8SimpleSegmentationIndicator;   // 简单分段指示码
	    public DJ_U8 m_u8MLPPUserIndicator;             // MLPP用户指示码

	    public fixed DJ_U8 m_u8Reserved[4];
    };


    // 任选前向呼叫指示码: ISUP_SP_OptForwardCallIndicator ////////////////////////
    public struct ISUP_spOptForwardCallIndicator
    {		
	    public DJ_U8 m_u8ClosedUserGroupCallIndicator; // CUG呼叫指示码
	    public DJ_U8 m_u8SimpleSegmentationIndicator;  // 简单分段指示码
	    public DJ_U8 m_u8UserIdentityRequestIndicator; // 接续的用户识别请求指示码
	    public DJ_U8 m_u8Reserved;                     // 对齐
    };


    // 原被叫号码: ISUP_SP_OriginalCalledNumber ///////////////////////////////////
    public struct ISUP_spOriginalCalledNumber
    {	
	    public DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质指示码
	    public DJ_U8 m_u8OddEvenIndicator;         // 奇偶指示码
    	
	    public DJ_U8 m_u8AddressPresentationRestrictedIndicator; // 显示指示
	    public DJ_U8 m_u8NumberingPlanIndicator; // 号码计划指示
    	
	    public fixed DJ_S8 m_s8AddressSignal[40]; // 地址信号
    	
	    public fixed DJ_U8 m_u8Reserved[4];  // 备用
    };


    // 始发国际交换中心(ISC)的点码: ISUP_SP_OriginationISCPointCode ///////////////
    public struct ISUP_spOriginationISCPointCode
    {
	    public DJ_U32 m_u32SPcode;     // 点码
	    public fixed DJ_U8  m_u8Reserved[4]; // 备用
    };


    // 参数兼容性信息: ISUP_SP_ParamCompatibilityInformation //////////////////////
    public struct ISUP_spParamCompatibilityInformation
    {
	    public DJ_U8 m_u8UpgradedParameter1;         // 第一个升格参数	
	    public DJ_U8 m_u8TransitAtIntermediateExchangeIndicator1;// 在中间交换局汇接指示码
	    public DJ_U8 m_u8ReleaseCallIndicator1;      // 释放呼叫指示码
	    public DJ_U8 m_u8SendNotificationIndicator1; // 发送通知指示码
	    public DJ_U8 m_u8DiscardMessageIndicator1;   // 舍弃消息指示码
	    public DJ_U8 m_u8DiscardParameterIndicator1; // 舍弃参数指示码
	    public DJ_U8 m_u8ExtensionIndicator1;        // 扩充指示码
	    public DJ_U8 m_u8Reserved1;                  // 备用
    	
	    public DJ_U8 m_u8UpgradedParameter2;         // 第二个升格参数	
	    public DJ_U8 m_u8TransitAtIntermediateExchangeIndicator2;// 在中间交换局汇接指示码
	    public DJ_U8 m_u8ReleaseCallIndicator2;      // 释放呼叫指示码
	    public DJ_U8 m_u8SendNotificationIndicator2; // 发送通知指示码
	    public DJ_U8 m_u8DiscardMessageIndicator2;   // 舍弃消息指示码
	    public DJ_U8 m_u8DiscardParameterIndicator2; // 舍弃参数指示码
	    public DJ_U8 m_u8ExtensionIndicator2;        // 扩充指示码
	    public DJ_U8 m_u8Reserved2;                  // 备用

	    public DJ_U8 m_u8UpgradedParameter3;         // 第三个升格参数	
	    public DJ_U8 m_u8TransitAtIntermediateExchangeIndicator3;// 在中间交换局汇接指示码
	    public DJ_U8 m_u8ReleaseCallIndicator3;      // 释放呼叫指示码
	    public DJ_U8 m_u8SendNotificationIndicator3; // 发送通知指示码
	    public DJ_U8 m_u8DiscardMessageIndicator3;   // 舍弃消息指示码
	    public DJ_U8 m_u8DiscardParameterIndicator3; // 舍弃参数指示码
	    public DJ_U8 m_u8ExtensionIndicator3;        // 扩充指示码
	    public DJ_U8 m_u8Reserved3;                  // 备用
    };


    // 传播延时计数器: ISUP_SP_PropagationDelayCounter ////////////////////////////
    public struct ISUP_spPropagationDelayCounter
    {	
	    public DJ_U16 m_u16PropagationDelayValue;  // 传播时延值
	    public fixed DJ_U8  m_u8Reserved[2]; // 对齐
    };


    // 范围和状态: ISUP_SP_RangeState /////////////////////////////////////////////
    public struct ISUP_spRangeState
    {
	    public DJ_U8  m_u8Range;      // 范围
	    public fixed DJ_U8  m_u8Reserved[3];// 对齐
    	
	    public DJ_U32 m_u32Status;    // 状态
    };


    // 改发号码: ISUP_SP_RedirectingNumber ////////////////////////////////////////
    public struct ISUP_spRedirectingNumber
    {	
	    public DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质指示码
	    public DJ_U8 m_u8OddEvenIndicator; // 奇偶指示码	
        
	    public DJ_U8 m_u8AddressPresentationRestrictedIndicator; // 显示限制指示码
	    public DJ_U8 m_u8NumberingPlanIndicator; // 号码计划指示码	
    	
	    public fixed DJ_S8 m_s8AddressSignal[40]; // 地址信号

	    public fixed DJ_U8 m_u8Reserved[4];  // 备用
    };


    // 改发信息: ISUP_SP_RedirectionInformation ///////////////////////////////////
    public struct ISUP_spRedirectionInformation
    {
	    public DJ_U8 m_u8RedirectingIndicator; // 改发指示码
	    public DJ_U8 m_u8OriginalRedirectionReason; // 原理的改发原因
	    public DJ_U8 m_u8RedirectionCounter;   // 改发计数器
	    public DJ_U8 m_u8RedirectingReason;    // 改发原因

	    public fixed DJ_U8 m_u8Reserved[4]; // 备用	
    };


    // 改发号码: ISUP_SP_RedirectionNumber ////////////////////////////////////////
    public struct ISUP_spRedirectionNumber
    {	
	    public DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质指示码
	    public DJ_U8 m_u8OddEvenIndicator;         // 奇偶指示码
	    public DJ_U8 m_u8NumberingPlanIndicator;   // 号码计划指示码
	    public DJ_U8 m_u8InternalNetworkNumberIndicator; // 内部网络号码指示码
    	
	    public fixed DJ_S8 m_s8AddressSignal[40];            // 地址信号

	    public fixed DJ_U8 m_u8Reserved[4]; // 备用
    };


    // 改发号码限制参数: ISUP_SP_RedirectionRestricition //////////////////////////
    public struct ISUP_spRedirectionRestricition
    {	
	    public DJ_U8 m_u8PresentationRestrictedIndicator; // 显示限制指示码
	    public fixed DJ_U8 m_u8Reserved[3];
    };


    // 远端操作: ISUP_SP_RemoteOperation //////////////////////////////////////////
    public struct ISUP_spRemoteOperation
    {	
	    public DJ_U8 m_u8ProtocolProfile;    // 协议剖析    
	    public DJ_U8 m_u8ExtensionIndicator; // 扩充	
    	
	    public fixed DJ_U8 m_u8Component[240];
    	
	    public DJ_U8 m_u8ComponentLen;
	    public DJ_U8 m_u8Reserved;          // 对齐
    };


    // 业务激活: ISUP_SP_ServiceActivation ////////////////////////////////////////
    public struct ISUP_spServiceActivation
    {
	    public fixed DJ_U8 m_u32FeatureCode[32];  // 特征码
    	
	    public DJ_U8 m_u8FCLen;             // 特征码长度
	    public fixed DJ_U8 m_u8Reserved[3];       // 对齐	
    };


    // 信令点编码: ISUP_SP_SignalPointCode ////////////////////////////////////////
    public struct ISUP_spSignalPointCode
    {	
	    public DJ_U32 m_u32SPcode;     // 点码	
	    public fixed DJ_U8  m_u8Reserved[4]; // 备用	
    };


    // 后续号码: ISUP_SP_SubsequentNumber /////////////////////////////////////////
    public struct ISUP_spSubsequentNumber
    {		
	    public DJ_U8 m_u8OddEvenIndicator; // 奇偶指示码
	    public fixed DJ_U8 m_u8Reserved[3];      // 对齐
    	
	    public fixed DJ_S8 m_s8AddressSignal[40];    // 地址信号
    };


    // 暂停恢复指示: ISUP_SP_SuspendResumeIndicator ///////////////////////////////
    public struct ISUP_spSuspendResumeIndicator
    {	
	    public DJ_U8 m_u8SuspendResumeIndicator; // 暂停/恢复指示码
	    public fixed DJ_U8 m_u8Reserved[3]; // 对齐	
    };


    // 汇接网络选择: ISUP_SP_TransitNetworkSelection //////////////////////////////
    public struct ISUP_spTransitNetworkSelection
    {	
	    public DJ_U8 m_u8NetworkIdentificationPlan;   // 网络识别计划
	    public DJ_U8 m_u8TypeOfNetworkIdentification; // 网络识别类型
	    public DJ_U8 m_u8OddEvenIndicator;            // 奇偶指示码
	    public DJ_U8 m_u8Reserved;                    // 对齐
    	
	    public fixed DJ_U8 m_u8NetworkIdentification[32];   // 网络识别
    	
	    public DJ_U8 m_u8NetIdLen;                    // 网络识别长度
	    public fixed DJ_U8 m_u8Rev[3];                      // 对齐	
    };


    // 传输媒价要求: ISUP_SP_TransmissionMediumRequirement ////////////////////////
    public struct ISUP_spTransmissionMediumRequirement
    {	
	    public DJ_U8 m_u8TransmissionMediumRequirement; // 传送媒介要求
	    public fixed DJ_U8 m_u8Reserved[3]; // 对齐	
    };


    // 传输媒介要求(基本): ISUP_SP_TransmissionMediumRequirementPrime /////////////
    public struct ISUP_spTransmissionMediumRequirementPrime
    {	
	    public DJ_U8 m_u8TransmissionMediumRequirement; // 传送媒介要求
	    public fixed DJ_U8 m_u8Reserved[3]; // 对齐
    };


    // 使用中的传输媒介: ISUP_SP_TransmissionMediumUsed ///////////////////////////
    public struct ISUP_spTransmissionMediumUsed
    {	
	    public DJ_U8 m_u8TransmissionMediumRequirement; // 传送媒介要求
	    public fixed DJ_U8 m_u8Reserved[3]; // 对齐
    };


    // 用户业务信息: ISUP_SP_UserServiceInformation ///////////////////////////////
    public struct ISUP_spUserServiceInformation
    {
	    public fixed DJ_U8 m_u8USInformation[32]; // 用户业务信息
    	
	    public DJ_U8 m_u8USILen;            // 信息长度
	    public fixed DJ_U8 m_u8Reserved[3];       // 对齐	
    };


    // 基本用户业务信息: ISUP_SP_UserServiceInformationPrime //////////////////////
    public struct ISUP_spUserServiceInformationPrime
    {
	    public fixed DJ_U8 m_u8USInformation[32]; // 用户业务信息
    	
	    public DJ_U8 m_u8USILen;            // 信息长度
	    public fixed DJ_U8 m_u8Reserved[3];       // 对齐	
    };


    // 用户电信业务信息: ISUP_SP_UserTeleserviceInformation ///////////////////////
    public struct ISUP_spUserTeleserviceInformation
    {	
	    public DJ_U8 m_u8Presentation;   // 显示
	    public DJ_U8 m_u8Interpretation; // 解释
	    public DJ_U8 m_u8CodingStandard; // 编码标准
	    public DJ_U8 m_u8ExtensionIndicator1; // 扩充
    	
	    public DJ_U8 m_u8HighLayerCharacteristicsIdentification; // 高层特性识别
	    public DJ_U8 m_u8ExtensionIndicator2; // 扩充

	    public DJ_U8 m_u8ExtendedHighLayerCharacteristicsIdentification; // 扩充的高层特性识别
	    public DJ_U8 m_u8ExtensionIndicator3;	// 扩充
    };


    // 用户至用户指示码: ISUP_SP_UserToUserIndicator //////////////////////////////
    public struct ISUP_spUserToUserIndicator
    {	
	    public DJ_U8 m_u8Type;     // 类型
	    public DJ_U8 m_u8Service1; // 业务
	    public DJ_U8 m_u8Service2; // 业务
	    public DJ_U8 m_u8Service3; // 业务
	    public DJ_U8 m_u8NetworkDiscardIndicator; // 网络舍弃指示码

	    public fixed DJ_U8 m_u8Reserved[3]; // 对齐
    };


    // 用户至用户信息: ISUP_SP_UserToUserInformation //////////////////////////////
    public struct ISUP_spUserToUserInformation
    {	
	    public fixed DJ_U8 m_u8UserToUserInformation[240];
    	
	    public DJ_U8 m_u8UifLen;      // 信息长度
	   public fixed DJ_U8 m_u8Reserved[3]; // 对齐
    };

#endregion

#region DJAcsTUPDef.h

    // TUP信令消息定义(根据需要直接发送部分) //////////////////////////////////////
    public enum XMS_TUP_Signalling_Message     // TUP信令消息
    {	  
        TUP_SM_SAM = 0x31,              // 后续地址信号
        TUP_SM_SAO = 0x41,              // 带有一个地址的后续地址信号
        
        TUP_SM_GSM = 0x12,              // 一般前向建立信息信号
        TUP_SM_GRQ = 0x13,              // 一般请求信号
        
        TUP_SM_BLO = 0x27,              // 闭塞信号
        TUP_SM_UBL = 0x47,              // 解除闭塞信号
        TUP_SM_RSC = 0x77,              // 电路复原信号
        
        TUP_SM_MGB = 0x18,              // 面向维护的群闭塞信号
        TUP_SM_MGU = 0x38,              // 面向维护的群解除闭塞信号
        TUP_SM_HGB = 0x58,              // 面向硬件故障的群闭塞信号
        TUP_SM_HGU = 0x78,              // 面向硬件故障的群解除闭塞信号
        TUP_SM_GRS = 0x98,              // 电路群复原信号
        TUP_SM_SGB = 0xB8,              // 软件产生的群闭塞信号
        TUP_SM_SGU = 0xD8,              // 软件产生的群解除闭塞消信号
    };


    // TUP信令参数定义 ////////////////////////////////////////////////////////////
    public enum XMS_TUP_Signalling_Parameter                   // TUP信令参数
    {	
	    TUP_SP_AccMessageIndicator        = 0x0C,       // ACC消息指示码
	    TUP_SP_AcmMessageIndicator        = 0x09,       // ACM消息指示码
	    TUP_SP_CalledPartAddress          = 0x0F,       // 被叫用户号码
	    TUP_SP_CallingLineAddress         = 0x02,       // 主叫用户号码
	    TUP_SP_CallingPartyCategory       = 0x01,       // 主叫用户类别
	    TUP_SP_ConnectionNatureIndicator  = 0x0D,       // 接续性质指示码
	    TUP_SP_EumOctetIndicator          = 0x0A,       // EUM消息八位组
	    TUP_SP_EumSignallingPointCode     = 0x0B,       // EUM消息信令点
	    TUP_SP_ForwardCallInformation     = 0x0E,       // 前向呼叫信息
	    TUP_SP_GrqRequestTypeIndicator    = 0x08,       // GRQ请求指示码
	    TUP_SP_GsmResponseTypeIndicator   = 0x06,       // GSM响应指示码
	    TUP_SP_IaiFirstIndicator          = 0x05,       // IAI第一表示语
	    TUP_SP_OriginalCalledAddress      = 0x03,       // 原被叫用户号码
	    TUP_SP_RangeStatus                = 0x04,       // 范围与状态
	    TUP_SP_SubsequentAddress          = 0x10        // 后续地址
    };


    // TUP信令参数数据结构定义 ////////////////////////////////////////////////////
    // ACC消息指示码: TUP_SP_AccMessageIndicator //////////////////////////////////
    // 信令: ACC
    public struct TUP_spAccMessageIndicator
    {
	    public DJ_U8 m_u8ACCInformation; // ACC信息
	    public fixed DJ_U8 m_u8Reserved[3]; // 备用
    };


    // ACM消息指示码: TUP_SP_AcmMessageIndicator //////////////////////////////////
    // 信令: ACM
    public struct TUP_spAcmMessageIndicator
    {
	    public DJ_U8 m_u8TypeOfACMIndicator; // 地址全信号类型表示语
	    public DJ_U8 m_u8SubscriberFreeIndicator; // 用户闲表示语
	    public DJ_U8 m_u8IncomingEchoSuppressorIndicator; // 来话回声抑制器表示语
	    public DJ_U8 m_u8CallForwardingIndicator; // 呼叫转移表示语
	    public DJ_U8 m_u8SignallingPathIndicator; // 信号通道表示语
	    public fixed DJ_U8 m_u8Reserved[3]; // 备用
    };


    // 被叫用户号码: TUP_SP_CalledPartAddress /////////////////////////////////////
    // 信令: IAM/IAI
    public struct TUP_spCalledPartAddress
    {
	    public DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质表示语
	    public DJ_U8 m_u8NumberOfAddressSignal; // 地址信号的数量
	    public fixed DJ_U8 m_u8Reserved[2]; // 备用
        public fixed DJ_S8 m_s8AddressSignal[40]; // 地址信号
    };


    // 主叫用户号码: TUP_SP_CallingLineAddress ////////////////////////////////////
    // 信令: IAI/GSM
    public struct TUP_spCallingLineAddress
    {
	    public DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质表示语
	    public DJ_U8 m_u8PresentationIndicator; // 提供主叫用户线标识表示语
	    public DJ_U8 m_u8IncompleteIndicator; // 主叫用户线标识不全表示语
	    public DJ_U8 m_u8NumberOfAddressSignal; // 主叫地址信号的数量
    	
	    public fixed DJ_S8 m_s8AddressSignal[40]; // 地址信号
    };


    // 主叫用户类别: TUP_SP_CallingPartyCategory //////////////////////////////////
    // 信令: IAM/IAI/GSM
    public struct TUP_spCallingPartyCategory
    {
	    public DJ_U8 m_u8CallingPartyCategory;  // 主叫用户类别
	    public fixed DJ_U8 m_u8Reserved[3]; // 备用
    };


    // 接续性质指示码: TUP_SP_ConnectionNatureIndicator ///////////////////////////
    // 信令: IAM/IAI
    public struct TUP_spConnectionNatureIndicator
    {	
	    public DJ_U8 m_u8NatureOfCircuitIndicator; // 电路性质表示语
	    public DJ_U8 m_u8ContinuityCheckIndicator; // 导通检验表示语
	    public DJ_U8 m_u8EchoSuppressorIndicator;  // 去话回声抑制器表示语
	    public DJ_U8 m_u8Reserved;
    };


    // EUM消息八位组: TUP_SP_EumOctetIndicator ////////////////////////////////////
    // 信令: EUM
    public struct TUP_spEumOctetIndicator
    {
	    public DJ_U8 m_u8UnsuccessfulIndicator; // 不成功表示语
	    public fixed DJ_U8 m_u8Reserved[3]; // 备用
    };


    // EUM消息信令点: TUP_SP_EumSignallingPointCode ///////////////////////////////
    // 信令: EUM
    public struct TUP_spEumSignallingPointCode
    {
	    public DJ_U32 m_u32SPC; // 信令点编码
    };


    // 前向呼叫信息: TUP_SP_ForwardCallInformation ////////////////////////////////
    // 信令: IAM/IAI
    public struct TUP_spForwardCallInformation
    {
	    public DJ_U8 m_u8InternationalCallIndicator; // 国际来话呼叫表示语
    	
	    public DJ_U8 m_u8RedirectedCallIndicator; // 改发呼叫表示语
	    public DJ_U8 m_u8AllDigitalPathRequiredIndicator; // 需要全部是数字通路表示语
	    public DJ_U8 m_u8SignallingPathIndicator; // 信号通道表示语
    };


    // GRQ请求指示码: TUP_SP_GrqRequestTypeIndicator //////////////////////////////
    // 信令: GRQ
    public struct TUP_spGrqRequestTypeIndicator
    {
	    public DJ_U8 m_u8CallingPartyCategoryRequestIndicator; // 主叫用户类别请求表示语
	    public DJ_U8 m_u8CallingLineIdentityRequestIndicator; // 主叫用户线标识请求表示语
	    public DJ_U8 m_u8OriginalCalledAddressRequestIndicator; // 原被叫地址请求表示语
	    public DJ_U8 m_u8MaliciousCallIdentificationIndicator; // 恶意呼叫识别请求表示语
	    public DJ_U8 m_u8HoldRequestIndicator; // 保持请求表示语
	    public DJ_U8 m_u8EchoSuppressorRequestIndicator; // 回声抑制器请求表示语
	    public fixed DJ_U8 m_u8Reserved[2]; // 备用
    };


    // GSM响应指示码: TUP_SP_GsmResponseTypeIndicator /////////////////////////////
    // 信令: GSM
    public struct TUP_spGsmResponseTypeIndicator
    {
	    public DJ_U8 m_u8CallingPartyCategoryIndicator; // 主叫用户类别表示语
	    public DJ_U8 m_u8CallingLineIdentityIndicator; // 主叫用户线标识表示语
	    public DJ_U8 m_u8IdentityIndicator; // 来话中继和转接交换局标识
	    public DJ_U8 m_u8OriginalCalledAddressIndicator; // 原被叫地址表示语
	    public DJ_U8 m_u8OutgoingEchoSuppressorIndicator; // 去话回声抑制器表示语
	    public DJ_U8 m_u8MaliciousCallIdentificationIndicator; // 恶意呼叫识别表示语
	    public DJ_U8 m_u8HoldIndicator; // 保持表示语
	    public DJ_U8 m_u8Reserved; // 备用
    };


    // IAI第一表示语: TUP_SP_IaiFirstIndicator ////////////////////////////////////
    // 信令: IAI
    public struct TUP_spIaiFirstIndicator
    {
	    public DJ_U8 m_u8FacilityInformationIndicator; // 网络能力或用户性能信息表示语
	    public DJ_U8 m_u8CUGInformationIndicator; // 闭合用户群信息表示语
	    public DJ_U8 m_u8AdditionalCallingPartyIndicator; // 附加主叫用户信息表示语
	    public DJ_U8 m_u8AdditionalRoutingIndicator; // 附加路由信息表示语
	    public DJ_U8 m_u8CallingLineIdentityIndicator; // 主叫用户线标识表示语
	    public DJ_U8 m_u8OriginalCalledAddressIndicator; // 原被叫地址表示语
	    public DJ_U8 m_u8ChargingInformationIndicator; // 计费信息表示语
	    public DJ_U8 m_u8Reserved; // 备用
    };


    // 原被叫用户号码: TUP_SP_OriginalCalledAddress ///////////////////////////////
    // 信令: IAI/GSM
    public struct TUP_spOriginalCalledAddress
    {
	    public DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质表示语
	    public DJ_U8 m_u8NumberOfAddressSignal; // 地址信号的数量
	    public fixed DJ_U8 m_u8Reserved[2]; // 备用
        public fixed DJ_S8 m_s8AddressSignal[40]; // 地址信号
    };


    // 范围与状态: TUP_SP_RangeStatus /////////////////////////////////////////////
    // 信令: GRM消息组
    public struct TUP_spRangeStatus
    {
	    public DJ_U8  m_u8Range; // 范围
	    public fixed DJ_U8  m_u8Reserved[3]; // 备用
    	
	    public DJ_U32 m_u32Status;    // 状态
    };


    // 后续地址: TUP_SP_SubsequentAddress /////////////////////////////////////////
    // 信令: SAM/SAO
    public struct TUP_spSubsequentAddress
    {
	    public fixed DJ_S8 m_s8AddressSignal[40]; // 地址信号
    };

#endregion

#region DJAcsDataDef.h

    public const int  ACS_MAX_CALL_NUM = 32;
    public const int  ACS_SIGDATA_MAX_LEN = 300;
    public const int  ACS_MAX_IO_SIZE = 2048;
    public const int  ACS_LOCALID_MAX_LEN = 20;
    public const int  ACS_REMOTEID_MAX_LEN = 20;
    public const int  ACS_MAX_DECODER_CFG_LEN = 200;
    public const int  XMS_MAX_REGNAME_LEN = 16;
    public const int  ACS_MAX_H245_SIG_PDU_LEN = 4000;
    public const int  ITP_VOIP_MONDATA_MAX = 1024;

    public delegate void EsrFunc(int esrParam);

    public enum XMS_DEVMAIN_TYPE
    {
    	XMS_DEVMAIN_CONFIG               = 0x01, /*config adding for log manager*/
	    XMS_DEVMAIN_VOICE                = 0x02, /*Voice device*/
	    XMS_DEVMAIN_FAX                  = 0x03, /*Fax device*/
	    XMS_DEVMAIN_DIGITAL_PORT         = 0x04, /*Digital Port device*/
	    XMS_DEVMAIN_INTERFACE_CH         = 0x05, /*Interface Ch device*/
	    XMS_DEVMAIN_DSS1_LINK            = 0x06, /*DSS1 Link device*/
	    XMS_DEVMAIN_SS7_LINK             = 0x07, /*SS7 Link device*/
	    XMS_DEVMAIN_BOARD                = 0x08, /*DSP Board device*/
	    XMS_DEVMAIN_CTBUS_TS             = 0x09, /*CTBus ts device*/
	    XMS_DEVMAIN_RTP	                 = 0x0A, /*Rtp device*/
	    XMS_DEVMAIN_MEDIAEX              = 0x0B, /*MediaEx device*/
	    XMS_DEVMAIN_CONFERENCE           = 0x0C, /*Conference Group Device*/
	    XMS_DEVMAIN_VIDEO                = 0x0D, /*Video device*/
	    XMS_DEVMAIN_CTX                  = 0x10, /*Ctx device*/
	    XMS_DEVMAIN_RTPX                 = 0x11, /*RTPX device*/
	    XMS_DEVMAIN_VOIP                 = 0x12, /*VoIP device*/
	    XMS_DEVMAIN_VIDEOCONF            = 0x1F, /*Video Conference Device*/
    };

    public enum XMS_INTERFACE_DEVSUB_TYPE
    {
	    XMS_DEVSUB_BASE                       = 0x0,  /*Base*/
	    XMS_DEVSUB_ANALOG_TRUNK               = 0x01, /*Analog Trunk*/
	    XMS_DEVSUB_ANALOG_USER                = 0x02, /*Analog User*/
	    XMS_DEVSUB_ANALOG_HIZ                 = 0x03, /*Analog Hiz*/
	    XMS_DEVSUB_ANALOG_EMPTY               = 0x04, /*Analog Empty*/
	    XMS_DEVSUB_E1_PCM                     = 0x05, /*E1 PCM*/
	    XMS_DEVSUB_E1_CAS                     = 0x06, /*E1 CAS*/
	    XMS_DEVSUB_E1_DSS1                    = 0x07, /*E1 DSS1*/
	    XMS_DEVSUB_E1_SS7_TUP                 = 0x08, /*E1 SS7 TUP*/
	    XMS_DEVSUB_E1_SS7_ISUP                = 0x09, /*E1 SS7 ISUP*/
	    XMS_DEVSUB_ANALOG_VOC2W			      = 0x0A, /*Voice only 2 wire*/
        XMS_DEVSUB_ANALOG_VOC4W			      = 0x0B, /*Voice only 4 wire*/
        XMS_DEVSUB_ANALOG_EM			      = 0x0C, /*EM control module*/
        XMS_DEVSUB_ANALOG_MAG			      = 0x0D, /*magnetic module*/
        XMS_DEVSUB_E1_DCH				      = 0x0E, /*E1 6D25B's Dchannel*/
        XMS_DEVSUB_E1_BCH				      = 0x0F, /*E1 6D25B's Bchannel*/
        XMS_DEVSUB_UNUSABLE				      = 0x10, /*unusable timeslot, such as ts0 of E1*/
	    XMS_DEVSUB_HIZ_CAS				      = 0x11, /*Hiz Cas*/
	    XMS_DEVSUB_HIZ_PRI				      = 0x12, /*Hiz Pri*/
	    XMS_DEVSUB_HIZ_SS7					  = 0x13, /*Hiz ss7*/
	    XMS_DEVSUB_HIZ_PRI_LINK			      = 0x14, /*Hiz pri link*/
	    XMS_DEVSUB_HIZ_SS7_64K_LINK  		  = 0x15, /*Hiz ss7 64k link*/
	    XMS_DEVSUB_HIZ_SS7_2M_LINK    		  = 0x16, /*Hiz ss7 2M link*/
	    XMS_DEVSUB_SS7_LINK		              = 0x17, /*ss7 link*/
	    XMS_DEVSUB_LINESIDE		              = 0x18, /*LineSide E1*/
	    XMS_DEVSUB_ANALOG_REC	              = 0x19, /*Analog phone Record*/
	    XMS_DEVSUB_HIZ_HDLC_N64K_LINK         = 0x1A, /*Hiz n*64K */
	    XMS_DEVSUB_SS7_2M_LINK                = 0x1B, /*SS7 2M LINK*/
	    XMS_DEVSUB_HIZ_HDLC                   = 0x1C, /*Hiz */
	    XMS_DEVSUB_DIGITAL_REC	              = 0x20, /*Digital phone Record*/
    };

    public enum XMS_MEDIA_DEVSUB_TYPE
    {
	    XMS_DEVSUB_MEDIA_VOC                 = 0x0,  /*voc device*/
	    XMS_DEVSUB_MEDIA_324                 = 0x1,  /*324 device*/
	    XMS_DEVSUB_MEDIA_RAW				 = 0x2,	 /*Raw device*/
    };

    public enum XMS_CTBUS_DEVSUB_TYPE
    {
	    XMS_DEVSUB_CTBUS_LINK                 = 0x0, /*CTBus link ts*/	
	    XMS_DEVSUB_CTBUS_CTX                  = 0x1, /*CTBus CTX ts*/	
    };

    public enum XMS_E1_TYPE
    {
	    XMS_E1_TYPE_Analog30	         = 1, /* Analog Interface 30*/
	    XMS_E1_TYPE_PCM31		         = 2, /* E1 Frame,ts31*/
	    XMS_E1_TYPE_PCM30		         = 3, /* E1 Frame,ts 30*/
	    XMS_E1_TYPE_CAS			         = 4, /* E1 Frame,CAS*/
	    XMS_E1_TYPE_PRI			         = 5, /* E1 Frame,PRI*/
	    XMS_E1_TYPE_SS7_TUP_0_Link	     = 6, /* E1 Frame,TUP: 0 link*/
	    XMS_E1_TYPE_SS7_TUP_1_Link	     = 7, /* E1 Frame,TUP: 1 link*/
	    XMS_E1_TYPE_SS7_TUP_2_Link	     = 8, /* E1 Frame,TUP: 2 link*/
	    XMS_T1_TYPE_D4	                 = 9, /* T1 Frame*/
	    XMS_T1_TYPE_ESF		             = 10, /* T1 Frame*/
	    XMS_J1_TYPE_D4		             = 11, /* J1 Frame*/
	    XMS_J1_TYPE_ESF		             = 12, /* J1 Frame*/
	    XMS_SLC_TYPE_96    	             = 13, /* SLC_96 Frame*/
	    XMS_E1_TYPE_SS7_ISUP_0_Link	     = 14, /* E1 Frame,ISUP: 0 link*/
	    XMS_E1_TYPE_SS7_ISUP_1_Link	     = 15, /* E1 Frame,ISUP: 1 link*/
	    XMS_E1_TYPESS7_ISUP_2_Link	     = 16, /*E1 Frame,ISUP: 2 link*/
	    XMS_E1_TYPE_6D25B		     = 17, /* E1 Frame, 6 DChannel,25 BChannel*/
	    XMS_E1_TYPE_1D30B                    = 18, /*E1 Frame, 1 DChannel, 30 BChannel*/
	    XMS_E1_TYPE_11D20B                   = 19, /*E1 Frame, 11 DChannel, 20 BChannel*/
	    XMS_E1_TYPE_HIZ_CAS                  = 20, /*E1 Frame, HIZ CAS*/
	    XMS_E1_TYPE_HIZ_PRI                  = 21, /*E1 Frame, HIZ PRI*/	
	    XMS_E1_TYPE_HIZ_SS7                  = 22, /*E1 Frame, HIZ SS7*/
	    XMS_E1_TYPE_HIZ_64K_SS7   	         = 23, /*E1 Frame, HIZ pure 64k SS7*/
	    XMS_E1_TYPE_HIZ_2M_SS7               = 24, /*E1 Frame, HIZ 2M SS7*/
	    XMS_E1_TYPE_LINESIDE                 = 25, /*E1 Frame, lineside*/
	    XMS_E1_TYPE_HIZ_N64K_HDLC            = 26, /*E1 Frame, HIZ N*64K HDLC*/	
	    XMS_E1_TYPE_2M_SS7									 = 27, /*E1 Frame, 2M SS7*/
    };

    /*E1 STATE BITS DEFINE*/
    public enum XMS_E1PORT_MASK_STATE
    {
	    XMS_E1PORT_MASK_LOST_SIGNAL	     = 0x00000001,
	    XMS_E1PORT_MASK_FAS_ALARM	     = 0x00000002,
	    XMS_E1PORT_MASK_MFAS_ALARM	     = 0x00000004,
	    XMS_E1PORT_MASK_CRC4_ALARM	     = 0x00000008,
	    XMS_E1PORT_MASK_REMOTE_ALARM	 = 0x00000010,
	    XMS_E1PORT_MASK_REMOTE_MF_ALARM	 = 0x00000020,
	    XMS_E1PORT_MASK_TX_OPEN_ALARM	 = 0x00000040,
	    XMS_E1PORT_MASK_TX_SHORT_ALARM	 = 0x00000080,
	    XMS_E1PORT_MASK_RX_LEVEL	     = 0x00000F00,
	    XMS_E1PORT_MASK_TYPE		     = 0x00FF0000,
    };

    public enum XMS_VOIP_PROTOCOL_TYPE
    {
	    XMS_VOIP_PROTOCOL_H323           = 0x1, /*VoIP H323 protocol*/
	    XMS_VOIP_PROTOCOL_SIP            = 0x2, /*VoIP SIP protocol*/
    };

    public enum XMS_VOC_SRC_MODE
    {
	    XMS_SRC_8K                       = 0x0,
	    XMS_SRC_6K                       = 0x1,
	    XMS_SRC_GTG                      = 0x2,
	    XMS_SRC_FSK                      = 0x3,
	    XMS_SRC_RTP                      = 0x4,
	    XMS_SRC_FAX                      = 0x5,
	    XMS_SRC_3GVIDEO                  = 0x6,
	    XMS_SRC_11K                      = 0x7,
	    XMS_SRC_FAX_ECM                  = 0x8,
    };

    public enum XMS_VOC_CODE_TYPE
    {
	    XMS_Alaw_type                    = 0x0,
	    XMS_Ulaw_type                    = 0x1,
	    XMS_Vox_type                     = 0x2,
	    XMS_Linear_8bit                  = 0x3,
	    XMS_Linear_16bit                 = 0x4,
	    XMS_Amr_type                     = 0x5,
	    XMS_G723_type                    = 0x6,
	    XMS_CODE_STREAM                  = 0x7,
    };

    public enum XMS_PLAYREC_STOP_MODE
    {
	    XMS_Normal_Stop                  = 0x0,
	    XMS_Single_Code                  = 0x1,
	    XMS_Any_Code                     = 0x2,
    };

    public enum XMS_CSPREC_TYPE
    {
	    XMS_CSPREC_NONE                  = 0x0,
	    XMS_CSPREC_BARGEIN               = 0x1,
	    XMS_CSPREC_NON_BARGEIN           = 0x2,
    };
    
    public enum XMS_CSPREC_PRIV_TYPE
		{
			XMS_CSPREC_PRIV_CMD              = 0x0,
		};
		
		public enum XMS_CSPREC_CMD_OPT
		{
			XMS_CSPREC_CMD_NORMAL            = 0x0,
			XMS_CSPREC_CMD_DIRECT            = 0x1,
		};
		
		public enum XMS_CONTROL_CSPREC_PRIV_TYPE
		{
			XMS_CONTROL_CSPREC_PRIV_CMD      = 0x0,
		};
		
		public enum XMS_CONTROL_CSPREC_CMD_OPT
		{
			XMS_CONTROL_CSPREC_CMD_NORMAL    = 0x0,
			XMS_CONTROL_CSPREC_CMD_DIRECT    = 0x1,
		};

    public const int XMS_MAX_PLAY_QUEUE_NUM = 255;

    public enum XMS_PLAY_TYPE
    {
	    XMS_PLAY_TYPE_FILE               = 0x0,
	    XMS_PLAY_TYPE_INDEX              = 0x1,
	    XMS_PLAY_TYPE_FILE_QUEUE         = 0x2,
	    XMS_PLAY_TYPE_INDEX_QUEUE        = 0x3,
    };

    public const int XMS_MAX_IDNEX_TABLE_NUM = 1024;
     
    public enum XMS_BUILD_INDEX_TYPE
    {
	    XMS_BUILD_INDEX_RAM              = 0x4,
	    XMS_BUILD_INDEX_FILE             = 0x5,
    };

    public enum XMS_CFG_TYPE
    {
	    XMS_CFG_TYPE_NON_INDEX           = 0x0,
	    XMS_CFG_TYPE_INDEX               = 0x1,
    };

    public enum XMS_CTRL_PLAY_TYPE
    {
	    XMS_STOP_PLAY                    = 0x0,
	    XMS_PAUSE_PLAY                   = 0x1,
	    XMS_RESUME_PLAY                  = 0x2,
	    XMS_STEP_BACKWARD_PLAY           = 0x3,
	    XMS_STEP_FORWARD_PLAY            = 0x4,

	    XMS_CSP_STOP_PLAY                = 0x5,
	    XMS_CSP_PAUSE_PLAY               = 0x6,
	    XMS_CSP_RESUME_PLAY              = 0x7,
	    XMS_CSP_STEP_BACKWARD_PLAY       = 0x8,
	    XMS_CSP_STEP_FORWARD_PLAY        = 0x9,
	    XMS_CSP_DELAY_STOP_PLAY          = 0xA,
    };

    public enum XMS_PLAY_GAIN_MODE
    {
	    XMS_PLAY_GAIN_MODE_NOCHANGE     = 0x0,
	    XMS_PLAY_GAIN_MODE_FIX          = 0x1,
	    XMS_PLAY_GAIN_MODE_ALS          = 0x2,
	    XMS_PLAY_GAIN_MODE_AGC          = 0x3,
    };

    public enum XMS_VOC_OUTPUT_TYPE
    {
	    XMS_VOC_OUTPUT_SILENCE           = 0x0,
	    XMS_VOC_OUTPUT_FROM_INPUT        = 0x1,
	    XMS_VOC_OUTPUT_FROM_PLAY         = 0x2,
	    XMS_VOC_OUTPUT_FROM_MIXER        = 0x3, 	
    };

    public enum XMS_MIXER_TYPE
    {
	    XMS_MIXER_FROM_NULL              = 0x00,
	    XMS_MIXER_FROM_INPUT             = 0x01,
	    XMS_MIXER_FROM_PLAY              = 0x02,
	    XMS_MIXER_FROM_CONF              = 0x03,
	    XMS_MIXER_FROM_IP                = 0x04,
	    XMS_MIXER_FROM_324               = 0x05,
	    XMS_MIXER_FROM_RTPX              = 0x06,
    };

    public enum XMS_AGC_MODE
    {
	    XMS_AGC_MODE_ALS		          = 0x00,
	    XMS_AGC_MODE_AGC		          = 0x01,
    };

    public enum XMS_EC_REF
    {
	    XMS_EC_REF_FROM_INPUT		      = 0x00,
	    XMS_EC_REF_FROM_OUTPUT		      = 0x01,
    };

    public enum XMS_CONF_INPUT_OPT
    {
	    XMS_CONF_INPUT_OPT_SILENCE        = 0x0,
	    XMS_CONF_INPUT_OPT_NORMAL         = 0x1,
	    XMS_CONF_INPUT_OPT_PLAY           = 0x2,	
    };

    public enum XMS_CONF_OUTPUT_OPT
    {
	    XMS_CONF_OUTPUT_OPT_SILENCE		  = 0x0,
	    XMS_CONF_OUTPUT_OPT_NORMAL	      = 0x1,
	    XMS_CONF_OUTPUT_OPT_SUM	          = 0x2,
    };

    public enum XMS_CTRL_RECORD_TYPE
    {
	    XMS_STOP_RECORD                   = 0x0,
	    XMS_PAUSE_RECORD                  = 0x1,
	    XMS_RESUME_RECORD                 = 0x2,
	    XMS_STEP_BACKWARD_RECORD          = 0x3,

	    XMS_CSP_STOP_RECORD               = 0x4,
	    XMS_CSP_PAUSE_RECORD              = 0x5,
	    XMS_CSP_RESUME_RECORD             = 0x6,
	    XMS_CSP_STEP_BACKWARD_RECORD      = 0x7,
    };
    
    public enum XMS_REC_DELAY_STOP_SWITCH
		{
			XMS_REC_DELAY_STOP_DISABLE        = 0x0,
			XMS_REC_DELAY_STOP_ENABLE         = 0x1,
		};

    public enum XMS_REC_OPENFILE_TYPE
    {
	    XMS_REC_FILE_TRUNC                = 0x0,
	    XMS_REC_FILE_APPEND               = 0x1,
    };

    public enum XMS_AUDIO_TRACKS
    {
	    XMS_AUDIO_TRACKS_MONO             = 0x1,
	    XMS_AUDIO_TRACKS_STEREO           = 0x2,
    };

    public enum XMS_VIDEO_CODE_TYPE
    {
	    XMS_VIDEO_CODE_TYPE_H263P      = 0x1,
        XMS_VIDEO_CODE_TYPE_H263       = 0x2,
        XMS_VIDEO_CODE_TYPE_MP4V       = 0x3,   
	    XMS_VIDEO_CODE_TYPE_H264       = 0x4,
    };

    public enum XMS_AUDIO_AMR_FRAME_TYPE
    {
	    XMS_AMR_FRAME_TYPE_4_75              = 0x0,
	    XMS_AMR_FRAME_TYPE_5_15              = 0x1,
	    XMS_AMR_FRAME_TYPE_5_90              = 0x2,
	    XMS_AMR_FRAME_TYPE_6_70              = 0x3,
	    XMS_AMR_FRAME_TYPE_7_40              = 0x4,
	    XMS_AMR_FRAME_TYPE_7_95              = 0x5,
	    XMS_AMR_FRAME_TYPE_10_2              = 0x6,
	    XMS_AMR_FRAME_TYPE_12_2              = 0x7,
	    XMS_AMR_FRAME_TYPE_AMR_SID           = 0x8,
	    XMS_AMR_FRAME_TYPE_GSM_EFR_SID       = 0x9,
	    XMS_AMR_FRAME_TYPE_TDMA_EFR_SID      = 0xA,
	    XMS_AMR_FRAME_TYPE_PDC_EFR_SID       = 0xB,
	    XMS_AMR_FRAME_TYPE_RESERVED1         = 0xC,
	    XMS_AMR_FRAME_TYPE_RESERVED2         = 0xD,
	    XMS_AMR_FRAME_TYPE_RESERVED3         = 0xE,
	    XMS_AMR_FRAME_TYPE_NO_DATA           = 0xF,
    };

    public enum XMS_CSPPLAY_DATA_TYPE
    {
	    XMS_CSPPLAY_DATA_VOC                 = 0x0,
	    XMS_CSPPLAY_DATA_VIDEO               = 0x1,
    };

    public enum XMS_PRIVATE_EXT_TYPE
    {
      XMS_EXT_TYPE_PATH                    = 0x01,             //extend to path's size from 128 to 260
    };
    public enum XMS_BOARD_PRIVATE_EXT_TYPE
    {
    	XMS_BOARD_EXT_TYPE_NULL              = 0x00,             //nothing will excute
      XMS_BOARD_EXT_TYPE_CLOCK             = 0x01,             //extend to main clock in keygoe system
    };

    public enum XMS_BOARD_EXT_CLOCK_TYPE
    {
      XMS_BOARD_EXT_CLOCK_TYPE_SLAVE       = 0x01,             //current board set slave clock to the peer CO
      XMS_BOARD_EXT_CLOCK_TYPE_MASTER      = 0x02,             //current board set master clock to the peer CO         
    };

    public enum XMS_BOARD_CLOCK_MODE
    {
    	XMS_BOARD_CLOCK_MODE_MANUAL          = 0x00,     //clock set by user-app
    	XMS_BOARD_CLOCK_MODE_AUTO            = 0x01,     //clock set by Keygoe
    };

    public enum XMS_ANALOG_TRUNK_CALLERID_OPT
    {
	    XMS_ANALOG_TRUNK_CALLERID_DISABLE      = 0x0,
	    XMS_ANALOG_TRUNK_CALLERID_FSK          = 0x1,
	    XMS_ANALOG_TRUNK_CALLERID_DTMF         = 0x2,
	    XMS_ANALOG_TRUNK_CALLERID_FSKORDTMF    = 0x3,
    };

    public enum XMS_ANALOG_TRUNK_DIALTONE_DETECT_OPT
    {
	    XMS_ANALOG_TRUNK_DIALTONE_DONTDETECT   = 0x0,
	    XMS_ANALOG_TRUNK_DIALTONE_DETECT       = 0x1,
    };

    public enum XMS_ANALOG_TRUNK_CALLOUT_METHOD_OPT
    {
	    XMS_ANALOG_TRUNK_CALLOUT_APP_FULLCONTROL     = 0x0,
	    XMS_ANALOG_TRUNK_CALLOUT_NORMAL_PROGRESS     = 0x1,
	    XMS_ANALOG_TRUNK_CALLOUT_POLARITY_REVERSE    = 0x2,
    };

    public enum XMS_ANALOG_USER_CALLERID_OPT
    {
	    XMS_ANALOG_USER_CALLERID_DSIABLE            = 0x0,
	    XMS_ANALOG_USER_CALLERID_FSK                = 0x1,
	    XMS_ANALOG_USER_CALLERID_DTMF               = 0x2,
    };

    public enum XMS_ANALOG_USER_RINGCADENCE_TYPE
    {
	    XMS_ANALOG_USER_RINGCADENCE_SINGLEPULSE    = 0x0,
	    XMS_ANALOG_USER_RINGCADENCE_DOUBLEPULSE    = 0x1,
	    XMS_ANALOG_USER_RINGCADENCE_TRIPLEPULSE    = 0x2,
    };

    public enum XMS_ANALOG_USER_CALLIN_METHOD_TYPE
    {
	    XMS_ANALOG_USER_CALLIN_METHOD_APP_FULLCONTROL    = 0x0,
	    XMS_ANALOG_USER_CALLIN_METHOD_AUTO_RECVCALLEE    = 0x1,
    };

    public const int  ACS_SNAPSHOT_ALL = 0x0;
    public const int  ACS_SNAPSHOT_INTERFACE = 0x1;
    public const int  ACS_SNAPSHOT_VOC = 0x2;
    public const int  ACS_SNAPSHOT_CTBUS = 0x3;
    public const int  ACS_SNAPSHOT_VOIP = 0x4;
    public const int  ACS_SNAPSHOT_CONFERENCE = 0x5;
    public const int  ACS_SNAPSHOT_VIDEO = 0x6;

    public enum XMS_FAX_MODEM_TYPE
    {
	    XMS_F48_Modem                        = 0x0,
	    XMS_F96_Modem                        = 0x1,
	    XMS_F144_Modem                       = 0x2,
    };

    public enum XMS_FAX_BPS_TYPE
    {
	    XMS_BPS_2400                         = 0x0,
	    XMS_BPS_4800                         = 0x1,
	    XMS_BPS_7200                         = 0x2,
	    XMS_BPS_9600                         = 0x3,
	    XMS_BPS_12000                        = 0x4,
	    XMS_BPS_14400                        = 0x5,
    };

    public enum XMS_FAX_T4_TYPE
    {
	    XMS_T4_Low_Dencity                   = 0x0,
	    XMS_T4_High_Dencity                  = 0x1,
	    XMS_T4_MH_Encode                     = 0x0,
	    XMS_T4_MR_Encode                     = 0x1,
    };

    public const int  T6_Encode = 0x2;

    public enum XMS_FAX_LINE_PIXEL_TYPE
    {
	    XMS_Line_Pixel_1728                  = 0x0,
	    XMS_Line_Pixel_2048                  = 0x1,
	    XMS_Line_Pixel_2432                  = 0x2,
	    XMS_Line_Pixel_3456                  = 0x3,
	    XMS_Line_Pixel_4096                  = 0x4,
	    XMS_Line_Pixel_4864                  = 0x5,
    };

    public enum XMS_FAX_PAGE_LENGTH
    {
	    XMS_Page_Length_A4                   = 0x0,	
	    XMS_Page_Length_B4                   = 0x1,
	    XMS_Page_Length_Unlinit              = 0x2,
    };

    public enum XMS_FAX_SCANLINE_TIME
    {
	    XMS_Scanline_Time_0                  = 0x0,
	    XMS_Scanline_Time_5                  = 0x1,
	    XMS_Scanline_Time_10                 = 0x2,	
	    XMS_Scanline_Time_20                 = 0x3,
	    XMS_Scanline_Time_40                 = 0x4,
    };

    public enum XMS_FAX_HOSTCTRL_TYPE
    {
	    XMS_Fax_Null                         = 0x0,
	    XMS_Fax_Recv                         = 0x1,
	    XMS_Fax_Send                         = 0x2,
	    XMS_Fax_Stop                         = 0x3,
    };

    public enum XMS_FAX_WORKMODE
    {	
	    XMS_FAX_WORKMODE_NORMAL              = 0x00,
	    XMS_FAX_WORKMODE_SERVER              = 0x01,
	    XMS_FAX_WORKMODE_GATEWAY             = 0x02,
    };

    public enum XMS_FAX_ECM_MODE_TYPE
    {
	    XMS_FAX_ECM_MODE_TYPE_NORMAL         = 0x00,
	    XMS_FAX_ECM_MODE_TYPE_ECM            = 0x01,	
    };

    public enum XMS_ANSWERCALL_TYPE
    {
	    XMS_ANSWERCALL_ANC                   = 0x0,
	    XMS_ANSWERCALL_ANN                   = 0x1,
	    XMS_ANSWERCALL_CON                   = 0x2,
    };

    public enum XMS_CTX_REG_TYPE
    {
	    XMS_CTX_REG                     = 0x1,/*ctx reg*/
	    XMS_CTX_UNREG                   = 0x2,/*ctx unreg*/
    };

    public enum XMS_CTX_LINK_OPTION
    {
	    CTX_LINK_OPTION_RESET			= 0x1,/*reset all link*/
	    CTX_LINK_OPTION_LINK			= 0x2,/*single link*/
	    CTX_LINK_OPTION_UNLINK			= 0x3,/*single unlink*/
	    CTX_LINK_OPTION_DUALLINK		= 0x4,/*dual link*/
	    CTX_LINK_OPTION_DUALUNLINK		= 0x5,/*dual unlink*/
    };

    public enum XMS_MEDIA_TYPE
    {
	    MEDIA_TYPE_AUDIO               = 0,   /*play audio only*/
	    MEDIA_TYPE_VIDEO               = 1,   /*play video only*/
	    MEDIA_TYPE_ANV                 = 4,   /*play audio and video*/
	    MEDIA_TYPE_MEDIAEX_AUDIO			 = 5,	/*use mediaex play audio*/
	    MEDIA_TYPE_MEDIAEX_VIDEO			 = 6,	/*use mediaex play video*/
	    MEDIA_TYPE_MEDIAEX_ANV				 = 7,	/*use mediaex play audio and video*/
    };

    public enum XMS_SS7_FRAME_USER_TYPE
    {
	    XMS_SS7_USER_SCCP = 0x03,
	    XMS_SS7_USER_TUP  = 0x04,
	    XMS_SS7_USER_ISUP = 0x05,
    };
     
    public enum XMS_SS7_FRAME_LINK_TYPE
    {
	    XMS_SS7_LINK_ITU  = 0x02,
	    XMS_SS7_LINK_CHINA= 0x04,
    };
     
    public enum XMS_SS7_FRAME_INFO_TYPE
    {
	    XMS_SS7_INFO_DATA   = 0x01,
	    XMS_SS7_INFO_CMD    = 0x02, 
    };

    public enum XMS_SYSMON_MODSTATE
    {   
	    SYSMON_MODSTATE_DISCONNECT      = 0x0,/*Module disconnect*/
        SYSMON_MODSTATE_CONNECT         = 0x1,/*Module connect*/    
    };

    /*#define  FetchEventData(pAcsEvt)    ((DJ_S8 *)pAcsEvt + sizeof(Acs_Evt_t));
    #define  FetchDeviceList(pAcsEvt)   ((DJ_S8 *)FetchEventData(pAcsEvt) + sizeof(Acs_Dev_List_Head_t));
    #define  FetchIOData(pAcsEvt)       ((DJ_S8 *)FetchEventData(pAcsEvt) + sizeof(Acs_IO_Data))
    #define  FetchParamData(pAcsEvt)    ((DJ_S8 *)FetchEventData(pAcsEvt) + sizeof(Acs_ParamProc_Data))*/

    /*UserLedCtrl*/
    public struct UserLedCtrl
    {
    	public DJ_U8	m_u8LedTimeEnable;       /*Led ontime & offtime ctrl paramter enable? */	
    	public DJ_S8   m_Rfu1;
    	public DJ_U16	m_u16OnTime;             /*LED ontime: 100~2000 ms*/
    	public DJ_U16	m_u16OffTime;            /*LED offtime: 100~2000 ms*/
    	public DJ_U8   m_u8WatchDogOutEnbale;   /*LED watchdog out time ctrl paramter enable? */
    	public DJ_S8   m_Rfu2;
    	public DJ_U16	m_u16WatchDogOutTime;    /*LED watchdog out time: 10~300 S*/
    	public DJ_U8   m_u8WatchDogTimeEnable;  /*LED watchdog out state ctrl paramter enable? */
    	public DJ_S8   m_Rfu3;
    	public DJ_U16	m_u16WatchDogOnTime;     /*LED watchdog ontime: 100~2000 ms*/
    	public DJ_U16	m_u16WatchDogOffTime;    /*LED watchdog offtime: 100~2000 ms*/
	    public DJ_U8   m_u8FeedWatchDogEnable;  /*LED watchdog feed ? 0: feed not enable, 1: feed*/
    	public fixed DJ_S8   m_Rfu4[3];
    };/*UserLedCtrl*/

    /*Acs_AnalogMEG_CMD*/
    public struct Acs_AnalogMEG_CMD
    {
      public DJ_U8	m_u8Channel_Enable;
	    public DJ_U8	m_u8CallOut;
    	public DJ_U8	m_u8RingTime;
    	public DJ_U8	m_u8Reservered;
    };/*Acs_AnalogMEG_CMD*/

    /*ACS server parm*/
    public struct ServerID_t
    {
	    public fixed DJ_S8    m_s8ServerIp[32]; /*XMS server ip*/
	    public DJ_U32   m_u32ServerPort;  /*XMS server port*/
	    public fixed DJ_S8    m_s8UserName[32]; /**/
        public fixed DJ_S8    m_s8UserPwd[32];  /**/
    };

    /*privatedata*/
    public struct PrivateData_t
    {
	    public DJ_U32   m_u32DataSize; /*private data size*/
    };/*PrivateData_t*/

    /*CallID*/
    public struct CallID_t
    {
        public FlowType_t      m_s32FlowType;    /*CallType*/
        public FlowChannel_t   m_s32FlowChannel; /*Call Channel*/
    };/*CallID_t*/

    /*DeviceID_t*/
    public struct DeviceID_t
    {   
	    public DeviceMain_t    m_s16DeviceMain;  /*device main type*/
        public DeviceSub_t     m_s16DeviceSub;   /*device sub type*/
        public ModuleID_t      m_s8ModuleID;     /*device module ID*/
	    public DJ_S8           m_s8MachineID;    /*device machine ID*/
        public ChannelID_t     m_s16ChannelID;   /*device channel ID*/
        public DeviceGroup_t   m_s16DeviceGroup; /*device group ID*/	
	    public fixed DJ_S8           m_Rfu2[2];        /*Reserved*/
	    public CallID_t        m_CallID;         /*Serveice ID*/
    };/*DeviceID_t*/

    /*Acs_Evt_t*/
    public struct Acs_Evt_t
    {
	    public ACSHandle_t		  m_s32AcsHandle;       /*acs handle*/	
	    public DeviceID_t        m_DeviceID;           /*Device ID*/
	    public DJ_S32            m_s32EvtSize;         /*Evt size*/
	    public EventType_t		  m_s32EventType;       /*event type code*/
	    public DJ_U32            m_u32EsrParam;        /*App esr param*/
    };/**/

    /*ACS Event Head*/
    public struct ACS_EVT_HEAD
    {
	    public PKG_HEAD_STRUCT  m_PkgEvtHead;  /*ITP package head*/
	    public Acs_Evt_t        m_AcsEvt_t;    /*acs event package head*/
    };/**/

    /*ACS playpropetry*/
    public struct PlayProperty_t
    {	
	    public DJ_U8                m_u8TaskID;         /*play task ID*/	
	    public DJ_U8                m_u8SrcMode;        /*file src mode, reference XMS_VOC_SRC_MODE*/
	    public DJ_U8                m_u8DecodeType;     /*decode type, reference XMS_VOC_CODE_TYPE*/	
	    public fixed DJ_S8                m_s8Rfu1[1];        /*Reserved*/
	    public DJ_U32               m_u32MaxSize;       /*play max size(BYTES),  0: file real size; >0: max play size*/
	    public DJ_U32               m_u32MaxTime;       /*play max time(Seconds) 0: file real seconds; >0: max play seconds*/	
	    public DJ_U32               m_u32StopMode;      /*stop play mode,referecne XMS_PLAYREC_STOP_MODE*/
	    public DJ_U32               m_u32StopCode;      /*stop play when receive this dtmf code*/
	    public DJ_U16               m_u16FileOffset;    /*start play at the file offset*/
	    public DJ_U16               m_u16PlayType;      /*play type: 0-normal,1-index,referecnce XMS_PLAY_TYPE*/
	    public DJ_U16               m_u16PlayIndex;     /**/
	    public fixed DJ_S8                m_s8PlayContent[ACS_MAX_FILE_NAME_LEN];/*play file name */
	    public DJ_U16               m_u16FileSubOffset; /*start play at the offset from m_u16FileOffset, and the granularity is 1 bytes, fileOffSet = m_u16FileOffset*8K + m_u16FileSubOffset*/
    };/*PlayProperty_t*/

    /*ACS CSPPlayProperty_t*/
    public struct CSPPlayProperty_t
    {	
	    public DJ_U8                m_u8TaskID;         /*play task ID*/	
	    public DJ_U8                m_u8SrcMode;        /*file src mode, reference XMS_VOC_SRC_MODE*/
	    public DJ_U8                m_u8DecodeType;     /*decode type, reference XMS_VOC_CODE_TYPE*/	
	    public fixed DJ_S8                m_s8Rfu1[1];        /*Reserved*/
	    public DJ_U32               m_u32MaxSize;       /*play max size(BYTES),  0: file real size; >0: max play size*/
	    public DJ_U32               m_u32MaxTime;       /*play max time(Seconds) 0: file real seconds; >0: max play seconds*/	
	    public DJ_U32               m_u32StopMode;      /*stop play mode,referecne XMS_PLAYREC_STOP_MODE*/
	    public DJ_U32               m_u32StopCode;      /*stop play when receive this dtmf code*/
	    public fixed DJ_S8                m_Rfu1[4];			
    };/*CSPPlayProperty_t*/

    /*CSPPlayDataInfo_t*/
    public struct CSPPlayDataInfo_t
    {
	    public DJ_U16	m_u16DataLen;   		/*data length*/
	    public DJ_U8	m_u8DataType;		    /*data type,0: voc,1:video,reference XMS_CSPPLAY_DATA_TYPE*/
	    public DJ_U8	m_u8TaskID;	  		    /*task id*/
    };/*CSPPlayDataInfo_t*/

    /*ACS play3gpppropetry*/
    public struct Play3gppProperty_t
    {	
	    public DJ_U8                m_u8TaskID;              /*audio: play task ID*/	
	    public DJ_U8                m_u8SrcMode;             /*audio: file src mode, reference XMS_VOC_SRC_MODE*/
	    public DJ_U8                m_u8DecodeType;          /*audio: decode type, reference XMS_VOC_CODE_TYPE*/	
	    public DJ_S8                m_u8Audio_tracks;        /*audio: audio tracks*/
	    public DJ_S8                m_u8AmrFrameType;        /*audio: amr frame type*/
	    public DJ_U8                m_u8AudioNoDecode;       /*audio: FALSE: AMR to line-decodetype(default value); TRUE: No decode;*/
	    public fixed DJ_U8                m_u8Rfu1[2];             /*reserved*/
	    public DJ_U32               m_u32MaxTime;            /*audio: play max time(Seconds) 0: file real seconds; >0: max play seconds*/	
	    public DJ_U32               m_u32StopMode;           /*audio: stop play mode,referecne XMS_PLAYREC_STOP_MODE*/
	    public DJ_U32               m_u32StopCode;           /*audio: stop play when receive this dtmf code*/
	    public DJ_U16               m_u16TimeOffset;         /*audio: start play at the file offset with time*/
	    public DJ_U16               m_u16PlayType;           /*audio: play type: 0-normal,1-index,referecnce XMS_PLAY_TYPE*/
	    public DJ_U16               m_u16PlayIndex;          /*audio: play index*/
	    public DJ_S16               m_s16Rfu2;               /*Reserved*/
	    public fixed DJ_S8                m_s8PlayContent[ACS_MAX_FILE_NAME_LEN];/*audio: play file name */
	    public DJ_U8                m_u8VideoFrameRate;      /*video frame rate*/
	    public DJ_U8	             m_u8VideoDecode_Type;    /*video: video decode type*/
	    public DJ_U8	             m_u8VideoHigh;           /*video: video high*/
	    public DJ_U8	             m_u8VideoWidth;          /*video: video width*/	
	    public DJ_U32               m_u32VideoMaxTime;       /*video: play max time(Seconds) 0: file real seconds; >0: max play seconds*/	
	    public DJ_U16               m_u16VideoTimeOffset;    /*video: start play at the file offset with time*/
	    public DJ_U16               m_u16VideoPlayType;      /*video: play type: 0-normal,1-index,referecnce XMS_PLAY_TYPE*/
	    public DJ_U16               m_u16VideoPlayIndex;     /*video: play index*/
	    public DJ_U8                m_u8VideoTaskID;         /*video: play video task ID*/
	    public DJ_U8                m_u8MediaType;           /*common: media type XMS_MEDIA_TYPE*/        
	    public fixed DJ_S8                m_s8VideoPlayContent[ACS_MAX_FILE_NAME_LEN];/*video: play file name */
    	
    };/*PlayProperty_3gp_t*/

    /*混音通道属性*/
    public struct MixerControlParam_t
    {
	    public DJ_U8	m_u8SRC1_Ctrl;  /*reference XMS_MIXER_TYPE*/
	    public DJ_U8	m_u8SRC2_Ctrl;  /*reference XMS_MIXER_TYPE*/
	    public DJ_U16	m_u16SRC_ChID1; /*Media ChID1*/
	    public DJ_U16	m_u16SRC_ChID2; /*Media ChID2*/
	    public DJ_U8	m_u8Video;
	    public DJ_S8   m_s8Rfu;     /*Rfu*/
    };/*MixerControl_t*/


    /*ACS record file propetry*/
    public struct RecordProperty_t
    {	
	    public DJ_U32                m_u32MaxSize;    /* record max size, 0: no limit file size; >0: record max size*/
	    public DJ_U32                m_u32MaxTime;    /* record max time, 0: no limit record time; >0: record max time*/	
	    public DJ_U8	              m_u8EncodeType;  /* encode type, reference XMS_VOC_CODE_TYPE*/	
	    public DJ_U8	              m_u8SRCMode;     /*file src mode, reference XMS_VOC_SRC_MODE*/
	    public DJ_U8	              m_u8StopMode;    /*stop record mode,referecne XMS_PLAYREC_STOP_MODE*/
	    public DJ_U8	              m_u8StopCode;	   /*stop record when receive this dtmf code*/
	    public DJ_S8                 m_s8IsMixEnable; /*is Mix*/
	    public DJ_U8                 m_u8TaskID;      /*change from Reserved to m_u8TaskID on 090112*/
	    public MixerControlParam_t   m_MixerControl;  /*Mixer Contronl parameter*/
	    public DJ_S8                 m_s8IsAppend;    /*0: trunc record file; 1: append record file,reference XMS_REC_OPENFILE_TYPE*/
	    public fixed FilePath_t            m_s8FileName[MAX_PATH];/*record file name*/
	    public fixed DJ_S8                 m_s8Rfu2[1];      /*Reserved*/
    };/*RecordProperty_t*/

    /*ACS 3gpp record propetry*/
    public struct Record3gppProperty_t
    {
	    public DJ_U32                m_u32MaxTime;          /*record max time, 0: no limit record time; >0: record max time*/	
	    public DJ_U8	              m_u8StopMode;          /*stop record mode,referecne XMS_PLAYREC_STOP_MODE*/	
	    public DJ_U8	              m_u8StopCode;	         /*stop record when receive this dtmf code*/

	    public DJ_S8                 m_s8IsAppend;          /*0: trunc record file; 1: append record file,reference XMS_REC_OPENFILE_TYPE*/	
	    public DJ_U8	              m_u8AudioEncodeType;  /*encode type, reference XMS_VOC_CODE_TYPE*/	
	    public DJ_U8	              m_u8AudioSRCMode;     /*file src mode, reference XMS_VOC_SRC_MODE*/
	    public DJ_S8                 m_u8AudioTracks;      /*audio channel,reference XMS_AUDIO_TRACKS*/
        public DJ_U16                m_u16AudioMaxBitRate; /*audio max bitrate,0~65535*/
        public DJ_U16                m_u16AudioAverageBitRate;/*audio average bitrate,0~65535*/
	    public DJ_S8                 m_u8MediaType;
	    public DJ_S8                 m_s8AudioIsMixEnable; /*is Mix, 0 : no mix,1: mix*/
	    public MixerControlParam_t   m_AudioMixerControl;  /*Mixer Contronl parameter*/
    	
	    public DJ_U8	              m_u8VideoEncodeType;  /*encode type, reference XMS_VIDEO_CODE_TYPE*/	
	    public DJ_U8	              m_u8VideoFrameRate;   /*video frame rate,10~30*/
	    public DJ_U16                m_u16VideoWidth;      /*video width,176*/
	    public DJ_U16                m_u16VideoHeight;     /*video heigth,144*/
	    public DJ_U16                m_u16VideoMaxBitRate; /*video max bit rate,0~65535*/
	    public DJ_U16                m_u16VideoAverageBitRate;/*video average bit rate,0~65535*/
	    public DJ_U8                 m_Rfu2;
	    public DJ_S8                 m_s8VideoIsMixEnable; /*is Mix, 0 : no mix,1: mix*/
	    public MixerControlParam_t   m_VideoMixerControl;  /*Mixer Contronl parameter*/

	    public DJ_U8                 m_u8AudioProfiles;    /*audio profiles?*/
        public DJ_U8                 m_u8AudioLevel;       /*audio level ?*/
	    public DJ_U16                m_u16AudioDecoderCfgLen;/*audio decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
	    public fixed DJ_U8                 m_u8AudioDecoderCfg[ACS_MAX_DECODER_CFG_LEN];/*audio decoder cfg*/
    	
	    public DJ_U8                 m_u8VideoProfiles;    /*video profiles?*/
	    public DJ_U8                 m_u8VideoLevel;       /*video level?*/	
	    public DJ_U16                m_u16VideoDecoderCfgLen;  /*video decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
	    public fixed DJ_U8                 m_u8VideoDecoderCfg[ACS_MAX_DECODER_CFG_LEN];/*video decoder cfg?*/
	    public fixed FilePath_t            m_s8FileName[MAX_PATH];/*record file name*/
    };/*Record3gpProperty_t*/

    /*ACS record Ram propetry*/
    public struct RecordCSPProperty_t
    {	
	    public DJ_U8	              m_u8EncodeType;  /* encode type, reference XMS_VOC_CODE_TYPE*/	
        public DJ_U8	              m_u8SRCMode;     /*file src mode, reference XMS_VOC_SRC_MODE*/
	    public DJ_U16                m_u16PacketLen;  /*Record Packet Length*/
	    public DJ_U8                 m_u8CSPRecType;  /*1: barge-in, 2: non barge-in, reference XMS_CSPREC_TYPE*/
	    public fixed DJ_S8                 m_s8Rfu1[3];
    };/*RecordCSPProperty_t*/

    /*control play */
    public struct ControlPlay_t
    {
	    public DJ_U16             m_u16ControlType;  /*play control type,reference XMS_CTRL_PLAY_TYPE*/
	    public DJ_U16             m_u16StepSize;     /*play step size*/
	    public DJ_U16             m_u16TuneType;     /*tune type,reserved*/
	    public DJ_U16             m_u16SpeedSize;    /*speed size,reserved*/
    };/*ControlPlay_t*/

    /*control 3gpp play */
    public struct Control3gppPlay_t
    {
	    public DJ_U16             m_u16ControlType;  /*play control type,reference XMS_CTRL_PLAY_TYPE*/
	    public DJ_U16             m_u16StepTime;     /*play step time*/
	    public DJ_U16             m_u16TuneType;     /*tune type,reserved*/
	    public DJ_U16             m_u16SpeedSize;    /*speed size,reserved*/
	    public DJ_U8              m_u8MediaType;     /*media type: 0: audio; 1: video; 4: A & V*/
	    public fixed DJ_U8              m_u8Reserv1[3];    /*reserve*/
    };/*Control3gppPlay_t*/


    /*ACS control record */
    public struct ControlRecord_t
    {
	    public DJ_U32             m_u32ControlType;  /*control record type,reference XMS_CTRL_RECORD_TYPE*/
	    public DJ_U32             m_u32StepSize;     /*step size*/
	    public DJ_U32             m_u32DelayStop;    /*Delay to stop record,reference to XMS_REC_DELAY_STOP_SWITCH*/
    };/*ControlRecord_t*/

    /*ACS control 3gpp record */
    public struct Control3gppRecord_t
    {
     	public DJ_U16             m_u32ControlType;  /*control record type,reference XMS_CTRL_RECORD_TYPE*/
    	public DJ_U8              m_u8MediaType;     /*media type: reference to XMS_MEDIA_TYPE*/
    	public DJ_U8              m_u8Reserv1;    /*reserve*/
     	public DJ_U32             m_u32StepTime;     /*step time*/
      public DJ_U32             m_u32SpeedSize;    /*speed size,reserved*/
    };/*Control3gpRecord_t*/

    /*ACS Get 3GPP file config add by fys*/
    public struct Get3gppCfg_t
    {
	    public DJ_U8              m_u8MediaType;                /*media type: XMS_MEDIA_TYPE*/
	    public DJ_U8              m_u8AudioFileType;            /*audio file type: XMS_CFG_TYPE*/
	    public DJ_U16             m_u16AudioFileIndex;          /*audio file index: 0~1023*/
	    public fixed DJ_S8              m_s8AudioFileName[MAX_PATH];  /*audio file path and name*/
	    public DJ_U8              m_u8VideoFileType;            /*video file type: XMS_CFG_TYPE*/
	    public DJ_U8              m_u8Rfu1;                     /*reserve*/
	    public DJ_U16             m_u16VideoFileIndex;          /*video file index: 0~1023*/
	    public fixed DJ_S8              m_s8VideoFileName[MAX_PATH];  /*video file path and name*/
    };/*Get3gppCfg_t*/

    public enum PUT_TEXTINPIC_FONTTYPE	     /* .\\PutTextInPicture.ini */
    {
      FONTTYPE_SIMSUN      = 0,    /*宋体&新宋体*/
      FONTTYPE_MICROSS,            /*Microsoft Sans Serif*/
    };

    public enum PUT_TEXTINPIC_TYPE
    {
      PUT_TYPE_TEXT            = 1,
      PUT_TYPE_PICTURE         = 2,
    };

    public struct tagDllCOLOR
    {
      public DJ_U8  m_u8R;
      public DJ_U8  m_u8G;
      public DJ_U8  m_u8B;
    };/*tagDllCOLOR*/
		
    public struct tagDllFONTPARAM
	  {
		  public DJ_F64    m_f64DBSize;		/*Font Size, default set to 20.0*/
		  public DJ_F64    m_f64DBBlank;	/*Bank ratio, default set to 0.5*/
		  public DJ_F64    m_f64DBGap;		/*Gap ratio,default set to 0.1*/
		  public DJ_F64    m_f64DBAngle;	/*Rotate angle(not present)*/
		  public DJ_S32    m_bUnderLine;	/*Add under line(not present)*/

		  public tagDllCOLOR strcutColor;		/*Font color*/
	  };/*tagDllFONTPARAM*/
	  
	  public struct tagDllPOINT
	  {
		  public DJ_S32 x;
		  public DJ_S32 y;
	  };/*tagDllPOINT*/
	
	  /*PutTextInPicture_Param*/
    public struct PutTextInPicture_Param
    {
	    public DJ_U8   m_u8PutByType;		/*1:Text; 2:Picture,refer PUT_TEXTINPIC_TYPE*/
	    public DJ_U8   m_u8PutByLevel;		/*Picture level*/
	    public fixed DJ_S8   m_s8PutText[260];	/*Put text string*/
	    public DJ_U16  m_u16FontType;		/*Font type,refer PUT_TEXTINPIC_FONTTYPE*/

	    public tagDllFONTPARAM structFontParam

	    public DJ_F32 m_f32Diaphaneity;/*Diaphaneity,default set to 1.0(opacity)*/
	    public tagDllPOINT structPoint;
    };/*PutTextInPicture_Param*/

    /*SigMon_t*/
    public struct SigMon_t
    {
	    public DJ_U8        m_u8MonSigType;     /*singnal type,reference XMS_SIGMON_SIG_TYPE*/
	    public DJ_U8        m_u8MonPackType;    /*Signal Pakcet type,reference XMS_SIGMON_PACK_TYPE*/	
	    public fixed DJ_S8        m_s8Rfu1[6];        /*Rfu*/	
    };/*SigMon_t*/

    /*CmdParamData_RTPXInput_t*/
    public struct CmdParamData_RTPXInput_t
    {
	    public DJ_U8    m_u8ChanEnable;       /*Enable flag, 0: disable; 1: enable*/
	    public DJ_U8    m_u8MediaType;        /*Data type,reference XMS_VOIP_MEDIA_CAPS*/
	    public DJ_U8    m_u8PayloadType;      /*Payload type*/
	    public DJ_U8    m_u8Rfu;              /*reserved*/ 
    };/*CmdParamData_RTPXInput_t*/
    
    /*CmdParamData_RTPXInput_A_t*/
    public struct CmdParamData_RTPXInput_A_t
    {
	    public DJ_U8    m_u8ChanEnable;       /*Enable flag, 0: disable; 1: enable*/
	    public DJ_U8    m_u8MediaType;        /*Data type,reference XMS_VOIP_MEDIA_CAPS*/
	    public DJ_U8    m_u8PayloadType;      /*Payload type*/
	    public DJ_U8    m_u8Decode;           /*Decode enable flag, 0: disable; 1: enable*/ 
    };/*CmdParamData_RTPXInput_A_t*/
     
    /*CmdParamData_RTPXOutput_t*/
    public struct CmdParamData_RTPXOutput_t
    {
	    public DJ_U8    m_u8ChanEnable;       /*Enable flag, 0: disable; 1: enable*/
	    public DJ_U8    m_u8MediaType;        /*Data type,reference XMS_VOIP_MEDIA_CAPS*/
	    public DJ_U8    m_u8PayloadType;      /*Payload type*/
	    public DJ_U8    m_u8SRC_Ctrl1;        /*Source type,reference XMS_MIXER_TYPE*/
	    public DJ_U16   m_u16SRC_Id1;         /*Source channel ID*/
	    public DJ_U16   m_u16RemotePort;	   /*Remote port*/
	    public DJ_U32	 m_u32RemoteIP;		   /*Remote IP*/
    };/*CmdParamData_RTPXOutput_t*/

    /*CmdParamData_RTPXOutput_A_t*/
    public struct CmdParamData_RTPXOutput_A_t
    {
    	public DJ_U8    m_u8ChanEnable;       /*Enable flag, 0: disable; 1: enable*/
    	public DJ_U8    m_u8MediaType;        /*Data type,reference XMS_VOIP_MEDIA_CAPS*/
    	public DJ_U8    m_u8PayloadType;      /*Payload type*/
    	public DJ_U8    m_u8Encode;           /*Encode enable flag, 0: disable; 1: enable*/ 
    	public DJ_U8    m_u8SRC_Ctrl1;        /*Source 1 type,reference XMS_MIXER_TYPE*/
    	public DJ_U8    m_u8SRC_Ctrl2;        /*Source 2 type,reference XMS_MIXER_TYPE*/
    	public DJ_U16   m_u16SRC_Id1;         /*Source channel 1 ID*/
    	public DJ_U16   m_u16SRC_Id2;         /*Source channel 2 ID*/
    	public DJ_U16   m_u16RemotePort;	   /*Remote port*/
    	public DJ_U32	 m_u32RemoteIP;		   /*Remote IP*/
    };/*CmdParamData_RTPXOutput_A_t*/

    /*CmdParamData_RTPXAddr_t*/
    public struct CmdParamData_RTPXAddr_t
    {
	    public DJ_U32	 m_u32RemoteIP;		   /*Remote IP*/
	    public DJ_U16   m_u16RemotePort;	   /*Remote port*/
	    public fixed DJ_U8	 m_u8Rfu[2];		   /*Reserved*/
    };/*CmdParamData_RTPXOutput_t*/

		/*ACS CSP record private parma*/
		public struct CSPRecordPrivate_t
		{
			public PrivateData_t   m_PrivateData;         /*privatedata head*/ 
		  public DJ_U8           m_u8CspRecPrivType;    /*directly send cmd to dsp,0:no,1:yes,reference XMS_CSPREC_PRIV_TYPE*/
			public DJ_U8           m_u8CmdDirect;         /*directly send cmd to dsp,0:no,1:yes,reference XMS_CSPREC_CMD_OPT*/
			public fixed DJ_S8           m_s8Rfu1[2];
		};/**/
		
		/*ACS CSP control record private parma*/
		public struct ControlCSPRecordPrivate_t
		{
			public PrivateData_t   m_PrivateData;                  /*privatedata head*/ 
		  public DJ_U8           m_u8CtrlCspRecPrivType;         /*directly send cmd to dsp,0:no,1:yes,reference XMS_CONTROL_CSPREC_PRIV_TYPE*/
			public DJ_U8           m_u8CmdDirect;                  /*directly send cmd to dsp,0:no,1:yes,reference XMS_CONTROL_CSPREC_CMD_OPT*/
			public fixed DJ_S8           m_s8Rfu1[2];
		};/**/

    /*ACS answer call private param*/
    public struct AnswerCallPrivate_t
    {
	    public PrivateData_t   m_PrivateData;         /*privatedata head*/ 
	    public DJ_S32          m_s32AnswerType;       /*answer type*/
    };/*AnswerCallPrivate_t*/

    /*ACS Fax private param*/
    public struct FaxPrivate_t
    {
	    public PrivateData_t   m_PrivateData;         /*privatedata head*/ 
	    public DeviceID_t      m_VoIPDevice;          /*VoIP device ID*/
	    public DJ_U8           m_u8WorkMode;          /*Fax work mode,reference XMS_FAX_WORKMODE*/
	    public fixed DJ_S8           m_s8Rfu1[3];           /*Rfu */
    };/*FaxPrivate_t*/
    
    /*Acs_TransAddHeader*/
    public struct Acs_TransAddHeader
    {
      public DJ_U32  m_u32Op;		               /*set param type, 0: clear old config, 
	                                         1: set new config, reference to 
	                                         XMS_FAX_PAGE_HEADER_TYPE*/
      public DJ_U16  m_u16XPos;		               /*the x of picture position,*/
      public DJ_U16  m_u16YPos;                     /*the y of picture position,*/
      public fixed DJ_S8   m_u8Data[73];                  /*define by user for fax picture*/
      public DJ_S8   m_u8Rsrv;
      public DJ_U32  m_u32FontSize;
      public DJ_U32  m_u32Header;
    };/*Acs_TransAddHeader*/

    /*Acs_TransAddHeaderEx*/
    public struct Acs_TransAddHeaderEx
    {
      public DJ_U32  m_u32Op;		               /*set param type, 0: clear old config, 
	                                         1: set new config, reference to 
	                                         XMS_FAX_PAGE_HEADER_TYPE*/
      public DJ_U16  m_u16XPos;		               /*the x of picture position,*/
      public DJ_U16  m_u16YPos;                     /*the y of picture position,*/
      public DJ_U32  m_u32FontSize;                 /* 1-7 */
      public fixed DJ_S8   m_u8Data[73];                  /*define by user for fax picture*/
    };/*Acs_TransAddHeaderEx*/

    /*ACS VoIP Call private param*/
    public struct VoIPCallPrivate_t
    {
	    public PrivateData_t   m_PrivateData;         /*privatedata head*/ 
	    public DJ_S32          m_s32Protocol;         /*protocol type*/
	    public fixed DJ_S8           m_s8CallerAddress[20]; /*Caller Address*/
	    public DJ_S32          m_s32CallerPort;       /*Caller Port*/
	    public fixed DJ_S8           m_s8CallerUserID[40];  /*Caller UserID*/		
	    public fixed DJ_S8           m_s8CalleeAddress[20]; /*Callee Address*/
	    public DJ_S32          m_s32CalleePort;       /*Callee Port*/
	    public fixed DJ_S8           m_s8CalleeUserID[40];  /*Callee UserID*/		
	    public DJ_U8           m_u8MediaCapNum;       /*media capability number*/
	    public fixed DJ_U8           m_u8MediaCapList[10];  /*media capability list*/
    };/*VoIPCallPrivate_t*/
    
    /*ACS VoIP Call private param*/
    public struct VoIPCallPrivateEx_t
    {
    	public PrivateData_t   m_PrivateData;         /*privatedata head*/ 
    	public DJ_S32          m_s32Protocol;         /*protocol type*/
    	public fixed DJ_S8           m_s8CallerAddress[20]; /*Caller Address*/
    	public DJ_S32          m_s32CallerPort;       /*Caller Port*/
    	public fixed DJ_S8           m_s8CallerUserID[40];  /*Caller UserID*/		
    	public fixed DJ_S8           m_s8CalleeAddress[20]; /*Callee Address*/
    	public DJ_S32          m_s32CalleePort;       /*Callee Port*/
	    public fixed DJ_S8           m_s8CalleeUserID[40];  /*Callee UserID*/		
	    public DJ_U8           m_u8MediaCapNum;       /*media capability number*/
    	public fixed DJ_U8           m_u8MediaCapList[10];  /*media capability list*/
    	public DJ_U8			u8MediaMode;			// media mode 0:noset(sendrecv) 1:sendonly 2:recvonly 3:sendrecv
    };/*VoIPCallPrivate_t*/
    
    /*ACS Voip Open private param*/
		public struct VoIPOpenPrivate_t
		{
			public PrivateData_t 	m_PrivateData;		/*privatedata head*/
			public DJ_U8		m_u8RtpMode;		/*RTP Mode:0-default auto,1-user control*/
		};/*VoIPOpenPrivate_t*/
		
		/*ACS VoIP Forward Call param*/
		public struct VoIPForwardCallPrivate_t
		{
			public PrivateData_t   m_PrivateData;         /*privatedata head*/ 
			public DJ_S32          m_s32Protocol;         /*protocol type*/
			public fixed DJ_S8           m_s8CallerAddress[20]; /*Caller Address*/
			public DJ_S32          m_s32CallerPort;       /*Caller Port*/
			public fixed DJ_S8           m_s8CallerUserID[40];  /*Caller UserID*/		
			public fixed DJ_S8		m_s8TelNo[20];	       /*telephone number*/
		};/*VoIPForwardCallPrivate_t*/

    /*ACS VoIP Alert private param*/
    public struct VoIPAlertPrivate_t
    {
	    public PrivateData_t   m_PrivateData;         /*privatedata head*/ 
	    public DJ_U8           m_u8MediaCapNum;       /*media capability number*/
	    public fixed DJ_U8           m_u8MediaCapList[10];  /*media capability list*/
    };/*VoIPAlertPrivate_t*/

    /*ACS VoIP Alert private param*/
    typpublicedef struct VoIPAlertPrivateEx_t
    {
      public PrivateData_t   m_PrivateData;         /*privatedata head*/ 
      public DJ_U8           m_u8MediaCapNum;       /*media capability number*/
      public fixed DJ_U8           m_u8MediaCapList[10];  /*media capability list*/
    	public DJ_U16			u16AlertCode;			// alert code for sip, support 180,181,182,183, default is 183
    };/*VoIPAlertPrivate_t*/

    /*ACS VoIP Answer private param*/
    public struct VoIPAnswerPrivate_t
    {
	    public PrivateData_t   m_PrivateData;         /*privatedata head*/ 
	    public DJ_U8           m_u8MediaCapNum;       /*media capability number*/
	    public fixed DJ_U8           m_u8MediaCapList[10];  /*media capability list*/
    };/*VoIPAnswerPrivate_t*/
    
    public struct VoIP_RTP_Format_t
		{
			public DJ_U8		u8CodecType;		/* codec type */
			public DJ_U8		u8PayloadType;		/* payload type */
		};/*VoIP_RTP_Format_t*/
				
    public struct VoIP_RTP_Session_t
		{
			public DJ_U32			u32IP;				/* remote rtp address */
			public DJ_U16			u16Port;			/* remote rtp port */
			public VoIP_RTP_Format_t tx;
			public VoIP_RTP_Format_t rx;
		};/*VoIP_RTP_Session_t*/
			
		public VoIPConnectPrivate_t struct
		{
			public PrivateData_t   m_PrivateData;			/*privatedata head*/ 
			public VoIP_RTP_Session_t audio;
			public VoIP_RTP_Session_t video;
		};/*VoIPConnectPrivate_t*/
		
		public struct ChCodec
		{
			public DJ_U8	m_u8Enable;				/* enable flag */
			public DJ_U8	m_u8TxCodec;			/* tx codec */
			public DJ_U8	m_u8TxPayloadType;		/* tx payload type (if dynamical) */
			public DJ_U8	m_u8RxCodec;			/* rx codec */
			public DJ_U8	m_u8RxPayloadType;		/* rx payload type (if dynamical) */
		};/*ChCodec*/
			
		/* Acs VoIP RTP Codec struct */
		public struct Acs_VoIP_RTPCODEC
		{
			public ChCodec audio;
			public ChCodec video;
		};/*Acs_VoIP_RTPCODEC*/
		
		public struct ChMedia
    {
			public DJ_U8	m_u8Enable;			/* enable flag */
			public fixed DJ_S8	m_s8IP[20];			/* ip address */
			public DJ_U16	m_u16Port;			/* port */
			public DJ_U8	m_u8TxCodec;			/* tx codec */
			public DJ_U8	m_u8TxPayloadType;		/* tx payload type (if dynamical) */
			public DJ_U8	m_u8RxCodec;			/* rx codec */
			public DJ_U8	m_u8RxPayloadType;		/* rx payload type (if dynamical) */	
    };/*ChMedia*/
    
		/* Acs Voip RTP Open struct */
		public struct Acs_VoIP_RTPOpen
		{
		    public DJ_U8	m_u8Enable;				/* enable/disable rtp session */
		    public DJ_U8	m_u8PayloadDtmf;		/* dynamic payload type for rtp dtmf */
		    public DJ_U8	m_u8PayloadTone;		/* dynamic payload type for rtp tone */	
		    public ChMedia audio;
		    public ChMedia video;	
		};/*AcsVoIP_RTPOpen*/
		
		/* Acs_VoIP_MediaInfo */
		public struct Acs_VoIP_MediaInfo
		{
		    public DJ_U8   payload_dtmf;
		    public DJ_U8   payload_tone;
		    public DJ_U8   u8AudioEnabled;
		    public fixed DJ_S8   s8AudioAddress[20];			// host address
		    public DJ_U16  u16AudioPort;			// port number
		    public DJ_U8   u8VideoEnabled;
		    public fixed DJ_S8   s8VideoAddress[20];			// host address
		    public DJ_U16  u16VideoPort;			// port number
		    public DJ_U8   u8MediaCapNum;                      // media capability number
		    public fixed DJ_U8   u8MediaCapList[10];                 // media capability list
		};/*Acs_VoIP_MediaInfo*/
		
		public struct ChAddr
    {
			public DJ_U8	m_u8Enable;			/* enable flag */
			public fixed DJ_S8	m_s8IP[20];			/* ip address */
			public DJ_U16	m_u16Port;			/* port */
    };/*ChAddr*/
		    
		/* Acs VoIP RTP Address struct */
		public struct Acs_VoIP_RTPADDR
		{
		  public ChAddr audio;
		  public ChAddr video;
		};/*Acs_VoIP_RTPADDR*/
		
		/* Acs VoIP RTP Session struct */
		public struct Acs_VoIP_RTPSESSION
		{
			DJ_U8	m_u8Enable;				/* enable/disable rtp session */
			DJ_U8	m_u8PayloadDtmf;		/* dynamic payload type for rtp dtmf */
			DJ_U8	m_u8PayloadTone;		/* dynamic payload type for rtp tone */
		};/*Acs_VoIP_RTPSESSION*/
		
		public struct VoIPDummyPrivate_t
		{
			PrivateData_t   m_PrivateData;			/*privatedata head*/ 
		};

    /* VoIP Media Capabilities */
    public enum XMS_VOIP_MEDIA_CAPS
    {
    // audio media
	    VOIP_MEDIA_AUDIO_PCMU		= 0x00,	// pcm u-law
	    VOIP_MEDIA_AUDIO_PCMA		= 0x01,	// pcm a-law
	    VOIP_MEDIA_AUDIO_G723		= 0x02,	// g.723
	    VOIP_MEDIA_AUDIO_G729		= 0x03,	// g.729
	    VOIP_MEDIA_AUDIO_T38		= 0x04,	// t.38/rtp
	    VOIP_MEDIA_AUDIO_AMR		= 0x05,	// amr-nb
    // video media
	    VOIP_MEDIA_VIDEO_H261		= 0x80,	// h.261
	    VOIP_MEDIA_VIDEO_H263		= 0x81,	// h.263
	    VOIP_MEDIA_VIDEO_H263P		= 0x82,	// h.263+
	    VOIP_MEDIA_VIDEO_MPEG4		= 0x83,	// mpeg-4 visual
	    VOIP_MEDIA_VIDEO_H264		= 0x84,	// h.264

	    VOIP_MEDIA_IMAGE_T38		= 0xF0,	// t.38/udptl
    };

    /* Board Device Params */
    public enum XMS_BOARD_PARAM_TYPE
    {
	    BOARD_PARAM_GETBOARDINFO          = 0,
	    BOARD_PARAM_SETFSK                = 1,
	    BOARD_PARAM_SETFLASH              = 2,
	    BOARD_PARAM_SETGTDFREQ            = 3,
	    BOARD_PARAM_SETGTDTONE            = 4,
	    BOARD_PARAM_SETTRUNKFLASH         = 5,
	    BOARD_PARAM_SETGTGFREQ            = 6, //GTG Freq
	    BOARD_PARAM_SETGTGTONE            = 7, //GTG Tone
	    BOARD_PARAM_SETVSD                = 8, //VSD
			BOARD_PARAM_SET_ACTIVE_MEM_VAD    = 9, //ACTIVE MEM VAD
    	BOARD_PARAM_SETCTCLK              = 10,     
    	BOARD_PARAM_SET_MIN_VAD           = 11, //ACTIVE MEM VAD           
			BOARD_PARAM_SET_COMMON_CFG        = 12, //COMMON CFG 
    };

    public enum XMS_FAX_PARAM_TYPE
    {
	    FAX_PARAM_FAXHEADER    = 0 ,
	    FAX_PARAM_ADDFAXFILE   = 1 ,
	    FAX_PARAM_STARTSENDFAX = 2,
        FAX_PARAM_MODE_TYPE    = 3,
	    FAX_PARAM_BPS	       = 4,
	    FAX_PARAM_FAXHEADEREX  = 5
    };

    /* Media Device Params */
    public enum XMS_VOC_PARAM_TYPE
    {
	    VOC_PARAM_UNIPARAM     = 0,// set universal vocice parameters.
	    VOC_PARAM_BREAKEN_CALL = 1,// added by jerry for keyInterrupet .08.02.19
	    VOC_PARAM_3GFAXTONE    = 2,// added by jerry for 3G FaxTone Eanble or Disable 08.02.20
    };

    /* ISDN Device Param type*/
    public enum XMS_ISDN_PARAM_TYPE
    {
         ISDN_PARAM_ORINUMBER = 0,
         ISDN_PARAM_CALLTYPE = 1,
         ISDN_PARAM_APPENDCALLEE = 2,
         ISDN_PARAM_CALLOUT =3,
         ISDN_PARAM_DISCONNECTREASON=4,
     ISDN_PARAM_LOW_LEVEL         = 5,
     ISDN_PARAM_UUI                = 6,
    };
    /* Conference Device Params */
    public enum XMS_CONF_PARAM_TYPE
    {
	    CONF_PARAM_UNIPARAM = 0,
    };

    /* Analog EM Device Params */
    public enum XMS_AEM_PARAM_TYPE
    {
	    XMS_AEM_PARAM_SND_M_SIGNAL = 1, //send M msg to endpoint
    };

    /* MediaEx Device Params */
    public enum XMS_MEDIAEX_PARAM_TYPE
    {
	    MEDIAEX_PARAM_INPUT = 0,
	    MEDIAEX_PARAM_OUTPUT,
    };

    /* VoIP Call Slot Access Flag */
    public const int XMS_VOIP_ACCESS_NONE = 0x00;	/* no access */
    public const int XMS_VOIP_ACCESS_H323 = 0x01;	/* h.323 call access */
    public const int XMS_VOIP_ACCESS_SIP = 0x02;	/* sip call access */
    public const int XMS_VOIP_ACCESS_INCOMING = 0x04;	/* incoming call access */
    public const int XMS_VOIP_ACCESS_OUTGOING = 0x08;	/* outgoing call access */
    public const int XMS_VOIP_ACCESS_REGISTRATION = 0x10;	/* registration access */

    /* VoIP Device Params */
    public enum XMS_VOIP_PARAM_TYPE
    {
	    VOIP_PARAM_ACCESS = 0,
	    VOIP_PARAM_VOICE,
	    VOIP_PARAM_RTPSESSION,
	    VOIP_PARAM_RTPADDR,
	    VOIP_PARAM_RTCPADDR,
	    VOIP_PARAM_RTPCODEC,
	    VOIP_PARAM_RTPMIXER,
	    VOIP_PARAM_RTPWANIP,
	    VOIP_PARAM_PAYLOAD,
			VOIP_PARAM_MEDIAINFO,
			VOIP_PARAM_RTPOPEN
	    VOIP_PARAM_SIP_USER_AGENT,
	    VOIP_PARAM_CALL_DIVERSION_INFO,
    };

    /* CAS Device Params */
    public enum XMS_CAS_PARAM_TYPE
    {
	    CAS_PARAM_UNIPARAM = 0,
            CAS_PARAM_MFCTYPE  = 1,
      CAS_PARAM_CALLTYPE      = 2,    //0 all (default)  1 逐位拨号 CmdParamData_CAS->m_u8CallType;
      CAS_PARAM_APPENDCALLEE  = 3,    //CmdParamData_CAS->m_u8AppendCallee 一次一位
    };

    /* Analog User Device Params */
    public enum XMS_ANALOGUSER_PARAM_TYPE
    {
	    ANALOGUSER_PARAM_UNIPARAM = 0,
	    ANALOGUSER_PARAM_UNBINDVOC     = 3 ,//Added by jerry For UnBind Voc From AnalogUser
	    ANALOGUSER_PARAM_READSN        = 4, //get AnalogUser's SN
	    ANALOGUSER_PARAM_GET_VOLTAGE   = 5, //Get AnalogUser's voltage
    };

    /* Analog Trunk Device Params */
    public enum XMS_ANALOGTRUNK_PARAM_TYPE
    {
	    ANALOGTRUNK_PARAM_UNIPARAM = 0,
	    ANALOGTRUNK_PARAM_SETFLASH = 1,
	    ANALOGTRUNK_PARAM_UNSETUNIPARAM = 2 ,//added by jerry for UnSet UniParam(id = 0 )....
	    ANALOGTRUNK_PARAM_UNBINDVOC     = 3 ,//Added by jerry For UnBind Voc From AnalogTrunk
      ANALOGTRUNK_PARAM_READSN        = 4 ,//get TRUNK's SN
	    ANALOGTRUNK_PARAM_GET_VOLTAGE   = 5 ,//get TRUNK's voltage
    };
         
    /* Analog HIZ Device Params */
    public enum XMS_ANALOGHIZ_PARAM_TYPE
    {
      ANALOGHIZ_PARAM_SET_SW_MODE   = 0 ,//set Switch Mode,replace by XMS_DIGREC_PARAM_UNI On Digital Module,reference to XMS_DIGREC_PARAM_TYPE
      ANALOGHIZ_PARAM_VOLTAGE       = 1 ,//Set voltage
      ANALOGHIZ_PARAM_READSN        = 4 ,//get HIZ's SN
      ANALOGHIZ_PARAM_GET_VOLTAGE   = 5 ,//get HIZ's voltage
    };

    /* Analog VOC2 Device Params */
	  public enum XMS_ANALOGVOC2_PARAM_TYPE
	  {
	    public ANALOGVOC2_PARAM_NULL          = 1 ,//RESERVE
	    public ANALOGVOC2_PARAM_READSN        = 4 ,//get VOC2 SN
    	public ANALOGVOC2_PARAM_GET_VOLTAGE   = 5 ,//get HIZ's voltage
    };
    
    /* Analog VOC4 Device Params */
    public enum XMS_ANALOGVOC4_PARAM_TYPE
	  {
	    public ANALOGVOC4_PARAM_NULL          = 1 ,//RESERVE
	    public ANALOGVOC4_PARAM_READSN        = 4 ,//get VOC4 SN
	  	public ANALOGVOC4_PARAM_GET_VOLTAGE   = 5 ,//get HIZ's voltage
    };
	  
    /* Analog MEG Device Params */
    public enum XMS_AMEG_PARAM_TYPE
    {
    	public XMS_AMEG_PARAM_SEND_RING_SIGNAL = 1, // send ring msg to meg
    	public XMS_AMEG_PARAM_GET_SN           = 4, // get param for sn
    	public XMS_AMEG_PARAM_GET_VOLTAGE      = 5, // get param for voltage
    };
    
    /* Analog EM Device Params */
    public enum XMS_ANALOGEM_PARAM_TYPE
    {
	    public ANALOGEM_PARAM_NULL             = 1, //RESERVE
      public ANALOGEM_PARAM_READSN           = 4, //get EM's SN
	    public ANALOGEM_PARAM_GET_VOLTAGE      = 5, //get EM's voltage
    };

    /* 324 Config Params*/
    public enum XMS_324_PARAM_TYPE
    {
	    H324_PARAM_UNIPARAM  = 0x0,
	    H324_PARAM_MEDIA     = 0x1,
	    H324_PARAM_CH	     = 0x2,
	    H324_PARAM_MIXER	 = 0x3,
	    H324_PARAM_TCS		 = 0x4,
    };

    /*Digtial machine Record param type*/
    public enum XMS_DIGREC_PARAM_TYPE
    {
	    XMS_DIGREC_PARAM_UNI  = 0x0,
	    XMS_AREC_PARAM_SET_VOLTAGE   = 0x01,      //set analog rec module valtage param type
    };

    public enum MD_CFG_TYPE
    {
	    MD_CFG_TYPE_NON_INDEX      = 0x00,   /*非索引操作*/
	    MD_CFG_TYPE_INDEX          = 0X01,   /*索引操作*/
    };


    /*XMS_324_CMD_SESSION_TYPE*/
    public enum XMS_324_CMD_SESSION_TYPE
    {	
	    XMS_324_CMD_TYPE_NORMAL_START			= 0x0,	/* start session in normal mode */
	    XMS_324_CMD_TYPE_MONITOR_START          = 0x1,	/* start session in monitor mode */
	    XMS_324_CMD_TYPE_STOP                   = 0x2,	/* stop session */
	    XMS_324_CMD_TYPE_RESET					= 0x3,	/* reset session */
    };

    /*XMS_324_CMD_CTRL_TYPE*/
    public enum XMS_324_CMD_CTRL_TYPE
    {
	    XMS_324_CMD_TYPE_SETMET					= 0x1,	/* set multiplex entry table */
	    XMS_324_CMD_TYPE_OLC					= 0x2,	/* open rx/tx logical channel */
	    XMS_324_CMD_TYPE_CLC					= 0x3,	/* close logical channel */
	    XMS_324_CMD_TYPE_UII					= 0x4,	/* Send user input */
	    XMS_324_CMD_TYPE_VFU					= 0x5,	/* send video fast update */	
    };
    
    /*XMS_324_EVT_TYPE*/
    public enum XMS_324_EVT_TYPE
    {
	    XMS_324_EVT_TYPE_START				    = 0x1,	/* start session event */
	    XMS_324_EVT_TYPE_STOP				    = 0x2,	/* stop session event */
	    XMS_324_EVT_TYPE_RESET					= 0x3,	/* reset session event */
	    XMS_324_EVT_TYPE_UII					= 0x4,	/* receive user input event */
	    XMS_324_EVT_TYPE_SIG_PDU                = 0x5,	/* receive h.245 signal message event */
	    XMS_324_EVT_TYPE_OLC						= 0x6,	/*open logical channel event*/
	    XMS_324_EVT_TYPE_CLC						= 0x7,	/*close logical channel event*/
    };

    /* XMS_324_STOP_CODE */
    public enum XMS_324_STOP_CODE
    {
	    XMS_324_STOP_CODE_UNKOWN				= 0x0,
	    XMS_324_STOP_CODE_UPERSTOP				= 0x1,
	    XMS_324_STOP_CODE_LOWERSTOP				= 0x2,
	    XMS_324_STOP_CODE_HOSTSTOP				= 0x3,	
	    XMS_324_STOP_CODE_REMOTESTOP			= 0x4,
    };

    /* XMS_324_AL_TYPE */
    public enum XMS_324_AL_TYPE
    {
	    XMS_324_AL1_FRAMED						= 0x1,	/* AL1 framed */
	    XMS_324_AL1_NOTFRAMED					= 0x2,	/* AL1 not framed */
	    XMS_324_AL2_WITHOUTSN					= 0x3,	/* AL2 */
	    XMS_324_AL2_SN							= 0x4,	/* AL2 with sn */
	    XMS_324_AL3								= 0x5,	/* AL3 */
    };

    /* encode type define for 3G324M module */
    /*  encode type */
    public enum XMS_ENCODE_TYPE
    {
	    XMS_324_LC_CTRL							= 0x0,
	    XMS_324_LC_AUDIO_G723					= 0x08,
	    XMS_324_LC_AUDIO_AMR					= 0x14,
	    XMS_324_LC_VIDEO_H263					= 0x83,
	    XMS_324_LC_VIDEO_MPEG4					= 0x85,
    };

    //////////////////////////////////////////////////////////////////
    /*XMS_SCCP_CMD_TYPE*/
    public enum XMS_SCCP_CMD_TYPE
    {
	    XMS_SCCP_CMD_SETRAWDATA             = 0x1,	
    };

    /*EXT_ENABLE_TYPE*/
    public enum EXT_ENABLE_TYPE
    {
        EXT_ENABLE_DPD                          = 0x01,
        EXT_ENABLE_PVD                          = 0x02,	
        EXT_ENABLE_MSK                          = 0x04,
        EXT_ENABLE_VSD                          = 0x08,
    };

    /*DRS_EVT_MASK*/
    public enum DRS_EVT_MASK
    {
        DRS_EVT_HOOK_MASK                       = 0x01,
        DRS_EVT_CONNECT_MASK                    = 0x02,	
        DRS_EVT_VAD_MASK                        = 0x04,
    };

    /*XMS_RTPX_PARAM_TYPE*/
    public enum XMS_RTPX_PARAM_TYPE
    {
	    XMS_RTPX_PARAM_INPUT               = 0x0,
	    XMS_RTPX_PARAM_OUTPUT              = 0x1,
	    XMS_RTPX_PARAM_MIXER		       = 0x2,
	    XMS_RTPX_PARAM_ADDR				   = 0x3,
	    XMS_RTPX_PARAM_INPUT_A               = 0x4,
	    XMS_RTPX_PARAM_OUTPUT_A              = 0x5,
	    XMS_RTPX_PARAM_MIXER_A		       = 0x6,
	    XMS_RTPX_PARAM_ADDR_A				   = 0x7
    };

    /*XMS_DRS_SWITCH_TYPE*/
    public enum XMS_DRS_SWITCH_TYPE
    { 
        XMS_DRS_SWITCH_AVAYA                = 0x01,
        XMS_DRS_SWITCH_SIMENZ               = 0x02,
        XMS_DRS_SWITCH_TADIRANT             = 0x03,
        XMS_DRS_SWITCH_ERRICSION            = 0x04,
        XMS_DRS_SWITCH_TOSHIBA              = 0x05,
    };

    /*VOC input control param*/
    public struct VocInputControlParam_t
    {
            public DJ_U8   m_u8AgcEnable;       /*0:disable;1:enable*/
            public DJ_U8   m_u8AgcMode;         /*0:ALS mode; 1:AGC mode,reference XMS_AGC_MODE*/
            public DJ_U8   m_u8EcEnable;        /*0:disable;1:enable*/
            public DJ_U8   m_u8EcRefType;       /*0:ref from input;1:ref from output*/
            public DJ_U8   m_u8VadEnable;       /*0:disable;1:enable*/
            public DJ_U8   m_u8TadEnable;       /*0:disable;1:enable*/
            public DJ_U8   m_u8NrEnable;        /*0:disable;1:enable*/
            public DJ_U8   m_u8Reserved;        /*Rfu*/
            public DJ_U16  m_u16FixGain;       /*0x400 = 0dB*/
            public DJ_U16  m_u16EcRefCh;       /*Rfu*/
            public DJ_U32  m_u32Reserved;      /*Rfu*/
    };/*VocInputControl_t*/

    /*VOC ouput control param*/
    public struct VocOutputControlParam_t
    {
	    public DJ_U8	             m_u8AgcEnable;	  /*0:disable;1:enable*/
	    public DJ_U8	             m_u8AgcMode;	  /*0:ALS mode; 1:AGC mode*/
	    public DJ_U8	             m_u8OutputType;  /*0:silence;1:from input;2:from play;3:from mixer,control by m_MixerControl,Reference XMS_VOC_OUTPUT_TYPE*/
	    public fixed DJ_U8	             m_u8Reserved[1]; /**/
	    public DJ_U16	             m_u16FixGain;	  /*0x400 = 0dB*/
	    public fixed DJ_S8                m_s8Rfu[2];      /*Rfu*/
	    public MixerControlParam_t	 m_MixerControl;  /**/
    };/*VocOutputControl_t*/

    /*VOC GTD control param*/
    public struct VocGtdControlParam_t
    {
	    public DJ_U8	m_u8ChannelEnable; /*0: all disable; 1: control by next params*/
	    public DJ_U8	m_u8DTMFEnable;	   /*0:disable;1:enable*/
	    public DJ_U8	m_u8MR2FEnable;	   /*0:disable;1:enable*/
	    public DJ_U8	m_u8MR2BEnable;	   /*0:disable;1:enable*/
	    public DJ_U8	m_u8GTDEnable;	   /*0:disable;1:enable*/
	    public DJ_U8	m_u8FSKEnable;	   /*0:disable;1:enable*/
	    public DJ_U8   m_u8EXTEnable;     /*0 bit: DPD, 1 bit: PVD, 2 bit: MSK reference to EXT_ENABLE_TYPE public enum*/
        public DJ_U8   m_u8Reserved;      /*rfu*/
	    public fixed DJ_U8	m_u8GTDID[8];      /**/
    };/*VocGtdControl_t*/

    /*Voice param*/
    public struct CmdParamData_Voice_t
    {
	    public DJ_U8                       m_u8InputCtrlValid;  /*is VocInputControl_t valid*/
	    public DJ_U8                       m_u8PlayGainMode;    /*Play gain mode,reference XMS_PLAY_GAIN_MODE*/  
	    public DJ_U16                      m_u16PlayFixGain;    /*Play fix gain*/ 
	    public VocInputControlParam_t	    m_VocInputControl;   /*valid to voc,not include RTP*/
	    public DJ_U8                       m_u8OutputCtrlValid; /*is VocOutputControl_t valid*/
	    public fixed DJ_S8                       m_s8Rfu2[3];         /*Rfu*/
	    public VocOutputControlParam_t	    m_VocOutputControl;  /*valid to voc and RTP*/
	    public DJ_U8                       m_u8GtdCtrlValid;    /*is VocGtdControl_t valid*/
	    public fixed DJ_S8                       m_s8Rfu3[3];         /*Rfu*/
	    public VocGtdControlParam_t	    m_VocGtdControl;	 /*valid to voc and RTP*/
    };/*CmdParamData_Voice_t*/

    /* Acs VoIP Registration State struct */
    public struct Acs_VoIP_REGSTATE
    {
	    public DJ_U16	m_u16SlotID;			/* Registration Slot ID */
	    public DJ_U8	m_u8Protocol;			/* VoIP Protocol */
	    public DJ_U8	m_u8State;				/* Registration State */
	    public fixed DJ_S8	m_s8TelNo[20];			/* Client Telephone-subscriber */
	    public fixed DJ_S8	m_s8Address[20];		/* Client Address */
	    public DJ_U16	m_u16Port;				/* Client Port */
	    public fixed DJ_S8	m_s8UserID[40];			/* Client UserID */
    };/*Acs_VoIP_REGISTRATION*/

		/* Acs_VoIP_Regist Struct */
		public struct Acs_VoIP_Regist
		{
			public DJ_U16	m_u16SlotID;			/* Registration Slot ID */
			public DJ_U8	m_u8Protocol;			/* VoIP Protocol */
			public DJ_U8	m_u8State;			/* Registration State */
			public fixed DJ_S8	m_s8TelNo[20];			/* Client Telephone-subscriber */
			public fixed DJ_S8	m_s8Address[20];		/* Client Address */
			public DJ_U16	m_u16Port;			/* Client Port */
			public fixed DJ_S8	m_s8UserID[40];			/* Client UserID */	
		};/*Acs_VoIP_Regist*/
		
		/* Acs_VoIP_Regist_Response struct */
		public struct Acs_VoIP_Regist_Response
		{
		    public DJ_U8	m_u8State;		/* Registration State */    
		    public fixed DJ_S8	m_s8TelNo[20];	    	/* subscriber number */
		    public fixed DJ_S8	m_s8Username[40];	/* username for authorization */
		};/*Acs_VoIP_Regist_Response*/
		
		/* Acs VoIP Refer struct */
		public struct Acs_VoIP_Refer
		{
			public DJ_U8	m_u8Protocol;			/* VoIP Protocol */
			public DJ_U8	m_u8State;				/* Registration State */
			public fixed DJ_S8	m_s8TelNo[20];			/* Client Telephone-subscriber */
			public fixed DJ_S8	m_s8Address[20];		/* Client Address */
			public DJ_U16	m_u16Port;				/* Client Port */
			public fixed DJ_S8	m_s8UserID[40];			/* Client UserID */
		};/*Acs_VoIP_Refer*/
		
		
		/* Acs VoIP Refer Response struct */
		public struct Acs_VoIP_Refer_Response
		{
			public DJ_U8	m_u8ReferFlag;			/* refer flag */
			public DJ_U8	m_u8SrcUnitID;				/* source Unit ID */
			public DJ_U16	m_u16SrcChanID;				/* source Channel ID */
			public DJ_U8	m_u8DestUnitID;				/* destination Unit ID */
			public DJ_U16	m_u16DestChanID;				/* destination Channel ID */
			public fixed DJ_S8	m_s8TelNo[20];			/* Client Telephone-subscriber */
			public fixed DJ_S8	m_s8Address[20];		/* Client Address */
			public DJ_U16	m_u16Port;				/* Client Port */
			public fixed DJ_S8	m_s8UserID[40];			/* Client UserID */
		};/*Acs_VoIP_Refer_Response*/
		
		/* Acs VoIP Refer Result struct */
		public struct Acs_VoIP_ReferResult
		{
			public DJ_U8	m_u8Protocol;			/* protocol */
			public DJ_U8	m_u8State;			/* state */
			public DJ_U8	m_u8Reason;			/* reason */
		};/*Acs_VoIP_ReferResult*/

    /* Acs VoIP Registraion Response struct */
    public struct Acs_VoIP_REGRESP
    {
	    public DJ_U16	m_u16SlotID;			/* Registration Slot ID */
	    public DJ_U8	m_u8Granted;			/* grant registration */
	    public fixed DJ_S8	m_s8Password[20];		/* password for sip authentication */
    };/*Acs_VoIP_REGRESP*/

    /*analog flash param*/
    public struct CmdParamData_FlashParam_t
    {
	    public DJ_U8	m_u8MinHookFlashTime;		//default is 5, //in units of 20ms
	    public DJ_U8	m_u8MaxHookFlashTime;		//default is 25,in units of 20ms	
    };/*CmdParamData_FlashParam_t*/

    public	struct CmdParamData_TrunkFlashParam_t
    {
	    public DJ_U8	m_u8HookFlashTime;		//default is 10, //in units of 20ms
	    public fixed DJ_U8	m_u8reserved[3];		
    };
    
    /*Analoge Rec Module Voltage param*/
    public struct CmdParamData_AnalogRecVoltage_t
    {
	  	public DJ_U8   m_u8Valtage;                   //[0, 54], default is 54
	  	public fixed DJ_U8   m_u8Reserve[3];                //reserve
	  };
    
    public struct CmdParamData_ReadSn_t
    {
      public fixed DJ_U8  m_u8ReadSn[13];
      public fixed DJ_U8  m_u8Reserved[3];
	  };
	  
    public struct CmdParamData_ReadVoltage_t
    {    
    	public DJ_U8   m_u8ReadFlag;      /*Read voltage control flag, 0: stop read; 1: start read*/
    	public fixed DJ_S8   m_s8Reserved1[3];
	  	public DJ_U32  m_u32TimeSpan;     /*Keygoe report voltage event time span, unit: ms*/
	  	public DJ_S8   m_s8Voltage;       /*Current voltage value*/ 
      public fixed DJ_U8   m_u8Reserved2[3];   /*reserved*/
    };

    /*silence voice detect param*/
    public struct CmdParam_SilenceDetectParam_t
    { 	
        public DJ_U32    m_u32SilenceLevel;            //silence detect level(db)        
        public DJ_U32    m_u32SilenceTimer;            //silence detect timer(ms)
        public DJ_U32    m_u32Reserved2;               //reserve
    };/*CmdParam_SilenceDetectParam_t*/
    
    /*VAD min level detect param*/
		public struct	CmdParam_VADMinDetectParam_t
		{ 	
		    public DJ_S32    m_s32VadLevel;                //VAD min detect level(db), default: -54, [-60, -20] 
		    public DJ_U16    m_u16VadInterval;             //VAD interval(5ms), default: 200, [10, 300]       
		    public fixed DJ_U8     m_u8Reserved1[2];             //reserve
		}; /*CmdParam_VADMinDetectParam_t*/
		
		/*Board Common param set*/
		public struct	CmdParam_BoardCommonParam_t
		{ 	
		    public DJ_U8     m_u8IsCNGEnable;              //the switch of CNG, 0: Disable, 1: Enable 
		    public DJ_U16    m_u16CNGGainLevel;            //the value of CNG gain,default: 9,[4, 15]       
		    public fixed DJ_U8     m_u8Reserved1[29];            //reserve
		}; /*CmdParam_BoardCommonParam_t*/

    /*FSK Send/Recv param*/
    public	struct CmdParamData_FskParam_t
    {
	    public DJ_U16	rxFilterWindow;		/*default is 4, shouldn't change it       */
	    public DJ_U16	rxPeriodTheshold;	/*=80*rxFilterLength,shouldn't change it  */
	    public DJ_U16	rx55Count;			/*default is 10, can be changed as needed */
	    public DJ_U16	rxAllOneSamples;	/*default is 60, can be changed as needed */
	    public DJ_U16	rxDataTimeOut;		/*default is 20ms,can be changed as needed */
	    public DJ_U16	txBit1Freq;			/*default is 1350,can be changed as needed */
	    public DJ_U16	txBit0Freq;			/*default is 2150,can be changed as needed */
	    public DJ_U16	tx55Count;			/*default is 20, can be changed as needed  */
	    public DJ_U16	txAllOneSamples;	/*default is 600, can be changed as needed */
	    public fixed DJ_U16	reserved[3];
    };/*CmdParamData_FskParam_t*/

    public struct CmdParamData_GtdFreq_t
    {	
	    public DJ_U16	m_u16Freq_Index;  /* Frequence index: 0-15*/
	    public DJ_U16  m_u16Freq_Coef;   /* Frequence*/
    };/*CmdParamData_GtdFreq_t*/

    public struct CmdParamData_GtdProtoType_t
    {
	    public DJ_U16  m_u16GtdID;
	    public DJ_U16	m_u16Freq_Mask;
	    public DJ_U16	m_u16Amp_Threshold;
	    public DJ_U16	m_u16Envelope_Mode;
	    public DJ_U16	m_u16Repeat_Count;
	    public DJ_U16	m_u16Min_On_Time1;
	    public DJ_U16	m_u16Max_On_Time1;
	    public DJ_U16	m_u16Min_Off_Time1;
	    public DJ_U16	m_u16Max_Off_Time1;
	    public DJ_U16	m_u16Min_On_Time2;
	    public DJ_U16	m_u16Max_On_Time2;
	    public DJ_U16	m_u16Min_Off_Time2;
	    public DJ_U16	m_u16Max_Off_Time2;
    };/*CmdParamData_GtdProtoType_t*/

    /* Acs VoIP H.245 UserInputIndication struct */
    public struct CmdParamData_GtgFreq_t
    {	 
	    public DJ_U16	m_u16Freq_Index;  /* Frequence index: 0-15*/
	    public DJ_U16  m_u16Freq_Coef;   /* Frequence*/
    };/*CmdParamData_GtgFreq_t*/

    //---This Struct according to ITP_GTG_Template(DSP_PACKET_DEF.H)
    public struct CmdParamData_GtgProtoType_t
    {
	    public DJ_U8	m_u8GTG_id;	        /*影射GTG ID，有效值0x30-0x3F*/
	    public DJ_U8	m_u8Reserved1;		/*保留*/
	    public DJ_U16	m_u16Reserved2;		/*保留*/

	    //-------ITP_GTG_Prototype--------
	    public DJ_U8	m_u8Freq1_Index;
	    public DJ_U8	m_u8Freq2_Index;
	    public DJ_U16	m_u16Freq1_Amp;
	    public DJ_U16	m_u16Freq2_Amp;
	    public DJ_U16	m_u16Envelope_Mode;
	    public DJ_U16	m_u16Repeat_Count;
	    public DJ_U16	m_u16On_Time1;
	    public DJ_U16	m_u16Off_Time1;
	    public DJ_U16	m_u16On_Time2;
	    public DJ_U16	m_u16Off_Time2;
	    public DJ_U16	m_u16Reserved;		/*保留*/
    };/*CmdParamData_GtgProtoType_t*/
    
    /* Acs VoIP H.245 UserInputIndication struct */
    public struct CmdParamData_CTCLKNET_t
    {
      public DJ_U8   m_u8NetRef1;       /*L_NET0=0x08,L_NET1=0x09,L_NET2=0x0A,L_Net3=0x0B*/
	    public DJ_U8   m_u8SysClockType;  /*reference to XMS_BOARD_EXT_CLOCK_TYPE*/
      public fixed DJ_U8   m_u8Rfu[2];        /* Reserved*/

    };/*CmdParamData_CTCLKNET_t*/

    /* Acs VoIP H.245 UserInputIndication struct */
    public struct Acs_VoIP_H245UII
    {
	    public fixed DJ_S8	m_s8String[100];		/* UserInputIndication string (general string)*/
	    public DJ_S8	m_s8Signal;				/* UserInputIndication signal type (dtmf char in "0123456789#*ABCD!")*/
	    public fixed DJ_S8   m_Rfu[3];               /* Reserved*/
	    public DJ_U32	m_u32Duration;			/* UserInputIndication signal duration (in milliseconds)*/
    };/*Acs_VoIP_H245UII*/

    public const int MAX_CAPS_NUM    = 4;
    public const int MAX_DECODER_CFG_INFO = 128;
    
    /* Acs MediaEx Video Input Param*/
    public struct Acs_MediaEx_Input_V
    {
	  	public DJ_U16		m_u16Port;				/* local port */
	  	public DJ_U8		m_u8Codec;				/* codec type */
	  	public DJ_U8		m_u8PayloadType;		/* rtp payload type (if dynamic) */
    	public DJ_U16      m_u32ProfileLevelId;	/* codec extra attribute */
	    public DJ_U16      decoderConfigLength;
	  	public DJ_U8       decoderConfigInfo[MAX_DECODER_CFG_INFO];
	  };/*Acs_MediaEx_Input_V*/
	  
	  /* Acs MediaEx Output Param */
	  public struct Acs_MediaEx_Output_V
	  {
	  	public fixed DJ_S8		m_s8IP[20];				/* dest address */
	  	public DJ_U16		m_u16Port;				/* dest port */
	  	public DJ_U8		m_u8Codec;				/* codec type */
	  	public DJ_U8		m_u8PayloadType;		/* rtp payload type (if dynamic) */
	  	public DJ_U16		m_u16ResX;				/* resolution x */
    	public DJ_U16		m_u16ResY;				/* resolution y */
    	public DJ_U8		m_u8Fps;				/* framerate in fps */
    	public DJ_U16		m_u16Kbps;				/* bitrate in Kbps */
    };/*Acs_MediaEx_Output_V*/
    
    /* Acs MediaEx Audio Output Param*/
	  public struct Acs_MediaEx_Output_A
    {
    	public fixed DJ_S8		m_s8IP[20];				/* dest address */
    	public DJ_U16		m_u16Port;				/* dest port */
    	public DJ_U8		m_u8Codec;				/* codec type */
    	public DJ_U8		m_u8PayloadType;		/* rtp payload type (if dynamic) */
    };/*Acs_MediaEx_Output_A*/

    /* Acs MediaEx Play Param */
    public struct Acs_MediaEx_Play
	  {
	  	public PrivateData_t   m_PrivateData;			/*privatedata head*/
	  	public DJ_S8			m_s8SrcName[ACS_MAX_FILE_NAME_LEN];	/* file name */
    	public DJ_U32			m_u32Start;				/* start time */
	  	public DJ_U8			m_u8Loop;				/* loop */
	  	public Acs_MediaEx_Output_A	audio;			/* audio output param */
	  	public Acs_MediaEx_Output_V	video;			/* video output param */
	  	public fixed DJ_S8					s8OverlayImage[200];
	  };/*Acs_MediaEx_PlayFile*/
	  
	  /* Acs 3GVConf Play Param */
	  public struct Acs_3GVConf_Play
	  {
	  	public PrivateData_t   m_PrivateData;			/*privatedata head*/
	  	public DeviceID_t         m_device;			/*voc conf DeviceID*/
	  	public Acs_MediaEx_Play   m_play;			/*Acs_MediaEx_PlayFile*/
    };/*Acs_MediaEx_PlayFile*/
    
    /* Acs MediaEx Transcode Param */
    public struct Acs_MediaEx_Transcode
    { 
    	public PrivateData_t			m_PrivateData;	/*privatedata head*/ 
	  	public Acs_MediaEx_Input_V		input;			/* input param */
    	public Acs_MediaEx_Output_V	output;			/* output param */
    	public fixed DJ_S8					s8OverlayImage[200];
    };/*Acs_MediaEx_Transcode*/
    
    /* Acs MediaEx Conference Param */
    public struct Acs_MediaEx_Conference
    {
    	public PrivateData_t			m_PrivateData;	/*privatedata head*/ 
	  	public fixed Acs_MediaEx_Input_V		input[16];		/* input param */
	  	public fixed Acs_MediaEx_Output_V	output[16];		/* output param */
	  	public fixed DJ_S8					s8OverlayImage[200];
    };/*Acs_MediaEx_Conference*/
	  
	  /* Acs MediaEx Record Param */
	  public struct Acs_MediaEx_Record
	  {
	  	public PrivateData_t   m_PrivateData;			/*privatedata head*/
	  	public DJ_S8			m_s8DstName[ACS_MAX_FILE_NAME_LEN];	/* file name */
	  	public Acs_MediaEx_Output_A	audio;			/* audio output param */
	  	public Acs_MediaEx_Output_V	video;			/* video output param */
	  };/*Acs_MediaEx_Record*/
	  
	  /* Acs 3GVConf Record Param */
	  public struct Acs_3GVConf_Record
    {
    	public PrivateData_t   m_PrivateData;			/*privatedata head*/
    	public DeviceID_t         m_device;			/*voc conf DeviceID*/
    	public Acs_MediaEx_Record   m_record;			/*Acs_MediaEx_RecordFile*/
    };/*Acs_MediaEx_RecordFile*/
    
	  /* Acs 3GVConf Cmd Param */
    public struct Acs_3GVConf_Cmd_V
    {
    	public DeviceID_t               m_device;
    	public Acs_MediaEx_Input_V      m_input;
    	public Acs_MediaEx_Output_V     m_output;
    	public DJ_U8                    m_u8Visible;
    	public DJ_U8                    m_u8CmdType;
    };/*Acs_3GVConf_Cmd_V*/
	  
	  /*Acs_3GVConf_LayoutList*/
	  public struct Acs_3GVConf_LayoutList
    {
	  	public fixed DeviceID_t               m_device[16];
	  };/*Acs_3GVConf_LayoutList*/
	  
	  /*Acs_3GVConf_VisibleList*/
	  public struct  Acs_3GVConf_VisibleList
	  {
	  	public fixed DeviceID_t               m_device[16];
	  };/*Acs_3GVConf_VisibleList*/
	  
	  /* Acs MediaEx Conference Layout */
	  public struct Acs_MediaEx_ConfLayout
	  {
    	public PrivateData_t			m_PrivateData;	/*privatedata head*/ 
    	public fixed int						layout[16];
    };/*Acs_MediaEx_ConfLayout*/
    
    /* Acs Video Link Param */
    public struct Acs_Video_Link_Param
	  {
    	public PrivateData_t m_PrivateData;	/*privatedata head*/ 
      public DJ_U8 m_u8TranscodeModule;		/* transcode module id */
    	public DJ_U8 m_u8SrcCodec;				/* source codec type */
      public DJ_U16 decoderConfigLength;
    	public DJ_U8 decoderConfigInfo[MAX_DECODER_CFG_INFO];
    	public DJ_U8 m_u8DstCodec;				/* destination codec type */
    	public DJ_U8 m_u8Fps;						/* destination framerate in fps */
    	public DJ_U16 m_u16Kbps;					/* destination bitrate in Kbps */ 
	    public DJ_U16 m_u16ResX;					/* destination resolution x */
	  	public DJ_U16 m_u16ResY;					/* destination resolution y */
	  	public fixed DJ_S8 s8OverlayImage[200];
    };/*Acs_Video_Link_Param*/
	  
	  public enum XMS_CAP_DIRECTION
	  {
	  	XMS_CAP_DIR_RX    = 1,
	  	XMS_CAP_DIR_TX    = 2,
	  	XMS_CAP_DIR_RXTX   = 3,
	  };
	  
	  public struct Acs_3G324M_H223CAP
	  {
	  	public DJ_U8 videoWithAL1;
	  	public DJ_U8 videoWithAL2;
    	public DJ_U8 videoWithAL3;
    	public DJ_U8 audioWithAL1;
    	public DJ_U8 audioWithAL2;
    	public DJ_U8 audioWithAL3;
    	public DJ_U16 maximumAl2SDUSize;
    	public DJ_U16 maximumAl3SDUSize;
	  	public DJ_U16 maximumDelayJitter;
    	public DJ_U8 maxMUXPDUSizeCapability;
    	public DJ_U8 nsrpSupport;
    	public DJ_U8 modeChangeCapability;
    	public DJ_U8 h223AnnexA;
    	public DJ_U8 h223AnnexADoubleFlag;
    	public DJ_U8 h223AnnexB;
    	public DJ_U8 h223AnnexBwithHeader;
    	public DJ_U8 reserved;
	  };
	  
	  public struct Acs_3G324M_CAP_AMR
    {
	  	public DJ_U8 maxBitRate;
	  	public DJ_U8 maxFramesPerSdu;
	  	public fixed DJ_U8 reserved[2];
	  };
	  
	  public struct Acs_3G324M_CAP_G723
	  {
	  	public DJ_U8 maxFramesPerSdu;
	  	public DJ_U8 silenceSuppression;
	  	public fixed DJ_U8 reserved[2];
	  };
	  
    public struct Acs_3G324M_CAP_H263
    {
    	public DJ_U8 sqcifMPI;
    	public DJ_U8 qcifMPI;
    	public DJ_U8 cifMPI;
    	public DJ_U8 cif4MPI;
	  	public DJ_U8 cif16MPI;
    	public DJ_U8 reserved1;
    	public DJ_U16 maxBitRate;
    	public DJ_U8 unrestrictedVector;
    	public DJ_U8 arithmeticCoding;
    	public DJ_U8 advancedPrediction;
    	public DJ_U8 pbFrames;
    	public DJ_U8 temporalSpatialTradeOffCapability;
    	public DJ_U8 errorCompensation;
	  	public fixed DJ_U8 reserved2[2];
	  };
	  
    public struct Acs_3G324M_CAP_MP4
	  {
	  	public DJ_U16 maxBitRate;
	  	public DJ_U8 profileAndLevel;
	  	public DJ_U8 object;
	  	public fixed DJ_U8 reserved[3];
	  	public DJ_U8 decoderConfigLength;
	  	public DJ_U8 decoderConfigInfo[MAX_DECODER_CFG_INFO];
	  };
	  
	  public union Acs_3G324M_CAP
	  {
	  	public Acs_3G324M_CAP_AMR AmrAudioCapability;
    	public Acs_3G324M_CAP_G723 G7231AudioCapability;
    	public Acs_3G324M_CAP_H263 H263VideoCapability;
    	public Acs_3G324M_CAP_MP4 Mpeg4VideoCapability;
    };
    
    public struct Acs_3G324M_CAPENTRY
	  {
    	public DJ_U16 entryNumber;
    	public DJ_U8 capType;							/* reference to XMS_VOIP_MEDIA_CAPS */
    	public DJ_U8 direction;						/* reference to XMS_CAP_DIRECTION */
    	public Acs_3G324M_CAP capability;
    };
    
    public struct Acs_3G324M_CAPTABLE
    {
	  	public DJ_U16 capabilityNum;
    	public DJ_U16 reserved;
    	public Acs_3G324M_CAPENTRY CapabilityTableEntry[MAX_CAPS_NUM];
    };
    
    public struct Acs_3G324M_TCS
    {
    	public Acs_3G324M_H223CAP h223Capability;
    	public Acs_3G324M_CAPTABLE capabilityTable;
    };

    /* Acs VoIP SIP INFO struct */
    public struct Acs_VoIP_SIPINFO
    {
	    public fixed DJ_S8	m_s8ContentType[50];	/* content type string (mime)*/
	    public fixed DJ_S8	m_s8Body[800];			/* info message body string*/
    };/*Acs_VoIP_SIPINFO*/
    
    /* Acs VoIP SIP Register/Unregister struct */
		public struct Acs_VoIP_SIPREG
		{
			public fixed DJ_S8	m_s8TelNo[20];	    /* subscriber number */
			public fixed DJ_S8	m_s8Username[20];	/* username for authorization */
			public fixed DJ_S8	m_s8Password[20];	/* paswword for authorization */
		};/*Acs_VoIP_SIPREG*/

    /* Acs VoIP RTP DTMF struct */
    public struct Acs_VoIP_RTPDTMF
    {
	    public DJ_S8	m_s8EventChar;			/* dtmf event char */
	    public DJ_S8	m_s8Volume;				/* volume (in dbm0 from -63 to 0) */
	    public DJ_U16	m_u16Duration;			/* duration (in timestamp units) */
    };/*Acs_VoIP_RTPDTMF*/

    /* Acs VoIP RTP TONE struct */
    public struct Acs_VoIP_RTPTONE
    {
	    public DJ_U16	m_u16Modulation;		/* modulation */
	    public DJ_U8	m_u8TriFlag;			/* tri-frequency flag */
	    public DJ_S8	m_s8Volume;				/* volume */
	    public DJ_U16	m_u16Duration;			/* duration */
	    public DJ_U8	m_u8FrequencyNum;		/* number of frequencies */
	    public fixed DJ_U16	m_u16Frequency[10];		/* frequencies to mix the tone */
    };/*Acs_VoIP_RTPTONE*/

    /* Acs VoIP Mixer struct*/
    public struct Acs_VoIP_Mixer
    {
	    public DJ_U8	m_u8SRC1_Ctrl;  /*reference XMS_MIXER_TYPE*/
	    public DJ_U8	m_u8SRC2_Ctrl;  /*reference XMS_MIXER_TYPE*/
	    public DJ_U16	m_u16SRC_ChID1; /*Media ChID1*/
	    public DJ_U16	m_u16SRC_ChID2; /*Media ChID2*/
	    public DJ_S8   m_s8Video;      /*Video Channel*/
	    public DJ_S8   m_s8Rfu;        /*Rfu*/
    };/*Acs_VoIP_Mixer*/

    /*ACS_Conf_Param*/
    public struct CmdParamData_Conf_t
    {
	    public DJ_U8               m_u8InputOpt;	 /*conf input option, reference XMS_CONF_INPUT_OPT*/
	    public DJ_U8               m_u8OutputOpt;	 /*conf output option, reference XMS_CONF_OUTPUT_OPT*/
	    public fixed DJ_U8               m_u8Rfu[2];      /*Rfu*/
    };/*CmdParamData_Conf_t*/

    /* Called Number Table Description */ 
    public struct CAS_CalledTableDesc_t
    {
	    public DJ_U8						m_u8NumHeadLen;			/* Compared Called Number Head Length */
	    public fixed DJ_U8						m_u8NumHead[14];		/* Compared Called Number Head Content */
	    public DJ_U8						m_u8NumLen;				/* Total Called Number Length */
    };/**/
    public const int CAS_CalledTableDesc_t_Size = 16;

    /* CAS Parameter Type Define*/
    public struct CmdParamData_CAS_t
    {
	    public DeviceID_t					m_VocDevID;				/* Voice Device ID which is used for MFC, alloced by Application */

	    /* Call In Parameter */
	    public DJ_U8						m_u8CalledTableCount;	/* Called Table Count ( 0-16:Table Count) */
	    public fixed DJ_U8                       m_Rfu1[3];              /* Reserved*/
        public fixed byte m_CalledTable[16 * CAS_CalledTableDesc_t_Size];		/* Max 16 items */
	    public DJ_U8						m_u8CalledLen;			/* Called Number Length (0:Variable, Other:Length) */

	    public DJ_U8						m_u8CalledTimeOut;		/* Time Out Seconds when Receive MFC */

	    public DJ_U8						m_u8NeedCaller;			/* Is Need Caller Number ( 1:Yes, 0:No ) */
	    public DJ_U8						m_u8AreaCodeLen;		/* Area Code Length when receive Called Number, Used for Receive Caller Number */

	    /* Call Out Parameter */
	    public DJ_U8						m_u8KA;					/* KA ( Default KA = 1 ) */
	    public DJ_U8						m_u8KD;					/* KD ( Default KD = 3 ) */

	    /* Other */
	    public DJ_U8						m_u8ControlMode;		/* Release Control Mode ( 0:None, 1:Caller Control, 2:Called Control ) */
	    public DJ_U8                       m_u8CountryCode;    
	    public DJ_U8                       m_u8CallType;
      public DJ_U8                       m_u8AppendCallee;
	    public fixed DJ_U8						m_u8Rfu[6];				/* Reserved for Future Use */
    };/*CmdParamData_CAS_t*/

    public const int   COUNTRY_BEGIN = 0x00;
    public const int   CHINA = 0x01;
    public const int   KOREA = 0x02;
    public const int   INDIA = 0x03;
    public const int   VIETNAM = 0x04;
    public const int   COUNTRY_END = 0x05;
    /*AnalogTrunk Parameter Define*/
    public struct CmdParamData_AnalogTrunk_t
    {
	    //CallIn Paramteter
	    public DJ_U16	m_u16CallInRingCount; //ring count before CallIn event
	    public DJ_U16  m_u16CallInRingTimeOut;//Unit:ms Ring TimeOut,when ring timed out ,state changed to DCS_Free
    };/*CmdParamData_AnalogTrunk_t*/


    public struct CmdParamData_AnalogTrunkFlash_t
    {
	    public DJ_U8	m_u8Channel_Enable;
	    public DJ_U8	m_u8Type;
	    public DJ_U8	m_u8Tx_State;
	    public DJ_U8	m_u8Rx_State;
    };/*CmdParamData_AnalogTrunkFlash_t*/

    /*AnalogUser Parameter Define*/
    public struct CmdParamData_AnalogUser_t
    {	
	    // Call Out Parameter 
	    public DJ_U8        m_u8CallerIdOption;//0:disabled; 1:Fsk CallerId; 2:DTMF CallerId;,reference XMS_ANALOG_USER_CALLERID_OPT
	    public DJ_U8        m_u8RingCadenceType;//0: single-pulse ring; 1:double-pulse ring; 2: triple-pulse ring
	    public DJ_U8        m_u8CallOutRingTimeOut;// unit: second ; Ringing TimeOut ,it timetout ,then state return to DCS_FREE
	    public DJ_U8        m_u8Rfu1;
        public fixed DJ_U8        m_u8Rfu2[12];
    };/*CmdParamData_AnalogUser_t*/


    /*DTMF control param*/
    public struct CmdDtmfParamData_Voice_t
    {
     public DJ_U32                      m_u32MaxValidIntervalTime;  /* max interval time: ms*/
     public DJ_U8                       m_u8MaxCodeNums;            /* max DTMF nums : 0 ~ 255*/
     public fixed DJ_U8                       m_u8Rfu1[3];                /*Rfu*/
     public fixed DJ_U8                       m_u8DTMF[32];               /*DTMF buffer*/
    };/*CmdDtmfParamData_Voice_t*/


    /* Struct of AddFaxFile */
    public struct  CmdParamData_AddFax_t
    {
	    public fixed DJ_S8       m_s8FaxFileName[128]; /* FaxFileName ,Usual As Tiff Format */
    };/*CmdParamData_AddFax_t*/

    /* Struct of StartSendFax */
    public struct CmdParamData_StartSendFax_t
    {
	    public DeviceID_t m_VocDev;
	    public fixed DJ_S8      m_s8LocalID[ACS_LOCALID_MAX_LEN];
    };/*CmdParamData_StartSendFax_t*/

    /*CmdParamData_3GPP_t*/
    public struct CmdParamData_3GPP_t
    {	
        public DJ_U8			m_u8AudioDecodeType;  /*audio decode type*/
	    public DJ_U8           m_u8AudioFrameType;   /*audio frame type,reference XMS_AUDIO_AMR_FRAME_TYPE*/
        public DJ_U16			m_u16AudioDecoderCfgLen;/*audio decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
	    public fixed DJ_U8			m_u8AudioDecoderCfg[ACS_MAX_DECODER_CFG_LEN];/*audio decoder cfg*/
	    public DJ_U8           m_u8AudioProfiles;    /*audio profiles?*/
        public DJ_U8           m_u8AudioLevel;		  /*audio level ?*/
        public fixed DJ_U8           m_Rfu1[2];

	    public DJ_U8           m_u8VideoDecodeType;      /*video decode type*/
	    public DJ_U8           m_u8VideoFrameRate;       /*video frame rate 10 ~ 30*/
	    public DJ_U16          m_u16VideoDecoderCfgLen;  /*video decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
	    public fixed DJ_U8           m_u8VideoDecoderCfg[ACS_MAX_DECODER_CFG_LEN];/*video decoder cfg?*/
	    public DJ_U8           m_u8VideoProfiles;        /*video profiles?*/
	    public DJ_U8           m_u8VideoLevel;           /*video level?*/
	    public fixed DJ_U8           m_Rfu2[2];
    };/*CmdParamData_3GPP_t*/

    /*DigRecSwitchMode*/
    public struct DigRecSwitchMode
    {
	    public DJ_U8           m_u8Enable;               /*the switch of the function, 0: disable; 1: enable*/
	    public DJ_U8           m_u8SwitchMode;           /*the digital switch type,referece to XMS_DRS_SWITCH_TYPE*/
	    public DJ_U8           m_u8EncodeType;           /*audio's encode type, referece to the A-Law or Mu-law of XMS_VOC_CODE_TYPE, and any other type is not supported by keygoe*/
	    public DJ_U8           m_u8IsRecordSigData;      /*the switch to wheather record the signal data from DSP, 0: disable; 1: enable*/
	    public fixed DJ_S8           m_Rfu1[4];                /*reserve*/
    };/*DigRecSwitchMode*/
    /*CmdParamData_SS7RawFrame_t*/
    public struct CmdParamData_SS7RawFrame_t
    {
	    public DJ_U8 m_u8UserType;
	    public DJ_U8 m_u8LinkType;
	    public DJ_U8 m_u8MsgType;
	    public DJ_U8 m_u8InfoLen;
    	
	    public DJ_U8 m_u8UnitId;
	    public DJ_U8 m_u8E1Port;
	    public DJ_U8 m_u8Ts;
	    public DJ_U8 m_u8Reserved1;
    	
	    public fixed DJ_U8 m_u8Info[255];
	    public DJ_U8 Reserved2;
    };/*CmdParamData_SS7RawFrame_t*/

    /*CmdParamdata Body*/
    public struct CmdParamData_t // 根据以下定义自行组织结构内容 UNION在C#中不存在
    {
        /*
        union
        {
            public CmdParamData_Voice_t m_cmdParamDataVoice;     
            public CmdParamData_Conf_t m_CmdParamDataConf;      
        };
        */
    };
    public struct CmdParamData_t_Voice
    {
		  public CmdParamData_Voice_t		m_cmdParamDataVoice;     /**/		
    };
    public struct CmdParamData_t_Conf
    {
		  public CmdParamData_Conf_t		    m_CmdParamDataConf;      /**/
    };/**/

    /************************************** Event define ******************************/

    public const int ACS_IOEVT_MASK_ALL = 0xFFFF;

    /*Event filter mask*/
    public enum XMS_IOEVT_MASK_TYPE
    {
	    XMS_IOEVT_MASK_GTD              = 0x0001,
	    XMS_IOEVT_MASK_FSK              = 0x0002,
	    XMS_IOEVT_MASK_MR2F             = 0x0004,
	    XMS_IOEVT_MASK_MR2B             = 0x0008,
    };

    public enum XMS_MEDIA_IO_TYPE
    {		
	    XMS_IO_TYPE_DTMF                = 1,
	    XMS_IO_TYPE_MR2F                = 2,
	    XMS_IO_TYPE_MR2B                = 3,
	    XMS_IO_TYPE_GTG                 = 4,
	    XMS_IO_TYPE_GTD                 = 4,
	    XMS_IO_TYPE_FSK                 = 5,
	    XMS_IO_TYPE_DPD                 = 6,
	    XMS_IO_TYPE_PVD                 = 7,
	    XMS_IO_TYPE_MSK                 = 8,
	    XMS_IO_TYPE_VSD                 = 9,
	    XMS_IO_TYPE_MSKREND             = 10,
	    XMS_IO_TYPE_DRS                 = 11,
    };

    public enum XMS_MEDIA_ERR_CODE
    {
	    XMS_ERR_CODE_OK                   = 0x00,
	    XMS_ERR_CODE_APPSTOP              = 0x01,
	    XMS_ERR_CODE_GTD                  = 0x02,
	    XMS_ERR_CODE_OPENFILE_FAILED      = 0x03,
	    XMS_ERR_CODE_WREADFILE_FAILED     = 0x04,
	    XMS_ERR_CODE_CH_MISSING           = 0x05,
	    XMS_ERR_CODE_EXE_FAILED           = 0x06,	
	    XMS_ERR_CODE_BUILD_INDEX_OK       = 0x07,
	    XMS_ERR_CODE_PLAY_QUEUE_FULL      = 0x08,
	    XMS_ERR_CODE_3G_AUDIO_OK          = 0x09,
	    XMS_ERR_CODE_3G_VIDEO_OK          = 0x0A,
	    XMS_ERR_CODE_BUILD_INDEX_FAILED   = 0x0B,
	    XMS_ERR_SYSTEM_OVERLOAD           = 0x0C,
    };

    public enum XMS_CLK_STATE_TYPE
    {
	    XMS_CLK_STATE_SET               = 0x01,    /*Set master/slave clock */
	    XMS_CLK_STATE_RELEASE           = 0x02,    /*Release master/slave clock*/
    };

    public enum XMS_VOIP_IO_TYPE
    {
	    XMS_IO_TYPE_VOIP_H245UII        = 1, /* VoIP H.245 UserInputIndication Event */
	    XMS_IO_TYPE_VOIP_SIPINFO        = 2, /* VoIP SIP INFO Event */
	    XMS_IO_TYPE_VOIP_RTPDTMF        = 3, /* VoIP RTP DTMF Event */
	    XMS_IO_TYPE_VOIP_RTPTONE        = 4, /* VoIP RTP TONE */
	    XMS_IO_TYPE_VOIP_FAXSTART       = 5, /* VoIP start fax mode (t.38 or t.30 pass-thru) */
	    XMS_IO_TYPE_VOIP_FAXSTOP        = 6, /* VoIP stop fax mode(t.38 or t.30 pass-thru) */
	    XMS_IO_TYPE_VOIP_REGSTATE       = 7, /* VoIP Registration State */
	    XMS_IO_TYPE_VOIP_REGREQUEST     = 8, /* VoIP Registration Request */
	    XMS_IO_TYPE_VOIP_REGRESPONSE    = 9, /* VoIP Registration Response */
	    XMS_IO_TYPE_VOIP_TRANSFER       = 10,/* VoIP Device Transfer */ 
	    XMS_IO_TYPE_VOIP_SIPREG         = 11,/* VoIP SIP Register */
			XMS_IO_TYPE_VOIP_SIPUNREG       = 12,/* VoIP SIP Unregister */
			XMS_IO_TYPE_VOIP_REFER		= 13,/* Voip SIP Refer */
			XMS_IO_TYPE_VOIP_REFERRESPONSE	= 14,/* Voip SIP Refer Response */
			XMS_IO_TYPE_VOIP_FORWARD	= 15,/* Voip SIP Forward call */
			XMS_IO_TYPE_VOIP_REFER_NOTIFY	= 16, // VoIP SIP Send Refer Notify to Subscribe
	    XMS_IO_TYPE_VOIP_CALLMODIFY		= 17, /* VoIP SIP Call Modified */
    };

    public enum XMS_DCH_IO_TYPE
    {
	    XMS_IO_TYPE_DCH_I_FRAME         = 1,
	    XMS_IO_TYPE_DCH_UI_FRAME        = 2,
	    XMS_IO_TYPE_DCH_DEBUG           = 3,
    };

    public enum XMS_LINESIDEE1_IO_TYPE
    {
	    XMS_IO_TYPE_LINESIDEE1          = 12,
    };

    public enum XMS_ANALOG_INTERFACE_STATE
    {
	    XMS_ANALOG_USER_CH_OFFHOOK             = 0,
	    XMS_ANALOG_USER_CH_ONHOOK              = 1,	
	    XMS_ANALOG_USER_CH_FLASH               = 2,


    };
    public enum XMS_ANALOG_INTERFACE_STATE2
    {
	    XMS_ANALOG_TRUNK_CH_RING               = 0, 
	    XMS_ANALOG_TRUNK_CH_POSITEX_POLARITY   = 1, 
	    XMS_ANALOG_TRUNK_CH_NEGATIVE_POLARITY  = 2, 
	    XMS_ANALOG_TRUNK_CH_LOOPDROP           = 3,
	    XMS_ANALOG_TRUNK_CH_NOLOOP             = 4, 
	    XMS_ANALOG_TRUNK_CH_FLASH              = 8, 
    };


    public enum XMS_SIG_RAWDATA_EVT_TYPE
    {
	    XMS_SIG_RAWDATA_EVT_BASE         = 0xFF00,	
    };
    
    public enum ACS_MASTER_STATE
    {
    	ACS_STATE_SLAVE                  = 0x0,
    	ACS_STATE_MASTER                 = 0x1,
    };

    public enum ACS_WORK_STATE
    {
    	ACS_STATE_WORK_FAILURE           = 0x0, 
    	ACS_STATE_WORKING                = 0x1,
    };

    public enum XMS_SS7_SN_STATUS
    {
	    XMS_SN_PAUSE      = 0x01, // Pause
	    XMS_SN_RESUME     = 0x02, // Resume
	    XMS_SN_CONG       = 0x03, // Network Congested
	    XMS_SN_RMTUSRUNAV = 0x04, // Remote User Unavailable
	    XMS_SN_RSTBEG     = 0x05, // Restart Begins
	    XMS_SN_RSTEND     = 0x06, // Restart Ends
	    XMS_SN_STPCONG    = 0x07, // Stop Network Congestion
	    XMS_SN_RESTRICT   = 0x08, // Restrict
	    XMS_SN_LNK_CHANGE = 0x09, // Link status changed
    };


    public enum XMS_SS7_MSG_TYPE
    {
	    XMS_SS7_MSG_DATA   = 0x01,
	    XMS_SS7_MSG_CMD    = 0x02,
	    XMS_SS7_MSG_STATUS = 0x03,
    };


    public enum XMS_SS7_USER_TYPE
    {
	    XMS_SS7_USER_TYPE_SCCP = 0x03,
	    XMS_SS7_USER_TYPE_TUP  = 0x04,
	    XMS_SS7_USER_TYPE_ISUP = 0x05,
    };


    public enum XMS_SS7_LINK_TYPE
    {
	    XMS_SS7_LINK_TYPE_ITU  = 0x02,
	    XMS_SS7_LINK_TYPE_CHINA= 0x04,
    };

    /* Event class define*/
    public enum XMS_EVT_CLASS
    {
	    XMS_EVT_CLASS_GENERAL            = 0x0001,
	    XMS_EVT_CLASS_CALLCONTROL        = 0x0002,
	    XMS_EVT_CLASS_CONFPROC           = 0x0003,
	    XMS_EVT_CLASS_VOIPPROC           = 0x0004,
	    XMS_EVT_CLASS_MEDIAPROC          = 0x0005,
	    XMS_EVT_CLASS_FAXPROC            = 0x0006,
	    XMS_EVT_CLASS_IOPROC             = 0x0007,
	    XMS_EVT_CLASS_SYSMONITOR         = 0x0008,
	    XMS_EVT_CLASS_UNIFAILURE         = 0x0009,	
    };

    /*Event type define */
    public enum XMS_EVT_TYPE
    {
        XMS_EVT_OPEN_STREAM = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x01),	
	    XMS_EVT_QUERY_DEVICE                    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x02),	
	    XMS_EVT_QUERY_DEVICE_END                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x03),
	    XMS_EVT_OPEN_DEVICE                     = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x04),
	    XMS_EVT_CLOSE_DEVICE                    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x05),
	    XMS_EVT_RESET_DEVICE                    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x06),
	    XMS_EVT_DEVICESTATE                     = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x07),
	    XMS_EVT_SETDEV_GROUP                    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x08),
	    XMS_EVT_SETPARAM                        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x09),
	    XMS_EVT_GETPARAM                        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x0A),
	    XMS_EVT_QUERY_ONE_DSP_START             = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x0B),
	    XMS_EVT_QUERY_ONE_DSP_END               = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x0C),
	    XMS_EVT_QUERY_REMOVE_ONE_DSP_START      = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x0D),
	    XMS_EVT_QUERY_REMOVE_ONE_DSP_END        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x0E),
	    XMS_EVT_OPEN_STREAM_EXT                 = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x0F),	
	    XMS_EVT_LICENSE_QUERY                   = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x10),
	    XMS_EVT_CLOSE_STREAM_EXT                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x11),	
	    XMS_EVT_MASTER_STATE                    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x13),
	    XMS_EVT_SLAVE_WORK_STATE			          = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x14),
	    XMS_EVT_E1STATE                         = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x20),
    	XMS_EVT_CTBUS_CLK_REF_SRC_STATE         = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x30),	
    	XMS_EVT_USER_DEF                        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0xE0),	
	    XMS_EVT_BAKSYS_STOP                     = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0xF0),
	    XMS_EVT_ACS_TIMER                       = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0xFF),
    			
	    XMS_EVT_CALLOUT							= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x01),
	    XMS_EVT_CALLIN							= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x02),
	    XMS_EVT_ALERTCALL		                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x03),
	    XMS_EVT_ANSWERCALL		                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x04),
	    XMS_EVT_LINKDEVICE				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x05),
	    XMS_EVT_UNLINKDEVICE					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x06),
	    XMS_EVT_CLEARCALL						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x07),
	    XMS_EVT_ANALOG_INTERFACE                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x08),
	    XMS_EVT_CAS_MFC_START					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x09),
	    XMS_EVT_CAS_MFC_END						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x0A),
	    XMS_EVT_SENDSIGMSG						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x0B),		
	    XMS_EVT_SIGMON       					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x0C),
	    XMS_EVT_3G324M       					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x0D),
	    XMS_EVT_CTX_REG                         = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x0E),
	    XMS_EVT_CTX_LINK                        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x0F),
	    XMS_EVT_CTX_APPDATA                     = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x10),
	    XMS_EVT_DRS_CALL_NUMS                   = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x11),
    	
    	
	    XMS_EVT_SS7RawFrame						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x20),
	    XMS_EVT_SS7SendRawFrame					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x21),

    		
	    XMS_EVT_JOINTOCONF					    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CONFPROC<<16)+0x01),
	    XMS_EVT_LEAVEFROMCONF					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CONFPROC<<16)+0x02),
	    XMS_EVT_CLEARCONF					    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CONFPROC<<16)+0x03),
	    
	    XMS_EVT_SET_PAYLOAD				    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC<<16)+0x01),
			XMS_EVT_SET_RTPADDR				    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC<<16)+0x02),
			XMS_EVT_SET_RTCPADDR				    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC<<16)+0x03),
			XMS_EVT_SET_RTPCODEC				    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC<<16)+0x04),
			XMS_EVT_SET_MEDIAINFO				    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC<<16)+0x05),
			XMS_EVT_REFER_RESULT				    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC<<16)+0x06),
			XMS_EVT_REGIST				    	    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC<<16)+0x07),
			XMS_EVT_REGIST_RESP				    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC<<16)+0x08),
    		
	    XMS_EVT_PLAY			                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x01),
	    XMS_EVT_INITINDEX				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x02),
	    XMS_EVT_BUILDINDEX						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x03),
	    XMS_EVT_CONTROLPLAY				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x04),
	    XMS_EVT_RECORD							= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x05),
	    XMS_EVT_CONTROLRECORD				    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x06),
	    XMS_EVT_RECORDCSP   				    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x07),
	    XMS_EVT_CONTROLRECORDCSP    		    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x08),
        XMS_EVT_3GPP_PLAY			            = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x09),
	    XMS_EVT_3GPP_CONTROLPLAY		        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x0A),
	    XMS_EVT_3GPP_RECORD	    				= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x0B),
	    XMS_EVT_3GPP_CONTROLRECORD    		    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x0C),
	    XMS_EVT_PLAYCSPREQ 				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x0D),
	    XMS_EVT_3GPP_INIT_INDEX                           = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x0E),
	    XMS_EVT_3GPP_BUILD_INDEX                          = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x0F),
    	
      XMS_EVT_3GVCONF_JOIN				= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x10),
	    XMS_EVT_3GVCONF_LEAVE				= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x11),
	    XMS_EVT_3GVCONF_CLEAR				= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x12),
	    XMS_EVT_3GVCONF_GETLAYOUT			= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x13),
      XMS_EVT_3GVCONF_SETLAYOUT			= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x14),
	    XMS_EVT_3GVCONF_GETVISIBLELIST			= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x15),
    	XMS_EVT_3GVCONF_SETVISIBLELIST			= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x16),
    	XMS_EVT_3GVCONF_STOP				= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x17),
	
	    XMS_EVT_SENDFAX			                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_FAXPROC<<16)+0x01),
	    XMS_EVT_RECVFAX					        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_FAXPROC<<16)+0x02),
    			
	    XMS_EVT_SENDIODATA						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_IOPROC<<16)+0x01),
	    XMS_EVT_RECVIODATA						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_IOPROC<<16)+0x02),
    		
	    XMS_EVT_MODMONITOR				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_SYSMONITOR<<16)+0x01),
	    XMS_EVT_DEV_TIMER						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_SYSMONITOR<<16)+0x02),
	    XMS_EVT_MODRELATE				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_SYSMONITOR<<16)+0x03),
	    XMS_EVT_VOIPMON  				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_SYSMONITOR<<16)+0x04),
    	
	    XMS_EVT_UNIFAILURE						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_UNIFAILURE<<16)+0x01),	
    };

    /*Error code define*/
    public const int  ACSPOSITIVE_ACK = 0x01;

    public const int  ACSERR_LOADLIBERR = 0x01;
    public const int  ACSERR_BADPARAMETER = 0x02;
    public const int  ACSERR_NOSERVER = 0x03;
    public const int  ACSERR_MAXCONN_EXCEED = 0x04;
    public const int  ACSERR_BADHDL = 0x05;
    public const int  ACSERR_FAILSEND = 0x06;
    public const int  ACSERR_LINKBROKEN = 0x07;
    public const int  ACSERR_NOMESSAGE = 0x08;
    public const int  ACSERR_GETRESFAIL = 0x09;
    public const int  ACSERR_NOSUPPORTCMD = 0x0A;
    public const int  ACSERR_DEVICEERR = 0x0B;
    public const int  ACSERR_CTX_REGOVERRUN = 0x0C;
    public const int	 ACSERR_CTX_REG_NAMEEXIS = 0x0D;
    public const int	 ACSERR_CTX_UNREG_NOREG = 0x0E;
    public const int  ACSERR_CTX_TRAN_NODEST = 0x0F;
    public const int  ACSERR_CTX_TRAN_NOSRC = 0x10;
    public const int  ACSERR_CTX_LINK_FAIL = 0x11;
    public const int  ACSERR_CTX_APPDATA_NODEST = 0x12;
    public const int  ACSERR_CTX_APPDATA_NOSRC = 0x13;
    public const int  ACSERR_NOTMASTER               0x14
    public const int  ACSERR_PUTTEXTINPIC_PARAMERROR 0x14
    public const int  ACSERR_PUTTEXTINPIC_OPENPICFAIL 0x15
    public const int  ACSERR_PUTTEXTINPIC_SAVEPICFAIL 0x16
    public enum XMS_3GVCONF_ERROR_CODE_DEF
    {
    	XMS_ERROR_DEVTYPEERROR = 0,		// 不是可加入会议的设备
    	XMS_ERROR_REJOIN3GVCONF = 1,		// 已存在会议中
    	XMS_ERROR_GETRESFAIL = 2,		// 分配资源失败
    	XMS_ERROR_OVERFLOW = 3,			// 会议成员已满
    	XMS_ERROR_NONEVISIBLE = 4,		// 会议无可视视频会员
    	XMS_ERROR_OVERFLOWPR = 5,		// 会议16方已满 因为有会议播放或者录制造成
    
	    XMS_ERROR_3GVCONFSTOP = 255,		// 会议停止 可能是新加入会议的可视成员参数错误或播放录音参数错误 也可能是会议进程出现错误
						// 遇到此事件应该重让最后一个加入会议的操作取消 或者重启会议
    };


    /*Acs_Dev_List_Head_t*/
    public struct Acs_Dev_List_Head_t
    {
	    public DJ_S32        m_s32DeviceMain;   /*device Main*/
	    public DJ_S32        m_s32ModuleID;     /*Device Module ID*/
	    public DJ_S32        m_s32DeviceNum;    /*device num*/
    };/**/

    /*general proc evt data*/
    public struct Acs_GeneralProc_Data
    {
	    public Acs_Evt_State_t         m_s32AcsEvtState;    /*acs event state, 1: success; 0: failed*/
	    public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;  /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
	    public DJ_S32                  m_s32DeviceState;    /*Device State*/
	    public DJ_S32                  m_s32Resrv;          /*reserved*/
	    public PrivateData_t           m_PrivData;          /*private data*/
    };/**/

    /*Acs_OpenDev_Evt*/
    public struct Acs_GeneralProc_Evt
    {
	    public ACS_EVT_HEAD              m_AcsEvtHead;     /*acs event head*/
	    public Acs_GeneralProc_Data      m_AcsGenLProcData; /*acs general proc event data*/
    };/**/

    /*OpenStreamExt evt data*/
    public struct Acs_OpenStreamExt_Data
    {
	    public ServerID_t      m_ServerID;
	    public Acs_Evt_State_t   m_s32AcsEvtState;    /*acs event state, 1: success; 0: failed*/
	    public fixed DJ_S8           m_s8Rfu1[12];
    };/**/

    /*Acs_OpenStreamExt_Evt*/
    public struct Acs_OpenStreamExt_Evt
    {
	    public ACS_EVT_HEAD                m_AcsEvtHead;           /*acs event head*/
	    public Acs_OpenStreamExt_Data      m_AcsOpenStreamExtData; /*acs general proc event data*/
    };/**/

		/*Acs_CloseStreamExt_Data*/
		public struct Acs_CloseStreamExt_Data
		{
			public ServerID_t      m_ServerID;
			public fixed DJ_S8           m_s8Rfu1[16];
		};/**/
		
		/*Acs_CloseStreamExt_Evt*/
		public struct Acs_CloseStreamExt_Evt
		{
			public ACS_EVT_HEAD                m_AcsEvtHead;            /*acs event head*/
			public Acs_CloseStreamExt_Data     m_AcsCloseStreamExtData; /*acs general proc event data*/
		};/**/
		
		/*ACS master state*/
    public struct Acs_MasterState_Data
    {
	  	public fixed DJ_S8      m_s8ServerIp[32]; /*XMS server ip*/
	  	public DJ_U32     m_u32ServerPort;  /*XMS server port*/
    	public DJ_U8      m_u8MasterState; /*Acs server master state,reference ACS_MASTER_STATE*/
    	public fixed DJ_S8      m_Rfu1[3];
		};
		
		/*Acs_MasterState_Evt*/
		public struct Acs_MasterState_Evt
		{
			public ACS_EVT_HEAD                m_AcsEvtHead;     /*acs event head*/
			public Acs_MasterState_Data        m_AcsMasterState; /*acs master state*/
		};/**/
		
		/*ACS Slave Work state*/
    public struct Acs_SlaveWorkState_Data
    {
	  	public DJ_S8      m_s8WorkState; /*Slave machine work state: 0: conk out, 1: working, reference to ACS_WORK_STATE*/
	  	public fixed DJ_S8      m_Rfu1[31];    /*reserve*/
    };
    
		/*Acs_SlaveWork_Evt*/
		public struct Acs_SlaveWorkState_Evt
		{
			public ACS_EVT_HEAD                m_AcsEvtHead;        /*acs event head*/
			public Acs_SlaveWorkState_Data     m_AcsSlaveWorkState; /*acs slave work state*/
		};/**/
		
		
		/*Acs_BakSysStartEvt*/
		public struct Acs_BakSysStartEvt
    {
      public ACS_EVT_HEAD   m_AcsEvtHead;  /*acs event head*/
      public DJ_S32         m_Rfu1;
    };/**/

    public struct Acs_ParamProc_Data
    {
	    public Acs_Evt_State_t         m_s32AcsEvtState;    /*acs event state, 1: success; 0: failed*/
	    public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;  /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
	    public DJ_U16                  m_u16ParamCmdType;  /*acs param Cmd Type*/
	    public DJ_U16                  m_u16ParamDataSize; /*acs param Data Size*/
    };/**/

    public struct Acs_ParamData_Evt
    {
	    public ACS_EVT_HEAD              m_AcsEvtHead;     /*acs event head*/
	    public Acs_ParamProc_Data        m_ParamProcData;
    };/**/

    public struct Acs_ParamData_UserReadXmsBoardInfo
    {
	    public fixed DJ_U8	m_u8MacAddr[6];	   /* Mac address */
	    public DJ_U8	m_u8ChassisType;   /* chassis type，0: ITP1200; 1:3U chassis; 2:5U chassis; 3: 11U chassis */
	    public DJ_U8	m_u8ChassisIndex;  /* chassis  No */
	    public DJ_U8	m_u8ChassisSlot;   /* chassis slot number */
	    public DJ_U8	m_u8SubBoardIndex; /* module index inside one board*/
	    public DJ_U8	m_u8BoardType;	   /* Board type，0:itp1200;1:itp2400; 2: itp4800*/
	    public fixed DJ_U8	rfu1[1];
	    public fixed DJ_S8	m_s8SystemName[32];/* System name */	
	    public DJ_S8	m_s8PlatformType;  /* Platform: 1:callback; 2:keygoe 1000; 3:keygoe 3000; 4:keygoe 8000*/
	    public fixed DJ_S8	m_s8UserCode[7];   /* User code */
	    public DJ_S32	m_s32SysId;        /* sys id*/
	    public fixed DJ_S8	rfu2[20];

	    public fixed DJ_S8	m_s8FirmwareName[8];	/* DSP firmwarename */
	    public fixed DJ_S8	m_s8FirmwareVersion[8];	/* DSP firmware version*/
	    public fixed DJ_S8	m_s8RevisionDate[8];	/* DSP firmware date*/
    };

    /*Acs_BoardPrivateExt_Data*/
    public struct Acs_BoardPrivateExt_Data
    {
    	public DJ_U32 m_u32ExtType;        /*reference to XMS_BOARD_PRIVATE_EXT_TYPE*/
    	public DJ_U8  m_u8SysClockMode;    /*reference to XMS_BOARD_CLOCK_MODE*/
    	public DJ_U8  m_u8SysClockType;    /*reference to XMS_BOARD_EXT_CLOCK_TYPE	*/
    	public fixed DJ_U8  m_u8Ref[2];
    };/*Acs_BoardPrivateExt_Data*/ 
    /*Acs_BoardRstState_Data*/
    public struct Acs_BoardRstState_Data
    {
    	public fixed DJ_U8  m_u8Ref[16];  //reserve
	
    };/*Acs_BoardRstState_Data*/

    /* CAS Extra Infomation, used by XMS_EVT_CAS_MFC_END*/
    public struct Acs_CAS_ExtraInfo_t
    {
	    /* Call In Infomation */
	    public DJ_U8                     m_u8KA; /* Caller's KA */
	    public DJ_U8                     m_u8KD; /* Caller's KD */
	    /* Call Out Infomation */

	    /* Other */
	    public fixed DJ_U8                     m_u8Rfu[14];/* Reserved for Future Use */
    };/*Acs_CAS_ExtraInfo_t*/

    /*Acs_CallControl_Evt*/
    public struct Acs_CAS_MFC_Evt
    {
	    public ACS_EVT_HEAD              m_AcsEvtHead;     /*acs event head*/
	    public Acs_CAS_ExtraInfo_t       m_AcsCASExtraInfo; /*acs CAS ExtraInfo event data*/
    };/**/

    /*Acs_CallControl_Data*/
    public struct Acs_CallControl_Data
    {
	    public Acs_Evt_State_t         m_s32AcsEvtState;                 /*acs event state, 1: success; 0: failed*/
	    public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;               /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
	    public DJ_S32                  m_s32CallClearCause;              /*Call clear cause code*/
	    public DJ_U8                   m_u8CallingCategory;              /*Calling Category*/
	    public DJ_U8                   m_u8CallingAddressIndicator;      /*Address Indicator*/
	    public DJ_U8                   m_u8CalledAddressIndicator;       /*Address Indicator*/
	    public fixed DJ_S8                   m_s8Rfu1[1];
	    public fixed CallNum_t               m_s8CallingNum[ACS_MAX_CALL_NUM]; /*calling num*/
	    public fixed CallNum_t               m_s8CalledNum[ACS_MAX_CALL_NUM];  /*called num*/
	    public DJ_U8                   m_u8DRSCallDirectFlag;            /*Call direction flag, 0: Call In; 1: Call Out, reference XMS_DRS_CALL_DIRECT_DEF*/
	    public fixed DJ_S8                   m_s8Rfu2[31];
	    public PrivateData_t           m_PrivData;                       /*private data*/
    };/**/

    public enum XMS_DRS_CALL_DIRECT_DEF
    {
	    XMS_DRS_CALL_DIRECT_CALL_IN           = 0,
	    XMS_DRS_CALL_DIRECT_CALL_OUT          = 1,
    };

    /*Acs_CallControl_Evt*/
    public struct Acs_CallControl_Evt
    {
	    public ACS_EVT_HEAD              m_AcsEvtHead;     /*acs event head*/
        public Acs_CallControl_Data      m_AcsCallControl; /*acs call control event data*/
    };/**/

    /*Acs_LinkDev_Data*/
    public struct Acs_LinkDev_Data
    {
	    public Acs_Evt_State_t         m_s32AcsEvtState;   /*acs event state, 1: success; 0: failed*/
	    public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
	    public DeviceID_t              m_SrcDevice;
	    public DeviceID_t              m_DestDevice;
    };/*Acs_LinkDev_Data*/

    /*Acs_LinkDev_Evt*/
    public struct Acs_LinkDev_Evt
    {
	    public ACS_EVT_HEAD              m_AcsEvtHead;     /*acs event head*/
	    public Acs_LinkDev_Data          m_AcsLinkDev;     /*acs Link Device event data*/
    };/*Acs_LinkDev_Evt*/

    /*Acs_CtxReg_Data*/
    public struct Acs_CtxReg_Data
    {
	    Acs_Evt_State_t         m_s32AcsEvtState;   /*acs event state, 1: success; -1: failed*/
	    Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
    };/**/

    /*Acs_CtxReg_Evt*/
    public struct Acs_CtxReg_Evt
    {
	    public ACS_EVT_HEAD              m_AcsEvtHead;     /*acs event head*/
	    public Acs_CtxReg_Data           m_AcsCtxReg;      /*acs ctxReg evt*/
    };/**/

    /*Acs_CtxLink_Data*/
    public struct Acs_CtxLink_Data
    {
	    public Acs_Evt_State_t         m_s32AcsEvtState;   /*acs event state, 1: success; 0: failed*/
	    public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
    };/**/

    /*Acs_CtxLink_Evt*/
    public struct Acs_CtxLink_Evt
    {
	    public ACS_EVT_HEAD              m_AcsEvtHead;     /*acs event head*/
	    public Acs_CtxLink_Data          m_AcsCtxLink;
    };/**/

    /*CTX App Data Info*/
    public struct CTX_AppData_Info
    {
	    public DJ_U32      m_u32AppDataSize; /*user APP data size,not include XMS_AppData_Info_t*/
	    public DJ_U8       m_u8AppReqType;   /*user APP req cmd type,user self define*/
	    public DJ_U8       m_u8AcsUnitID;
	    public fixed DJ_U8       m_Rfu1[2];      
	    public fixed DJ_S8       m_s8SrcRegName[XMS_MAX_REGNAME_LEN]; /*src reg name*/
	    public fixed DJ_S8       m_s8DestRegName[XMS_MAX_REGNAME_LEN];/*dest reg name*/
	    public DJ_U8       m_u8SrcAppUnitID;
	    public DJ_U8       m_u8DstAppUnitID;
	    public fixed DJ_S8       m_Rfu2[2];
	    public DeviceID_t  m_srcDevice;
	    public fixed DJ_S8       m_Rfu3[20];
	    public DJ_S32      m_s32Rst;
    };/**/

    /*Acs_CtxAppData_Info*/
    public struct Acs_CtxAppData_Info
    {
	    public Acs_Evt_State_t         m_s32AcsEvtState;   /*acs event state, 1: success; 0: failed*/
	    public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
	    public CTX_AppData_Info        m_AppDataInfo;
    };/**/

    /*Acs_CtxAppData_Evt*/
    public struct Acs_CtxAppData_Evt
    {
	    public ACS_EVT_HEAD             m_AcsEvtHead;     /*acs event head*/
	    public Acs_CtxAppData_Info      m_AcsCtxAppData;
    };/**/

    /*Acs_CtxState_Info*/
    public struct Acs_CtxState_Info
    {
	    public Acs_Evt_State_t         m_s32AcsEvtState;   /*acs event state, 1: success; 0: failed*/
	    public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
	    public DJ_U32                  m_u32CtxState;
	    public fixed DJ_S8                   m_s8SrcRegName[XMS_MAX_REGNAME_LEN];
	    public fixed DJ_S8                   m_s8DestRegName[XMS_MAX_REGNAME_LEN];
    };/**/

    /*Acs_Ctx_State_Evt*/
    public struct Acs_Ctx_State_Evt
    {
	    public ACS_EVT_HEAD             m_AcsEvtHead;     /*acs event head*/
	    public Acs_CtxState_Info        m_AcsCtxState;
    };/**/

    /*Acs_SigMon_Data*/
    public struct Acs_SigMon_Data
    {
	    public SMON_EVENT           m_SigMon;            /*sig monitor data*/
	    public PrivateData_t        m_PrivData;          /*private data*/
    };/*Acs_SigMon_Data*/

    /*Acs_SigMon_Evt*/
    public struct Acs_SigMon_Evt
    {
	    public ACS_EVT_HEAD              m_AcsEvtHead;     /*acs event head*/
	    public Acs_SigMon_Data           m_AcsSigMon;      /*acs call control event data*/
    };/**/

    /*Acs_3G324_Data*/
    public	struct Acs_3G324_Data
    {
	    public DJ_U8	m_u8DataType;		    /*3G324 event data type*/
	    public DJ_S8	Rfu1;				    /*reserved*/
	    public DJ_U16	m_u16DataLen;	        /*3G324 event data size*/	
    };/*Acs_3G324_Data*/

    /*Acs_3G324_Evt*/
    public struct Acs_3G324_Evt
    {
	    public ACS_EVT_HEAD		m_AcsEvtHead;  /*acs event head*/	
	    public Acs_3G324_Data		m_Acs324Data;  /*acs 3G324 event*/
    };/**/
    
    /*Acs_3G324_Stop_Evt*/
    public	struct Acs_3G324_Stop_Evt
    {
     	public DJ_U8	m_u8StopCode;			/*3G324 session stop code*/
    	public fixed DJ_U8	m_u8Rfu[3];				/*reserved*/	
    };/**/

    /*Acs_AnalogInterface_Data*/
    public struct Acs_AnalogInterface_Data
    {
	    public Acs_Evt_State_t         m_s32AcsEvtState;   /*acs event state, 1: success; 0: failed*/
	    public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
	    public DJ_U8                   m_u8AnalogInterfaceState;/*Analog Interface State,reference XMS_ANALOG_INTERFACE_STATE*/
	    public fixed DJ_U8                   m_Rfu1[3];
	    public PrivateData_t           m_PrivData;          /*private data*/
    };/**/

    /*Acs_AnalogInterface_Evt*/
    public struct Acs_AnalogInterface_Evt
    {
	    public ACS_EVT_HEAD                  m_AcsEvtHead;     /*acs event head*/
	    public Acs_AnalogInterface_Data      m_AcsAnalogInterfaceData; /*acs Analog Interface event data*/
    };/**/

    /*Acs_SendSigMsg_Data*/
    public struct Acs_SendSigMsg_Data
    {
	    public Acs_Evt_State_t         m_s32AcsEvtState;    /*acs event state, 1: success; 0: failed*/
	    public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;  /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
	    public DJ_S16                  m_s16SignalMsgType;  /*acs signal msg type*/
	    public fixed DJ_S8                   m_s8Rfu[2];          /*Rfu*/
    };/**/

    /*Acs_SendSigMsg_Evt*/
    public struct Acs_SendSigMsg_Evt
    {
	    public ACS_EVT_HEAD              m_AcsEvtHead;     /*acs event head*/
	    public Acs_SendSigMsg_Data       m_AcsSendSigMsg;  /*acs send signal msg event data*/
    };/**/

    /*Acs_ConfControl_Data*/
    public struct Acs_ConfControl_Data
    {
	    public Acs_Evt_State_t         m_s32AcsEvtState;    /*acs event state, 1: success; 0: failed*/
	    public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;  /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
	    public DJ_S32                  m_s32ConfMembers;    /*conference member num*/		
	    public DeviceID_t              m_MediaDevice;
	    public PrivateData_t           m_PrivData;/*private data*/
    };/**/

    /*Acs_ConfControl_Evt*/
    public struct Acs_ConfControl_Evt
    {
	    public ACS_EVT_HEAD              m_AcsEvtHead;      /*acs event head*/
	    public Acs_ConfControl_Data      m_AcsConfControl;  /*acs call control event data*/
    };/**/

    /*Acs_MediaProc_Data*/
    public struct Acs_MediaProc_Data
    {
	    public Acs_Evt_State_t         m_s32AcsEvtState;    /*acs event state, 1: success; 0: failed*/
	    public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;  /*acs event errcode ,reference XMS_MEDIA_ERR_CODE*/	
	    public DJ_U8                   m_u8TaskID;          /*play Task ID*/
	    public DJ_U8                   m_u8GTD;             /*GTD ID*/	
	    public fixed DJ_S8                   m_s8Rfu[2];
	    public DJ_U32                  m_u32CurFileIndex;   /*current play file index*/
	    public DJ_U32                  m_u32CurFilePos;     /*current play pos*/
	    public PrivateData_t           m_PrivData;          /*private data*/
    };/**/

    /*Acs_MediaProc_Evt*/
    public struct Acs_MediaProc_Evt
    {
	    public ACS_EVT_HEAD              m_AcsEvtHead;    /*acs event head*/
	    public Acs_MediaProc_Data        m_AcsMediaProc;  /*acs media proc event data*/
    };/**/

    /*Acs_CSPDataReq_Data*/
    public	struct Acs_CSPDataReq_Data
    {
	    public DJ_U16			m_u16ReqCspDataLen; /*DSP request data length*/
	    public DJ_U8			m_u8TaskID;	        /*Task ID*/
	    public DJ_U8			m_u8DataType;	    /*Data Type: reference XMS_CSPPLAY_DATA_TYPE*/
    };/*Acs_CSPDataReq_Data*/

    /*Acs_CSPDataReq_Evt*/
    public struct Acs_CSPDataReq_Evt
    {
	    public ACS_EVT_HEAD              m_AcsEvtHead;         /*acs event head*/
	    public Acs_CSPDataReq_Data       m_AcsCSPDataReqProc;  /*acs media CSP play request data*/
    };/**/


    //public const int		ITP_MAX_STREAM_DATA_LENGTH = 4000;

    /*Acs_MediaCSPProc_Data*/
    public	struct Acs_MediaCSPProc_Data
    {
	    public DJ_U16	m_u16DataLen;	        /*stream data size*/
	    public DJ_U8	m_u8DataType;		    /*stream data type*/
	    public DJ_U8	m_u8TagNumber;			/*Rfu*/
	    public fixed DJ_U8	m_u8StreamData[ITP_MAX_STREAM_DATA_LENGTH ];	/*stream data*/
    };

    /*Acs_MediaCSPProc_Evt*/
    public struct Acs_MediaCSPProc_Evt
    {
	    public ACS_EVT_HEAD              m_AcsEvtHead;       /*acs event head*/
	    public Acs_MediaCSPProc_Data     m_AcsMediaCSPProc;  /*acs media CSP proc event data*/
    };/**/

    /*Acs_Media3GPPProc_Data*/
    public struct Acs_Media3GPPProc_Data
    {
	    public Acs_Evt_State_t         m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	    public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	    public DJ_U8                   m_u8AudioTaskID;          /*audio:  play Task ID*/
	    public DJ_U8                   m_u8MediaType;            /*common: media type XMS_MEDIA_TYPE*/
	    public DJ_U8                   m_u8VideoTaskID;          /*video:  play Task ID*/
	    public DJ_S8                   m_s8Rfu;
	    public DJ_U32                  m_u32AudioCurFileIndex;   /*audio:current play index*/
	    public DJ_U32                  m_u32AudioCurFilePos;     /*audio:current play pos*/
	    public DJ_U32                  m_u32VideoCurFileIndex;   /*video:current play index*/
	    public DJ_U32                  m_u32VideoCurFilePos;     /*video:current play pos*/
	    public PrivateData_t           m_PrivData;/*private data*/
    };/**/

    /*Acs_Media3GPPProc_Evt*/
    public struct Acs_Media3GPPProc_Evt
    {
	    public ACS_EVT_HEAD              m_AcsEvtHead;    /*acs event head*/
	    public Acs_Media3GPPProc_Data    m_AcsMedia3GPPProc;  /*acs media proc event data*/
    };/**/
    
    /*Acs_JoinTo3GVConf_Data*/
    public struct Acs_JoinTo3GVConf_Data
    {
	  	public Acs_Evt_State_t         m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	  	public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	  	public DeviceID_t              m_3GVConfDev;
	  	public DeviceID_t              m_srcDev;
	  	public PrivateData_t           m_PrivData;/*private data*/
	  };/**/
	  
	  /*Acs_JoinTo3GVConf_Evt*/
	  public struct Acs_JoinTo3GVConf_Evt
	  {
	  	public ACS_EVT_HEAD              m_AcsEvtHead;    /*acs event head*/
    	public Acs_JoinTo3GVConf_Data    m_AcsJoinTo3GVConf;  /*acs Join to 3GVConf event data*/
    };/**/
    
	  /*Acs_LeaveFrom3GVConf_Data*/
	  public struct Acs_LeaveFrom3GVConf_Data
	  {
	  	public Acs_Evt_State_t         m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	  	public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	  	public DeviceID_t              m_3GVConfDev;
	  	public DeviceID_t              m_srcDev;
	  	public PrivateData_t           m_PrivData;/*private data*/
	  };/**/
	  
	  /*Acs_LeaveFrom3GVConf_Evt*/
    public struct Acs_LeaveFrom3GVConf_Evt
    {
    	public ACS_EVT_HEAD              m_AcsEvtHead;    /*acs event head*/
	  	public Acs_LeaveFrom3GVConf_Data    m_AcsLeaveFrom3GVConf;  /*acs leave from 3GVConf event data*/
	  };/**/
	  
	  /*Acs_Clear3GVConf_Data*/
	  public struct Acs_Clear3GVConf_Data
	  {
	  	public Acs_Evt_State_t         m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	  	public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	  	public DeviceID_t              m_3GVConfDev;
	  	public PrivateData_t           m_PrivData;/*private data*/
	  };/**/
    
    /*Acs_Clear3GVConf_Evt*/
    public struct Acs_Clear3GVConf_Evt
	  {
	  	public ACS_EVT_HEAD              m_AcsEvtHead;    /*acs event head*/
	  	public Acs_Clear3GVConf_Data     m_AcsClear3GVConf;  /*acs clear 3GVConf event data*/
	  };/**/
	  
	  /*Acs_GetLayout_Data*/
	  public struct Acs_GetLayout_Data
	  {
	  	public Acs_Evt_State_t         m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	  	public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	  	public DeviceID_t              m_3GVConfDev;
    	public Acs_3GVConf_LayoutList  m_list;
    	public PrivateData_t           m_PrivData;/*private data*/
    };/**/
	  
	  /*Acs_GetLayout_Evt*/
	  public struct Acs_GetLayout_Evt
	  {
	  	public ACS_EVT_HEAD              m_AcsEvtHead;    /*acs event head*/
	  	public Acs_GetLayout_Data        m_AcsGetLayout;  /*acs Get Layout event data*/
	  };/**/
	  
	  /*Acs_SetLayout_Data*/
	  public struct Acs_SetLayout_Data
	  {
    	public Acs_Evt_State_t         m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
    	public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
    	public DeviceID_t              m_3GVConfDev;
	  	public PrivateData_t           m_PrivData;/*private data*/
	  };/**/
	  
	  /*Acs_SetLayout_Evt*/
	  public struct Acs_SetLayout_Evt
	  {
	  	public ACS_EVT_HEAD              m_AcsEvtHead;    /*acs event head*/
	  	public Acs_SetLayout_Data        m_AcsSetLayout;  /*acs Set Layout event data*/
	  };/**/
	  
	  /*Acs_GetVisibleList_Data*/
    public struct Acs_GetVisibleList_Data
    {
    	public Acs_Evt_State_t         m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	  	public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	  	public DeviceID_t              m_3GVConfDev;
	  	public Acs_3GVConf_VisibleList m_list;
	  	public PrivateData_t           m_PrivData;/*private data*/
	  };/**/
	  
	  /*Acs_GetVisibleList_Evt*/
	  public struct Acs_GetVisibleList_Evt
	  {
	  	public ACS_EVT_HEAD              m_AcsEvtHead;    /*acs event head*/
	  	public Acs_GetVisibleList_Data   m_AcsGetVisibleList;  /*acs Get Visible List event data*/
    };/**/

    /*Acs_SetVisibleList_Data*/
    public struct Acs_SetVisibleList_Data
	  {
	  	public Acs_Evt_State_t         m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	  	public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	  	public DeviceID_t              m_3GVConfDev;
	  	public PrivateData_t           m_PrivData;/*private data*/
	  };/**/
	  
	  /*Acs_SetVisibleList_Evt*/
	  public struct Acs_SetVisibleList_Evt
	  {
	  	public ACS_EVT_HEAD              m_AcsEvtHead;    /*acs event head*/
    	public Acs_SetVisibleList_Data   m_AcsSetVisibleList;  /*acs Set Visible List event data*/
    };/**/
    
	  /*Acs_3GVConfStop_Data*/
	  public struct Acs_3GVConfStop_Data
	  {
	  	public Acs_Evt_State_t         m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	  	public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	  	public DeviceID_t              m_3GVConfDev;
	  	public PrivateData_t           m_PrivData;/*private data*/
	  } ;/**/
	  
	  /*Acs_3GVConfStop_Evt*/
	  public struct Acs_3GVConfStop_Evt
    {
    	public ACS_EVT_HEAD              m_AcsEvtHead;    /*acs event head*/
	    public Acs_3GVConfStop_Data   m_Acs3GVConfStop;  /*acs 3G VConf Stop event data*/
    };/**/

    /*Acs_IO_Data*/
    public struct Acs_IO_Data
    {
	    public Acs_Evt_State_t      m_s32AcsEvtState;   /*acs event state*/
	    public Acs_Evt_ErrCode_t    m_s32AcsEvtErrCode; /*acs event errcode*/	
        public DJ_U16               m_u16IoType;     /*io proc type*/
	    public DJ_U16               m_u16IoDataLen;  /*io data len*/  
    };/**/

    /*Acs_IO_Evt*/
    public struct Acs_IO_Evt
    {
	    public ACS_EVT_HEAD          m_AcsEvtHead; /*acs event head*/	
	    public Acs_IO_Data           m_AcsIOData;  /*acs io event*/
    };/**/

    /*Acs License Query event*/
    public struct Acs_LicenseQuery_Data
    {
	    public DJ_U8     m_u8ModuleID;          /*license alarm Board module ID*/
	    public DJ_U16    m_u16LicLeftDay;        /*license alarm Board left license days,0: No license or license overdue;100:license forever; else: left license days*/
	    public fixed DJ_S8     m_Rfu1[1];
    };/**/

    /*Acs_LicenseAlarm_Evt*/
    public struct Acs_LicenseQuery_Evt
    {
	    public ACS_EVT_HEAD              m_AcsEvtHead;       /*acs event head*/
	    public Acs_LicenseQuery_Data     m_LicenseQueryData; /*universal failure confirmation event*/	
    };/**/

    /*Acs unifail event*/
    public struct Acs_UniFailure_Data
    {
	    public Acs_Evt_State_t          m_s32AcsEvtState;   /*acs event state, -1*/
	    public Acs_Evt_ErrCode_t        m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
    };/**/

    /*Acs_UniFailure_Evt*/
    public struct Acs_UniFailure_Evt
    {
	    public ACS_EVT_HEAD              m_AcsEvtHead;     /*acs event head*/
	    public Acs_UniFailure_Data       m_UniverFailData; /*universal failure confirmation event*/	
    };/**/

    /*Acs_FaxEnd_Data*/
    public struct Acs_FaxProc_Data
    {
	    public Acs_Evt_State_t      m_s32AcsEvtState;   /*acs event state*/
	    public Acs_Evt_ErrCode_t    m_s32AcsEvtErrCode; /*acs event errcode*/	
	    public DJ_U8                m_u8ErrorStep;      /*error state of last fax operation*/
	    public DJ_U8                m_u8T30SendState;   /*the state the T30 command just sent*/
	    public DJ_U8                m_u8RecvT30Cmd;     /*the T30 command just received*/
	    public DJ_U8                m_u8Rfu1;            /*Reserved*/ 
	    public DJ_U16               m_u16TotalPages;    /*total pages,send: sending total pages successfully  ;rev: receiving total pages successfully*/
        public fixed DJ_S8                m_s8RemoteID[ACS_REMOTEID_MAX_LEN];/*Remote ID*/	
	    public fixed DJ_U8                m_u8Rfu2[2];           /*Reserved*/
	    public PrivateData_t        m_PrivData;/*private data*/
    };/**/

    /*Acs_FaxProc_Evt*/
    public struct Acs_FaxProc_Evt
    {
	    public ACS_EVT_HEAD          m_AcsEvtHead;     /*acs event head*/	
	    public Acs_FaxProc_Data      m_AcsFaxProcData; /*acs fax proc data*/
    };/**/

    /*ITP_3GPP_PARAM_CFG*/
    public struct ITP_3GPP_PARAM_CFG
    {
        public DJ_U8	    m_u8AudioDecodeType;      /*audio decode type*/
        public DJ_U8           m_u8AudioFrameType;       /*audio frame type,reference XMS_AUDIO_AMR_FRAME_TYPE*/
        public DJ_U16	    m_u16AudioDecoderCfgLen;  /*audio decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
        public fixed DJ_U8           m_u8AudioDecoderCfg[ACS_MAX_DECODER_CFG_LEN];/*audio decoder cfg*/
        public DJ_U8           m_u8AudioProfiles;        /*audio profiles?*/
        public DJ_U8           m_u8AudioLevel;		  /*audio level ?*/
        public fixed DJ_U8           m_Rfu1[2];

        public DJ_U8           m_u8VideoDecodeType;      /*video decode type*/
        public DJ_U8           m_u8VideoFrameRate;       /*video frame rate 10 ~ 30*/
        public DJ_U16          m_u16VideoDecoderCfgLen;  /*video decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
        public fixed DJ_U8           m_u8VideoDecoderCfg[ACS_MAX_DECODER_CFG_LEN];/*video decoder cfg?*/
        public DJ_U8           m_u8VideoProfiles;        /*video profiles?*/
        public DJ_U8           m_u8VideoLevel;           /*video level?*/
        public fixed DJ_U8           m_Rfu2[2];  

        public DJ_U32          m_u32TrackNums;           /*track numbers*/
        public DJ_U16          m_u16AudioMaxBitRate;
        public DJ_U16          m_u16AudioAverageBitRate;
        public DJ_U32          m_u32AudioBitMask;
        public DJ_U16          m_u16VideoMaxBitRate;
        public DJ_U16          m_u16VideoAverageBitRate;
        public DJ_U32          m_u32VideoBitMask;
        public DJ_U16          m_u16VideoWidth;
        public DJ_U16          m_u16VideoHeight;
    	
    };/*ITP_3GPP_PARAM_CFG*/

    /*CmdParamData_324CH_t*/
    public struct CmdParamData_324CH_t
    {
	    public DJ_U8	m_u8Channel_Enable;		/* channel enable flag, 1 - enable, 0 - disable*/
    	
	    public DJ_U8	m_u8AudioSRC1_Ctrl;		/* audio channel source 1 type */
	    public DJ_U8	m_u8AudioSRC2_Ctrl;		/* audio channel source 2 type */
	    public DJ_U8	m_u8VideoSRC1_Ctrl;		/* video channel source type */
	    public DJ_U16	m_u16AudioSRC1_ID;		/* audio channel source 1 id */
	    public DJ_U16	m_u16AudioSRC2_ID;		/* audio channel source 2 id */
	    public DJ_U16	m_u16VideoSRC1_ID;		/* video channel source id */

	    public DJ_U8 	m_u8AudioInDecodeFlag;	/* 1 - input decode, 0 - no decode */
	    public DJ_U8 	m_u8AudioOutEncodeFlag; /* 1 - output encode, 0 - no encode */
	    public DJ_U8 	m_u8AudioInCodec;		/* audio input codec */
	    public DJ_U8	m_u8AudioOutCodec;		/* audio output codec */
	    public DJ_U8	m_u8VideoInCodec;		/* video input codec */
	    public DJ_U8	m_u8VideoOutCodec;		/* video output codec */
    };
    
    /*EvtH245OLC*/
	  public struct Evt_H245_OLC
	  {
	  	public DJ_U8	u8ChannelNumber;// logical channel number
	  	public DJ_U8	u8Direction;	// transmit or receive
    	public DJ_U8	u8Codec;		// codec type
	  	public DJ_U8	u8DecoderConfigInfoLen;	//decoder Config Length
	  	public DJ_U8	s8DecoderConfigInfo[MAX_DECODER_CFG_INFO];
	  };
	  
	  /*EvtH245CLC*/
	  public struct Evt_H245_CLC
	  {
    	public DJ_U8	u8ChannelNumber;// logical channel number
    	public DJ_U8	u8Direction;	// transmit or receive
    	public fixed DJ_U8 u8Reserved[2];
    };

    /*EvtH245SIG_PDU*/
    public struct Evt_H245_SIG_PDU
    {

	    public fixed DJ_U8	m_u8H245SigPdu[ACS_MAX_H245_SIG_PDU_LEN];		/* H.245 signal data */
    };

    /*EvtH245USER_INPUT*/
    public struct H245_UII
    {
	    public DJ_U8 m_u8Type;		/* type=1: signal is valid, type=2: str is valid*/
	    public DJ_S8 m_s8Signal;		
	    public fixed DJ_S8 str[126];     
    };

    public  struct ITP_3G_FaxToneStruct_t
    {
	    public DJ_U16  m_u16ChanEnable;  // 1: enable; 0: disable
    };/*ITP_3G_FaxToneStruct_t;*/

    public  struct ITP_3G_FaxToneEventStruct_t
    {
	    public DJ_U16   m_u16ChanState;  //1￡ofax_tone; 0: voice tone
    };/*ITP_3G_FaxToneEventStruct_t;*/

    public struct CmdParamData_FaxSetHeader_t
    {
	    public DJ_S32   s32WithHeader;   /* 0-NoHeader ,1-WithHeader*/
	    public fixed DJ_S8    s8HeaderUser[20];/* User*/
	    public fixed DJ_S8    s8HeaderFrom[20];/* From*/
	    public fixed DJ_S8    s8HeaderTo[20];  /* To */
    };/*CmdParamData_FaxSetHeader_t*/


    /*Acs_SS7RawFrame_Data*/
    public struct Acs_SS7RawFrame_Data
    {
	    public DJ_U8 m_u8UserType; /*SS7 frame user type,reference XMS_SS7_FRAME_USER_TYPE*/
	    public DJ_U8 m_u8LinkType; /*SS7 frame link type,reference XMS_SS7_FRAME_LINK_TYPE*/
	    public DJ_U8 m_u8InfoType; /*SS7 frame info type,reference XMS_SS7_FRAME_INFO_TYPE*/
	    public DJ_U8 m_u8InfoLen;  /*SS7 frame info len*/
	    public fixed DJ_U8 m_u8Rfu1[4];
	    public fixed DJ_U8 m_u8Info[255];/*SS7 frame info*/
	    public DJ_U8 m_u8Rfu2;
    };/**/

    /*Acs_SS7RawFrame_Evt*/
    public struct Acs_SS7RawFrame_Evt
    {
	    public ACS_EVT_HEAD              m_AcsEvtHead;         /*acs event head*/	
	    public Acs_SS7RawFrame_Data		  m_AcsSS7RawFrameData; /*acs ss7 ras frame data*/
    };/**/


    /*Acs_MediaPrivateExt_Data*/
    public struct Acs_MediaPrivateExt_Data
    {
	    public DJ_U32 m_u32ExtType;        //reference to XMS_PRIVATE_EXT_TYPE
	    public fixed DJ_U8  m_u8Buf[MAX_PATH];
    };/*Acs_MediaPrivateExt_Data*/ 


    /*Acs_MediaECM_OffSet*/
    public struct Acs_MediaECM_OffSet
    {
	    public DJ_U32  m_u32Play_FileOffset; //文件偏移,单位为1bytes
	    public DJ_U32  m_u32Play_Max_Length; //期望放音长度(单位：字节)
    };/*Acs_MediaECM_OffSet*/
    public const int Acs_MediaECM_OffSet_Size = 8;

    /*Acs_MediaECM_CMD*/
    public struct Acs_MediaECM_CMD
    {
	    public DJ_U16  m_u16FrameNums;
	    public fixed DJ_U16  m_u16Reserved[3];
	    public fixed byte m_stOffSet[256*Acs_MediaECM_OffSet_Size];
    };/*Acs_MediaECM_CMD*/

    /*Acs_AnalogEM_CMD*/
    public struct Acs_AnalogEM_CMD
    {
	    public DJ_U8	m_u8Channel_Enable;
	    public DJ_U8	m_u8Type;
	    public DJ_U8	m_u8Tx_State;
	    public DJ_U8	m_u8Rx_State;
    };/*Acs_AnalogEM_CMD*/

    /*Acs_FAXECM_MODE_Cmd*/
    public struct Acs_FAXECM_MODE_Cmd
    {
	    public DJ_U8  m_u8FaxECMMode;           /*referent to XMS_FAX_ECM_MODE_TYPE*/	
	    public fixed DJ_U8  m_u8Ref[3];               /*reserve*/
    };/*Acs_FAXECM_MODE_Cmd*/

    /*Acs_SysMon_Data*/
    public struct Acs_SysMon_Data
    {    
        public DJ_U8       m_u8ModuleType;       /*Module type*/
        public DJ_U8       m_u8UnitID;           /*Module unitid*/        
        public DJ_U16      m_u16ModuleState;     /*Module state,reference XMS_SYSMON_MODSTATE*/        
        public fixed DJ_S8       m_s8IPAddress[32];    /*Module IP address*/
        public DJ_U32      m_u32Port;            /*Module port*/
        public fixed DJ_S8       m_s8Rfu[16];          /*rfu*/
    };/**/

    /*Acs_SysMon_Evt*/
    public struct Acs_SysMon_Evt
    {
	    public ACS_EVT_HEAD          m_AcsEvtHead;     /*acs event head*/	
	    public Acs_SysMon_Data       m_AcsSysMonData; /*acs fax proc data*/
    };/**/
    
    /*Acs_VoIP_Regist_Evt*/
		public struct Acs_VoIP_Regist_Evt
		{
		    public ACS_EVT_HEAD	    m_AcsEvtHead;
		    public Acs_VoIP_Regist    	    m_AcsRegist;
		};/*Acs_VoIP_Regist_Evt*/
		
		/*Acs_VoIP_Regist_State_Evt*/
		public struct Acs_VoIP_Regist_State_Evt
		{
		    public ACS_EVT_HEAD	    m_AcsEvtHead;
		    public Acs_VoIP_REGSTATE	    m_AcsRegistState;
		};/*Acs_VoIP_Regist_State_Evt*/
		
		/*Acs_VoIP_Regist_Response_Evt*/
		public struct Acs_VoIP_Regist_Response_Evt
		{
		    public ACS_EVT_HEAD	    	m_AcsEvtHead;
		    public Acs_VoIP_Regist_Response    m_AcsRegistResp;
		};/*Acs_VoIP_Regist_Response_Evt*/
		
		/*Acs_VoIP_ReferResult_Evt*/
		public struct Acs_VoIP_ReferResult_Evt
		{
		    public ACS_EVT_HEAD	    m_AcsEvtHead;
		    public Acs_VoIP_ReferResult    m_AcsReferResult;
		};/*Acs_VoIP_ReferResult_Evt*/
		
		/*Acs_VoIP_MediaInfo_Evt*/
		public struct Acs_VoIP_MediaInfo_Evt
		{
		    public ACS_EVT_HEAD	    m_AcsEvtHead;
		    public Acs_VoIP_MediaInfo	    m_AcsMediaInfo;
		};/*Acs_VoIP_MediaInfo_Evt*/
		
		/*Acs_VoIP_RTPSESSION_Evt*/
		public struct Acs_VoIP_RTPSESSION_Evt
		{
		    public ACS_EVT_HEAD	    m_AcsEvtHead;
		    public Acs_VoIP_RTPSESSION	    m_AcsRtpSession;
		};/*Acs_VoIP_RTPSESSION_Evt*/
		
		/*Acs_VoIP_RTPADDR_Evt*/
		public struct Acs_VoIP_RTPADDR_Evt
		{
		    public ACS_EVT_HEAD	    m_AcsEvtHead;
		    public Acs_VoIP_RTPADDR	    m_AcsRtpAddr;
		};/*Acs_VoIP_RTPADDR_Evt*/
		
		/*Acs_VoIP_RTCPADDR_Evt*/
		public struct Acs_VoIP_RTCPADDR_Evt
		{
		    public ACS_EVT_HEAD	    m_AcsEvtHead;
		    public Acs_VoIP_RTPADDR	    m_AcsRtcpAddr;
		};/*Acs_VoIP_RTCPADDR_Evt*/
		
		/*Acs_VoIP_RTPCODEC_Evt*/
		public struct Acs_VoIP_RTPCODEC_Evt
		{
		    public ACS_EVT_HEAD	    m_AcsEvtHead;
		    public Acs_VoIP_RTPCODEC	    m_AcsRtpCodec;
		};/*Acs_VoIP_RTPCODEC_Evt*/
		
		/*UserEvt_Head_t*/
		public struct UserEvt_Head_t
		{
		  public DJ_U32    m_u32UsrEvtType;     /*User self-define event type*/
			public DJ_U32    m_u32UsrEvtLen;      /*User self-define event length*/
			public fixed DJ_S8     m_Rfu1[4];
			public DJ_Void * m_pUsrEvtData;       /*User self-define event data*/  
		};/**/
		
		/*Acs_UserDef_Evt*/
		public struct Acs_UserDef_Evt
		{
			public ACS_EVT_HEAD      m_AcsEvtHead;     /*acs event head*/	
      public UserEvt_Head_t    m_UsrEvtHead;     /*User self-define event head*/
    };/**/

		/*Acs_ModRelate_Mod*/
		public struct Acs_ModRelate_Mod
		{    	
		    public DJ_U8       m_u8ModuleType;       /*Module type*/
		    public DJ_U8       m_u8UnitID;           /*Module unitid*/        	
				public DJ_U8       m_u8Flag;             /*Relate flag, 0:upper module; 1:lower module*/ 
		    public DJ_S8       m_s8Rfu1;          /*rfu1*/        
		    public fixed DJ_S8       m_s8IPAddress[32];    /*Module IP address*/
		    public DJ_U32      m_u32Port;            /*Module port*/
		    public fixed DJ_S8       m_s8Rfu2[4];           /*rfu2*/
		};/**/
		
		/*Acs_ModRelate_Data*/
		public struct Acs_ModRelate_Data
		{    
			public DJ_U8                m_u8ModCount;         /*Relate module count*/
			public DJ_U8                m_u8SrcModType;
			public DJ_U8                m_u8SrcModUnitID;
			public DJ_S8                m_rfu1;
		  public fixed Acs_ModRelate_Mod    m_RelateMod[64]; /*Relate module info*/    
		};/**/
		
		/*Acs_ModRelate_Evt*/
		public struct Acs_ModRelate_Evt
		{
			public ACS_EVT_HEAD          m_AcsEvtHead;     /*acs event head*/	
			public Acs_ModRelate_Data    m_AcsModRelateData; /*acs fax proc data*/
		};/**/
		
		/*Acs_VoIPMon_Data*/
		public struct Acs_VoIPMon_Data
		{    
			public DJ_U32               m_u32DataLen;
			public DJ_U8                m_u8MonData[ITP_VOIP_MONDATA_MAX];     /*VoIP Mon data*/	
		};/**/
		
		/*Acs_ModRelate_Evt*/
		public struct Acs_VoIPMon_Evt
		{
			public ACS_EVT_HEAD          m_AcsEvtHead;     /*acs event head*/	
			public Acs_VoIPMon_Data      m_AcsVoIPMonData; /*acs VoIP mon data*/
		};/**/
		
		public struct ACS_Digital_PortState_Data
		{
			public DJ_U8	m_u8Lost_signal;	//1:无信号，0：有信号
			public DJ_U8	m_u8Fas_align;	//0：同步，1：失步
			public DJ_U8	m_u8Mf_align; 	//0：同步，1：失步
			public DJ_U8	m_u8Crc4_align; 	//0：同步，1：失步
			public DJ_U8	m_u8Remote_alarm; 	//0：无告警，1：远端告警
			public DJ_U8	m_u8Remote_MF_alarm;	//0：无告警，1：远端告警
			public DJ_U8	m_u8Rx_level;	//0-15: *(-2.5db)
			public DJ_U8	m_u8Tx_open;	//1:open circuit,
			public DJ_U8	m_u8Tx_overlimit;	//1:current over limit
			public DJ_U8	m_u8Port_Current_State;	//0: error state; 1: normal working state
			public DJ_U8	m_u8Port_Normal_Count;	//seconds of digital port normal working
			public DJ_U8	m_u8Port_Error_Count;	// seconds of digital port error
			public DJ_U32	m_u32total_seconds;	//统计总时间
			public DJ_U32	m_u32RLOS_seconds;	//接收失步总秒数
			public DJ_U32 	m_u32LRCL_seconds;	//接收无信号总秒数
			public DJ_U32 	m_u32RUA1_seconds;	//接收全1信号总秒数
			public DJ_U32 	m_u32RRA_seconds;	//远端告警总秒数
			public DJ_U32 	m_u32RDMA_seconds;	//远端CAS复帧告警总秒数
			public DJ_U32 	m_u32ILUT_seconds;	//接收电平过低总秒数
			public DJ_U32 	m_u32JALT_seconds;	//抖动超限总秒数
			public DJ_U32 	m_u32TOCD_seconds;	//发送开路错误总秒数
			public DJ_U32 	m_u32TCLE_seconds;	//发送短路错误总秒数
			public DJ_U32 	m_u32RSLIP_seconds;	//接收滑码错误总秒数
			public DJ_U32 	m_u32TSLIP_seconds;	//发送滑码错误总秒数
			public DJ_U32 	m_u32LCVCR_count;	//接收线路码型错误总计数
			public DJ_U32 	m_u32PCVCR_count;	//接收CRC4错误总计数
			public DJ_U32 	m_u32FOSCR_count;	//接收FAS错误总计数
			public DJ_U32 	m_u32EBCR_count;		//远端CRC4 E-BIT总计数
			public DJ_U32	m_u32HDLC1_Tx_packets;	//HDLC1发送包计数
			public DJ_U32	m_u32HDLC1_Rx_goodpk;	//HDLC1接收正确包计数
			public DJ_U32	m_u32HDLC1_Rx_badpk;		//HDLC1接收错误包计数
			public DJ_U32	m_u32HDLC2_Tx_packets;	//HDLC2发送包计数
			public DJ_U32	m_u32HDLC2_Rx_goodpk;	//HDLC2接收正确包计数
			public DJ_U32	m_u32HDLC2_Rx_badpk;		//HDLC2接收错误包计数
			public DJ_U8	m_u8E1Type;		/*E1 type*/
			public fixed DJ_U8	m_u8Rfu[3];	/**/
		};
		
		public struct ACS_Digital_PortState_Evt
		{
      public ACS_EVT_HEAD                 m_AcsEvtHead;
      public ACS_Digital_PortState_Data   m_AcsDigitalPortStateData;
		};
		
		public struct ACS_Clock_RefSrc_State_Data
		{
		  public DJ_U8     m_u8ModuleID;            /*The Module ID Of DSP*/
		  public DJ_U8     m_u8E1ID;                /*The E1 ID Of A DSP*/
		  public DJ_U8     m_u8State;               /*The E1's Master Clock Ref Source Of A DSP, Reference to XMS_CLK_STATE_TYPE*/
			public DJ_U8     m_u8ClockType;           /*Keygoe current clock type is slave or master,Reference XMS_BOARD_EXT_CLOCK_TYPE*/
		  public fixed DJ_U8     m_u8Ref[4];              /*Reserve*/
		};
		
		public struct ACS_Clock_RefSrc_State_Evt
		{
		  public ACS_EVT_HEAD                  m_AcsEvtHead;
		  public ACS_Clock_RefSrc_State_Data   m_AcsClockRefSrcStateData;  
		};
		
		/* Acs VoIP SIP User Agent struct */
		public struct Acs_VoIP_SIP_User_Agent
		{
			public fixed DJ_S8	m_s8UserAgent[40];	/* Sip User Agent Name with version No */
		};/*Acs_VoIP_SIP_User_Agent*/
		
		/* Acs VoIP SIP Diversion Information struct */
		public struct Acs_VoIP_Call_Diversion_Info
		{
			public fixed DJ_S8	m_s8Diversion[64];	/* Sip Call Diversion URL */
	    public fixed DJ_S8	m_s8Reason[16];		/* Sip Call Diversion Reason */
    };/*Acs_VoIP_Call_Diversion_Info*/

#endregion

#region DJAcsCmdDef.h
    
    public enum ACS_CMD_TYPE
    {	
	    ACS_CMD_TYPE_GETDEVLIST  = 0x01,
	    ACS_CMD_TYPE_OPENDEVICE,
	    ACS_CMD_TYPE_CLOSEDEVICE,
	    ACS_CMD_TYPE_RESETDEVICE,
	    ACS_CMD_TYPE_GETDEVICESTATE,
	    ACS_CMD_TYPE_SETDEVGROUP,	
	    ACS_CMD_TYPE_SETDEVPARAM,	
	    ACS_CMD_TYPE_GETDEVPARAM,	
	    ACS_CMD_TYPE_MAKECALLOUT,
	    ACS_CMD_TYPE_ALERTCALL,
	    ACS_CMD_TYPE_ANSWERCALLIN,	
	    ACS_CMD_TYPE_LINKDEV,
	    ACS_CMD_TYPE_UNLINKDEV,	
	    ACS_CMD_TYPE_CLEARCALL,
	    ACS_CMD_TYPE_JOINTOCONF,
	    ACS_CMD_TYPE_LEAVEFROMCONF,
	    ACS_CMD_TYPE_CLEARCONF,
	    ACS_CMD_TYPE_PLAYFILE,
	    ACS_CMD_TYPE_INITPLAYINDEX,
	    ACS_CMD_TYPE_BUILDPLAYINDEX,
	    ACS_CMD_TYPE_CONTROLPLAY,
	    ACS_CMD_TYPE_RECORDFILE,
	    ACS_CMD_TYPE_CONTROLRECORD,
	    ACS_CMD_TYPE_SENDFAX,
	    ACS_CMD_TYPE_STOPSENDFAX,
	    ACS_CMD_TYPE_RECVFAX,
	    ACS_CMD_TYPE_STOPRECVFAX,
	    ACS_CMD_TYPE_CHANGEMONITORFILTER,	
	    ACS_CMD_TYPE_SENDIO,	
	    ACS_CMD_TYPE_SENDSIGMSG,
	    ACS_CMD_TYPE_RECORDCSP,	
	    ACS_CMD_TYPE_DBGON,
	    ACS_CMD_TYPE_DBGOFF,    
        ACS_CMD_TYPE_PLAY_3GPP,
        ACS_CMD_TYPE_CONTROL_3GPP_PLAY,
        ACS_CMD_TYPE_RECORD_3GPP,
        ACS_CMD_TYPE_CONTROL_3GPP_RECORD,    		
	    ACS_CMD_TYPE_PLAYCSP,
	    ACS_CMD_TYPE_SENDPLAYCSP,
	    ACS_CMD_TYPE_QUERYLIC,
	    ACS_CMD_TYPE_CTXREG,
	    ACS_CMD_TYPE_CTXLINK,
	    ACS_CMD_TYPE_CTXSENDAPPDATA,
	    ACS_CMD_TYPE_INIT3GPPINDEX,
	    ACS_CMD_TYPE_BUILD3GPPINDEX,
	    ACS_CMD_TYPE_SENDRAWFRAME,
    };

    public enum CTX_APPDATA_RET
    {
	    CTX_APPDATA_RET_SUCCESS		= 0x0,
	    CTX_APPDATA_RET_NODEST		= 0x4,
	    CTX_APPDATA_RET_NOSRC  		= 0x5,
	    CTX_APPDATA_DEST_RECVOK     = 0xFF,
    };
    /*Acs_Cmd_t*/
    public struct Acs_Cmd_t
    {	
	    public ACSHandle_t      m_s32AcsHandle;    /*acs handle*/	
        public DeviceID_t       m_ITPDeviceID;      /*Device id*/
	    public AcsCmdTye_t      m_s32CmdType;      /*command type*/
	    public fixed ParmName_t       m_s8PackName[64];  /*parmeter name*/
	    public ParmSize_t       m_s32PackSize;     /*parmeter size*/
	    public DJ_U8            m_u8AcsId;         /*acs server use*/
	    public fixed DJ_S8            m_Rfu1[3];
    };/*Acs_Cmd_t*/

    /*ACS Cmd Head*/
    public struct ACS_CMD_HEAD
    {
	    public PKG_HEAD_STRUCT  m_ITPPkgCmdHead;   /*ITP package head*/	
	    public Acs_Cmd_t        m_ITPAcsCmd_t;     /*acs command package head*/
    };/**/

    /*ACS open device parm*/
    public struct OpenDevParm_t
    {
	    public DJ_S32      m_s32Resrv;/*Reserved*/
    };/**/

    /*ACS close device parm*/
    public struct CloseDevParm_t
    {
	    public DJ_S32      m_s32Resrv;/*Reserved*/
    };/**/

    public struct ResetDevParm_t
    {
	    public DJ_S32      m_s32Resrv;/*Reserved*/
    };/**/

    public struct GetDevStateParm_t
    {
	    public DJ_S32      m_s32Resrv;/*Reserved*/
    };/**/

    /*ACS set device group parm*/
    public struct SetDevGroupParm_t
    {
	    public DJ_S32      m_s32Resrv;/*Reserved*/
    };/**/

    /*ACS callout parm*/
    public struct CalloutParm_t
    {	
	    public fixed CallNum_t       m_s8CallingNum[ACS_MAX_CALL_NUM];/*calling id*/
	    public fixed CallNum_t       m_s8CalledNum[ACS_MAX_CALL_NUM];/*called id*/
    };/**/

    public struct SetParm_t
    {	
	    public DJ_U16              m_u16ParamCmdType;
	    public DJ_U16              m_u16ParamDataSize;
    };/**/

    public struct GetParm_t
    {
	    public DJ_U16              m_u16ParamCmdType;
	    public DJ_U16              m_u16ParamDataSize;
    };/**/

    /*ACS callin parm*/
    public struct AlertCallParm_t
    {
	    public DJ_S32        m_s32Resrv;/*Reserved*/
    };/**/

    /*ACS callin parm*/
    public struct AnswerCallInParm_t
    {
	    public DJ_S32        m_s32Resrv;/*Reserved*/
    };/**/

    /*ACS Link Device parm*/
    public struct LinkDevParm_t
    {
	    public DeviceID_t        m_ITPDestDeviceID;/*Device id*/
    };/**/

    /*ACS UnLink parm*/
    public struct UnlinkDevParm_t
    {
	    public DeviceID_t        m_ITPDestDeviceID;/*Device id*/
    };/**/

    /*ACS XMS Reg parm*/
    public struct XMSCtxRegParm_t
    {
	    public fixed DJ_S8   m_s8RegName[XMS_MAX_REGNAME_LEN];/*Reg Name*/	
	    public DJ_U8   m_u8RegType;  /*1:Reg; 2: unReg,reference XMS_CTX_REG_TYPE*/
	    public DJ_U8   m_u8AcsUnitID;
	    public fixed DJ_S8   m_Rfu1[2];
	    public DJ_S32  m_s32Rst;
    };

    /*ACS XMS ctxlink parm*/
    public struct XMSCtxLinkParm_t
    {
	    public DJ_U8	      m_u8CtxLinkOpt;/*link option,reference CTX_LINK_OPTION*/
	    public DJ_U8         m_u8AcsUnitID;
	    public fixed DJ_S8         m_Rfu1[2];
	    public DeviceID_t    m_srcDev;
	    public DeviceID_t    m_destDev;
	    public DJ_S32        m_s32Rst;
    };

    /*ACS App Data Info*/
    public struct XMS_AppData_Info_t
    {
	    public DJ_U32      m_u32AppDataSize; /*user APP data size,not include XMS_AppData_Info_t*/
	    public DJ_U8       m_u8AppReqType;   /*user APP req cmd type,user self define*/
	    public DJ_U8       m_u8AcsUnitID;
	    public fixed DJ_U8       m_Rfu1[2];      
	    public fixed DJ_S8       m_s8SrcRegName[XMS_MAX_REGNAME_LEN]; /*src reg name*/
	    public fixed DJ_S8       m_s8DestRegName[XMS_MAX_REGNAME_LEN];/*dest reg name*/
	    public DJ_U8       m_u8SrcAppUnitID;
	    public DJ_U8       m_u8DstAppUnitID;
	    public fixed DJ_S8       m_Rfu2[2];
	    public DeviceID_t  m_srcDevice;
	    public fixed DJ_S8       m_Rfu3[20];
	    public DJ_S32      m_s32Rst;
    };/**/

    /*ACS clearcall parm*/
    public struct ClearCallParm_t
    {
	    public DJ_S32        m_s32ClearCause;/*Reserved*/
	    public DJ_S32        m_s32Resrv;/*Reserved*/
    };/**/

    /*ACS Jointo conf parm*/
    public struct JoinToConfParm_t
    {
	    public DeviceID_t           m_ITPMediaDevice;/*media device*/
        public CmdParamData_Conf_t  m_ITPConfParam;  /*Conf param*/ 
    };/**/

    /*ACS Leave conf parm*/
    public struct LeaveFromConfParm_t
    {
	    public DeviceID_t           m_ITPMediaDevice;/*media device*/    
	    public CmdParamData_Conf_t  m_ITPConfParam;  /*Conf param*/ 
    };/**/

    public struct ClearConfParm_t
    {
        public DJ_S32       m_s32Resrv;/*Reserved*/
    };/*Clear conf param*/

    /*ACS play parm*/
    public struct PlayParm_t
    {    	
	    public PlayProperty_t       m_PlayProperty;   /*playProperty*/	
    };/**/

    public struct InitPlayIndexParm_t
    {
	    public DJ_S32               m_s32Reserved;     /**/
    };/**/

    public struct BuildPlayIndexParm_t
    {	
	    public PlayProperty_t   m_ITPPlayProperty;/**/
    };/**/

    /*ACS control play parm*/
    public struct ControlPlayParm_t
    {
	    public ControlPlay_t  m_ITPControlPlay; /*control play parmeter*/
    };/**/

    /*ACS record parm*/
    public struct RecordParm_t
    {	
	    public RecordProperty_t    m_ITPRecordProperty;/*record property set*/
    };/**/

    /*ACS control record parm*/
    public struct ControlRecordParm_t
    {
	    public ControlRecord_t  m_ITPControlRecord;/*control record set*/
    };/**/

    /*ACS record Ram parm*/
    public struct RecordCSPParm_t
    {	
	    public RecordCSPProperty_t    m_ITPRecordCSPProperty;/*record CSP property set*/
    };/**/

    public const int ITP_MAX_STREAM_DATA_LENGTH = 4000;

    /*ACS CSPPlayParm_t*/
    public struct CSPPlayParm_t
    {	
	    public CSPPlayProperty_t            m_ITPCSPPlayProperty;     /*ITP csp play property*/
    };/**/

    /*CSPPlayData*/
    public struct CSPPlaySendDataParm_t
    {
	    public PKG_HEAD_STRUCT        m_ITPPkgCmdHead;      /*ITP package head*/
	    public CSPPlayDataInfo_t      m_CspPlayDataInfo;    /*csp play data info*/
	    public fixed DJ_U8                  m_u8StreamData[ITP_MAX_STREAM_DATA_LENGTH ];	/*stream data*/
    };/**/

    /*ACS monitor filter parm*/
    public struct MonitorFilterParm_t
    {
	    public DJ_U32                m_u32MonitorFilter;/*event monitor filter,reference ACS_IOEVT_MASK*/
    };/**/

    /*ACS send io parm*/
    public struct SendIOParm_t
    {	
        public DJ_U16         m_u16IoType;     /*io proc type*/
	    public DJ_U16         m_u16IoDataLen;  /*io data len*/  
    };/*IO data pack*/

    /*ACS send Signal Msg Type*/
    public struct SendSigMsgParm_t
    {	
        public DJ_U16         m_u16SigMsgType;     /*Signal Msg Type*/
	    public fixed DJ_S8          m_s8Rfu[2];          /*Rfu*/  
    };/**/

    /*fax_shakehand_param*/
    public struct FaxHandShake_t
    {
	    public DJ_U8   m_u8Handshake_Result;   /*T30 handshake result*/
	    public fixed DJ_U8	m_u8Local_ID[20];
	    public fixed DJ_U8	m_u8Remote_ID[20];
	    public DJ_U8	m_u8Modem_Type;		/*F144_MODEM,F96_MODEM,F48_MODEM*/
	    public DJ_U8	m_u8Fax_Speed;          /*2400,4800,7200,9600,12000,14400*/
	    public DJ_U8	m_u8Dencity;		/*T4_LOW_DENSITY or T4_HIGH_DENSITY*/
	    public DJ_U8	m_u8Encode_Type;   /*T4_MH_ENCODE or T4_MR_ENCODE or T6_ENCODE*/
	    public DJ_U8	m_u8Line_Width;		
	    public DJ_U8	m_u8Min_Scanline_Time; 	/*minimum scanline time in ms, 0 for no limit*/
	    public DJ_U8	m_u8Page_Length;		
	    public DJ_U8	m_u8Ecm_Support;	/*ECM_SUPPORT or ECM_UNSUPPORT*/
	    public DJ_U8   m_u8Host_Control;  //host command
	    public fixed DJ_U8   m_u8Reserve[6];
	    public DJ_U32  m_u32Total_Page_Num;  //total sending page num, set by Ap when sending fax

    };/*FaxHandShake_t*/

    /*faxReceivePageParam*/
    public struct  FaxPageAttri_t
    {
	    public DJ_U32	  m_u32PageNo;       //当前页的页号，从1开始
	    public DJ_U32	  m_u32ByteCount;    //当前页的总字节数	
	    public DJ_U8	  m_u8YResolution;	 //垂直分辨率，低分辨率0， 高分辨率1
	    public DJ_U8	  m_u8EncodeType;    //MH 0， MR 1， MMR 2
	    public DJ_U8	  m_u8PageWidth;	 //页宽0代表1728
	    public DJ_U8	  m_u8MinScanlineTime;  //最小行扫描时间
	    public DJ_U32    m_u32PageOffset;     //页数据偏移量
	    public DJ_U32    m_u32FillOrder;      //字节的bit位顺序
	    public DJ_U32    m_u32XResolution;    //水平分辨率      
	    public fixed DJ_U32    m_u32Reserve[10];    //保留

    };/*FaxRecvPage_t*/


    public struct FaxLocalSpec_t
    {
	    public DJ_U8	m_u8Modem_Type;		
	    public DJ_U8	m_u8Fax_Speed;          
	    public DJ_U8	m_u8Dencity;		
	    public DJ_U8	m_u8Encode_Type;  
	    public DJ_U8	m_u8Line_Width;		
	    public DJ_U8	m_u8Min_Scanline_Time; 	
	    public DJ_U8	m_u8Page_Length;		
	    public DJ_U8	m_u8Ecm_Support;	
	    public fixed DJ_U8	m_u8Remote_ID[20]; 
    };/*FaxLocalSpec_t*/

    public struct FaxEndingParam_t
    {
	    public DJ_U16  m_u16Fax_Channel_ID;    //Fax Chan
	    public DJ_U16  m_u16Fax_End_Flag;      //Fax end flag
	    public DJ_U8	m_u8Last_Error_Code;	//error code of last fax operation
	    public DJ_U8	m_u8Last_Error_State;	//error state of last fax operation
	    public DJ_U8	m_u8Last_Send_T30_Command_State;//store the state the T30 command just sent
	    public DJ_U8	m_u8Last_Rcv_T30_Command;	//store the T30 command just received
	    public DJ_U16	m_u16Total_Page_Num;		//total pages,send: sending total pages successfully  ;rev: receiving total pages successfully
        public fixed DJ_U8	m_u8Remote_Id[20];
    };/*FaxEndingParam_t*/

    public struct FaxRemoteSepc_t
    {
	    public DJ_U8	m_u8Modem_Type;		//F144_MODEM,F96_MODEM,F48_MODEM
	    public DJ_U8	m_u8Fax_Speed;		//BPS_14400,BPS_12000,BPS_9600,BPS_7200,BPS_4800,BPS_2400
	    public DJ_U8	m_u8Dencity;		//T4_LOW_DENSITY or T4_HIGH_DENSITY
	    public DJ_U8	m_u8Encode_Type;	//T4_MH_ENCODE or T4_MR_ENCODE or T6_ENCODE
	    public DJ_U8	m_u8Line_Width;		//see line width list
	    public DJ_U8	m_u8Min_Scanline_Time; 	//minimum scanline time in ms, 0 for no limit
	    public DJ_U8	m_u8Page_Length;		//
	    public DJ_U8	m_u8Ecm_Support;	//ECM_SUPPORT or ECM_UNSUPPORT
    };/*FaxRemoteSepc_t*/

    /*Fax_Page_t*/
    public struct Fax_Page_t
    {
	    public DJ_U16	 m_u16Total_Page_Num;        //总共需要发送的页数
	    public DJ_U16	 m_u16Send_EOM_Flag;        //页后控制
	    public DJ_U32	 m_u32Current_Page_Offset;  //页偏移    
	    public DJ_U32	 m_u32Current_Page_Bytes;	     //当前页的字节数
    };/*Fax_Page_t*/

    /*SendFaxParm_t*/
    public struct SendFaxParm_t
    {
	    public fixed DJ_S8   	   m_s8LocalID[ACS_LOCALID_MAX_LEN]; /*Local ID*/	
	    public fixed DJ_S8          m_s8FaxTiffFile[MAX_PATH];        /*fax tiff file*/
	    public DeviceID_t     m_ITPMediaDeviceID;               /*Media deviceID*/	
    };/**/

    /*StopSendFaxParm_t*/
    public struct StopSendFaxParm_t
    {	
	    public fixed DJ_S8          m_s8Rfu1[4]; /*Reserved*/	
    };/**/

    /*RecvFaxParm_t*/
    public struct RecvFaxParm_t
    {
	    public fixed DJ_S8   	   m_s8LocalID[ACS_LOCALID_MAX_LEN]; /*fax Local ID*/	
	    public fixed DJ_S8          m_s8FaxTiffFile[MAX_PATH];        /*fax tiff file*/
	    public DeviceID_t     m_ITPMediaDeviceID;               /*media deviceID*/
    };/**/

    /*StopRecvFaxParm_t*/
    public struct StopRecvFaxParm_t
    {	
	    public fixed DJ_S8          m_s8Rfu1[4]; /*Reserved*/	
    };/**/

    public struct InitPlay3gppIndexParm_t
    {
	    public DJ_S32               m_s32Reserved;     /**/
    };/**/

    public struct BuildPlay3gppIndexParm_t
    {	
	    public Play3gppProperty_t   m_ITPPlayProperty;/**/
    };/**/

    /*ACS 3gpp play parm*/
    public struct Play3gppParm_t
    {    	
	    public Play3gppProperty_t       m_PlayProperty;   /*Play3gppProperty_t*/	
    };/**/

    /*ACS control play parm*/
    public struct Control3gppPlayParm_t
    {
	    public Control3gppPlay_t  m_ITPControlPlay; /*control play parmeter*/
    };/**/

    /*ACS record parm*/
    public struct Record3gppParm_t
    {	
	    public Record3gppProperty_t    m_ITPRecordProperty;/*record property set*/
    };/**/

    /*ACS control record parm*/
    public struct Control3gppRecordParm_t
    {
	    public Control3gppRecord_t  m_ITPControlRecord;/*control record set*/
    };/**/

    /*ACS Query License parm*/
    public struct QueryLicenseParm_t
    {
	    public DJ_U8     m_u8ModuleID; /*Board module ID*/
	    public fixed DJ_S8     m_Rfu1[3];    /*Rfu*/
    };/**/

    /*SendRawFrameParm_t*/
    public struct SendRawFrameParm_t
    {		
	    public DJ_U16              m_u16FrameSize;
	    public DJ_U16              m_Rfu1;
    };/**/
        
    /*Acs_cmd*/
    public struct Acs_Cmd   // 根据以下定义自行组织结构内容 UNION在C#中不存在
    {
	    /*public ACS_CMD_HEAD     m_ITPAcsCmdHead;//acs cmd head
	    union
	    {
		    OpenDevParm_t          m_ITPAcsOpenDevParm;       //open devcie parm
		    CloseDevParm_t         m_ITPAcsCloseDevParm;      //Close device parm
		    ResetDevParm_t         m_ITPAcsResetDevParm;      //Reset device parm
		    GetDevStateParm_t      m_ITPAcsGetDevStateParm;   //Get device state parm
		    SetDevGroupParm_t      m_ITPAcsSetDevGrpParm;     //set device group parm
		    CalloutParm_t          m_ITPAcsCallOutParm;       //callout parm
		    SetParm_t              m_ITPAcsSetParm;           //set parm
		    GetParm_t              m_ITPAcsGetParm;           //get parm
		    AnswerCallInParm_t     m_ITPAcsAnSwerCallInParm;  //answer callin parm
		    LinkDevParm_t          m_ITPAcsLinkDevParm;       //Link device parm
		    UnlinkDevParm_t        m_ITPAcsUnlinkDevParm;     //Unlink device parm		
		    ClearCallParm_t        m_ITPAcsClearCallParm;     //clear call parm		
		    JoinToConfParm_t       m_ITPAcsJoinToConfParm;    //join to conf parm
		    LeaveFromConfParm_t    m_ITPAcsLeaveConfParm;     //Leave from conf parm
		    PlayParm_t             m_ITPAcsPlayParm;          //play file parm
		    InitPlayIndexParm_t    m_ITPAcsInitPlayIndex;     //Init play index
		    BuildPlayIndexParm_t   m_ITPAcsBuildPlayIndex;    //Build play idnex
		    ControlPlayParm_t      m_ITPAcsCtrlPlayParm;      //control play parm
		    RecordParm_t           m_ITPAcsRecordParm;        //record file parm
		    ControlRecordParm_t    m_ITPAcsCtrlRecordParm;    //control record parm			
		    SendFaxParm_t          m_ITPAcsSendFaxParm;       //send  fax parm
		    StopSendFaxParm_t      m_ITPAcsStopSendFaxParm;   //stop send fax parm
		    SendFaxParm_t          m_ITPAcsRecvFaxParm;       // recv fax parm
		    StopRecvFaxParm_t      m_ITPAcsStopRecvFaxParm;   //stop recv fax parm
		    MonitorFilterParm_t    m_ITPAcsMonFilterParm;     //monitor filter parm
		    SendIOParm_t           m_ITPAcsSendIoParm;        //send io parm  
		    Play3gppParm_t             m_ITPAcsPlay3gpParm;          //play 3gp file parm
		    Control3gppPlayParm_t      m_ITPAcsCtrl3gpPlayParm;      //control 3gp play parm
		    Record3gppParm_t           m_ITPAcsRecord3gpParm;        //record 3gp file parm
		    Control3gppRecordParm_t    m_ITPAcsCtrl3gpRecordParm;    //control 3gp record parm			
	    };//acs cmd parm
	    public PrivateData_t    m_ITPPrivateData;//private data*/
    };/**/
    
    public struct Acs_DevSub_Info
    {
	    public DJ_S16      m_s16DeviceSub;
	    public DJ_S16      m_s16StartTs;
	    public DJ_S16      m_s16DeviceNum;
	    public DJ_S16      m_Rfu1;
    };
    public const int Acs_DevSub_Info_Size = 8;

    public struct Acs_Dev_Info
    {
	    public DJ_S8             m_s8MachID;
	    public DJ_S8             m_s8ModuleID;	
	    public DJ_S16            m_s16DeviceMain;
	    public DJ_S16            m_s16DevSubNum;	
	    public DJ_S16            m_Rfu1;
	    public fixed byte   m_DevSub[128*Acs_DevSub_Info_Size];
    };

#endregion

#region ITPCom.h

    public const int ITP_SYSTEM_FLAG = 0x49545031; 

    public  struct LICENCE_INFO_STRUCT
    {	
	    public DJ_S32          m_ItpFlag;       //
        public DJ_U8           m_u8ModuleType;  //
	    public DJ_U8           m_u8MainFuncId;  //
	    public DJ_U8           m_u8SubFuncId;   //
	    public DJ_U8           m_u8UnitId;      //
    	
	    public DJ_S32          m_Version;       //
	    public DJ_S32          m_AckInfo;       //
    	
	    public PKG_HEAD_STRUCT m_PkgHead;       //
	    public fixed DJ_S8           m_s8Username[32];//
	    public fixed DJ_S8           m_s8Password[32];//
        public fixed DJ_U8           m_u8Reserved[36];//
    };

    public struct CONN_INFO_STRUCT
    {
	    public DJ_SOCKET     m_SkForListen;     //
	    public DJ_SOCKET     m_SkForClient;     //
	    public fixed DJ_S8         m_szIP[32];        //
	    public DJ_S32        m_Port;            //

	    public LICENCE_INFO_STRUCT Licence;	
    };

#endregion

#region ITPComErrorCode.h

/*#ifdef WIN32*/
	public const int DJ_EINTR = 10004;     // Interrupted system call
	public const int DJ_EBADF = 10009 ;    // Bad file number
	public const int DJ_EACCES = 10013 ;    // Permission denied
	public const int DJ_EFAULT = 10014  ;   // Bad address
	public const int DJ_EINVAL = 10022   ;  // Invalid argument
	public const int DJ_EMFILE = 10024    ; // Too many open files
	public const int DJ_EWOULDBLOCK = 10035;     // Resource temporarily unavailable
	public const int DJ_EINPROGRESS = 10036 ;    // Operation now in progress
	public const int DJ_EALREADY = 10037     ;// Operation already in progress
	public const int DJ_ENOTSOCK = 10038     ;// Socket operation on nonsocket
	public const int DJ_EDESTADDRREQ = 10039  ;   // Destination address required
	public const int DJ_EMSGSIZE = 10040    ; // Message too long
	public const int DJ_EPROTOTYPE = 10041   ;  // Protocol wrong type for socket
	public const int DJ_ENOPROTOOPT = 10042   ;  // Bad protocol option
	public const int DJ_EPROTONOSUPPORT = 10043;     // Protocol not supported
	public const int DJ_ESOCKTNOSUPPORT = 10044 ;    // Socket type not supported
	public const int DJ_EOPNOTSUPPORT = 10045    ; // Operation not supported on transport endpoint
	public const int DJ_EPFNOSUPPORT = 10046    ; // Protocol family not supported
	public const int DJ_EAFNOSUPPORT = 10047 	;   // Address family not supported by protocol family
	public const int DJ_EADDRINUSE = 10048     ;// Address already in use
	public const int DJ_EADDRNOTAVAIL = 10049   ;  // Cannot assign requested address
	public const int DJ_ENETDOWN = 10050     ;// Network is down
	public const int DJ_ENETUNREACH = 10051   ;  // Network is unreachable
	public const int DJ_ENETRESET = 10052    ; // Network dropped connection on reset
	public const int DJ_ECONNABORTED = 10053  ;   // Software caused connection abort
	public const int DJ_ECONNRESET = 10054    ; // Connection reset by peer
	public const int DJ_ENOBUFS = 10055    ; // No buffer space available
	public const int DJ_EISCONN = 10056    ; // Socket is already connected
	public const int DJ_ENOTCONN = 10057    ; // Socket is not connected
	public const int DJ_ESHUTDOWN = 10058    ; // Cannot send after socket shutdown
	public const int DJ_ETIMEDOUT = 10060     ;// Connection timed out
	public const int DJ_ECONNREFUSED = 10061   ;  // Connection refused
	public const int DJ_EHOSTDOWN = 10064     ;// Host is down
	public const int DJ_EHOSTUNREACH = 10065   ;  // No route to host
/*#else
	public const int DJ_EINTR = 4 ;        // Interrupted system call
	public const int DJ_EBADF = 9  ;       // Bad file number
	public const int DJ_EACCES = 13 ;       // Permission denied
	public const int DJ_EFAULT = 14  ;      // Bad address
	public const int DJ_EINVAL = 22   ;     // Invalid argument
	public const int DJ_EMFILE = 24    ;    // Too many open files
	public const int DJ_EWOULDBLOCK = 11;        // Resource temporarily unavailable
	public const int DJ_EINPROGRESS = 115;       // Operation now in progress
	public const int DJ_EALREADY = 114    ;   // Operation already in progress
	public const int DJ_ENOTSOCK = 88      ;  // Socket operation on nonsocket
	public const int DJ_EDESTADDRREQ = 89   ;     // Destination address required
	public const int DJ_EMSGSIZE = 90        ;// Message too long
	public const int DJ_EPROTOTYPE = 91;        // Protocol wrong type for socket
	public const int DJ_ENOPROTOOPT = 92;        // Bad protocol option
	public const int DJ_EPROTONOSUPPORT = 93;        // Protocol not supported	
	public const int DJ_ESOCKTNOSUPPORT = 94 ;       // Socket type not supported
	public const int DJ_EOPNOTSUPPORT = 95    ;    // Operation not supported on transport endpoint
	public const int DJ_EPFNOSUPPORT = 96      ;  // Protocol family not supported
	public const int DJ_EAFNOSUPPORT = 97 	    ; // Address family not supported by protocol family
	public const int DJ_EADDRINUSE = 98    ;    // Address already in use
	public const int DJ_EADDRNOTAVAIL = 99  ;      // Cannot assign requested address
	public const int DJ_ENETDOWN = 100   ;    // Network is down
	public const int DJ_ENETUNREACH = 101 ;      // Network is unreachable
	public const int DJ_ENETRESET = 102    ;   // Network dropped connection on reset
	public const int DJ_ECONNABORTED = 103  ;     // Software caused connection abort
	public const int DJ_ECONNRESET = 104     ;  // Connection reset by peer
	public const int DJ_ENOBUFS = 105;       // No buffer space available
	public const int DJ_EISCONN = 106 ;      // Socket is already connected
	public const int DJ_ENOTCONN = 107 ;      // Socket is not connected
	public const int DJ_ESHUTDOWN = 108 ;      // Cannot send after socket shutdown
	public const int DJ_ETIMEDOUT = 110  ;     // Connection timed out
	public const int DJ_ECONNREFUSED = 111;       // Connection refused
	public const int DJ_EHOSTDOWN = 112    ;   // Host is down
	public const int DJ_EHOSTUNREACH = 113  ;     // No route to host
#endif*/

////////////////////  These error code value of our own system  /////////////////////////
    public const int DJ_ITPCOM_ERRBASE = 20000   ;  // Start error code

    public const int DJ_EPARAMETER = (DJ_ITPCOM_ERRBASE + 1);  // Parameter error
    public const int DJ_ENODATA = (DJ_ITPCOM_ERRBASE + 2)  ;// Receive no data or enough data
    public const int DJ_EMEMALLOC = (DJ_ITPCOM_ERRBASE + 3) ; // Allocate memory error
    public const int DJ_EMAXSOCKET = (DJ_ITPCOM_ERRBASE + 4) ; // Have set up  128 socket (max)
    public const int DJ_EAUTHORIZE = (DJ_ITPCOM_ERRBASE + 5);  // Authorization not passed
    public const int DJ_EPKGFLAG = (DJ_ITPCOM_ERRBASE + 6) ; // Package flag error
    public const int DJ_ESENDSELECT = (DJ_ITPCOM_ERRBASE + 7);  // Before send select error
    public const int DJ_EREMOTEDOWN = (DJ_ITPCOM_ERRBASE + 8); // Remote connect gracefully closed

#endregion

#region DJMissCall.h

    public const int DJSSM_CALL_GENERATE = 0x01;	// 呼叫发起
    public const int DJSSM_CALL_CONNECT = 0x02;	// 通话建立
    public const int DJSSM_CALL_DISCONNECT = 0x03;	// 通话断开
    public const int DJSSM_CALL_INFO = 0x04;	// 呼叫信息
    public const int DJSSM_CALL_INFO_ACM = 0x05;	// 收到ACM消息
    	
    public const int FORCE_MODE = 0x01;	// 强制重连

    // TUP遇忙信号
    public const int CALLEE_SLB = 0x1E;	// 被叫市话忙	
    public const int CALLEE_SSB = 0x65;	// 被叫忙
    public const int CALLEE_STB = 0x2E;	// 被叫长话忙
        
    public const int CALLEE_LOS = 0x85;	// 线路退出服务
    public const int CALLEE_CGC = 0x25;	// 电路群拥塞
    public const int CALLEE_ADI = 0x45;	// 地址不全
    public const int CALLEE_SEC = 0x15;	// 交换设备拥塞
    public const int CALLEE_UNN = 0x75;	// 未分配号码信号
    public const int CALLEE_SST = 0x95;	// 特别信号音
    public const int CALLEE_EUM = 0xF5;	// 后向建立不成功（扩充）

    // TUP拆线信号
    public const int CALLINF_CLF = 0x46;	// 前向拆线
    public const int CALLINF_CBK = 0x36;    // 后向拆线

    // ISUP呼叫释放原因值
    public enum CAUSE_VALUE
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

    public const int ERR_DMSU_SOCKFAIL = 1000;//-1		// 创建到DMSU连接socket失败
    public const int ERR_DMSU_CONNECTFAIL = 2000;//-2		// 连接DMSU失败
    public const int ERR_DMSU_INITRPARSERFAIL	 = -3;		// 初始化消息解析队列失败
    public const int ERR_DMSU_INITFRAGMENTFAIL	 = -4;		// 初始化数据交换队列失败
    public const int ERR_DMSU_INITRECVFAIL	     = -5;		// 初始化接收队列失败
    public const int ERR_DMSU_STARTRECVTFAIL	 = 	-6;		// 启动接收线程失败
    public const int ERR_DMSU_STARTHEARTTFAIL	 = -7;		// 启动心跳线程失败
    public const int ERR_DMSU_STARTPARSERTFAIL   =  -8;		// 启动解析线程失败
    public const int ERR_DMSU_NOTEXISTS			 = -9;		// 连接不存
    public const int ERR_DMSU_CONNECTIONOK		 = -10;		// 当前连接正常
    	
    public const int ERR_EVT_NODATA				 = -1;		// 没有接收到数据
    public const int ERR_EVT_GETDATAFAIL		 = 	-2;		// 获取数据失败
    public const int ERR_EVT_DATANOTENOUGH		 = -3;		// 数据长度不足
    public const int ERR_EVT_NOTEXISTS			 = -4;		// 连接不存在
    public const int ERR_EVT_DISCONNECT			 = -5;		// 到DMSU的连接断开



    public struct tSockInfo
    {
	    public fixed DJ_S8 Addr[16];
	    public DJ_U16 Port;
	    public DJ_U32 BufSize;
	    public DJ_U32 RecvBufSize;
	    public DJ_U8 UnitID;
    };

    public struct tMonEvt
    {
	    public fixed DJ_S8 caller_id[32];			// 主叫号码
	    public fixed DJ_S8 callee_id[32];			// 被叫号码
	    public fixed DJ_S8 original_callee_id[32];// 原被叫号码
	    public DJ_U8 Event;		// 事件指示码
	    public DJ_U8 LocalPcmID;	// 本地获得信令数据PCM号
	    public DJ_U8 pcm;			// 信令数据描述中继号
	    public DJ_U8 chn;			// 信令数据描述时隙号
	    public DJ_U8 Protocol;		// 协议类型
	    public DJ_U8 SubProtocol;	// 协议子类型 
	    public DJ_U8 ToneID;		// 保留字
	    public DJ_U8 ReleaseReason;// 拆线原因值
	    public DJ_U8 MsgType;		// 消息类型
	    public DJ_S32 DPC;
	    public DJ_S32 OPC; 	
	    public DJ_S32 DataLen;					 // 原始包长度
	    public fixed DJ_U8 OriginalData[300]; // 原始包 CR20061116_01
    };

    /////////////////////////////////////////////////////////////////////////
    // 系统状态信息 CR20061116_02
    //

    /////////////////////////////////////////////////////////////////////////
    // 信息掩码
    public const int SYS_INFO_BUFFER		=		00;		// 消息队列信息

    /////////////////////////////////////////////////////////////////////////
    // 出错提示
    public const int SYS_NOT_EXISTS			=	-1	;	// 指定的DMSU设备不存在
    public const int SYS_MAX_INFO_LEN		=	128;		// 信息内容最大长度

    /////////////////////////////////////////////////////////////////////////
    // 结构定义
    public struct tSysBufInfo
    {
	    public DJ_U8 BuffID;
	    public DJ_S32 BufSize;
	    public DJ_S32 InUse;	
    };

    public struct tSysState
    {
	    public DJ_U8 sysID;						// 返回信息类属资源
	    public DJ_U8 infoLen;						// 信息长度
	    public fixed DJ_U8 info[SYS_MAX_INFO_LEN];		// 信息内容
    };

    // end CR20061116_02

    //////////////////////////////////////////////////////////////////////////// 
    // 设置原始信令包传送方式  CR20061116_01

    // 解析掩码
    public const DJ_U8  PRO_TRANS		 = 0x00;	// 透传
    public const DJ_U8  PRO_PARSER		 = 0x01;	// 解析
    public const DJ_U8  PRO_BOTH		 = 0x02;	// 解析并传送

    // 操作掩码
    public const DJ_U8  PRO_ADD		 = 0x00;	// 添加
    public const DJ_U8 PRO_REMOVE		 = 0x01;	// 移除
    public const DJ_U8  PRO_MODIFY		 = 0x02;	// 修改

    // 协议工作模式
    public struct tProtocolMode
    {
	    public DJ_U8 Protocol;
	    public DJ_U8 WorkMode;
    };

    // END CR20061116_01

    // CR20070830_001
    public struct DMSU_LOG
    {
        public DJ_S32 LogType;
        public DJ_S32 Param1;
    };

#endregion

#region DJAcsUserDef.h

    /*#define min(a, b)  (((a) < (b)) ? (a) : (b))
    #define max(a, b)  (((a) > (b)) ? (a) : (b))*/

    /*Acs_Fax_InterCmd*/
    public struct Acs_Fax_InterCmd
    {
	    public ITP_RES_CHAN*         m_ITPFaxRes;/*fax res*/
        public ITP_RES_CHAN*         m_ITPFaxVocRes;/*fax voice res*/
        public SendFaxParm_t         m_ITPSendFaxParm;/*send fax parm*/
    };/*Acs_Fax_InterCmd*/

    /*Acs_FaxEnd_InterCmd*/
    public struct Acs_FaxEnd_InterCmd
    {
        public ITP_RES_CHAN*         m_ITPFaxVocRes;/*fax voice res*/
        public DJ_S32                m_s32EvtState;
        public DJ_S32                m_s32ErrCode;
        public DJ_U8                 m_u8ErrStep;
        public DJ_U8                 m_u8T30CmdState;
        public DJ_U8                 m_u8T30RcvState;
        public DJ_U16                m_u16TotalPages;
        public fixed DJ_S8                 m_s8RemoteID[20];
    };/*Acs_FaxEnd_InterCmd*/

    public struct LostCallInfo
    {
	    public fixed char szCalling[20];/**/
	    public fixed char szCalled[20];/**/
	    public fixed char szOrigCalled[20];/**/
	    public fixed char szLostTime[40];/**/
    };/*LostCallInfo*/

    public struct Fax_VoIP_InterCmd
    {
	    public DeviceID_t        m_FaxDevice;
	    public DJ_S8             m_s8T38Shake;
	    public fixed DJ_S8             m_s8Rfu1[3];
    };/*Fax_VoIP_InterCmd*/

    public struct CallUserInfor
    {
	    public DeviceID_t    m_DeviceID;
	    public fixed DJ_S8          m_szCaller[32];
    };/*CallUserInfor*/

    public struct InterCmdStru
    {
        public fixed DJ_S8 m_s8Buff[1024];
    };/*InterCmdStru*/

#endregion

#region DJAcsSignalMonitor.h

    ///////////////////////////////////////////////////////////////////////////////
    public enum ITP_SIGMonitor_EventType        // 信令监控事件定义
    {	
	    SMON_EVT_Call_Generate  =  0x01, // 呼叫发起
        SMON_EVT_Call_Connect   =  0x02, // 呼叫连接
	    SMON_EVT_Call_Disconnect=  0x03, // 呼叫断开
	    SMON_EVT_Call_Info      =  0x04, // 呼叫信息
	    SMON_Evt_Gen_Signal_Info=  0x05, // 信令信息
	    SMON_Evt_Raw_Signal_Info=  0x06, // 原始信息
    };


    public enum ITP_SIGMonitor_Protocol         // 信令监控协议定义
    {	
	    SMON_Protocol_ISDN      = 0x01,  // ISDN信令
	    SMON_Protocol_SS7       = 0x02,  // 七号信令
	    SMON_Protocol_N64K      = 0x03,  // N64K
    };


    public enum ITP_SIGMonitor_SI               // 业务表示语定义
    {	
	    SMON_SI_SCCP = 0x03,             // SCCP
        SMON_SI_TUP  = 0x04,             // TUP
	    SMON_SI_ISUP = 0x05,             // ISUP
    };


    public enum ITP_SIGMonitor_ISUP_MsgType     // 信令监控消息定义
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


    public enum ITP_SIGMonitor_TUP_MsgType      // 信令监控消息定义
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


    public enum ITP_SIGMonitor_ISDN_MsgType     // 信令监控消息定义
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
    public const int SMON_Evt_Len_But_Raw_Data = 128;// 事件包除原始数据部分的长度

    public struct SMON_EVENT                       // 返回的事件数据结构
    {	
	    public DJ_U8   EventType;               // 事件类型
	    public DJ_U8   Protocol;                // 协议类型
	    public DJ_U8   SI;                      // 业务表示
	    public DJ_U8   MsgType;                 // 信令消息
    	
	    public fixed DJ_S8   Caller_ID[32];           // 主叫号码
	    public fixed DJ_S8   Called_ID[32];           // 被叫号码
	    public fixed DJ_S8   OriCalled[32];           // 原始被叫
    	
	    public fixed DJ_U8   DPC[3];                  // 目的点码
	    public fixed DJ_U8   OPC[3];                  // 原端点码
	    public DJ_U8   Pcm;                     // CIC_Hig7
	    public DJ_U8   Chn;                     // CIC_Low5
    	
	    public DJ_U8   ReleaseReason;           // 拆线原因
	    public fixed DJ_U8   Reserved[14];            // 保留备用
	    public DJ_U8   Unit_ID;                 // 来源单元
	    public DJ_U8   Port_ID;                 // 来源端口
	    public DJ_U8   TS;                      // 来源时隙
	    public DJ_U16  DataLen;                 // 数据长度
    	
	    public fixed DJ_U8   RAWdata[2048];           // 原始数据
    };

#endregion

#region ItpFlowChanDef.h

    public const int ITP_MAX_MOD_TYPE_NUM     =      128 ;   // 最大模块数
    public const int ITP_MAX_RELATEMOD_NUM    =     64    ; //最大关联模块数
    public const int ITP_MAX_SYSFUNC_NUM      =      16;     //流程模块系统函数接口个数
    public const int ITP_MAX_DLLFUNC_NUM     =       4  ;    //流程动态库接口函数个数
    public const int ITP_FLOW_MAX_FLOWNAME_LEN  =    40  ;   //流程名最大长度          
      
    public const int ITP_FLOW_MAX_INTERNAME_LEN  =   120   ; //用户自定义结构名最大长度
    public const int ITP_MAX_BINDRES_NUM         =   256    ; //流程通道绑定的最大资源个数
    public const int ITP_MAX_BINDTIMER_NUM        =  64 ;    //流程通道绑定的最大定时器个数
    public const int ITP_FLOW_SHOW_INFO_SIZE     =   40  ;   //用户显示状态缓存长度
    public const int ITP_FLOW_SHOW_INFO_NUM      =   3    ;  //用户显示状态缓存个数

    /*typedef struct _tagITP_FLOW_INFO ITP_FLOW_INFO,*PITP_FLOW_INFO;
    typedef struct _tagITP_FLOW_CHAN ITP_FLOW_CHAN,*PITP_FLOW_CHAN;
    typedef struct _tagITP_RES_CHAN  ITP_RES_CHAN, *PITP_RES_CHAN;
    typedef struct _tagITP_FLOW_TIMER ITP_FLOW_TIMER, *PITP_FLOW_TIMER;*/

    public delegate DJ_S32 PTIMERFUNC(DJ_S32 esrParam);

    public enum ITP_RESOPEN_TYPE
    {
        ITP_RESOPEN_FREE = 0,
        ITP_RESOPEN_LISTEN,
	    ITP_RESOPEN_EXCLUDE,
    };

    //流程信息结构
    public struct ITP_FLOW_INFO
    {
        public DJ_U32     m_u32FlowIndex;                          //流程标号
        public fixed DJ_S8      m_s8FlowName[ITP_FLOW_MAX_FLOWNAME_LEN]; //流程名
        public fixed DJ_S8      m_s8DllName[MAX_PATH];                   //动态库名	
        public DJ_U32     m_u32StartState;                         //流程使能状态
        public DJ_U32     m_u32LoadState;                          //流程加载状态
        public DJ_U32*    m_hdlDllHandle;                          //流程动态库句柄
        public fixed DJ_U32/* DJ_U32* */    m_hdlDllFunc[ITP_MAX_DLLFUNC_NUM];       //流程动态库接口函数指针
        public DJ_U16     m_u16FlowChanNum;                        //该动态库对应的副本个数
	    public DJ_U16     m_u16Resrv;
        public ITP_FLOW_CHAN* *m_PITPFlowChan;                     //该动态库对应的副本表
    };

    //流程通道结构
    public struct ITP_FLOW_CHAN
    {
        public DJ_U16           m_u16FlowCurState;           //该流程通道当前状态
        public DJ_U16           m_u16FlowInfoIndex;          //该流程通道对应流程类型标记
        public DJ_U16           m_u16ChanIndex;              //该流程通道对应通道标记
        public DJ_U16           m_u16StartState;             //启动标志,0:禁止;1:使能
	    public DJ_U16           m_u16BusyState;              //Busy标志,0:Free;1:Busy
        public ITP_FLOW_INFO*   m_PITPFlowInfo;              //流程信息
        public DJ_U16           m_u16CurResNum;              //与此流程通道绑定的当前资源数量
        public DJ_S16           m_s16ChanRetCode;            //流程通道返回状态值
	    public fixed DJ_U32 /* ITP_RES_CHAN* */    m_PITPResList[ITP_MAX_BINDRES_NUM];//与此流程通道绑定的资源句柄表
        public DJ_U16           m_u16CurTimerNum;            //定时器个数
	    public DJ_S16           m_s16Resrv2;
        public fixed DJ_U32/* ITP_FLOW_TIMER* */  m_PITPTimerChan[ITP_MAX_BINDTIMER_NUM];//定时器句柄
        public fixed DJ_U32 /* DJ_U32* */          m_PITPSysFunc[ITP_MAX_SYSFUNC_NUM];    //系统函数指针
        public fixed DJ_S8            m_s8InfoBuf[ITP_FLOW_SHOW_INFO_NUM/*][*/*ITP_FLOW_SHOW_INFO_SIZE];//用户显示状态
	    public fixed DJ_U8            m_u8RelateModInfo[ITP_MAX_MOD_TYPE_NUM]; //相关的模块
        public PKG_HEAD_STRUCT *m_PITPEvtPack;                 //事件包指针
	    public PKG_HEAD_STRUCT *m_PITPInterEvt;                //流程内部事件包指针
        public DJ_U8            *m_PITPFlowExtData;            //流程扩展数据
        public DJ_U8            *m_PITPPublicBuf;              //公共使用缓存区
    };

    //资源通道结构
    public struct ITP_RES_CHAN
    {
	    public DJ_U16	 m_u16ChanIndex;        //该通道的通道索引号
        public DJ_U8	 m_u8UnitIndex;         //该通道所在模块单元索引号
	    public DJ_U8	 m_u8ModType;           //该通道所在模块的Module_Type
        public DJ_U8	 m_u8FuncType;          //该通道所在模块的Func_Type        
        public DJ_U8	 m_u8ChanType;          //该通道的类型，此项仅只有Interface_ch有用
        public DJ_S16	 m_s16ChanGroup;        //该通道的组号
        public DJ_U8	 m_u8BusyFlag;          //通道忙标志,0:空闲;1:独占打开;2:监听打开
        public ITP_FLOW_CHAN*  m_PITPFlowChan; //流程通道信息
	    public ITP_FLOW_CHAN*  m_PITPListenFlowChan; //监听流程通道
        public fixed DJ_S8    m_s8InfoBuf[ITP_FLOW_SHOW_INFO_NUM/*][*/*ITP_FLOW_SHOW_INFO_SIZE];//用户显示状态
        public fixed DJ_U8    m_u8RelateModInfo[ITP_MAX_RELATEMOD_NUM];     //与该资源相关的模块
	    public DJ_S8    m_s8MachineId;                                //机箱号ID 
	    public fixed DJ_S8    m_s8Resrv[ITP_MAX_RELATEMOD_NUM-1];
    };

    //定时器结构
    public struct ITP_FLOW_TIMER
    {	
        public double/*DJ_F64*/     m_u64Time;              //触发时间
        public DJ_U32     m_u32Ticks;             //触发间隔
        public DJ_U8      m_u8StartFlag;          //启动标志
	    public DJ_U8      m_u8Caller;             //调用者:用户DLL或者模块本身
	    public fixed DJ_U8      m_Resrv[2];
        public ITP_FLOW_CHAN*  m_PITPFlowChan;   //流程通道指针
        public PTIMERFUNC m_PITPTimerFunc;       //定时处理函数
	    public DJ_U16	   m_u16ChanIndex;        //后续三个定义是为了与流程转换部分的事件参数为资源句柄相一致
        public DJ_U8	   m_u8UnitIndex;         //
	    public DJ_U8	   m_u8ModType;           //
    };

    //流程内自部通讯事件结构
    public struct FLOW_INTERDATA_HEAD
    {
	    public PKG_HEAD_STRUCT  m_PkgHead;                                 //事件包头
	    public CallID_t         m_SrcCallID;                               //源流程
	    public CallID_t         m_destCallID;                              //目的流程
	    public DJ_U32           m_u32CmdType;                              //自定义命令类型
	    public DJ_U32           m_u32InterNameLen;                         //用户结构名长度
	    public fixed DJ_S8            m_s8InterName[ITP_FLOW_MAX_INTERNAME_LEN]; //用户结构名
	    public DJ_U32           m_u32InterDataSize;                        //用户自定义结构大小
    };

#endregion

#region ITPGUID.h
        
    public const int  MODULE_TYPE_DSP    =	0x01    ;       //DSP功能模块
    public const int  MODULE_TYPE_MEDIA	  =  0x02      ;     //媒体处理模块
    public const int  MODULE_TYPE_SS7      =  0x03     ;      //七号处理模块	
    public const int  MODULE_TYPE_CFG 	  =  0x04     ;      //配置模块
    public const int  MODULE_TYPE_MONITOR =	0x05        ;   //监控模块
    public const int  MODULE_TYPE_FLOW     =  0x06;	       //流程模块
    public const int  MODULE_TYPE_PRI       = 0x07;	       //ISDN信令模块
    public const int  MODULE_TYPE_USER       =0x08 ;          //用户模块
    public const int  MODULE_TYPE_INTERFACE = 0x09  ;         //界面模块
    public const int  MODULE_TYPE_VOIP   =    0x0A   ;        //VoIP模块
    public const int  MODULE_TYPE_3G324M  =   0x0B    ;       //3G-324M模块
    public const int  MODULE_TYPE_MEDIAEX=	0x0C	;				 //媒体编解码模块
    public const int  MODULE_TYPE_FAXTIFF =   0x0E   ;        //FAXTIFF模块
    public const int  MODULE_TYPE_ACS      =  0x0F    ;       //API模块
    public const int  MODULE_TYPE_SIGMON    = 0x10     ;      //信令监控模块
    public const int  MODULE_TYPE_CTXM       =0x11      ;     //交换矩阵模块
    	
    //DSP功能模块功能ID定义***************************************
    public const int  DSP_MAIN_FUNCTION_CONFIG=      0x01;           //全局设备管理
    public const int  DSP_MAIN_FUNCTION_SPEECH =     0x02 ;          //语音功能
    public const int  DSP_MAIN_FUNCTION_FAX     =    0x03  ;         //传真功能
    public const int  DSP_MAIN_FUNCTION_DIGITAL  =   0x04   ;        //数字中继功能
    public const int  DSP_MAIN_FUNCTION_INTERFACE =  0x05    ;       //坐席功能模块
    public const int  DSP_MAIN_FUNCTION_PRILINK    = 0x06     ;      //会议功能模块
    public const int  DSP_MAIN_FUNCTION_SS7LINK    = 0x07      ;     //数字中继功能模块
    public const int  DSP_MAIN_FUNCTION_CTCLK      = 0x08       ;    //CT_BUS时钟
    public const int  DSP_MAIN_FUNCTION_CTTS       = 0x09        ;   //CT_BUS资源
    public const int  DSP_MAIN_FUNCTION_CONNECTTS  = 0x0A         ;  //时隙连接
    public const int  DSP_MAIN_FUNCTION_FIRMWARE   = 0x0B          ; //固件操作
    public const int  DSP_MAIN_FUNCTION_VOIP       = 0x0C           ;//VoIP功能
    public const int  DSP_MAIN_FUNCTION_3G324M     = 0x0D;           //3G-324M功能
    public const int  DSP_MAIN_FUNCTION_LICENSE    = 0x0E ;          //license alarm
    public const int  DSP_MAIN_FUNCTION_RTPX		=	0x0F;						//RTPX数据交换

    public const int  SUB_FUNCTION_ALL              =  0xFF   ;     //所有子功能

    public const int  DSP_SUB_FUNCTION_SPEECH_INPUT =  0x01    ;    //输入功能(EC,AGC等)
    public const int  DSP_SUB_FUNCTION_SPEECH_OUTPUT = 0x02     ;   //输出功能(混音,AGC等)
    public const int  DSP_SUB_FUNCTION_SPEECH_PLAY   = 0x03      ;  //放音功能
    public const int  DSP_SUB_FUNCTION_SPEECH_RECORD  =0x04       ; //录音功能
    public const int  DSP_SUB_FUNCTION_SPEECH_GTD    = 0x05        ;//各种音频处理功能
    public const int  DSP_SUB_FUNCTION_SPEECH_CONF   = 0x06        ;//会议处理功能


    //DSP DSS1子功能定义
    public const int  DSP_SUB_FUNCTION_DSS1_CFG_CMD_TO_DSP    =    0x01;      //DSS1配置命令，        Q931->DSP
    public const int  DSP_SUB_FUNCTION_DSS1_GET_CFG_TO_DSP     =   0x02 ;     //获取DSS1配置信息命令，Q931->DSP
    public const int  DSP_SUB_FUNCTION_DSS1_CFG_INFO_TO_Q931=      0x02  ;    //DSS1配置信息，        DSP->Q931   
    public const int  DSP_SUB_FUNCTION_DSS1_CONTROL_CMD_TO_DSP=    0x03   ;   //DSS1控制命令          Q931->DSP
    public const int  DSP_SUB_FUNCTION_DSS1_STATE_EVENT_TO_Q931=   0x03    ;  //DSS1状态事件          DSP->Q931 
    public const int  DSP_SUB_FUNCTION_DSS1_SIGNAL_DATA_TO_DSP  =  0x04     ; //DSS1信令数据          Q931->DSP
    public const int  DSP_SUB_FUNCTION_DSS1_SIGNAL_DATA_TO_Q931  = 0x04      ;//DSS1信令数据          DSP->Q931
    public const int  DSP_SUB_FUNCTION_DSS1_DATA_REQ_TO_Q931      =0x05;      //DSS1数据请求包        DSP->Q931
    public const int  DSP_SUB_FUNCTION_DSS1_DEBUG_DATA_TO_Q931   = 0x06 ;     //DSS1调试信息包        DSP->Q931
    //DSP DSS1子功能定义 end

    //DSP 固件子功能定义
    public const int  DSP_SUB_FUNCTION_FIRMWARE_READ_FLASH   =     0x01;      //读FLASH命令
    public const int  DSP_SUB_FUNCTION_FIRMWARE_WRITE_FLASH   =    0x02  ;    //写FLASH命令
    public const int  DSP_SUB_FUNCTION_FIRMWARE_ERASE_FLASH    =   0x03 ;     //擦除FLASH命令
    public const int  DSP_SUB_FUNCTION_FIRMWARE_FINISH_FLASH    =  0x04   ;   //更新FLASH完成命令
    public const int  DSP_SUB_FUNCTION_FIRMWARE_READ_SDRAM       = 0x06    ;  //读SDRAM命令
    public const int  DSP_SUB_FUNCTION_REBOOT                     =0x07     ; //DSP重启命令
    //DSP 固件子功能定义

    //******************************************************************************

    public const int  MEDIA_MAIN_FUNCTION_STREAMPLAY =   0x01    ;       //流放音
    //媒体功能模块功能ID定义***************************************
    public const int  MEDIA_MAIN_FUNCTION_STREAMRECORD = 0x02   ;        //流录音

    //SS7信令功能模块功能ID定义***************************************
    public const int  SS7_MAIN_FUNCTION_ISUP      = 0x01;           //七号信令ISUP
    public const int  SS7_MAIN_FUNCTION_TUP       = 0x02 ;          //七号信令TUP
    public const int  SS7_MAIN_FUNCTION_SCCP      = 0x03  ;         //七号信令SCCP
    public const int  SS7_MAIN_FUNCTION_LINK      = 0x10   ;        //七号信令链路
    public const int  SS7_MAIN_FUNCTION_FLOW      = 0x11    ;       //流程标识交互

    //PRI信令功能模块功能ID定义***************************************
    public const int  PRI_MAIN_FUNCTION_Q931      = 0x01;           //Q.931信令


    //配置模块功能ID定义***************************************

    public const int  CONFIG_MAIN_FUNCTION_INIT        = 0x01;           //初始化模块
    public const int  CONFIG_MAIN_FUNCTION_START       = 0x02 ;          //启动模块
    public const int  CONFIG_MAIN_FUNCTION_STOP        = 0x03  ;         //停止模块
    public const int  CONFIG_MAIN_FUNCTION_RELATE      = 0x04   ;        //关联模块
    public const int  CONFIG_MAIN_FUNCTION_UNRELATE    = 0x05    ;       //停止关联模块
    public const int  CONFIG_MAIN_FUNCTION_MONCONFIG   = 0x06     ;      //监视配置
    public const int  CONFIG_MAIN_FUNCTION_MONSTART    = 0x07      ;     //监视启动
    public const int  CONFIG_MAIN_FUNCTION_MONSTOP     = 0x08       ;    //监视停止
    public const int  CONFIG_MAIN_FUNCTION_HEART       = 0x09        ;   //心跳包
    public const int  CONFIG_MAIN_FUNCTION_VALIDITY    = 0x0A         ;  //系统连接验证包
    public const int  CONFIG_MAIN_FUNCTION_RELEAT      = 0x0B;
    public const int  CONFIG_MAIN_FUNCTION_MODSTATE_REPORT = 0x0C;

    public const int  CONFIG_MAIN_FUNCTION_INTERFACE   = 0x10;           //界面模块发送过来的数据


    public const int CONFIG_SUB_FUNCTION_INTERFACE_REQALL      = 0x01;    //请求所有模块数据
    public const int CONFIG_SUB_FUNCTION_INTERFACE_REQSINGAL   = 0x02 ;   //请求某个模块数据
    public const int CONFIG_SUB_FUNCTION_INTERFACE_REQINIT     = 0x03  ;  //请求某个模块初始化包数据
    public const int CONFIG_SUB_FUNCTION_INTERFACE_SETPARM     = 0x04   ; //设置某个模块参数(例如IP,是否使能等)
    public const int CONFIG_SUB_FUNCTION_INTERFACE_SETINIT     = 0x05    ;//设置模块初始化包
    public const int CONFIG_SUB_FUNCTION_INTERFACE_START       = 0x06;    //模块初始化和启动
    public const int CONFIG_SUB_FUNCTION_INTERFACE_STOP        = 0x07 ;   //模块停止
    public const int CONFIG_SUB_FUNCTION_INTERFACE_REQRELATE   = 0x08  ;  //请求模块关联信息
    public const int CONFIG_SUB_FUNCTION_INTERFACE_TRANRELATE  = 0x09   ; //模块关联信息
    public const int CONFIG_SUB_FUNCTION_INTERFACE_ADD         = 0x0a    ;//增加一个模块
    public const int CONFIG_SUB_FUNCTION_INTERFACE_SUB         = 0x0b;    //删除一个模块

    public const int CONFIG_SUB_FUNCTION_INTERFACE_HEART       = 0x10;   //心跳包


    //界面模块功能ID定义***************************************
    public const int FACE_MAIN_FUNCTION_REQNODE                = 0x01;    //请求节点定义
    public const int FACE_MAIN_FUNCTION_READNODE               = 0x02 ;   //读节点数据
    public const int FACE_MAIN_FUNCTION_WRITENODE              = 0x03  ;  //写节点数据
    public const int FACE_MAIN_FUNCTION_SAVECONFIG             = 0x04   ; //保存节点配置
    public const int FACE_MAIN_FUNCTION_LOADCONFIG             = 0x05    ;//转载节点配置

    public const int FACE_MAIN_FUNCTION_HEART                  = 0x09;    //界面的心跳包


    //流程执行模块功能ID定义*************************************
    public const int  CTX_MAIN_FUNCTION_CTXCMD                = 0xFA;	   //交换中心命令
    //流程执行模块子功能ID定义*************************************
    public const int  CTX_SUB_FUNCTION_CTXREG                 = 0x01;     //ACS发送交换中心注册命令
    public const int  CTX_SUB_FUNCTION_CTXLINK                = 0x02 ;    //ACS发送交换中心Link命令
    public const int  CTX_SUB_FUNCTION_CTXAPPDATA             = 0x03  ;   //ACS发送注册交换中AppData心命令

    //流程执行模块功能ID定义*************************************
    public const int  FLOW_MAIN_FUNCTION_SYNCMD                = 0xFB;	   //流程同步命令

    public const int  FLOW_MAIN_FUNCTION_ACSEVT                = 0xFC;	   //流程API事件

    public const int  FLOW_MAIN_FUNCTION_ACSCMD                = 0xFD;	   //流程命令
    //流程执行模块子功能ID定义*************************************
    public const int  FLOW_SUB_FUNCTION_INTERCMD               = 0x01;     //流程内部命令
    public const int  FLOW_SUB_FUNCTION_REQDEVICE              = 0x02 ;    //ACS请求资源列表
    public const int  FLOW_SUB_FUNCTION_OPENDEVICE             = 0x03  ;   //ACS打开设备
    public const int  FLOW_SUB_FUNCTION_CLOSEDEVICE            = 0x04   ;  //ACS关闭设备
    public const int  FLOW_SUB_FUNCTION_RESETDEVICE            = 0x05    ; //ACS复位设备
    public const int  FLOW_SUB_FUNCTION_GETDEVSTATE            = 0x06     ;//ACS获取设备状态
    public const int  FLOW_SUB_FUNCTION_SETDEVGROUP            = 0x07;     //ACS设置资源组号
    public const int  FLOW_SUB_FUNCTION_SETPARAM               = 0x08 ;    //ACS设置参数
    public const int  FLOW_SUB_FUNCTION_GETPARAM               = 0x09  ;   //ACS设置参数 ...
    public const int  FLOW_SUB_FUNCTION_MAKECALLOUT            = 0x0A   ;  //ACS发起呼叫
    public const int  FLOW_SUB_FUNCTION_ALERTCALL              = 0x0B    ; //ACS Alert呼叫
    public const int  FLOW_SUB_FUNCTION_ANSWERCALLIN           = 0x0C     ;//ACS应答呼入
    public const int  FLOW_SUB_FUNCTION_LINKDEV                = 0x0D;     //ACS连接设备
    public const int  FLOW_SUB_FUNCTION_UNLINKDEV              = 0x0E ;    //ACS拆除设备连接
    public const int  FLOW_SUB_FUNCTION_CLEARCALL              = 0x0F  ;   //ACS清除呼叫
    public const int  FLOW_SUB_FUNCTION_JOINTOCONF             = 0x10   ;  //ACS加入会议
    public const int  FLOW_SUB_FUNCTION_LEAVEFROMCONF          = 0x11    ; //ACS离开会议
    public const int  FLOW_SUB_FUNCTION_CLEARCONF              = 0x12     ;//ACS删除会议
    public const int  FLOW_SUB_FUNCTION_PLAYFILE               = 0x13;     //ACS放音
    public const int  FLOW_SUB_FUNCTION_INITPLAYINDEX          = 0x14 ;    //ACS初始化索引
    public const int  FLOW_SUB_FUNCTION_BUILDINDEX             = 0x15  ;   //ACS建立放音索引
    public const int  FLOW_SUB_FUNCTION_CONTROLPLAY            = 0x16   ;  //ACS控制放音
    public const int  FLOW_SUB_FUNCTION_RECORDFILE             = 0x17    ; //ACS录音
    public const int  FLOW_SUB_FUNCTION_CONTROLRECORD          = 0x18     ;//ACS控制录音
    public const int  FLOW_SUB_FUNCTION_SENDFAX                = 0x19;     //ACS发送传真
    public const int  FLOW_SUB_FUNCTION_STOPSENDFAX            = 0x1A ;    //ACS停止发送传真
    public const int  FLOW_SUB_FUNCTION_RECVFAX                = 0x1B  ;   //ACS接收传真
    public const int  FLOW_SUB_FUNCTION_STOPRECVFAX            = 0x1C   ;  //ACS停止接收传真
    public const int  FLOW_SUB_FUNCTION_CHANGEMONITORFILTER    = 0x1D    ; //ACS改变事件filter
    public const int  FLOW_SUB_FUNCTION_SENDIODATA             = 0x1E     ;//ACS发送IO数据
    public const int  FLOW_SUB_FUNCTION_SENDSIGMSG             = 0x1F;     //ACS发送信令消息
    public const int  FLOW_SUB_FUNCTION_RECORDCSP              = 0x20 ;    //ACS内存录音
    public const int  ACS_SUB_FUNCTION_DBGON                   = 0x22  ;   //调试使能
    public const int  ACS_SUB_FUNCTION_DBGOFF                  = 0x23   ;  //调试禁止
    public const int  FLOW_SUB_FUNCTION_PLAY3GPP               = 0x24    ; //播放3gpp
    public const int  FLOW_SUB_FUNCTION_CONTROLPLAY3GPP        = 0x25     ;//控制播放3gpp
    public const int  FLOW_SUB_FUNCTION_RECORD3GPP             = 0x26;     //播放3gpp
    public const int  FLOW_SUB_FUNCTION_CONTROLRECORD3GPP      = 0x27 ;    //控制播放3gpp
    public const int  FLOW_SUB_FUNCTION_PLAYCSP                = 0x28  ;   //ACS启动CSP放音
    public const int  FLOW_SUB_FUNCTION_SENDPLAYCSP            = 0x29   ;  //ACS发送CSP放音数据
    public const int  FLOW_SUB_FUNCTION_CTXREG                 = 0x2A    ; //ACS发送Ctx Reg事件
    public const int  FLOW_SUB_FUNCTION_CTXLINK                = 0x2B     ;//ACS发送CTX Link事件
    public const int  FLOW_SUB_FUNCTION_CTXAPPDATA             = 0x2C;     //ACS发送CTX AppData事件
    public const int  FLOW_SUB_FUNCTION_LICQUERY               = 0x2E ;    //ACS发送License query
    public const int  FLOW_SUB_FUNCTION_LINKQUERY              = 0x2F  ;   //ACS发送Link query
    public const int  FLOW_SUB_FUNCTION_INIT3GPPINDEX          = 0x30   ;  //ACS初始化3gpp索引
    public const int  FLOW_SUB_FUNCTION_BUILD3GPPINDEX         = 0x31    ; //ACS建立3gpp索引
    public const int  FLOW_SUB_FUNCTION_SENDRAWFRAME           = 0x32     ;//ACS发送原始Frame数据
    public const int  FLOW_SUB_FUNCTION_RESETCHAN              = 0xFF;     //发送复位通道事件


    //流程执行模块功能ID定义*************************************
    public const int  FLOW_MAIN_FUNCTION_TIMEREVT              = 0xFE;	   //定时器事件
    public const int  MOD_MAIN_FUNCTION_MODHEART               = 0xFF;	   //各模块之间的心跳包


    //IP信令模块功能ID定义*******************************************

    //faxTiff模块主功能
    public const int FAXTIFF_MAIN_FUNCTION_CHANGE  = 0x01;

    //faxTiff模块子功能
    //命令包定义
    public const int FAXTIFF_SUB_FUNCTION_CHANGE_DECOMPOSE	= 0x01;	//分解
    public const int FAXTIFF_SUB_FUNCTION_CHANGE_COMPOSE	= 0x02;    //合成
    public const int FAXTIFF_SUB_FUNCTION_PAGE_REQ		= 0x03;
    public const int FAXTIFF_SUB_FUNCTION_TRANS_CONTROL	= 0x04;	
    //事件包定义
    public const int FAXTIFF_SUB_FUNCTION_DECOMPOSE_RESULT	= 0x01;  //分解结果
    public const int FAXTIFF_SUB_FUNCTION_COMPOSE_RESULT	= 0x02;  //合成结果
    public const int FAXTIFF_SUB_FUNCTION_TRANS_STATE = 0x03;

#endregion

#region ITPISDN.h

    //Q931模块与流程执行模块之间通讯包包头子功能定义
    public const int ITP_SUB_FUNC_FLOW_TO_Q931_GET_CHNL_STATE       = 0x01;     //获取通道状态  查询指定单元指定通道的当前状态
    public const int ITP_SUB_FUNC_FLOW_TO_Q931_CALL_OUT             = 0x02 ;    //发起一个呼叫  
    public const int ITP_SUB_FUNC_FLOW_TO_Q931_APPEND_CALLEEID      = 0x03  ;   //追加被叫号码  发起呼叫后，追加被叫号码
    public const int ITP_SUB_FUNC_FLOW_TO_Q931_GET_CALL_INFO        = 0x04   ;  //获取呼叫信息  获取呼叫信息，包括主叫号码、被叫号码等
    public const int ITP_SUB_FUNC_FLOW_TO_Q931_GET_CALL_RESULT      = 0x05    ; //获取呼出结果 
    public const int ITP_SUB_FUNC_FLOW_TO_Q931_GET_DISCONN_REASON   = 0x06     ;//获取挂机原因 
    public const int ITP_SUB_FUNC_FLOW_TO_Q931_SET_CHNL_STATE       = 0x07;     //设置通道状态 
    public const int ITP_SUB_FUNC_FLOW_TO_Q931_SET_PARAM            = 0x08 ;    //设置参数
    public const int ITP_SUB_FUNC_FLOW_TO_Q931_GET_PARAM            = 0x09  ;   //获取参数
    public const int ITP_SUB_FUNC_FLOW_TO_Q931_SET_SIGNAL           = 0x10   ;  //设置信号

    public const int ITP_SUB_FUNC_Q931_TO_FLOW_CHNL_STATE           = 0x11;     //反馈通道状态  当通道状态发生了迁移或接收到流程执行模块的请求包，Q931模块向流程执行模块发送本包，以告之流程执行模块指定通道的当前状态
    public const int ITP_SUB_FUNC_Q931_TO_FLOW_CALL_INFO            = 0x12 ;    //反馈呼叫信息  当接收到流程执行模块的请求包，Q931模块向流程执行模块发送本包，包含主叫号码、被叫号码、主叫子地址、被叫子地址及它们的长度
    public const int ITP_SUB_FUNC_Q931_TO_FLOW_CALL_RESULT          = 0x13  ;   //反馈呼出结果  当接收到流程执行模块的请求包，Q931模块向流程执行模块发送本包，以告之流程执行模块指定通道的呼出结果
    public const int ITP_SUB_FUNC_Q931_TO_FLOW_DISCONN_REASON       = 0x14   ;  //反馈挂机原因  当接收到流程执行模块的请求包，Q931模块向流程执行模块发送本包，以告之流程执行模块指定通道的挂机原因
    public const int ITP_SUB_FUNC_Q931_TO_FLOW_SET_PARAM            = 0x15    ; //反馈设置参数结果  
    public const int ITP_SUB_FUNC_Q931_TO_FLOW_GET_PARAM            = 0x16     ;//反馈获取参数结果 
    public const int ITP_SUB_FUNC_Q931_TO_FLOW_SET_SIGNAL           = 0x17;     //反馈设置信号结果


    //Q931模块通道状态定义
    public const int ITP_Q931_CH_FREE					   = 1;   //空闲状态
    //public const int ITP_Q931_CH_WAIT_APP_FREE		   = 2;   //Q931等待应用层同步释放资源
    public const int ITP_Q931_CH_RESTART                   = 2;
    public const int ITP_Q931_CH_UNAVIABLE			       = 3 ;  //通道不可用
    public const int ITP_Q931_CH_WAIT_CONNECT_ACK		   = 4;   //等待连接证实
    public const int ITP_Q931_CH_CONNECT				   =     5;   //通道连通状态
    public const int ITP_Q931_CH_WAIT_RELEASE			   = 6 ;  //已发送拆线信号，等待对方发送释放信号
    public const int ITP_Q931_CH_WAIT_RELEASE_COMPLETE     =  7 ;  //已发送释放信号，等待对方发送释放完成信号
    public const int ITP_Q931_CALLEE_WAIT_ANSWER		   =     11;  //来话方，呼叫到达
    public const int ITP_Q931_CALLER_WAIT_ANSWER		   =     12 ; //去话方，已呼出，等待对方回应
    public const int ITP_Q931_CALLER_RECV_ALERT		       = 21;  //去话方，已接收到提醒消息
    public const int ITP_Q931_CALLER_RECV_SETUP_ACK	       = 22 ; //去话方，已接收到建立确认消息
    public const int ITP_Q931_CALLER_RECV_CALLPROCESS      =  23 ; //去话方，已接收到呼叫进程消息
    public const int ITP_Q931_CALLER_WAIT_SETUP_ACK	       = 24 ; //去话方，等待建立确认
    public const int ITP_Q931_CALLEE_WAIT_INFO             = 0x90; //来话方，等待后续被叫号码信息
    public const int ITP_Q931_CALLEE_SEND_ALERT			   = 0x91 ;//来话方，发送了提醒消息


    //通道动作定义
    public const int	ITP_Q931_CH_SET_FREE			      = 1;    //APP 层检查通道状态为 OxO2 时，同步释放通道资源
    public const int ITP_Q931_CH_SET_CONNECT		          = 2;    //设置通道连接
    public const int ITP_Q931_CH_SET_DISCONNECT	          = 3 ;   //解除通道连接
    public const int ITP_Q931_CALLEE_SET_ALERTING	      = 4  ;  //被叫方发送提醒消息
    public const int	ITP_Q931_CH_SET_RESTART		         =  5;    //设置通道重新启动


    //Q931呼出结果定义
    public const int ITP_Q931_C_NO_RESULT		  = 0;    //尚未返回呼出结果
    public const int ITP_Q931_C_USER_IDLE		  = 1 ;   //被叫空闲
    public const int ITP_Q931_C_USER_OFFHOOK	     =  2;    //被叫摘机，连通
    public const int ITP_Q931_C_WAIT_CALL_PROC     = 3  ;  //重叠发送被叫号码，等待对端确认被叫号码收齐
    public const int ITP_Q931_C_OTHERS             = 10  ; //其它结果，呼叫可能结束，请查询通道状态


    //定义挂机原因
    public const int ITP_Q931_RSN_UNKNOW_REASON           = 0x00  ; //原因未知
    public const int ITP_Q931_RSN_UNALLOC_NUMBER          = 0x01  ; //空号
    public const int ITP_Q931_RSN_NORMAL_DISCONNECT       = 0x10  ; //正常的呼叫清除
    public const int ITP_Q931_RSN_USER_BUSY               = 0x11  ; //用户忙
    public const int ITP_Q931_RSN_NO_RESPOND              = 0x12  ; //无响应
    public const int ITP_Q931_RSN_NO_ANSWER               = 0x13  ; //无用户应答
    public const int ITP_Q931_RSN_REFUSR_CALL             = 0x15  ; //呼叫拒绝
    public const int ITP_Q931_RSN_NUMBER_ERROR            = 0x1C  ; //号码不全
    public const int ITP_Q931_RSN_TIMEOUT	             = 0x66   ;//超时
    public const int ITP_Q931_RSN_DCHANNEL_DOWN           = 0xfd  ; //链路中断
    public const int ITP_Q931_RSN_BCHANNEL_UNAVIABLE      = 0x22  ; //通道不可用
    public const int ITP_Q931_RSN_UNAVIABLE_CIRCULT       = 0x2c  ; //无可用通路

    public const int ITP_Q931_RSN_UNAVIABLE_CRN           = 0x51  ; //无效的参考值
    public const int ITP_Q931_RSN_UNCOMPATIBLE            = 0x58  ; //不兼容的终点
    public const int ITP_Q931_RSN_UNAVIABLE_MSG           = 0x5F  ; //无效的消息


    public const int ITP_Q931_RSN_NEEDMSG_LOST            = 0x60  ; //必须的信息单元丢失

    public const int ITP_Q931_RSN_UNKNOW_MSG              = 0x61  ;  //消息类型不存在
    public const int ITP_Q931_RSN_UNAVIABLE_STATUE        = 0x65  ; //呼叫和状态不符合

    //承载能力
    //定义信息传递能力

    public const int ITP_Q931_CAP_SPEECH          = 0x00;  /* Speech Bearer Capability */
    public const int ITP_Q931_CAP_UNREST_DIG      = 0x08;  /* Unrestricted Digital Capability */
    public const int ITP_Q931_CAP_REST_DIG        = 0x09;  /* Restricted Digital Capability */
    public const int ITP_Q931_CAP_3DOT1K_AUDIO    = 0x10;  /* 3.1KHz Audio Capability */
    public const int ITP_Q931_CAP_7K_AUDIO        = 0x11;  /* 7KHz Audio Capability */
    public const int ITP_Q931_CAP_VIDEO           = 0x18;  /* Video Capability */


    //定义信息传递速率

    public const int ITP_Q931_RATE_64KBPS         = 0x10 ; /* B_CHANNEL_UNITS 1X64 */
    public const int ITP_Q931_RATE_128KBPS        = 0x11 ; /* Non-standard 2X64       */
    public const int ITP_Q931_RATE_384KBPS        = 0x13 ; /* H0_CHANNEL_UNITS 6X64   */
    public const int ITP_Q931_RATE_1536KBPS       = 0x15 ; /* H11_CHANNEL_UNITS 24X64 */
    public const int ITP_Q931_RATE_1920KBPS       = 0x17 ; /* H12_CHANNEL_UNITS 3= 0x64 */

    //定义传递方式
    public const int ITP_Q931_ITM_CIRCUIT         = 0x00 ; /* 电路方式 */  //默认(only support)
    public const int ITP_Q931_ITM_PACKET          = 0x02 ; /* 分组方式 */

    //定义用户一层协议
    public const int ITP_Q931_UIL1_CCITTV110      = 0x01 ; /* user info layer 1 - CCITT V.110/X.3*/
    public const int ITP_Q931_UIL1_G711ALAW       = 0x03 ; /* user info layer 1 - G.711 A-law */
    public const int ITP_Q931_UIL1_G721ADCPM      = 0x04 ; /* user info layer 1 - G.721 ADCPM */
    public const int ITP_Q931_UIL1_G722G725       = 0x05 ; /* user info layer 1 - G.722 and G.725 */
    public const int ITP_Q931_UIL1_CCITTV120      = 0x08 ; /* user info layer 1 - CCITT V.120 */
    public const int ITP_Q931_UIL1_CCITTX31       = 0x09 ; /* user info layer 1 - CCITT X.31 */


    //定义号码类型
    public const int ITP_Q931_CALLNUM_UNKNOWN		        = 0x00 ;  //未知
    public const int ITP_Q931_CALLNUM_INTERNATIONAL	        = 0x01 ;  //国际号码
    public const int ITP_Q931_CALLNUM_DOMESTIC		        = 0x02 ;  //国内号码
    public const int ITP_Q931_CALLNUM_NETWORK_SPECIFIC       = 0x03;   //网络特定号码
    public const int ITP_Q931_CALLNUM_USER		 	        = 0x04 ;  //用户号码
    public const int ITP_Q931_CALLNUM_RESERVE		        = 0x07 ;  //扩展保留


    //定义号码编码类型
    public const int ITP_Q931_NUMPLAN_UNKNOWN                = 0x00 ;  //未知
    public const int ITP_Q931_NUMPLAN_ISDN                   = 0x01 ;  /* ISDN numb. plan E.164 */
    public const int ITP_Q931_NUMPLAN_TELEPHONY              = 0x02 ;  /* Telephony numb. plan E.163 */
    public const int ITP_Q931_NUMPLAN_PRIVATE                = 0x09 ;  /* Private numbering plan */


    //数据结构定义

    public struct ITP_Q931_CALL_PARAM
    {
        public DJ_U8 m_u8Cap;                //信息传递能力
        public DJ_U8 m_u8ITM;                //传递方式
        public DJ_U8 m_u8Rate;               //信息传递速率
        public DJ_U8 m_u8UIL1;               //用户一层协议
        public DJ_U8 m_u8CallerType;         //主叫号码类型
        public DJ_U8 m_u8CallerPlan;         //主叫号码编码类型
        public DJ_U8 m_u8CallerSubType;      //主叫子地址号码类型
        public DJ_U8 m_u8CallerSubPlan;      //主叫子地址号码编码类型
        public DJ_U8 m_u8CalleeType;         //被叫号码类型
        public DJ_U8 m_u8CalleePlan;         //被叫号码编码类型
        public DJ_U8 m_u8CalleeSubType;      //被叫子地址号码类型
        public DJ_U8 m_u8CalleeSubPlan;      //被叫子地址号码编码类型
        public fixed DJ_U8 reserved[36];           //保留字段

    };
    /*消息类型*/
    public enum ITP_Q931_MSG_TYPE
    {
	    ITP_Q931_Resume       =  0x26,	 //恢复
	    ITP_Q931_Suspend      =  0x25,	 //暂停

	    ITP_Q931_Information    = 0x7b,    //信息 
	    ITP_Q931_Notify         = 0x6e,	 //通知
	    ITP_Q931_StatusEnquiry  = 0x75,    //状态询问
    };

    //呼叫信息结构
    public struct ITP_Q931_CALL_INFO_STRUCT
    {
	    public DJ_U8 m_u8CallerLen;                      //主叫号码长度
        public DJ_U8 m_u8CalleeLen;                      //被叫号码长度
        public DJ_U8 m_u8CallerSubAddrLen;               //主叫号码子地址长度
        public DJ_U8 m_u8CalleeSubAddrLen;               //被叫号码子地址长度
        public fixed DJ_S8 m_s8CallerId[32];                   //主叫号码缓冲区
        public fixed DJ_S8 m_s8CalleeId[32];                   //被叫号码缓冲区
        public fixed DJ_S8 m_s8CallerSubAddr[32];              //主叫号码子地址缓冲区 
        public fixed DJ_S8 m_s8CalleeSubAddr[32];              //被叫号码子地址缓冲区
    };

    //通道信息结构     
    public struct ITP_Q931_CHNL_INFO_STRUCT
    {
	    public DJ_U8  m_u8UnitId;                        //DSP 单元ID
        public DJ_U8  m_u8Reserved;                      //保留
        public DJ_U16 m_u16Chnl;                         //DSP单元内的通道号
    };

    //发起一个呼叫
    public struct ITP_Q931_CMD_TO_Q931_CALLOUT
    {
	    public ITP_Q931_CHNL_INFO_STRUCT m_ITP_q931ChnlInfo;     //通道信息
        public ITP_Q931_CALL_INFO_STRUCT m_ITP_q931CallInfo;     //呼叫信息
    	
	    public DJ_U8                 m_u8CallerNumType;  //主叫号码类型 
        public DJ_U8                 m_u8CalleeNumType;  //被叫号码类型
        public DJ_U16                m_u16OverlapFlag;   //重叠发送被叫号码标志
    };

    //追加被叫号码   
    public struct ITP_Q931_CMD_TO_Q931_APPEND_CALLEEID
    {
	    public ITP_Q931_CHNL_INFO_STRUCT m_ITP_q931ChnlInfo;     //通道信息

	    public DJ_U8                 m_u8Length;         //追加被叫号码长度
        public DJ_U8                 m_u8SendEnd;        //发送完全标志
        public fixed DJ_S8                 m_s8Reserved[2];    //保留
        public fixed DJ_S8                 m_s8CalleeBuf[32];  //被叫号码缓冲区
    };

    //设置通道状态
    public struct ITP_Q931_CMD_TO_Q931_CHNL_STATE
    {   
	    public ITP_Q931_CHNL_INFO_STRUCT m_ITP_q931ChnlInfo;     //通道信息
    	
        public DJ_U8                 m_u8State;                  //通道状态
        public fixed DJ_S8                 m_s8Reserved[3];            //保留
    };

    //Q931模块向流程执行模块反馈通道状态
    public struct ITP_Q931_EVENT_TO_FLOW_CHNL_STATE
    {
	    public DJ_U8                 m_u8State;          //通道状态
        public fixed DJ_S8                 m_s8Reserved[3];    //保留
    };

    //Q931模块向流程执行模块反馈呼出结果
    public struct ITP_Q931_EVENT_TO_FLOW_CALL_RESULT
    {
	    public DJ_U8                 m_u8CallResult;     //呼出结果
        public fixed DJ_S8                 m_s8Reserved[3];    //保留
    };

    //Q931模块向流程执行模块反馈挂机原因
    public struct ITP_Q931_EVENT_TO_FLOW_DISCONN_REASON
    {
	    public DJ_U8                 m_u8DisconnReason;  //挂机原因
        public fixed DJ_U8                 m_s8Reserved[3];    //保留
    };

    public struct ITP_Q931_PARAM
    {
        public ITP_Q931_CHNL_INFO_STRUCT m_ITP_q931ChnlInfo; //通道信息
    	
	    public DJ_U8                 m_u8ErrorCode;       //错误代码

	    public DJ_U8                 m_u8ParamType;       //参数类型
        public DJ_U8                 m_u8ParamLen;        //参数长度
        public fixed DJ_S8                 m_s8ParamData[100];  //参数数据
    };

    public struct ITP_Q931_SIGNAL
    {
        public ITP_Q931_CHNL_INFO_STRUCT m_ITP_q931ChnlInfo; //通道信息

        public DJ_U8                 m_u8ErrorCode;       //错误代码
        public DJ_U8                 m_u8SignalType;      //信令类型
    };

#endregion

#region ITPMsgPublic.h

    //通讯包特殊字段的定义
    public const int PKG_EXTEND_NORMAL     = 0x00;
    public const int PKG_EXTEND_ERROR      = 0x01;
    public const int PKG_EXTEND_CONFIG     = 0x02;
    public const int PKG_EXTEND_INTERFACE  = 0x03;

    //通讯消息包头
    public struct ITP_GUID_tag
	{
	    DJ_U8   m_u8ModuleType;  //模块类型
	    DJ_U8   m_u8MainFuncId;  //主功能ID      
	    DJ_U8   m_u8SubFuncId;   //子功能ID
	    DJ_U8   m_u8UnitId;      //单元ID 
	    DJ_U16  m_u16ChanId;     //通道ID
	};
    public struct PKG_HEAD_STRUCT
    {
	    public DJ_U8	m_u8PkgFlag;	// 包标志: 0xa5,0x5a
	    public DJ_U8	m_u8PkgExtend;	// 包扩展位
    	
	    public DJ_U16	m_u16DataLen;	//不定长数据长度

        //GUID的组成部分
	    public ITP_GUID_tag ITP_GUID;

	    public DJ_U16 m_u16Reserve;     //保留字段

    };

    public const int PKG_HEAD_LEN = 12; 

    public enum PACKAGE_TYPE
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

    public const int MODULE_INIT    = 0x01;    //模块已初始化
    public const int MODULE_START   = 0x02 ;   //模块已启动
    public const int MODULE_RELATE  = 0x04  ;  //模块已全部被其上级模块关联
    public const int MODULE_MONITOR = 0x08   ; //模块已被监视
    public const int MODULE_CONNECT = 0x10    ;//模块已连接
    public const int MODULE_STOPPING= 0x20;    //模块正在停止
    public const int MODULE_ISTUNING= 0x40 ;   //正在运行模块

    //心跳包数据
    public struct  ITP_HEART_TIME
    {
	    public DJ_U32	m_u32time;
	    public DJ_U32	m_u32date;
	    public DJ_U16  m_u16ModuleStates;
	    public DJ_U16  m_u16Param;
    };

    //关联模块数据
    //系统关联信息(关联模块信息)

    public struct ITP_MODULE_ADDR
    {
	    public DJ_U8	m_u8ModuleType;      //模块类型
        public DJ_U8   m_u8UnitID;          //模块单元ID
	    public DJ_U16  m_u16Port;           //模块连接的端口号
        public DJ_U32  m_u32IPAddress;      //模块IP地址
    };

    public struct ITP_MOD_VALIDITY_DATA
    {
	    public fixed DJ_S8         m_s8Username[32]; // 授权用户
	    public fixed DJ_S8         m_s8Password[32]; // 授权密码	
    };

    //监控模块数据包
    public struct ITP_MONITOR_ADDR
    {
	    public DJ_U8	m_u8ModuleType;      //模块类型
        public DJ_U8   m_u8UnitID;          //模块单元ID
	    public DJ_U16  m_u16ChanID;         //模块通道号
	    public DJ_U16	m_u16DebugLevel;     //模块监控级别
        public DJ_U16  m_u16UdpPort;        //模块连接的UDP端口号
        public DJ_U32  m_u32IPAddress;      //模块IP地址
	    public DJ_U32	m_u32Reserved;       //保留字段
    };

    public const int MAX_MACADDR_STR_LEN   =  0x14;     //网卡地址字符串长度最大值
    public const int MAX_MODULENAME_STR_LEN=	0x10;     //模块名字符串长度最大值
    public const int MAX_ERRMSG_LEN        =  0x60;     //错误信息字符串长度最大值

    //界面和配置管理之间的消息包
    public struct ITP_MODULE_STRUCT
    {
        public DJ_U8       m_u8ModuleType;       //模块类型
        public DJ_U8       m_u8UnitID;           //单元ID
        public DJ_U8		m_u8IsEnable;         //是否使能模块 0:不使能; 1:使能
        public DJ_U8       m_u8DSPType;          //DSP类型
        public DJ_U16      m_u16ModuleStates;    //模块状态
        public fixed DJ_S8       m_s8ModuleName[MAX_MODULENAME_STR_LEN]; //模块名
        public fixed DJ_S8       m_s8pMACAddress[MAX_MACADDR_STR_LEN];  //网卡地址，非DSP为全0
        public DJ_U32      m_u32Version;         //模块版本名
        public DJ_U32      m_u32IPAddress;       //IP地址
        public DJ_U32      m_u32Port;            //服务端口
	    public DJ_U32      m_u32Param;           //保留参数
    };

    //错误包数据
    public struct ITP_ERROR_STRUCT
    {
        public DJ_S32      m_s32ErrorCode;
        public fixed DJ_S8       m_s8pErrMsg[MAX_ERRMSG_LEN];
    };

    //**************************************
    //ITP配置界面和其他模块的消息包


    //根节点标识
    public const int ITP_ROOT_NODE   =   0x01;

    //节点类型，如果无此节点，则返回NODE_NONE
    public const int NODE_NONE     =  0x00;
    public const int NODE_PARENT   =  0x01;     //分支配置
    public const int NODE_RDONLY   =  0x02;     //只读配置
    public const int NODE_RDWR     =  0x03;     //可读写配置
    public const int NODE_SHOWONLY =  0x04;     //只读列表配置
    public const int NODE_RDWR_TABLE= 0x05;     //可读写列表配置 

    //节点定义信息
    public struct ITP_INTERFACE_NODE_DATA
    {
	    public DJ_U8       m_u8NodeType;
	    public fixed DJ_S8       m_s8ConfigName[31];
	    public fixed DJ_S8       m_s8ConfigFileName[32];
	    public DJ_S32      m_s32NodeMsgCode;
        public DJ_S32      m_s32ConfigNum;  
    };


    //子节点标识列表
    public struct ITP_INTERFACE_SUBNODE_DATA
    {
	    public DJ_U8       m_u8NodeType;
	    public fixed DJ_S8       m_s8ConfigName[31];
	    public DJ_S32      m_s32NodeMsgCode;
    };


    //读写节点数据
    public struct ITP_INTERFACE_DONE_DATA
    {
	    public DJ_S32      m_s32IsWriteini;
	    public DJ_S32      m_s32NodeMsgCode;
	    public DJ_U16      m_u16FisrtData;
	    public DJ_U16      m_u16DataNum;
    };


    //写节点数据结果
    public struct ITP_INTERFACE_WRDATA_MSG
    {
	    public DJ_S32      m_s32NodeMsgCode;
	    public DJ_S32      m_s32RetCode;
    };

    //读节点操作结果
    public struct ITP_INTERFACE_RDATA_MSG
    {
	    public DJ_U8       m_u8NodeType;
	    public fixed DJ_S8       m_s8ConfigFileName[31];
	    public DJ_S32      m_s32NodeMsgCode;
	    public DJ_U16      m_u16FisrtData;
	    public DJ_U16      m_u16DataNum;
    };
    //**************************************


    ////ITP配置界面和DSP模块进行固件更新的消息包

    public const uint ERASE_PASSWORD= 0x87654321   ; //DSP FLASH擦除密码
    public const int MAX_DATA_BLOCK_LENGTH=  4000 ; //写入FLASH数据的最大长度

    //读FLASH操作
    public struct ITP_FLASH_READ
    {
        public DJ_U32 m_u32AddrOffset;
	    public DJ_U32 m_u32ByteNum;
    };

    //写FLASH操作
    public struct ITP_FLASH_WRITE
    {
        public DJ_U32 m_u32AddrOffset;
	    public DJ_U32 m_u32ByteNum;
	    public fixed DJ_U8  m_u8pData[MAX_DATA_BLOCK_LENGTH];
    };

    //读FLASH操作结果
    public struct ITP_FLASH_READ_MSG
    {
        public DJ_U32 m_u32DataLen;
	    public fixed DJ_U8  m_u8pData[MAX_DATA_BLOCK_LENGTH];
    };

    //写FLASH操作结果
    public struct ITP_FLASH_WRITE_MSG
    {
        public DJ_U32 m_u32WriteStates;
	    public DJ_U32 m_u32CheckSum;
    };
    //*******************************************************


    //******************媒体处理层消息包定义***********************************
    public const int   MSG_MEDIA				=		0x3000;

    public const int   MSG_MEDIA_DEV			=		MSG_MEDIA + 0x100;
    public const int   MSG_MEDIA_DEV_OPEN		=	MSG_MEDIA_DEV + 0x001;
    public const int   MSG_MEDIA_DEV_CLOSE		=	MSG_MEDIA_DEV + 0x002;
    public const int   MSG_MEDIA_DEV_STOP		=	MSG_MEDIA_DEV + 0x003;

    public const int   MSG_MEDIA_PLAYREC		=		MSG_MEDIA_DEV + 0x100;
    public const int   MSG_MEDIA_PLAYREC_PLAY	=	0x001;
    public const int   MSG_MEDIA_PLAYREC_RECORD	=	0x002;

    public const int   MSG_MEDIA_UT				=	MSG_MEDIA_PLAYREC + 0x100;
        
    public const int   MSG_MEDIA_FSK			=		MSG_MEDIA_UT + 0x100;

    public const int   MSG_MEDIA_EC				=	MSG_MEDIA_FSK + 0x100;

    public const int   MSG_MEDIA_DTMF			=	MSG_MEDIA_EC + 0x100;

    public const int   MSG_MEDIA_CA				=	MSG_MEDIA_DTMF + 0x100;

    public const int   MSG_MEDIA_DIAL			=	MSG_MEDIA_CA + 0x100;

    public const int   MSG_MEDIA_PARM			=	MSG_MEDIA_DIAL + 0x100;

    public const int   MSG_MEDIA_CONF			=	MSG_MEDIA_PARM + 0x100;

    public const int   MSG_MEDIA_MS				=	MSG_MEDIA_CONF + 0x100;
    public const int   MSG_MEDIA_MS_SEND		=		MSG_MEDIA_MS + 0x001;
    public const int   MSG_MEDIA_MS_RECV		=		MSG_MEDIA_MS + 0x002;
    public const int MSG_MEDIA_MS_VLDRSC = MSG_MEDIA_MS + 0x003;



    public const int   MSG_MEDIA_END        =       0x3FFF;

#endregion

#region ITPMainModCallBack.h

    public const int ITP_MAX_UNIT_NUM            =                128;    // 最大UNIT数目
    public const int ITP_MAX_CH_NUM              =                128;    // 最大通道数目

    //回调接口函数指针
    public struct ITP_MOD_CALLBACK
    {
        public DJ_U32 m_pGetSelfUnitId;
        public DJ_U32 m_pGetModState;
        public DJ_U32 m_pSendPack;
        public DJ_U32 m_pReSendPack;
        public DJ_U32 m_pGetModIpPort;
        public DJ_U32 m_pGetModIniFile;
        public DJ_U32 m_pGetModUnitID;
        public DJ_U32 m_pGetModAllUnitID;
    };

#endregion
};
}