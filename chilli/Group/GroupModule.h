#pragma once

#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <string>
#include <atomic>
#include <thread>

namespace chilli {
namespace Group {
	class GroupModule :public model::ProcessModule
	{

	public:
		explicit GroupModule(const std::string & id);
		~GroupModule();

		virtual int Start() override;
		virtual int Stop() override;
		virtual bool LoadConfig(const std::string & configContext) override;
		virtual const model::ExtensionMap &GetExtension() override;

	private:
		//inherit from SendInterface
		virtual void fireSend(const std::string &strContent, const void * param) override;

		log4cplus::Logger log;
		std::atomic_bool m_bRunning = false;
		model::ExtensionMap m_Extensions;

	};
}
}

