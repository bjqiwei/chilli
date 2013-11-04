#ifndef __XMS_ISUP_H__
#define __XMS_ISUP_H__


// ISUP信令消息定义(根据需要直接发送部分) /////////////////////////////////////
enum XMS_ISUP_Signalling_Message     // ISUP信令消息
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
enum XMS_ISUP_Signalling_Parameter                     // ISUP信令参数
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
typedef struct
{
	DJ_U8 m_u8AccessDeliveryID;  // 接入传递指示码	
	DJ_U8 m_u8Reserved[3];       // 对齐
} ISUP_spAccessDeliveryInformation, *PISUP_spAccessDeliveryInformation;


// 接入传送: ISUP_SP_AccessTransport //////////////////////////////////////////
typedef struct
{
	DJ_U8 m_u8AtpInformation[240];  // 信息单元按4.5/Q.931所述编码

	DJ_U8 m_u8AtpLen;               // 参数长度
	DJ_U8 m_u8Reserved[3];          // 对齐
} ISUP_spAccessTransport, *PISUP_spAccessTransport;


// 自动拥塞级: ISUP_SP_AutomaticCongestionLevel ///////////////////////////////
typedef struct
{	
	DJ_U8 m_u8CongestionLevelExceeded;     // 拥塞级超过某个级别
	DJ_U8 m_u8Reserved[3];                 // 对齐
} ISUP_spAutomaticCongestionLevel, *PISUP_spAutomaticCongestionLevel;


// 后向呼叫指示码: ISUP_SP_BackwardCallIndicator //////////////////////////////
typedef struct
{	
	DJ_U8 m_u8ChargeIndicator;             // 计费指示码
	DJ_U8 m_u8CalledStatusIndicator;       // 被叫用户状态指示码
	DJ_U8 m_u8CalledCategoryIndicator;     // 被叫用户类别指示码
 	DJ_U8 m_u8EndToEndMethodIndicator;     // 端到端方法指示码
	
	DJ_U8 m_u8InterworkingIndicator;       // 互通指示码
	DJ_U8 m_u8EndToEndInformationIndicator;// 端到端信息指示码
	DJ_U8 m_u8ISDNUserPartIndicator;       // ISDN用户部分指示码
	DJ_U8 m_u8HoldingIndicator;            // 保持指示码
	DJ_U8 m_u8ISDNAccessIndicator;         // ISDN接入指示码
	DJ_U8 m_u8EchoControlDeviceIndicator;  // 回音控制器件指示码
	DJ_U8 m_u8SCCPMethodIndicator;         // SCCP方法指示码
	DJ_U8 m_u8Reserved;                    // 对齐
} ISUP_spBackwardCallIndicator, *PISUP_spBackwardCallIndicator;


// 呼叫转移信息: ISUP_SP_CallDiversionInformation /////////////////////////////
typedef struct
{	
	DJ_U8 m_u8NotificationSubscriptionOptions; // 通知登记任选
	DJ_U8 m_u8RedirectingReason;               // 改发原因
	DJ_U8 m_u8Reserved[2];                     // 对齐
} ISUP_spCallDiversionInformation, *PISUP_spCallDiversionInformation;


// 呼叫历史信息: ISUP_SP_CallHistoryInformation ///////////////////////////////
typedef struct
{	
	DJ_U16 m_u16PropagationDelayValue; // 传播时延值
	DJ_U8  m_u8Reserved[2];            // 对齐
} ISUP_spCallHistoryInformation, *PISUP_spCallHistoryInformation;


// 呼叫参考: ISUP_SP_CallReference ////////////////////////////////////////////
typedef struct
{	
	DJ_U32  m_u32CallIdentity; // 呼叫识别

	DJ_U32  m_u32SPcode;       // 点码
	DJ_U8   m_u8Reserved[4];   // 备用
} ISUP_spCallReference, *PISUP_spCallReference;


// 被叫用户号码: ISUP_SP_CalledPartNumber /////////////////////////////////////
typedef struct
{
	DJ_U8 m_u8NatureOfAddressIndicator;  // 地址性质指示码
	DJ_U8 m_u8OddEvenIndicator;          // 奇偶指示码
	DJ_U8 m_u8NumberingPlanIndicator;    // 号码计划指示
	DJ_U8 m_u8InternalNetworkNumberIndicator;// 内部网络号码指示码

	DJ_U8 m_u8Reserved[4];               // 备用
	
 	DJ_S8 m_s8AddressSignal[40];         // 地址信号	
} ISUP_spCalledPartNumber, *PISUP_spCalledPartNumber;


