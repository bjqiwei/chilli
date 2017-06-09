#include "MonitorModule.h"
#include "../model/ConnectAdapter.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"

// MonitorModule

namespace chilli {
namespace Monitor {

	// Constructor of the MonitorModule 
	MonitorModule::MonitorModule(const std::string & id) :ProcessModule(id)
	{
		log = log4cplus::Logger::getInstance("chilli.MonitorModule");
		LOG4CPLUS_DEBUG(log, "Constuction a  module.");
	}

	// Destructor of MonitorModule
	MonitorModule::~MonitorModule()
	{
		LOG4CPLUS_DEBUG(log, "Destruction a module.");
	}

	int MonitorModule::Stop(void)
	{
		LOG4CPLUS_DEBUG(log, "Stop module");
		if (m_bRunning) {
			ProcessModule::Stop();
			m_bRunning = false;

			m_StateEventBuf.Put(std::string());
			if (m_thread.joinable())
				m_thread.join();

		}
		return 0;
	}

	int MonitorModule::Start()
	{
		LOG4CPLUS_DEBUG(log, "Start module");
		if (!m_bRunning) {
			ProcessModule::Start();
			m_bRunning = true;
			m_thread = std::thread(&MonitorModule::run, this);
		}
		return 0;
	}

	bool MonitorModule::LoadConfig(const std::string & configContext)
	{
		return true;
	}

	model::ExtensionPtr MonitorModule::newExtension(const model::ExtensionConfigPtr & config)
	{
		return nullptr;
	}


	void MonitorModule::fireSend(const std::string & strContent, const void * param)
	{
		LOG4CPLUS_TRACE(log, strContent);
		m_StateEventBuf.Put(strContent);

	}
	void MonitorModule::run()
	{
		LOG4CPLUS_INFO(log, "Starting...");
		while (m_bRunning)
		{
			try
			{
				std::string strEvent;
				if (m_StateEventBuf.Get(strEvent) && !strEvent.empty())
				{
					LOG4CPLUS_DEBUG(log, "Process:" << strEvent);

					Json::Value jsonData;
					Json::Reader jsonReader;
					if (jsonReader.parse(strEvent, jsonData)) {
						if (jsonData["event"].asString() == "MonitorAgent")
						{
							std::string ext = jsonData["from"].asString();
							m_MonitorExtension.insert(ext);
							
							Json::Value monitorData;
							monitorData["type"] = "monitoragent";
							monitorData["data"] = Json::Value(Json::arrayValue);

							for (auto & it: m_Agents)
							{
								monitorData["data"].append(it.second);
							}
							
							monitorData["extension"] = ext;
							monitorData["event"] = "MonitorAgent";
							model::EventType_t evt(monitorData);
							this->PushEvent(evt);
						}

						else if (jsonData["event"].asString() == "MonitorEnd")
						{
							std::string ext = jsonData["from"].asString();
							m_MonitorExtension.erase(ext);
						}

						else {
							std::string ext = jsonData["from"].asString();
							m_Agents[ext] = jsonData["param"];

							Json::Value monitorData;
							monitorData["type"] = "monitoragent";
							monitorData["data"] = Json::Value(Json::arrayValue);

							monitorData["data"].append(jsonData["param"]);

							for (auto & it: m_MonitorExtension)
							{
								monitorData["extension"] = it;
								monitorData["event"] = "MonitorAgent";
								model::EventType_t evt(monitorData);
								this->PushEvent(evt);
							}

						}

					}
					else {
						LOG4CPLUS_ERROR(log, strEvent << " not json data.");
					}
				}

			}
			catch (std::exception & e)
			{
				LOG4CPLUS_ERROR(log, e.what());
			}
		}

		LOG4CPLUS_INFO(log, "Stoped.");
		log4cplus::threadCleanup();
	}
}
}

