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
	virtual int Start();
	virtual int Stop();
	virtual bool LoadConfig();
private:
	log4cplus::Logger log;

public:
	static void addEventToBuffer(std::string strContent);
private:
	void DisplayEventInfo(const std::string &) const;

private:
	static helper::CEventBuffer<std::string> recEvtBuffer;
};
}
}
#endif // end acd header

