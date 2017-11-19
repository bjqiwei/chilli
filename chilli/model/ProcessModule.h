#pragma once
#ifndef _CHILLI_CTI_PROCESS_MODULE_HEADER_
#define _CHILLI_CTI_PROCESS_MODULE_HEADER_
#include "..\CEventBuffer.h"
#include "Extension.h"
#include <map>
#include <memory>
#include "TypeDef.h"
#include <log4cplus/logger.h>

namespace chilli{
namespace model{

typedef std::map<std::string, ExtensionPtr> ExtensionMap;
class ProcessModule :public fsm::SendInterface
{
public:
	explicit ProcessModule(const std::string & modelId);
	virtual ~ProcessModule();

	virtual bool LoadConfig(const std::string & configContext) = 0;
	virtual int Start();
	virtual int Stop();
	virtual ExtensionMap GetExtensions() final;

	//Only define a copy constructor and assignment function, these two functions can be disabled
	ProcessModule(const ProcessModule & other) = delete;
	ProcessModule & operator=(const ProcessModule &) = delete;
	virtual void PushEvent(const EventType_t & event) final;
	static void OnTimerExpiredFunc(unsigned long timerId, const std::string & attr, void * userdata);

	bool addExtension(const std::string &ext, ExtensionPtr & extptr);
	void removeExtension(const std::string & ext);
	ExtensionPtr getExtension(const std::string & ext);

public:
	log4cplus::Logger log;
	static std::vector<std::shared_ptr<model::ProcessModule>> g_Modules;
private:
	static std::recursive_mutex g_ExtMtx;
	static model::ExtensionMap g_Extensions;

	model::ExtensionMap m_Extensions;

protected:
	helper::CEventBuffer<EventType_t> m_RecEvtBuffer;
	std::atomic<bool> m_bRunning = false;
private:
	std::thread m_thread;
	void run();
};
typedef std::shared_ptr<model::ProcessModule> ProcessModulePtr;
}
}
#endif //end process module header