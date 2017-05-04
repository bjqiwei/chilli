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
	virtual bool LoadConfig(const std::string & configContext) override;
	virtual model::ExtensionPtr newExtension(const model::ExtensionConfigPtr & config) override;
private:
	//inherit from SendInterface
	virtual void fireSend(const std::string &strContent, const void * param) override;
};
}
}
#endif // end ivr header

