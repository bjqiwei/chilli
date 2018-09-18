#pragma once
#include <string>
#include "Action.h"

namespace fsm
{
namespace model
{


class Data :public Action
{


private:
	std::string m_strId;
	std::string m_strExpr;
public:
	Data(const std::string &filename, uint32_t lineno);
	void setId(const std::string &id) { m_strId = id; }
	void setExpr(const std::string &expr) { m_strExpr = expr; }
	virtual void execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId) const override;
	virtual bool isEnabledCondition(fsm::Context * ctx) const override;
private:
	const std::string  &getId() const;
	const std::string  &getExpr() const;
};

}
}
