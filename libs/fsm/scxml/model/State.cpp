#include "State.h"
#include "../../common/xmlHelper.h"

namespace fsm
{
namespace model
{

	State::State(const std::string &filename, uint32_t lineno):m_strFilename(filename),m_lineNo(lineno)
	{

	}

	State::~State()
	{
		m_OnEntrys.clear();
		m_OnExits.clear();
		m_Events.clear();
	}

	void State::setId(const std::string & id)
	{
		this->m_strId = id;
	}

	void State::setName(const std::string & name)
	{
		this->m_strName = name;
	}

	void State::setDescription(const std::string & desc)
	{
		m_strDescription = desc;
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
	void State::setParent(State * parent)
	{
		m_Parent = parent;
	}
	State * State::getParent()const
	{
		return this->m_Parent;
	}
	void State::addOnEntry(std::shared_ptr<OnEntry> onentryptr)
	{
		m_OnEntrys.push_back(onentryptr);
	}
	void State::addOnExit(std::shared_ptr<OnExit> onexitptr)
	{
		this->m_OnExits.push_back(onexitptr);
	}
	void State::addEvent(std::shared_ptr<Event> eventptr)
	{
		m_Events.push_back(eventptr);
	}
}
}