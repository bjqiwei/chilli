#pragma once
#include <string>
#include "Action.h"

namespace fsm
{
namespace model
{

	class Raise :public Action
	{
	public:
		Raise(const std::string &filename, uint32_t lineno);
		virtual ~Raise(void);

		virtual void execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId)const override;
		const std::string &getEvent()const;
		void setEvent(const std::string & event);
	private:
		std::string m_strEvent;
	};
	
}//end namespace model
}//end namespace fsm

