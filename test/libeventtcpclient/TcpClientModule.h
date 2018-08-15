#ifndef __TCPCLIENT_MODULE_HEADER_
#define __TCPCLIENT_MODULE_HEADER_

#include <event2/event.h>
#include "CEventBuffer.h"
#include <json/config.h>
#include <json/json.h>
#include <atomic>
#include <thread>

class TcpClientModule {
public:
	TcpClientModule();
	virtual ~TcpClientModule();

	void Start(Json::Value address);
	void Stop();
	bool IsConnected();
	void PutMessage(const std::string & sessionid, const std::string & data);

	void run();
	virtual void onConnected();
	virtual void onClosed();
	virtual void onError(long err);
	virtual void onReceived(const std::string & data);
	virtual void onWriteble();
	void onConnectTimeOut();
	void onConnectDelay();
	virtual void Login() = 0;
	virtual void Ping() = 0;

	int Send(const char * data, unsigned int len, const std::string & sessionId = "");

	static void connect_event_cb(struct bufferevent *bev, short event, void *arg);
	static void connect_read_cb(struct bufferevent* bev, void* arg);
	static void connect_write_cb(struct bufferevent* bev, void* arg);
	static void connect_timeout(evutil_socket_t fd, short event, void *arg);
	static void connect_delay_timer(evutil_socket_t fd, short event, void *arg);
	static void onwriteble(evutil_socket_t fd, short event, void *arg);
	static void ping_timer(evutil_socket_t fd, short event, void *arg);
private:
	struct event_base * m_pBase = nullptr;
	struct bufferevent* m_bev = nullptr;
	struct event	  * m_connect_timer = nullptr;
	struct event      * m_ping_timer = nullptr;
	struct event	  * m_connect_deley_timer = nullptr;
	struct event      * m_Writeble = nullptr;
	std::atomic<bool>	m_Connected;

	std::thread m_thread;
	std::atomic_bool    m_Running;
	Json::Value m_tcpAddr;
	uint32_t	m_tcpIndex = 0;
	std::string m_tcpIp;
	int			m_tcpPort = 0;
	helper::CEventBuffer<class TCPData *> m_Datas;
protected:
};

#endif
