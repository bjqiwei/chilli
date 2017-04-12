#pragma once

#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <string>
#include <atomic>
#include <thread>
#include "AvayaAPI.h"

namespace chilli {
	namespace Avaya {
		class TSAPIModule :public model::ProcessModule
		{

		public:
			explicit TSAPIModule(const std::string & id);
			~TSAPIModule();

			virtual int Start() override;
			virtual int Stop() override;
			virtual bool LoadConfig(const std::string & configContext) override;
			virtual const model::ExtensionMap &GetExtension() override;

		protected:
			//inherit from SendInterface
			virtual void fireSend(const std::string &strContent, const void * param) override;

			// This function is used to Open a communication Channel(in the form of ACS Stream) for the application to send csta request
			bool OpenStream(const char * serviceId, const char * userId, const char * password);		// for opening an ACS Stream

			bool CloseStream();
			void processSend(const std::string &strContent, const void * param, bool & bHandled, model::Extension * ext);
			log4cplus::Logger log;
			ACSHandle_t m_lAcsHandle = 0;	// Handle for ACS Stream
			ATTPrivateData_t m_stPrivateData;	// Private Data for using extended features of TSAPI service
			std::atomic_uint32_t m_ulInvokeID = 1;			// This application uses, Application generated InvokeID
			std::string m_ServiceID;
			std::string m_UserID;
			std::string m_Password;
			std::thread m_thread;
			std::atomic<bool> m_bRunning = false;
			model::ExtensionMap m_Extensions;
			std::map<uint32_t, std::string>m_InvokeID2Extension;
			std::map<uint32_t, std::string>m_InvokeID2Event;
			std::map<uint32_t, std::string>m_monitorID2Extension;
			void run();
			friend class AvayaAgent;
			friend class AvayaExtension;
			friend class AvayaVDN;

		};
	}
}

