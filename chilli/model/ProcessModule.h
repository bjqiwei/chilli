#pragma once
#ifndef _CHILLI_CTI_PROCESS_MODULE_HEADER_
#define _CHILLI_CTI_PROCESS_MODULE_HEADER_
#include <libxml/tree.h>
#include <log4cplus/logger.h>
#include <Windows.h>

namespace chilli{
namespace abstract{

class ProcessModule
{
public:
	ProcessModule(void);
	virtual ~ProcessModule(void);

	virtual bool Init(xmlNodePtr xNode) = 0;
	virtual bool reloadConfig(xmlNodePtr xNode) = 0;
	virtual bool Init(void) = 0;
	virtual void Start() = 0;
	virtual int Close(void) = 0;
	bool setConfigNode(xmlNodePtr xNodePtr);
	virtual bool ParserConfig(void) = 0 ;

protected:
	xmlNodePtr m_xmlConfigNodePtr;
	log4cplus::Logger log;

private:
	//Only define a copy constructor and assignment function, these two functions can be disabled
	ProcessModule(const ProcessModule & other);
	ProcessModule & operator=(const ProcessModule &);

	void InitializeInstanceFields();
};
struct thread_data {
	HANDLE thread_hnd;
	unsigned thread_id;
};

}
}
#endif //end process module header