#pragma once
#ifndef _CHILLI_AGENTMODULE_HEADER_
#define _CHILLI_AGENTMODULE_HEADER_
#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <thread>
#include <vector>

namespace chilli{
namespace Agent{

class AgentModule :public model::ProcessModule
{
public:
	AgentModule();
	virtual ~AgentModule(void);
	virtual int Start() override;
	virtual int Stop() override;
	virtual bool LoadConfig(const std::string & configContext) override;
	virtual const model::ExtensionMap & GetExtension() override;

public:
	log4cplus::Logger log;
private:
	std::vector<std::thread> m_Threads;
	model::ExtensionMap m_Agents;
	std::atomic<bool> m_bRunning = false;
	void run();

	struct event_base * m_Base = nullptr;
	int m_tcpPort = -1;
	int m_wsPort = -1;

	bool listenTCP(int port);
	bool listenWS(int port)const;

};
}
}
#endif // end Agent header

