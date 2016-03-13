#pragma once
#ifndef _CHILLI_ACD_EXTENSION_HEADER_
#define _CHILLI_ACD_EXTENSION_HEADER_
#include "..\model\extension.h"


namespace chilli{
namespace ACD{

class ACDExtension:public model::Extension{
public:
	ACDExtension();
	virtual ~ACDExtension();
private:
	int processEvent(const std::string& strEvent);

public:
	virtual bool Init(void);
	int EvtHandler(std::string strEvent);
	virtual bool LoadConfig(void);
	virtual void fireSend(const std::string &strContent);
	virtual bool processTransfer(std::string strEvent,std::string from);
	virtual bool addAcdEvent(const std::string& strEvent);
private:
	log4cplus::Logger log;

};
typedef ACDExtension *  ACDExtensionPtr;
}
}
#endif // end ACD extension header