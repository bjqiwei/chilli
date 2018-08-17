// ShDev.cpp : Defines the entry point for the console application.
//

#include "chilli.h"
#include <iostream>
#ifdef WIN32
#include <direct.h>
#endif
#include <apr.h>
#include <apr_getopt.h>
#include <apr_general.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include "tinyxml2/tinyxml2.h"

#include "ACD/ACDModule.h"
#include "Sh/ShDevModule.h"
#include "Agent/AgentModule.h"
#include "Group/GroupModule.h"
#include "FreeSWITCH/FreeSwitchModule.h"
#include "IVR/IVRModule.h"
#include "Avaya/TSAPIModule.h"
#include "mysql/MySqlModule.h"
#include "EventReport/EventReportModule.h"
#include "Call/CallModule.h"

#define _STRVERSION(str) #str
#define STRVERSION(str) _STRVERSION(str)
static const char* appversion = STRVERSION(APPVERSION);

#define  FREESWITCHNODE "FreeSwitch"
#define  AVAYANODE      "Avaya"
#define  AGENTNODE      "Agents"
#define  GROUPS         "Groups"
#define  MYSQL          "MySql"
#define  EVENTREPORT	"EventReport"
#define  CALL			"Call"


typedef struct {
	const char   *root_dir_path;
	bool          foreground;
	bool          cmd_line;
#ifdef WIN32
	uint32_t      install;
	const char   *svcname;
#endif
} server_options_t;

#ifdef WIN32
bool uni_service_run(const char *name, uint32_t install = 0);
#endif

bool uni_daemon_run(bool detach);
bool uni_cmdline_run();

static void usage()
{
	printf(
		"\n"
		" * " UNI_COPYRIGHT "\n"
		" *\n"
		UNI_LICENSE "\n"
		"\n"
		"Usage:\n"
		"\n"
		"  chilli server [options]\n"
		"\n"
		"  Available options:\n"
		"\n"
#ifdef WIN32
		"   -i [--install]           : install a Windows service.\n"
		"\n"
		"   -u [--uninstall]           : uninstall Windows service.\n"
		"\n"
		"   -s [--service]           : Run as a Windows service.\n"
		"\n"
		"   -n [--name] svcname      : Set the service name (default: chilli)\n"
		"\n"
#else
		"   -d [--daemon]            : Run as a daemon.\n"
		"\n"
#endif
		"   -w [--without-cmdline]   : Run without command-line.\n"
		"\n"
		"   -v [--version]           : Show the version.\n"
		"\n"
		"   -h [--help]              : Show the help.\n"
		"\n");
}

static bool options_load(server_options_t *options, int argc, const char * const *argv, apr_pool_t *pool)
{
	apr_status_t rv;
	apr_getopt_t *opt = NULL;
	int optch;
	const char *optarg;

	const apr_getopt_option_t opt_option[] = {
		/* long-option, short-option, has-arg flag, description */
		{ "root-dir",        'r', TRUE,  "path to root dir" },         /* -r arg or --root-dir arg */
#ifdef WIN32
		{ "install",         'i', FALSE, "install service" },           /* -s or --service */
		{ "uninstall",       'u', FALSE, "uninstall service" },           /* -s or --service */
		{ "service",         's', FALSE, "run as service" },           /* -s or --service */
		{ "name",            'n', TRUE,  "service name" },             /* -n or --name arg */
#else
		{ "daemon",          'd', FALSE, "start as daemon" },          /* -d or --daemon */
#endif
		{ "without-cmdline", 'w', FALSE, "run without command-line" }, /* -w or --without-cmdline */
		{ "version",         'v', FALSE, "show version" },             /* -v or --version */
		{ "help",            'h', FALSE, "show help" },                /* -h or --help */
		{ NULL, 0, 0, NULL },                                          /* end */
	};

	rv = apr_getopt_init(&opt, pool, argc, argv);
	if (rv != APR_SUCCESS) {
		return FALSE;
	}

	/* reset the options */
	options->root_dir_path = nullptr;
	options->foreground = true;
	options->cmd_line = true;
#ifdef WIN32
	options->install = 0;
	options->svcname = nullptr;
#endif

	while ((rv = apr_getopt_long(opt, opt_option, &optch, &optarg)) == APR_SUCCESS) {
		switch (optch) {
		case 'r':
			options->root_dir_path = optarg;
			break;
#ifdef WIN32
		case 'i':
			options->install = 1;
			break;
		case 'u':
			options->install = 2;
			break;
		case 's':
			options->foreground = false;
			break;
		case 'n':
			options->svcname = optarg;
			break;
#else
		case 'd':
			options->foreground = FALSE;
			break;
#endif
		case 'w':
			options->cmd_line = false;
			break;
		case 'v':
			printf("%s", appversion);
			return FALSE;
		case 'h':
			usage();
			return FALSE;
		}
	}

	if (rv != APR_EOF) {
		usage();
		return FALSE;
	}

	return TRUE;
}

