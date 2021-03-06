#pragma once
#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <thread>
#include <vector>
#include "../TCP/tcp.h"
#include <mutex>

namespace chilli{
namespace EventReport{

class EPConnection {
public:
	explicit EPConnection(class EventReportModule * module);

	virtual ~EPConnection();

	uint64_t getId();
public:
	//virtual void Open() = 0;
	//virtual void Close() = 0;
	virtual int Send(const char * lpBuf, int nBufLen) = 0;
	virtual int Send(Json::Value send) = 0;
protected:
	const uint64_t m_Id;
	class EventReportModule * m_module = nullptr;
	static std::atomic<uint64_t> __newConnectionId;
};

typedef std::shared_ptr<EPConnection> EPConnectionPtr;

class EventReportModule :public model::ProcessModule, public TCP::TCPServer
{
public:
	explicit EventReportModule(const std::string & id, uint32_t threadSize = 16);
	virtual ~EventReportModule(void);
	virtual int Start() override;
	virtual int Stop() override;
	virtual bool LoadConfig(const std::string & configContext) override;

	//Connection interface
	void ConnOnClose(uint64_t id);
	void ConnOnError(uint64_t id, const std::string & errorCode);
	void ConnOnMessage(EPConnection * conn, uint64_t id, const std::string & message, log4cplus::Logger & log, const std::string & logId);
private:
	void processSend(const fsm::FireDataType & fireData, const void * param, bool & bHandled);
	//inherit from SendInterface
	virtual void fireSend(const fsm::FireDataType & fireData, const void * param) override;
	virtual void run() override;
	virtual void execute(helper::CEventBuffer<model::EventType_t> * eventQueue) override;
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
	void addConnection(uint64_t id, EPConnection * conn);
	void removeConnection(uint64_t id);
	void send(uint64_t id, const Json::Value & send);
	void send(const Json::Value &send);
	std::mutex m_ConnectionMtx;
	std::map<uint64_t, EPConnectionPtr>m_Connections;

};
}
}

