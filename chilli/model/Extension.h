#pragma once
#ifndef _CHILLI_CTI_EXTENSION_HEADER_
#define _CHILLI_CTI_EXTENSION_HEADER_
#include <FSM.h>
#include <scxml/SendInterface.h>

namespace chilli{
namespace model{

class Extension
{
public:
	Extension(){};
	virtual ~Extension(){};
	virtual bool setExtensionNumber(const std::string & number) = 0;
	virtual const std::string & getExtensionNumber() const = 0;
	virtual bool setEnable(const std::string &strEnable) = 0;
	virtual bool setEnable(const bool bEnable) = 0;
	virtual bool setXmlConfigNode(xmlNodePtr xNodePtr) = 0;
	virtual bool isIdle() = 0;
	virtual void go() = 0;
	virtual void pushEvent(fsm::TriggerEvent &evt) = 0;
	virtual bool LoadConfig(void) = 0;
	virtual bool Init(void) = 0;
	virtual int processCmd(const std::string& strCmd) = 0;
	virtual int processEvent(const std::string& strEvent) = 0;

//media interface
	virtual int Answer() = 0;
	virtual int PlayFile(const std::string &fileName) = 0;
	virtual int HangUp() = 0;
private:
	//Only define a copy constructor and assignment function, these two functions can be disabled
	Extension(const Extension &);
	Extension & operator=(const Extension &);
};
typedef Extension * ExtensionPtr;
}
}
#endif // end extension header
