#include "IVRModule.h"
#include "../Extension/ExtensionImp.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/json.h>


namespace chilli{
namespace IVR{


IVRModule::IVRModule(const std::string & id):ProcessModule(id)
{
	log =log4cplus::Logger::getInstance("chilli.IVRModule");
	LOG4CPLUS_DEBUG(log, "Constuction a IVR module.");
}


IVRModule::~IVRModule(void)
{
	if (m_bRunning){
		Stop();
	}

	for (auto & it : m_Extensions) {
		g_Extensions.erase(it.first);
	}

	LOG4CPLUS_DEBUG(log, "Destruction a IVR module.");
}

int IVRModule::Stop(void)
{
	LOG4CPLUS_DEBUG(log,"Stop  IVR module");
	if (m_bRunning) {
		m_bRunning = false;
		for (auto & it : m_Extensions) {
			it.second->Stop();
		}
	}
	return 0;
}

int IVRModule::Start()
{
	LOG4CPLUS_DEBUG(log, "Start  IVR module");
	if (!m_bRunning){
		m_bRunning = true;
		for (auto & it : m_Extensions) {
			it.second->Start();
		}
	}
	return 0;
}

bool IVRModule::LoadConfig(const std::string & configContext)
{
	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if (config.Parse(configContext.c_str()) != XMLError::XML_SUCCESS){
		LOG4CPLUS_ERROR(log, "load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}


	for (XMLElement *child = config.FirstChildElement("Extension"); 
		child != nullptr; 
		child = child->NextSiblingElement("Extension")) {

		const char * num = child->Attribute("ExtensionNumber");
		const char * sm = child->Attribute("StateMachine");
		num = num ? num : "";
		sm = sm ? sm : "";
		if (this->g_Extensions.find(num) == this->g_Extensions.end())
		{
			model::ExtensionPtr ext(new Extension::ExtensionImp(this, num, sm));
			this->g_Extensions[num] = ext;
			this->m_Extensions[num] = ext;
		}
		else {
			LOG4CPLUS_ERROR(log, "alredy had extension:" << num);
		}
	}
	return true;
}

const model::ExtensionMap & IVRModule::GetExtension()
{
	return m_Extensions;
}

void IVRModule::fireSend(const std::string &strContent, const void * param)
{
	LOG4CPLUS_WARN(log, "fireSend not implement.");
}
}
}
