// ShDev.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <tchar.h>
#include "ServiceModule.h"
#include "chilli.h"
#include "signal.h"
#include "ACD\ACDModule.h"
#include "Sh/ShDevModule.h"
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>

using namespace  std;
using namespace log4cplus;


chilli::ServiceModule * _ServiceModule =NULL;
chilli::ShDev::ShDevModule _deviceSH;
chilli::IVR::IVRModule _IVR;
chilli::ACD::ACDModule _ACD;

BOOL WINAPI ConsoleHandler(DWORD msgType)
{
	static log4cplus::Logger log = log4cplus::Logger::getInstance("chilli.ConsoleHandler");
	LOG4CPLUS_INFO(log,"console handler encounter a signal "<<msgType);
	switch(msgType)
	{
	case CTRL_C_EVENT:
	case CTRL_BREAK_EVENT:
	case CTRL_CLOSE_EVENT:
	case CTRL_SHUTDOWN_EVENT:
	case CTRL_LOGOFF_EVENT:
		chilli::App::CoreDestroy();
		chilli::App::running = 0;
	return FALSE;
	default: return TRUE;
	}
}
void SignalHandler(int  sig)
{
	static log4cplus::Logger log = log4cplus::Logger::getInstance("ShCTI.Service");
	LOG4CPLUS_INFO(log,"encounter a signal "<<sig);
	switch(sig)
	{
	case SIGILL:
	case SIGINT:
	case SIGTERM:
		chilli::App::CoreDestroy();
		chilli::App::running = 0;
	default:break;
	}
}
void WINAPI ServiceCtrlHandler(DWORD  dwOpcode)
{
	static log4cplus::Logger log = log4cplus::Logger::getInstance("ShCTI.Service");
	switch (dwOpcode)
	{
	case SERVICE_CONTROL_STOP:
		_ServiceModule->SetServiceStatus(SERVICE_STOP_PENDING);
		chilli::App::CoreDestroy();
		chilli::App::running = 0;
		_ServiceModule->SetServiceStatus(SERVICE_STOPPED);
		break;
	case SERVICE_CONTROL_PAUSE:
		break;
	case SERVICE_CONTROL_CONTINUE:
		break;
	case SERVICE_CONTROL_INTERROGATE:
		break;
	case SERVICE_CONTROL_SHUTDOWN:
		break;
	default:
		LOG4CPLUS_WARN(log,"Bad service request");
	}
}

void WINAPI ServiceMain(DWORD  dwArgc, LPTSTR* lpszArgv)
{
	// Register the control request handler
	static log4cplus::Logger log = log4cplus::Logger::getInstance("chilli.Service");
	_ServiceModule->m_hServiceStatus = RegisterServiceCtrlHandler(_ServiceModule->m_szServiceName, ServiceCtrlHandler);
	if (_ServiceModule->m_hServiceStatus == NULL)
	{
		LOG4CPLUS_ERROR(log,"Handler not installed");
		return;
	}
	_ServiceModule->SetServiceStatus(SERVICE_START_PENDING);

	_ServiceModule->m_status.dwWin32ExitCode = S_OK;
	_ServiceModule->m_status.dwCheckPoint = 0;
	_ServiceModule->m_status.dwWaitHint = 0;

	//执行你自己的代码
	if (chilli::App::CoreInit())
	{
		_ServiceModule->SetServiceStatus(SERVICE_RUNNING);
		chilli::App::Run();
	}
	else
	{
		_ServiceModule->SetServiceStatus(SERVICE_STOPPED);
		LOG4CPLUS_ERROR(log,"Service stopped");
	}
	LOG4CPLUS_INFO(log,"Service stopped");
}
int main(int argc, char* argv[])
{
	chilli::App::AppInit();

	log4cplus::initialize();
	log4cplus::helpers::LogLog::getLogLog()->setInternalDebugging(true);
	log4cplus::PropertyConfigurator::doConfigure("log4cplus.properties");
	static log4cplus::Logger log = log4cplus::Logger::getInstance("chilli");

	try
	{
		
		LOG4CPLUS_INFO(log,"Entering main()...");
		_ServiceModule = new chilli::ServiceModule();
		int  x;

		char opts_str[1024] = "";
		char *local_argv[512] = { 0 };
		int local_argc = argc;
		char *arg_argv[128] = { 0 };
		
		for (x = 0; x < argc; x++) {
			local_argv[x] = argv[x];
		}
		for (x = 1; x < local_argc; x++) {
			if (strlen(local_argv[x])== 0)
				continue;

			if (x == 1 && !strcmp(local_argv[x], "-service")) {
				/* New installs service  */
				LOG4CPLUS_INFO(log,"Command parameter is service,registerserver begin...");
				return _ServiceModule->RegisterServer(true);
			}

			else if (x == 1 && !strcmp(local_argv[x], "-install")) {
				/* New install service*/
				LOG4CPLUS_INFO(log,"Command parameter is install,registerserver begin...");
				return _ServiceModule->RegisterServer(true);
			}

			else if (x == 1 && !strcmp(local_argv[x], "-UnregServer")) {
				/*uninstall service*/
				LOG4CPLUS_INFO(log,"Command parameter is UnregServer,unregister server begin...");
				return _ServiceModule->UnregisterServer();
			}

			else if (x == 1 && !strcmp(local_argv[x], "-uninstall")) {
				/*uninstall service*/
				LOG4CPLUS_INFO(log,"Command parameter is uninstall,unregister server begin...");
				return _ServiceModule->UnregisterServer();
			}
			else if (x == 1 && !strcmp(local_argv[x], "-startservice")) {
				/*startup by service manager*/
				LOG4CPLUS_INFO(log,"Command parameter is startservice,start server begin...");
				_ServiceModule->m_bService = true;
			}
		}

		signal(SIGTERM, SignalHandler);
		signal(SIGILL, SignalHandler);

		if (_ServiceModule->m_bService)
		{
			// 如果是以服务程序启动
			_ServiceModule->Init(_T("chilli"));

			SERVICE_TABLE_ENTRY st[] =
			{
				{ _ServiceModule->m_szServiceName, ServiceMain },
				{ NULL, NULL }
			};
			if (_ServiceModule->m_bService && !::StartServiceCtrlDispatcher(st))
			{
				LOG4CPLUS_DEBUG(log,"error startup as  a console app with a -startservice...");
				_ServiceModule->m_bService = FALSE;
			}
			LOG4CPLUS_DEBUG(log,"ServiceMain Exiting...");
			return 0;
		}

		//在控制台方式下运行
		SetConsoleCtrlHandler(ConsoleHandler, TRUE);
		chilli::App::CoreInit();
		chilli::App::Run();
		chilli::App::CoreRuntimeLoop(0);

	}
	catch (std::exception & e)
	{
		LOG4CPLUS_FATAL(log, LOG4CPLUS_TEXT("Exception occured..." ));
		LOG4CPLUS_FATAL(log,e.what());
	}

	LOG4CPLUS_INFO(log,"Exiting main()...");
	// When we get here, the service has been stopped
	int nExitCode = _ServiceModule->m_status.dwWin32ExitCode;
	delete _ServiceModule;
	return nExitCode;
}
helper::xml::CXmlDocumentPtr chilli::App::_docPtr = NULL;
volatile int chilli::App::running = 0;
std::string chilli::App::strFileDir = "";
std::string chilli::App::strFileNameNoExtension = "";
chilli::App::App()
{
}


