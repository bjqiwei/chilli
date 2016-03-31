#pragma once
#ifndef _CHILLI_IVR_EXTENSION_HEADER_
#define _CHILLI_IVR_EXTENSION_HEADER_
#include "..\model\extension.h"
#include <log4cplus\logger.h>
#include <FSM.h>


namespace chilli{
namespace IVR{

class IVRExtension :public model::Extension, public fsm::SendInterface{
public:
	IVRExtension(const std::string &ext, const std::string &smFileName, fsm::SMInstance * smInstance);
	virtual ~IVRExtension();

	virtual const std::string & getExtensionNumber() const;
	virtual bool isIdle();
	virtual void go();
	virtual void run();
	virtual void termination();
	virtual void setSessionId(const std::string & sessinId);
	virtual const std::string & getSessionId();

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
typedef std::shared_ptr<IVRExtension>  IVRExtensionPtr;
}
}
#endif // end ivr extension header