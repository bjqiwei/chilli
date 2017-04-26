#include "ProcessModule.h"
#include <log4cplus/loggingmacros.h>
#include "ConnectAdapter.h"

namespace chilli{
namespace model{
	model::ExtensionMap ProcessModule::g_Extensions;

	ProcessModule::ProcessModule(const std::string & modelId) :SendInterface(modelId)
	{
	}

	ProcessModule::~ProcessModule()
	{
		if (m_bRunning) {
			Stop();
		}

		for (auto & it : m_Extensions) {
			g_Extensions.erase(it.first);
		}

		m_Extensions.clear();
	}

	int ProcessModule::Start()
	{
		if (!m_bRunning) {
			m_bRunning = true;
			m_thread = std::thread(&ProcessModule::run, this);
		}
		else {
			LOG4CPLUS_WARN(log, "already running for this module.");
		}
		return 0;
	}

	int ProcessModule::Stop()
	{
		if (m_bRunning) {
			m_bRunning = false;
			chilli::model::EventType_t stopEvent(Json::nullValue);
			this->m_RecEvtBuffer.Put(stopEvent);

			if (m_thread.joinable()) {
				m_thread.join();
			}
		}
		return 0;
	}

	const ExtensionMap & ProcessModule::GetExtension()
	{
		// TODO: insert return statement here
		return m_Extensions;
	}

	void ProcessModule::PushEvent(const EventType_t & Event)
	{
		
		const Json::Value & jsonEvent = Event.event;

		if (!jsonEvent["extension"].isArray()) {

			std::string ext;
			if (jsonEvent["extension"].isString()) {
				ext = jsonEvent["extension"].asString();
			}

			auto &it = m_Extensions.find(ext);

			if (it != m_Extensions.end()) {
				m_RecEvtBuffer.Put(Event);
				return;
			}
			
			it = g_Extensions.find(ext);
			if (it != g_Extensions.end()) {
				it->second->m_model->m_RecEvtBuffer.Put(Event);
				return;
			}
			else {

				Json::Value originEvent = Event.event;
				originEvent["status"] = 1;
				originEvent["mem"] = "not find this extension";
				Json::FastWriter writer;
				std::string errorStr = writer.write(originEvent);
				chilli::model::ConnectAdapter::Send(Event.connect, errorStr.c_str(), errorStr.length());

				LOG4CPLUS_ERROR(log, " not find extension by event:" << Event.event.toStyledString());
				return;
			}
		}
		else {
			for (int i = 0; i < jsonEvent["extension"].size(); i++) {

				std::string ext;
				if (jsonEvent["extension"][i].isString()) {
					ext = jsonEvent["extension"][i].asString();
				}

				chilli::model::EventType_t newEvent(Event.event);
				newEvent.event["extension"] = ext;

				auto & it = m_Extensions.find(ext);
				if (it != m_Extensions.end()){
					this->m_RecEvtBuffer.Put(newEvent);
					continue;
				}
				it = g_Extensions.find(ext);

				if (it != g_Extensions.end()) {
					it->second->m_model->m_RecEvtBuffer.Put(newEvent);
					continue;
				}
				else {
					LOG4CPLUS_ERROR(log, " not find extension by event:" << newEvent.event.toStyledString());
				}
				
			}
		}
	}

	void ProcessModule::run()
	{
		LOG4CPLUS_INFO(log, "Starting...");
		try
		{
			for (auto & it : m_Extensions){
				it.second->AddSendImplement(it.second.get());
				it.second->Start();
			}

			while (m_bRunning)
			{
				try
				{
					model::EventType_t Event;
					if (m_RecEvtBuffer.Get(Event) && !Event.event.isNull())
					{
						const Json::Value & jsonEvent = Event.event;
						std::string ext;
						if (jsonEvent["extension"].isString()) {
							ext = jsonEvent["extension"].asString();
						}

						auto &it = m_Extensions.find(ext);

						if (it != m_Extensions.end()) {

							it->second->pushEvent(Event);
							it->second->m_SM->mainEventLoop();
						}
					}
				}
				catch (std::exception & e)
				{
					LOG4CPLUS_ERROR(log, e.what());
				}
			}

			for (auto & it : m_Extensions) {
				it.second->Stop();
			}
		}
		catch (std::exception & e)
		{
			LOG4CPLUS_ERROR(log, e.what());
		}

		LOG4CPLUS_INFO(log, "Stoped.");
		log4cplus::threadCleanup();
	}

	void ProcessModule::OnTimerExpiredFunc(unsigned long timerId, const std::string & attr, void * userdata)
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("Timer");
		Json::Value jsonEvent;
		Json::Reader jsonReader;
		std::string ext;

		if (jsonReader.parse(attr, jsonEvent)) {
			jsonEvent["extension"] = jsonEvent["sessionId"];

			if (jsonEvent["extension"].isString()) {
				ext = jsonEvent["extension"].asString();
			}
		}
		chilli::model::EventType_t evt(jsonEvent);

		auto & it = g_Extensions.find(ext);

		if (it != g_Extensions.end()){
			it->second->m_model->PushEvent(evt);
		}
		else{
			LOG4CPLUS_ERROR(log, " not find extension by event:" << attr);
		}
	}
}
}