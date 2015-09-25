#include "StdAfx.h"
#include "DevModule.h"
#include <log4cplus/loggingmacros.h>

namespace chilli{
namespace model{


DevModule::DevModule(void)
{
	log = log4cplus::Logger::getInstance("chilli.DevModule");
	LOG4CPLUS_DEBUG(log,"new a DevModule object.");
}


DevModule::~DevModule(void)
{
	LOG4CPLUS_DEBUG(log,"destruction a DevModule object.");
}

}
}
