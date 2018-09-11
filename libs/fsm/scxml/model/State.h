#pragma once
#include <string>
#include "OnEntry.h"
#include "OnExit.h"
#include "Event.h"

namespace fsm
{
namespace model
{


	/// <summary>
	/// The class in this fsm object model that corresponds to the
	/// &lt;state&gt; fsm element.
	/// 
	/// </summary>

	class State
	{

	private:
		std::string m_strId;
		std::string m_strName;
		//std::string m_strVersion;
		std::string m_strDescription;
		std::string m_strFilename;
		uint32_t m_lineNo;

	public:
		State* m_Parent = nullptr;
		std::vector<std::shared_ptr<OnEntry>> m_OnEntrys;
		std::vector<std::shared_ptr<OnExit>> m_OnExits;
		std::vector<std::shared_ptr<Event>>m_Events;

		State(const std::string &filename, uint32_t lineno);
		virtual ~State();
		void setId(const std::string & id);
		void setName(const std::string & name);
		void setDescription(const std::string & desc);
		const std::string &getId()const;
		const std::string &getName()const;
		//std::string &getVersion();
		const std::string &getDescription()const;

		void setParent(State * parent);
		State * getParent() const;

		void addOnEntry(std::shared_ptr<OnEntry> onentryptr);
		void addOnExit(std::shared_ptr<OnExit> onexitptr);
		void addEvent(std::shared_ptr<Event> eventptr);

	};


}
}
