#pragma once
#ifndef _CHILLI_CTI_PROCESS_MODULE_HEADER_
#define _CHILLI_CTI_PROCESS_MODULE_HEADER_
#include <libxml/tree.h>
#include <log4cplus/logger.h>
#include <Windows.h>

namespace chilli{
namespace model{

class ProcessModule
{
public:
	explicit ProcessModule(xmlNodePtr xNodePtr):m_xmlConfigNodePtr(xNodePtr){};
	virtual ~ProcessModule(){};

	virtual bool reloadConfig() = 0;
	virtual int Start() = 0;
	virtual int Stop(void) = 0;

protected:
	xmlNodePtr m_xmlConfigNodePtr;

private:
	//Only define a copy constructor and assignment function, these two functions can be disabled
	ProcessModule(const ProcessModule & other);
	ProcessModule & operator=(const ProcessModule &);
};
}
}
#endif //end process module header