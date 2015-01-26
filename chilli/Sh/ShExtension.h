#pragma once

#ifndef _CHILLI_SHDEV_SHEXTENSION_HEADER_
#define _CHILLI_SHDEV_SHEXTENSION_HEADER_
#include "..\model\Extension.h"
#include <log4cplus\logger.h>

namespace chilli{
namespace ShDev{


class ShExtension :public model::Extension
{
public:
	ShExtension(void);
	virtual ~ShExtension(void);
	virtual void fireSend(const std::string &strContent);

	virtual bool ParserConfig(void);
	virtual bool processTransfer(std::string strEvent,std::string from);
	virtual bool addAcdEvent(const std::string& strEvent) ;
	virtual int processCmd(const std::string& strCmd);
	virtual int processEvent(const std::string& strEvent);
	virtual bool Init(void);
	virtual int getChannelID();
	bool setType(std::string strType);
	void setType(int _type);
	virtual int Answer();
	virtual int PlayFile(std::string file);
	virtual int HangUp();

private:
	log4cplus::Logger log;
	int ch;
		
};
	typedef ShExtension * ShExtensionPtr;
}
}
#endif //end shextension header