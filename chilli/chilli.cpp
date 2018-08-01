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
#include "Group/GroupModule.h"
#include "freeswitch/FreeSwitchModule.h"
#include "IVR/IVRModule.h"
#include "Avaya/TSAPIModule.h"
#include "mysql/MySqlModule.h"
#include "EeventReport/EventReportModule.h"
#include "Call/CallModule.h"
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include "tinyxml2/tinyxml2.h"

#define  FREESWITCHNODE "FreeSwitch"
#define  AVAYANODE      "Avaya"
#define  AGENTNODE      "Agents"
#define  GROUPS         "Groups"
#define  MYSQL          "MySql"
#define  EVENTREPORT	"EventReport"
#define  CALL			"Call"

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
#ifdef DEBUG
	log4cplus::helpers::LogLog::getLogLog()->setInternalDebugging(true);
#endif
	log4cplus::PropertyConfigurator::doConfigure("conf/log4cplus.properties");
	log4cplus::Logger log = log4cplus::Logger::getInstance("chilli");

	std::string parameter;
	if (argc > 1 && argv[1]) {
		const char * para = argv[1];
		while (*para && !isalpha(*para)) {
			para++;
		}
		if (para)
			parameter = para;
	}

	if (parameter == "service") {
		/* New installs service  */
		LOG4CPLUS_INFO(log, "Command parameter is service,registerserver begin...");
		return chilli::ServiceModule::RegisterServer(true);
	}

	else if (parameter == "install") {
		/* New install service*/
		LOG4CPLUS_INFO(log, "Command parameter is install,registerserver begin...");
		return chilli::ServiceModule::RegisterServer(true);
	}

	else if (parameter == "UnregServer") {
		/*uninstall service*/
		LOG4CPLUS_INFO(log, "Command parameter is UnregServer,unregister server begin...");
		return chilli::ServiceModule::UnregisterServer();
	}

	else if (parameter == "uninstall") {
		/*uninstall service*/
		LOG4CPLUS_INFO(log, "Command parameter is uninstall,unregister server begin...");
		return chilli::ServiceModule::UnregisterServer();
	}
	else if (parameter == "version" || parameter == "v") {
		std::cout << VERSION << std::endl;
		return 0;
	}
	else if (parameter == "startservice" || parameter == "start") {
		/*startup by service manager*/
		LOG4CPLUS_INFO(log, "Command parameter is startservice,start server begin...");
		chilli::ServiceModule::m_bService = true;
	}


	signal(SIGTERM, SignalHandler);
	signal(SIGILL, SignalHandler);

	if (chilli::ServiceModule::m_bService)
	{
		// 如果是以服务程序启动
#ifdef __linux__

		pid_t pid;
		/* 屏蔽一些有关控制终端操作的信号
		* 防止在守护进程没有正常运转起来时，因控制终端受到干扰退出或挂起
		* */

		signal(SIGINT, SIG_IGN);// 终端中断  
		signal(SIGHUP, SIG_IGN);// 连接挂断  
		signal(SIGQUIT, SIG_IGN);// 终端退出  
		signal(SIGPIPE, SIG_IGN);// 向无读进程的管道写数据  
		signal(SIGTTOU, SIG_IGN);// 后台程序尝试写操作  
		signal(SIGTTIN, SIG_IGN);// 后台程序尝试读操作  
		signal(SIGTERM, SIG_IGN);// 终止  

		pid = fork();
		if (pid < 0) {
			perror("fork error!");
			exit(1);
		}
		else if (pid > 0) {
			exit(0);
		}

		// [2] create a new session  
		setsid();

		// [3] set current path  

		int fd;
		//[4]将标准输入输出重定向到空设备
		fd = open("/dev/null", O_RDWR, 0);
		if (fd != -1) {
			dup2(fd, STDIN_FILENO);
			dup2(fd, STDOUT_FILENO);
			dup2(fd, STDERR_FILENO);
			if (fd > 2)
				close(fd);
		}
		// [5] umask 0  
		umask(0);
#else
		chilli::ServiceModule::Init();
		SERVICE_TABLE_ENTRY st[] =
		{
			{ chilli::ServiceModule::m_szServiceName, chilli::ServiceModule::Start },
			{ NULL, NULL }
		};
		if (chilli::ServiceModule::m_bService && !::StartServiceCtrlDispatcher(st))
		{
			LOG4CPLUS_DEBUG(log, "error startup as  a console app with a -startservice...");
			chilli::ServiceModule::m_bService = FALSE;
		}
		LOG4CPLUS_DEBUG(log,"Service Exiting...");
		return 0;
#endif
	}

	try
	{
		//在控制台方式下运行
		log4cplus::initialize();
#ifdef DEBUG
		log4cplus::helpers::LogLog::getLogLog()->setInternalDebugging(true);
#endif
		log4cplus::ConfigureAndWatchThread logconfig(LOG4CPLUS_TEXT("conf/log4cplus.properties"), 10 * 1000);

		SetConsoleCtrlHandler(ConsoleHandler, TRUE);

		time_t t;  //秒时间  
		tm* local; //本地时间   
		tm* gmt;   //格林威治时间  
		char buf[128] = { 0 };

		t = time(NULL); //获取目前秒时间  
		local = localtime(&t); //转为本地时间  
		strftime(buf, 64, "%Y-%m-%d %H:%M:%S", local);
		std::string timeoutstr = "2019-01-01 00:00:00";
		//std::cout << buf << std::endl;
		if (buf > timeoutstr){
			LOG4CPLUS_ERROR(log, LOG4CPLUS_TEXT("timeout..."));
			return 1;
		}

		chilli::App::Start();
		CoreRuntimeLoop(0);
		chilli::App::Stop();

	}
	catch (std::exception & e)
	{
		LOG4CPLUS_FATAL(log, LOG4CPLUS_TEXT("Exception occured..." ));
		LOG4CPLUS_FATAL(log,e.what());
	}

	// When we get here, the service has been stopped
	int nExitCode = 0;
	return nExitCode;
}

