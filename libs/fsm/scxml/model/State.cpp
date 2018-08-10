#include "State.h"
#include "../../common/xmlHelper.h"

namespace fsm
{
namespace model
{

	State::State(xmlNodePtr xNode,const std::string &session,const std::string & filename):node(xNode),
		m_strSession(session),m_strFilename(filename)
	{
		log = log4cplus::Logger::getInstance("fsm.model.State");
		log.setAppendName("." + m_strSession);
		InitializeInstanceFields();
		m_strId = helper::xml::getXmlNodeAttributesValue(node,"id");
		m_strName = helper::xml::getXmlNodeAttributesValue(node,"name");
		//m_strVersion = xmlHelper::getXmlNodeAttributesValue(node,"version");
		m_strDescription = helper::xml::getXmlNodeAttributesValue(node,"memo");
	}


	void State::InitializeInstanceFields()
	{
		
	}
	const std::string & State::getId()const
	{
		return m_strId;
	}
	const std::string & State::getName()const
	{
		return m_strName;
	}
	//std::string & State::getVersion()
	//{
	//	return m_strVersion;
	//}
	const std::string & State::getDescription()const
	{
		return m_strDescription;
	}
}
}