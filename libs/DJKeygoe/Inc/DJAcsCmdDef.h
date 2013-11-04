#ifndef _DJACSCMDDEF_H
#define _DJACSCMDDEF_H

#include "ITPDataDefine.h"
#include "DJAcsDataDef.h"

enum ACS_CMD_TYPE
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
	ACS_CMD_TYPE_SETMASTER,
	ACS_CMD_TYPE_QUERYLIC,
	ACS_CMD_TYPE_CTXREG,
	ACS_CMD_TYPE_CTXLINK,
	ACS_CMD_TYPE_CTXSENDAPPDATA,
	ACS_CMD_TYPE_INIT3GPPINDEX,
	ACS_CMD_TYPE_BUILD3GPPINDEX,
	ACS_CMD_TYPE_SENDRAWFRAME,
	ACS_CMD_TYPE_JOIN3GCONF,
	ACS_CMD_TYPE_LEAVE3GCONF,
	ACS_CMD_TYPE_CLEAR3GCONF,
	ACS_CMD_TYPE_GET3GCONFLAYOUT,
	ACS_CMD_TYPE_SET3GCONFLAYOUT,
	ACS_CMD_TYPE_GET3GCONFVISABLE,
	ACS_CMD_TYPE_SET3GCONFVISABLE,
	ACS_CMD_TYPE_RESTART3GCONF,
};

enum CTX_APPDATA_RET
{
	CTX_APPDATA_RET_SUCCESS		= 0x0,
	CTX_APPDATA_RET_NODEST		= 0x4,
	CTX_APPDATA_RET_NOSRC  		= 0x5,
	CTX_APPDATA_DEST_RECVOK     = 0xFF,
};
/*Acs_Cmd_t*/
typedef struct
{	
	ACSHandle_t      m_s32AcsHandle;    /*acs handle*/	
	DeviceID_t       m_ITPDeviceID;      /*Device id*/
	AcsCmdTye_t      m_s32CmdType;      /*command type*/
	ParmName_t       m_s8PackName[64];  /*parmeter name*/
	ParmSize_t       m_s32PackSize;     /*parmeter size*/
	DJ_U8            m_u8AcsId;         /*acs server use*/
	DJ_S8            m_Rfu1[3];
}Acs_Cmd_t;/*Acs_Cmd_t*/

/*ACS Cmd Head*/
typedef struct
{
	PKG_HEAD_STRUCT  m_ITPPkgCmdHead;   /*ITP package head*/	
	Acs_Cmd_t        m_ITPAcsCmd_t;     /*acs command package head*/
}ACS_CMD_HEAD;/**/

/*ACS set Master parm*/
typedef struct
{
	DJ_U8    m_u8Master;
	DJ_U8    m_u8AppUnitID;
	DJ_S8    m_Rfu1[2];
}SetMasterParm_t;/**/

/*ACS open device parm*/
typedef struct
{
	DJ_S32      m_s32Resrv;/*Reserved*/
}OpenDevParm_t;/**/

/*ACS close device parm*/
typedef struct
{
	DJ_S32      m_s32Resrv;/*Reserved*/
}CloseDevParm_t;/**/

typedef struct
{
	DJ_S32      m_s32Resrv;/*Reserved*/
}ResetDevParm_t;/**/

typedef struct
{
	DJ_S32      m_s32Resrv;/*Reserved*/
}GetDevStateParm_t;/**/

/*ACS set device group parm*/
typedef struct
{
	DJ_S32      m_s32Resrv;/*Reserved*/
}SetDevGroupParm_t;/**/

/*ACS callout parm*/
typedef struct
{	
	CallNum_t       m_s8CallingNum[ACS_MAX_CALL_NUM];/*calling id*/
	CallNum_t       m_s8CalledNum[ACS_MAX_CALL_NUM];/*called id*/
}CalloutParm_t;/**/

typedef struct
{	
	DJ_U16              m_u16ParamCmdType;
	DJ_U16              m_u16ParamDataSize;
}SetParm_t;/**/

typedef struct
{
	DJ_U16              m_u16ParamCmdType;
	DJ_U16              m_u16ParamDataSize;
}GetParm_t;/**/

