#pragma once
#ifndef _CHILLI_AGENTMODULE_HEADER_
#define _CHILLI_AGENTMODULE_HEADER_
#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <scxml/SMInstance.h>
#include <common/Timer.h>
#include <thread>
#include <map>

namespace chilli{
namespace Agent{

class AgentModule :public model::ProcessModule, public fsm::SMInstance, public helper::CTimerNotify
{
public:
	AgentModule();
	virtual ~AgentModule(void);
	virtual int Start();
	virtual int Stop();
	virtual bool LoadConfig(const std::string & configFile);
	virtual const std::map<std::string, model::ExtensionPtr> GetExtension();

	virtual void OnTimerExpired(unsigned long timerId, const std::string & attr);
private:
	log4cplus::Logger log;
	std::vector<std::shared_ptr<std::thread>> m_Thread;
	std::map<std::string, model::ExtensionPtr> m_Agents;
	std::atomic<bool> bRunning;
	void run();

	int m_tcpPort;
	int m_wsPort;
	mutable struct event_base *m_libeventbase;
	bool listenTCP(int port) const;

};
}
}
#endif // end Agent header

