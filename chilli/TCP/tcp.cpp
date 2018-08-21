#include "tcp.h"
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <event2/thread.h>
#include <cstring>

#pragma comment(lib,"ws2_32.lib")

#include <log4cplus/loggingmacros.h>



namespace TCP {

	static void listener_cb(struct evconnlistener *, evutil_socket_t fd, struct sockaddr *, int socklen, void *);
	static void conn_read_cb(struct bufferevent *bev, void *ctx);
	static void conn_writecb(struct bufferevent *, void *);
	static void conn_eventcb(struct bufferevent *, short, void *);

	static void listener_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sa, int socklen, void *user_data)
	{
		TCPServer * This = reinterpret_cast<TCPServer *>(user_data);

		struct event_base *base = evconnlistener_get_base(listener);
		TCPConnection * client = This->OnAccept(base, fd);
		sockaddr_in * sa_in = (sockaddr_in *)sa;
		char ip[64];
		evutil_inet_ntop(AF_INET, sa_in, ip, sizeof(ip));
		LOG4CPLUS_DEBUG(This->getLogger(), "." + This->getId(), " accept client:" << client << ":" << ip << ":" << ntohs(sa_in->sin_port));
		client->OnOpen();
	}

	static void conn_read_cb(struct bufferevent *bev, void * user_data)
	{
		TCPConnection * This = (TCPConnection*)user_data;
		evbuffer *buffer = bufferevent_get_input(bev);

		size_t len = evbuffer_get_length(buffer);

		if (len >0)
		{
			std::vector<char>data(len);
			evbuffer_remove(buffer, data.data(), len);
			std::string content = std::string(data.begin(), data.end());
			This->OnReceived(content);
		}
		
	}

	static void conn_writecb(struct bufferevent *bev, void *user_data)
	{
		TCPConnection * This = (TCPConnection*)user_data;
		struct evbuffer *output = bufferevent_get_output(bev);
		if (evbuffer_get_length(output) == 0) {
			This->OnSend();
			//LOG4CPLUS_DEBUG(This->log, "." + This->getId(), "write data end.");
		}

	}

	static void conn_eventcb(struct bufferevent *bev, short events, void * user_data)
	{
		TCPConnection * This = (TCPConnection*)user_data;

		if (events & BEV_EVENT_EOF) {
			if (typeid(*This) == typeid(TCPConnection)) {
				This->OnClosed();
				delete This;
			}
			else
				This->OnClosed();
		}
		else if (events & BEV_EVENT_ERROR) {
			if (typeid(*This) == typeid(TCPConnection)) {
				This->OnError(EVUTIL_SOCKET_ERROR());
				delete This;
			}
			else
				This->OnError(EVUTIL_SOCKET_ERROR());
		}
		else if (events & BEV_EVENT_CONNECTED) {
			This->OnOpen();
		}
		else if (events & BEV_EVENT_TIMEOUT)
		{
			This->OnError(BEV_EVENT_TIMEOUT);
		}

	}

	TCPConnection * TCPServer::OnAccept(event_base * base, int64_t fd)
	{
		TCPConnection * client = new TCPConnection(base, fd);
		return client;
	}

	TCPConnection::TCPConnection(event_base * base, int64_t fd):m_pBase(base)
	{
		m_bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE | BEV_OPT_THREADSAFE);
		bufferevent_setcb(m_bev, conn_read_cb, conn_writecb, conn_eventcb, this);
		bufferevent_enable(m_bev, EV_WRITE | EV_READ | EV_ET);
	}

	TCPConnection::~TCPConnection()
	{
		if (m_bev) {
			bufferevent_free(m_bev);
			m_bev = nullptr;
		}
	}

	void TCPConnection::OnOpen()
	{
	}

	void TCPConnection::OnSend()
	{
	}

	void TCPConnection::OnClosed()
	{
	}

	void TCPConnection::OnError(uint32_t err)
	{
	}

	void TCPConnection::OnReceived(const std::string & data)
	{
	}

	void TCPConnection::Close()
	{
		if (m_bev) {
			evutil_closesocket(bufferevent_getfd(m_bev));
		}
	}

	int TCPConnection::Send(const char * lpBuf, int nBufLen)
	{
		if(m_bev)
			return bufferevent_write(m_bev, lpBuf, nBufLen);

		return 0;
	}

	TCPServer::TCPServer()
	{
	}

	TCPServer::~TCPServer()
	{
	}

	void TCPServer::setLogger(log4cplus::Logger log)
	{
		this->loger = log;
	}

	log4cplus::Logger TCPServer::getLogger()
	{
		return this->loger;
	}

	void TCPServer::setId(const std::string & id)
	{
		m_Id = id;
	}

	std::string TCPServer::getId()
	{
		return m_Id;
	}


	void TCPServer::ListenTCP(uint32_t port)
	{
		struct sockaddr_in sin;
		struct evconnlistener *listener;

		LOG4CPLUS_INFO(loger, "."+ this->getId(), " listen TCP Starting...");
#ifdef WIN32
		evthread_use_windows_threads();
		WSADATA wsa_data;
		WSAStartup(MAKEWORD(2, 2), &wsa_data);
#else
		evthread_use_pthreads();
#endif

		const char ** methods = event_get_supported_methods();
		for (int i = 0; methods[i] != nullptr; ++i) {
			//LOG4CPLUS_INFO(log, ",libevent supported method:" << methods[i]);
		}

		m_Base = event_base_new();
		LOG4CPLUS_INFO(loger, "." + this->getId(), ",libevent current method:" << event_base_get_method(m_Base));

		if (!m_Base) {
			LOG4CPLUS_ERROR(loger, "." + this->getId(), " Could not initialize libevent!");
			goto done;
		}

		memset(&sin, 0, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = htonl(0);
		sin.sin_port = htons(port);

		listener = evconnlistener_new_bind(m_Base, listener_cb, this,
			LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE | LEV_OPT_THREADSAFE, -1,
			(struct sockaddr*)&sin,
			sizeof(sin));

		if (!listener) {
			LOG4CPLUS_ERROR(loger, "." + this->getId(), " Could not create a listener!");
			goto done;
		}

		LOG4CPLUS_INFO(loger, "." + this->getId(), ",start listen tcp port:" << port);

		event_base_dispatch(m_Base);

	done:
		if (listener) {
			evconnlistener_free(listener);
			listener = nullptr;
		}

		if (m_Base) {
			event_base_free(m_Base);
			m_Base = nullptr;
		}

#ifdef WIN32
		WSACleanup();
#endif
		LOG4CPLUS_INFO(loger, "." + this->getId(), " listen TCP Stoped.");
		log4cplus::threadCleanup();
		
	}

	void TCPServer::Stop()
	{
		if(m_Base)
			event_base_loopbreak(m_Base);
	}

}