/*ACS callin parm*/
typedef struct
{
	DJ_S32        m_s32Resrv;/*Reserved*/
}AlertCallParm_t;/**/

/*ACS callin parm*/
typedef struct
{
	DJ_S32        m_s32Resrv;/*Reserved*/
}AnswerCallInParm_t;/**/

/*ACS Link Device parm*/
typedef struct
{
	DeviceID_t        m_ITPDestDeviceID;/*Device id*/
}LinkDevParm_t;/**/

/*ACS UnLink parm*/
typedef struct
{
	DeviceID_t        m_ITPDestDeviceID;/*Device id*/
}UnlinkDevParm_t;/**/

/*ACS XMS Reg parm*/
typedef struct
{
	DJ_S8   m_s8RegName[XMS_MAX_REGNAME_LEN];/*Reg Name*/	
	DJ_U8   m_u8RegType;  /*1:Reg; 2: unReg,reference XMS_CTX_REG_TYPE*/
	DJ_U8   m_u8AcsUnitID;
	DJ_S8   m_Rfu1[2];
	DJ_S32  m_s32Rst;
}XMSCtxRegParm_t;

/*ACS XMS ctxlink parm*/
typedef struct
{
	DJ_U8	      m_u8CtxLinkOpt;/*link option,reference CTX_LINK_OPTION*/
	DJ_U8         m_u8AcsUnitID;
	DJ_S8         m_Rfu1[2];
	DeviceID_t    m_srcDev;
	DeviceID_t    m_destDev;
	DJ_S32        m_s32Rst;
}XMSCtxLinkParm_t;

/*ACS App Data Info*/
typedef struct
{
	DJ_U32      m_u32AppDataSize; /*user APP data size,not include XMS_AppData_Info_t*/
	DJ_U8       m_u8AppReqType;   /*user APP req cmd type,user self define*/
	DJ_U8       m_u8AcsUnitID;
	DJ_U8       m_Rfu1[2];      
	DJ_S8       m_s8SrcRegName[XMS_MAX_REGNAME_LEN]; /*src reg name*/
	DJ_S8       m_s8DestRegName[XMS_MAX_REGNAME_LEN];/*dest reg name*/
	DJ_U8       m_u8SrcAppUnitID;
	DJ_U8       m_u8DstAppUnitID;
	DJ_S8       m_Rfu2[2];
	DeviceID_t  m_srcDevice;
	DJ_S8       m_Rfu3[20];
	DJ_S32      m_s32Rst;
}XMS_AppData_Info_t;/**/

/*ACS clearcall parm*/
typedef struct
{
	DJ_S32        m_s32ClearCause;/*Reserved*/
	DJ_S32        m_s32Resrv;/*Reserved*/
}ClearCallParm_t;/**/

/*ACS Jointo conf parm*/
typedef struct
{
	DeviceID_t           m_ITPMediaDevice;/*media device*/
    CmdParamData_Conf_t  m_ITPConfParam;  /*Conf param*/ 
}JoinToConfParm_t;/**/

/*ACS Leave conf parm*/
typedef struct
{
	DeviceID_t           m_ITPMediaDevice;/*media device*/    
	CmdParamData_Conf_t  m_ITPConfParam;  /*Conf param*/ 
}LeaveFromConfParm_t;/**/

typedef struct
{
    DJ_S32       m_s32Resrv;/*Reserved*/
}ClearConfParm_t;/*Clear conf param*/

/*ACS play parm*/
typedef struct
{    	
	PlayProperty_t       m_PlayProperty;   /*playProperty*/	
}PlayParm_t;/**/

typedef struct
{
	DJ_S32               m_s32Reserved;     /**/
}InitPlayIndexParm_t;/**/

typedef struct
{	
	PlayProperty_t   m_ITPPlayProperty;/**/
}BuildPlayIndexParm_t;/**/

/*ACS control play parm*/
typedef struct
{
	ControlPlay_t  m_ITPControlPlay; /*control play parmeter*/
}ControlPlayParm_t;/**/

