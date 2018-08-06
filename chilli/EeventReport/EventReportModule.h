#pragma once
#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <thread>
#include <vector>

namespace chilli{
namespace EventReport{

class EventReportModule :public model::ProcessModule
{
public:
	explicit EventReportModule(const std::string & id);
	virtual ~EventReportModule(void);
	virtual int Start() override;
	virtual int Stop() override;
	virtual bool LoadConfig(const std::string & configContext) override;
private:
	//inherit from SendInterface
	virtual void fireSend(const std::string &strContent, const void * param) override;
private:
	std::vector<std::thread> m_Threads;

	struct event_base * m_Base = nullptr;
	int m_tcpPort = -1;
	int m_wsPort = -1;
	std::string m_wsUrl;

	bool listenTCP(int port);
	bool listenWS(int port);

	virtual void run() override;

};
}
}

