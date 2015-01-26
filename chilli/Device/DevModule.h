#pragma once

#ifndef _CHILLI_CTI_DEVICE_MODULE_HEADER_
#define _CHILLI_CTI_DEVICE_MODULE_HEADER_

#include "..\model\ProcessModule.h"
#include "..\CEventBuffer.h"
#include "scxml\SMInstance.h"

namespace chilli{
namespace model{


class DevModule :
	public ProcessModule
{
public:
	DevModule(void);
	virtual ~DevModule(void);

	virtual bool ParserConfig(void) ;
	virtual bool reloadConfig(xmlNodePtr xNode) ;
	
protected:
	virtual bool Init(void);
	
private:

	//Only define a copy constructor and assignment function, these two functions can be disabled
	DevModule(const DevModule & other);
	DevModule & operator=(const DevModule &);

protected:
	//thread function
	static unsigned int __stdcall ThreadProc( void *pParam );


	static std::vector<chilli::model::ExtensionPtr> m_ExtensionVector;
public:
	static const std::vector<chilli::model::ExtensionPtr> & getExtVec();
	static void addEventToBuffer(std::string strContent);
	//State machine executer, one instance per thread
	static fsm::SMInstance smInstance;
	static helper::CEventBuffer<std::string> recEvtBuffer;

};
}
}
#endif //end dev module header