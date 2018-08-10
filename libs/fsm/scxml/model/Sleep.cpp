#include "Sleep.h"
#include "../../common/xmlHelper.h"
#include <thread>
#include <log4cplus/loggingmacros.h>

namespace fsm{
namespace model{

	Sleep::Sleep(xmlNodePtr xNode,const std::string &session,const std::string & filename)
		:Action(xNode, session, filename)
	{
		log = log4cplus::Logger::getInstance("fsm.model.Sleep");
		log.setAppendName("." + m_strSession);
		this->interval = helper::xml::getXmlNodeAttributesValue(m_node,"interval");
	}
	Sleep::~Sleep(){

	}

	unsigned int Sleep::getInterval()
	{
		return std::stoi(interval);
	}

	void Sleep::execute(fsm::Context * ctx)
	{
		LOG4CPLUS_DEBUG(log, ",sleep " << getInterval() << "ms");
		std::this_thread::sleep_for(std::chrono::milliseconds(getInterval()));
	}

}
}