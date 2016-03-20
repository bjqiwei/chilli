#pragma once
#ifndef _CHILLI_IVR_EXTENSION_HEADER_
#define _CHILLI_IVR_EXTENSION_HEADER_
#include "..\model\extension.h"
#include <log4cplus\logger.h>


namespace chilli{
namespace IVR{

class IVRExtension:public model::Extension{
public:
	IVRExtension();
	virtual ~IVRExtension();

public:
	int EvtHandler(std::string strEvent);
	virtual bool LoadConfig(void);
	virtual void fireSend(const std::string &strContent);
	virtual bool processTransfer(std::string strEvent,std::string from);
private:
	log4cplus::Logger log;

};
typedef IVRExtension *  IVRExtensionPtr;
}
}
#endif // end ivr extension header