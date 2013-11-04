#pragma once
#ifndef _STATE_HEADER_
#define _STATE_HEADER_
#include <string>
#include <xmlHelper.h>
#include <log4cplus/logger.h>

namespace fsm
{
namespace model
{


	/// <summary>
	/// The class in this SCXML object model that corresponds to the
	/// &lt;state&gt; SCXML element.
	/// 
	/// </summary>

	class State
	{

	private:
		xmlNodePtr node;
		log4cplus::Logger log;
		std::string m_strId;
		std::string m_strName;
		//std::string m_strVersion;
		std::string m_strDescription;
		/// <summary>
		/// Constructor.
		/// </summary>
	public:
		State(xmlNodePtr xNode);
		virtual ~State(){};
		std::string &getId();
		std::string &getName();
		//std::string &getVersion();
		std::string &getDescription();

	private:
		void InitializeInstanceFields();
	};


}
}

#endif // end state
