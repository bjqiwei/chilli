#pragma once
#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <atomic>

namespace chilli{
namespace Call{

class CallModule :public model::ProcessModule
{
public:
	explicit CallModule(const std::string & id);
	virtual ~CallModule(void);
	virtual bool LoadConfig(const std::string & configContext) override;

protected:
	void processSend(const std::string &strContent, const void * param, bool & bHandled);
private:
	//inherit from SendInterface
	virtual void fireSend(const std::string &strContent, const void * param) override;
	virtual void run() override;
	std::string m_SMFileName;
	typedef std::string sessionID;
	typedef std::string CallID;
	std::map<sessionID, CallID>m_Calls;
};
}
}

