#include "OnEntry.h"

namespace fsm{
namespace model{

	void OnEntry::addAction(std::shared_ptr<Action> actionptr)
	{
		m_Actions.push_back(actionptr);
	}
}
}