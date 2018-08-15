#include "TcpClientModule.h"
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <iostream>


#define INT_SIZE                        sizeof(unsigned int)
#define PING_INTERVAL					10
#define CONNECT_TIMEOUT					30
#define CONNECT_DELAY					5

union contextlen {
	char buffer[INT_SIZE];
	unsigned int  nlen;
	unsigned int  hlen;
};


class TCPData {
public:
	TCPData(const std::string & sessionid, const std::string & data) :m_sessionId(sessionid), m_data(data)
	{
	}

public:
	std::string m_sessionId;
	std::string m_data;
};
typedef TCPData* TCPDataPtr;

void TcpClientModule::connect_event_cb(struct bufferevent *bev, short event, void *arg)
{
	TcpClientModule * This = (TcpClientModule*) arg;

	if (event & BEV_EVENT_EOF) {
		This->onClosed();
	}
	else if (event & BEV_EVENT_ERROR) {
		This->onError(EVUTIL_SOCKET_ERROR());
	}
	else if (event & BEV_EVENT_CONNECTED) {
		This->onConnected();
	}
	else
		std::cout << "Unkown event." << std::endl;
}

void TcpClientModule::connect_read_cb(struct bufferevent* bev, void* arg)
{
	TcpClientModule * This = (TcpClientModule*)arg;

	contextlen hlen;
	struct evbuffer *buffer = bufferevent_get_input(bev);

	size_t len = evbuffer_get_length(buffer);
	if (len > 0) {
		std::vector<char>data(len);
		evbuffer_copyout(buffer, data.data(), data.size());
		std::cout << "receve data:" << std::string(data.begin(), data.end()) << std::endl;
	}

	while (evbuffer_get_length(buffer) >= INT_SIZE) {
		evbuffer_copyout(buffer, hlen.buffer, INT_SIZE);
		hlen.hlen = ntohl(hlen.nlen);

		if (evbuffer_get_length(buffer) >= hlen.hlen) {
			std::vector<char>data(hlen.hlen);
			evbuffer_remove(buffer, data.data(), hlen.hlen);
			std::string content = std::string(data.begin() + INT_SIZE, data.end());
			This->onReceived(content);
		}
		else {// 不够一个完整的包，跳出循环   
			break;
		}
	}
	
}

void TcpClientModule::connect_write_cb(struct bufferevent* bev, void* arg)
{
	TcpClientModule * This = (TcpClientModule*)arg;
	struct evbuffer *output = bufferevent_get_output(bev);
	if (evbuffer_get_length(output) == 0) {
		//This->onWriteble();
		//LOG4CPLUS_DEBUG(This->log, "write data end.");
	}
}

void TcpClientModule::connect_timeout(evutil_socket_t fd, short event, void *arg)
{
	TcpClientModule * This = (TcpClientModule*)arg;
	This->onConnectTimeOut();
}

void TcpClientModule::connect_delay_timer(evutil_socket_t fd, short event, void *arg)
{
	TcpClientModule * This = (TcpClientModule*)arg;
	This->onConnectDelay();
}

void TcpClientModule::onwriteble(evutil_socket_t fd, short event, void *arg)
{
	TcpClientModule * This = (TcpClientModule*)arg;
	This->onWriteble();
}

void TcpClientModule::ping_timer(evutil_socket_t fd, short event, void *arg)
{
	TcpClientModule * This = (TcpClientModule*)arg;
	This->Ping();
}

TcpClientModule::TcpClientModule() :m_Connected(false), m_Running(false)
{
}

TcpClientModule::~TcpClientModule()
{
	if (m_thread.joinable()){
		Stop();
	}
}

void TcpClientModule::Start(Json::Value address)
{
	this->m_Running = true;
	if (m_thread.joinable())
		return;

	this->m_tcpAddr = address;

	if (m_tcpAddr.isArray() && m_tcpAddr.size() > 0) {
		m_thread = std::thread(&TcpClientModule::run, this);
	}
	else {
		std::cout << " address not array." << std::endl;
	}
}


