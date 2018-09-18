#pragma once

#include <string>
#include "Action.h"



namespace   fsm{
namespace model{

	class  Timer:public Action{
	public:
		Timer(const std::string &filename, uint32_t lineno);
		virtual ~Timer();

		void setId(const std::string &id);
		void setIdExpr(const std::string idexpr);
		void setInterval(const std::string & interval);
		void setIntervalExpr(const std::string & intervalexpr);
		virtual void execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId) const override;
		void execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId, std::string&id, uint64_t & interval) const;
	private:
		std::string id;
		std::string idexpr;
		std::string interval;
		std::string intervalexpr;
	private:
		const std::string& getId() const;
		const std::string& getIdExpr() const;
		uint64_t getInterval(const Json::Value & jsonInterval) const;
		const std::string& getIntervalExpr() const;
	};
}
}