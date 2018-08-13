#pragma once
#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <thread>
#include <vector>
#include "../TCP/tcp.h"

namespace chilli{
namespace EventReport{

class EPConnection {
public:
	explicit EPConnection(class EventReportModule * module);

	virtual ~EPConnection();

	uint64_t GetId();
public:
	//virtual void Open() = 0;
	//virtual void Close() = 0;
	virtual int Send(const char * lpBuf, int nBufLen) = 0;
	virtual int Send(Json::Value send) = 0;
protected:
	const uint64_t m_Id;
	class EventReportModule * m_module = nullptr;
	static std::atomic_uint64_t __newConnectionId;
};

typedef std::shared_ptr<EPConnection> EPConnectionPtr;

class EventReportModule :public model::ProcessModule, public TCP::TCPServer
{
public:
	explicit EventReportModule(const std::string & id);
	virtual ~EventReportModule(void);
	virtual int Start() override;
	virtual int Stop() override;
	virtual bool LoadConfig(const std::string & configContext) override;

	//Connection interface
	void ConnOnClose(uint64_t id);
	void ConnOnError(uint64_t id, const std::string & errorCode);
	void ConnOnMessage(EPConnection * conn, uint64_t id, const std::string & message, log4cplus::Logger & log);
private:
	void processSend(const std::string &strContent, const void * param, bool & bHandled);
	//inherit from SendInterface
	virtual void fireSend(const std::string &strContent, const void * param) override;
	virtual void run() override;
private:
	std::vector<std::thread> m_Threads;

	int m_tcpPort = -1;
	int m_wsPort = -1;
	std::string m_wsUrl;

public:
	virtual TCP::TCPConnection * OnAccept(struct event_base * base, int64_t fd) override;
private:
	void ListenTCP(uint32_t port);
	bool listenWS(int port);

	std::map<uint32_t, EPConnectionPtr>m_Connections;

};
}
}

