#ifndef _CHILLI_FREESWITCHMODULE_HEADER_
#define _CHILLI_FREESWITCHMODULE_HEADER_
#include <log4cplus/logger.h>
#include "../model/ProcessModule.h"
#include <scxml/SMInstance.h>
#include <common/Timer.h>
#include <mutex>
#include <thread>

namespace chilli{
namespace FreeSwitch{

	class FreeSwtichModule :public model::ProcessModule, public fsm::SMInstance, public helper::CTimerNotify
	{
	public:
		FreeSwtichModule();
		virtual ~FreeSwtichModule(void);
		virtual int Start();
		virtual int Stop();
		virtual bool LoadConfig(const std::string & config);
		virtual const std::map<std::string, model::ExtensionPtr> GetExtension();

		virtual void OnTimerExpired(unsigned long timerId, const std::string & attr);
	private:
		log4cplus::Logger log;
		std::vector<std::shared_ptr<std::thread>> m_Thread;
		std::map<std::string, model::ExtensionPtr> m_Extension;
		std::atomic<bool> bRunning;
		std::string m_Host;
		int m_Port;
		std::string m_User;
		std::string m_Password;
		void Listen();
	};

}
}
#endif // end header
