#pragma once

#ifndef _CHILLI_SERVICEMODULE_HEADER_
#define _CHILLI_SERVICEMODULE_HEADER_

#include <winsock2.h>
#include <windows.h>
#include <log4cplus/logger.h>

namespace chilli{

	#define SERVICENAME_DEFAULT ("chilli")
	#define SERVICEDESCRIPTION ("The chilli service.")
	#define  WINSERVERPARAMETER ("-startservice")

	class ServiceModule
	{
	public:
		ServiceModule(void){};
		~ServiceModule(void){};
		static bool m_bService;
		static char m_szServiceName[256];
		static SERVICE_STATUS_HANDLE m_hServiceStatus;
		static SERVICE_STATUS m_status;
	
	private: 
		static log4cplus::Logger log ;
		static HANDLE stopEvent;
		static HANDLE stopEvented;

	public:
		static void Init();

		static long UnregisterServer(void);
		static long RegisterServer(bool bService);

		static void SetServiceStatus(DWORD dwState);
		static const char * GetServiceStatusStrName(unsigned long dwState);
		static void WINAPI Start(DWORD  dwArgc, LPTSTR* lpszArgv);
		static void Stop();
		static void WINAPI chilli::ServiceModule::ServiceCtrlHandler(DWORD  dwOpcode);
	private:
		static bool Uninstall(void);
		static bool IsInstalled(void);
		static bool Install(void);
	};

}//end namespace chilli

#endif //_SERVICEMODULE_HEADER_