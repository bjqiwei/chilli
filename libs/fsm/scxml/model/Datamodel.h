#pragma once
#ifndef _FSM_MODEL_DATAMODEL_HEADER_
#define _FSM_MODEL_DATAMODEL_HEADER_
#include <libxml/tree.h>
#include "Action.h"
#include <log4cplus/logger.h>

namespace fsm
{
namespace model
{


	/// <summary>
	/// The class in this FSM object model that corresponds to the FSM
	/// &lt;datamodel&gt; element.
	/// 
	/// </summary>
	class Datamodel :public Action
	{

	private:

		/// <summary>
		/// The set of &lt;data&gt; elements, parsed as Elements, that are
		/// children of this &lt;datamodel&gt; element.
		/// </summary>
		xmlNodePtr node;
		std::string m_strSession;
		log4cplus::Logger log;
		std::string m_strFilename;
	public:
		Datamodel(xmlNodePtr xNode,const std::string &session,const std::string &filename);
		virtual void execute(fsm::Context * ctx);
	};
}
}
#endif //end datamodel head
