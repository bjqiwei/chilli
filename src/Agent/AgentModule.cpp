#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <event2/thread.h>

#pragma comment(lib,"ws2_32.lib")

#include "AgentModule.h"
#include "Agent.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/config.h>
#include <json/json.h>
#include "../websocket/websocket.h"


namespace chilli{
namespace Agent {

AgentModule::AgentModule(const std::string & id, uint32_t threadSize) :ProcessModule(id, threadSize)
{
	log = log4cplus::Logger::getInstance("chilli.AgentModule");
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " Constuction a Agent module.");
}


AgentModule::~AgentModule(void)
{
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " Destruction a Agent module.");
}


bool AgentModule::LoadConfig(const std::string & configContext)
{
	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if (config.Parse(configContext.c_str()) != XMLError::XML_SUCCESS)
	{
		LOG4CPLUS_ERROR(log, "." + this->getId(), " load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}

	tinyxml2::XMLElement * eAgent = config.FirstChildElement();

	for (XMLElement *child = eAgent->FirstChildElement("Agent");
		child != nullptr;
		child = child->NextSiblingElement("Agent"))
	{

		const char * num = child->Attribute("ExtensionNumber");
		const char * sm = child->Attribute("StateMachine");
		const char * password = child->Attribute("password");
		const char * extension = child->Attribute("Extension");

		num = num ? num : "";
		sm = sm ? sm : "";
		password = password ? password : "";
		extension = extension ? extension : "";

		model::PerformElementPtr ext(new Agent(this, num, sm));

		if (ext != nullptr && addPerformElement(num, ext)) {
			ext->setVar("_agent.AgentId", num);
			ext->setVar("_agent.Password", password);
			ext->setVar("_agent.Extension", extension);
		}
		else {
			LOG4CPLUS_ERROR(log, "." + this->getId(), " alredy had agent:" << num);
		}
	}

	return true;
}

void AgentModule::run()
{
}

void AgentModule::execute(helper::CEventBuffer<model::EventType_t>* eventQueue)
{
	fsm::threadIdle();
	fsm::threadCleanup();
	log4cplus::threadCleanup();
}


void AgentModule::fireSend(const std::string & strContent, const void * param)
{
	LOG4CPLUS_WARN(log, "." + this->getId(), " fireSend not implement.");
}
}
}