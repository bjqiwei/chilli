#include "CallModule.h"
#include "Call.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/json.h>


namespace chilli{
namespace Call{

CallModule::CallModule(const std::string & id):ProcessModule(id)
{
	log =log4cplus::Logger::getInstance("chilli.CallModule");
	LOG4CPLUS_DEBUG(log, this->getId() << " Constuction a Call module.");
}


CallModule::~CallModule(void)
{
	LOG4CPLUS_DEBUG(log, this->getId() << " Destruction a ACD module.");
}


bool CallModule::LoadConfig(const std::string & configContext)
{
	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if(config.Parse(configContext.c_str()) != XMLError::XML_SUCCESS) 
	{ 
		LOG4CPLUS_ERROR(log, this->getId() << " load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}
	
	tinyxml2::XMLElement * ecall = config.FirstChildElement();
	const char * sm = ecall->Attribute("StateMachine");
	m_SMFileName = sm ? sm : "";
	return true;
}


void CallModule::fireSend(const std::string & strContent, const void * param)
{
	LOG4CPLUS_WARN(log, this->getId() << " fireSend not implement.");
}

}
}
