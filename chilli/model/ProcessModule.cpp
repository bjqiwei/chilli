#include "stdafx.h"
#include "ProcessModule.h"
#include <log4cplus/loggingmacros.h>
namespace chilli{
namespace abstract{


ProcessModule::ProcessModule(void):m_xmlConfigNodePtr(NULL)
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
bool ProcessModule::setConfigNode(xmlNodePtr xNodePtr)
{
	this->m_xmlConfigNodePtr = xNodePtr;
	LOG4CPLUS_DEBUG(log,"set xmlConfigNode ." );
	return true;
}

}
}