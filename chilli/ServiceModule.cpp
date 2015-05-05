#include "StdAfx.h"
#include "ServiceModule.h"
#include <tchar.h>
#include <log4cplus/loggingmacros.h>

namespace chilli{

	
	ServiceModule::ServiceModule(void)
		: m_bService(false)
	{
		log = log4cplus::Logger::getInstance("chilli.ServiceModule");
		lstrcpy(m_szServiceName,SERVICENAME_DEFAULT);
		Init();
		LOG4CPLUS_DEBUG(log,"constructor.");
	}


	ServiceModule::~ServiceModule(void)
	{
		LOG4CPLUS_DEBUG(log,"destruction a servicemodule.");
	}


	void ServiceModule::Init()
	{		
		
		LOG4CPLUS_TRACE(log,"Init fuction starting...");
		// set up the initial service status 
		m_hServiceStatus = NULL;
		m_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
		m_status.dwCurrentState = SERVICE_STOPPED;
		m_status.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
		m_status.dwWin32ExitCode = 0;
		m_status.dwServiceSpecificExitCode = 0;
		m_status.dwCheckPoint = 0;
		m_status.dwWaitHint = 0;
		LOG4CPLUS_INFO(log,"ServiceModule Init finished,type=SERVICE_WIN32_OWN_PROCESS,state=SERVICE_STOPPED,accepter=SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN,exitcode=0.");
		
	}

	long ServiceModule::UnregisterServer(void)
	{
		LOG4CPLUS_DEBUG(log,"UnregisterServer. ");
		return Uninstall();
	}

	long ServiceModule::RegisterServer(bool bService)
	{
		LOG4CPLUS_DEBUG(log,"register server.");
		Uninstall();
		if (bService)
		{
			return Install();
		}
		return 0;
	}


	bool ServiceModule::Uninstall(void)
	{
		LOG4CPLUS_TRACE(log,"Uninstall,starting...");
		if (!IsInstalled())
			return true;

		SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

		if (hSCM == NULL)
		{
			LOG4CPLUS_ERROR(log, "Couldn't open service manager"<<m_szServiceName);
			return false;
		}

		SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_STOP | DELETE);

		if (hService == NULL)
		{
			::CloseServiceHandle(hSCM);
			LOG4CPLUS_ERROR(log, "Couldn't open service");
			return false;
		}
		SERVICE_STATUS status;
		::ControlService(hService, SERVICE_CONTROL_STOP, &status);

		bool bDelete = ::DeleteService(hService)?true:false;
		if (!bDelete)
		{
			LOG4CPLUS_ERROR(log,"Service could not be deleted errorcode="<<GetLastError());
		}
	
		::CloseServiceHandle(hService);
		::CloseServiceHandle(hSCM);
	
		return bDelete;
	}


	bool ServiceModule::IsInstalled(void)
	{
		bool bResult = false;

		SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

		if (hSCM != NULL)
		{
			SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_QUERY_CONFIG);
			if (hService != NULL)
			{
				bResult = true;
				::CloseServiceHandle(hService);
			}
			::CloseServiceHandle(hSCM);
		}
		if (bResult)
		{
			LOG4CPLUS_TRACE(log,"service is instatlled");
		}
		else
		{
			LOG4CPLUS_TRACE(log,"service is not instatlled");
		}
		return bResult;
	}


	bool ServiceModule::Install(void)
	{
		LOG4CPLUS_TRACE(log,"install service starting...");
		if (IsInstalled())
			return true;

		SERVICE_DESCRIPTION desc;
		desc.lpDescription = SERVICEDESCRIPTION;

		SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if (hSCM == NULL)
		{
			LOG4CPLUS_ERROR(log, _T("Couldn't open service manager"));
			return FALSE;
		}

		// Get the executable file path
		TCHAR szFilePath[_MAX_PATH];
		::GetModuleFileName(NULL, szFilePath, _MAX_PATH);

		strcat_s(szFilePath,WINSERVERPARAMETER);
		
		LOG4CPLUS_TRACE(log, "servicename (" << m_szServiceName << ")" << std::endl);
		LOG4CPLUS_TRACE(log," FilePath (" << szFilePath << ")" << std::endl);

		SC_HANDLE hService = ::CreateService(
			hSCM, m_szServiceName, m_szServiceName,
			SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
			SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,
			szFilePath, NULL, NULL, _T("RPCSS\0"), NULL, NULL);
	
		if (hService == NULL) {
			LOG4CPLUS_ERROR(log, "Error creating chilli service (" << GetLastError() << ")");
			CloseServiceHandle(hSCM);
			return false;
		}

		/* Set desc, and don't care if it succeeds */
		if (!ChangeServiceConfig2(hService, SERVICE_CONFIG_DESCRIPTION, &desc)) {
			LOG4CPLUS_ERROR(log, "chilli installed, but could not set the service description (" << GetLastError() << ")");
		}

		::CloseServiceHandle(hService);
		::CloseServiceHandle(hSCM);
		return true;

	}


	void ServiceModule::SetServiceStatus(DWORD dwState)
	{
		m_status.dwCurrentState = dwState;
		LOG4CPLUS_INFO(log,"Set Service status=" << GetServiceStatusStrName(dwState));
		::SetServiceStatus(m_hServiceStatus, &m_status);
	}


}//end namespace ServiceMudoule



char * chilli::ServiceModule::GetServiceStatusStrName(unsigned long dwState)
{
	switch(dwState)
	{
		case SERVICE_STOPPED:return "SERVICE_STOPPED" ;
		case SERVICE_START_PENDING:return "SERVICE_START_PENDING" ;
		case SERVICE_STOP_PENDING:return "SERVICE_STOP_PENDING" ;
		case SERVICE_RUNNING:return "SERVICE_RUNNING" ;
		case SERVICE_CONTINUE_PENDING:return "SERVICE_CONTINUE_PENDING" ;
		case SERVICE_PAUSE_PENDING:return "SERVICE_PAUSE_PENDING" ;
		case SERVICE_PAUSED:return "SERVICE_PAUSED" ;
		default:return"UNKNOWN";
	}
	return NULL;

}