#pragma once
#ifndef _CHILLI_VIRTUALDEVICE_GROUP_HEADER_
#define _CHILLI_VIRTUALDEVICE_GROUP_HEADER_

#include "Extension.h"
#include <log4cplus/logger.h>

namespace chilli
{
namespace model{

class Group:public Extension
{
public:
	Group();
	virtual ~Group();
	virtual bool Init(void);
	virtual bool ParserConfig(void);
	virtual bool processTransfer(std::string strEvent,std::string from);
	virtual bool addAcdEvent(const std::string& strEvent);
	virtual void fireSend(const std::string &strContent);
private:
	std::vector<std::string> m_ExtVec;
	log4cplus::Logger log;
private:
	int processCmd(const std::string& strCmd);
	int processEvent(const std::string& strEvent);
};
typedef Group * GroupPtr;

}
}
#endif // end header define

