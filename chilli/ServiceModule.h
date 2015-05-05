#pragma once

#ifndef _CHILLI_SERVICEMODULE_HEADER_
#define _CHILLI_SERVICEMODULE_HEADER_

#include <winsock2.h>
#include <windows.h>
#include <log4cplus/logger.h>

namespace chilli{

	#define SERVICENAME_DEFAULT _T("chilli")
	#define SERVICEDESCRIPTION _T("The chilli service.")
	#define  WINSERVERPARAMETER _T("-startservice")

	class ServiceModule
	{
	public:
		ServiceModule(void);
		~ServiceModule(void);
		bool m_bService;
		char m_szServiceName[256];
		SERVICE_STATUS_HANDLE m_hServiceStatus;
		SERVICE_STATUS m_status;
	
	private: 
		log4cplus::Logger log ;
		void Init();
	public:

		long UnregisterServer(void);


		long RegisterServer(bool bService);

		bool Uninstall(void);
		bool IsInstalled(void);
		bool Install(void);


	public:
		void SetServiceStatus(DWORD dwState);

		static char * GetServiceStatusStrName(unsigned long dwState);
	};

}//end namespace chilli

#endif //_SERVICEMODULE_HEADER_