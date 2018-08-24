#pragma once
#ifndef _FSM_CONTEXT_HEADER_
#define _FSM_CONTEXT_HEADER_
#include "Context.h"
#include "libxml/tree.h"
#include <list>


namespace fsm
{


	/// <summary>
	/// Interface for a component that may be used by the fsm engines to
	/// evaluate the expressions within the fsm document.
	/// 
	/// </summary>
	class  Evaluator
	{

	public:
		Evaluator(){};
		virtual ~Evaluator(){};
		virtual Context * newContext(const std::string &sessionid, Context * const parent) = 0;
		virtual void deleteContext(Context * const cx) = 0;
		virtual size_t getContextCount(){ return m_contexts.size();};
		virtual bool hasContext() = 0;
	protected:
		std::list<Context * > m_contexts;

	};

}

#endif // end context head