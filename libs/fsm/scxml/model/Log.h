#pragma once

#include <string>
#include "Action.h"

namespace fsm
{
namespace model
{
	/// </summary>
	class  Log :public Action
	{
	private:
		std::string m_strExpr;
		std::string m_strLevel;
		std::string m_Type;

	public:
		Log(const std::string &filename, uint32_t lineno);
		virtual ~Log(){};

		void setExpr(const std::string & expr);
		void setLevel(const std::string & level);
		void setType(const std::string & type);

		virtual  void execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId) const override;
	private:
		const std::string & getLevel() const;
		const std::string & getExpr() const;
		const std::string & getType() const;
	};
}
}
