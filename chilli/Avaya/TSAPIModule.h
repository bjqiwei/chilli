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

		protected:
			//inherit from SendInterface
			virtual void fireSend(const std::string &strContent, const void * param) override;

			// This function is used to Open a communication Channel(in the form of ACS Stream) for the application to send csta request
			bool OpenStream(const char * serviceId, const char * userId, const char * password);		// for opening an ACS Stream

			bool CloseStream();
			void processSend(const std::string &strContent, const void * param, bool & bHandled, model::PerformElement * pe);
			
			ACSHandle_t m_lAcsHandle = 0;	// Handle for ACS Stream
			ATTPrivateData_t m_stPrivateData;	// Private Data for using extended features of TSAPI service
			std::atomic_uint32_t m_ulInvokeID = 1;			// This application uses, Application generated InvokeID
			std::string m_ServiceID;
			std::string m_UserID;
			std::string m_Password;
			
			std::map<uint32_t, std::string>m_InvokeID2Extension;
			std::map<uint32_t, std::string>m_InvokeID2Event;
			std::map<uint32_t, std::string>m_monitorID2Extension;

			std::map<std::string, bool>m_ACDExts;
			std::string findIdleACD(uint32_t callid = 0);
			std::map<std::string, uint32_t>m_callid2ACDExtenion;
			std::string findACDByCallid(uint32_t callid);
			void removeAcdExtension(const std::string & ext);
			std::map<uint32_t, std::string>m_callid2UUID;

			std::thread m_thread;
			void run();
			friend class AvayaAgent;
			friend class AvayaExtension;
			friend class AvayaVDN;
			friend class AvayaACD;

		};
	}
}

