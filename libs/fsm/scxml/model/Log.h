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
			const std::string & getExpr() const;
			void setExpr(const std::string & expr);
			const std::string & getLevel() const;
			void setLevel(const std::string & level);
			const std::string & getType() const;
			void setType(const std::string & type);

			virtual  void execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId) const override;
		};


	}
}
