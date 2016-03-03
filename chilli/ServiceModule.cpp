#include "ServiceModule.h"
#include "chilli.h"
#include <log4cplus/loggingmacros.h>


namespace chilli{

	log4cplus::Logger ServiceModule::log = log4cplus::Logger::getInstance("chilli.ServiceModule");
	HANDLE ServiceModule::stopEvent;
	bool ServiceModule::m_bService = false;
	char ServiceModule::m_szServiceName[256] = SERVICENAME_DEFAULT;
	SERVICE_STATUS_HANDLE ServiceModule::m_hServiceStatus = NULL;
	SERVICE_STATUS ServiceModule::m_status;

	void ServiceModule::Init()
	{		
		//lstrcpy(m_szServiceName,SERVICENAME_DEFAULT);
		
		LOG4CPLUS_TRACE(log, __FUNCTION__ << " start.");
		// set up the initial service status 
		
		m_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
		m_status.dwCurrentState = SERVICE_STOPPED;
		m_status.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
		m_status.dwWin32ExitCode = 0;
		m_status.dwServiceSpecificExitCode = 0;
		m_status.dwCheckPoint = 0;
		m_status.dwWaitHint = 0;
		LOG4CPLUS_INFO(log,"ServiceModule Init finished,type=SERVICE_WIN32_OWN_PROCESS,state=SERVICE_STOPPED,accepter=SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN,exitcode=0.");
		LOG4CPLUS_TRACE(log, __FUNCTION__ << " end.");
	}

	long ServiceModule::UnregisterServer(void)
	{
		LOG4CPLUS_TRACE(log, __FUNCTION__ << " start.");
		if (IsInstalled()){
			Uninstall();
		}
		LOG4CPLUS_TRACE(log, __FUNCTION__ << " end.");
		return 0;
	}

	long ServiceModule::RegisterServer(bool bService)
	{
		LOG4CPLUS_TRACE(log, __FUNCTION__ << " start.");
		if (IsInstalled()){
			Uninstall();
		}

		if (bService)
		{
			Install();
		}
		LOG4CPLUS_TRACE(log, __FUNCTION__ << " end.");
		return 0;
	}


	bool ServiceModule::Uninstall(void)
	{
		LOG4CPLUS_TRACE(log, __FUNCTION__ << " start.");

		SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

		if (hSCM == NULL)
		{
			DWORD err = GetLastError();
			LOG4CPLUS_ERROR(log, "Couldn't open service manager:" << err);
			return false;
		}

		SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_STOP | DELETE);

		if (hService == NULL)
		{
			DWORD err = GetLastError();
			::CloseServiceHandle(hSCM);
			LOG4CPLUS_ERROR(log, "Couldn't open service:" << err);
			return false;
		}
		SERVICE_STATUS status;
		::ControlService(hService, SERVICE_CONTROL_STOP, &status);

		bool bDelete = ::DeleteService(hService)?true:false;
		if (!bDelete)
		{
			DWORD err = GetLastError();
			LOG4CPLUS_ERROR(log,"Service could not be deleted errorcode="<< err);
		}
	
		::CloseServiceHandle(hService);
		::CloseServiceHandle(hSCM);
		LOG4CPLUS_TRACE(log, __FUNCTION__ << " end.");
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
		else{
			DWORD err = GetLastError();
			LOG4CPLUS_ERROR(log, "Couldn't open service manager:" << err);
		}

