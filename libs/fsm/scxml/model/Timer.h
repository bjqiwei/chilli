#pragma once

#include <string>
#include "Action.h"



namespace   fsm{
namespace model{

	class  Timer:public Action{
	public:
		Timer(const std::string &filename, uint32_t lineno);
		virtual ~Timer();

		const std::string& getId() const;
		void setId(const std::string &id);
		const std::string& getIdExpr() const;
		void setIdExpr(const std::string idexpr);

		uint64_t getInterval() const;
		void setInterval(const std::string & interval);
		const std::string& getIntervalExpr() const;
		void setIntervalExpr(const std::string & intervalexpr);

		virtual  void execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId) const override;

	private:
		std::string id;
		std::string idexpr;
		std::string interval;
		std::string intervalexpr;
		Json::Value jsonInterval;
	};
}
}