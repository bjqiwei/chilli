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
	explicit IVRModule(const std::string & id);
	virtual ~IVRModule(void);
	virtual int Start() override;
	virtual int Stop() override;
	virtual bool LoadConfig(const std::string & configContext) override;
	virtual const model::ExtensionMap & GetExtension() override;
private:
	//inherit from SendInterface
	virtual void fireSend(const std::string &strContent, const void * param) override;
private:
	log4cplus::Logger log;
	std::thread m_Thread;
	std::atomic_bool bRunning = false;
	void run();
};
}
}
#endif // end ivr header

