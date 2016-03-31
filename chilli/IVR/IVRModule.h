#pragma once
#ifndef _CHILLI_IVRMODULE_HEADER_
#define _CHILLI_IVRMODULE_HEADER_
#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <scxml/SMInstance.h>
#include <common/Timer.h>
#include <thread>

namespace chilli{
namespace IVR{

class IVRModule :public model::ProcessModule, public fsm::SMInstance, public helper::CTimerNotify
{
public:
	IVRModule();
	virtual ~IVRModule(void);
	virtual int Start();
	virtual int Stop();
	virtual bool LoadConfig(const std::string & configFile);
	virtual const std::map<std::string, model::ExtensionPtr> GetExtension();

	virtual void OnTimerExpired(unsigned long timerId, const std::string & attr);
private:
	log4cplus::Logger log;
	std::vector<std::shared_ptr<std::thread>> m_Thread;
	std::map<std::string, model::ExtensionPtr> m_Extension;
	std::atomic<bool> bRunning;
	void run();
};
}
}
#endif // end ivr header

