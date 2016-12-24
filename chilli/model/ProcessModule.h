#pragma once
#ifndef _CHILLI_CTI_PROCESS_MODULE_HEADER_
#define _CHILLI_CTI_PROCESS_MODULE_HEADER_
#include "..\CEventBuffer.h"
#include "Extension.h"
#include <map>
#include <memory>
#include <FSM.h>

namespace chilli{
namespace model{

typedef std::map<std::string, ExtensionPtr> ExtensionMap;
class ProcessModule :public fsm::SendInterface
{
public:
	explicit ProcessModule(const std::string & modelId):SendInterface(modelId){};
	virtual ~ProcessModule(){};

	virtual bool LoadConfig(const std::string & configContext) = 0;
	virtual int Start() = 0;
	virtual int Stop() = 0;
	virtual const ExtensionMap & GetExtension() = 0;

	//Only define a copy constructor and assignment function, these two functions can be disabled
	ProcessModule(const ProcessModule & other) = delete;
	ProcessModule & operator=(const ProcessModule &) = delete;
	virtual void PushEvent(const std::string & event) final
	{
		m_recEvtBuffer.Put(event);
	};
protected:
	helper::CEventBuffer<std::string> m_recEvtBuffer;
};
typedef std::shared_ptr<model::ProcessModule> ProcessModulePtr;
}
}
#endif //end process module header