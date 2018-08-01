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
	explicit IVRModule(const std::string & id);
	virtual ~IVRModule(void);
	virtual bool LoadConfig(const std::string & configContext) override;
private:
	//inherit from SendInterface
	virtual void fireSend(const std::string &strContent, const void * param) override;
};
}
}
#endif // end ivr header

