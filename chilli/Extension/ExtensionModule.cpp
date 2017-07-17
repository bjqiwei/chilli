#include "ExtensionModule.h"
#include "ExtensionImp.h"
#include "../model/ConnectAdapter.h"
#include <log4cplus/loggingmacros.h>
#include <memory>
#include "../tinyxml2/tinyxml2.h"

// ExtensionModule

namespace chilli {
	namespace Extension {

		// Constructor of the ExtensionModule 
		ExtensionModule::ExtensionModule(const std::string & id) :ProcessModule(id)
		{
			log = log4cplus::Logger::getInstance("chilli.ExtensionModule");
			LOG4CPLUS_DEBUG(log, "Constuction a  module.");
		}

		// Destructor of ExtensionModule
		ExtensionModule::~ExtensionModule()
		{
			LOG4CPLUS_DEBUG(log, "Destruction a module.");
		}

		bool ExtensionModule::LoadConfig(const std::string & configContext)
		{
			using namespace tinyxml2;
			tinyxml2::XMLDocument config;
			if (config.Parse(configContext.c_str()) != XMLError::XML_SUCCESS)
			{
				LOG4CPLUS_ERROR(log, "load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
				return false;
			}

			tinyxml2::XMLElement * extensions = config.FirstChildElement();
			//extensions 
			for (XMLElement *child = extensions->FirstChildElement("Extension");
				child != nullptr;
				child = child->NextSiblingElement("Extension"))
			{
				const char * num = child->Attribute("ExtensionNumber");
				const char * sm = child->Attribute("StateMachine");
				num = num ? num : "";
				sm = sm ? sm : "";

				model::ExtensionPtr ext(new ExtensionImp(this, num, sm));
				if (ext != nullptr && addExtension(num,ext)) {
					ext->setVar("_extension.Extension", num);
				}
				else {
					LOG4CPLUS_ERROR(log, "alredy had extension:" << num);
				}
			}

			return true;
		}

		void ExtensionModule::fireSend(const std::string & strContent, const void * param)
		{
			LOG4CPLUS_DEBUG(log, strContent);
			LOG4CPLUS_WARN(log, "fireSend not implement.");
		}
	}
}

