#pragma once

#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <string>
#include <atomic>
#include <thread>
#include <acs.h>
#include <csta.h>
#include <attpriv.h>

namespace chilli {
	namespace Avaya {
		class TSAPIModule :public model::ProcessModule
		{

		public:
			explicit TSAPIModule();
			~TSAPIModule();

			virtual int Start() override;
			virtual int Stop() override;
			virtual bool LoadConfig(const std::string & configContext) override;
			virtual const model::ExtensionMap &GetExtension() override;

		private:
			// This function is used to Open a communication Channel(in the form of ACS Stream) for the application to send csta request
			bool OpenStream(const char * serviceId, const char * userId, const char * password);		// for opening an ACS Stream

			bool CloseStream();
			log4cplus::Logger log;
			model::ExtensionMap m_Extensions;
			ACSHandle_t m_lAcsHandle = 0;	// Handle for ACS Stream
			ATTPrivateData_t m_stPrivateData;	// Private Data for using extended features of TSAPI service
			InvokeID_t m_ulInvokeID = 1;			// This application uses, Application generated InvokeID
			std::string m_ServiceID;
			std::string m_UserID;
			std::string m_Password;
			std::thread m_thread;
			void run();

		};
	}
}

