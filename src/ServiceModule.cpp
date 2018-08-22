#include "ServiceModule.h"
#include "chilli.h"
#include <iostream>


bool uni_service_run(const char *name, uint32_t install)
{
	if (install == 1)
		return chilli::ServiceModule::RegisterServer(true) == 0;
	else if (install == 2)
		return chilli::ServiceModule::RegisterServer(false) == 0;
	else {

		chilli::ServiceModule::Init();
		SERVICE_TABLE_ENTRY st[] =
		{
			{ chilli::ServiceModule::m_szServiceName, chilli::ServiceModule::Start },
			{ NULL, NULL }
		};
		if (!::StartServiceCtrlDispatcher(st))
		{
			std::cout << "error startup as  a console app with a service..." << std::endl;
		}
	}

	return true;
}

namespace chilli{

	HANDLE ServiceModule::stopEvent = NULL;
	HANDLE ServiceModule::stopEvented = NULL;
	char ServiceModule::m_szServiceName[256] = SERVICENAME_DEFAULT;
	SERVICE_STATUS_HANDLE ServiceModule::m_hServiceStatus = NULL;
	SERVICE_STATUS ServiceModule::m_status;

	void ServiceModule::Init()
	{		
		//lstrcpy(m_szServiceName,SERVICENAME_DEFAULT);
		
		// set up the initial service status 
		
		m_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
		m_status.dwCurrentState = SERVICE_STOPPED;
		m_status.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
		m_status.dwWin32ExitCode = 0;
		m_status.dwServiceSpecificExitCode = 0;
		m_status.dwCheckPoint = 0;
		m_status.dwWaitHint = 0;
		//LOG4CPLUS_INFO(log,"ServiceModule Init finished,type=SERVICE_WIN32_OWN_PROCESS,state=SERVICE_STOPPED,accepter=SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN,exitcode=0.");
	}

	long ServiceModule::UnregisterServer(void)
	{
		if (IsInstalled()){
			Uninstall();
		}
		return 0;
	}

	long ServiceModule::RegisterServer(bool bService)
	{
		if (IsInstalled()){
			Uninstall();
		}

		if (bService)
		{
			Install();
		}
		return 0;
	}


	bool ServiceModule::Uninstall(void)
	{

		SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

		if (hSCM == NULL)
		{
			DWORD err = GetLastError();
			std::cout << "Couldn't open service manager:" << err << std::endl;
			return false;
		}

		SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_STOP | DELETE);

		if (hService == NULL)
		{
			DWORD err = GetLastError();
			::CloseServiceHandle(hSCM);
			std::cout << "Couldn't open service:" << err << std::endl;
			return false;
		}
		SERVICE_STATUS status;
		::ControlService(hService, SERVICE_CONTROL_STOP, &status);

		bool bDelete = ::DeleteService(hService)?true:false;
		if (!bDelete)
		{
			DWORD err = GetLastError();
			std::cout << "Service could not be deleted errorcode=" << err << std::endl;
		}
		else
		{
			std::cout << "Service Uninstalled." << std::endl;
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
		else{
			DWORD err = GetLastError();
			std::cout << "Couldn't open service manager:" << err << std::endl;
		}

		if (bResult){
			std::cout << "service is already instatlled" << std::endl;
		}
		else{
			std::cout << "service is not instatlled yet" << std::endl;
		}
		return bResult;
	}


	bool ServiceModule::Install(void)
	{

		SERVICE_DESCRIPTION desc;
		desc.lpDescription = SERVICEDESCRIPTION;

		SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if (hSCM == NULL)
		{
			DWORD err = GetLastError();
			std::cout << "Couldn't open service manager:" << err << std::endl;
			return FALSE;
		}

		// Get the executable file path
		TCHAR szFilePath[_MAX_PATH];
		::GetModuleFileName(NULL, szFilePath, _MAX_PATH);
		strcat_s(szFilePath, " ");
		strcat_s(szFilePath,WINSERVERPARAMETER);
		
		std::cout << "servicename (" << m_szServiceName << ")" << std::endl;
		std::cout << " FilePath (" << szFilePath << ")" << std::endl;

		SC_HANDLE hService = ::CreateService(
			hSCM, m_szServiceName, m_szServiceName,
			SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
			SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,
			szFilePath, NULL, NULL, ("RPCSS\0"), NULL, NULL);
	
		if (hService == NULL) {
			DWORD err = GetLastError();
			std::cout << "Error creating chilli service (" << err << ")" << std::endl;
			CloseServiceHandle(hSCM);
			return false;
		}

		std::cout << "service is instatlled" << std::endl;
		/* Set desc, and don't care if it succeeds */
		if (!ChangeServiceConfig2(hService, SERVICE_CONFIG_DESCRIPTION, &desc)) {
			DWORD err = GetLastError();
			std::cout << "chilli installed, but could not set the service description (" << err << ")" << std::endl;
		}

		::CloseServiceHandle(hService);
		::CloseServiceHandle(hSCM);
		return true;

	}


	void ServiceModule::SetServiceStatus(DWORD dwState)
	{
		m_status.dwCurrentState = dwState;
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

	chilli::ServiceModule::m_hServiceStatus = RegisterServiceCtrlHandler(chilli::ServiceModule::m_szServiceName, ServiceCtrlHandler);
	if (chilli::ServiceModule::m_hServiceStatus == NULL)
	{
		std::cout << "ServiceCtrlHandler not installed" << std::endl;
		return;
	}
	chilli::ServiceModule::SetServiceStatus(SERVICE_START_PENDING);
	//执行你自己的代码
	stopEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
	stopEvented = CreateEvent(NULL, FALSE, FALSE, NULL);

	chilli::App::Start();

	chilli::ServiceModule::SetServiceStatus(SERVICE_RUNNING);
	WaitForSingleObject(stopEvent,INFINITE);
	chilli::App::Stop();
	SetEvent(stopEvented);
}

void chilli::ServiceModule::Stop()
{
	SetEvent(stopEvent);
	WaitForSingleObject(stopEvented,INFINITE);
	CloseHandle(stopEvent);
	CloseHandle(stopEvented);
}

void WINAPI chilli::ServiceModule::ServiceCtrlHandler(DWORD  dwOpcode)
{
	
	switch (dwOpcode)
	{
	case SERVICE_CONTROL_STOP:
		//LOG4CPLUS_DEBUG(log, "SERVICE_CONTROL_STOP");
		goto stoping;
	case SERVICE_CONTROL_SHUTDOWN:
		//LOG4CPLUS_DEBUG(log, "SERVICE_CONTROL_SHUTDOWN");
stoping:
		chilli::ServiceModule::SetServiceStatus(SERVICE_STOP_PENDING);
		Stop();
		chilli::ServiceModule::SetServiceStatus(SERVICE_STOPPED);
		break;
	case SERVICE_CONTROL_PAUSE:
		//LOG4CPLUS_DEBUG(log, "SERVICE_CONTROL_PAUSE");
		break;
	case SERVICE_CONTROL_CONTINUE:
		//LOG4CPLUS_DEBUG(log, "SERVICE_CONTROL_CONTINUE");
		break;
	case SERVICE_CONTROL_INTERROGATE:
		//LOG4CPLUS_DEBUG(log, "SERVICE_CONTROL_INTERROGATE");
		break;
	default:
		//LOG4CPLUS_WARN(log, "Bad service request:" << dwOpcode);
		break;
	}

}