chilli::App::~App()
{
}

bool chilli::App::CoreInit(void)
{
	return chilli::App::ReadXMLConfig();
}


void chilli::App::CoreDestroy(void)
{
	log4cplus::Logger log = log4cplus::Logger::getInstance("chilli");
	LOG4CPLUS_WARN(log,"chilli::App::CoreDestroy");
}


void chilli::App::AppInit(void)
{
	char szFilePath[_MAX_PATH];

	::GetModuleFileName(NULL, szFilePath, _MAX_PATH);
	std::string strFilePath = szFilePath;

	App::strFileDir = strFilePath.substr(0,strFilePath.find_last_of('\\')+1);
	App::strFileNameNoExtension = strFilePath.substr(strFilePath.find_last_of('\\')+1,strFilePath.find_last_of('.')-strFilePath.find_last_of('\\')-1);
	::SetCurrentDirectory(App::strFileDir.c_str());
}


bool chilli::App::ReadXMLConfig(void)
{
	bool bResult = true;
	std::string strXmlFile;
	static log4cplus::Logger log = log4cplus::Logger::getInstance("chilli");
	try
	{
		strXmlFile = strFileNameNoExtension+".xml";
		_docPtr = xmlParseFile(strXmlFile.c_str());
		if (!_docPtr._xDocPtr)
		{
			LOG4CPLUS_ERROR(log, "Document not parsed successfully."); 
			throw exception( "Document not parsed successfully."); 
		}
	}
	catch (...)
	{
		LOG4CPLUS_ERROR(log, "An error occurred during parsing\n ");
		throw ;
	}
	LOG4CPLUS_INFO(log," read xml config "<< strXmlFile << "  is finished.");
	return bResult;
}


int chilli::App::Run(void)
{
	_deviceSH.Init(xmlDocGetRootElement(_docPtr._xDocPtr));
	_IVR.Init(xmlDocGetRootElement(_docPtr._xDocPtr));
	_ACD.Init(xmlDocGetRootElement(_docPtr._xDocPtr));
	_deviceSH.Start();
	_IVR.Start();
	_ACD.Start();
	chilli::App::running = 1;
	return 0;
}

void chilli::App::ConsoleLoop()
{
	std::string strCmd;
	static log4cplus::Logger log = log4cplus::Logger::getInstance("chilli.ConsoleLoop");
	while (running && std::cin>>strCmd && strCmd.compare("quit") != 0){
		if (strCmd.compare("reloadxml") == 0)
		{
			CoreInit();
			_deviceSH.reloadConfig(xmlDocGetRootElement(_docPtr._xDocPtr));
			//_IVR.reloadConfig(xmlDocGetRootElement(_docPtr._xDocPtr));
			//_ACD.reloadConfig(xmlDocGetRootElement(_docPtr._xDocPtr));
		}
		else
		{
			LOG4CPLUS_WARN(log,"Unrecognized command:" <<strCmd);
		}
	}
	_deviceSH.Close();
	_IVR.Close();
	_ACD.Close();

}

void chilli::App::CoreRuntimeLoop(int bg)
{
	ConsoleLoop();
}