		if (bResult){
			LOG4CPLUS_TRACE(log,"service is instatlled");
		}
		else{
			LOG4CPLUS_TRACE(log,"service is not instatlled");
		}
		return bResult;
	}


	bool ServiceModule::Install(void)
	{
		LOG4CPLUS_TRACE(log, __FUNCTION__ << " start.");

		SERVICE_DESCRIPTION desc;
		desc.lpDescription = SERVICEDESCRIPTION;

		SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if (hSCM == NULL)
		{
			DWORD err = GetLastError();
			LOG4CPLUS_ERROR(log, "Couldn't open service manager:" << err);
			return FALSE;
		}

		// Get the executable file path
		TCHAR szFilePath[_MAX_PATH];
		::GetModuleFileName(NULL, szFilePath, _MAX_PATH);
		strcat_s(szFilePath, " ");
		strcat_s(szFilePath,WINSERVERPARAMETER);
		
		LOG4CPLUS_TRACE(log, "servicename (" << m_szServiceName << ")");
		LOG4CPLUS_TRACE(log," FilePath (" << szFilePath << ")");

		SC_HANDLE hService = ::CreateService(
			hSCM, m_szServiceName, m_szServiceName,
			SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
			SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,
			szFilePath, NULL, NULL, ("RPCSS\0"), NULL, NULL);
	
		if (hService == NULL) {
			DWORD err = GetLastError();
			LOG4CPLUS_ERROR(log, "Error creating chilli service (" << err << ")");
			CloseServiceHandle(hSCM);
			return false;
		}

		/* Set desc, and don't care if it succeeds */
		if (!ChangeServiceConfig2(hService, SERVICE_CONFIG_DESCRIPTION, &desc)) {
			DWORD err = GetLastError();
			LOG4CPLUS_ERROR(log, "chilli installed, but could not set the service description (" << err << ")");
		}

		::CloseServiceHandle(hService);
		::CloseServiceHandle(hSCM);
		LOG4CPLUS_TRACE(log, __FUNCTION__ << " end.");
		return true;

	}


	void ServiceModule::SetServiceStatus(DWORD dwState)
	{
		m_status.dwCurrentState = dwState;
		LOG4CPLUS_INFO(log,"Set Service status=" << GetServiceStatusStrName(dwState));
		::SetServiceStatus(m_hServiceStatus, &m_status);
	}


}//end namespace ServiceMudoule



const char * chilli::ServiceModule::GetServiceStatusStrName(unsigned long dwState)
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

void WINAPI chilli::ServiceModule::Start(DWORD  dwArgc, LPTSTR* lpszArgv)
{
	// Register the control request handler
	LOG4CPLUS_TRACE(log, __FUNCTION__ << " Start.");	
	chilli::ServiceModule::m_hServiceStatus = RegisterServiceCtrlHandler(chilli::ServiceModule::m_szServiceName, ServiceCtrlHandler);
	if (chilli::ServiceModule::m_hServiceStatus == NULL)
	{
		LOG4CPLUS_ERROR(log,"ServiceCtrlHandler not installed");
		return;
	}
	chilli::ServiceModule::SetServiceStatus(SERVICE_START_PENDING);
	//执行你自己的代码
	stopEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
	chilli::App::Start();

	chilli::ServiceModule::SetServiceStatus(SERVICE_RUNNING);
	WaitForSingleObject(stopEvent,INFINITE);
	chilli::App::Stop();
	LOG4CPLUS_TRACE(log, __FUNCTION__ << " end.");
	SetEvent(stopEvent);
}

void chilli::ServiceModule::Stop()
{
	SetEvent(stopEvent);
	WaitForSingleObject(stopEvent,INFINITE);
	CloseHandle(stopEvent);
}

void WINAPI chilli::ServiceModule::ServiceCtrlHandler(DWORD  dwOpcode)
{
	LOG4CPLUS_TRACE(log, __FUNCTION__ << " start.");	
	switch (dwOpcode)
	{
	case SERVICE_CONTROL_STOP:
	case SERVICE_CONTROL_SHUTDOWN:
		chilli::ServiceModule::SetServiceStatus(SERVICE_STOP_PENDING);
		Stop();
		chilli::ServiceModule::SetServiceStatus(SERVICE_STOPPED);
		break;
	case SERVICE_CONTROL_PAUSE:
		break;
	case SERVICE_CONTROL_CONTINUE:
		break;
	case SERVICE_CONTROL_INTERROGATE:
		break;
	default:
		LOG4CPLUS_WARN(log,"Bad service request:" << dwOpcode);
	}

	LOG4CPLUS_TRACE(log, __FUNCTION__ << " end.");
}