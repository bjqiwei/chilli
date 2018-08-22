#pragma once
#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <thread>
#include <vector>

namespace chilli{
namespace Agent{

class AgentModule :public model::ProcessModule
{
public:
	explicit AgentModule(const std::string & id);
	virtual ~AgentModule(void);
	virtual bool LoadConfig(const std::string & configContext) override;
private:
	//inherit from SendInterface
	virtual void fireSend(const std::string &strContent, const void * param) override;

};
}
}

