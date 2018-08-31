#pragma once
#include "../Device/Device.h"
#include <log4cplus/logger.h>


namespace chilli{
namespace Group {

	class Group :public Device::Device {
	public:
		Group(model::ProcessModule * model, const std::string &ext, const std::string &smFileName);
		virtual ~Group();

		//inherit from SendInterface
		virtual void fireSend(const fsm::FireDataType & fireData, const void * param) override;

	protected:
		void processSend(const fsm::FireDataType & fireData, const void * param, bool & bHandled);

	};
	typedef std::shared_ptr<Group>  GroupImpPtr;
}
}