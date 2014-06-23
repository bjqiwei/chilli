#pragma once
#ifndef _CHILLI_ACD_EVENTDISPATCHER_HEADER
#define _CHILLI_ACD_EVENTDISPATCHER_HEADER
#include <scxml/EventDispatcher.h>
#include <log4cplus/logger.h>
namespace chilli
{

class AcdEventtDispatcher:public fsm::EventDispatcher
{
public:
	AcdEventtDispatcher(void);
	virtual ~AcdEventtDispatcher(void);
	virtual void fireSend(const std::string &strContent,void * param);
private:
	log4cplus::Logger log;

};

}
#endif
