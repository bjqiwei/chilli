#pragma once
#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <thread>
#include <atomic>

namespace chilli{
namespace IVR{

class IVRModule :public model::ProcessModule
{
public:
	explicit IVRModule(const std::string & id, uint32_t threadSize = 16);
	virtual ~IVRModule(void);
	virtual bool LoadConfig(const std::string & configContext) override;
	virtual void run() override;
	virtual void execute(helper::CEventBuffer<model::EventType_t> * eventQueue) override;
private:
	//inherit from SendInterface
	virtual void fireSend(const fsm::FireDataType & fireData, const void * param) override;
};
}
}

