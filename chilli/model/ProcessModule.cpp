#include "ProcessModule.h"
#include <log4cplus/loggingmacros.h>
#include "ConnectAdapter.h"

namespace chilli{
namespace model{
	std::recursive_mutex ProcessModule::g_ExtMtx;
	model::ExtensionMap ProcessModule::g_Extensions;
	std::vector<ProcessModulePtr> ProcessModule::g_Modules;

	ProcessModule::ProcessModule(const std::string & modelId) :SendInterface(modelId)
	{
	}

	ProcessModule::~ProcessModule()
	{
		if (m_bRunning) {
			Stop();
		}

		for (auto & it = m_Extensions.begin(); it != m_Extensions.end();) {
			removeExtension(it++->first);
		}

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

	ExtensionMap  ProcessModule::GetExtensions()
	{
		// TODO: insert return statement here
		std::unique_lock<std::recursive_mutex> lck(g_ExtMtx);
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

			//
			auto extptr = getExtension(ext);
			if (extptr != nullptr){
				extptr->m_model->m_RecEvtBuffer.Put(Event);
				return;
			}
			else {

				Json::Value originEvent = Event.event;
				originEvent["cause"] = 1;
				originEvent["mem"] = "not find this extension";
				Json::FastWriter writer;
				std::string errorStr = writer.write(originEvent);
				chilli::model::ConnectAdapter::Send(Event.connect, errorStr.c_str(), errorStr.length());

				LOG4CPLUS_ERROR(log, " not find extension by event:" << Event.event.toStyledString());
				return;
			}
		}
		else {
			for (size_t i = 0; i < jsonEvent["extension"].size(); i++) {

				std::string ext;
				if (jsonEvent["extension"][i].isString()) {
					ext = jsonEvent["extension"][i].asString();
				}

				chilli::model::EventType_t newEvent(Event.event);
				newEvent.event["extension"] = ext;

				auto extptr = getExtension(ext);
				if (extptr != nullptr) {
					extptr->m_model->m_RecEvtBuffer.Put(newEvent);
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
			for (auto & it : m_Extensions) {
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

						auto extptr = getExtension(ext);

						if (extptr != nullptr) {
							extptr->pushEvent(Event);
							extptr->mainEventLoop();
						}
						else {
							LOG4CPLUS_ERROR(log, "not find extension:" << ext);
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
		{
			std::unique_lock<std::recursive_mutex> lck(g_ExtMtx);
			auto & it = g_Extensions.find(ext);

			if (it != g_Extensions.end()) {
				it->second->m_model->PushEvent(evt);
			}
			else {
				LOG4CPLUS_ERROR(log, " not find extension by event:" << attr);
			}
		}
	}


	bool ProcessModule::addExtension(const std::string &ext, ExtensionPtr & extptr)
	{
		std::unique_lock<std::recursive_mutex> lck(g_ExtMtx);
		if (this->g_Extensions.find(ext) == this->g_Extensions.end()){
			this->g_Extensions[ext] = extptr;
			this->m_Extensions[ext] = extptr;
			return true;
		}
		return false;
	}

	void ProcessModule::removeExtension(const std::string & ext)
	{
		std::unique_lock<std::recursive_mutex> lck(g_ExtMtx);
		this->g_Extensions.erase(ext);
		this->m_Extensions.erase(ext);
	}

	chilli::model::ExtensionPtr ProcessModule::getExtension(const std::string & ext)
	{
		std::unique_lock<std::recursive_mutex> lck(g_ExtMtx);
		auto & it = this->m_Extensions.find(ext);
		if (it != this->m_Extensions.end()) {
			return it->second;
		}

		it = this->g_Extensions.find(ext);
		if (it != this->g_Extensions.end()) {
			return it->second;
		}

		return nullptr;
	}

}
}