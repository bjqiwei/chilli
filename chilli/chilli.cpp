// ShDev.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <tchar.h>
#include "ServiceModule.h"
#include "chilli.h"
#include "signal.h"
#include "ACD/ACDModule.h"
#include "Sh/ShDevModule.h"
#include "Agent/AgentModule.h"
#include "freeswitch/FreeSwitchModule.h"
#include "IVR/IVRModule.h"
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include "tinyxml2/tinyxml2.h"



chilli::ShDev::ShDevModule _deviceSH;
chilli::ACD::ACDModule _ACD;
chilli::IVR::IVRModule _IVR;
chilli::Agent::AgentModule _Agent;

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
		{
		// 会使std::cin 返回false;
		//chilli::App::Stop();
		return TRUE;
		};
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

	LOG4CPLUS_INFO(log,"Entering main()...");
	try
	{
		
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
		}
		else{

			//在控制台方式下运行
			SetConsoleCtrlHandler(ConsoleHandler, TRUE);
			chilli::App::Start();
			CoreRuntimeLoop(0);
			chilli::App::Stop();
			
		}

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

std::string chilli::App::strFileDir;
std::string chilli::App::strFileNameNoExtension;
std::vector<chilli::model::ProcessModulePtr> chilli::App::m_Modules;


void chilli::App::AppInit(void)
{
	char szFilePath[_MAX_PATH];

	::GetModuleFileName(NULL, szFilePath, _MAX_PATH);
	std::string strFilePath = szFilePath;

	App::strFileDir = strFilePath.substr(0,strFilePath.find_last_of('\\')+1);
	App::strFileNameNoExtension = strFilePath.substr(strFilePath.find_last_of('\\')+1,strFilePath.find_last_of('.')-strFilePath.find_last_of('\\')-1);
	::SetCurrentDirectory(App::strFileDir.c_str());
}


bool chilli::App::LoadConfig(const std::string & strConfigFile)
{
	bool bResult = true;
	static log4cplus::Logger log = log4cplus::Logger::getInstance("chilli");
	LOG4CPLUS_INFO(log, "config file: " << strConfigFile);
	_deviceSH.LoadConfig(strConfigFile);
	_ACD.LoadConfig(strConfigFile);
	_IVR.LoadConfig(strConfigFile);
	_Agent.LoadConfig(strConfigFile);

	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if (config.LoadFile(strConfigFile.c_str()) != XMLError::XML_SUCCESS)
	{
		LOG4CPLUS_ERROR(log, "load config file error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}
	if (tinyxml2::XMLElement *eConfig = config.FirstChildElement("Config")){
		tinyxml2::XMLElement * e = eConfig->FirstChildElement();
		while( e != nullptr)
		{
#define  FREESWITCHNODE "FreeSwitch"
			std::string nodeName = e->Value() ? e->Value() : "";
			if (nodeName == FREESWITCHNODE){
				model::ProcessModulePtr freeswtich(new chilli::FreeSwitch::FreeSwtichModule());
				XMLPrinter printer;
				e->Accept(&printer);
				freeswtich->LoadConfig(printer.CStr());
				m_Modules.push_back(freeswtich);
			}
		
			e = e->NextSiblingElement();
		}
#undef FREESWITCHNODE

	}
	else {
		LOG4CPLUS_ERROR(log, "config file missing Config element.");
		return false;
	}

	return bResult;
}


void ConsoleLoop()
{
	std::string strCmd;
	static log4cplus::Logger log = log4cplus::Logger::getInstance("chilli.ConsoleLoop");
	while ( std::cin>>strCmd ){
		LOG4CPLUS_TRACE(log, "command:" << strCmd);
		if (strCmd == "quit"){
			break;
		}
		else if (strCmd == "loadconfig"){
			//std::string strConfigFile = chilli::App::strFileNameNoExtension + ".xml";
			//chilli::App::LoadConfig(strConfigFile);
		}
		else{
			LOG4CPLUS_WARN(log,"Unrecognized command:" <<strCmd);
		}
	}
}

void CoreRuntimeLoop(int bg)
{
	ConsoleLoop();
}

void chilli::App::Start()
{
	static log4cplus::Logger log = log4cplus::Logger::getInstance("chilli");
	LOG4CPLUS_TRACE(log, __FUNCTION__ << " start.");
	std::string strConfigFile = strFileNameNoExtension + ".xml";
	LoadConfig(strConfigFile);
	_deviceSH.Start();
	_ACD.Start();
	_IVR.Start();
	_Agent.Start();
	for (auto it:m_Modules){
		it->Start();
	}
	LOG4CPLUS_TRACE(log, __FUNCTION__ << " end.");

}

void chilli::App::Stop()
{
	static log4cplus::Logger log = log4cplus::Logger::getInstance("chilli");
	LOG4CPLUS_TRACE(log, __FUNCTION__ << " start.");
	_deviceSH.Stop();
	_ACD.Stop();
	_IVR.Stop();
	_Agent.Stop();
	for (auto it : m_Modules){
		it->Stop();
	}
	m_Modules.clear();
	LOG4CPLUS_TRACE(log, __FUNCTION__ << " end.");

}
