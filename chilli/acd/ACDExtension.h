#pragma once
#include "..\model\Extension.h"
#include <log4cplus\logger.h>


namespace chilli{
namespace ACD{

class ACDExtension :public model::Extension{
public:
	ACDExtension(model::ProcessModule * model, const std::string &ext, const std::string &smFileName);
	virtual ~ACDExtension();

public:
	virtual int pushEvent(const model::EventType_t &evt) override;

	//inherit from SendInterface
	virtual void fireSend(const std::string &strContent, const void * param) override;

	//media interface
	virtual int Answer() override;
	virtual int PlayFile(const std::string &fileName) override;
	virtual int HangUp() override;

private:
};
typedef std::shared_ptr<ACDExtension>  ACDExtensionPtr;
}
}