#include "websocket.h"
#include <atomic>
#include <thread>
#include <condition_variable>
#include <log4cplus/loggingmacros.h>
#include <sstream>
#include <map>
#include <mutex>

namespace WebSocket{
	static std::atomic_flag bInit = ATOMIC_FLAG_INIT;
	static struct lws_context_creation_info info;
	static struct lws_context *context;
	static std::thread th;
	static std::map<websocketclient *, struct lws *> WSClientSet;
	static std::recursive_mutex wsClientSetMtx;
	std::atomic<bool> bRunning(false);

	/*
	* dumb_increment protocol
	*
	* since this also happens to be protocols[0], some callbacks that are not
	* bound to a specific protocol also turn up here.
	*/

	static int
		callback_lws(struct lws *wsi, enum lws_callback_reasons reason,
		void *user, void *in, size_t len)
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("callback_lws");

		websocketclient * wsclient = (websocketclient*)user;
		std::lock_guard<std::recursive_mutex> lcx(wsClientSetMtx);
		bool isdeconstruct = false;
		if (WSClientSet.find(wsclient) == WSClientSet.end()){
			isdeconstruct = true;
		}

		switch (reason) {

		case LWS_CALLBACK_CLIENT_ESTABLISHED:
		case LWS_CALLBACK_ESTABLISHED:
			if (!isdeconstruct) wsclient->OnOpen();
			break;

		case LWS_CALLBACK_CLOSED:
		case LWS_CALLBACK_CLOSED_HTTP:
		{
			std::string errorCode;
			if (in){
				errorCode.assign((char *)in, len);
			}
			if (!isdeconstruct) wsclient->OnClose(errorCode);
			WSClientSet.erase(wsclient);
		}
		break;

		case LWS_CALLBACK_CLIENT_RECEIVE:{
			std::string message;
			if (in){
				message.assign((char *)in, len);
			}
			if (!isdeconstruct) wsclient->OnMessage(message);
		}
		break;

		case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:{
			std::string errorCode;
			if (in){
				errorCode.assign((char *)in, len);
			}
			if (!isdeconstruct) wsclient->OnError(errorCode);
		}
		break;
		case LWS_CALLBACK_CLIENT_WRITEABLE:
			if (!isdeconstruct) {
				wsclient->OnSend();
				int bufLen = wsclient->m_sendBuf.size() - LWS_PRE;
				if (bufLen > 0)
				{
					int len = lws_write(wsi, wsclient->m_sendBuf.data() + LWS_PRE, bufLen, LWS_WRITE_BINARY);
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
			else{
				LOG4CPLUS_DEBUG(log, "Close a connection " << wsi);
				return -1;
			}
			break;
		case LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS:
			LOG4CPLUS_DEBUG(log, "LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS");
			break;
		case LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER:
			LOG4CPLUS_DEBUG(log, "LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER");
			break;
		case LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED:
			LOG4CPLUS_DEBUG(log, "LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED");
			break;
		case LWS_CALLBACK_PROTOCOL_INIT:
			LOG4CPLUS_DEBUG(log, "LWS_CALLBACK_PROTOCOL_INIT");
			break;
		case LWS_CALLBACK_WSI_CREATE:
			LOG4CPLUS_DEBUG(log, "LWS_CALLBACK_WSI_CREATE");
			break;
		case LWS_CALLBACK_WSI_DESTROY:
			LOG4CPLUS_DEBUG(log, "LWS_CALLBACK_WSI_DESTROY");
			break;
		case LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH:
		case LWS_CALLBACK_PROTOCOL_DESTROY:
		case LWS_CALLBACK_GET_THREAD_ID:
		case LWS_CALLBACK_ADD_POLL_FD:
		case LWS_CALLBACK_DEL_POLL_FD:
		case LWS_CALLBACK_CHANGE_MODE_POLL_FD:
		case LWS_CALLBACK_LOCK_POLL:
		case LWS_CALLBACK_UNLOCK_POLL:
			break;
		default:
			LOG4CPLUS_DEBUG(log, "Unknown:" << reason);
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

	static void Loop(struct lws_context *context, int timeout_ms)
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("WebSocket");
		LOG4CPLUS_DEBUG(log, __FUNCTION__ " start");
		while (bRunning){
			lws_service(context, timeout_ms);
		}
		LOG4CPLUS_DEBUG(log, __FUNCTION__ " end");

	}

	static bool InitInstance()
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("WebSocket");
		bool result = true;
		LOG4CPLUS_TRACE(log, __FUNCTION__ << " start");
		if (!bInit.test_and_set()){
			memset(&info, 0, sizeof(info));
			info.port = CONTEXT_PORT_NO_LISTEN;
			info.protocols = protocols;
			info.gid = -1;
			info.uid = -1;
			context = lws_create_context(&info);
			if (context == NULL) {
				LOG4CPLUS_ERROR(log, "Creating libwebsocket context failed\n");
				result = false;
			}
			bRunning = true;
			th = std::thread(Loop, context,500);
		}
		LOG4CPLUS_TRACE(log, __FUNCTION__ << " end");
		return result;
	}

	static bool UnInitInstance()
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("WebSocket");
		bool result = false;
		LOG4CPLUS_TRACE(log, __FUNCTION__ << " start");
		std::lock_guard<std::recursive_mutex>lck(wsClientSetMtx);
		if (WSClientSet.empty())
		{
			if (th.joinable())
			{
				bRunning = false;
				//th.join();
			}
			if (context)
			{
				lws_context_destroy(context);
				context = nullptr;
			}
			
			bInit.clear();
			result = true;
		}
		LOG4CPLUS_TRACE(log, __FUNCTION__ << " end");
		return result;
		
	}

