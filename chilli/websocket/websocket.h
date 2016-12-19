#ifndef WEBSOCKET_CLASS
#define WEBSOCKET_CLASS

#include <log4cplus/logger.h>
#include <libwebsockets.h>

namespace WebSocket {
	class WebSocketServer {
	public:
		explicit WebSocketServer(int port = CONTEXT_PORT_NO_LISTEN);
		virtual ~WebSocketServer();
	private:
		struct lws_context_creation_info m_Info;
		struct lws_context *m_Context;
		int m_port;
		log4cplus::Logger log;
	public:
		bool InitInstance();
		bool UnInitInstance();
		void Loop(int timeout_ms);
	};

	typedef enum {
	CONNECTING	= 0,// 	The connection is not yet open.
		OPEN		= 1,// 	The connection is open and ready to communicate.
		CLOSING 	= 2,// 	The connection is in the process of closing.
		CLOSED 		= 3,// 	The connection is closed or couldn't be opened.
	}Status;
	class websocketclient
	{
	public:
		explicit websocketclient(const std::string & ws, struct lws_context *ctx);
		explicit websocketclient(struct lws_context *context);
		explicit websocketclient(struct lws *);
		virtual ~websocketclient();

		void Open();
		void Close();
		int Send(const char * lpBuf, int nBufLen);
		void SetWSUrl(const std::string & url);
		const std::string & GetWSUrl();

		websocketclient(const websocketclient&) = delete;
		websocketclient& operator=(const websocketclient&) = delete;
		//websocketclient& operator=(const websocketclient&) volatile = delete;

	protected:
		Status m_state;
		virtual void OnOpen();
		virtual void OnSend();
		virtual void OnClose(const std::string & ErrorCode);
		virtual void OnError(const std::string & errorCode);
		virtual void OnMessage(const std::string & message);

		friend int callback_lws(struct lws *wsi, enum lws_callback_reasons reason,
			void *user, void *in, size_t len);
	private:
		log4cplus::Logger log;
		struct lws_context *m_Context;
		struct lws_client_connect_info con_info;
		struct lws *wsi;
		std::string m_url;
		std::vector<unsigned char> m_sendBuf;
		std::string m_SessionId;
	};
}

#endif//end header file
