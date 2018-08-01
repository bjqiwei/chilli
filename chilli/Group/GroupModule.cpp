#include "GroupModule.h"
#include "Group.h"
#include <log4cplus/loggingmacros.h>
#include <memory>
#include "../tinyxml2/tinyxml2.h"

// GroupModule

namespace chilli {
namespace Group {

	// Constructor of the GroupModule 
	GroupModule::GroupModule(const std::string & id) :ProcessModule(id)
	{
		log = log4cplus::Logger::getInstance("chilli.GroupModule");
		LOG4CPLUS_DEBUG(log, this->getId() << " Constuction a  module.");
	}

	// Destructor of GroupModule
	GroupModule::~GroupModule()
	{
		LOG4CPLUS_DEBUG(log, this->getId() << " Destruction a module.");
	}

	int GroupModule::Start()
	{
		int result = ProcessModule::Start();
		/*
		for (auto & it : GetExtensionConfig()) {
			Json::Value start;
			start["extension"] = it.first;
			start["event"] = "Start";
			chilli::model::EventType_t evt(start);
			this->PushEvent(evt);
		}
		*/
		return result;
	}

	int GroupModule::Stop()
	{
		return ProcessModule::Stop();
	}

	bool GroupModule::LoadConfig(const std::string & configContext)
	{
		using namespace tinyxml2;
		tinyxml2::XMLDocument config;
		if (config.Parse(configContext.c_str()) != XMLError::XML_SUCCESS)
		{
			LOG4CPLUS_ERROR(log, this->getId() << " load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
			return false;
		}

		tinyxml2::XMLElement * groups = config.FirstChildElement();
		//groups 
		for (XMLElement *child = groups->FirstChildElement("Group");
			child != nullptr;
			child = child->NextSiblingElement("Group"))
		{
			const char * num = child->Attribute("ExtensionNumber");
			const char * sm = child->Attribute("StateMachine");
			num = num ? num : "";
			sm = sm ? sm : "";

			model::PerformElementPtr ext(new Group(this, num, sm));
			if (ext != nullptr && addPerformElement(num,ext)) {
				ext->setVar("_extension.Extension", num);

				Json::Value extensions;

				for (XMLElement *extptr = child->FirstChildElement("Extension"); extptr != nullptr;
					extptr = extptr->NextSiblingElement("Extension"))
				{
					std::string extension = extptr->GetText() ? extptr->GetText() : "";
					extensions.append(extension);
				}

				ext->setVar("_extension.Extensions", extensions);
			}
			else {
				LOG4CPLUS_ERROR(log, this->getId() << " alredy had extension:" << num);
			}
		}

		return true;
	}

	void GroupModule::fireSend(const std::string & strContent, const void * param)
	{
		LOG4CPLUS_DEBUG(log, strContent);
		LOG4CPLUS_WARN(log, this->getId() << " fireSend not implement.");
	}
}
}

