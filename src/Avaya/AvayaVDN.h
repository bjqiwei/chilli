#pragma once
#include "../Device/Device.h"
#include <log4cplus/logger.h>


namespace chilli{
	namespace Avaya {

		class TSAPIModule;
		class AvayaVDN :public Device::Device {
		public:
			AvayaVDN(TSAPIModule * model, const std::string &ext, const std::string &smFileName);
			virtual ~AvayaVDN();

			virtual bool IsClosed() override;

			virtual bool pushEvent(const model::EventType_t &evt) override;
			virtual void mainEventLoop() override;

			//inherit from SendInterface
			virtual void fireSend(const fsm::FireDataType &fireData, const void * param) override;

		private:
			TSAPIModule * m_model;
			std::string m_stationNo;
			std::string m_companyid;
		};
		typedef std::shared_ptr<AvayaVDN>  AvayaVDNPtr;
	}
}