#pragma  once
#include <string>
#include <stdint.h>
#include <log4cplus/logger.h>

struct event_base;
struct evbuffer;
struct bufferevent;
namespace TCP {

class TCPConnection {
public:
	explicit TCPConnection(struct event_base * base, int64_t fd);
	virtual ~TCPConnection();

	virtual void OnOpen();
	virtual void OnSend();
	virtual void OnClosed();
	virtual void OnError(uint32_t err);
	virtual void OnReceived(const std::string & data);

	void Close();
	int Send(const char * lpBuf, int nBufLen);

private:
	struct event_base * m_pBase = nullptr;
	struct bufferevent* m_bev = nullptr;
};

class TCPServer {
public:
	explicit TCPServer();
	virtual ~TCPServer();

	void setLogger(log4cplus::Logger log);
	log4cplus::Logger getLogger();
	void setId(const std::string & id);
	std::string getId();

	void ListenTCP(uint32_t port);
	void Stop();
	virtual TCPConnection * OnAccept(struct event_base * base, int64_t fd);
private:
	struct event_base * m_Base = nullptr;
	log4cplus::Logger loger;
	std::string m_Id;
};
}