/*ACS record parm*/
typedef struct
{	
	RecordProperty_t    m_ITPRecordProperty;/*record property set*/
}RecordParm_t;/**/

/*ACS control record parm*/
typedef struct
{
	ControlRecord_t  m_ITPControlRecord;/*control record set*/
}ControlRecordParm_t;/**/

/*ACS record Ram parm*/
typedef struct
{	
	RecordCSPProperty_t    m_ITPRecordCSPProperty;/*record CSP property set*/
}RecordCSPParm_t;/**/

#define		ITP_MAX_STREAM_DATA_LENGTH		4000

/*ACS CSPPlayParm_t*/
typedef struct
{	
	CSPPlayProperty_t            m_ITPCSPPlayProperty;     /*ITP csp play property*/
}CSPPlayParm_t;/**/

/*CSPPlayData*/
typedef struct
{
	PKG_HEAD_STRUCT        m_ITPPkgCmdHead;      /*ITP package head*/
	CSPPlayDataInfo_t      m_CspPlayDataInfo;    /*csp play data info*/
	DJ_U8                  m_u8StreamData[ITP_MAX_STREAM_DATA_LENGTH ];	/*stream data*/
}CSPPlaySendDataParm_t;/**/

/*ACS monitor filter parm*/
typedef struct
{
	DJ_U32                m_u32MonitorFilter;/*event monitor filter,reference ACS_IOEVT_MASK*/
}MonitorFilterParm_t;/**/

/*ACS send io parm*/
typedef struct
{	
    DJ_U16         m_u16IoType;     /*io proc type*/
	DJ_U16         m_u16IoDataLen;  /*io data len*/  
}SendIOParm_t;/*IO data pack*/

/*ACS send Signal Msg Type*/
typedef struct
{	
    DJ_U16         m_u16SigMsgType;     /*Signal Msg Type*/
	DJ_S8          m_s8Rfu[2];          /*Rfu*/  
}SendSigMsgParm_t;/**/
/*fax_shakehand_param*/
typedef struct
{
	DJ_U8   m_u8Handshake_Result;   /*T30 handshake result*/
	DJ_U8	m_u8Local_ID[20];
	DJ_U8	m_u8Remote_ID[20];
	DJ_U8	m_u8Modem_Type;		/*F144_MODEM,F96_MODEM,F48_MODEM*/
	DJ_U8	m_u8Fax_Speed;          /*2400,4800,7200,9600,12000,14400*/
	DJ_U8	m_u8Dencity;		/*T4_LOW_DENSITY or T4_HIGH_DENSITY*/
	DJ_U8	m_u8Encode_Type;   /*T4_MH_ENCODE or T4_MR_ENCODE or T6_ENCODE*/
	DJ_U8	m_u8Line_Width;		
	DJ_U8	m_u8Min_Scanline_Time; 	/*minimum scanline time in ms, 0 for no limit*/
	DJ_U8	m_u8Page_Length;		
	DJ_U8	m_u8Ecm_Support;	/*ECM_SUPPORT or ECM_UNSUPPORT*/
	DJ_U8   m_u8Host_Control;  //host command
	DJ_U8   m_u8Reserve[6];
	DJ_U32  m_u32Total_Page_Num;  //total sending page num, set by Ap when sending fax

}FaxHandShake_t;/*FaxHandShake_t*/

/*faxReceivePageParam*/
typedef struct 
{
	DJ_U32	  m_u32PageNo;       //当前页的页号，从1开始
	DJ_U32	  m_u32ByteCount;    //当前页的总字节数	
	DJ_U8	  m_u8YResolution;	 //垂直分辨率，低分辨率0， 高分辨率1
	DJ_U8	  m_u8EncodeType;    //MH 0， MR 1， MMR 2
	DJ_U8	  m_u8PageWidth;	 //页宽0代表1728
	DJ_U8	  m_u8MinScanlineTime;  //最小行扫描时间
	DJ_U32    m_u32PageOffset;     //页数据偏移量
	DJ_U32    m_u32FillOrder;      //字节的bit位顺序
	DJ_U32    m_u32XResolution;    //水平分辨率      
	DJ_U32    m_u32Reserve[10];    //保留

}FaxPageAttri_t;/*FaxRecvPage_t*/


