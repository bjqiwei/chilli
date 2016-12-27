#pragma once
#ifndef _CHILLI_ACD_EXTENSION_HEADER_
#define _CHILLI_ACD_EXTENSION_HEADER_
#include "..\model\extension.h"
#include <log4cplus\logger.h>


namespace chilli{
namespace Agent{

class Agent :public model::Extension{
public:
	Agent(const std::string &ext, const std::string &smFileName);
	virtual ~Agent();

public:
	virtual const std::string & getExtensionNumber() const override;
	virtual void setSessionId(const std::string & sessinId) override;
	virtual const std::string & getSessionId() override;
	virtual int pushEvent(const model::EventType_t &evt) override;

	//inherit from SendInterface
	virtual void fireSend(const std::string &strContent, const void * param) override;

	//media interface
	virtual int Answer() override;
	virtual int PlayFile(const std::string &fileName) override;
	virtual int HangUp() override;

private:
	std::string m_ExtNumber;
	std::string m_SessionId;
	uint64_t m_curConnectId = 0;
	uint64_t m_ConnectId = 0;
};
typedef std::shared_ptr<Agent>  AgentPtr;
}
}
#endif // end ACD extension header