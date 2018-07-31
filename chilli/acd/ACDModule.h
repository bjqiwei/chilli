#pragma once
#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <atomic>

namespace chilli{
namespace ACD{

class ACDModule :public model::ProcessModule
{
public:
	explicit ACDModule(const std::string & id);
	virtual ~ACDModule(void);
	virtual bool LoadConfig(const std::string & configContext) override;

private:
	//inherit from SendInterface
	virtual void fireSend(const std::string &strContent, const void * param) override;
};
}
}

