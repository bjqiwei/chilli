#include "Raise.h"

namespace fsm{
	namespace model{
		Raise::Raise(xmlNodePtr xNode,const std::string &session,const std::string & filename)
			:Action(xNode, session, filename)
		{
			log = log4cplus::Logger::getInstance("fsm.model.Raise");
			log.setAppendName("." + m_strSession);
			log.setAppendName("." + m_strSession);
			m_strEvent = helper::xml::getXmlNodeAttributesValue(m_node,"event");
		}


		Raise::~Raise(void)
		{
		}

		const std::string &Raise::getEvent()const
		{
			return m_strEvent;
		}

		void Raise::execute(fsm::Context * ctx)
		{
		}
	}
}
