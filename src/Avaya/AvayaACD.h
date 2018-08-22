#pragma once
#include "AvayaDevice.h"
#include <log4cplus/logger.h>


namespace chilli{
	namespace Avaya {

		class TSAPIModule;
		class AvayaACD :public AvayaDevice {
		public:
			AvayaACD(TSAPIModule * model, const std::string &ext, const std::string &smFileName);
			virtual ~AvayaACD();
		private:
			TSAPIModule * m_model = nullptr;
		};
		typedef std::shared_ptr<AvayaACD>  AvayaACDPtr;
	}
}