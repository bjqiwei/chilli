#ifndef __XMS_TUP_H__
#define __XMS_TUP_H__


// TUP信令消息定义(根据需要直接发送部分) //////////////////////////////////////
enum XMS_TUP_Signalling_Message     // TUP信令消息
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
enum XMS_TUP_Signalling_Parameter                   // TUP信令参数
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
typedef struct
{
	DJ_U8 m_u8ACCInformation; // ACC信息
	DJ_U8 m_u8Reserved[3]; // 备用
}TUP_spAccMessageIndicator, *PTUP_spAccMessageIndicator;


// ACM消息指示码: TUP_SP_AcmMessageIndicator //////////////////////////////////
// 信令: ACM
typedef struct
{
	DJ_U8 m_u8TypeOfACMIndicator; // 地址全信号类型表示语
	DJ_U8 m_u8SubscriberFreeIndicator; // 用户闲表示语
	DJ_U8 m_u8IncomingEchoSuppressorIndicator; // 来话回声抑制器表示语
	DJ_U8 m_u8CallForwardingIndicator; // 呼叫转移表示语
	DJ_U8 m_u8SignallingPathIndicator; // 信号通道表示语
	DJ_U8 m_u8Reserved[3]; // 备用
}TUP_spAcmMessageIndicator, *PTUP_spAcmMessageIndicator;


// 被叫用户号码: TUP_SP_CalledPartAddress /////////////////////////////////////
// 信令: IAM/IAI
typedef struct
{
	DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质表示语
	DJ_U8 m_u8NumberOfAddressSignal; // 地址信号的数量
	DJ_U8 m_u8Reserved[2]; // 备用
	
	DJ_S8 m_s8AddressSignal[40]; // 地址信号
}TUP_spCalledPartAddress, *PTUP_spCalledPartAddress;


// 主叫用户号码: TUP_SP_CallingLineAddress ////////////////////////////////////
// 信令: IAI/GSM
typedef struct
{
	DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质表示语
	DJ_U8 m_u8PresentationIndicator; // 提供主叫用户线标识表示语
	DJ_U8 m_u8IncompleteIndicator; // 主叫用户线标识不全表示语
	DJ_U8 m_u8NumberOfAddressSignal; // 主叫地址信号的数量
	
	DJ_S8 m_s8AddressSignal[40]; // 地址信号
}TUP_spCallingLineAddress, *PTUP_spCallingLineAddress;


// 主叫用户类别: TUP_SP_CallingPartyCategory //////////////////////////////////
// 信令: IAM/IAI/GSM
typedef struct
{
	DJ_U8 m_u8CallingPartyCategory;  // 主叫用户类别
	DJ_U8 m_u8Reserved[3]; // 备用
}TUP_spCallingPartyCategory, *PTUP_spCallingPartyCategory;


// 接续性质指示码: TUP_SP_ConnectionNatureIndicator ///////////////////////////
// 信令: IAM/IAI
typedef struct
{	
	DJ_U8 m_u8NatureOfCircuitIndicator; // 电路性质表示语
	DJ_U8 m_u8ContinuityCheckIndicator; // 导通检验表示语
	DJ_U8 m_u8EchoSuppressorIndicator;  // 去话回声抑制器表示语
	DJ_U8 m_u8Reserved;
}TUP_spConnectionNatureIndicator, *PTUP_spConnectionNatureIndicator;


// EUM消息八位组: TUP_SP_EumOctetIndicator ////////////////////////////////////
// 信令: EUM
typedef struct
{
	DJ_U8 m_u8UnsuccessfulIndicator; // 不成功表示语
	DJ_U8 m_u8Reserved[3]; // 备用
}TUP_spEumOctetIndicator, *PTUP_spEumOctetIndicator;


// EUM消息信令点: TUP_SP_EumSignallingPointCode ///////////////////////////////
// 信令: EUM
typedef struct
{
	DJ_U32 m_u32SPC; // 信令点编码
}TUP_spEumSignallingPointCode, *PTUP_spEumSignallingPointCode;


// 前向呼叫信息: TUP_SP_ForwardCallInformation ////////////////////////////////
// 信令: IAM/IAI
typedef struct
{
	DJ_U8 m_u8InternationalCallIndicator; // 国际来话呼叫表示语
	
	DJ_U8 m_u8RedirectedCallIndicator; // 改发呼叫表示语
	DJ_U8 m_u8AllDigitalPathRequiredIndicator; // 需要全部是数字通路表示语
	DJ_U8 m_u8SignallingPathIndicator; // 信号通道表示语
}TUP_spForwardCallInformation, *PTUP_spForwardCallInformation;


