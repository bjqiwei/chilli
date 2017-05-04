#include "ExtensionModule.h"
#include "ExtensionImp.h"
#include "../model/ConnectAdapter.h"
#include <log4cplus/loggingmacros.h>
#include <memory>
#include "../tinyxml2/tinyxml2.h"

// ExtensionModule

namespace chilli {
	namespace Extension {

		enum ExtType {
			ExtensionType = 0,
		};


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

				model::ExtensionConfigPtr extConfig = newExtensionConfig(this, num, sm, ExtType::ExtensionType);
				if (extConfig != nullptr) {
					extConfig->m_Vars.push_back(std::make_pair("_extension.Extension", num));
				}
				else {
					LOG4CPLUS_ERROR(log, "alredy had extension:" << num);
				}
			}

			return true;
		}

		model::ExtensionPtr ExtensionModule::newExtension(const model::ExtensionConfigPtr & config)
		{
			if (config != nullptr)
			{
				if (config->m_ExtType == ExtType::ExtensionType) {
					model::ExtensionPtr ext(new ExtensionImp(this, config->m_ExtNumber, config->m_SMFileName));
					return ext;
				}
			}
			return nullptr;
		}


		void ExtensionModule::fireSend(const std::string & strContent, const void * param)
		{
			LOG4CPLUS_DEBUG(log, strContent);
			LOG4CPLUS_WARN(log, "fireSend not implement.");
		}
	}
}

