#include "AvayaACD.h"
#include "TSAPIModule.h"

namespace chilli {
namespace Avaya {

	AvayaACD::AvayaACD(TSAPIModule * model, const std::string &ext, const std::string &smFileName)
		:m_model(model), AvayaDevice(model, ext, smFileName)
	{
		std::string logName = "AvayaACD";
		log = log4cplus::Logger::getInstance(logName);
	}

	AvayaACD::~AvayaACD()
	{
		m_model->removeAcdExtension(this->m_Id);
	}

}
}