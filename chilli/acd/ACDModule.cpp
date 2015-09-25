#include "StdAfx.h"
#include "ACDModule.h"
#include <regex>
#include <log4cplus/loggingmacros.h>


namespace chilli{
namespace model{


ACDModule::ACDModule(void)
{
	log =log4cplus::Logger::getInstance("chilli.ACDModule");
	LOG4CPLUS_DEBUG(log,"Constuction a ACD object.");
}


ACDModule::~ACDModule(void)
{
	LOG4CPLUS_DEBUG(log,"Destruction a ACD object.");
}


void ACDModule::DisplayEventInfo (const std::string &strEvent )const
{
	LOG4CPLUS_INFO(log," Recive a event,event=" << strEvent);
}

int ACDModule::Stop(void)
{
	LOG4CPLUS_DEBUG(log,"Close a ACD device");
	return 0;
}

int ACDModule::Start()
{
	return 0;
}
bool ACDModule::LoadConfig()
{
	return false;
}

}
}
