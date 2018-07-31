#pragma once
#include "..\model\PerformElement.h"
#include <log4cplus\logger.h>


namespace chilli{
namespace Agent{

class Agent :public model::PerformElement{
public:
	Agent(model::ProcessModule * model, const std::string &ext, const std::string &smFileName);
	virtual ~Agent();

public:
	virtual int pushEvent(const model::EventType_t &evt) override;

	//inherit from SendInterface
	virtual void fireSend(const std::string &strContent, const void * param) override;

	//media interface
	virtual int Answer() override;
	virtual int PlayFile(const std::string &fileName) override;
	virtual int HangUp() override;
protected:
	void processSend(const std::string &strContent, const void * param, bool & bHandled);

	uint64_t m_curConnectId = 0;
	uint64_t m_ConnectId = 0;
};
typedef std::shared_ptr<Agent>  AgentPtr;
}
}