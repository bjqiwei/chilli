#include "AvayaACD.h"

namespace chilli {
namespace Avaya {

	AvayaACD::AvayaACD(TSAPIModule * model, const std::string &ext, const std::string &smFileName)
		:AvayaExtension(model, ext, smFileName)
	{
		std::string logName = "AvayaACD.";
		log = log4cplus::Logger::getInstance(logName.append(m_ExtNumber));
	}

}
}