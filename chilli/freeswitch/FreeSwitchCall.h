#pragma once
#include "..\Extension\ExtensionImp.h"
#include <log4cplus\logger.h>


namespace chilli{
namespace FreeSwitch {
	class FreeSwitchModule;
	class FreeSwitchCall :public Extension::ExtensionImp {
	public:
		FreeSwitchCall(FreeSwitchModule * model, const std::string &ext, const std::string &smFileName);
		virtual ~FreeSwitchCall();

		//inherit from SendInterface
		virtual void fireSend(const std::string &strContent, const void * param) override;
		virtual void mainEventLoop() override;
		virtual bool IsFinalState() override;
		virtual void Start() override;
		virtual void Stop() override;

	protected:
		void processSend(const std::string &strContent, const void * param, bool & bHandled);
	private:
		FreeSwitchModule * m_model;
		typedef std::shared_ptr<fsm::StateMachine> Call;
		std::map<std::string, Call> m_Calls;
		std::map<std::string, std::string>m_ConnectID2CallID;
		std::map<std::string, std::string>m_ConnectID2ConnectID;

	};
	typedef std::shared_ptr<FreeSwitchCall>  FreeSwitchCallPtr;
}
}