#pragma once
#ifndef _CHILLI_CTI_EXTENSION_HEADER_
#define _CHILLI_CTI_EXTENSION_HEADER_
#include <string>
#include <memory>
#include <thread>
#include <atomic>
#include <FSM.h>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include "TypeDef.h"
#include <json/json.h>
#include <list>

namespace chilli{
namespace model{

class ExtensionConfig {
public:
	ExtensionConfig(class ProcessModule * model, const std::string &ext, const std::string &smFileName, uint32_t type);

	uint32_t m_ExtType = 0;
	class ProcessModule * m_model = nullptr;
	std::string m_ExtNumber;
	std::string m_SMFileName;
	std::list<std::pair<std::string, Json::Value>>  m_Vars;
};

typedef std::shared_ptr<model::ExtensionConfig> ExtensionConfigPtr;

class Extension: public fsm::SendInterface
{
public:
	Extension(class ProcessModule * model, const std::string &ext, const std::string &smFileName);

	virtual ~Extension();

	virtual void Start() final;

	virtual void Stop() final;
	virtual bool IsFinalState() final;

	bool AddSendImplement(SendInterface * evtDsp);

	bool setVar(const std::string &name, const Json::Value &value);

	virtual const std::string & getExtNumber() final;

	virtual int pushEvent(const EventType_t &evt) = 0;

	virtual void setSessionId(const std::string & sessinId) final;

	virtual const std::string & getSessionId()final;

	virtual log4cplus::Logger getLogger()final;

//media interface
	virtual int Answer() = 0;
	virtual int PlayFile(const std::string &fileName) = 0;
	virtual int HangUp() = 0;

	//Only define a copy constructor and assignment function, these two functions can be disabled
	Extension(const Extension &) = delete;
	Extension & operator=(const Extension &) = delete;
	friend class ProcessModule;

protected:
	fsm::StateMachine * m_SM = nullptr;
	class ProcessModule * m_model = nullptr;
	log4cplus::Logger log;
	std::string m_ExtNumber;
	std::string m_SessionId;

};
typedef std::shared_ptr<model::Extension> ExtensionPtr;
}
}
#endif // end extension header
