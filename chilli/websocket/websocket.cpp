#include "websocket.h"
#include <log4cplus/loggingmacros.h>
#include <sstream>
#include <map>
#include <mutex>

namespace WebSocket {
	static std::map<WebSocketClient *, struct lws *> WSClientSet;
	static std::recursive_mutex wsClientSetMtx;

	/*
	* dumb_increment protocol
	*
	* since this also happens to be protocols[0], some callbacks that are not
	* bound to a specific protocol also turn up here.
	*/

	static int
		callback_lws(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
	{

		WebSocketClient * wsclient = (WebSocketClient*)user;
		WebSocketServer * This = reinterpret_cast<WebSocketServer*>(lws_context_user(lws_get_context(wsi)));

		std::lock_guard<std::recursive_mutex> lcx(wsClientSetMtx);
		bool isdeconstruct = false;
		if (WSClientSet.find(wsclient) == WSClientSet.end()) {
			isdeconstruct = true;
		}

		switch (reason) {
		case LWS_CALLBACK_ESTABLISHED:
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_ESTABLISHED");
			if (!isdeconstruct)
				wsclient->OnOpen();
			break;
		case LWS_CALLBACK_CLIENT_CONNECTION_ERROR: {
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_CLIENT_CONNECTION_ERROR");
			std::string errorCode;
			if (in) {
				errorCode.assign((char *)in, len);
			}
			if (!isdeconstruct)
				wsclient->OnError(errorCode);
		}
												   break;
		case LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH:
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH");
			break;
		case LWS_CALLBACK_CLIENT_ESTABLISHED:
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_CLIENT_ESTABLISHED");
			if (!isdeconstruct)
				wsclient->OnOpen();
			break;
		case LWS_CALLBACK_CLOSED:
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_CLOSED");
			goto lwsclose;
			break;
		case LWS_CALLBACK_CLOSED_HTTP:
		{
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_CLOSED_HTTP");
lwsclose:
			std::string errorCode;
			if (in) {
				errorCode.assign((char *)in, len);
			}
			if (!isdeconstruct)
				wsclient->OnClose(errorCode);
			WSClientSet.erase(wsclient);
		}
		break;
		case LWS_CALLBACK_RECEIVE: {
			//LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_RECEIVE");
			std::string message;
			if (in) {
				message.assign((char *)in, len);
			}
			if (!isdeconstruct)
				wsclient->OnMessage(message);
		}
								   break;
		case LWS_CALLBACK_RECEIVE_PONG:
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_RECEIVE_PONG");
			break;
		case LWS_CALLBACK_CLIENT_RECEIVE: {
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_CLIENT_RECEIVE");
			std::string message;
			if (in) {
				message.assign((char *)in, len);
			}
			if (!isdeconstruct)
				wsclient->OnMessage(message);
		}
										  break;
		case LWS_CALLBACK_CLIENT_RECEIVE_PONG:
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_CLIENT_RECEIVE_PONG");
			break;
		case LWS_CALLBACK_CLIENT_WRITEABLE:
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_CLIENT_WRITEABLE");
			goto ws_write;
			break;
		case LWS_CALLBACK_SERVER_WRITEABLE: {
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_SERVER_WRITEABLE");
		ws_write:
			if (!isdeconstruct) {
				wsclient->OnSend();
				int bufLen = wsclient->m_sendBuf.size() - LWS_PRE;
				if (bufLen > 0)
				{
					int len = lws_write(wsi, wsclient->m_sendBuf.data() + LWS_PRE, bufLen, LWS_WRITE_TEXT);
					if (len > 0)
					{
						wsclient->m_sendBuf.erase(wsclient->m_sendBuf.begin() + LWS_PRE, wsclient->m_sendBuf.begin() + LWS_PRE + len);
					}
					else {
						return -1;
					}
					if (wsclient->m_sendBuf.size() - LWS_PRE > 0)
					{
						lws_callback_on_writable(wsi);
					}
				}
			}
			else {
				LOG4CPLUS_DEBUG(This->log, "Close a connection " << wsi);
				return -1;
			}
		}
											break;
		case LWS_CALLBACK_HTTP: {
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_HTTP");
		}
								break;
		case LWS_CALLBACK_HTTP_BODY: {
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_HTTP_BODY");
		}
									 break;
		case LWS_CALLBACK_HTTP_BODY_COMPLETION: {
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_HTTP_BODY_COMPLETION");
		}
												break;
		case LWS_CALLBACK_HTTP_FILE_COMPLETION: {
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_HTTP_FILE_COMPLETION");
		}
												break;
		case LWS_CALLBACK_HTTP_WRITEABLE: {
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_HTTP_WRITEABLE");
		}
										  break;
		case LWS_CALLBACK_FILTER_NETWORK_CONNECTION: {
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_FILTER_NETWORK_CONNECTION");
		}
													 break;
		case LWS_CALLBACK_FILTER_HTTP_CONNECTION: {
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_FILTER_HTTP_CONNECTION");
		}
												  break;
		case LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED: {
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED");
		}
														  break;
		case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION: {
			//LOG4CPLUS_DEBUG(log, "LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION");
		}
													  break;
		case LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS: {
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS");
		}
																  break;
		case LWS_CALLBACK_OPENSSL_LOAD_EXTRA_SERVER_VERIFY_CERTS: {
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_OPENSSL_LOAD_EXTRA_SERVER_VERIFY_CERTS");
		}
																  break;
		case LWS_CALLBACK_OPENSSL_PERFORM_CLIENT_CERT_VERIFICATION: {
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_OPENSSL_PERFORM_CLIENT_CERT_VERIFICATION");
		}
																	break;
		case LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER:
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER");
			break;
		case LWS_CALLBACK_CONFIRM_EXTENSION_OKAY: {
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_CONFIRM_EXTENSION_OKAY");
		}
												  break;
		case LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED:
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED");
			break;
		case LWS_CALLBACK_PROTOCOL_INIT:
			//LOG4CPLUS_DEBUG(log, "LWS_CALLBACK_PROTOCOL_INIT");
			break;
		case LWS_CALLBACK_PROTOCOL_DESTROY: {
			//LOG4CPLUS_DEBUG(log, "LWS_CALLBACK_PROTOCOL_DESTROY");
		}
											break;
		case LWS_CALLBACK_WSI_CREATE: {
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_WSI_CREATE");
			WebSocketClient * wsclient = This->OnAccept(wsi);
			lws_wsi_set_user(wsi, wsclient);
			WSClientSet.insert(std::pair<WebSocketClient*, struct lws *>(wsclient, wsi));
		}
									  break;
		case LWS_CALLBACK_WSI_DESTROY: {
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_WSI_DESTROY");
			if (wsclient){
				WSClientSet.erase(wsclient);
				if (typeid(*wsclient) == typeid(WebSocketClient))
					delete wsclient;
			}

		}
									   break;
		case LWS_CALLBACK_GET_THREAD_ID: {
			//LOG4CPLUS_DEBUG(log, "LWS_CALLBACK_GET_THREAD_ID");
		}
										 break;
		case LWS_CALLBACK_ADD_POLL_FD:
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_ADD_POLL_FD");
			break;
		case LWS_CALLBACK_DEL_POLL_FD:
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_DEL_POLL_FD");
			break;
		case LWS_CALLBACK_CHANGE_MODE_POLL_FD:
			//LOG4CPLUS_DEBUG(log, "LWS_CALLBACK_CHANGE_MODE_POLL_FD");
			break;
		case LWS_CALLBACK_LOCK_POLL:
			//LOG4CPLUS_DEBUG(log, "LWS_CALLBACK_LOCK_POLL");
			break;
		case LWS_CALLBACK_UNLOCK_POLL:
			//LOG4CPLUS_DEBUG(log, "LWS_CALLBACK_UNLOCK_POLL");
			break;
		case LWS_CALLBACK_OPENSSL_CONTEXT_REQUIRES_PRIVATE_KEY:
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_OPENSSL_CONTEXT_REQUIRES_PRIVATE_KEY");
			break;
		case LWS_CALLBACK_WS_PEER_INITIATED_CLOSE:
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_WS_PEER_INITIATED_CLOSE");
			break;
		case LWS_CALLBACK_WS_EXT_DEFAULTS:
			LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_WS_EXT_DEFAULTS");
			break;
		case LWS_CALLBACK_HTTP_DROP_PROTOCOL:
			//LOG4CPLUS_DEBUG(log, "LWS_CALLBACK_HTTP_DROP_PROTOCOL");
			break;
		default:
			LOG4CPLUS_DEBUG(This->log, "Unknown:" << reason);
			break;
		}

		return 0;
	}



	/* list of supported protocols and callbacks */

	static struct lws_protocols protocols[] = {
		{
			"",
			callback_lws,
			0,
			0,
		},
		{ NULL, NULL, 0, 0 } /* end */
	};

	void WebSocketServer::Loop(int timeout_ms)
	{
		lws_service(m_Context, timeout_ms);
	}

	WebSocket::WebSocketClient * WebSocketServer::OnAccept(struct lws *wsi)
	{
		WebSocketClient * wsclient = new WebSocketClient(wsi);
		return wsclient;
	}

	WebSocketServer::WebSocketServer(int port) :m_Context(nullptr), m_port(port)
	{
		this->log = log4cplus::Logger::getInstance("chilli.WebSocketModule");
	}

	WebSocketServer::~WebSocketServer()
	{
	}

	bool WebSocketServer::InitInstance()
	{
		bool result = true;

		memset(&m_Info, 0, sizeof(m_Info));
		m_Info.port = m_port;
		m_Info.protocols = protocols;
		m_Info.gid = -1;
		m_Info.uid = -1;
		m_Info.timeout_secs = 5;
		m_Info.user = this;
		m_Context = lws_create_context(&m_Info);
		if (m_Context == NULL) {
			LOG4CPLUS_ERROR(log, "Creating libwebsocket context failed");
			result = false;
		}
		
		return result;
	}


	bool WebSocketServer::UnInitInstance()
	{
		bool result = true;
		std::lock_guard<std::recursive_mutex>lck(wsClientSetMtx);
		if (m_Context) {
			lws_context_destroy(m_Context);
			m_Context = nullptr;
		}

		return result;

	}

	WebSocketClient::WebSocketClient(const std::string & ws, struct lws_context *ctx) :m_Context(ctx), m_url(ws), wsi(nullptr), m_state(CLOSED), m_sendBuf(LWS_PRE)
	{
		std::stringstream str;
		str << this << ":";
		m_SessionId = str.str();

		this->log = log4cplus::Logger::getInstance("wsclient");
		//LOG4CPLUS_DEBUG(log, m_SessionId << "WS:" << m_url);
		//LOG4CPLUS_DEBUG(log, m_SessionId << "context:" << m_Context);

		memset(&con_info, 0, sizeof(con_info));

		//LOG4CPLUS_TRACE(log, m_SessionId << "construction");

	}

	WebSocketClient::WebSocketClient(struct lws_context *ctx) :m_Context(ctx), wsi(nullptr), m_state(CLOSED), m_sendBuf(LWS_PRE)
	{
		std::stringstream str;
		str << this << ":";
		m_SessionId = str.str();
		this->log = log4cplus::Logger::getInstance("wsclient");

		//LOG4CPLUS_DEBUG(log, m_SessionId << "context:" << m_Context);

		memset(&con_info, 0, sizeof(con_info));

		//LOG4CPLUS_TRACE(log, m_SessionId << "construction");

	}

	WebSocketClient::WebSocketClient(struct lws * _wsi) :m_Context(nullptr), wsi(_wsi), m_state(CLOSED), m_sendBuf(LWS_PRE)
	{
		std::stringstream str;
		str << this << ":";
		m_SessionId = str.str();
		this->log = log4cplus::Logger::getInstance("wsclient");

		//LOG4CPLUS_DEBUG(log, m_SessionId << "wsi:" << wsi);
		m_Context = lws_get_context(wsi);
		//LOG4CPLUS_DEBUG(log, m_SessionId << "context:" << m_Context);

		memset(&con_info, 0, sizeof(con_info));

		//LOG4CPLUS_TRACE(log, m_SessionId << "construction");

	}

	WebSocketClient::~WebSocketClient()
	{
		Close();
		//LOG4CPLUS_TRACE(log, m_SessionId << "deconstruct");
	}

	void WebSocketClient::Open()
	{
		const char * prot = nullptr;
		char m_urlbuff[1024];

		memset(m_urlbuff, 0, sizeof(m_urlbuff));
		strncpy_s(m_urlbuff, m_url.c_str(), sizeof(m_urlbuff));

		if (lws_parse_uri(m_urlbuff, &prot, &con_info.address, &con_info.port, &con_info.path))
			LOG4CPLUS_ERROR(log, m_SessionId << "parse uri error.");

		if (!strcmp(prot, "http") || !strcmp(prot, "ws"))
			con_info.ssl_connection = 0;
		if (!strcmp(prot, "https") || !strcmp(prot, "wss"))
			con_info.ssl_connection = 1;


		con_info.context = m_Context;
		con_info.host = con_info.address;
		con_info.origin = con_info.address;
		con_info.userdata = this;
		wsi = lws_client_connect_via_info(&con_info);
		LOG4CPLUS_TRACE(log, m_SessionId << "wsi:" << wsi);

		std::lock_guard<std::recursive_mutex>lck(wsClientSetMtx);
		WSClientSet.insert(std::pair<WebSocketClient*, struct lws *>(this, wsi));

		m_state = CONNECTING;

	}

	void WebSocketClient::Close()
	{
		std::lock_guard<std::recursive_mutex>lck(wsClientSetMtx);
		if (WSClientSet.find(this) != WSClientSet.end())
		{
			WSClientSet.erase(this);
			lws_wsi_set_user(wsi, nullptr);
			lws_callback_on_writable(wsi);
			lws_cancel_service(m_Context);
		}

	}

	int WebSocketClient::Send(const char* lpBuf, int nBufLen)
	{
		std::lock_guard<std::recursive_mutex>lck(wsClientSetMtx);
		m_sendBuf.insert(m_sendBuf.end(), lpBuf, lpBuf + nBufLen);

		if (WSClientSet.find(this) != WSClientSet.end()) {
			lws_callback_on_writable(this->wsi);
			lws_cancel_service(m_Context);
		}
		else {
			LOG4CPLUS_ERROR(log, m_SessionId << "Send:" << std::string(m_sendBuf.begin() + LWS_PRE, m_sendBuf.end()));
			LOG4CPLUS_ERROR(log, m_SessionId << " closed");
		}

		return 0;
	}


	void WebSocketClient::OnOpen()
	{
		LOG4CPLUS_DEBUG(log, m_SessionId << "OnOpen");
	}

	void WebSocketClient::OnSend()
	{
		LOG4CPLUS_DEBUG(log, m_SessionId << "OnSend");
	}

	void WebSocketClient::OnClose(const std::string & ErrorCode)
	{
		LOG4CPLUS_DEBUG(log, m_SessionId << "OnClose:" << ErrorCode);
	}

	void WebSocketClient::OnError(const std::string & errorCode)
	{
		LOG4CPLUS_DEBUG(log, m_SessionId << "OnError:" << errorCode);
	}

	void WebSocketClient::OnMessage(const std::string & message)
	{
		LOG4CPLUS_DEBUG(log, m_SessionId << "OnMessage:" << message);
	}

	void WebSocketClient::SetWSUrl(const std::string & url)
	{
		this->m_url = url;
		LOG4CPLUS_DEBUG(log, m_SessionId << "WS:" << this->m_url);
	}

	const std::string & WebSocketClient::GetWSUrl()
	{
		return this->m_url;
	}
}
