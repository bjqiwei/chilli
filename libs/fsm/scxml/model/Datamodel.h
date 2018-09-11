#pragma once
#include "Data.h"
#include <vector>

namespace fsm
{
namespace model
{


	/// <summary>
	/// The class in this FSM object model that corresponds to the FSM
	/// &lt;datamodel&gt; element.
	/// 
	/// </summary>
	class Datamodel
	{

	private:

		/// <summary>
		/// The set of &lt;data&gt; elements, parsed as Elements, that are
		/// children of this &lt;datamodel&gt; element.
		/// </summary>

	public:
		Datamodel(const std::string &filename, uint32_t lineno);
		virtual ~Datamodel();
		void addData(std::shared_ptr<Data> data);
		std::vector<std::shared_ptr<Data>> m_Datas;
	};
}
}
