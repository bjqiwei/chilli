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


chilli::ShDev::ShDevModule _deviceSH;
chilli::model::ACDModule _ACD;

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
		chilli::App::Stop();
	return TRUE;
	default: return FALSE;
	}
}
void SignalHandler(int  sig)
{
	static log4cplus::Logger log = log4cplus::Logger::getInstance("chilli.SignalHandler");
	LOG4CPLUS_INFO(log,"encounter a signal "<<sig);
	switch(sig)
	{
	case SIGILL:
	case SIGINT:
	case SIGTERM:
		chilli::App::Stop();
	default:break;
	}
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
				return chilli::ServiceModule::RegisterServer(true);
			}

			else if (x == 1 && !strcmp(local_argv[x], "-install")) {
				/* New install service*/
				LOG4CPLUS_INFO(log,"Command parameter is install,registerserver begin...");
				return chilli::ServiceModule::RegisterServer(true);
			}

			else if (x == 1 && !strcmp(local_argv[x], "-UnregServer")) {
				/*uninstall service*/
				LOG4CPLUS_INFO(log,"Command parameter is UnregServer,unregister server begin...");
				return chilli::ServiceModule::UnregisterServer();
			}

			else if (x == 1 && !strcmp(local_argv[x], "-uninstall")) {
				/*uninstall service*/
				LOG4CPLUS_INFO(log,"Command parameter is uninstall,unregister server begin...");
				return chilli::ServiceModule::UnregisterServer();
			}
			else if (x == 1 && !strcmp(local_argv[x], WINSERVERPARAMETER)) {
				/*startup by service manager*/
				LOG4CPLUS_INFO(log,"Command parameter is startservice,start server begin...");
				chilli::ServiceModule::m_bService = true;
			}
		}

		signal(SIGTERM, SignalHandler);
		signal(SIGILL, SignalHandler);

		if (chilli::ServiceModule::m_bService)
		{
			// 如果是以服务程序启动
			chilli::ServiceModule::Init();
			SERVICE_TABLE_ENTRY st[] =
			{
				{ chilli::ServiceModule::m_szServiceName, chilli::ServiceModule::Start },
				{ NULL, NULL }
			};
			if (chilli::ServiceModule::m_bService && !::StartServiceCtrlDispatcher(st))
			{
				LOG4CPLUS_DEBUG(log,"error startup as  a console app with a -startservice...");
				chilli::ServiceModule::m_bService = FALSE;
			}
			LOG4CPLUS_DEBUG(log,"Service Exiting...");
			return 0;
		}

		//在控制台方式下运行
		SetConsoleCtrlHandler(ConsoleHandler, TRUE);
		//chilli::App::CoreInit();
		chilli::App::Start();
		chilli::App::CoreRuntimeLoop(0);

	}
	catch (std::exception & e)
	{
		LOG4CPLUS_FATAL(log, LOG4CPLUS_TEXT("Exception occured..." ));
		LOG4CPLUS_FATAL(log,e.what());
	}

	LOG4CPLUS_INFO(log,"Exiting main()...");
	// When we get here, the service has been stopped
	int nExitCode = 0;
	return nExitCode;
}
helper::xml::CXmlDocumentPtr chilli::App::_docPtr = NULL;
std::string chilli::App::strFileDir = "";
std::string chilli::App::strFileNameNoExtension = "";
chilli::App::App()
{
}


chilli::App::~App()
{
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
	//_ACD.Init(xmlDocGetRootElement(_docPtr._xDocPtr));
	_deviceSH.Start();
	_ACD.Start();
	return 0;
}

void chilli::App::ConsoleLoop()
{
	std::string strCmd;
	static log4cplus::Logger log = log4cplus::Logger::getInstance("chilli.ConsoleLoop");
	while ( std::cin>>strCmd && strCmd.compare("quit") != 0){
		LOG4CPLUS_TRACE(log, "msg");
		if (strCmd.compare("reloadxml") == 0)
		{
			//CoreInit();
			//_deviceSH.reloadConfig(xmlDocGetRootElement(_docPtr._xDocPtr));
			//_IVR.reloadConfig(xmlDocGetRootElement(_docPtr._xDocPtr));
			//_ACD.reloadConfig(xmlDocGetRootElement(_docPtr._xDocPtr));
		}
		else
		{
			LOG4CPLUS_WARN(log,"Unrecognized command:" <<strCmd);
		}
	}

}

void chilli::App::CoreRuntimeLoop(int bg)
{
	ConsoleLoop();
}

void chilli::App::Start()
{
	Run();
}

void chilli::App::Stop()
{

}
