#pragma once

#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <string>
#include <thread>
#include <set>

namespace chilli {
namespace Monitor {
	class MonitorModule :public model::ProcessModule
	{

	public:
		explicit MonitorModule(const std::string & id);
		~MonitorModule();

		virtual int Start() override;
		virtual int Stop() override;
		virtual bool LoadConfig(const std::string & configContext) override;
		virtual model::ExtensionPtr newExtension(const model::ExtensionConfigPtr & config) override;

	private:
		//inherit from SendInterface
		virtual void fireSend(const std::string &strContent, const void * param) override;
		std::thread m_thread;
		helper::CEventBuffer<std::string> m_StateEventBuf;
		std::map<std::string, Json::Value> m_Agents;
		std::set<std::string>m_MonitorExtension;
		virtual void run();

	};
}
}

