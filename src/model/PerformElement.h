#pragma once
#include <string>
#include <FSM.h>
#include <log4cplus/logger.h>
#include "TypeDef.h"
#include <json/config.h>
#include <json/json.h>

namespace chilli{
namespace model{

class PerformElement: public fsm::SendInterface
{
public:
	PerformElement(class ProcessModule * model, const std::string &id);

	virtual ~PerformElement();

	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual bool IsClosed() = 0;

	virtual bool pushEvent(const EventType_t &evt) = 0;
	virtual void mainEventLoop() = 0;
	virtual void PushEvent(const EventType_t &evt) final;

	virtual const std::string & getId() final;
	virtual log4cplus::Logger getLogger()final;

	virtual bool setVar(const std::string &name, const Json::Value &value) final;
	virtual Json::Value getVar(const std::string & name) final;
	virtual void removeVar(const std::string & name) final;

	//Only define a copy constructor and assignment function, these two functions can be disabled
	PerformElement(const PerformElement &) = delete;
	PerformElement & operator=(const PerformElement &) = delete;
	friend class ProcessModule;

protected:
	class ProcessModule * m_model = nullptr;
	log4cplus::Logger log;
	const std::string m_Id;
	Json::Value m_Vars;

};
typedef std::shared_ptr<model::PerformElement> PerformElementPtr;
}
}
