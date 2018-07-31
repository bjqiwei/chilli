#pragma once
#include "..\Device\Device.h"
#include <log4cplus\logger.h>


namespace chilli{
namespace ACD{

class ACDDevice :public Device::Device{
public:
	ACDDevice(model::ProcessModule * model, const std::string &ext, const std::string &smFileName);
	virtual ~ACDDevice();

	virtual void mainEventLoop() override;

};
typedef std::shared_ptr<ACDDevice>  ACDDevicePtr;
}
}