typedef struct
{
	DJ_U8	m_u8Modem_Type;		
	DJ_U8	m_u8Fax_Speed;          
	DJ_U8	m_u8Dencity;		
	DJ_U8	m_u8Encode_Type;  
	DJ_U8	m_u8Line_Width;		
	DJ_U8	m_u8Min_Scanline_Time; 	
	DJ_U8	m_u8Page_Length;		
	DJ_U8	m_u8Ecm_Support;	
	DJ_U8	m_u8Remote_ID[20]; 
}FaxLocalSpec_t;/*FaxLocalSpec_t*/

typedef struct
{
	DJ_U16  m_u16Fax_Channel_ID;    //Fax Chan
	DJ_U16  m_u16Fax_End_Flag;      //Fax end flag
	DJ_U8	m_u8Last_Error_Code;	//error code of last fax operation
	DJ_U8	m_u8Last_Error_State;	//error state of last fax operation
	DJ_U8	m_u8Last_Send_T30_Command_State;//store the state the T30 command just sent
	DJ_U8	m_u8Last_Rcv_T30_Command;	//store the T30 command just received
	DJ_U16	m_u16Total_Page_Num;		//total pages,send: sending total pages successfully  ;rev: receiving total pages successfully
    DJ_U8	m_u8Remote_Id[20];
}FaxEndingParam_t;/*FaxEndingParam_t*/

typedef struct
{
	DJ_U8	m_u8Modem_Type;		//F144_MODEM,F96_MODEM,F48_MODEM
	DJ_U8	m_u8Fax_Speed;		//BPS_14400,BPS_12000,BPS_9600,BPS_7200,BPS_4800,BPS_2400
	DJ_U8	m_u8Dencity;		//T4_LOW_DENSITY or T4_HIGH_DENSITY
	DJ_U8	m_u8Encode_Type;	//T4_MH_ENCODE or T4_MR_ENCODE or T6_ENCODE
	DJ_U8	m_u8Line_Width;		//see line width list
	DJ_U8	m_u8Min_Scanline_Time; 	//minimum scanline time in ms, 0 for no limit
	DJ_U8	m_u8Page_Length;		//
	DJ_U8	m_u8Ecm_Support;	//ECM_SUPPORT or ECM_UNSUPPORT
}FaxRemoteSepc_t;/*FaxRemoteSepc_t*/

/*Fax_Page_t*/
typedef struct
{
	DJ_U16	 m_u16Total_Page_Num;        //总共需要发送的页数
	DJ_U16	 m_u16Send_EOM_Flag;        //页后控制
	DJ_U32	 m_u32Current_Page_Offset;  //页偏移    
	DJ_U32	 m_u32Current_Page_Bytes;	     //当前页的字节数
}Fax_Page_t;/*Fax_Page_t*/

/*SendFaxParm_t*/
typedef struct
{
	DJ_S8   	   m_s8LocalID[ACS_LOCALID_MAX_LEN]; /*Local ID*/	
	DJ_S8          m_s8FaxTiffFile[MAX_PATH];        /*fax tiff file*/
	DeviceID_t     m_ITPMediaDeviceID;               /*Media deviceID*/	
}SendFaxParm_t;/**/

/*StopSendFaxParm_t*/
typedef struct
{	
	DJ_S8          m_s8Rfu1[4]; /*Reserved*/	
}StopSendFaxParm_t;/**/

/*RecvFaxParm_t*/
typedef struct
{
	DJ_S8   	   m_s8LocalID[ACS_LOCALID_MAX_LEN]; /*fax Local ID*/	
	DJ_S8          m_s8FaxTiffFile[MAX_PATH];        /*fax tiff file*/
	DeviceID_t     m_ITPMediaDeviceID;               /*media deviceID*/
}RecvFaxParm_t;/**/

/*StopRecvFaxParm_t*/
typedef struct
{	
	DJ_S8          m_s8Rfu1[4]; /*Reserved*/	
}StopRecvFaxParm_t;/**/

