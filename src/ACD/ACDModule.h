#pragma once
#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <atomic>

namespace chilli{
namespace ACD{

class ACDModule :public model::ProcessModule
{
public:
	explicit ACDModule(const std::string & id, uint32_t threadSize = 16);
	virtual ~ACDModule(void);
	virtual bool LoadConfig(const std::string & configContext) override;
	virtual void run() override;
	virtual void execute(helper::CEventBuffer<model::EventType_t> * eventQueue) override;
private:
	//inherit from SendInterface
	virtual void fireSend(const std::string &strContent, const void * param) override;
};
}
}

