#pragma once
#ifndef _CHILLI_CTI_PROCESS_MODULE_HEADER_
#define _CHILLI_CTI_PROCESS_MODULE_HEADER_
#include "..\CEventBuffer.h"
#include "Extension.h"
#include <vector>

namespace chilli{
namespace model{

class ProcessModule
{
public:
	explicit ProcessModule(){};
	virtual ~ProcessModule(){};

	virtual bool LoadConfig(const std::string & configFile) = 0;
	virtual int Start() = 0;
	virtual int Stop() = 0;
	virtual void PushEvent(const std::string & event)
	{
		m_recEvtBuffer.addData(event);
	};
	virtual std::vector<ExtensionPtr>GetExtension() = 0;
private:
	//Only define a copy constructor and assignment function, these two functions can be disabled
	ProcessModule(const ProcessModule & other);
	ProcessModule & operator=(const ProcessModule &);
	helper::CEventBuffer<std::string> m_recEvtBuffer;
};
}
}
#endif //end process module header