#pragma once
#ifndef _CHILLI_ACDMODULE_HEADER_
#define _CHILLI_ACDMODULE_HEADER_
#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <scxml/SMInstance.h>
#include <common/Timer.h>
#include <thread>
#include <map>
#include <mutex>
#include <memory>

namespace chilli{
namespace ACD{

class ACDModule :public model::ProcessModule, public fsm::SMInstance, public helper::CTimerNotify
{
public:
	ACDModule();
	virtual ~ACDModule(void);
	virtual int Start();
	virtual int Stop();
	virtual bool LoadConfig(const std::string & configFile);
	virtual const std::map<std::string, model::ExtensionPtr> GetExtension();

	virtual void OnTimerExpired(unsigned long timerId, const std::string & attr);
private:
	log4cplus::Logger log;
	void DisplayEventInfo(const std::string &) const;
	std::vector<std::thread*> m_Thread;
	std::map<std::string, model::ExtensionPtr> m_Extension;
	std::map<std::string, std::string>m_SMFile;
	std::map<std::string, model::ExtensionPtr> m_Session;
	std::mutex m_SessionLock;
	model::ExtensionPtr GetSession(const std::string & sessionid, const std::string & eventName, const std::string & ext);
	void RemoveSession(const std::string & sessionId);
	std::atomic<bool> bRunning;
	void run();
};
}
}
#endif // end acd header

