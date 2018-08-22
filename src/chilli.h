#pragma once
#include <string>

namespace chilli
{

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
	};
}//end namespace KeygoeAdapter

#define UNI_COPYRIGHT "Copyright 2008-2017 Arsen Chaloyan"
#define UNI_LICENSE ""


