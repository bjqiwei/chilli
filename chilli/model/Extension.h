#pragma once
#ifndef _CHILLI_CTI_EXTENSION_HEADER_
#define _CHILLI_CTI_EXTENSION_HEADER_
#include <FSM.h>
#include <scxml/SendInterface.h>
#include "AcdProcess.h"

namespace chilli{
namespace abstract{

class Extension:public fsm::SendInterface
{
public:
	Extension(void);
	virtual ~Extension(void);

	bool setExtensionNumber(std::string & number);
	const std::string & getExtensionNumber();
	bool setEnable(std::string &strEnable);
	bool setEnable(bool bEnable);
	bool setXmlConfigNode(xmlNodePtr xNodePtr);
	bool setStateMachineFile(std::string smFile);
	bool isIdle();
	void go();
	void pushEvent(fsm::TriggerEvent &evt);
	const std::string getStateID();
	virtual bool ParserConfig(void) = 0;
	virtual bool Init(void) = 0;

	virtual int processCmd(const std::string& strCmd) = 0;
	virtual int processEvent(const std::string& strEvent) = 0;
	virtual int getChannelID();

	std::string m_CallerId;
	std::string m_CalleeId;
	std::string _event_data;
	std::string m_PendingReason;
protected:
	//log4cplus::Logger log;
	bool m_bEnable;
	xmlNodePtr m_xmlConfigNodePtr;
	std::string m_strExtensionNumber;
	std::string _stateMachieFile;
	bool NewConfig;
	fsm::StateMachine stateMachie;
	bool reload();
private:
	//Only define a copy constructor and assignment function, these two functions can be disabled
	Extension(const Extension &);
	Extension & operator=(const Extension &);

	//
	enum tagProperty {ExtensionNumber,Channel,Enable,EventData,CallerId,CalleeId,PendingReason};
};
typedef Extension * ExtensionPtr;
}
}
#endif // end extension header
