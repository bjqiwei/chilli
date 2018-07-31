#pragma once
#include "..\model\PerformElement.h"
#include <log4cplus\logger.h>


namespace chilli{
	namespace Device {

		class Device :public model::PerformElement {
		public:
			Device(model::ProcessModule * model, const std::string &ext, const std::string &smFileName);
			virtual ~Device();

			//inherit from SendInterface
			virtual void fireSend(const std::string &strContent, const void * param) override;

			//media interface
			virtual int Answer() override;
			virtual int PlayFile(const std::string &fileName) override;
			virtual int HangUp() override;

		protected:
			void processSend(const std::string &strContent, const void * param, bool & bHandled);

		};
		typedef std::shared_ptr<Device>  ExtensionImpPtr;
	}
}