// 主叫用户号码: ISUP_SP_CallingPartNumber ////////////////////////////////////
typedef struct
{	
	DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质指示码
	DJ_U8 m_u8OddEvenIndicator;         // 奇偶指示码
	
	DJ_U8 m_u8Screening;                // 屏蔽
	DJ_U8 m_u8AddressPresentationRestrictedIndicator;  // 地址显示指示
	DJ_U8 m_u8NumberingPlanIndicator;   // 号码计划指示
	DJ_U8 m_u8NumberIncompleteIndicator;// 主叫号码不全指示	
	
	DJ_S8 m_s8AddressSignal[40]; // 地址信号
	
	DJ_U8 m_u8Reserved[2];       // 对齐
} ISUP_spCallingPartNumber, *PISUP_spCallingPartNumber;


// 主叫用户类别: ISUP_SP_CallingPartCategory //////////////////////////////////
typedef struct
{	
	DJ_U8 m_u8CallingPartyCategory; // 主叫用户类别
	DJ_U8 m_u8Reserved[3];          // 对齐
} ISUP_spCallingPartCategory, *PISUP_spCallingPartCategory;


// 原因指示码: ISUP_SP_CauseIndicator /////////////////////////////////////////
typedef struct
{	
	DJ_U8 m_u8Location;             // 定位
	DJ_U8 m_u8CodindStandard;       // 编码标准
	DJ_U8 m_u8ExtensionIndicator1;  // 扩充
	
	DJ_U8 m_u8CauseValue;           // 原因值
	DJ_U8 m_u8ExtensionIndicator2;  // 扩充
	
	DJ_U8 m_u8Reserved[2];          // 对齐
	
	DJ_U8 m_u8Diagnose[32];         // 诊断	
	DJ_U8 m_u8DiagnoseLen;          // 诊断长度
} ISUP_spCauseIndicator, *PISUP_spCauseIndicator;


// 电路群监视消息类型指示码: ISUP_SP_CircuitGroupSupervisionIndicator /////////
typedef struct
{
	DJ_U8 m_u8CircuitGroupSupervisionIndicator; // 类型指示码
	DJ_U8 m_u8Reserved[3]; // 对齐
} ISUP_spCircuitGroupSupervisionIndicator, *PISUP_spCircuitGroupSupervisionIndicator;


// 电路状态指示码: ISUP_SP_CircuitStateIndicator //////////////////////////////
typedef struct
{	
	DJ_U8 m_u8CircuitStateIndicator[32];
} ISUP_spCircuitStateIndicator, *PISUP_spCircuitStateIndicator;


// 闭合用户群相关码: ISUP_SP_CUGInterlockCode /////////////////////////////////
typedef struct
{	
	DJ_U8  m_u8NIDigit1;  // 第1个NI数字
	DJ_U8  m_u8NIDigit2;  // 第2个NI数字
	DJ_U8  m_u8NIDigit3;  // 第3个NI数字
	DJ_U8  m_u8NIDigit4;  // 第4个NI数字	
	
	DJ_U16 m_u16BinaryCode; // 二进制码
	DJ_U8  m_u8Reserved[2]; // 对齐
} ISUP_spCUGInterlockCode, *PISUP_spCUGInterlockCode;


// 接续的号码: ISUP_SP_ConnectedNumber ////////////////////////////////////////
typedef struct
{	
	DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质指示码
	DJ_U8 m_u8OddEvenIndicator;         // 奇偶指示码
    
	DJ_U8 m_u8ScreeningIndicator;       // 屏蔽指示码
	DJ_U8 m_u8AddressPresentationRestrictedIndicator; // 地址显示限制
	DJ_U8 m_u8NumberingPlanIndicator;   // 号码计划指示	

	DJ_U8 m_u8Reserved[3];              // 备用
	
	DJ_S8 m_s8AddressSignal[40];        // 地址信号	
} ISUP_spConnectedNumber, *PISUP_spConnectedNumber;


