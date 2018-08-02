#pragma once
#include "..\CEventBuffer.h"
#include "PerformElement.h"
#include "FSM.h"
#include <map>
#include <memory>
#include "TypeDef.h"
#include <log4cplus/logger.h>

namespace chilli{
namespace model{

typedef std::map<std::string, PerformElementPtr> PerformElementMap;
class ProcessModule :public fsm::SendInterface, public fsm::OnTimerInterface
{
public:
	explicit ProcessModule(const std::string & modelId);
	virtual ~ProcessModule();

	virtual bool LoadConfig(const std::string & configContext) = 0;
	virtual int Start();
	virtual int Stop();

	virtual void PushEvent(const EventType_t & event) final;
	//virtual PerformElementMap GetExtensions() final;
	virtual bool addPerformElement(const std::string &peId, PerformElementPtr & extptr) final;
	virtual void removePerfromElement(const std::string & peId) final;
	virtual PerformElementPtr getPerformElement(const std::string & peId) final;
	virtual void OnTimer(unsigned long timerId, const std::string & attr, void * userdata) final;
	virtual const log4cplus::Logger & getLogger()final;
	virtual const std::string getId()final;

	static std::vector<std::shared_ptr<model::ProcessModule>> g_Modules;

protected:
	log4cplus::Logger log;
	const std::string m_Id;
	std::recursive_mutex m_PEMtx;
	model::PerformElementMap m_PerformElements;

	helper::CEventBuffer<EventType_t> m_RecEvtBuffer;
	std::atomic<bool> m_bRunning = false;
	std::thread m_thread;
	void run();

	//Only define a copy constructor and assignment function, these two functions can be disabled
	ProcessModule(const ProcessModule & other) = delete;
	ProcessModule & operator=(const ProcessModule &) = delete;
};
typedef std::shared_ptr<model::ProcessModule> ProcessModulePtr;
}
}