#pragma once
#ifndef _FSM_MODEL_ACTION_HEADER_
#define _FSM_MODEL_ACTION_HEADER_
#include <string>
#include "config.h"
#include "scxml/Evaluator.h"
#include "scxml/Context.h"

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

		Action(){}; //super();
		virtual~Action(){};
		virtual void execute(fsm::Evaluator * evl,fsm::Context * ctx) = 0;

	};
}
}
#endif // end action header