// 接续请求: ISUP_SP_ConnectionRequest ////////////////////////////////////////
typedef struct
{	
	DJ_U32 m_u32LocalReference; // 呼叫识别
	
	DJ_U32 m_u32SPcode;         // 点码
	
	DJ_U8  m_u8ProtocolClass;   // 协议类别
	DJ_U8  m_u8Credit;          // 信号量

	DJ_U8  m_u8Reserved[2];     // 对齐
} ISUP_spConnectionRequest, *PISUP_spConnectionRequest;


// 导通指示码: ISUP_SP_ContitnuityIndicator ///////////////////////////////////
typedef struct
{	
	DJ_U8 m_u8ContinuityIndicator; // 导通指示码
	DJ_U8 m_u8Reserved[3]; // 对齐
} ISUP_spContitnuityIndicator, *PISUP_spContitnuityIndicator;


// 回声控制信息: ISUP_SP_EchoControlInformation ///////////////////////////////
typedef struct
{	
	DJ_U8 m_u8OutEchoControlInformationIndicator; // 去话半回声控制响应指示
	DJ_U8 m_u8InEchoControlInformationIndicator;  // 来话半回声控制响应指示
	DJ_U8 m_u8OutEchoControlRequestIndicator;     // 去话半回声控制请求指示
	DJ_U8 m_u8InEchoControlRequestIndicator;      // 来话半回声控制请求指示
} ISUP_spEchoControlInformation, *PISUP_spEchoControlInformation;


// 事件信息: ISUP_SP_EventInformation /////////////////////////////////////////
typedef struct
{
	DJ_U8 m_u8EventIndicator; // 事件指示码
	DJ_U8 m_u8EventPresentationRestrictedIndicator;// 事件显示限制指示码	
	DJ_U8 m_u8Reserved[2]; // 对齐
} ISUP_spEventInformation, *PISUP_spEventInformation;


// 功能指示码: ISUP_SP_FacilityIndicator //////////////////////////////////////
typedef struct
{	
	DJ_U8 m_u8FacilityIndicator; // 功能指示码
	DJ_U8 m_u8Reserved[3];
} ISUP_spFacilityIndicator, *PISUP_spFacilityIndicator;


// 前向呼叫指示码: ISUP_SP_ForwardCallIndicator ///////////////////////////////
typedef struct
{	
	DJ_U8 m_u8NationalInternatoinalIndicator; // 国内/国际呼叫指示码
	DJ_U8 m_u8EndToEndMethodIndicator;        // 端到端方法指示码
	DJ_U8 m_u8InterworkingIndicator;          // 互通指示码
	DJ_U8 m_u8EndToEndInformationIndicator;   // 端到端信息指示码
	DJ_U8 m_u8ISDNUserPartIndicator;          // ISDN用户部分指示码
	DJ_U8 m_u8ISDNUserPartPreferenceIndicator;// ISDN用户部分优先指示码
	
	DJ_U8 m_u8ISDNAccessIndicator; // ISDN接入指示码
	DJ_U8 m_u8SCCPMethodIndicator; // SCCP方法指示码
	
	DJ_U8 m_u8Reserved[4];         // 备用
} ISUP_spForwardCallIndicator, *PISUP_spForwardCallIndicator;


// 类属数字: ISUP_SP_GenericDigit /////////////////////////////////////////////
typedef struct
{	
	DJ_U8 m_u8TypeOfDigit;   // 数字类型
	DJ_U8 m_u8EncodingScheme;// 编码计划	
	
	DJ_U8 m_u8Digit[32];     // 数字
	DJ_U8 m_u8DigitLen;      // 数字长度
	
	DJ_U8 m_u8Reserved;      // 对齐
} ISUP_spGenericDigit, *PISUP_spGenericDigit;


// 类属通知指示码: ISUP_SP_GenericNotifyIndicator /////////////////////////////
typedef struct
{
	DJ_U8 m_u8NotificationIndicator; // 通知指示码
	DJ_U8 m_u8ExtensionIndicator;    // 扩充指示码
	DJ_U8 m_u8Reserved[2];           // 对齐
} ISUP_spGenericNotifyIndicator, *PISUP_spGenericNotifyIndicator;


