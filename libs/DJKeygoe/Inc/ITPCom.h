#ifndef __ITP_COM_H__
#define __ITP_COM_H__

#include "ITPMsgPublic.h"
#include "ITPDataDefine.h"
#include "ITPMainModCallBack.h"

#define ITP_SYSTEM_FLAG 0x49545031  // ITP系统标识

///////////////// 模块连接到服务端时，发送的授权请求信息 //////////////////////
typedef struct
{	
	DJ_S32          m_ItpFlag;       // 系统标识	
	DJ_U8           m_u8ModuleType;  // 模块类型
	DJ_U8           m_u8MainFuncId;  // 主功能号
	DJ_U8           m_u8SubFuncId;   // 子功能号
	DJ_U8           m_u8UnitId;      // 单元号			
	
	DJ_S32          m_Version;       // 版本号	
	DJ_S32          m_AckInfo;       // 确认值,初始0,成功1,错误-1，上层不用关心
	
	PKG_HEAD_STRUCT m_PkgHead;       // 授权包头
	DJ_S8           m_s8Username[32];// 授权用户
	DJ_S8           m_s8Password[32];// 授权密码
	
	DJ_U8           m_u8Reserved[36];// 备用	
}LICENCE_INFO_STRUCT, *PLICENCE_INFO_STRUCT;

///////////////// 上层模块查询服务端有无客户端连接用到的结构 //////////////////
typedef struct
{
	DJ_SOCKET     m_SkForListen;     // 接受连接时用到的套节字：用来监听
	DJ_SOCKET     m_SkForClient;     // 接受连接时返回的套节字：用来通讯
	DJ_S8         m_szIP[32];        // 客户端IP地址
	DJ_S32        m_Port;            // 客户端端口号

	LICENCE_INFO_STRUCT Licence;	
}CONN_INFO_STRUCT, *PCONN_INFO_STRUCT;


#ifdef __cplusplus
extern "C" 
{
#endif

DJ_S32  TCP_SkOpen(DJ_SOCKET *ps);                                   // 打开一个套节字
DJ_S32  TCP_SkClose(DJ_SOCKET s);                                    // 关闭一个套节字

DJ_S32  TCP_SkConnect(DJ_SOCKET s, DJ_S8* pszIP, DJ_S32 Port, PLICENCE_INFO_STRUCT pLicence);

DJ_S32  TCP_SkWaitSet(DJ_SOCKET s, DJ_S8* pszIP, DJ_S32 Port);       // 进行绑定和监听
DJ_S32  TCP_SkWaitConnect(DJ_SOCKET s);                              // 启动等待线程
DJ_S32  TCP_SkGetConnect(DJ_SOCKET s, PCONN_INFO_STRUCT pConnInfo);  // 查询客户连接						
DJ_S32  TCP_SkEasyAuthorize(DJ_SOCKET s, DJ_S8* pszUsername,DJ_S8* pszPassword, DJ_U8 f = 0);

DJ_S32  TCP_SkSend(DJ_SOCKET s, PPKG_HEAD_STRUCT pHead);             // 发送数据
DJ_S32  TCP_SkRecv(DJ_SOCKET s, PPKG_HEAD_STRUCT pHead);             // 接收数据

DJ_S32  TCP_SkGetLastError();                                        // 最后的错误代码

//DJ_S32  TCP_SkBeginLOGFile(DJ_S8* pszFilename);                      // 开始写日志文件
//DJ_S32  TCP_SkEndLOGFile();                                          // 结束写日志文件

DJ_S32  TCP_SkStartup();                                             // 初始化(Linux专用)
DJ_S32  TCP_SkCleanup();                                             // 清除(Linux专用)

//日志初始化接口，windows和linux都必须调用
DJ_S32  TCP_SkStartLog( DJ_Void* pCallBack, DJ_Void *pLogCallBack, DJ_U8 u8LogType, DJ_U8 u8ModuleType, DJ_U8 u8ModuleUnitNo, DJ_S8 *pIniPath, DJ_S8 *pLogDllPath  );                                            // 初始化(Linux专用)
DJ_S32  TCP_SkCleanLog();                                            

#ifdef __cplusplus
}
#endif

#endif
