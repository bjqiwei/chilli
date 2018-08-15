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
		virtual void fireSend(const std::string &strContent, const void * param) override;

	protected:
		void processSend(Json::Value &jsonData, const void * param, bool & bHandled);

	};
	typedef std::shared_ptr<Group>  GroupImpPtr;
}
}