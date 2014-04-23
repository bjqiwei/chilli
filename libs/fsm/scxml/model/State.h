#pragma once
#ifndef _STATE_HEADER_
#define _STATE_HEADER_
#include <string>
#include <libxml/tree.h>
#include <log4cplus/logger.h>

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
		xmlNodePtr node;
		log4cplus::Logger log;
		std::string m_strId;
		std::string m_strName;
		//std::string m_strVersion;
		std::string m_strDescription;
		std::string m_strSession;
		std::string m_strFilename;
		/// <summary>
		/// Constructor.
		/// </summary>
	public:
		State(xmlNodePtr xNode,const std::string &session,const std::string & filename);
		virtual ~State(){};
		const std::string &getId()const;
		const std::string &getName()const;
		//std::string &getVersion();
		const std::string &getDescription()const;

	private:
		void InitializeInstanceFields();
	};


}
}

#endif // end state
