#pragma once
#include "../CEventBuffer.h"
#include "PerformElement.h"
#include "FSM.h"
#include <map>
#include <memory>
#include <atomic>
#include <thread>
#include "TypeDef.h"
#include <log4cplus/logger.h>

namespace chilli{
namespace model{

typedef std::map<std::string, PerformElementPtr> PerformElementMap;
class ProcessModule :public fsm::SendInterface, public fsm::OnTimerInterface
{
public:
	explicit ProcessModule(const std::string & modelId, uint32_t threadSize);
	virtual ~ProcessModule();

	virtual bool LoadConfig(const std::string & configContext) = 0;
	virtual int Start();
	virtual int Stop();

	virtual void PushEvent(const EventType_t & event) final;
	//virtual PerformElementMap GetExtensions() final;
	virtual bool addPerformElement(const std::string &peId, PerformElementPtr & extptr) final;
	virtual PerformElementPtr removePerfromElement(const std::string & peId) final;
	virtual PerformElementPtr getPerformElement(const std::string & peId) final;
	virtual PerformElementPtr getPerformElementByGlobal(const std::string & peId) final;
	virtual uint64_t getPerformElementCount();
	virtual void OnTimer(unsigned long timerId, const std::string & attr, void * userdata) final;
	virtual const log4cplus::Logger & getLogger()final;
	virtual const std::string getId()final;

	static std::vector<std::shared_ptr<model::ProcessModule>> g_Modules;

protected:
	log4cplus::Logger log;
	helper::CEventBuffer<EventType_t> m_RecEvtBuffer;
	std::atomic<bool> m_bRunning;
	typedef struct
	{
		std::thread th;
		helper::CEventBuffer<model::EventType_t> eventQueue;
	}TexecuteThread;

	std::vector<TexecuteThread> m_executeThread;
private:
	const std::string m_Id;
	static std::recursive_mutex g_PEMtx;
	model::PerformElementMap m_PerformElements;
	static model::PerformElementMap g_PerformElements;
	std::thread m_thread;
	void _run();
	virtual void run() = 0;
	void _execute(helper::CEventBuffer<model::EventType_t> * eventQueue);
	virtual void execute(helper::CEventBuffer<model::EventType_t> * eventQueue) = 0;

	//Only define a copy constructor and assignment function, these two functions can be disabled
	ProcessModule(const ProcessModule & other) = delete;
	ProcessModule & operator=(const ProcessModule &) = delete;
};
typedef std::shared_ptr<model::ProcessModule> ProcessModulePtr;
}
}