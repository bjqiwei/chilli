#include "Datamodel.h"
#include "Data.h"
#include <log4cplus/loggingmacros.h>

namespace fsm
{
namespace model
{

	Datamodel::Datamodel(const std::string &filename, uint32_t lineno)
	{
	}

	void Datamodel::addData(std::shared_ptr<Data> data)
	{
		m_Datas.push_back(data);
	}
}
}

