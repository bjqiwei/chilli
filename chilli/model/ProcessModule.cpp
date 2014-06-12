#include "stdafx.h"
#include "ProcessModule.h"
#include <log4cplus/loggingmacros.h>
namespace chilli{
namespace abstract{


ProcessModule::ProcessModule(xmlNodePtr xNodePtr):m_xmlConfigNodePtr(xNodePtr)
{
	log = log4cplus::Logger::getInstance("chilli.abstract.ProcessModule");
	LOG4CPLUS_DEBUG(log,"new a ProcessModule object");
	InitializeInstanceFields();
}


ProcessModule::~ProcessModule(void)
{
	LOG4CPLUS_DEBUG(log,"destruction a ProcessModule object");
}
void ProcessModule::InitializeInstanceFields()
{
	
}


}
}