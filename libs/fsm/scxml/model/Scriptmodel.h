#pragma once
#include "Script.h"
#include <string>


namespace fsm{
namespace model{


class Scriptmodel
{
public:
	Scriptmodel(const std::string &filename, uint32_t lineno);
	virtual ~Scriptmodel(void);
	void addScript(std::shared_ptr<model::Script> script);
	std::vector<std::shared_ptr<Script>> m_Scripts;

};
}// end namespace model
}// end namespace fsm
