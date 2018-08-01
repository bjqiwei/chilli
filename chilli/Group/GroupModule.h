#pragma once
#include "../model/ProcessModule.h"
#include <string>

namespace chilli {
namespace Group {
	class GroupModule :public model::ProcessModule
	{

	public:
		explicit GroupModule(const std::string & id);
		~GroupModule();

		virtual int Start() override;
		virtual int Stop() override;
		virtual bool LoadConfig(const std::string & configContext) override;

	private:
		//inherit from SendInterface
		virtual void fireSend(const std::string &strContent, const void * param) override;

	};
}
}

