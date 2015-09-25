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
	void DisplayEventInfo(const std::string &) const;

};
}
}
#endif // end acd header

