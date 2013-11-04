#ifndef DJACSINTERDEF_H
#define DJACSINTERDEF_H

#include "ItpFlowChanDef.h"
#include "DJAcsDataDef.h"
#include "DJAcsCmdDef.h"
#ifdef WIN32
#include <io.h>
#include <string.h>
#include <stdio.h>
#endif
#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((a) > (b)) ? (a) : (b))

#define PLFROMCODEC(X)	(X)==VOIP_MEDIA_AUDIO_PCMU? 0 : \
						((X)==VOIP_MEDIA_AUDIO_PCMA? 8 : \
						((X)==VOIP_MEDIA_AUDIO_G723? 4 : \
						((X)==VOIP_MEDIA_AUDIO_G729? 18 : \
						((X)==VOIP_MEDIA_AUDIO_AMR? 98 : \
						((X)==VOIP_MEDIA_VIDEO_H263? 34 : \
						((X)==VOIP_MEDIA_VIDEO_H263P? 100 : \
						((X)==VOIP_MEDIA_VIDEO_MPEG4? 101 : \
						((X)==VOIP_MEDIA_VIDEO_H264? 102 : 103))))))))

//mediaex local port
//type: 0-mediaex, 1-videoconf(only video)
//base: mediaex unit base port
//channel: mediaex or videoconf channel id
//sub_ch: videoconf sub channel
#define MEDIAEX_CH_PERUNIT	120
#define MEDIAEX_PORTVIDEO(type, base, channel, sub_ch) (type)==0? ((base)+(channel)*4):((base)+MEDIAEX_CH_PERUNIT*4+(channel)*64+(sub_ch)*4)
#define MEDIAEX_PORTAUDIO(type, base, channel) ((base)+(channel)*4+2)

//rtpx local port
//channel: rtpx channel id
#define RTPXPORT(channel) (20000+channel*2)

/*Acs_Fax_InterCmd*/
typedef struct
{
	PITP_RES_CHAN         m_ITPFaxRes;/*fax res*/
    PITP_RES_CHAN         m_ITPFaxVocRes;/*fax voice res*/
    SendFaxParm_t         m_ITPSendFaxParm;/*send fax parm*/
}Acs_Fax_InterCmd;/*Acs_Fax_InterCmd*/

/*Acs_FaxEnd_InterCmd*/
typedef struct
{
    PITP_RES_CHAN         m_ITPFaxVocRes;/*fax voice res*/
    DJ_S32                m_s32EvtState;
    DJ_S32                m_s32ErrCode;
    DJ_U8                 m_u8ErrStep;
    DJ_U8                 m_u8T30CmdState;
    DJ_U8                 m_u8T30RcvState;
    DJ_U16                m_u16TotalPages;
    DJ_S8                 m_s8RemoteID[20];
}Acs_FaxEnd_InterCmd;/*Acs_FaxEnd_InterCmd*/

typedef struct
{
	char szCalling[20];/**/
	char szCalled[20];/**/
	char szOrigCalled[20];/**/
	char szLostTime[40];/**/
}LostCallInfo;/*LostCallInfo*/

typedef struct
{
	DeviceID_t        m_FaxDevice;
	DJ_S8             m_s8T38Shake;
	DJ_S8             m_s8Rfu1[3];
}Fax_VoIP_InterCmd;/*Fax_VoIP_InterCmd*/

typedef struct 
{
	DeviceID_t    m_DeviceID;
	char          m_szCaller[32];
}CallUserInfor;/*CallUserInfor*/

typedef struct
{
	char          m_s8Buff[1024];
}InterCmdStru;/*InterCmdStru*/

typedef struct
{
    unsigned char  u8Char;
}UCHAR;/*UCHAR*/
double T_Pow( int e, int b)
{
	double e1 = e;
	double b1 = b;
	double dRet = 0;

	int i, j;

	if ( 0 == e )
	    return 0;

	dRet = 1;
	if ( 0 < b )
	{
		for ( i = 0; i < b; i++ )
		{
			dRet = dRet*e1;
		}
	}
	else if ( 0 == b )
	{
		return 1;
	}
	else
	{
	    for ( i = 0; i < (b<0?-b:b); i++ )
	    {
		dRet = dRet*e1;
	    }
	    
	    dRet = 1/dRet;
	}
	
	return dRet;
}
#ifndef WIN32
#define pow   T_Pow
#endif 
/*LinkStru*/
typedef struct
{
	  DeviceID_t						DstDev; /*dst dev*/
    PITP_RES_CHAN         SRtpx;
    PITP_RES_CHAN         DRtpx;
    PITP_RES_CHAN         MEx;
}LinkStru;/*LinkStru*/

#define MAX_LINKS			128

/*MediaType*/
typedef struct
{
	DJ_U8 m_u8MediaType;
	DJ_U8 rfu;
	DJ_U16 m_u16Kbps;
}MediaType;/*MediaType*/

#ifndef NULL
#define NULL 0
#endif
DJ_S32 S2Int(DJ_S8 * str,DJ_S8 * sep,DJ_U32 buf[])
{
	DJ_U32 i = 0;
	DJ_S8 * p = NULL;
	DJ_S8  s8Buf[2048];
	
	if(str == NULL|| strlen(str) == 0 || sep == NULL || strlen(sep) == 0)
	{
		return -1;
	}
	strcpy(s8Buf,str);
	p=strtok(s8Buf,sep);
	
	while(p!=NULL)
	{
		buf[i++] = atoi(p);
		p=strtok(NULL,sep);
	}
	return i;
}

DJ_U32  IPStringtoInt(DJ_S8* string)
{
	DJ_U32 FIP[4];
	DJ_U32 UIP = 0;

	if (string)
	{
		S2Int(string,".",FIP);
		UIP = FIP[3] << 24 | 
			  FIP[2] << 16 |
			  FIP[1] << 8  | 
			  FIP[0];		
	}

	return UIP;
}

/*CmdParamData_ReadVoltage_t*/
typedef struct
{    
	DJ_U8   m_u8ReadFlag;      /*Read voltage control flag, 0: stop read; 1: start read*/
	DJ_S8   m_s8Reserved1[3];
	DJ_U32  m_u32TimeSpan;     /*Keygoe report voltage event time span, unit: ms*/
	DJ_S8   m_s8Voltage;       /*Current voltage value*/ 
    DJ_U8   m_u8Reserved2[3];   /*reserved*/
}CmdParamData_ReadVoltage_t;/*CmdParamData_ReadVoltage_t*/


#endif //DJACSINTERDEF_H
