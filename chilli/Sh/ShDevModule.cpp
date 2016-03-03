#include "ShDevModule.h"
#include "ShExtension.h"
#include <common/xmlHelper.h>
#include <log4cplus/loggingmacros.h>
#include <thread>

namespace chilli{
namespace ShDev{


static std::string GetSsmLastErrMsg()
{
	char Err[600];
	SsmGetLastErrMsg(Err); //Get error message
	return Err;
}

ShDevModule::ShDevModule(void):DevModule()
{
	log =log4cplus::Logger::getInstance("chilli.ShDevModule");
	LOG4CPLUS_DEBUG(log,"new a ShDevModule object.");
}


ShDevModule::~ShDevModule(void)
{
	LOG4CPLUS_DEBUG(log,"destruction a ShDevModule object.");
}

bool ShDevModule::Init()
{

	//load configuration file and initialize system
	if (SsmStartCti("ShConfig.ini", "ShIndex.ini") == -1)
	{
		LOG4CPLUS_ERROR(log, GetSsmLastErrMsg());
		return false;
	}


	int nTotCh = SsmGetMaxCh();
	LOG4CPLUS_INFO(log, "MaxCh:" << nTotCh);
	for (int i = 0; i < nTotCh; i++)
	{
		//chilli::ShDev::ShExtensionPtr extPtr = new ShExtension();
		//extPtr->setEnable(false);
		//extPtr->setType(SsmGetChType(i));
		//extPtr->setChannelID(i);
		//m_ExtensionVector.push_back(extPtr);
	}


	return true;
}

int ShDevModule::Start()
{
	if (!Init())
		return -1;

	EVENT_SET_INFO EventMode;
	EventMode.dwWorkMode = EVENT_CALLBACKA;
	EventMode.lpHandlerParam = EvtHandler;

	if (SsmSetEvent(0xffff, -1, true, &EventMode) != 0)
	{
		LOG4CPLUS_ERROR(log, "set CallBack fuction failed. " << GetSsmLastErrMsg());
	}


	//td.thread_hnd = (HANDLE)_beginthreadex(NULL,0,ThreadProc,NULL,0,&td.thread_id);

	return 0;
}

int ShDevModule::Stop()
{
	LOG4CPLUS_DEBUG(log,"Close a Sanhuid device");
	if(SsmCloseCti() == -1)									 
	{
		LOG4CPLUS_ERROR(log, GetSsmLastErrMsg());
	}
	return 0;
}


std::vector<chilli::model::ExtensionPtr> ShDevModule::GetExtension()
{
	return std::vector <chilli::model::ExtensionPtr>();
}

int ShDevModule::getDeviceTypeByName(const std::string & strChType)
{
	if (strChType == "Analog_Trunk") return Analog_Trunk;
	else if (strChType == "Anolog_User") return Anolog_User;
	else if (strChType == "Anolog_Record") return Anolog_Record;
	else if (strChType == "Anolog_MicroPhone") return Anolog_MicroPhone;
	else if (strChType == "Anolog_Nothing") return Anolog_Nothing;
	else if (strChType == "ISDN_User") return ISDN_User;
	else if (strChType == "ISND_Trunk") return ISND_Trunk;
	else return -1;
}

int ShDevModule::EvtHandler(const PSSM_EVENT const pEvent)
{
	static log4cplus::Logger log = log4cplus::Logger::getInstance("chilli.ShDev.ShDevModule.EvtHandler");
	unsigned int evtCh = pEvent->nReference;
	/*if (evtCh < m_ExtensionVector.size())
	{
	model::ExtensionPtr extPtr = m_ExtensionVector.at(evtCh);
	recEvtBuffer.addData(TransferEvtToXmlEvent(pEvent,extPtr->getExtensionNumber()));
	}
	else
	{
	LOG4CPLUS_WARN(log,"recive one event,ch is Out of range. event ch=" << evtCh);
	}*/
	return 0;
}


bool ShDevModule::LoadConfig(const std::string & configFile)
{
	return false;
}
std::string ShDevModule::TransferEvtToXmlEvent(const PSSM_EVENT const pEvent, const std::string & extNum){
	
	static log4cplus::Logger log = log4cplus::Logger::getInstance("chilli.ShDev.ShDevModule.EvtHandler");

	helper::xml::CXmlDocmentHelper xmlHelper;
	std::stringstream ss;
	ss << pEvent->nReference;
	xmlHelper.setRootNode("event");
	xmlHelper.newRootProp("from",ss.str());
	xmlHelper.newRootProp("dest",extNum);
	xmlHelper.newRootProp("event",ShDevModule::GetString_EventType(pEvent->wEventCode));
	ss.str("");

	switch(pEvent->wEventCode)
	{
	case E_CHG_RcvDTMF:
		{
			std::stringstream ss;
			char dtmf =(pEvent->dwParam & 0x00FF);
			ss << dtmf;
			xmlHelper.addChild("data",ss.str());
		}
		break;

	case E_CHG_HookState:
		{
			std::stringstream ss;
			ss <<  (pEvent->dwParam); 
			xmlHelper.addChild("data",ss.str());
		}
		break;
	case E_CHG_RingCount:
		{
			std::stringstream ss;
			ss <<  (pEvent->dwParam); 
			xmlHelper.addChild("data",ss.str());
		}
		break;
	case E_CHG_ChState:
		{
			std::stringstream ss;
			ss <<  ShDevModule::GetString_State(pEvent->dwParam & 0xFFFF); 
			xmlHelper.addChild("data",ss.str());
			switch(pEvent->dwParam)
			{
			case S_CALL_RINGING:{
				char buf[256]={0};
				/*this->m_CallerId = SsmGetCallerIdA(this->Ch) == NULL ? "":SsmGetCallerIdA(this->Ch);
				this->m_CalleeId = SsmGetPhoNumStrA(this->Ch) == NULL ? "":SsmGetPhoNumStrA(this->Ch);*/
				SsmGetCallerId(pEvent->nReference,buf);
				xmlHelper.addChild("Caller",buf);
				SsmGetPhoNumStr(pEvent->nReference,buf);
				xmlHelper.addChild("Callee", buf);
				}
				break;
			case S_CALL_STANDBY:
				break; 
			case S_CALL_PENDING:
				xmlHelper.addChild("reason",ShDevModule::GetString_PengdingReason(SsmGetPendingReason(pEvent->nReference)));
				break;
			}
		}
		break;
	case E_PROC_PlayEnd:
		{
			std::stringstream ss;
			ss <<  (pEvent->dwParam); 
			xmlHelper.addChild("data",ss.str());
		}
		break;
	default:
		break;
	}
	
	LOG4CPLUS_TRACE(log,"ch=" << pEvent->nReference << ",Recive a event,event=" << xmlHelper.getContent());
	return xmlHelper.getContent();
}

const char * ShDevModule::GetString_EventType( int nEvent )
{
	switch ( nEvent )
	{
	case E_PROC_Recognize					:return "E_PROC_Recognize";//						//= 0x0000,	// voice recognition ends	
	case E_CHG_ISDNStatus					:return "E_CHG_ISDNStatus";//						= 0x0001,	// ISDN: ISDN LAPD layer changes
	case E_RCV_Ss7Msu						:return "E_RCV_Ss7Msu";//					= 0x0002,	// SS7: a new message (MSU) is received from the SS7 server
	case E_CHG_Mtp3State					:return "E_CHG_Mtp3State";//				= 0x0003,	// SS7: SS7 MTP3 layer changes, usually to indicate if some DPC route is usable or not
	case E_CHG_FaxChState					:return "E_CHG_FaxChState";//					= 0x0004,	// FAX channel: channel state changes
	case E_CHG_FaxPages						:return "E_CHG_FaxPages";//					= 0x0005,	// FAX channel: driver finishes receiving or transmitting a page of fax data
	case E_PROC_FaxEnd						:return "E_PROC_FaxEnd";//						= 0x0006,	// FAX channel: driver finishes receiving or transmitting all fax data
	case E_CHG_PcmLinkStatus				:return "E_CHG_PcmLinkStatus";//				= 0x0007,	// synchronization status of the digital trunk changes
	case E_CHG_LineVoltage					:return "E_CHG_LineVoltage";//				= 0x0008,	// voltage on the analog phone line changes
	case E_RCV_CAS							:return "E_RCV_CAS";//					= 0x0009,	// SS1 channel: ABCD signaling code from the remote PBX changes
	case E_RCV_R2							:return "E_RCV_R2";//					= 0x000a,	// SS1 channel: R2 signal from the remote PBX is received
	case E_PROC_WaitDTMF					:return "E_PROC_WaitDTMF";//					= 0x000b,	// the task of WaitDTMF is completed and submitted via the function SsmSetWaitDtmf, SsmSetWaitDtmfEx or SsmSetWaitDtmfExA
	case E_CHG_RcvDTMF						:return "E_CHG_RcvDTMF";//						= 0x000c,	// DTMF detector: a DTMF digit is received
	case E_PROC_SendDTMF					:return "E_PROC_SendDTMF";//					= 0x000d,	// DTMF generator: the task of transmitting DTMF started by the function SsmTxDtmf is completed
	case E_PROC_SendFlash					:return "E_PROC_SendFlash";//					= 0x000e,	// the task of sending the flash signal is completed
	case E_PROC_PlayEnd						:return "E_PROC_PlayEnd";//					= 0x000f,	// the task of playing voice ends
	case E_PROC_PlayFile					:return "E_PROC_PlayFile";//					= 0x0010,	// indicates the file playing progress
	case E_PROC_PlayFileList				:return "E_PROC_PlayFileList";//					= 0x0011,	// indicates driver has finished playing a file in the file queue
	case E_PROC_PlayMem						:return "E_PROC_PlayMem";//					= 0x0012,	// indicates the voice playing progress in Single Buffer Mode
	case E_PROC_RecordEnd					:return "E_PROC_RecordEnd";//					= 0x0013,	// task of recording voice terminates
	case E_PROC_RecordFile					:return "E_PROC_RecordFile";//					= 0x0014,	// indicates the file recording progress
	case E_PROC_RecordMem					:return "E_PROC_RecordMem";//					= 0x0015,	// indicates the memory recording progress
	case E_PROC_SendFSK						:return "E_PROC_SendFSK";//					= 0x0016,	// FSK transmitter finishes sending all data
	case E_PROC_RcvFSK						:return "E_PROC_RcvFSK";//					= 0x0017,	// task of RcvFSK ends
	case E_CHG_ChState						:return "E_CHG_ChState";//					= 0x0018,	// channel state changes
	case E_PROC_AutoDial					:return "E_PROC_AutoDial";//					= 0x0019,	// task of AutoDial progresses
	case E_CHG_RemoteChBlock				:return "E_CHG_RemoteChBlock";//				= 0x001a,	// TUP/ISUP channel: the operation to block the remote channel is completed
	case E_CHG_RemotePCMBlock				:return "E_CHG_RemotePCMBlock";//				= 0x001b,	// TUP/ISUP channel: the operation to block the remote PCM is completed
	case E_SYS_ActualPickup					:return "E_SYS_ActualPickup";//			= 0x001c,	// Analog Trunk channel: pickup command has been executed
	case E_CHG_RingFlag						:return "E_CHG_RingFlag";//				= 0x001d,	// Analog Trunk channel/Analog Trunk Recording channel: voltage level of the ringing current changes
	case E_CHG_RingCount					:return "E_CHG_RingCount";//				= 0x001e,	// Analog Trunk channel: The counter for signal cycles in the ringing current detector changes
	case E_CHG_CIDExBuf						:return "E_CHG_CIDExBuf";//				= 0x001f,	// extended buffer area that stores the CallerID information in FSK and DTMF: The size of Extended Caller ID Buffer changes
	case E_CHG_RxPhoNumBuf					:return "E_CHG_RxPhoNumBuf";//				= 0x0020,	// DTMF detector: a new called party number is received
	case E_CHG_PolarRvrsCount				:return "E_CHG_PolarRvrsCount";//				= 0x0021,	// Analog Trunk channel: a polarity reversal is detected on the line
	case E_SYS_RemotePickup					:return "E_SYS_RemotePickup";//				= 0x0022,	// Analog Trunk channel: enhanced remote pickup detector detects that the called party picks up	
	case E_CHG_FlashCount					:return "E_CHG_FlashCount";//				= 0x0023,	// Station channel or Recording channel: a flash operation is detected on the phone
	case E_CHG_HookState					:return "E_CHG_HookState";//					= 0x0024,	// Station channel: a pickup or hangup behavior is detected on the phone
	case E_CHG_ToneAnalyze					:return "E_CHG_ToneAnalyze";//				= 0x0025,	// Tone detector: tone analyzed result changes
	case E_OverallEnergy					:return "E_OverallEnergy";//				= 0x0026,	// Tone detector: overall energy on the line changes
	case E_CHG_OvrlEnrgLevel				:return "E_CHG_OvrlEnrgLevel";//				= 0x0027,	// Tone detector: indicates the overall energy
	case E_CHG_BusyTone						:return "E_CHG_BusyTone";//				= 0x0028,	// Tone detector: the call progress tone detector detects the change in number of busy tone cycles
	case E_CHG_BusyToneEx					:return "E_CHG_BusyToneEx";//				= 0x0029,	// Tone detector: busy tone is detected by back-to-back busy tone detection
	case E_CHG_VocFxFlag					:return "E_CHG_VocFxFlag";//				= 0x002a,	// Tone detector: voltage level of single tones changes, usually for detecting the fax tone
	case E_CHG_ToneValue					:return "E_CHG_ToneValue";//				= 0x002b,	// Tone detector: tone voltage level changes
	case E_CHG_RingEchoToneTime				:return "E_CHG_RingEchoToneTime";//				= 0x002c,	// Tone detector: count of the ringback tone counter changes
	case E_CHG_PeakFrq						:return "E_CHG_PeakFrq";//				= 0x002d,	// Tone detector: peak frequency changes
	case E_SYS_BargeIn						:return "E_SYS_BargeIn";//					= 0x002e,	// Barge-in detector: detected result changes
	case E_SYS_NoSound						:return "E_SYS_NoSound";//				= 0x002f,	// Tone detector: line keeps silent
	case E_SYS_TIMEOUT						:return "E_SYS_TIMEOUT";//			= 0x0030,	// Global Timer: the timer started by the function SsmStartTimer overflows
	case E_CHG_SpyState						:return "E_CHG_SpyState";//				= 0x0031,	// DTP series: state of the monitoring circuit changes
	case E_CHG_SpyLinkStatus				:return "E_CHG_SpyLinkStatus";//				= 0x0032,	// not use any more
	case E_RCV_DTR_AUDIO					:return "E_RCV_DTR_AUDIO";//				= 0x0033,	// not use any more
	case E_RCV_DTR_HOOK						:return "E_RCV_DTR_HOOK";//				= 0x0034,	// not use any more
	case E_RCV_DTR_LAMP						:return "E_RCV_DTR_LAMP";//				= 0x0035,	// not use any more
	case E_RCV_DTR_FKEY						:return "E_RCV_DTR_FKEY";//				= 0x0036,	// not use any more
	case E_RCV_DTR_DKEY						:return "E_RCV_DTR_DKEY";//				= 0x0037,	// not use any more
	case E_RCV_DTR_VOX						:return "E_RCV_DTR_VOX";//				= 0x0038,	// not use any more
	case E_RCV_DTR_DISPLAY					:return "E_RCV_DTR_DISPLAY";//				= 0x0039,	// not use any more
	case E_RCV_DTR_DIRECTION				:return "E_RCV_DTR_DIRECTION";//				= 0x003a,	// not use any more
	case E_RCV_DTR_RING						:return "E_RCV_DTR_RING";//				= 0x003b,	// not use any more
	case E_CHG_CICRxPhoNumBuf				:return "E_CHG_CICRxPhoNumBuf";//				= 0x003c,	// SS7 Virtual Circuit: new called party numbers are received
	case E_CHG_CICState						:return "E_CHG_CICState";//				= 0x003d,	// SS7 Virtual Circuit: circuit state changes
	case E_PROC_CICAutoDial					:return "E_PROC_CICAutoDial";//				= 0x003e,	// SS7 Virtual Circuit: the task of ShgAutoDial progresses
	case E_RCV_Ss7IsupUtuinf				:return "E_RCV_Ss7IsupUtuinf";//				= 0x003f,	// SS7: USR message is received
	case E_CHG_Mtp2Status					:return "E_CHG_Mtp2Status";//				= 0x0040,	// SS7 signaling link: signaling link state changes
	case E_RCV_DSTDChannel					:return "E_RCV_DSTDChannel";//				= 0x0041,	// DST Series: D-channel event
	case E_RCV_Ss7SpyMsu					:return "E_RCV_Ss7SpyMsu";//				= 0X0042,	// SS7: new monitoring messages (MSU) are received from the SS7 server
	case E_CHG_ToneDetector					:return "E_CHG_ToneDetector";//				= 0x0043,	// Tone detector: the event to output the detection result in the new mode
	case E_CHG_ToneDetectorItem				:return "E_CHG_ToneDetectorItem";//				= 0x0044,	// Tone detector: the event to count the periods of tones in the new mode
	case E_RCV_CALLERID						:return "E_RCV_CALLERID";//				= 0x0045,	// receive caller id
	case E_PROC_FaxDcnTag					:return "E_PROC_FaxDcnTag";//				= 0x0046,	// Fax channel: when the fax reception is successfully completed, judge if the remote fax machine has ever been compelled to stop
	case E_CHG_AMD							:return "E_CHG_AMD";//				= 0x0047,	// Tone detector: used to analyze if it is a human or an answer machine that picks up the phone
	case E_RCV_Ss7IsupCpg					:return "E_RCV_Ss7IsupCpg";//				= 0x0048,	// SS7: CPG message is received
	case E_CHG_CbChStatus					:return "E_CHG_CbChStatus";//				= 0x0049,	// Large-capacity Channel Bank: to monitor any change in the connection state of a line between an on-board channel and a channel bank
	case E_RCV_SS7Mtp2Msu					:return "E_RCV_SS7Mtp2Msu";//				= 0x004a,
		//Reserved 0x4b-0x4f
	case E_REFER_Status						:return "E_REFER_Status";//				= 0x0050,	// SsmIpInitiateTransfer: status after call transfer
	case E_CHG_SpyHangupInfo				:return "E_CHG_SpyHangupInfo";//				= 0x0051,	// DTP series: monitoring circuit receives the off-hook event
	case E_CHG_CallBackRingCount			:return "E_CHG_CallBackRingCount";//				= 0x0052,	// ringback count
	case E_CHG_RcvMF						:return "E_CHG_RcvMF";//				= 0x0053,
	case E_CHG_Pcm32LineState				:return "E_CHG_Pcm32LineState";//				= 0x0054,
	case E_RCV_SPY_CAS						:return "E_RCV_SPY_CAS";//				= 0x0055,
	case E_CHG_RingEchoToneCnt				:return "E_CHG_RingEchoToneCnt";//				= 0x0056,
	case E_Ss7_L2ToL3_IND					:return "E_Ss7_L2ToL3_IND";//				= 0x0057,
		//Reserved 0x58-0x5f
	case E_RCV_IPR_DChannel					:return "E_RCV_IPR_DChannel";//				= 0x0060,	// IPR series: D-channel event
	case E_RCV_IPR_DONGLE_ADDED				:return "E_RCV_IPR_DONGLE_ADDED";//				= 0x0061,	// IPR series: USB-key detected
	case E_RCV_IPR_DONGLE_REMOVED			:return "E_RCV_IPR_DONGLE_REMOVED";//				= 0x0062,	// IPR series: the removal of USB-key detected
	case E_RCV_IPR_NIC_LINKED				:return "E_RCV_IPR_NIC_LINKED";//				= 0x0063,	// IPR series: specified network card detected
	case E_RCV_IPR_NIC_UNLINKED				:return "E_RCV_IPR_NIC_UNLINKED";//				= 0x0064,	// IPR series: specified network card not detected
	case E_RCV_IPR_AUTH_OVERFLOW			:return "E_RCV_IPR_AUTH_OVERFLOW";//				= 0x0065,	// IPR series: authorization overflow	
	case E_RCV_IPR_MEDIA_SESSION_STARTED	:return "E_RCV_IPR_MEDIA_SESSION_STARTED";//		= 0x0066,	// IPR series: session started 
	case E_RCV_IPR_MEDIA_SESSION_STOPED		:return "E_RCV_IPR_MEDIA_SESSION_STOPED";//	= 0x0067,	// IPR series: session stopped 
	case E_RCV_IPR_MEDIA_SESSION_STARTED_TOO:return "E_RCV_IPR_MEDIA_SESSION_STARTED_TOO";//	= 0x0068,	// IPR series: the same session started again
	case E_RCV_IPR_MEDIA_SESSION_FOWARDING	:return "E_RCV_IPR_MEDIA_SESSION_FOWARDING";//	= 0x0069,	// IPR series: session being forwarded (reserved. not used at present)	
	case E_RCV_IPR_MEDIA_SESSION_FOWARD_STOPED:return "E_RCV_IPR_MEDIA_SESSION_FOWARD_STOPED";//	= 0x006a,	// IPR series: session forwarding stopped (reserved. not used at present)
	case E_RCV_IPR_STATION_ADDED			:return "E_RCV_IPR_STATION_ADDED";//		= 0x006b,	// IPR series: the entrance of terminal detected
	case E_RCV_IPR_STATION_REMOVED			:return "E_RCV_IPR_STATION_REMOVED";//			= 0x006c,	// IPR series: the exit of terminal detected	
	case E_IPR_LINK_REC_SLAVER_CONNECTED	:return "E_IPR_LINK_REC_SLAVER_CONNECTED";//		= 0x006d,	// IPR series: recording slaver connection detected
	case E_IPR_LINK_REC_SLAVER_DISCONNECTED	:return "E_IPR_LINK_REC_SLAVER_DISCONNECTED";//	= 0x006e,	// IPR series: recording slaver disconnection detected
	case E_IPR_SLAVER_INIT_CB				:return "E_IPR_SLAVER_INIT_CB";//		= 0x006f,	// IPR series: feedback on the recording slaver initialization
	case E_IPR_ACTIVE_SESSION_CB			:return "E_IPR_ACTIVE_SESSION_CB";//		= 0x0070,	// IPR series: feedback on the requirement for the IPRR channel to enable session receiving 
	case E_IPR_DEACTIVE_SESSION_CB			:return "E_IPR_DEACTIVE_SESSION_CB";//		= 0x0071,	// IPR series: feedback on the requirement for the IPRR channel to disable session receiving 
	case E_IPR_START_REC_CB					:return "E_IPR_START_REC_CB";//		= 0x0072,	// IPR series: feedback on the requirement for the IPRR channel to start recording 
	case E_IPR_STOP_REC_CB					:return "E_IPR_STOP_REC_CB";//			= 0x0073,	// IPR series: feedback on the requirement for the IPRR channel to stop recording 
	case E_IPR_PAUSE_REC_CB					:return "E_IPR_PAUSE_REC_CB";//			= 0x0074,	// IPR series: feedback on the requirement for the IPRR channel to pause recording 
	case E_IPR_RESTART_REC_CB				:return "E_IPR_RESTART_REC_CB";//				= 0x0075,	// IPR series: feedback on the requirement for the IPRR channel to restart recording 
	case E_IPR_START_SLAVER_CB				:return "E_IPR_START_SLAVER_CB";//			= 0x0076,	// IPR series: feedback on the requirement of starting slaver 
	case E_IPR_CLOSE_SLAVER_CB				:return "E_IPR_CLOSE_SLAVER_CB";//			= 0x0077,	// IPR series: feedback on the requirement of closing slaver 
	case E_IPR_RCV_DTMF						:return "E_IPR_RCV_DTMF";//			= 0x0078,	// IPR series: in-band or RFC2833 DTMF detected
	case E_IPR_ACTIVE_AND_REC_CB			:return "E_IPR_ACTIVE_AND_REC_CB";//			= 0x0079,	// IPR series: feedback on the requirement for the IPRR channel to enable Session receiving and start recording 
	case E_IPR_DEACTIVE_AND_STOPREC_CB		:return "E_IPR_DEACTIVE_AND_STOPREC_CB";//		= 0x007a,	// IPR series: feedback on the requirement for the IPRR channel to disable Session receiving and stop recording 
	case E_RCV_IPA_DONGLE_ADDED				:return "E_RCV_IPA_DONGLE_ADDED";//			= 0x007b,	// IPA series: USB-key detected	
	case E_RCV_IPA_DONGLE_REMOVED			:return "E_RCV_IPA_DONGLE_REMOVED";//			= 0x007c, 	// IPA series: removal of USB-key detected	
	default:		{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("ShDevModule.GetString_EventType");
		LOG4CPLUS_ERROR(log,"UNKNOWN the event:" << nEvent);
		return "UNKNOWN";
		}
	}
}

const char * ShDevModule::GetString_State( int nState )
{
	switch ( nState )
	{
	case S_CALL_STANDBY						:return "S_CALL_STANDBY";//				= 0,	// idle
	case S_CALL_PICKUPED					:return "S_CALL_PICKUPED";//			= 1,	// off-hook
	case S_CALL_RINGING						:return "S_CALL_RINGING";//				= 2,	// ringing
	case S_CALL_TALKING						:return "S_CALL_TALKING";//				= 3,	// talking

	case S_CALL_ANALOG_WAITDIALTONE			:return "S_CALL_ANALOG_WAITDIALTONE";//	= 4,	// analog trunk channel: outgoing call, wait for dialing tone
	case S_CALL_ANALOG_TXPHONUM				:return "S_CALL_ANALOG_TXPHONUM";//		= 5,	// analog trunk channel: outgoing call, dialing
	case S_CALL_ANALOG_WAITDIALRESULT		:return "S_CALL_ANALOG_WAITDIALRESULT";//= 6,	// analog trunk channel: outgoing call, wait for dialing result

	case S_CALL_PENDING						:return "S_CALL_PENDING";//				= 7,	// pending
	case S_CALL_OFFLINE						:return "S_CALL_OFFLINE";//				= 8,	// off-line
	case S_CALL_WAIT_REMOTE_PICKUP			:return "S_CALL_WAIT_REMOTE_PICKUP";//	= 9,	// outgoing call: 'wait answer' or 'wait called subscriber pickup'
	case S_CALL_ANALOG_CLEAR				:return "S_CALL_ANALOG_CLEAR";//		= 10,	// analog trunk channel: internal state 
	case S_CALL_UNAVAILABLE					:return "S_CALL_UNAVAILABLE";//			= 11,	// channel unusable
	case S_CALL_LOCKED						:return "S_CALL_LOCKED";//				= 12,	// outgoing call locked

	case S_CALL_RemoteBlock					:return "S_CALL_RemoteBlock";//			= 19,	// blocked by remote
	case S_CALL_LocalBlock					:return "S_CALL_LocalBlock";//			= 20,	// blocked locally

	case S_CALL_Ss1InWaitPhoNum				:return "S_CALL_Ss1InWaitPhoNum";//		= 30,	// SS1 Channel: receive called subscriber number
	case S_CALL_Ss1InWaitFwdStop			:return "S_CALL_Ss1InWaitFwdStop";//	= 31,	// SS1 Channel: wait remote PBX to stop sending forward signal
	case S_CALL_Ss1InWaitCallerID			:return "S_CALL_Ss1InWaitCallerID";//	= 32,	// SS1 Channel: receive Caller ID
	case S_CALL_Ss1InWaitKD					:return "S_CALL_Ss1InWaitKD";//			= 33,	// SS1 Channel: receive KD signal
	case S_CALL_Ss1InWaitKDStop				:return "S_CALL_Ss1InWaitKDStop";//		= 34,	// SS1 Channel: wait remote PBX to stop sending KD signal
	case S_CALL_SS1_SAYIDLE					:return "S_CALL_SS1_SAYIDLE";//			= 35,	// SS1 Channel: send idle signal to remote PBX
	case S_CALL_SS1WaitIdleCAS				:return "S_CALL_SS1WaitIdleCAS";//		= 36,	// SS1 Channel: wait idle signal from remote PBX
	case S_CALL_SS1PhoNumHoldup				:return "S_CALL_SS1PhoNumHoldup";//		= 37,	// SS1 Channel: phone number hold-up
	case S_CALL_Ss1InWaitStopSendA3p		:return "S_CALL_Ss1InWaitStopSendA3p";//= 38,	// SS1 Channel: wait remote PBX to stop sending pulse-method based A3 signal

	case S_CALL_Ss1OutWaitBwdAck			:return "S_CALL_Ss1OutWaitBwdAck";//	= 40,	// SS1 Channel: wait remote PBX to answer seizure confirmation signal	
	case S_CALL_Ss1OutTxPhoNum				:return "S_CALL_Ss1OutTxPhoNum";//		= 41,	// SS1 Channel: send called subscriber number
	case S_CALL_Ss1OutWaitAppendPhoNum		:return "S_CALL_Ss1OutWaitAppendPhoNum";//= 42,	// SS1 Channel: wait application to append phone number
	case S_CALL_Ss1OutTxCallerID			:return "S_CALL_Ss1OutTxCallerID";//	= 43,	// SS1 Channel: send caller ID
	case S_CALL_Ss1OutWaitKB				:return "S_CALL_Ss1OutWaitKB";//		= 44,	// SS1 Channel: wait KB signal which is from remote PBX	
	case S_CALL_Ss1OutDetectA3p				:return "S_CALL_Ss1OutDetectA3p";//		= 45,	// SS1 Channel: wait A3 pulse signal which is from remote PBX

		//case S_FAX_OK							:return "S_FAX_OK";//					= 1,	// 
		//case S_FAX_Wait							:return "S_FAX_Wait";//					= S_CALL_STANDBY,	// FAX channel: idle
	case S_FAX_ROUND						:return "S_FAX_ROUND";//				= 50,	// FAX channel: state transition is in progress
	case S_FAX_PhaseA						:return "S_FAX_PhaseA";//				= 51,	// FAX channel: fax call setup(Phase A)	
	case S_FAX_PhaseB						:return "S_FAX_PhaseB";//				= 52,	// FAX channel: handling before fax message transmission(Phase B) 
	case S_FAX_SendDCS						:return "S_FAX_SendDCS";//				= 53,	// FAX channel: send DCS signal to the receiver during transmission	
	case S_FAX_Train						:return "S_FAX_Train";//				= 54,	// FAX channel: train before fax message transmission
	case S_FAX_PhaseC						:return "S_FAX_PhaseC";//				= 55,	// FAX channel: in fax message transmission(Phase C)	
	case S_FAX_PhaseD						:return "S_FAX_PhaseD";//				= 56,	// FAX channel: handling after fax message transmission(Phase D)
	case S_FAX_NextPage						:return "S_FAX_NextPage";//				= 57,	// FAX channel: transmit next page
	case S_FAX_AllSent						:return "S_FAX_AllSent";//				= 58,	// FAX channel: fax message transmission is completed
	case S_FAX_PhaseE						:return "S_FAX_PhaseE";//				= 59,	// FAX channel: fax call is released(Phase E)
	case S_FAX_Reset						:return "S_FAX_Reset";//				= 60,	// FAX channel: reset MODEM
	case S_FAX_Init							:return "S_FAX_Init";//					= 61,	// FAX channel: "initialize MODEM
	case S_FAX_RcvDCS						:return "S_FAX_RcvDCS";//				= 62,	// FAX channel: receiving fax, "receive DCS signal from sender"
	case S_FAX_SendFTT						:return "S_FAX_SendFTT";//				= 63,	// FAX channel: receiving fax, "send FTT signal indicating training failure"	
	case S_FAX_SendCFR						:return "S_FAX_SendCFR";//				= 64,	// FAX channel: receiving fax, "send CFR signal confirming the request is acceptable"

	case S_FAX_SendPPS						:return "S_FAX_SendPPS";//				= 65,	// FAX channel: fax transmission, successive fax negotiation is undergone in the ECM mode	
	case S_FAX_RcvPPR						:return "S_FAX_RcvPPR";//				= 66,	// FAX channel: fax reception of the PPR signal after its transmission of the PPS signal
	case S_FAX_RepeatECMPage				:return "S_FAX_RepeatECMPage";//		= 67,	// FAX channel: fax transmission, fax data are resent in the ECM mode	
	case S_FAX_CTC_CTR						:return "S_FAX_CTC_CTR";//				= 68,	// FAX channel: positive negotiation is undergone in the ECM mode after 4 times data resending
	case S_FAX_SendPPR						:return "S_FAX_SendPPR";//				= 69,	// FAX channel: the sender is required to resend the fax data in the ECM mode
	case S_FAX_EOR_ERR						:return "S_FAX_EOR_ERR";//				= 300,	// FAX channel: negative processing is done in the ECM mode after several times fax resending
	case S_FAX_RNR_RR						:return "S_FAX_RNR_RR";//				= 301,	// FAX channel: the fax receiver is busy in the ECM mode
	case S_FAX_RTN							:return "S_FAX_RTN";//					= 302,	// FAX channel: fax reception-receiving the message denial and retraining
	case S_FAX_NextPage_EOM					:return "S_FAX_NextPage_EOM";//			= 303,
	case S_FAX_V34_PhaseV8					:return "S_FAX_V34_PhaseV8";//			= 400,

	case S_TUP_WaitPcmReset					:return "S_TUP_WaitPcmReset";//			= 70,	// TUP channel: wait circuit group to reset
	case S_TUP_WaitSAM						:return "S_TUP_WaitSAM";//				= 71,	// TUP channel: wait for subsequent address message of remote PBX
	case S_TUP_WaitGSM						:return "S_TUP_WaitGSM";//				= 72,	// TUP channel: wait for GSM message from remote PBX
	case S_TUP_WaitCLF						:return "S_TUP_WaitCLF";//				= 73,	// TUP channel: wait for disconnect message from remote PBX
	case S_TUP_WaitPrefix					:return "S_TUP_WaitPrefix";//			= 74,	// TUP channel: inbound office prefix
	case S_TUP_WaitDialAnswer				:return "S_TUP_WaitDialAnswer";//		= 75,	// TUP channel: wait for message from remote PBX
	case S_TUP_WaitRLG						:return "S_TUP_WaitRLG";//				= 76,	// TUP channel: wait for release-guard signal from remote PBX
	case S_TUP_WaitSetCallerID				:return "S_TUP_WaitSetCallerID";//		= 77,	// TUP channel: wait for the application to set callerID

	case S_ISDN_OUT_WAIT_NET_RESPONSE		:return "S_ISDN_OUT_WAIT_NET_RESPONSE";//= 81,	// ISDN channel: wait for network respons
	case S_ISDN_OUT_PLS_APPEND_NO			:return "S_ISDN_OUT_PLS_APPEND_NO";//	= 82,	// ISDN channel: wait for the application to append the number
	case S_ISDN_IN_CHK_CALL_IN				:return "S_ISDN_IN_CHK_CALL_IN";//		= 83,	// ISDN channel: incoming call is detected
	case S_ISDN_IN_RCVING_NO				:return "S_ISDN_IN_RCVING_NO";//		= 84,	// ISDN channel: number is been receiving
	case S_ISDN_IN_WAIT_TALK				:return "S_ISDN_IN_WAIT_TALK";//		= 85,	// ISDN channel: ready for talk
	case S_ISDN_OUT_WAIT_ALERT				:return "S_ISDN_OUT_WAIT_ALERT";//		= 86,	// ISDN channel: wait for the alerting signal from remote end
	case S_ISDN_CALL_BEGIN					:return "S_ISDN_CALL_BEGIN";//			= 87,	// ISDN channel: originate an outgoing call or detect an incoming call
	case S_ISDN_WAIT_HUANGUP				:return "S_ISDN_WAIT_HUANGUP";//		= 88,	// ISDN channel: wait for hangup
	case S_ISDN_IN_CALL_PROCEEDING			:return "S_ISDN_IN_CALL_PROCEEDING";//	= 89,	// ISDN channel: call proceeding

	case S_CALL_SENDRING					:return "S_CALL_SENDRING";//			= 100,	// Magnetic channel: send ring

		//case S_SPY_STANDBY						:return "S_SPY_STANDBY";//				= S_CALL_STANDBY,
	case S_SPY_RCVPHONUM					:return "S_SPY_RCVPHONUM";//			= 105,	
		//case S_SPY_RINGING						:return "S_SPY_RINGING";//				= S_CALL_RINGING,
		//case S_SPY_TALKING						:return "S_SPY_TALKING";//				= S_CALL_TALKING,

	case S_SPY_SS1RESET						:return "S_SPY_SS1RESET";//				= 110,	// SS1 channel: reset
	case S_SPY_SS1WAITBWDACK				:return "S_SPY_SS1WAITBWDACK";//		= 111,	// SS1 channel: waiting for the backward acknowledgement
	case S_SPY_SS1WAITKB					:return "S_SPY_SS1WAITKB";//			= 112,	// SS1 channel: waiting for the KB signal

	case S_ISUP_WaitSAM						:return "S_ISUP_WaitSAM";//				= 120,	// ISUP channel: wait for SAM message from remote PBX
	case S_ISUP_WaitRLC						:return "S_ISUP_WaitRLC";//				= 121,	// ISUP channel: wait for release complete signal from remote PBX
	case S_ISUP_WaitReset					:return "S_ISUP_WaitReset";//			= 122,	// ISUP channel: wait for circuit to reset
	case S_ISUP_LocallyBlocked				:return "S_ISUP_LocallyBlocked";//		= 123,	// ISUP channel: locally blocked
	case S_ISUP_RemotelyBlocked				:return "S_ISUP_RemotelyBlocked";//		= 124,	// ISUP channel: remotely blocked
	case S_ISUP_WaitDialAnswer				:return "S_ISUP_WaitDialAnswer";//		= 125,	// ISUP channel: wait for message from remote PBX
	case S_ISUP_WaitINF						:return "S_ISUP_WaitINF";//				= 126,	// ISUP channel: wait for INF message from remote PBX
	case S_ISUP_WaitSetCallerID				:return "S_ISUP_WaitSetCallerID";//		= 127,	// ISUP channel: wait for the application to set caller ID

	case S_DTRC_ACTIVE						:return "S_DTRC_ACTIVE";//				= 128,	// DTR channel: monitored voice channel is in active state
	case S_ISUP_Suspend						:return "S_ISUP_Suspend";//				= 129,	// ISUP channel: suspended

	case S_CALL_EM_TXPHONUM					:return "S_CALL_EM_TXPHONUM";//			= 130,	// E/M channel: 'dial' or the voice alteration resource is used
	case S_CALL_EM_WaitIdleCAS				:return "S_CALL_EM_WaitIdleCAS";//		= 131,	// E/M channel: wait for the idle signal from remote end
	case S_CALL_VOIP_DIALING				:return "S_CALL_VOIP_DIALING";//		= 132,	// IP channel: VoIP calling party is dialing
	case S_CALL_VOIP_WAIT_CONNECTED			:return "S_CALL_VOIP_WAIT_CONNECTED";//	= 133,	// IP channel: VoIP called party picks up the phone and waits for the channel to enter 'talking' state
	case S_CALL_VOIP_CHANNEL_UNUSABLE		:return "S_CALL_VOIP_CHANNEL_UNUSABLE";//= 134,	// IP channel: IP channel is unusable now

	case S_CALL_DISCONECT					:return "S_CALL_DISCONECT";//			= 135,	// USB connection is disconnected

	case S_CALL_SS1WaitFlashEnd				:return "S_CALL_SS1WaitFlashEnd";//		= 136,	// SS1 channel: wait for the end of flash
	case S_CALL_FlashEnd					:return "S_CALL_FlashEnd";//			= 137,	// SS1 channel: flash ends"
	case S_CALL_SIGNAL_ERROR				:return "S_CALL_SIGNAL_ERROR";//		= 139,	// DTR channel: frame synchronization normal but signal incomplete
	case S_CALL_FRAME_ERROR					:return "S_CALL_FRAME_ERROR";//			= 140,	// DTR channel: frame synchronization abnormal but signal complete

		//150-159, reserved for VoIP board
	case S_CALL_VOIP_SESSION_PROCEEDING		:return "S_CALL_VOIP_SESSION_PROCEEDING";//	= 150,	// IP channel: 'In session', it is a state when 183 received
	case S_CALL_VOIP_REG_ING				:return "S_CALL_VOIP_REG_ING";//		= 151,	// IP channel: registering a SIP channel
	case S_CALL_VOIP_REG_FAILED				:return "S_CALL_VOIP_REG_FAILED";//		= 152,	// IP channel: fail to register a SIP channel
	case S_CALL_VOIP_CALL_ON_HOLD			:return "S_CALL_VOIP_CALL_ON_HOLD";//	= 153,

		//160-169, resoured for VoIP resource board
	case S_IP_MEDIA_LOCK					:return "S_IP_MEDIA_LOCK";//			= 160,	// MEDIA channel: locked
	case S_IP_MEDIA_OPEN					:return "S_IP_MEDIA_OPEN";//			= 161,	// MEDIA channel: unlocked
	case S_SPY_RBSWAITACK					:return "S_SPY_RBSWAITACK";//			= 162,
	case S_SPY_RBSSENDACK					:return "S_SPY_RBSSENDACK";//			= 163,

	case S_IPR_USING						:return "S_IPR_USING";//				= 170,	// IPR channel: the channel is used
	case S_IPR_COMMUNICATING				:return "S_IPR_COMMUNICATING";//		= 171,	// IPR channel: the channel is in the communicating state
	default:		{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("ShDevModule.GetString_State");
		LOG4CPLUS_ERROR(log,"UNKNOWN the state:" << nState);
		return "UNKNOWN";
		}
	}
}

const char *ShDevModule::GetString_PengdingReason(int nReason)
{
	switch(nReason){
		case ANALOGOUT_NO_DIALTONE				:return "ANALOGOUT_NO_DIALTONE";//	= 0,	// analog trunk channel: no dial tone detected
		case ANALOGOUT_BUSYTONE					:return "ANALOGOUT_BUSYTONE";//		= 1,	// analog trunk channel: busy tone detected
		case ANALOGOUT_ECHO_NOVOICE				:return "ANALOGOUT_ECHO_NOVOICE";//		= 2,	// analog trunk channel: after the ringback tone detected, the phone line keeps silence
		case ANALOGOUT_NOANSWER					:return "ANALOGOUT_NOANSWER";//		= 3,	// analog trunk channel: after the ringback tone detected, the called subscriber doesn't answer during the specified time 
		case ANALOGOUT_TALKING_REMOTE_HANGUPED	:return "ANALOGOUT_TALKING_REMOTE_HANGUPED";//	= 4,	// analog trunk channel: detected remote subscriber hang up while channel in "connected" state
		case ANALOGOUT_NOVOICE					:return "ANALOGOUT_NOVOICE";//		= 5,	// analog trunk channel: AutoDial finished but no ringback tone or other voice signals have been detected

		case PEND_WaitBckStpMsg					:return "PEND_WaitBckStpMsg";//		= 10,	// indicates the driver has completed the incoming call progress implementation and is waiting for the application to accept or refuse the incoming call
		case SS1IN_BWD_KB5						:return "SS1IN_BWD_KB5";//		= 11,	// SS1 signaling channel: waits for the release signal from the calling party
		case PEND_RemoteHangupOnTalking			:return "PEND_RemoteHangupOnTalking";//		= 12,	// remote end hangs up the phone while talking.
		case PEND_AutoDialFailed				:return "PEND_AutoDialFailed";//		= 13,	// Outgoing call failed
		case PEND_SsxUnusable					:return "PEND_SsxUnusable";//		= 14,	// SS7 signaling is unavailable	
		case PEND_CircuitReset					:return "PEND_CircuitReset";//		= 15,	// generate the event of circuit reset	
		case PEND_PcmSyncLos					:return "PEND_PcmSyncLos";//		= 16,	// the basic frame (0 timeslot) synchronization signal of the digital trunk is lost
		//case	SS1OUT_TALKING_REMOTE_HANGUPED:return "";//		= 20,	// remote end hangs up the phone while talking
		case PEND_CalleeHangupOnTalking			:return "PEND_CalleeHangupOnTalking";//		= 20,	// remote end hangs up the phone while talking

		case SS1OUT_NOANSWER					:return "SS1OUT_NOANSWER";//		= 21,	// SS1 signaling channel: called subscriber doesn't answer the call duiring the time specified by the configuration item MaxWaitAutoDialAnswerTime
		case SS1OUT_NOBWDACK					:return "SS1OUT_NOBWDACK";//		= 22,	// SS1 signaling channel: wait for the 'Seizure Ack' signal from the remote PBX time out
		case SS1OUT_DIALING_BWD_HANGUP			:return "SS1OUT_DIALING_BWD_HANGUP";//		= 23,	// SS1 signaling channel: remote PBX cancels the call
		case SS1OUT_BWD_A5						:return "SS1OUT_BWD_A5";//		= 24,	// SS1 signaling channel: receives the A5 signal (unallocated number signal) from the remote PBX
		case SS1OUT_BWD_KB5						:return "SS1OUT_BWD_KB5";//		= 25,	// SS1 signaling channel: receives the KB=5 (unallocated number signal) from the remote PBX
		case SS1OUT_BWD_KB2						:return "SS1OUT_BWD_KB2";//		= 26,	// SS1 signaling channel: receives KB=2(called subscriber 'local busy')from the remote PBX
		case SS1OUT_BWD_KB3						:return "SS1OUT_BWD_KB3";//		= 27,	// SS1 signaling channel: receives KB=3(called subscriber 'toll busy')receives from the remote PBX
		case SS1OUT_BWD_A4						:return "SS1OUT_BWD_A4";//		= 28,	// SS1 signaling channel: receives A4 signal (keys congestion) from remote PBX
		case SS1OUT_BWD_KB4						:return "SS1OUT_BWD_KB4";//		= 29,	// SS1 signaling channel: receives KB=4 signal (keys congestion) from remote PBX
		case SS1OUT_TIMEOUT_BWD_A				:return "SS1OUT_TIMEOUT_BWD_A";//		= 30,	// SS1 signaling channel: wait for backward group A signals from the remote PBX is time out
		case SS1OUT_TIMEOUT_BWD_A_STOP			:return "SS1OUT_TIMEOUT_BWD_A_STOP";//		= 31,	// SS1 signaling channel: wait for the remote PBX to stop sending backward group A signals time out
		case SS1OUT_TIMEOUT_BWD_KB				:return "SS1OUT_TIMEOUT_BWD_KB";//		= 32,	// SS1 signaling channel: wait for KB signal from the remote PBX time out
		case SS1OUT_TIMEOUT_BWD_KB_STOP			:return "SS1OUT_TIMEOUT_BWD_KB_STOP";//		= 33,	// SS1 signaling channel: wait for the remote PBX to stop sending KB signal time out
		case SS1OUT_TIMEOUT_CALLERID_BWD_A1		:return "SS1OUT_TIMEOUT_CALLERID_BWD_A1";//		= 34,	// SS1 signaling channel: wait for backward group A signal from the remote PBX time out when sending calling party number to the remote PBX
		case SS1OUT_TIMEOUT_CALLERID_BWD_A1_STOP:return "SS1OUT_TIMEOUT_CALLERID_BWD_A1_STOP";//	= 35,	// SS1 signaling channel: wait for remote PBX to stop sending backward group A signals time out and autodial fails when sending calling party number to remote PBX 
		case SS1OUT_UNDEFINED_CALLERID_BWD_A	:return "SS1OUT_UNDEFINED_CALLERID_BWD_A";//	= 36,	// SS1 signaling channel: receive undefined backward group A signal when sending calling party number to remote PBX
		case SS1OUT_UNDEFINED_BWD_A				:return "SS1OUT_UNDEFINED_BWD_A";//	= 37,	// SS1 signaling channel: receive undefined backward group A signal
		case SS1OUT_UNDEFINED_BWD_KB			:return "SS1OUT_UNDEFINED_BWD_KB";//	= 38,	// SS1 signaling channel: receive the undefined KB signal 

		case ISDN_CALLOVER						:return "ISDN_CALLOVER";//	= 41,	// call is over and the remote end hangs up at first
		case ISDN_WAIT_RELEASE					:return "ISDN_WAIT_RELEASE";//	= 42,	// receives the 'disconnected' message from the remote end and waits for the release of the local end
		case ISDN_HANGING						:return "ISDN_HANGING";//	= 43,	// local end hangs up 
		case ISDN_RELEASING						:return "ISDN_RELEASING";//	= 44,	// call releasing
		case ISDN_UNALLOCATED_NUMBER			:return "ISDN_UNALLOCATED_NUMBER";//	= 45,	// unallocated number
		case ISDN_NETWORK_BUSY					:return "ISDN_NETWORK_BUSY";//	= 46,	// network busy	
		case ISDN_CIRCUIT_NOT_AVAILABLE			:return "ISDN_CIRCUIT_NOT_AVAILABLE";//	= 47,	// designated circuit is unavailable

		case PEND_CalleeHangupOnWaitRemotePickUp:return "PEND_CalleeHangupOnWaitRemotePickUp";//	= 48,	// receives the "disconnected" message from the remote PBX when waiting for the called subscriber to pick up
		case ISUP_HardCircuitBlock				:return "ISUP_HardCircuitBlock";//	= 49,	// receives the hardware blocking message from the remote PBX
		case ISUP_RemoteSuspend					:return "ISUP_RemoteSuspend";//	= 50,	// timer T6 time out, for more information about the timer T6, refer to the "ISUP Channel State Machine" in chapter 1

		case PEND_RcvHGBOrSGB					:return "PEND_RcvHGBOrSGB";//	= 51,	// receives the blocking message from the remote PBX(SGB/HGB)

		case ISDN_NO_ANSWER						:return "ISDN_NO_ANSWER";//	= 52,	// no answer
		case ISDN_CALL_REJ						:return "ISDN_CALL_REJ";//	= 53,	// call rejection
		case PEND_RemoteHangupOnRinging			:return "PEND_RemoteHangupOnRinging";//	= 54,	// remote PBX cancel the call while channel in ringing state
		case ISDN_NO_ROUTE						:return "ISDN_NO_ROUTE";//	= 55,	// no route to the destination, the cause may be the mobile phone is not in the service area	
		case ISDN_NO_ROUTE_TO_DEST				:return "ISDN_NO_ROUTE_TO_DEST";//	= 56,	// no route to the destination, the cause may be the mobile phone is power off	

		case EM_USER_BUSY						:return "EM_USER_BUSY";//	= 57,	// user busy
		case EM_CH_ERROR						:return "EM_CH_ERROR";//	= 58,	// channel error
		case EM_LOCAL_HANGUP					:return "EM_LOCAL_HANGUP";//	= 59,	// local end hangs up first
		case EM_LOCAL_NOANSWER					:return "EM_LOCAL_NOANSWER";//	= 60,	// local end no answer
		case EM_REMOTE_HANGUP					:return "EM_REMOTE_HANGUP";//	= 61,	// remote end hangs up first
		case EM_REMOTE_NOANSWER					:return "EM_REMOTE_NOANSWER";//	= 62,	// remote end no answer

		case PEND_RemoteHangupOnSuspend			:return "PEND_RemoteHangupOnSuspend";//	= 63,	// remote end hangs up while channel in suspended state
		case PEND_CalleeHangupOnSuspend			:return "PEND_CalleeHangupOnSuspend";//	= 64,	// called party hangs up while channel in suspended state

		case ISDN_NORMAL_UNSPEC					:return "ISDN_NORMAL_UNSPEC";//	= 65,	// calll is finished normally
		case ISDN_USER_ABSENCE					:return "ISDN_USER_ABSENCE";//	= 66,	// user absent
		case ISDN_INVALID_NUMBER_FOEMAT			:return "ISDN_INVALID_NUMBER_FOEMAT";//	= 67,	// number format invalid
		case ISDN_NO_CIRCUIT_AVAILABLE			:return "ISDN_NO_CIRCUIT_AVAILABLE";//	= 68,	// no circuit/channel available	
		case IP_REMOTE_CRASH					:return "IP_REMOTE_CRASH";//	= 69,	// remote crash
		case IP_REMOTE_CLOSE					:return "IP_REMOTE_CLOSE";//	= 70,	// remote close(Bye or Cancel)
		case IP_DIAL_TIMEOUT					:return "IP_DIAL_TIMEOUT";//	= 71,	// dial time out
		case IP_REMOTE_REJECT					:return "IP_REMOTE_REJECT";//	= 72,	// remote rejection
		case IP_REFER_SUCCEED					:return "IP_REFER_SUCCEED";//	= 73,
		case IP_REFER_REFUSE					:return "IP_REFER_REFUSE";//	= 74,
		case IP_STUN_FAILED						:return "IP_STUN_FAILED";//	= 75, 	//stun failed in call
		case IP_NOTRCV_ACK						:return "IP_NOTRCV_ACK";//    = 76,   // Not receive ACK
		case IP_REDIRECT_FAIL					:return "IP_REDIRECT_FAIL";//	= 77    // Redirect failed
		default:	{
			static log4cplus::Logger log = log4cplus::Logger::getInstance("ShDevModule.GetString_State");
			LOG4CPLUS_ERROR(log,"UNKNOWN the state:" << nReason);
			return "UNKNOWN";
		}
	}
}

}
}
