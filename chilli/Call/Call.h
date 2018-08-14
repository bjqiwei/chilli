#pragma once
#include "..\model\PerformElement.h"
#include "../CEventBuffer.h"


namespace chilli{
namespace Call {
	class Call :public model::PerformElement {
	protected:
		typedef std::shared_ptr<fsm::StateMachine> StateMachine;
	public:
		Call(model::ProcessModule * model, const std::string &callid, const std::string &smFileName);
		virtual ~Call();

		virtual void Start() override;
		virtual void Stop() override;
		virtual bool IsClosed() override;
		virtual bool pushEvent(const model::EventType_t &evt) override;
		virtual void mainEventLoop() override;

		//inherit from SendInterface
		virtual void fireSend(const std::string &strContent, const void * param) override;

	protected:
		void processSend(Json::Value &jsonData, const void * param, bool & bHandled);
		std::map<std::string, StateMachine> m_StateMachines;
		const std::string m_SMFileName;
		helper::CEventBuffer<model::EventType_t> m_EvtBuffer;

	};
	typedef std::shared_ptr<Call> CallPtr;
}
}