#include "ACDModule.h"
#include "ACDExtension.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"


namespace chilli{
namespace ACD{


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
bool ACDModule::LoadConfig(const std::string & configFile)
{
	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if(config.LoadFile(configFile.c_str()) != XMLError::XML_SUCCESS)
	{ 
		LOG4CPLUS_ERROR(log, "load config file error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}
	if (tinyxml2::XMLElement *eConfig  = config.FirstChildElement("Config")){
		if(tinyxml2::XMLElement *eACD = eConfig->FirstChildElement("ACDs"))
		{
			for (XMLElement *child = eACD->FirstChildElement("ACD"); child != nullptr; child = child->NextSiblingElement("ACD")){
				const char * num = child->Attribute("ExtensionNumber");
				const char * sm = child->Attribute("StateMachine");
				model::ExtensionPtr ext = new ACDExtension();
			}
		}
		else {
			LOG4CPLUS_ERROR(log, "config file missing ACDs element.");
			return false;
		}

	}
	else {
		LOG4CPLUS_ERROR(log, "config file missing Config element.");
		return false;
	}
	return true;
}

std::vector<model::ExtensionPtr> ACDModule::GetExtension()
{
	return std::vector <model::ExtensionPtr >();
}
}
}
