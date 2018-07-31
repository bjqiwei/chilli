#include "ProcessModule.h"
#include <log4cplus/loggingmacros.h>
#include "ConnectAdapter.h"

namespace chilli{
namespace model{
	std::recursive_mutex ProcessModule::g_PEMtx;
	model::PerformElementMap ProcessModule::g_PerformElements;
	std::vector<ProcessModulePtr> ProcessModule::g_Modules;

	ProcessModule::ProcessModule(const std::string & modelId) :SendInterface(modelId),
		m_Id(modelId)
	{
	}

	ProcessModule::~ProcessModule()
	{
		if (m_bRunning) {
			Stop();
		}

		for (auto & it = m_PerformElements.begin(); it != m_PerformElements.end();) {
			removePerfromElement(it++->first);
		}

	}

	int ProcessModule::Start()
	{
		if (!m_bRunning) {
			m_bRunning = true;
			m_thread = std::thread(&ProcessModule::run, this);
		}
		else {
			LOG4CPLUS_WARN(log, this->getId() << " already running for this module.");
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

	/*
	PerformElementMap  ProcessModule::GetExtensions()
	{
		// TODO: insert return statement here
		std::unique_lock<std::recursive_mutex> lck(g_PEMtx);
		return g_PerformElements;
	}
	*/

	void ProcessModule::PushEvent(const EventType_t & Event)
	{
		
		const Json::Value & jsonEvent = Event.event;

		if (!jsonEvent["extension"].isArray()) {

			std::string peId;
			if (jsonEvent["extension"].isString()) {
				peId = jsonEvent["extension"].asString();
			}

			//
			auto peptr = getPerformElement(peId);
			if (peptr != nullptr){
				peptr->m_model->m_RecEvtBuffer.Put(Event);
				return;
			}
			else {

				LOG4CPLUS_WARN(log, this->getId() << " not find extension by event:" << Event.event.toStyledString());
				return;
			}
		}
		else {
			for (size_t i = 0; i < jsonEvent["extension"].size(); i++) {

				std::string peId;
				if (jsonEvent["extension"][i].isString()) {
					peId = jsonEvent["extension"][i].asString();
				}

				chilli::model::EventType_t newEvent(Event.event);
				newEvent.event["extension"] = peId;

				auto extptr = getPerformElement(peId);
				if (extptr != nullptr) {
					extptr->m_model->m_RecEvtBuffer.Put(newEvent);
					continue;
				}
				else {
					LOG4CPLUS_WARN(log, this->getId() << " not find extension by event:" << newEvent.event.toStyledString());
				}
				
			}
		}
	}

	void ProcessModule::run()
	{
		LOG4CPLUS_INFO(log, this->getId() << "Starting...");
		try
		{
			for (auto & it : m_PerformElements) {
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
						std::string peId;
						if (jsonEvent["extension"].isString()) {
							peId = jsonEvent["extension"].asString();
						}

						auto extptr = getPerformElement(peId);

						if (extptr != nullptr) {
							extptr->pushEvent(Event);
							extptr->mainEventLoop();
						}
						else {
							LOG4CPLUS_WARN(log, this->getId() << " not find extension:" << peId);
						}
					}
				}
				catch (std::exception & e)
				{
					LOG4CPLUS_ERROR(log, e.what());
				}
			}

			for (auto & it : m_PerformElements) {
				it.second->Stop();
			}
		}
		catch (std::exception & e)
		{
			LOG4CPLUS_ERROR(log, this->getId() << " " << e.what());
		}

		LOG4CPLUS_INFO(log, this->getId() << " Stoped.");
		log4cplus::threadCleanup();
	}
	
	void ProcessModule::OnTimer(unsigned long timerId, const std::string & attr, void * userdata)
	{
		Json::Value jsonEvent;
		Json::Reader jsonReader;
		std::string peId;

		if (jsonReader.parse(attr, jsonEvent)) {
			jsonEvent["extension"] = jsonEvent["sessionId"];

			if (jsonEvent["extension"].isString()) {
				peId = jsonEvent["extension"].asString();
			}
		}
		chilli::model::EventType_t evt(jsonEvent);
		m_RecEvtBuffer.Put(evt);
	}

	log4cplus::Logger ProcessModule::getLogger()
	{
		return this->log;
	}

	const std::string ProcessModule::getId()
	{
		return m_Id;
	}

	bool ProcessModule::addPerformElement(const std::string &peId, PerformElementPtr & peptr)
	{
		std::unique_lock<std::recursive_mutex> lck(g_PEMtx);
		if (this->g_PerformElements.find(peId) == this->g_PerformElements.end()){
			this->g_PerformElements[peId] = peptr;
			this->m_PerformElements[peId] = peptr;
			return true;
		}
		return false;
	}

	void ProcessModule::removePerfromElement(const std::string & peId)
	{
		std::unique_lock<std::recursive_mutex> lck(g_PEMtx);
		this->g_PerformElements.erase(peId);
		this->m_PerformElements.erase(peId);
	}

	chilli::model::PerformElementPtr ProcessModule::getPerformElement(const std::string & peId)
	{
		std::unique_lock<std::recursive_mutex> lck(g_PEMtx);
		auto & it = this->m_PerformElements.find(peId);
		if (it != this->m_PerformElements.end()) {
			return it->second;
		}

		it = this->g_PerformElements.find(peId);
		if (it != this->g_PerformElements.end()) {
			return it->second;
		}

		return nullptr;
	}

}
}