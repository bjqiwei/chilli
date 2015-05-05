#pragma once

#ifndef _CHILLI_HEADER_
#define _CHILLI_HEADER_
#include <common/xmlHelper.h>


namespace chilli
{
	class App
	{
	public:
		App(void);
		virtual ~App(void);
		static void AppInit(void);
		static int Run(void);
		static void CoreRuntimeLoop(int bg);
	private:
		static bool ReadXMLConfig(void);
		static void ConsoleLoop();
		static helper::xml::CXmlDocumentPtr _docPtr;
		static std::string strFileDir;
		static std::string strFileNameNoExtension;
	};
}//end namespace KeygoeAdapter


BOOL WINAPI ConsoleHandler(DWORD msgType);
void SignalHandler(int  sig);
void WINAPI ServiceCtrlHandler(DWORD  dwOpcode);
void WINAPI ServiceMain(DWORD  dwArgc, LPTSTR* lpszArgv);
#endif

