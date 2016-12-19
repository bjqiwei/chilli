#ifndef _CHILLI_FREESWITCHMODULE_HEADER_
#define _CHILLI_FREESWITCHMODULE_HEADER_
#include <log4cplus/logger.h>
#include "../model/ProcessModule.h"
#include <thread>

namespace chilli{
namespace FreeSwitch{

	class FreeSwtichModule :public model::ProcessModule
	{
	public:
		FreeSwtichModule();
		virtual ~FreeSwtichModule(void);
		virtual int Start() override;
		virtual int Stop() override;
		virtual bool LoadConfig(const std::string & config) override;
		virtual const model::ExtensionMap & GetExtension() override;
	private:
		log4cplus::Logger log;
		model::ExtensionMap m_Extension;
		std::thread m_Thread;
		std::atomic<bool> bRunning = false;
		std::string m_Host;
		int m_Port = 0;
		std::string m_User;
		std::string m_Password;
		void ConnectFS();
	};

}
}
#endif // end header
