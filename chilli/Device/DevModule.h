#pragma once

#ifndef _CHILLI_CTI_DEVICE_MODULE_HEADER_
#define _CHILLI_CTI_DEVICE_MODULE_HEADER_

#include "..\model\ProcessModule.h"
#include "..\EventBuffer.h"
#include "scxml\SCInstance.h"
#include "..\model\Extension.h"

namespace chilli{
namespace abstract{


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
	static chilli::abstract::thread_data td;

	static std::vector<chilli::abstract::ExtensionPtr> m_ExtensionVector;
public:
	static const std::vector<chilli::abstract::ExtensionPtr> & getExtVec();
	static void addEventToBuffer(std::string strContent);
	//State machine executer, one instance per thread
	static fsm::SCInstance scInstance;
	static chilli::EventBuffer recEvtBuffer;

};
}
}
#endif //end dev module header