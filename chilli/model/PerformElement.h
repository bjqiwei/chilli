#pragma once
#ifndef _CHILLI_CTI_EXTENSION_HEADER_
#define _CHILLI_CTI_EXTENSION_HEADER_
#include <string>
#include <FSM.h>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include "TypeDef.h"
#include <json/json.h>
#include <map>
#include "../CEventBuffer.h"

namespace chilli{
namespace model{

class PerformElement: public fsm::SendInterface
{
protected:
	typedef std::shared_ptr<fsm::StateMachine> Connction;
public:
	PerformElement(class ProcessModule * model, const std::string &ext, const std::string &smFileName);

	virtual ~PerformElement();

	virtual void Start();
	virtual void Stop();
	virtual bool IsFinalState();

	virtual bool setVar(const std::string &name, const Json::Value &value);
	virtual Json::Value getVar(const std::string & name);

	virtual const std::string & getExtNumber() final;

	virtual int pushEvent(const EventType_t &evt);

	virtual void mainEventLoop();

	virtual void setSessionId(const std::string & sessinId) final;

	virtual const std::string & getSessionId()final;
	
	virtual std::string getStateId()final;

	virtual log4cplus::Logger getLogger()final;

//media interface
	virtual int Answer() = 0;
	virtual int PlayFile(const std::string &fileName) = 0;
	virtual int HangUp() = 0;

	//Only define a copy constructor and assignment function, these two functions can be disabled
	PerformElement(const PerformElement &) = delete;
	PerformElement & operator=(const PerformElement &) = delete;
	friend class ProcessModule;

protected:
	std::map<std::string, Connction> m_Connections;
	class ProcessModule * m_model = nullptr;
	log4cplus::Logger log;
	std::string m_ExtNumber;
	std::string m_SessionId;
	std::string m_SMFileName;
	std::string m_AgentID;
	helper::CEventBuffer<EventType_t> m_EvtBuffer;
	Json::Value m_Vars;

};
typedef std::shared_ptr<model::PerformElement> ExtensionPtr;
}
}
#endif // end extension header
