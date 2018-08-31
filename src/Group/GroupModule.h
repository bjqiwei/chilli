#pragma once
#include "../model/ProcessModule.h"
#include <string>

namespace chilli {
namespace Group {
	class GroupModule :public model::ProcessModule
	{

	public:
		explicit GroupModule(const std::string & id, uint32_t threadSize = 16);
		~GroupModule();

		virtual int Start() override;
		virtual int Stop() override;
		virtual bool LoadConfig(const std::string & configContext) override;
		virtual void run() override;
		virtual void execute(helper::CEventBuffer<model::EventType_t> * eventQueue) override;

	private:
		//inherit from SendInterface
		virtual void fireSend(const fsm::FireDataType & fireData, const void * param) override;

	};
}
}

