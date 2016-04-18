#ifndef WEBSOCKET_CLASS
#define WEBSOCKET_CLASS

#include <log4cplus/logger.h>
#include <string>
#include <libwebsockets.h>

namespace WebSocket{
	class websocketserver{
	public:
		explicit websocketserver(int port = CONTEXT_PORT_NO_LISTEN);
		virtual~websocketserver();
	private:
		struct lws_context_creation_info info;
		struct lws_context *context;
		bool bInit;
		int m_port;
		log4cplus::Logger log;
	public:
		bool InitInstance();
		bool UnInitInstance();
		struct lws_context * GetContext();
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
		struct lws_context *context;
		struct lws_client_connect_info con_info;
		struct lws *wsi;
		std::string m_url;
		std::vector<unsigned char> m_sendBuf;
	};
}

#endif//end header file
