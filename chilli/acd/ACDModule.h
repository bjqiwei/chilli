#pragma once
#ifndef _CHILLI_ACDMODULE_HEADER_
#define _CHILLI_ACDMODULE_HEADER_
#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <thread>
#include <mutex>
#include <memory>

namespace chilli{
namespace ACD{

class ACDModule :public model::ProcessModule
{
public:
	explicit ACDModule(const std::string & id);
	virtual ~ACDModule(void);
	virtual int Start() override;
	virtual int Stop() override;
	virtual bool LoadConfig(const std::string & configContext) override;
	virtual const std::map<std::string, model::ExtensionPtr> &GetExtension() override;
private:
	//inherit from SendInterface
	virtual void fireSend(const std::string &strContent, const void * param) override;
private:
	log4cplus::Logger log;
	std::atomic_bool m_bRunning = false;
	model::ExtensionMap m_Extensions;
};
}
}
#endif // end acd header

