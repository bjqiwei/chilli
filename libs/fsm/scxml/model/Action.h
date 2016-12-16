#pragma once
#ifndef _FSM_MODEL_ACTION_HEADER_
#define _FSM_MODEL_ACTION_HEADER_
#include "../Context.h"
#include <libxml/tree.h>
#include <log4cplus/logger.h>
#include "../../common/xmlHelper.h"

namespace fsm
{
namespace model
{
	/// <summary>
	/// An abstract base class for executable elements in FSM,
	/// such as log¡¢script etc.
	/// 
	/// </summary>
	class  Action 
	{

		/// <summary>
		/// Constructor.
		/// </summary>
	public:

		Action(xmlNodePtr xNode,const std::string & session,const std::string &filename):m_node(xNode),
			m_strSession(session),m_strFileName(filename),m_bCond(true)
		{
			m_strCond = helper::xml::getXmlNodeAttributesValue(m_node,"cond");
		}; //super();
		virtual~Action(){};
		virtual void execute(fsm::Context * ctx) = 0;
		virtual bool isEnabledCondition(fsm::Context * ctx)
		{
			if (!this->getCond().empty() && ctx){
				return ctx->evalCond(this->getCond(),m_strFileName,m_node->line);
			}
			return m_bCond;
		}
	protected:
		xmlNodePtr m_node;
		std::string m_strSession;
		std::string m_strFileName;
		std::string m_strCond;
		log4cplus::Logger log;
	private:
		bool m_bCond;

	protected:
		const std::string &getCond(){ return this->m_strCond;}

	};
}
}
#endif // end action header
