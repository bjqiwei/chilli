#pragma once

#include <string>
#include "Action.h"


namespace fsm
{
namespace model
{
	/// </summary>
	class  Script :public Action
	{
	private:
		//TLogFile * log;
		std::string m_content;
		std::string m_scriptFileName;

	public:
		Script(const std::string & filename, uint32_t lineno);

		void setContext(const std::string & context);
		void setFileName(const std::string & fileName);
		virtual  void execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId) const override;
	private:
		const std::string &getContent()const;
	};


}
}
