#pragma once
#ifndef _FSM_MODEL_DATAMODEL_HEADER_
#define _FSM_MODEL_DATAMODEL_HEADER_
#include "Action.h"

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
	
	public:
		Datamodel(xmlNodePtr xNode,const std::string &session,const std::string &filename);
		virtual void execute(fsm::Context * ctx);
	};
}
}
#endif //end datamodel head