// 类属号码: ISUP_SP_GenericNumber ////////////////////////////////////////////
typedef struct
{	
	DJ_U8 m_u8NumberQualifierIndicator;    // 号码限定指示码
	
	DJ_U8 m_u8NatureOfAddressIndicator;// 地址性质指示码
	DJ_U8 m_u8OddEvenIndicator;  // 奇偶指示码	
	
	DJ_U8 m_u8ScreeningIndicator;// 屏蔽
	DJ_U8 m_u8AddressPresentationRestrictedIndicator; // 显示指示
	DJ_U8 m_u8NumberingPlanIndicator;    // 号码计划指示
	DJ_U8 m_u8NumberIncompleteIndicator; //	号码不全指示	
	
	DJ_S8 m_s8AddressSignal[40]; // 地址信号
	
	DJ_U8 m_u8Reserved;          // 对齐
} ISUP_spGenericNumber, *PISUP_spGenericNumber;


// 类属参考: ISUP_SP_GenericReference /////////////////////////////////////////
typedef struct  
{
	DJ_U8 m_u8ReferenceRestrictedIndicator; // 参考限定指示码
	DJ_U8 m_u8ReferenceLength;  // 参考长度	
	
	DJ_U8 m_u8ReferenceCode[4]; // 参考八位组信息

	DJ_U8 m_u8Reserved[2];      // 对齐
} ISUP_spGenericReference, *PISUP_spGenericReference;


// 信息指示码: ISUP_SP_InformationIndicator ///////////////////////////////////
typedef struct
{	
	DJ_U8 m_u8CallingPartyAddressResponseIndicator; // 主叫用户地址响应指示码
	DJ_U8 m_u8HoldProvidedIndicator; // 保持提供指示码
	
	DJ_U8 m_u8CallingPartyCategoryResponseIndicator; // 主叫用户类别响应指示码
	DJ_U8 m_u8ChargeInformationResponseIndicator;  // 计费信息响应指示码
	DJ_U8 m_u8SolicitedInformationIndicator;  // 请求信息指示码
	
	DJ_U8 m_u8Reserved[3]; // 对齐
} ISUP_spInformationIndicator, *PISUP_spInformationIndicator;


// 信息请示指示码: ISUP_SP_InformationRequestIndicator ////////////////////////
typedef struct
{	
	DJ_U8 m_u8CallingPartyAddressRequestIndicator; // 主叫用户地址请求指示码
	DJ_U8 m_u8HoldingIndicator; // 保持指示码
	
	DJ_U8 m_u8CallingPartyCategoryRequestIndicator;// 主叫用户类别请求指示码
	DJ_U8 m_u8ChargeInformationRequestIndicator;   // 计费信息请求指示码
	
	DJ_U8 m_u8MaliciousCallIdentificationRequestIndicator; // 恶意呼叫识别
	DJ_U8 m_u8Reserved[3];  // 对齐
} ISUP_spInformationRequestIndicator, *PISUP_spInformationRequestIndicator;


// 定位号码: ISUP_SP_LocationNumber ///////////////////////////////////////////
typedef struct
{	
	DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质指示码
	DJ_U8 m_u8OddEvenIndicator;         // 奇偶指示码

	DJ_U8 m_u8ScreeningIndicator;       // 屏蔽指示码
	DJ_U8 m_u8AddressPresentationRestrictedIndicator; // 地址显示限制指示码
	DJ_U8 m_u8NumberingPlanIndicator;   // 号码计划指示码
	DJ_U8 m_u8InternalNetworkNumberIndicator; // 内部网络号码指示码	
	
	DJ_S8 m_s8AddressSignal[40]; // 地址信号

	DJ_U8 m_u8Reserved[2]; // 对齐
} ISUP_spLocationNumber, *PISUP_spLocationNumber;


// MCID请求指示码: ISUP_SP_MCIDRequestIndicator ///////////////////////////////
typedef struct
{	
	DJ_U8 m_u8MCIDRequestIndicator; // MCID请求指示码
	DJ_U8 m_u8HoldingIndicator;     // 保持指示码
	DJ_U8 m_u8Reserved[2]; // 备用
} ISUP_spMCIDRequestIndicator, *PISUP_spMCIDRequestIndicator;


// MCID 响应指示码: ISUP_SP_MCIDResponseIndicator /////////////////////////////
typedef struct
{	
	DJ_U8 m_u8MCIDResponseIndicator; // MCID响应指示码
	DJ_U8 m_u8HoldProvidedIndicator; // 保持提供指示码
	DJ_U8 m_u8Reserved[2]; // 备用
} ISUP_spMCIDResponseIndicator, *PISUP_spMCIDResponseIndicator;


