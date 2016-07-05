#pragma once

#ifndef _CHILLI_HEADER_
#define _CHILLI_HEADER_
#include <string>
#include <vector>

namespace chilli
{
	namespace model{
		class ProcessModule;
		typedef std::shared_ptr<ProcessModule> ProcessModulePtr;
	}
	class App
	{
	public:
		static void AppInit(void);
		static void Start();
		static void Stop();
		static bool LoadConfig(const std::string & strConfigFile);
	private:
		static std::string strFileDir;
		static std::string strFileNameNoExtension;
		static std::vector<model::ProcessModulePtr> m_Modules;
	};
}//end namespace KeygoeAdapter

void ConsoleLoop();
void CoreRuntimeLoop(int bg);
BOOL WINAPI ConsoleHandler(DWORD msgType);
void SignalHandler(int  sig);

#endif

