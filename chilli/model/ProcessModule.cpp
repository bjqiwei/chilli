#include "ProcessModule.h"
#include <log4cplus/loggingmacros.h>
#include <regex>

namespace chilli{
namespace model{
	std::vector<ProcessModulePtr> ProcessModule::g_Modules;
	std::recursive_mutex ProcessModule::g_PEMtx;
	model::PerformElementMap ProcessModule::g_PerformElements;

	ProcessModule::ProcessModule(const std::string & modelId) :SendInterface(modelId),
		m_Id(modelId)
	{
	}

	ProcessModule::~ProcessModule()
	{
		if (m_bRunning) {
			Stop();
		}

		for (auto it = m_PerformElements.begin(); it != m_PerformElements.end();) {
			removePerfromElement(it++->first);
		}

	}

	int ProcessModule::Start()
	{
		if (!m_bRunning) {
			m_bRunning = true;
			m_thread = std::thread(&ProcessModule::_run, this);
		}
		else {
			LOG4CPLUS_WARN(log, " already running for this module.");
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
		this->m_RecEvtBuffer.Put(Event);
	}

	void ProcessModule::_run()
	{
		return this->run();
	}

	void ProcessModule::run()
	{
		LOG4CPLUS_INFO(log, " Starting...");
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
						if (jsonEvent["id"].isString()) {
							peId = jsonEvent["id"].asString();
						}

						auto extptr = getPerformElement(peId);

						if (extptr != nullptr) {
							extptr->pushEvent(Event);
							extptr->mainEventLoop();
						}
						else {
							LOG4CPLUS_WARN(log, " not find device:" << peId);
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
			LOG4CPLUS_ERROR(log, e.what());
		}

		LOG4CPLUS_INFO(log, " Stoped.");
		log4cplus::threadCleanup();
	}
	
	void ProcessModule::OnTimer(unsigned long timerId, const std::string & attr, void * userdata)
	{
		Json::Value jsonEvent;
		Json::CharReaderBuilder b;
		std::shared_ptr<Json::CharReader> jsonReader(b.newCharReader());
		std::string jsonerr;
		std::string peId;

		if (jsonReader->parse(attr.c_str(),attr.c_str()+attr.length(), &jsonEvent, &jsonerr)) {
			jsonEvent["id"] = jsonEvent["sessionId"];

			if (jsonEvent["id"].isString()) {
				peId = jsonEvent["id"].asString();
			}
		}
		chilli::model::EventType_t evt(jsonEvent);
		m_RecEvtBuffer.Put(evt);
	}

	const log4cplus::Logger & ProcessModule::getLogger()
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

	PerformElementPtr ProcessModule::removePerfromElement(const std::string & peId)
	{
		std::unique_lock<std::recursive_mutex> lck(g_PEMtx);
		PerformElementPtr peptr;
		const auto & it = this->g_PerformElements.find(peId);
		if (it != this->g_PerformElements.end())
			peptr = it->second;

		this->g_PerformElements.erase(peId);
		this->m_PerformElements.erase(peId);

		return peptr;
	}

	chilli::model::PerformElementPtr ProcessModule::getPerformElement(const std::string & peId)
	{
		std::unique_lock<std::recursive_mutex> lck(g_PEMtx);
		const auto & it = this->m_PerformElements.find(peId);
		if (it != this->m_PerformElements.end()) {
			return it->second;
		}

		return nullptr;
	}

	chilli::model::PerformElementPtr ProcessModule::getPerformElementByGlobal(const std::string & peId)
	{
		std::unique_lock<std::recursive_mutex> lck(g_PEMtx);

		const auto & it = this->g_PerformElements.find(peId);
		if (it != this->g_PerformElements.end()) {
			return it->second;
		}

		return nullptr;
	}

}
}