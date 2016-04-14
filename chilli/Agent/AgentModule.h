#pragma once
#ifndef _CHILLI_AGENTMODULE_HEADER_
#define _CHILLI_AGENTMODULE_HEADER_
#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <scxml/SMInstance.h>
#include <common/Timer.h>
#include <thread>
#include <map>
#include <event2/util.h>

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

	mutable struct event_base *base;
	int m_tcpPort;
	int m_wsPort;

	bool listenTCP(int port) const;
	friend void timeout_cb(evutil_socket_t fd, short event, void *arg);

};
}
}
#endif // end Agent header

