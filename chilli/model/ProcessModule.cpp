#include "ProcessModule.h"
#include <log4cplus/loggingmacros.h>
#include "ConnectAdapter.h"

namespace chilli{
namespace model{
	std::recursive_mutex ProcessModule::g_ExtMtx;
	model::ExtensionMap ProcessModule::g_Extensions;
	model::ExtensionConfigMap ProcessModule::g_ExtensionConfigs;
	std::vector<ProcessModulePtr> ProcessModule::g_Modules;

	std::recursive_mutex ProcessModule::g_GroupMtx;
	std::map<std::string, std::vector<std::string>> ProcessModule::g_ExtBelongGroup;
	std::map<std::string, std::vector<std::string>> ProcessModule::g_GroupHasExt;

	ProcessModule::ProcessModule(const std::string & modelId) :SendInterface(modelId)
	{
	}

	ProcessModule::~ProcessModule()
	{
		if (m_bRunning) {
			Stop();
		}

		for (auto & it : m_Extensions) {
			removeExtension(it.first);
		}

		for (auto & it: m_ExtensionConfigs)
		{
			deleteExtensionConfig(it.first);
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

	ExtensionMap  ProcessModule::GetExtension()
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

			auto extptr = getExtension(ext);

			if (extptr != nullptr) {
				extptr->m_model->m_RecEvtBuffer.Put(Event);
				return;
			}
			
			//
			auto extconfigptr = getExtensionConfig(ext);
			if (extconfigptr != nullptr){
				extconfigptr->m_model->m_RecEvtBuffer.Put(Event);
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

				auto extptr = getExtension(ext);

				if (extptr != nullptr) {
					extptr->m_model->m_RecEvtBuffer.Put(newEvent);
					continue;
				}

				auto extconfigptr = getExtensionConfig(ext);
				if (extconfigptr != nullptr) {
					extconfigptr->m_model->m_RecEvtBuffer.Put(newEvent);
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
			/*
			for (auto & it : m_Extensions) {
				for (auto & it2 : g_Modules) {
					it.second->AddSendImplement(it2.get());
				}
				it.second->AddSendImplement(it.second.get());
				it.second->Start();
			}
			*/
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


						auto & it = m_Extensions.find(ext);
						ExtensionPtr extptr = nullptr;
						if (it != m_Extensions.end())
						{
							extptr = it->second;
						}

						
						if (extptr == nullptr) {
							ExtensionConfigPtr config = getExtensionConfig(ext);
							extptr = newExtension(config);
							if (extptr != nullptr ){

								addExtension(ext, extptr);
								for (auto & it : config->m_Vars)
								{
									extptr->setVar(it.first,it.second);
								}
								// Group has extensions
								{
									auto & it = getExtByGroup(ext);
									Json::Value extensions;

									for (auto & it2 : it) {
										extensions.append(it2);
									}
									extptr->setVar("_extension.Extensions", extensions);
									
								}

								// extension belong group
								{
									auto & it = getGroupByExt(ext);
									Json::Value groups;

									for (auto & it2 : it) {
										groups.append(it2);
									}
									extptr->setVar("_extension.Groups", groups);
									
								}

								for (auto & it : g_Modules) {
									extptr->AddSendImplement(it.get());
								}

								extptr->AddSendImplement(extptr.get());
								extptr->Start();

							}
						}

						if (extptr != nullptr) {

							extptr->pushEvent(Event);
							extptr->m_SM->mainEventLoop();
							if (extptr->IsFinalState()) {
								removeExtension(ext);
								extptr->Stop();
							}
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

	ExtensionConfigPtr ProcessModule::newExtensionConfig(ProcessModule * model, const std::string & ext, const std::string & smFileName, uint32_t type)
	{
		std::unique_lock<std::recursive_mutex> lck(g_ExtMtx);
		if (g_ExtensionConfigs.find(ext) == g_ExtensionConfigs.end())
		{
			model::ExtensionConfigPtr extptr(new model::ExtensionConfig(model, ext, smFileName, type));
			g_ExtensionConfigs[ext] = extptr;
			m_ExtensionConfigs[ext] = extptr;
			return extptr;
		}
		return nullptr;
	}

	void ProcessModule::deleteExtensionConfig(const std::string & ext)
	{
		std::unique_lock<std::recursive_mutex> lck(g_ExtMtx);
		g_ExtensionConfigs.erase(ext);
		m_ExtensionConfigs.erase(ext);
	}

	ExtensionConfigPtr ProcessModule::getExtensionConfig(const std::string & ext)
	{
		std::unique_lock<std::recursive_mutex> lck(g_ExtMtx);
		auto & it = g_ExtensionConfigs.find(ext);
		if (it != g_ExtensionConfigs.end()){
			return it->second;
		}
		return nullptr;
	}

	ExtensionConfigMap ProcessModule::GetExtensionConfig()
	{
		std::unique_lock<std::recursive_mutex> lck(g_ExtMtx);
		return m_ExtensionConfigs;
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

	void ProcessModule::addExtToGroup(const std::string & group, const std::string & ext)
	{
		std::unique_lock<std::recursive_mutex> lck(g_GroupMtx);
		g_GroupHasExt[group].push_back(ext);
	}

	void ProcessModule::addGroupToExt(const std::string & ext, const std::string & group)
	{
		std::unique_lock<std::recursive_mutex> lck(g_GroupMtx);
		g_ExtBelongGroup[ext].push_back(group);
	}

	std::vector<std::string> ProcessModule::getExtByGroup(const std::string & group)
	{
		std::unique_lock<std::recursive_mutex> lck(g_GroupMtx);
		auto & it = g_GroupHasExt.find(group);
		if (it != g_GroupHasExt.end())
			return it->second;

		return std::vector<std::string>();
	}

	std::vector<std::string> ProcessModule::getGroupByExt(const std::string & ext)
	{
		std::unique_lock<std::recursive_mutex> lck(g_GroupMtx);
		auto & it = g_ExtBelongGroup.find(ext);
		if (it != g_ExtBelongGroup.end())
			return it->second;

		return std::vector<std::string>();
	}

}
}