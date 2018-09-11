#include "Scriptmodel.h"

namespace fsm{
namespace model{


Scriptmodel::Scriptmodel(const std::string & filename, uint32_t lineno)
{
}

void Scriptmodel::addScript(std::shared_ptr<model::Script> script)
{
	m_Scripts.push_back(script);
}

Scriptmodel::~Scriptmodel(void)
{
	m_Scripts.clear();
}
}//end namespace model
}// end namespace fsm
