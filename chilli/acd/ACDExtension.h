#pragma once
#ifndef _CHILLI_ACD_EXTENSION_HEADER_
#define _CHILLI_ACD_EXTENSION_HEADER_
#include "..\model\extension.h"
#include <log4cplus\logger.h>
#include <FSM.h>


namespace chilli{
namespace ACD{

class ACDExtension:public model::Extension{
public:
	ACDExtension();
	virtual ~ACDExtension();

public:
	virtual const std::string & getExtensionNumber() const;
	virtual bool isIdle();
	virtual void go();

	virtual void fireSend(const std::string &strContent, const void * param);
	virtual int pushEvent(const std::string &evt);

	//media interface
	virtual int Answer();
	virtual int PlayFile(const std::string &fileName);
	virtual int HangUp();

private:
	log4cplus::Logger log;
	fsm::StateMachine  m_SM;
	std::string m_ExtNumber;

};
typedef ACDExtension *  ACDExtensionPtr;
}
}
#endif // end ACD extension header