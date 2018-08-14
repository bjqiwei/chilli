#pragma once
#include "..\Device\Device.h"
#include <log4cplus\logger.h>


namespace chilli{
	namespace Avaya {

		class TSAPIModule;
		class AvayaDevice :public Device::Device {
		public:
			AvayaDevice(TSAPIModule * model, const std::string &ext, const std::string &smFileName);
			virtual ~AvayaDevice();

			//inherit from SendInterface
			virtual void fireSend(const std::string &strContent, const void * param) override;

		protected:
			void processSend(Json::Value &jsonData, const void * param, bool & bHandled);
		private:
			TSAPIModule * m_model;

		};
		typedef std::shared_ptr<AvayaDevice>  AvayaDevicePtr;
	}
}