/*ACS 3gpp play parm*/
typedef struct
{
	DJ_S32               m_s32Reserved;     /**/
}InitPlay3gppIndexParm_t;/**/

typedef struct
{	
	Play3gppProperty_t   m_ITPPlayProperty;/**/
}BuildPlay3gppIndexParm_t;/**/

/*ACS 3gpp play parm*/
typedef struct
{    	
	Play3gppProperty_t       m_PlayProperty;   /*Play3gppProperty_t*/	
}Play3gppParm_t;/**/

/*ACS control play parm*/
typedef struct
{
	Control3gppPlay_t  m_ITPControlPlay; /*control play parmeter*/
}Control3gppPlayParm_t;/**/

/*ACS record parm*/
typedef struct
{	
	Record3gppProperty_t    m_ITPRecordProperty;/*record property set*/
}Record3gppParm_t;/**/

/*ACS control record parm*/
typedef struct
{
	Control3gppRecord_t  m_ITPControlRecord;/*control record set*/
}Control3gppRecordParm_t;/**/

/*ACS Query License parm*/
typedef struct
{
	DJ_U8     m_u8ModuleID; /*Board module ID*/
	DJ_S8     m_Rfu1[3];    /*Rfu*/
}QueryLicenseParm_t;/**/

/*SendRawFrameParm_t*/
typedef struct
{		
	DJ_U16              m_u16FrameSize;
	DJ_U16              m_Rfu1;
}SendRawFrameParm_t;/**/

/*JoinTo3GVConfParm_t*/
typedef struct
{	
	DeviceID_t               m_device;
	Acs_MediaEx_Input_V      m_input;
	Acs_MediaEx_Output_V     m_output;
	DJ_U8                    m_u8Visible;
}JoinTo3GVConfParm_t;/**/

/*LeaveFrom3GVConfParm_t*/
typedef struct
{	
	DeviceID_t               m_device;
}LeaveFrom3GVConfParm_t;/**/

/*Clear3GVConfParm_t*/
typedef struct
{
	DJ_S32               m_s32Reserved;     /**/
}Clear3GVConfParm_t;/**/

/*GetLayoutParm_t*/
typedef struct
{	
	DJ_S32               m_s32Reserved;     /**/
}GetLayoutParm_t;/**/

/*SetLayoutParm_t*/
typedef struct
{	
	Acs_3GVConf_LayoutList m_list;
}SetLayoutParm_t;/**/

/*GetVisibleListParm_t*/
typedef struct
{	
	DJ_S32               m_s32Reserved;     /**/
}GetVisibleListParm_t;/**/

/*SetVisibleListParm_t*/
typedef struct
{	
	Acs_3GVConf_VisibleList m_list;
}SetVisibleListParm_t;/**/

/*Restart3GVConfParm_t*/
typedef struct
{	
	DJ_S32               m_s32Reserved;     /**/
}Restart3GVConfParm_t;/**/

/*Syn_OpenDev*/
typedef struct
{
	DeviceID_t    m_ITPDevice;
}QueryDevLinkParm_t;

/*Syn_OpenDev*/
typedef struct
{
	Acs_Cmd_t     m_AcsCmd;
	DeviceID_t    m_TrunkDev;
	DeviceID_t    m_CtxDev;
}Syn_OpenDev;/*Syn_OpenDev*/

/*SS7_Syn_CallIn*/
typedef struct
{
	DJ_S8     m_s8Caller[32];
	DJ_S8     m_s8Called[32];
	DJ_S32    m_s32CallingPartCategory;
	DJ_S32    m_s32NatureOfCallerAddress;
	DJ_S32    m_s32NatureOfCalledAddress;
	DJ_S32    m_s32iAnswerType;
	DJ_S32    m_s32iCallOUTorIN;
}SS7_Syn_CallIn;/*SS7_Syn_CallIn*/

/*SS7_Syn_CallOut*/
typedef struct
{		
	DJ_S32    m_s32iCallOutResult;
	DJ_S32    m_s32iCallOUTorIN;
}SS7_Syn_CallOut;/*SS7_Syn_CallOut*/

