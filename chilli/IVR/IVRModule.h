#pragma once
#ifndef _CHILLI_IVRMODULE_HEADER_
#define _CHILLI_IVRMODULE_HEADER_
#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <thread>
#include <atomic>

namespace chilli{
namespace IVR{

class IVRModule :public model::ProcessModule
{
public:
	IVRModule();
	virtual ~IVRModule(void);
	virtual int Start() override;
	virtual int Stop() override;
	virtual bool LoadConfig(const std::string & configContext) override;
	virtual const model::ExtensionMap & GetExtension() override;
private:
	log4cplus::Logger log;
	std::thread m_Thread;
	std::atomic_bool bRunning = false;
	model::ExtensionMap m_Extensions;
	void run();
};
}
}
#endif // end ivr header