// 消息兼容性信息: ISUP_SP_MsgCompatibilityInformation ////////////////////////
typedef struct
{	
	DJ_U8 m_u8TransitAtIntermediateExchangeIndicator1;// 在中间交换局汇接指示码
	DJ_U8 m_u8ReleaseCallIndicator1;      // 释放呼叫指示码
	DJ_U8 m_u8SendNotificationIndicator1; // 发送通知指示码
	DJ_U8 m_u8DiscardMessageIndicator1;   // 舍弃消息指示码
	DJ_U8 m_u8PassOnNotPossibleIndicator1;// 通过不可能指示码
	DJ_U8 m_u8ExtensionIndicator1;        // 扩充指示码
	DJ_U8 m_u8Reserved1[2];               // 对齐
	
	DJ_U8 m_u8TransitAtIntermediateExchangeIndicator2;// 在中间交换局汇接指示码
	DJ_U8 m_u8ReleaseCallIndicator2;      // 释放呼叫指示码
	DJ_U8 m_u8SendNotificationIndicator2; // 发送通知指示码
	DJ_U8 m_u8DiscardMessageIndicator2;   // 舍弃消息指示码
	DJ_U8 m_u8PassOnNotPossibleIndicator2;// 通过不可能指示码
	DJ_U8 m_u8ExtensionIndicator2;        // 扩充指示码
	DJ_U8 m_u8Reserved2[2];               // 对齐
} ISUP_spMsgCompatibilityInformation, *PISUP_spMsgCompatibilityInformation;


// MLPP优先: ISUP_SP_MlppPrecedence ///////////////////////////////////////////
typedef struct
{	
	DJ_U8  m_u8PrecedenceLevel;  // 优先级	
	DJ_U8  m_u8LFB;        // LFB
	DJ_U8  m_u8Reserved[2];// 对齐
	
	DJ_U8  m_u8NIDigit1;  // 第1个NI数字
	DJ_U8  m_u8NIDigit2;  // 第2个NI数字
	DJ_U8  m_u8NIDigit3;  // 第3个NI数字
	DJ_U8  m_u8NIDigit4;  // 第4个NI数字	
	
	DJ_U32 m_u32MLPPServiceDomain;
} ISUP_spMlppPrecedence, *PISUP_spMlppPrecedence;


// 接续性质指示码: ISUP_SP_NatureOfConnectionIndicator ////////////////////////
typedef struct
{	
	DJ_U8 m_u8SatelliteIndicator;        // 卫星指示码
	DJ_U8 m_u8ContinuityCheckIndicator;  // 导通检验指示码
	DJ_U8 m_u8EchoControlDeviceIndicator;// 回声控制器件指示码
	DJ_U8 m_u8Reserved;
} ISUP_spNatureOfConnectionIndicator, *PISUP_spNatureOfConnectionIndicator;


// 网络特定功能: ISUP_SP_NetworkSpecificFacility //////////////////////////////
typedef struct
{	
	DJ_U8 m_u8NsfInformation[32];  // 参数信息
	
	DJ_U8 m_u8NsfLen;              // 参数长度
	DJ_U8 m_u8Reserved[3];         // 对齐	
} ISUP_spNetworkSpecificFacility, *PISUP_spNetworkSpecificFacility;


// 任选后向呼叫指示码: ISUP_SP_OptBackwardCallIndicator ///////////////////////
typedef struct
{	
	DJ_U8 m_u8InBandInformationIndicator;    // 带内信息指示码
	DJ_U8 m_u8CallTransferPossibleIndicator; // 呼叫转移可能发送指示码
	DJ_U8 m_u8SimpleSegmentationIndicator;   // 简单分段指示码
	DJ_U8 m_u8MLPPUserIndicator;             // MLPP用户指示码

	DJ_U8 m_u8Reserved[4];
} ISUP_spOptBackwardCallIndicator, *PISUP_spOptBackwardCallIndicator;


// 任选前向呼叫指示码: ISUP_SP_OptForwardCallIndicator ////////////////////////
typedef struct
{		
	DJ_U8 m_u8ClosedUserGroupCallIndicator; // CUG呼叫指示码
	DJ_U8 m_u8SimpleSegmentationIndicator;  // 简单分段指示码
	DJ_U8 m_u8UserIdentityRequestIndicator; // 接续的用户识别请求指示码
	DJ_U8 m_u8Reserved;                     // 对齐
} ISUP_spOptForwardCallIndicator, *PISUP_spOptForwardCallIndicator;


