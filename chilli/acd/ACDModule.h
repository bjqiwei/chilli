#pragma once
#ifndef _CHILLI_ACDMODULE_HEADER_
#define _CHILLI_ACDMODULE_HEADER_
#include "../model/ProcessModule.h"
#include "scxml/SMInstance.h"
#include "../model/Group.h"
#include "../CEventBuffer.h"

namespace chilli{
namespace ACD{

class ACDModule:public abstract::ProcessModule
{
public:
	ACDModule(void);
	virtual ~ACDModule(void);
	virtual bool Init(void);
	virtual void Start();
	virtual int Close(void);
	virtual bool ParserConfig(void);
	virtual bool reloadConfig();
	void	DisplayEventInfo ( std::string strEvent );

	static helper::CEventBuffer<std::string> recEvtBuffer;
	static fsm::SMInstance smInstance;
	static void addEventToBuffer(std::string strContent);
private:
	static std::vector<xmlNodePtr> m_DialPlanVector;
	static std::vector<VD::GroupPtr> m_GroupVec;

	ACDModule(const ACDModule & other);
	ACDModule & operator=(const ACDModule &);
	xmlNodePtr  isMatched(xmlNodePtr xExtNode,std::string strEvent);
	int processActions(xmlNodePtr xCondNode,std::string strEvent);
	int processTransfer(xmlNodePtr xAppNode ,std::string strEvent);

	static int EvtHandler(const std::string& strEvent);
	static unsigned int __stdcall ThreadProc( void *pParam );
	chilli::abstract::thread_data td;
};
}
}
#endif // end acd header