	websocketclient::websocketclient(const std::string & ws) :m_url(ws), wsi(nullptr), m_state(CLOSED), m_sendBuf(LWS_PRE)
	{
		std::stringstream str;
		str << "websocketclient." << this;
		this->log = log4cplus::Logger::getInstance(str.str());
		LOG4CPLUS_DEBUG(log, "WS:" << ws);

		memset(&con_info, 0, sizeof(con_info));

		LOG4CPLUS_TRACE(log, "construction");

	}


	websocketclient::~websocketclient()
	{
		Close();
		LOG4CPLUS_TRACE(log, "deconstruct");
	}

	void websocketclient::Open()
	{
		LOG4CPLUS_TRACE(log, __FUNCTION__ << " start");
		const char * prot = nullptr;

		memset(m_urlbuff, 0, sizeof(m_urlbuff));
		strncpy_s(m_urlbuff, m_url.c_str(), sizeof(m_urlbuff));

		if (lws_parse_uri(m_urlbuff, &prot, &con_info.address, &con_info.port, &con_info.path))
			LOG4CPLUS_ERROR(log, "parse uri error.");

		if (!strcmp(prot, "http") || !strcmp(prot, "ws"))
			con_info.ssl_connection = 0;
		if (!strcmp(prot, "https") || !strcmp(prot, "wss"))
			con_info.ssl_connection = 1;

		WebSocket::InitInstance();

		con_info.context = context;
		con_info.host = con_info.address;
		con_info.origin = con_info.address;
		con_info.userdata = this;
		wsi = lws_client_connect_via_info(&con_info);
		LOG4CPLUS_TRACE(log, "wsi:" << wsi);

		std::lock_guard<std::recursive_mutex>lck(wsClientSetMtx);
		WSClientSet.insert(std::pair<websocketclient*, struct lws *>(this, wsi));

		m_state = CONNECTING;
		LOG4CPLUS_TRACE(log, __FUNCTION__ << " end");
	}

	void websocketclient::Close()
	{
		LOG4CPLUS_TRACE(log, __FUNCTION__ << " start");
		std::lock_guard<std::recursive_mutex>lck(wsClientSetMtx);
		if (WSClientSet.find(this) != WSClientSet.end())
		{
			lws_callback_on_writable(wsi);
			WSClientSet.erase(this);
		}
		WebSocket::UnInitInstance();
		LOG4CPLUS_TRACE(log, __FUNCTION__ << " end");

	}

	int websocketclient::Send(const char* lpBuf, int nBufLen)
	{
		LOG4CPLUS_TRACE(log, __FUNCTION__ << " start");
		std::lock_guard<std::recursive_mutex>lck(wsClientSetMtx);
		m_sendBuf.insert(m_sendBuf.end(), lpBuf, lpBuf + nBufLen);
		LOG4CPLUS_DEBUG(log, "Send:" << std::string(m_sendBuf.begin(), m_sendBuf.end()));
		if (WSClientSet.find(this) != WSClientSet.end())
		{
			lws_callback_on_writable(this->wsi);
			lws_cancel_service(context);
		}
		
		LOG4CPLUS_TRACE(log, __FUNCTION__ << " end");
		return 0;
	}
	

	void websocketclient::OnOpen()
	{
		LOG4CPLUS_DEBUG(log, "OnOpen");
	}

	void websocketclient::OnSend()
	{
		LOG4CPLUS_DEBUG(log, "OnSend");
	}

	void websocketclient::OnClose(const std::string & ErrorCode)
	{
		LOG4CPLUS_DEBUG(log, "OnClose:" << ErrorCode);
	}

	void websocketclient::OnError(const std::string & errorCode)
	{
		LOG4CPLUS_DEBUG(log, "OnError:" << errorCode);
	}

	void websocketclient::OnMessage(const std::string & message)
	{
		LOG4CPLUS_DEBUG(log, "OnMessage:" << message);
	}

	void websocketclient::SetWSUrl(const std::string & url)
	{
		this->m_url = url;
		LOG4CPLUS_DEBUG(log, "WS:" << this->m_url);
	}

	const std::string & websocketclient::GetWSUrl()
	{
		return this->m_url;
	}

}
