#pragma once

#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <string>
#include <atomic>
#include <thread>

namespace chilli {
	namespace Extension {
		class ExtensionModule :public model::ProcessModule
		{

		public:
			explicit ExtensionModule(const std::string & id);
			~ExtensionModule();

			virtual bool LoadConfig(const std::string & configContext) override;
			virtual model::ExtensionPtr newExtension(const model::ExtensionConfigPtr & config) override;

		private:
			//inherit from SendInterface
			virtual void fireSend(const std::string &strContent, const void * param) override;

		};
	}
}

