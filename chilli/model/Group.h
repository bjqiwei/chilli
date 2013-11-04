#pragma once
#ifndef _CHILLI_VIRTUALDEVICE_GROUP_HEADER_
#define _CHILLI_VIRTUALDEVICE_GROUP_HEADER_

#include <FSM.h>
#include <scxml/env/SimpleContext.h>
#include <scxml/env/SimpleEvaluator.h>
#include <scxml/SCInstance.h>
#include "AcdEventtDispatcher.h"
#include "Extension.h"

namespace chilli
{
namespace VD{

class Group:public abstract::Extension
{
public:
	Group();
	virtual ~Group();
	virtual bool Init(void);
	virtual bool ParserConfig(void);
	virtual bool processTransfer(std::string strEvent,std::string from);
	virtual bool addAcdEvent(const std::string& strEvent);
	virtual void fireSend(const std::string &strContent);
private:
	std::vector<std::string> m_ExtVec;
private:
	int processCmd(const std::string& strCmd);
	int processEvent(const std::string& strEvent);
public:
	static bool isGroupConfigNode(xmlNodePtr xGroupNode);
};
typedef Group * GroupPtr;


}
}
#endif // end header define