int main(int argc, char* argv[])
{
	apr_pool_t *pool;
	server_options_t options;

	/* APR global initialization */
	if (apr_initialize() != APR_SUCCESS) {
		std::cout << "apr_initialize";
		apr_terminate();
		return 0;
	}

	/* create APR pool */
	apr_pool_create(&pool,nullptr);
	if (!pool) {
		std::cout << "apr_pool_create";
		apr_terminate();
		return 0;
	}


	/* load options */
	if (options_load(&options, argc, argv, pool) != TRUE) {
		apr_pool_destroy(pool);
		apr_terminate();
		return 0;
	}

	chilli::App::AppInit();
	log4cplus::initialize();

#ifdef DEBUG
	log4cplus::helpers::LogLog::getLogLog()->setInternalDebugging(true);
#endif
	log4cplus::PropertyConfigurator::doConfigure("conf/log4cplus.properties");
	log4cplus::Logger log = log4cplus::Logger::getInstance("chilli");

	if (options.foreground == true) {
#ifdef WIN32
		if (options.install != 0){

			uni_service_run(options.svcname, options.install);
		}
		else 
#endif
		if (options.cmd_line == true) {
			/* run command line */
			uni_cmdline_run();
		}
		else {
			/* run as daemon */
			uni_daemon_run(FALSE);
		}
	}
#ifdef WIN32
	else {
		/* run as windows service */
		uni_service_run(options.svcname, 0);
	}
#else
	else {
		/* run as daemon */
		uni_daemon_run(TRUE);
	}
#endif

	/* destroy APR pool */
	apr_pool_destroy(pool);
	/* APR global termination */
	apr_terminate();

	// When we get here, the service has been stopped
	int nExitCode = 0;
	return nExitCode;
}

std::string chilli::App::strFileDir;
std::string chilli::App::strFileNameNoExtension;


void chilli::App::AppInit(void)
{
	//获取应用程序的绝对路径
	const uint32_t max_path = 260;
	static char path[max_path + 64] = "";
#ifdef WIN32
		::GetModuleFileName(::GetModuleHandle(NULL), path, max_path);
		assert(strrchr(path, '\\'));
		*strrchr(path, '.') = 0;
		strFileNameNoExtension = strrchr(path, '\\') + 1;
		*strrchr(path, '\\') = 0;
#else //_LINUX
		char buff[max_path + 64] = "";
		sprintf(buff, "/proc/%d/exe", getpid());

		getcwd(path, max_path);
		readlink(buff, path, max_path);

		assert(strrchr(path, '/'));
		if(strrchr(path, '.')) *strrchr(path, '.') = 0;
		strFileNameNoExtension = strrchr(path, '/') + 1;
		*strrchr(path, '/') = 0;
#endif

		strFileDir = path;
#ifdef WIN32
		_chdir(path);
#else
		chdir(path);
#endif

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

void chilli::App::Start()
{
	AppInit();
	log4cplus::initialize();
	static log4cplus::ConfigureAndWatchThread logconfig("./conf/log4cplus.properties", 10 * 1000);
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