// 原被叫号码: ISUP_SP_OriginalCalledNumber ///////////////////////////////////
typedef struct
{	
	DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质指示码
	DJ_U8 m_u8OddEvenIndicator;         // 奇偶指示码
	
	DJ_U8 m_u8AddressPresentationRestrictedIndicator; // 显示指示
	DJ_U8 m_u8NumberingPlanIndicator; // 号码计划指示
	
	DJ_S8 m_s8AddressSignal[40]; // 地址信号
	
	DJ_U8 m_u8Reserved[4];  // 备用
} ISUP_spOriginalCalledNumber, *PISUP_spOriginalCalledNumber;


// 始发国际交换中心(ISC)的点码: ISUP_SP_OriginationISCPointCode ///////////////
typedef struct
{
	DJ_U32 m_u32SPcode;     // 点码
	DJ_U8  m_u8Reserved[4]; // 备用
} ISUP_spOriginationISCPointCode, *PISUP_spOriginationISCPointCode;


// 参数兼容性信息: ISUP_SP_ParamCompatibilityInformation //////////////////////
typedef struct
{
	DJ_U8 m_u8UpgradedParameter1;         // 第一个升格参数	
	DJ_U8 m_u8TransitAtIntermediateExchangeIndicator1;// 在中间交换局汇接指示码
	DJ_U8 m_u8ReleaseCallIndicator1;      // 释放呼叫指示码
	DJ_U8 m_u8SendNotificationIndicator1; // 发送通知指示码
	DJ_U8 m_u8DiscardMessageIndicator1;   // 舍弃消息指示码
	DJ_U8 m_u8DiscardParameterIndicator1; // 舍弃参数指示码
	DJ_U8 m_u8ExtensionIndicator1;        // 扩充指示码
	DJ_U8 m_u8Reserved1;                  // 备用
	
	DJ_U8 m_u8UpgradedParameter2;         // 第二个升格参数	
	DJ_U8 m_u8TransitAtIntermediateExchangeIndicator2;// 在中间交换局汇接指示码
	DJ_U8 m_u8ReleaseCallIndicator2;      // 释放呼叫指示码
	DJ_U8 m_u8SendNotificationIndicator2; // 发送通知指示码
	DJ_U8 m_u8DiscardMessageIndicator2;   // 舍弃消息指示码
	DJ_U8 m_u8DiscardParameterIndicator2; // 舍弃参数指示码
	DJ_U8 m_u8ExtensionIndicator2;        // 扩充指示码
	DJ_U8 m_u8Reserved2;                  // 备用

	DJ_U8 m_u8UpgradedParameter3;         // 第三个升格参数	
	DJ_U8 m_u8TransitAtIntermediateExchangeIndicator3;// 在中间交换局汇接指示码
	DJ_U8 m_u8ReleaseCallIndicator3;      // 释放呼叫指示码
	DJ_U8 m_u8SendNotificationIndicator3; // 发送通知指示码
	DJ_U8 m_u8DiscardMessageIndicator3;   // 舍弃消息指示码
	DJ_U8 m_u8DiscardParameterIndicator3; // 舍弃参数指示码
	DJ_U8 m_u8ExtensionIndicator3;        // 扩充指示码
	DJ_U8 m_u8Reserved3;                  // 备用
} ISUP_spParamCompatibilityInformation, *PISUP_spParamCompatibilityInformation;


// 传播延时计数器: ISUP_SP_PropagationDelayCounter ////////////////////////////
typedef struct
{	
	DJ_U16 m_u16PropagationDelayValue;  // 传播时延值
	DJ_U8  m_u8Reserved[2]; // 对齐
} ISUP_spPropagationDelayCounter, *PISUP_spPropagationDelayCounter;


// 范围和状态: ISUP_SP_RangeState /////////////////////////////////////////////
typedef struct
{
	DJ_U8  m_u8Range;      // 范围
	DJ_U8  m_u8Reserved[3];// 对齐
	
	DJ_U32 m_u32Status;    // 状态
} ISUP_spRangeState, *PISUP_spRangeState;


