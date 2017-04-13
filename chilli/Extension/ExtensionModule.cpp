#include "ExtensionModule.h"
#include "ExtensionImp.h"
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
			if (m_bRunning) {
				Stop();
			}

			for (auto & it : m_Extensions) {
				g_Extensions.erase(it.first);
			}

			LOG4CPLUS_DEBUG(log, "Destruction a module.");
		}

		int ExtensionModule::Start()
		{
			if (!m_bRunning){
				m_bRunning = true;

				for (auto & it : m_Extensions) {
					it.second->Start();
				}

				m_thread = std::thread(&ExtensionModule::run, this);
				
			}
			else {
				LOG4CPLUS_WARN(log, "already running for this module.");
			}
			return 0;
		}

		int ExtensionModule::Stop()
		{
			if (m_bRunning) {
				m_bRunning = false;
				chilli::model::EventType_t stopEvent(Json::nullValue);
				this->PushEvent(stopEvent);

				for (auto & it : m_Extensions) {
					it.second->Stop();
				}

				if (m_thread.joinable()) {
					m_thread.join();
				}
			}
			return 0;
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
				if (this->g_Extensions.find(num) == this->g_Extensions.end())
				{
					model::ExtensionPtr ext(new ExtensionImp(this, num, sm));
					this->g_Extensions[num] = ext;
					this->m_Extensions[num] = ext;
				}
				else {
					LOG4CPLUS_ERROR(log, "alredy had extension:" << num);
				}
			}

			return true;
		}

		const model::ExtensionMap & ExtensionModule::GetExtension()
		{
			// TODO: insert return statement here
			return m_Extensions;
		}

		void ExtensionModule::fireSend(const std::string & strContent, const void * param)
		{
			LOG4CPLUS_DEBUG(log, strContent);
			LOG4CPLUS_WARN(log, "fireSend not implement.");
		}

		void ExtensionModule::run()
		{
			LOG4CPLUS_INFO(log, "Starting...");
			while (m_bRunning)
			{
				model::EventType_t Event;
				if (g_recEvtBuffer.Get(Event) && !Event.event.isNull())
				{
					const Json::Value & jsonEvent = Event.event;					

					if (!jsonEvent["extension"].isArray())
					{

						std::string ext;

						if (jsonEvent["extension"].isString()) {
							ext = jsonEvent["extension"].asString();
						}

						auto &it = g_Extensions.find(ext);

						if (it != g_Extensions.end()) {

							it->second->pushEvent(Event);
						}
						else {
							LOG4CPLUS_ERROR(log, " not find extension by event:" << Event.event.toStyledString());
						}
					}
					else {
						for (int i = 0; i < jsonEvent["extension"].size();i++) {

							std::string ext;
							if (jsonEvent["extension"][i].isString()){
								ext = jsonEvent["extension"][i].asString();
							}

							chilli::model::EventType_t newEvent(Event.event);
							newEvent.event["extension"] = ext;

							auto &it = g_Extensions.find(ext);

							if (it != g_Extensions.end()) {

								it->second->pushEvent(newEvent);
							}
							else {
								LOG4CPLUS_ERROR(log, " not find extension by event:" << newEvent.event.toStyledString());
							}
						}
					}
				}
			}

			LOG4CPLUS_INFO(log, "Stoped.");
			log4cplus::threadCleanup();
		}
	}
}

