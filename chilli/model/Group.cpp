#include "Group.h"
#include <log4cplus/loggingmacros.h>




namespace chilli
{
namespace model{
	
	Group::Group(const std::string &ext, const std::string &smFileName):Extension(ext,smFileName)
	{
		log = log4cplus::Logger::getInstance("chilli.model.Group");
		LOG4CPLUS_TRACE(log,"new a Group object.");
	}
	Group::~Group(){
		LOG4CPLUS_TRACE(log,"destruction a extension object.");
	}

}
}
