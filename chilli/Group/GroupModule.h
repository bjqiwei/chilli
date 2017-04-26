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

		virtual bool LoadConfig(const std::string & configContext) override;

	private:
		//inherit from SendInterface
		virtual void fireSend(const std::string &strContent, const void * param) override;

	};
}
}

