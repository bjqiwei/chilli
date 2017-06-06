#include "AvayaACD.h"
#include "TSAPIModule.h"

namespace chilli {
namespace Avaya {

	AvayaACD::AvayaACD(TSAPIModule * model, const std::string &ext, const std::string &smFileName)
		:m_model(model), AvayaExtension(model, ext, smFileName)
	{
		std::string logName = "AvayaACD.";
		log = log4cplus::Logger::getInstance(logName.append(m_ExtNumber));
	}

	AvayaACD::~AvayaACD()
	{
		m_model->removeAcdExtension(this->m_ExtNumber);
	}

}
}