// 改发号码: ISUP_SP_RedirectingNumber ////////////////////////////////////////
typedef struct
{	
	DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质指示码
	DJ_U8 m_u8OddEvenIndicator; // 奇偶指示码	
    
	DJ_U8 m_u8AddressPresentationRestrictedIndicator; // 显示限制指示码
	DJ_U8 m_u8NumberingPlanIndicator; // 号码计划指示码	
	
	DJ_S8 m_s8AddressSignal[40]; // 地址信号

	DJ_U8 m_u8Reserved[4];  // 备用
} ISUP_spRedirectingNumber, *PISUP_spRedirectingNumber;


// 改发信息: ISUP_SP_RedirectionInformation ///////////////////////////////////
typedef struct
{
	DJ_U8 m_u8RedirectingIndicator; // 改发指示码
	DJ_U8 m_u8OriginalRedirectionReason; // 原理的改发原因
	DJ_U8 m_u8RedirectionCounter;   // 改发计数器
	DJ_U8 m_u8RedirectingReason;    // 改发原因

	DJ_U8 m_u8Reserved[4]; // 备用	
} ISUP_spRedirectionInformation, *PISUP_spRedirectionInformation;


// 改发号码: ISUP_SP_RedirectionNumber ////////////////////////////////////////
typedef struct
{	
	DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质指示码
	DJ_U8 m_u8OddEvenIndicator;         // 奇偶指示码
	DJ_U8 m_u8NumberingPlanIndicator;   // 号码计划指示码
	DJ_U8 m_u8InternalNetworkNumberIndicator; // 内部网络号码指示码
	
	DJ_S8 m_s8AddressSignal[40];            // 地址信号

	DJ_U8 m_u8Reserved[4]; // 备用
} ISUP_spRedirectionNumber, *PISUP_spRedirectionNumber;


// 改发号码限制参数: ISUP_SP_RedirectionRestricition //////////////////////////
typedef struct
{	
	DJ_U8 m_u8PresentationRestrictedIndicator; // 显示限制指示码
	DJ_U8 m_u8Reserved[3];
} ISUP_spRedirectionRestricition, *PISUP_spRedirectionRestricition;


// 远端操作: ISUP_SP_RemoteOperation //////////////////////////////////////////
typedef struct
{	
	DJ_U8 m_u8ProtocolProfile;    // 协议剖析    
	DJ_U8 m_u8ExtensionIndicator; // 扩充	
	
	DJ_U8 m_u8Component[240];
	
	DJ_U8 m_u8ComponentLen;
	DJ_U8 m_u8Reserved;          // 对齐
} ISUP_spRemoteOperation, *PISUP_spRemoteOperation;


// 业务激活: ISUP_SP_ServiceActivation ////////////////////////////////////////
typedef struct
{
	DJ_U8 m_u32FeatureCode[32];  // 特征码
	
	DJ_U8 m_u8FCLen;             // 特征码长度
	DJ_U8 m_u8Reserved[3];       // 对齐	
} ISUP_spServiceActivation, *PISUP_spServiceActivation;


// 信令点编码: ISUP_SP_SignalPointCode ////////////////////////////////////////
typedef struct
{	
	DJ_U32 m_u32SPcode;     // 点码	
	DJ_U8  m_u8Reserved[4]; // 备用	
} ISUP_spSignalPointCode, *PISUP_spSignalPointCode;


// 后续号码: ISUP_SP_SubsequentNumber /////////////////////////////////////////
typedef struct
{		
	DJ_U8 m_u8OddEvenIndicator; // 奇偶指示码
	DJ_U8 m_u8Reserved[3];      // 对齐
	
	DJ_S8 m_s8AddressSignal[40];    // 地址信号
} ISUP_spSubsequentNumber, *PISUP_spSubsequentNumber;


// 暂停恢复指示: ISUP_SP_SuspendResumeIndicator ///////////////////////////////
typedef struct
{	
	DJ_U8 m_u8SuspendResumeIndicator; // 暂停/恢复指示码
	DJ_U8 m_u8Reserved[3]; // 对齐	
} ISUP_spSuspendResumeIndicator, *PISUP_spSuspendResumeIndicator;


