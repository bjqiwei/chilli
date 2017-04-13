#include "ACDExtension.h"
#include <log4cplus/loggingmacros.h>
#include <json/json.h>

namespace chilli{
namespace ACD{


ACDExtension::ACDExtension(model::ProcessModule * model, const std::string &ext, const std::string &smFileName) 
	:ExtensionImp(model, ext,smFileName)
{
	std::string logName = "ACD.";
	log = log4cplus::Logger::getInstance(logName.append(m_ExtNumber));
	LOG4CPLUS_DEBUG(log,"new a ACD extension object.");
}
ACDExtension::~ACDExtension(){
	LOG4CPLUS_DEBUG(log,"destruction a ACD extension object.");
}

}
}