// GRQ请求指示码: TUP_SP_GrqRequestTypeIndicator //////////////////////////////
// 信令: GRQ
typedef struct
{
	DJ_U8 m_u8CallingPartyCategoryRequestIndicator; // 主叫用户类别请求表示语
	DJ_U8 m_u8CallingLineIdentityRequestIndicator; // 主叫用户线标识请求表示语
	DJ_U8 m_u8OriginalCalledAddressRequestIndicator; // 原被叫地址请求表示语
	DJ_U8 m_u8MaliciousCallIdentificationIndicator; // 恶意呼叫识别请求表示语
	DJ_U8 m_u8HoldRequestIndicator; // 保持请求表示语
	DJ_U8 m_u8EchoSuppressorRequestIndicator; // 回声抑制器请求表示语
	DJ_U8 m_u8Reserved[2]; // 备用
}TUP_spGrqRequestTypeIndicator, *PTUP_spGrqRequestTypeIndicator;


// GSM响应指示码: TUP_SP_GsmResponseTypeIndicator /////////////////////////////
// 信令: GSM
typedef struct
{
	DJ_U8 m_u8CallingPartyCategoryIndicator; // 主叫用户类别表示语
	DJ_U8 m_u8CallingLineIdentityIndicator; // 主叫用户线标识表示语
	DJ_U8 m_u8IdentityIndicator; // 来话中继和转接交换局标识
	DJ_U8 m_u8OriginalCalledAddressIndicator; // 原被叫地址表示语
	DJ_U8 m_u8OutgoingEchoSuppressorIndicator; // 去话回声抑制器表示语
	DJ_U8 m_u8MaliciousCallIdentificationIndicator; // 恶意呼叫识别表示语
	DJ_U8 m_u8HoldIndicator; // 保持表示语
	DJ_U8 m_u8Reserved; // 备用
}TUP_spGsmResponseTypeIndicator, *PTUP_spGsmResponseTypeIndicator;


// IAI第一表示语: TUP_SP_IaiFirstIndicator ////////////////////////////////////
// 信令: IAI
typedef struct
{
	DJ_U8 m_u8FacilityInformationIndicator; // 网络能力或用户性能信息表示语
	DJ_U8 m_u8CUGInformationIndicator; // 闭合用户群信息表示语
	DJ_U8 m_u8AdditionalCallingPartyIndicator; // 附加主叫用户信息表示语
	DJ_U8 m_u8AdditionalRoutingIndicator; // 附加路由信息表示语
	DJ_U8 m_u8CallingLineIdentityIndicator; // 主叫用户线标识表示语
	DJ_U8 m_u8OriginalCalledAddressIndicator; // 原被叫地址表示语
	DJ_U8 m_u8ChargingInformationIndicator; // 计费信息表示语
	DJ_U8 m_u8Reserved; // 备用
}TUP_spIaiFirstIndicator, *PTUP_spIaiFirstIndicator;


// 原被叫用户号码: TUP_SP_OriginalCalledAddress ///////////////////////////////
// 信令: IAI/GSM
typedef struct
{
	DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质表示语
	DJ_U8 m_u8NumberOfAddressSignal; // 地址信号的数量
	DJ_U8 m_u8Reserved[2]; // 备用
	
	DJ_S8 m_s8AddressSignal[40]; // 地址信号
}TUP_spOriginalCalledAddress, *PTUP_spOriginalCalledAddress;


// 范围与状态: TUP_SP_RangeStatus /////////////////////////////////////////////
// 信令: GRM消息组
typedef struct
{
	DJ_U8  m_u8Range; // 范围
	DJ_U8  m_u8Reserved[3]; // 备用
	
	DJ_U32 m_u32Status;    // 状态
}TUP_spRangeStatus, *PTUP_spRangeStatus;


// 后续地址: TUP_SP_SubsequentAddress /////////////////////////////////////////
// 信令: SAM/SAO
typedef struct
{
	DJ_S8 m_s8AddressSignal[40]; // 地址信号
}TUP_spSubsequentAddress, *PTUP_spSubsequentAddress;


#endif
