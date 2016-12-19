#pragma once
#ifndef _CHILLI_ACDMODULE_HEADER_
#define _CHILLI_ACDMODULE_HEADER_
#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <thread>
#include <mutex>
#include <memory>

namespace chilli{
namespace ACD{

class ACDModule :public model::ProcessModule
{
public:
	ACDModule();
	virtual ~ACDModule(void);
	virtual int Start() override;
	virtual int Stop() override;
	virtual bool LoadConfig(const std::string & configContext) override;
	virtual const std::map<std::string, model::ExtensionPtr> &GetExtension() override;

private:
	log4cplus::Logger log;
	std::thread m_Thread;
	std::map<std::string, model::ExtensionPtr> m_Extension;
	std::map<std::string, model::ExtensionPtr> m_Session;
	std::mutex m_SessionLock;
	model::ExtensionPtr GetSession(const std::string & sessionid, const std::string & eventName, const std::string & ext);
	void RemoveSession(const std::string & sessionId);
	std::atomic<bool> bRunning = false;
	void run();
};
}
}
#endif // end acd header