std::string chilli::App::strFileDir;
std::string chilli::App::strFileNameNoExtension;


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
	log4cplus::Logger log = log4cplus::Logger::getInstance("chilli");
	LOG4CPLUS_INFO(log, "config file: " << strConfigFile);

	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if (config.LoadFile(strConfigFile.c_str()) != XMLError::XML_SUCCESS)
	{
		LOG4CPLUS_ERROR(log, "load config file error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}
	if (tinyxml2::XMLElement *eConfig = config.FirstChildElement("Config")){
		tinyxml2::XMLElement * e = eConfig->FirstChildElement();
		while (e != nullptr)
		{
			std::string nodeName = e->Name() ? e->Name() : "";
			const char * modelid = e->Attribute("id");
			modelid = modelid ? modelid : "";

			if (nodeName == FREESWITCHNODE) {
				model::ProcessModulePtr freeswitch(new chilli::FreeSwitch::FreeSwitchModule(modelid));
				XMLPrinter printer;
				e->Accept(&printer);
				freeswitch->LoadConfig(printer.CStr());
				model::ProcessModule::g_Modules.push_back(freeswitch);
			}
			else if (nodeName == AVAYANODE)
			{
				model::ProcessModulePtr tsapi(new chilli::Avaya::TSAPIModule(modelid));
				XMLPrinter printer;
				e->Accept(&printer);
				tsapi->LoadConfig(printer.CStr());
				model::ProcessModule::g_Modules.push_back(tsapi);

			}
			else if (nodeName == AGENTNODE)
			{
				model::ProcessModulePtr agent(new chilli::Agent::AgentModule(modelid));
				XMLPrinter printer;
				e->Accept(&printer);
				agent->LoadConfig(printer.CStr());
				model::ProcessModule::g_Modules.push_back(agent);

			}
			else if (nodeName == GROUPS)
			{
				model::ProcessModulePtr group(new chilli::Group::GroupModule(modelid));
				XMLPrinter printer;
				e->Accept(&printer);
				group->LoadConfig(printer.CStr());
				model::ProcessModule::g_Modules.push_back(group);
			}
			else if (nodeName == MYSQL)
			{
				model::ProcessModulePtr mysql(new chilli::DataBase::MySqlModule(modelid));
				XMLPrinter printer;
				e->Accept(&printer);
				mysql->LoadConfig(printer.CStr());
				model::ProcessModule::g_Modules.push_back(mysql);
			}
			else if (nodeName == EVENTREPORT)
			{
				model::ProcessModulePtr eventreport(new chilli::EventReport::EventReportModule(modelid));
				XMLPrinter printer;
				e->Accept(&printer);
				eventreport->LoadConfig(printer.CStr());
				model::ProcessModule::g_Modules.push_back(eventreport);

			}
			else if (nodeName == CALL)
			{
				model::ProcessModulePtr eventreport(new chilli::Call::CallModule(modelid));
				XMLPrinter printer;
				e->Accept(&printer);
				eventreport->LoadConfig(printer.CStr());
				model::ProcessModule::g_Modules.push_back(eventreport);

			}
			e = e->NextSiblingElement();
		}

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
		else if(strCmd == "...") {
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
	log4cplus::Logger log = log4cplus::Logger::getInstance("chilli");
	LOG4CPLUS_TRACE(log, __FUNCTION__ << " start.");
	std::string strConfigFile = "conf/" + strFileNameNoExtension + ".xml";
	LoadConfig(strConfigFile);

	for (auto & it:model::ProcessModule::g_Modules){
		it->Start();
	}

	LOG4CPLUS_TRACE(log, __FUNCTION__ << " end.");

}

void chilli::App::Stop()
{
	static log4cplus::Logger log = log4cplus::Logger::getInstance("chilli");
	LOG4CPLUS_TRACE(log, __FUNCTION__ << " start.");
	for (auto & it : model::ProcessModule::g_Modules){
		it->Stop();
	}
	model::ProcessModule::g_Modules.clear();
	LOG4CPLUS_TRACE(log, __FUNCTION__ << " end.");

}
