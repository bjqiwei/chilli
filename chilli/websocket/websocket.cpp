#include "websocket.h"
#include <log4cplus/loggingmacros.h>
#include <sstream>
#include <map>
#include <mutex>
#include <thread>
#include <atomic>

namespace WebSocket {
	static std::map<struct lws *, WSConnection *> WSClientSet;
	//static std::recursive_mutex wsClientSetMtx;

	/*
	* dumb_increment protocol
	*
	* since this also happens to be protocols[0], some callbacks that are not
	* bound to a specific protocol also turn up here.
	*/

	int callback_lws(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
	{

		WSConnection * wsclient = nullptr;
		WebSocketServer * This = reinterpret_cast<WebSocketServer*>(lws_context_user(lws_get_context(wsi)));

		//std::lock_guard<std::recursive_mutex> lcx(wsClientSetMtx);
		const auto & it = WSClientSet.find(wsi);
		if (it != WSClientSet.end())
			wsclient = it->second;

		switch (reason) {
		case LWS_CALLBACK_ESTABLISHED:
			//LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_ESTABLISHED");
			if (wsclient) {
				wsclient->m_state = OPEN;
				wsclient->OnOpen();
				lws_callback_on_writable(wsi);
			}
			break;
		case LWS_CALLBACK_CLIENT_CONNECTION_ERROR: {
			LOG4CPLUS_WARN(This->log, "", "LWS_CALLBACK_CLIENT_CONNECTION_ERROR");
			std::string errorCode;
			if (in) {
				errorCode.assign((char *)in, len);
			}

			WSClientSet.erase(wsi);
			if (wsclient) {
				wsclient->m_state = CLOSED;
				std::this_thread::yield();
				wsclient->OnError(errorCode);
				std::this_thread::yield();
				wsclient->OnClose(errorCode);
			}
		}
												   break;
		case LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH:
			LOG4CPLUS_DEBUG(This->log, "", "LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH");
			break;
		case LWS_CALLBACK_CLIENT_ESTABLISHED:
			LOG4CPLUS_DEBUG(This->log, "", "LWS_CALLBACK_CLIENT_ESTABLISHED");
			if (wsclient) {
				wsclient->m_state = OPEN;
				wsclient->OnOpen();
				lws_callback_on_writable(wsi);
			}
			break;
		case LWS_CALLBACK_CLOSED:
			LOG4CPLUS_DEBUG(This->log, "", "LWS_CALLBACK_CLOSED");
			goto lwsclose;
			break;
		case LWS_CALLBACK_CLOSED_CLIENT_HTTP:
			LOG4CPLUS_DEBUG(This->log, "", "LWS_CALLBACK_CLOSED_CLIENT_HTTP");
			goto lwsclose;
			break;
		case LWS_CALLBACK_CLOSED_HTTP:
		{
			LOG4CPLUS_DEBUG(This->log, "", "LWS_CALLBACK_CLOSED_HTTP");
lwsclose:
			std::string errorCode;
			if (in) {
				errorCode.assign((char *)in, len);
			}

			WSClientSet.erase(wsi);
			if (wsclient && wsclient->m_state != CLOSED) {
				wsclient->m_state = CLOSED;
				wsclient->OnClose(errorCode);
			}
		}
		break;
		case LWS_CALLBACK_RECEIVE: {
			//LOG4CPLUS_DEBUG(This->log, "LWS_CALLBACK_RECEIVE");
			std::string message;
			if (in) {
				message.assign((char *)in, len);
			}
			if (wsclient)
				wsclient->OnMessage(message);
		}
								   break;
		case LWS_CALLBACK_RECEIVE_PONG:
			LOG4CPLUS_DEBUG(This->log, "", "LWS_CALLBACK_RECEIVE_PONG");
			break;
		case LWS_CALLBACK_CLIENT_RECEIVE: {
			LOG4CPLUS_DEBUG(This->log, "", "LWS_CALLBACK_CLIENT_RECEIVE");
			std::string message;
			if (in) {
				message.assign((char *)in, len);
			}
			if (wsclient)
				wsclient->OnMessage(message);
		}
										  break;
		case LWS_CALLBACK_CLIENT_RECEIVE_PONG:
			LOG4CPLUS_DEBUG(This->log, "", "LWS_CALLBACK_CLIENT_RECEIVE_PONG");
			break;
		case LWS_CALLBACK_CLIENT_WRITEABLE:
			//LOG4CPLUS_TRACE(This->log, "", "LWS_CALLBACK_CLIENT_WRITEABLE");
			goto ws_write;
			break;
		case LWS_CALLBACK_SERVER_WRITEABLE: {
			//LOG4CPLUS_TRACE(This->log, "", "LWS_CALLBACK_SERVER_WRITEABLE");
		ws_write:
			if ( wsclient && wsclient->m_state != CLOSING) {
				wsclient->OnSend();
				if (wsclient->m_sendBuf.size() > 0) {
					int bufLen = wsclient->m_sendBuf.at(0).size() - LWS_PRE;
					if (bufLen > 0)
					{
						std::string sdata = std::string(wsclient->m_sendBuf.at(0).begin() + LWS_PRE, wsclient->m_sendBuf.at(0).end());
						LOG4CPLUS_TRACE(wsclient->log, "", "Send:" << sdata);

						int len = lws_write(wsi, wsclient->m_sendBuf.at(0).data() + LWS_PRE, bufLen, LWS_WRITE_TEXT);
						if (len > 0){
							wsclient->m_sendBuf.at(0).erase(wsclient->m_sendBuf.at(0).begin() + LWS_PRE, wsclient->m_sendBuf.at(0).begin() + LWS_PRE + len);
						}
						else {
							return -1;
						}
					}

					if (wsclient->m_sendBuf.at(0).size() - LWS_PRE <= 0) {
						wsclient->m_sendBuf.erase(wsclient->m_sendBuf.begin());
					}
				}

				if (wsclient->m_sendBuf.size() > 0) {
					lws_callback_on_writable(wsi);
				}
			}
			else {
				LOG4CPLUS_DEBUG(This->log, "", "Close a connection ");
				return -1;
			}
		}
											break;
		case LWS_CALLBACK_HTTP: {
			LOG4CPLUS_TRACE(This->log, "", "LWS_CALLBACK_HTTP");
		}
								break;
		case LWS_CALLBACK_HTTP_BODY: {
			LOG4CPLUS_TRACE(This->log, "", "LWS_CALLBACK_HTTP_BODY");
		}
									 break;
		case LWS_CALLBACK_HTTP_BODY_COMPLETION: {
			LOG4CPLUS_TRACE(This->log, "", "LWS_CALLBACK_HTTP_BODY_COMPLETION");
		}
												break;
		case LWS_CALLBACK_HTTP_FILE_COMPLETION: {
			LOG4CPLUS_TRACE(This->log, "", "LWS_CALLBACK_HTTP_FILE_COMPLETION");
		}
												break;
		case LWS_CALLBACK_HTTP_WRITEABLE: {
			LOG4CPLUS_TRACE(This->log, "", "LWS_CALLBACK_HTTP_WRITEABLE");
		}
										  break;
		case LWS_CALLBACK_FILTER_NETWORK_CONNECTION: {
			//LOG4CPLUS_TRACE(This->log, "", "LWS_CALLBACK_FILTER_NETWORK_CONNECTION");
		}
													 break;
		case LWS_CALLBACK_FILTER_HTTP_CONNECTION: {
			LOG4CPLUS_TRACE(This->log, "", "LWS_CALLBACK_FILTER_HTTP_CONNECTION");
		}
												  break;
		case LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED: {
			//LOG4CPLUS_TRACE(This->log, "", "LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED");
		}
														  break;
		case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION: {
			//LOG4CPLUS_DEBUG(log,  "","LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION");
		}
													  break;
		case LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS: {
			LOG4CPLUS_TRACE(This->log, "", "LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS");
		}
																  break;
		case LWS_CALLBACK_OPENSSL_LOAD_EXTRA_SERVER_VERIFY_CERTS: {
			LOG4CPLUS_TRACE(This->log, "", "LWS_CALLBACK_OPENSSL_LOAD_EXTRA_SERVER_VERIFY_CERTS");
		}
																  break;
		case LWS_CALLBACK_OPENSSL_PERFORM_CLIENT_CERT_VERIFICATION: {
			LOG4CPLUS_TRACE(This->log, "", "LWS_CALLBACK_OPENSSL_PERFORM_CLIENT_CERT_VERIFICATION");
		}
																	break;
		case LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER:
			LOG4CPLUS_TRACE(This->log, "", "LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER");
			break;
		case LWS_CALLBACK_CONFIRM_EXTENSION_OKAY: {
			LOG4CPLUS_TRACE(This->log, "", "LWS_CALLBACK_CONFIRM_EXTENSION_OKAY");
		}
												  break;
		case LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED:
			LOG4CPLUS_TRACE(This->log, "", "LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED");
			break;
		case LWS_CALLBACK_PROTOCOL_INIT:
			//LOG4CPLUS_DEBUG(log,  "","LWS_CALLBACK_PROTOCOL_INIT");
			break;
		case LWS_CALLBACK_PROTOCOL_DESTROY: {
			//LOG4CPLUS_DEBUG(log,  "","LWS_CALLBACK_PROTOCOL_DESTROY");
		}
											break;
		case LWS_CALLBACK_WSI_CREATE: {
			//LOG4CPLUS_DEBUG(This->log, "", "LWS_CALLBACK_WSI_CREATE");
			if(lws_wsi_user(wsi) == nullptr)
				WSConnection * wsclient = This->OnAccept(wsi);
		}
									  break;
		case LWS_CALLBACK_WSI_DESTROY: {
			//LOG4CPLUS_DEBUG(This->log,  "","LWS_CALLBACK_WSI_DESTROY");
			if (wsclient){
				if (typeid(*wsclient) == typeid(WSConnection))
					delete wsclient;
			}

		}
									   break;
		case LWS_CALLBACK_GET_THREAD_ID: {
			//LOG4CPLUS_DEBUG(log,  "","LWS_CALLBACK_GET_THREAD_ID");
		}
										 break;
		case LWS_CALLBACK_ADD_POLL_FD:
			//LOG4CPLUS_DEBUG(This->log, "", "LWS_CALLBACK_ADD_POLL_FD");
			break;
		case LWS_CALLBACK_DEL_POLL_FD:
			//LOG4CPLUS_DEBUG(This->log, "", "LWS_CALLBACK_DEL_POLL_FD");
			break;
		case LWS_CALLBACK_CHANGE_MODE_POLL_FD:
			//LOG4CPLUS_DEBUG(log,  "","LWS_CALLBACK_CHANGE_MODE_POLL_FD");
			break;
		case LWS_CALLBACK_LOCK_POLL:
			//LOG4CPLUS_DEBUG(log,  "","LWS_CALLBACK_LOCK_POLL");
			break;
		case LWS_CALLBACK_UNLOCK_POLL:
			//LOG4CPLUS_DEBUG(log,  "","LWS_CALLBACK_UNLOCK_POLL");
			break;
		case LWS_CALLBACK_OPENSSL_CONTEXT_REQUIRES_PRIVATE_KEY:
			LOG4CPLUS_TRACE(This->log, "", "LWS_CALLBACK_OPENSSL_CONTEXT_REQUIRES_PRIVATE_KEY");
			break;
		case LWS_CALLBACK_WS_PEER_INITIATED_CLOSE:
			LOG4CPLUS_TRACE(This->log, "", "LWS_CALLBACK_WS_PEER_INITIATED_CLOSE");
			break;
		case LWS_CALLBACK_WS_EXT_DEFAULTS:
			LOG4CPLUS_TRACE(This->log, "", "LWS_CALLBACK_WS_EXT_DEFAULTS");
			break;
		case LWS_CALLBACK_HTTP_DROP_PROTOCOL:
			//LOG4CPLUS_DEBUG(log,  "","LWS_CALLBACK_HTTP_DROP_PROTOCOL");
			break;
		case LWS_CALLBACK_OPENSSL_PERFORM_SERVER_CERT_VERIFICATION:
			LOG4CPLUS_DEBUG(This->log, "", "LWS_CALLBACK_OPENSSL_PERFORM_SERVER_CERT_VERIFICATION");
			{
				/* Verify the client certificate */
				X509_STORE_CTX_set_error((X509_STORE_CTX*)user, X509_V_OK);
				/*if (!len || (SSL_get_verify_result((SSL*)in) != X509_V_OK)) {
				int err = X509_STORE_CTX_get_error((X509_STORE_CTX*)user);
				int depth = X509_STORE_CTX_get_error_depth((X509_STORE_CTX*)user);
				const char* msg = X509_verify_cert_error_string(err);
				LOG4CPLUS_ERROR(This->log, "SSL error: " << msg << "(" << err << "), depth:" << depth);
				return 1;
				}*/
			}
			break;
		default:
			LOG4CPLUS_DEBUG(This->log, "", "Unknown:" << reason);
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

	lws_context * WebSocketServer::GetContext()
	{
		return m_Context;
	}

	WebSocket::WSConnection * WebSocketServer::OnAccept(struct lws *wsi)
	{
		WSConnection * wsclient = new WSConnection(wsi);
		return wsclient;
	}

	WebSocketServer::WebSocketServer(int port) :m_Context(nullptr), m_port(port)
	{
		this->log = log4cplus::Logger::getInstance("chilli.WebSocketModule");
	}

	WebSocketServer::~WebSocketServer()
	{
	}

	void lwsl_log(int level, const char *line)
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("wslog");
		std::string msg(line,strlen(line)-1);
		if (level == LLL_ERR)
			LOG4CPLUS_ERROR(log,"", msg);
		else if (level == LLL_WARN)
			LOG4CPLUS_WARN(log,"", msg);
		else if (level == LLL_NOTICE)
			LOG4CPLUS_INFO(log,"", msg);
		else if (level == LLL_INFO)
			LOG4CPLUS_INFO(log,"", msg);
		else if (level == LLL_DEBUG)
			LOG4CPLUS_DEBUG(log,"", msg);
		else 
			LOG4CPLUS_TRACE(log,"", msg);
	}

	bool WebSocketServer::InitInstance()
	{
		bool result = true;
		lws_set_log_level(LLL_ERR | LLL_WARN | LLL_NOTICE | LLL_INFO | LLL_DEBUG | LLL_PARSER | LLL_HEADER | LLL_EXT | LLL_CLIENT | LLL_LATENCY, lwsl_log);
		memset(&m_Info, 0, sizeof(m_Info));
		m_Info.port = m_port;
		m_Info.protocols = protocols;
		m_Info.gid = -1;
		m_Info.uid = -1;
		m_Info.timeout_secs = 5;
		m_Info.user = this;

		static std::atomic<bool> initssl;
		if (initssl == false){
			initssl = true;
			m_Info.options = m_Info.options | LWS_SERVER_OPTION_ALLOW_NON_SSL_ON_SSL_PORT;
		}
	
		m_Info.options = m_Info.options | LWS_SERVER_OPTION_VALIDATE_UTF8;

		m_Info.ssl_cert_filepath = m_cert_path.c_str();
		//m_Info.ssl_ca_filepath = m_cert_path.c_str();
		m_Info.ssl_private_key_filepath = m_key_path.c_str();

		/*m_Info.ssl_cipher_list = "ECDHE-ECDSA-AES256-GCM-SHA384:"
			"ECDHE-RSA-AES256-GCM-SHA384:"
			"DHE-RSA-AES256-GCM-SHA384:"
			"ECDHE-RSA-AES256-SHA384:"
			"HIGH:!aNULL:!eNULL:!EXPORT:"
			"!DES:!MD5:!PSK:!RC4:!HMAC_SHA1:"
			"!SHA1:!DHE-RSA-AES128-GCM-SHA256:"
			"!DHE-RSA-AES128-SHA256:"
			"!AES128-GCM-SHA256:"
			"!AES128-SHA256:"
			"!DHE-RSA-AES256-SHA256:"
			"!AES256-GCM-SHA384:"
			"!AES256-SHA256";
			*/

		m_Context = lws_create_context(&m_Info);
		if (m_Context == NULL) {
			LOG4CPLUS_ERROR(log,"", "Creating libwebsocket context failed");
			result = false;
		}
		
		return result;
	}


	bool WebSocketServer::UnInitInstance()
	{
		bool result = true;
		//std::lock_guard<std::recursive_mutex>lck(wsClientSetMtx);
		if (m_Context) {
			lws_context_destroy(m_Context);
			m_Context = nullptr;
		}

		return result;

	}

	WSConnection::WSConnection(const std::string & ws, struct lws_context *ctx) :m_Context(ctx), m_url(ws), wsi(nullptr)
	{
		this->log = log4cplus::Logger::getInstance("wsclient");
		//LOG4CPLUS_DEBUG(log, m_SessionId << "WS:" << m_url);
		//LOG4CPLUS_DEBUG(log, m_SessionId << "context:" << m_Context);

		memset(&con_info, 0, sizeof(con_info));

		//LOG4CPLUS_TRACE(log, m_SessionId << "construction");

	}

	WSConnection::WSConnection(struct lws_context *ctx) :m_Context(ctx), wsi(nullptr)
	{
		this->log = log4cplus::Logger::getInstance("wsclient");

		//LOG4CPLUS_DEBUG(log, m_SessionId << "context:" << m_Context);

		memset(&con_info, 0, sizeof(con_info));

		//LOG4CPLUS_TRACE(log, m_SessionId << "construction");

	}

	WSConnection::WSConnection(struct lws * _wsi) :m_Context(nullptr), wsi(_wsi)
	{
		this->log = log4cplus::Logger::getInstance("wsclient");

		//LOG4CPLUS_DEBUG(log, "", m_SessionId << "wsi:" << wsi);
		m_Context = lws_get_context(wsi);
		//LOG4CPLUS_DEBUG(log, "", m_SessionId << "context:" << m_Context);

		WSClientSet.insert(std::make_pair(wsi, this));
		memset(&con_info, 0, sizeof(con_info));

		//LOG4CPLUS_TRACE(log,  "", m_SessionId << "construction");

	}

	WSConnection::~WSConnection()
	{
		//std::lock_guard<std::recursive_mutex>lck(wsClientSetMtx);
		if (WSClientSet.find(this->wsi) != WSClientSet.end())
			Close();

		WSClientSet.erase(this->wsi);
		//LOG4CPLUS_TRACE(log, m_SessionId << "deconstruct");
	}

	void WSConnection::Open()
	{
		if (this->wsi != nullptr)
			return;

		const char * prot = nullptr;
		char m_urlbuff[1024];

		memset(m_urlbuff, 0, sizeof(m_urlbuff));
		strncpy(m_urlbuff, m_url.c_str(), sizeof(m_urlbuff));

		if (lws_parse_uri(m_urlbuff, &prot, &con_info.address, &con_info.port, &con_info.path)) {
			LOG4CPLUS_ERROR(log, "", " parse uri error.");
			return;
		}

		std::string path = con_info.path;
		if (!path.empty() && path.compare(0,1,"/",1)){
			path = "/" + path;
			con_info.path = path.c_str();
		}

		if (!strcmp(prot, "http") || !strcmp(prot, "ws"))
			con_info.ssl_connection = 0;
		if (!strcmp(prot, "https") || !strcmp(prot, "wss"))
			con_info.ssl_connection = 1;


		con_info.context = m_Context;
		con_info.host = con_info.address;
		con_info.origin = con_info.address;
		con_info.userdata = this;
		//std::lock_guard<std::recursive_mutex>lck(wsClientSetMtx);
		wsi = lws_client_connect_via_info(&con_info);
		LOG4CPLUS_TRACE(log, "", "wsi:" << wsi);

		WSClientSet.insert(std::make_pair(wsi, this));

		m_state = CONNECTING;

	}

	void WSConnection::Close()
	{
		//std::lock_guard<std::recursive_mutex>lck(wsClientSetMtx);
		if (WSClientSet.find(this->wsi) != WSClientSet.end() && this->wsi)
		{
			if (this->m_state == OPEN)
			{
				this->m_state = CLOSING;
				//WSClientSet.erase(this->wsi);
				lws_callback_on_writable(wsi);
				lws_cancel_service(m_Context);
			}
		}

	}

	int WSConnection::Send(const char* lpBuf, int nBufLen)
	{
		//std::lock_guard<std::recursive_mutex>lck(wsClientSetMtx);
		std::vector<unsigned char> data(LWS_PRE);
		data.insert(data.end(), lpBuf, lpBuf + nBufLen);
		m_sendBuf.push_back(data);

		if (WSClientSet.find(this->wsi) != WSClientSet.end() && this->wsi && this->m_state == OPEN) {
			lws_callback_on_writable(this->wsi);
			lws_cancel_service(m_Context);
		}
		else {
			LOG4CPLUS_ERROR(log, ""," closed");
		}

		return 0;
	}


	void WSConnection::OnOpen()
	{
		LOG4CPLUS_DEBUG(log, "", "OnOpen");
	}

	void WSConnection::OnSend()
	{
		LOG4CPLUS_TRACE(log, "", "OnSend");
	}

	void WSConnection::OnClose(const std::string & ErrorCode)
	{
		LOG4CPLUS_DEBUG(log, "", "OnClose:" << ErrorCode);
	}

	void WSConnection::OnError(const std::string & errorCode)
	{
		LOG4CPLUS_DEBUG(log, "", "OnError:" << errorCode);
	}

	void WSConnection::OnMessage(const std::string & message)
	{
		LOG4CPLUS_DEBUG(log, "", "OnMessage:" << message);
	}

	void WSConnection::SetWSUrl(const std::string & url)
	{
		this->m_url = url;
		LOG4CPLUS_DEBUG(log, "", "WS:" << this->m_url);
	}

	const std::string & WSConnection::GetWSUrl()
	{
		return this->m_url;
	}

	long WSConnection::GetStatus()
	{
		return m_state;
	}

}
