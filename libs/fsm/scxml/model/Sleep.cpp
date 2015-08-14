#include "Sleep.h"
#include "../../common/xmlHelper.h"
#include <Windows.h>

namespace fsm{
namespace model{

	Sleep::Sleep(xmlNodePtr xNode,const std::string &session,const std::string & filename)
		:Action(xNode, session, filename)
	{
		log = log4cplus::Logger::getInstance("fsm.model.Sleep");
		this->interval = helper::xml::getXmlNodeAttributesValue(node,"interval");
	}
	Sleep::~Sleep(){

	}

	unsigned int Sleep::getInterval()
	{
		return std::stoi(interval);
	}

	void Sleep::execute(fsm::Context * ctx)
	{
		::Sleep(getInterval());
	}

}
}