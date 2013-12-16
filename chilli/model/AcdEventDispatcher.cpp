#include "StdAfx.h"
#include "AcdEventDispatcher.h"
#include <xmlHelper.h>
#include "..\acd\ACDModule.h"

namespace chilli{
AcdEventtDispatcher::AcdEventtDispatcher(void):EventDispatcher("acd")
{
	log = log4cplus::Logger::getInstance("chilli.model.AcdEventtDispatcher");
}


AcdEventtDispatcher::~AcdEventtDispatcher(void)
{

}

void AcdEventtDispatcher::fireSend(const std::string &strContent)
{
	chilli::ACD::ACDModule::recEvtBuffer.addData(strContent);
	LOG4CPLUS_TRACE(log, ": recive a Send event:" << strContent);
}

}
