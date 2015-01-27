#pragma once
#ifndef _CHILLI_ACDMODULE_HEADER_
#define _CHILLI_ACDMODULE_HEADER_
#include "../model/ProcessModule.h"
#include "../CEventBuffer.h"
#include <log4cplus/logger.h>

namespace chilli{
namespace model{

class ACDModule:public model::ProcessModule
{
public:
	ACDModule(void);
	virtual ~ACDModule(void);
	virtual bool Init(void);
	virtual int Start();
	virtual int Stop(void);
	virtual bool ParserConfig(void);
	virtual bool reloadConfig();
public:
	static void addEventToBuffer(std::string strContent);
private:
	void DisplayEventInfo(const std::string &) const;
private:
	ACDModule(const ACDModule & other);
	ACDModule & operator=(const ACDModule &);
	log4cplus::Logger log;
private:
	static helper::CEventBuffer<std::string> recEvtBuffer;
};
}
}
#endif // end acd header

