#pragma once
#ifndef _CHILLI_ACD_EXTENSION_HEADER_
#define _CHILLI_ACD_EXTENSION_HEADER_
#include "..\model\extension.h"
#include <log4cplus\logger.h>
#include <FSM.h>


namespace chilli{
namespace ACD{

class ACDExtension :public model::Extension, public fsm::SendInterface{
public:
	ACDExtension(const std::string &ext, const std::string &smFileName, fsm::SMInstance * smInstance);
	virtual ~ACDExtension();

public:
	virtual const std::string & getExtensionNumber() const;
	virtual bool isIdle();
	virtual void go();
	virtual void run();
	virtual void termination();
	virtual void setSessionId(const std::string & sessinId);
	virtual int pushEvent(const std::string &evt);

	//inherit from SendInterface
	virtual void fireSend(const std::string &strContent, const void * param);

	//media interface
	virtual int Answer();
	virtual int PlayFile(const std::string &fileName);
	virtual int HangUp();

private:
	log4cplus::Logger log;
	std::string m_ExtNumber;
	std::string m_SessionId;
	fsm::SMInstance *m_smInstance;
	fsm::StateMachine * m_SM;
};
typedef std::shared_ptr<ACDExtension>  ACDExtensionPtr;
}
}
#endif // end ACD extension header