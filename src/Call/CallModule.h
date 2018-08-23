#pragma once
#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <atomic>

namespace chilli{
namespace Call{

class CallModule :public model::ProcessModule
{
public:
	explicit CallModule(const std::string & id, uint32_t threadSize = 10);
	virtual ~CallModule(void);
	virtual int Start() override;
	virtual int Stop() override;
	virtual bool LoadConfig(const std::string & configContext) override;

protected:
	void processSend(Json::Value &jsonData, const void * param, bool & bHandled);
private:
	//inherit from SendInterface
	virtual void fireSend(const std::string &strContent, const void * param) override;
	virtual void run() override;
	typedef struct
	{
		std::thread th;
		helper::CEventBuffer<model::EventType_t> eventQueue;
	}TexecuteThread;

	std::vector<TexecuteThread> m_executeThread;

	void execute(helper::CEventBuffer<model::EventType_t> * eventQueue);
	std::string m_SMFileName;
	typedef std::string TSessionID;
	typedef std::string TCallID;
	std::mutex m_callMtx;
	std::map<TSessionID, TCallID>m_Calls;
	void setCallSession(const TSessionID & sessionid, const TCallID & callid);
	bool findCallBySession(const TSessionID & sessionid, TCallID & callid);
	void removeCallSession(const TSessionID & sessionid);
};
}
}