// 汇接网络选择: ISUP_SP_TransitNetworkSelection //////////////////////////////
typedef struct
{	
	DJ_U8 m_u8NetworkIdentificationPlan;   // 网络识别计划
	DJ_U8 m_u8TypeOfNetworkIdentification; // 网络识别类型
	DJ_U8 m_u8OddEvenIndicator;            // 奇偶指示码
	DJ_U8 m_u8Reserved;                    // 对齐
	
	DJ_U8 m_u8NetworkIdentification[32];   // 网络识别
	
	DJ_U8 m_u8NetIdLen;                    // 网络识别长度
	DJ_U8 m_u8Rev[3];                      // 对齐	
} ISUP_spTransitNetworkSelection, *PISUP_spTransitNetworkSelection;


// 传输媒价要求: ISUP_SP_TransmissionMediumRequirement ////////////////////////
typedef struct
{	
	DJ_U8 m_u8TransmissionMediumRequirement; // 传送媒介要求
	DJ_U8 m_u8Reserved[3]; // 对齐	
} ISUP_spTransmissionMediumRequirement, *PISUP_spTransmissionMediumRequirement;


// 传输媒介要求(基本): ISUP_SP_TransmissionMediumRequirementPrime /////////////
typedef struct
{	
	DJ_U8 m_u8TransmissionMediumRequirement; // 传送媒介要求
	DJ_U8 m_u8Reserved[3]; // 对齐
} ISUP_spTransmissionMediumRequirementPrime, *PISUP_spTransmissionMediumRequirementPrime;


// 使用中的传输媒介: ISUP_SP_TransmissionMediumUsed ///////////////////////////
typedef struct
{	
	DJ_U8 m_u8TransmissionMediumRequirement; // 传送媒介要求
	DJ_U8 m_u8Reserved[3]; // 对齐
} ISUP_spTransmissionMediumUsed, *PISUP_spTransmissionMediumUsed;


// 用户业务信息: ISUP_SP_UserServiceInformation ///////////////////////////////
typedef struct
{
	DJ_U8 m_u8USInformation[32]; // 用户业务信息
	
	DJ_U8 m_u8USILen;            // 信息长度
	DJ_U8 m_u8Reserved[3];       // 对齐	
} ISUP_spUserServiceInformation, *PISUP_spUserServiceInformation;


// 基本用户业务信息: ISUP_SP_UserServiceInformationPrime //////////////////////
typedef struct
{
	DJ_U8 m_u8USInformation[32]; // 用户业务信息
	
	DJ_U8 m_u8USILen;            // 信息长度
	DJ_U8 m_u8Reserved[3];       // 对齐	
} ISUP_spUserServiceInformationPrime, *PISUP_spUserServiceInformationPrime;


// 用户电信业务信息: ISUP_SP_UserTeleserviceInformation ///////////////////////
typedef struct
{	
	DJ_U8 m_u8Presentation;   // 显示
	DJ_U8 m_u8Interpretation; // 解释
	DJ_U8 m_u8CodingStandard; // 编码标准
	DJ_U8 m_u8ExtensionIndicator1; // 扩充
	
	DJ_U8 m_u8HighLayerCharacteristicsIdentification; // 高层特性识别
	DJ_U8 m_u8ExtensionIndicator2; // 扩充

	DJ_U8 m_u8ExtendedHighLayerCharacteristicsIdentification; // 扩充的高层特性识别
	DJ_U8 m_u8ExtensionIndicator3;	// 扩充
} ISUP_spUserTeleserviceInformation, *PISUP_spUserTeleserviceInformation;


// 用户至用户指示码: ISUP_SP_UserToUserIndicator //////////////////////////////
typedef struct
{	
	DJ_U8 m_u8Type;     // 类型
	DJ_U8 m_u8Service1; // 业务
	DJ_U8 m_u8Service2; // 业务
	DJ_U8 m_u8Service3; // 业务
	DJ_U8 m_u8NetworkDiscardIndicator; // 网络舍弃指示码

	DJ_U8 m_u8Reserved[3]; // 对齐
} ISUP_spUserToUserIndicator, *PISUP_spUserToUserIndicator;


// 用户至用户信息: ISUP_SP_UserToUserInformation //////////////////////////////
typedef struct
{	
	DJ_U8 m_u8UserToUserInformation[240];
	
	DJ_U8 m_u8UifLen;      // 信息长度
	DJ_U8 m_u8Reserved[3]; // 对齐
} ISUP_spUserToUserInformation, *PISUP_spUserToUserInformation;


#endif
