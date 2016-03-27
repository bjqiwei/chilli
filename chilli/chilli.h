#pragma once

#ifndef _CHILLI_HEADER_
#define _CHILLI_HEADER_


namespace chilli
{
	class App
	{
	public:
		static void AppInit(void);
		static void Start();
		static void Stop();
		static bool LoadConfig(void);
	private:
		static std::string strConfigFile;
		static std::string strFileDir;
		static std::string strFileNameNoExtension;
	};
}//end namespace KeygoeAdapter

void ConsoleLoop();
void CoreRuntimeLoop(int bg);
BOOL WINAPI ConsoleHandler(DWORD msgType);
void SignalHandler(int  sig);

#endif