void TcpClientModule::run()
{
	std::cout << "Starting..." << std::endl;

	m_pBase = event_base_new();
	std::cout << "current method:" << event_base_get_method(m_pBase) << std::endl;

	m_Writeble = event_new(m_pBase, -1, EV_PERSIST, onwriteble, this);

	while (m_Running)
	{
		m_tcpIp.clear();
		m_tcpPort = 0;

		m_tcpIndex = m_tcpIndex % m_tcpAddr.size();

		if (m_tcpAddr[m_tcpIndex]["ipaddr"].isString()) {
			m_tcpIp = m_tcpAddr[m_tcpIndex]["ipaddr"].asString();
		}

		if (m_tcpAddr[m_tcpIndex]["socketport"].isInt()) {
			m_tcpPort = m_tcpAddr[m_tcpIndex]["socketport"].asInt();
		}

		m_tcpIndex++;

		m_connect_timer = evtimer_new(m_pBase, TcpClientModule::connect_timeout, this);
		m_connect_deley_timer = evtimer_new(m_pBase, TcpClientModule::connect_delay_timer, this);
		m_ping_timer = event_new(m_pBase, -1, EV_PERSIST, ping_timer, this);

		struct timeval tv;
		evutil_timerclear(&tv);
		tv.tv_sec = CONNECT_TIMEOUT;
		event_add(m_connect_timer, &tv);

		this->m_bev = bufferevent_socket_new(m_pBase, -1,
			BEV_OPT_CLOSE_ON_FREE | BEV_OPT_THREADSAFE);

		bufferevent_socket_connect_hostname(m_bev, NULL, AF_INET, m_tcpIp.c_str(), m_tcpPort);

		bufferevent_setcb(m_bev, TcpClientModule::connect_read_cb, TcpClientModule::connect_write_cb, TcpClientModule::connect_event_cb, this);
		bufferevent_enable(m_bev, EV_READ | EV_WRITE);

		std::cout << "connecting to " << m_tcpIp << ":" << m_tcpPort << std::endl;

		event_base_dispatch(m_pBase);

		event_free(m_connect_timer);
		m_connect_timer = nullptr;

		event_free(m_connect_deley_timer);
		m_connect_deley_timer = nullptr;

		event_free(m_ping_timer);
		m_ping_timer = NULL;

		bufferevent_free(m_bev);
		m_bev = nullptr;

	}

	event_free(m_Writeble);
	m_Writeble = nullptr;

	event_base_free(m_pBase);
	m_pBase = nullptr;

	std::cout << "Stoped." << std::endl;
}

void TcpClientModule::Stop()
{
	m_Running = false;
	if (m_thread.joinable()) {
		event_base_loopbreak(m_pBase);
		m_thread.join();
	}
}

bool TcpClientModule::IsConnected()
{
	return m_Connected;
}

void TcpClientModule::onConnected()
{
	event_del(m_connect_timer);
	event_active(m_Writeble, 0, 0);
	m_Connected = true;
	std::cout << "the client has connected" << std::endl;
	this->Login();
	struct timeval tv;
	evutil_timerclear(&tv);
	tv.tv_sec = PING_INTERVAL;
	event_add(m_ping_timer, &tv);
}

void TcpClientModule::onClosed()
{
	struct timeval tv;
	evutil_timerclear(&tv);
	tv.tv_sec = CONNECT_DELAY;
	event_add(m_connect_deley_timer, &tv);
	event_del(m_ping_timer);
	m_Connected = false;
	std::cout << "connection closed" << std::endl;
}

void TcpClientModule::onError(long err)
{
	struct timeval tv;
	evutil_timerclear(&tv);
	tv.tv_sec = CONNECT_DELAY;
	event_add(m_connect_deley_timer, &tv);
	event_del(m_ping_timer);
	m_Connected = false;
	std::cout << "error:" << err << std::endl;
}

void TcpClientModule::onReceived(const std::string & data)
{
	std::cout << "onreceived:" << data << std::endl;
}


void TcpClientModule::onConnectTimeOut()
{
	std::cout << "connect " << m_tcpIp << ":" << m_tcpPort << " timeout:" << std::endl;
	event_base_loopbreak(this->m_pBase);
}

void TcpClientModule::onConnectDelay()
{
	event_base_loopbreak(this->m_pBase);
}


int TcpClientModule::Send(const char * data, unsigned int len, const std::string & sessionId)
{
	if (m_Connected) {
		contextlen nlen;
		std::string buffer;
		nlen.nlen = htonl(len + INT_SIZE);
		buffer.append(nlen.buffer, INT_SIZE);
		buffer.append(data, len);

		std::cout << sessionId << " send to :" << buffer << std::endl;
		return bufferevent_write(m_bev, buffer.c_str(), buffer.length());
	}
	else
		std::cout << "no connected." << std::endl;
	return -1;
}

void TcpClientModule::PutMessage(const std::string & sessionid, const std::string & data)
{
	TCPDataPtr _data = new TCPData(sessionid, data);
	std::cout << " Add to Queue " << this->m_thread.get_id() << " Queue size:" << m_Datas.size() + 1 << std::endl;
	m_Datas.Put(_data);
	if (m_Connected){
		event_active(m_Writeble, 0, 0);
	}
}


void TcpClientModule::onWriteble()
{
	while (m_Datas.size() > 0 && m_Connected) {
		TCPDataPtr data = nullptr;
		m_Datas.Get(data);
		std::cout << "Queue size:" << m_Datas.size() << std::endl;
		this->Send(data->m_data.c_str(), data->m_data.size(), data->m_sessionId);
		delete data;
	}
}