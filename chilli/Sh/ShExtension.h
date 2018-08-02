#pragma once
#include "..\Device\Device.h"
#include <log4cplus\logger.h>
#include <memory>

namespace chilli{
namespace ShDev{


class ShExtension :public Device::Device
{
public:
	ShExtension(model::ProcessModule * model, const std::string &ext, const std::string &smFileName);
	virtual ~ShExtension(void);


	virtual int getChannelID();
	bool setType(const std::string & strType);
	void setType(int _type);

	//inherit from SendInterface
	virtual void fireSend(const std::string &strContent, const void * param) override;
private:
	int ch;
		
};
typedef std::shared_ptr<ShExtension> ShExtensionPtr;
}
}