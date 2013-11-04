#ifndef _DJITPAPIDLL_H
#define _DJITPAPIDLL_H

#include "ITPCom.h"
#include "DJAcsDataDef.h"

#ifndef WIN32
#define WINAPI
#endif

#ifdef __cplusplus
extern "C" 
{
#endif

#ifndef WIN32
	RetCode_t  XMS_acsDllInit();

	RetCode_t  XMS_acsDllLUnInit(); 
#endif

	RetCode_t __stdcall XMS_acsOpenStream(ACSHandle_t * acsHandle,ServerID_t *serverID,DJ_U8 u8AppID,
										DJ_U32 u32SendQSize,DJ_U32 u32RecvQSize,DJ_S32 s32DebugOn,PrivateData_t * privateData);
	
	RetCode_t __stdcall XMS_acsCloseStream(ACSHandle_t acsHandle,PrivateData_t * privateData);
			
	RetCode_t __stdcall XMS_acsSetMaster(ACSHandle_t acsHandle,DJ_U8 u8Master,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_acsSetESR(ACSHandle_t acsHandle,EsrFunc esr,DJ_U32 esrParam,int notifyAll);	
		
	RetCode_t __stdcall XMS_acsGetDeviceList(ACSHandle_t acsHandle,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_acsSetTimer(ACSHandle_t acsHandle,DJ_U32 u32Elapse);

	RetCode_t __stdcall XMS_ctsOpenDevice(ACSHandle_t acsHandle,DeviceID_t * deviceID,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctsCloseDevice(ACSHandle_t acsHandle,DeviceID_t * deviceID,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctsResetDevice(ACSHandle_t acsHandle,DeviceID_t * deviceID,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctsSetDevTimer(ACSHandle_t acsHandle,DeviceID_t * deviceID,DJ_U32 u32Elapse);
	
	RetCode_t __stdcall XMS_ctsGetDevState(ACSHandle_t acsHandle,DeviceID_t * deviceID,PrivateData_t * privateData);
			
	RetCode_t __stdcall XMS_ctsSetDevGroup(ACSHandle_t acsHandle,DeviceID_t * deviceID,PrivateData_t * privateData);	

	RetCode_t __stdcall XMS_ctsMakeCallOut(ACSHandle_t acsHandle,DeviceID_t * deviceID,CallNum_t * callingID,
										CallNum_t * calledID,PrivateData_t * privateData);
	
	RetCode_t __stdcall XMS_ctsSetParam(ACSHandle_t acsHandle,DeviceID_t * deviceID,DJ_U16 u16ParamCmdType,DJ_U16 u16ParamDataSize,DJ_Void * paramData);

	RetCode_t __stdcall XMS_ctsGetParam(ACSHandle_t acsHandle,DeviceID_t * deviceID,DJ_U16 u16ParamCmdType,DJ_U16 u16ParamDataSize,DJ_Void * paramData);
	
	RetCode_t __stdcall XMS_ctsAlertCall(ACSHandle_t acsHandle,DeviceID_t * deviceID,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctsAnswerCallIn(ACSHandle_t acsHandle,DeviceID_t * deviceID,PrivateData_t * privateData);
	
	RetCode_t __stdcall XMS_ctsLinkDevice(ACSHandle_t acsHandle,DeviceID_t * srcDeviceID,DeviceID_t * destDeviceID,PrivateData_t * privateData);
	
	RetCode_t __stdcall XMS_ctsUnlinkDevice(ACSHandle_t acsHandle,DeviceID_t * srcDeviceID,DeviceID_t * destDeviceID,PrivateData_t * privateData);
		
	RetCode_t __stdcall XMS_ctsClearCall(ACSHandle_t acsHandle, DeviceID_t * deviceID,DJ_S32 s32ClearCause,PrivateData_t * privateData);
	
	RetCode_t __stdcall  XMS_ctsJoinToConf(ACSHandle_t acsHandle,DeviceID_t * confDeviceID,DeviceID_t * mediaDeviceID, CmdParamData_Conf_t * confParam, PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctsLeaveFromConf(ACSHandle_t acsHandle,DeviceID_t * confDeviceID,DeviceID_t * mediaDeviceID,CmdParamData_Conf_t * confParam,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctsClearConf(ACSHandle_t acsHandle,DeviceID_t * confDeviceID,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctsPlay(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,
								PlayProperty_t * playProperty,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctsInitPlayIndex(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctsBuildPlayIndex(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,PlayProperty_t * playProperty,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctsControlPlay(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,
								ControlPlay_t * controlPlay,PrivateData_t * privateData);
	
	RetCode_t __stdcall XMS_ctsRecord(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,
								RecordProperty_t * recordProperty,PrivateData_t * privateData);
	
	RetCode_t __stdcall XMS_ctsControlRecord(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,
								ControlRecord_t * controlRecord,PrivateData_t * privateData);
	
	RetCode_t __stdcall XMS_ctsSendFax(ACSHandle_t acsHandle,DeviceID_t * faxDeviceID,DeviceID_t * mediaDeviceID,
							    DJ_S8 * s8TiffFile,DJ_S8 * s8LocalID,PrivateData_t * privateData);
	
	RetCode_t __stdcall XMS_ctsStopSendFax(ACSHandle_t acsHandle,DeviceID_t * faxDeviceID,PrivateData_t * privateData);
	
	RetCode_t __stdcall XMS_ctsReceiveFax(ACSHandle_t acsHandle,DeviceID_t * faxDeviceID,DeviceID_t * mediaDeviceID,
							    DJ_S8 * s8TiffFile,DJ_S8 * s8LocalID,PrivateData_t * privateData);
	
	RetCode_t __stdcall XMS_ctsStopReceiveFax(ACSHandle_t acsHandle,DeviceID_t * faxDeviceID,PrivateData_t * privateData);
	
	RetCode_t __stdcall XMS_ctsChangeMonitorFilter(ACSHandle_t acsHandle,DeviceID_t * deviceID,DJ_U32 monitorFilter,PrivateData_t * privateData);	

	RetCode_t __stdcall XMS_ctsSendIOData(ACSHandle_t acsHandle,DeviceID_t * deviceID,DJ_U16 u16IoType,DJ_U16 u16IoDataLen,DJ_Void * ioData);

	RetCode_t __stdcall XMS_ctsSendSignalMsg(ACSHandle_t acsHandle,DeviceID_t * deviceID,DJ_U16 u16SignalMsgType);

	RetCode_t __stdcall XMS_acsOpenStreamExt(ACSHandle_t acsHandle,ServerID_t *serverID,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_acsCloseStreamExt(ACSHandle_t acsHandle,ServerID_t *serverID,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctsPlayCSP(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,CSPPlayProperty_t *  cspPlayProperty,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctsSendCSPData(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,CSPPlayDataInfo_t *  cspDataInfo,DJ_Void * cspData,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctsControlPlayCSP(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,ControlPlay_t * controlPlay,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctsRecordCSP(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,
								RecordCSPProperty_t * recCSPProperty,PrivateData_t * privateData);
	
	RetCode_t __stdcall XMS_ctsControlRecordCSP(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,
								ControlRecord_t * controlRecord,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctsInitPlay3gppIndex(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctsBuildPlay3gppIndex(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,
										   Play3gppProperty_t * playProperty,PrivateData_t * privateData);

    RetCode_t __stdcall XMS_cts3gppPlay(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,
								Play3gppProperty_t * playProperty,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctsControl3gppPlay(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,
								Control3gppPlay_t * controlPlay,PrivateData_t * privateData);
	
	RetCode_t __stdcall XMS_cts3gppRecord(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,
								Record3gppProperty_t * recordProperty,PrivateData_t * privateData);
	
	RetCode_t __stdcall XMS_ctsControl3gppRecord(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,
								Control3gppRecord_t * controlRecord,PrivateData_t * privateData);
	RetCode_t __stdcall XMS_acsQueryLicense(ACSHandle_t acsHandle,DeviceID_t * deviceID,PrivateData_t * privateData);
	RetCode_t __stdcall XMS_ctxRegister(ACSHandle_t acsHandle,DJ_S8 * s8AppRegName,DJ_U8 u8RegType,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctxLink(ACSHandle_t acsHandle,DeviceID_t * srcDev,DeviceID_t * destDev,DJ_U8 u8Option,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctxSendAppData(ACSHandle_t acsHandle,DJ_S8 * s8SrcAppRegName,DJ_S8 * s8DestAppRegName,
									DJ_U8 u8AppReqType,DJ_Void * pData,DJ_U32 u32DataSize,
									DJ_U8 u8SrcAppUnitID,DJ_U8 u8DestAppUnitID,
									DeviceID_t * srcDevice,PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctsSendRawFrame(ACSHandle_t acsHandle,DeviceID_t * deviceID, DJ_U16 u16FrameSize,DJ_Void * pData);
	
	RetCode_t __stdcall XMS_ctsJoinTo3GVConf(ACSHandle_t acsHandle, DeviceID_t * device3GVConfID, 
						DeviceID_t * deviceID, Acs_MediaEx_Input_V* input, Acs_MediaEx_Output_V* output, 
						DJ_U8 u8Visible, PrivateData_t * privateData);
						
	RetCode_t __stdcall XMS_ctsLeaveFrom3GVConf(ACSHandle_t acsHandle, DeviceID_t * device3GVConfID, DeviceID_t * deviceID, PrivateData_t * privateData);
	
	RetCode_t __stdcall XMS_ctsClear3GVConf(ACSHandle_t acsHandle, DeviceID_t * device3GVConfID, PrivateData_t * privateData);
	
	RetCode_t __stdcall XMS_ctsGetLayout(ACSHandle_t acsHandle, DeviceID_t * device3GVConfID, PrivateData_t * privateData);
	
	RetCode_t __stdcall XMS_ctsSetLayout(ACSHandle_t acsHandle, DeviceID_t * device3GVConfID, Acs_3GVConf_LayoutList * layoutList, PrivateData_t * privateData);
	
	RetCode_t __stdcall XMS_ctsGetVisibleList(ACSHandle_t acsHandle, DeviceID_t * device3GVConfID, PrivateData_t * privateData);
	
	RetCode_t __stdcall XMS_ctsSetVisibleList(ACSHandle_t acsHandle, DeviceID_t * device3GVConfID, Acs_3GVConf_VisibleList * visableList, PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctsPutTextInPicture(ACSHandle_t acsHandle, DJ_S8 *s8DstFile, PutTextInPicture_Param *paramItem, DJ_U32 u32ParamSum, PrivateData_t * privateData);

	RetCode_t __stdcall XMS_ctsRestart3GVConf(ACSHandle_t acsHandle, DeviceID_t * device3GVConfID, PrivateData_t * privateData);

	RetCode_t __stdcall XMS_acsGetRelateMod(ACSHandle_t acsHandle,DJ_U8 u8ModType,DJ_U8 u8UnitID);
	
	RetCode_t __stdcall XMS_ctsPutUsrEvt(ACSHandle_t acsHandle,DeviceID_t * deviceID, UserEvt_Head_t * pUserEvt);

	RetCode_t __stdcall XMS_acsLedCtrl(ACSHandle_t acsHandle, DJ_U8 u8DspUnitID, UserLedCtrl * pLedCtrl);
			
#ifdef __cplusplus
}
#endif

#endif