/*Acs_cmd*/
typedef struct
{
	ACS_CMD_HEAD     m_ITPAcsCmdHead;/*acs cmd head*/	
	union
	{
		OpenDevParm_t          m_ITPAcsOpenDevParm;       /*open devcie parm*/
		CloseDevParm_t         m_ITPAcsCloseDevParm;      /*Close device parm*/
		ResetDevParm_t         m_ITPAcsResetDevParm;      /*Reset device parm*/
		GetDevStateParm_t      m_ITPAcsGetDevStateParm;   /*Get device state parm*/
		SetDevGroupParm_t      m_ITPAcsSetDevGrpParm;     /*set device group parm*/
		CalloutParm_t          m_ITPAcsCallOutParm;       /*callout parm*/		
		SetParm_t              m_ITPAcsSetParm;           /*set parm*/
		GetParm_t              m_ITPAcsGetParm;           /*get parm*/
		AnswerCallInParm_t     m_ITPAcsAnSwerCallInParm;  /*answer callin parm*/
		LinkDevParm_t          m_ITPAcsLinkDevParm;       /*Link device parm*/
		UnlinkDevParm_t        m_ITPAcsUnlinkDevParm;     /*Unlink device parm*/		
		ClearCallParm_t        m_ITPAcsClearCallParm;     /*clear call parm*/		
		JoinToConfParm_t       m_ITPAcsJoinToConfParm;    /*join to conf parm*/
		LeaveFromConfParm_t    m_ITPAcsLeaveConfParm;     /*Leave from conf parm*/
		PlayParm_t             m_ITPAcsPlayParm;          /*play file parm*/
		InitPlayIndexParm_t    m_ITPAcsInitPlayIndex;     /*Init play index*/
		BuildPlayIndexParm_t   m_ITPAcsBuildPlayIndex;    /*Build play idnex*/
		ControlPlayParm_t      m_ITPAcsCtrlPlayParm;      /*control play parm*/
		RecordParm_t           m_ITPAcsRecordParm;        /*record file parm*/
		ControlRecordParm_t    m_ITPAcsCtrlRecordParm;    /*control record parm*/			
		SendFaxParm_t          m_ITPAcsSendFaxParm;       /*send  fax parm*/
		StopSendFaxParm_t      m_ITPAcsStopSendFaxParm;   /*stop send fax parm*/
		SendFaxParm_t          m_ITPAcsRecvFaxParm;       /* recv fax parm*/
		StopRecvFaxParm_t      m_ITPAcsStopRecvFaxParm;   /*stop recv fax parm*/
		MonitorFilterParm_t    m_ITPAcsMonFilterParm;     /*monitor filter parm*/
		SendIOParm_t           m_ITPAcsSendIoParm;        /*send io parm*/     
		Play3gppParm_t             m_ITPAcsPlay3gpParm;          /*play 3gp file parm*/
		Control3gppPlayParm_t      m_ITPAcsCtrl3gpPlayParm;      /*control 3gp play parm*/
		Record3gppParm_t           m_ITPAcsRecord3gpParm;        /*record 3gp file parm*/
		Control3gppRecordParm_t    m_ITPAcsCtrl3gpRecordParm;    /*control 3gp record parm*/			
	};/*acs cmd parm*/
	PrivateData_t    m_ITPPrivateData;/*private data*/
}Acs_Cmd;/**/

typedef struct
{
	DJ_S16      m_s16DeviceSub;
	DJ_S16      m_s16StartTs;
	DJ_S16      m_s16DeviceNum;
	DJ_S16      m_Rfu1;
}Acs_DevSub_Info,*PAcs_DevSub_Info;

typedef struct
{
	DJ_S8             m_s8MachID;
	DJ_S8             m_s8ModuleID;	
	DJ_S16            m_s16DeviceMain;
	DJ_S16            m_s16DevSubNum;	
	DJ_S16            m_Rfu1;
	Acs_DevSub_Info   m_DevSub[128];
}Acs_Dev_Info,*PAcs_Dev_Info;

#endif
