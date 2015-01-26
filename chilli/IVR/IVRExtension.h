#pragma once
#ifndef _CHILLI_IVR_EXTENSION_HEADER_
#define _CHILLI_IVR_EXTENSION_HEADER_
#include "..\model\extension.h"


namespace chilli{
namespace IVR{

class IVRExtension:public model::Extension{
public:
	IVRExtension();
	virtual ~IVRExtension();
private:
	int processCmd(const std::string& strCmd);
	int processEvent(const std::string& strEvent);

public:
	virtual bool Init(void);
	int EvtHandler(std::string strEvent);
	virtual bool ParserConfig(void);
	virtual void fireSend(const std::string &strContent);
	virtual bool processTransfer(std::string strEvent,std::string from);
	virtual bool addAcdEvent(const std::string& strEvent);
	friend class IVRModule;

};
typedef IVRExtension *  IVRExtensionPtr;
}
}
#endif // end ivr extension header