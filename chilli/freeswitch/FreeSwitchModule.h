#ifndef _CHILLI_FREESWITCHMODULE_HEADER_
#define _CHILLI_FREESWITCHMODULE_HEADER_
#include <log4cplus/logger.h>
#include "../model/ProcessModule.h"
#include <thread>

namespace chilli{
namespace FreeSwitch{

	class FreeSwitchModule :public model::ProcessModule
	{
	public:
		explicit FreeSwitchModule(const std::string & id);
		virtual ~FreeSwitchModule(void);
		virtual int Start() override;
		virtual int Stop() override;
		virtual bool LoadConfig(const std::string & config) override;
		virtual model::ExtensionPtr newExtension(const model::ExtensionConfigPtr & config) override;
	protected:
		//inherit from SendInterface
		virtual void fireSend(const std::string &strContent, const void * param) override;
		void processSend(const std::string &strContent, const void * param, bool & bHandled, model::Extension * ext);
	private:
		std::thread m_Thread;
		std::string m_Host;
		int m_Port = 0;
		std::string m_User;
		std::string m_Password;
		void ConnectFS();
		friend class FreeSwitchExtension;
	};

}
}
#endif // end header
