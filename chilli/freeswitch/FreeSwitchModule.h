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
		explicit FreeSwtichModule(const std::string & id);
		virtual ~FreeSwtichModule(void);
		virtual int Start() override;
		virtual int Stop() override;
		virtual bool LoadConfig(const std::string & config) override;
		virtual const model::ExtensionMap & GetExtension() override;
	private:
		//inherit from SendInterface
		virtual void fireSend(const std::string &strContent, const void * param) override;
	private:
		log4cplus::Logger log;
		std::thread m_Thread;
		std::atomic_bool m_bRunning = false;
		model::ExtensionMap m_Extensions;
		std::string m_Host;
		int m_Port = 0;
		std::string m_User;
		std::string m_Password;
		void ConnectFS();
	};

}
}
#endif // end header
