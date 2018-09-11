#include "OnEntry.h"

namespace fsm{
namespace model{


	OnEntry::~OnEntry()
	{
		m_Actions.clear();
	}

	void OnEntry::addAction(std::shared_ptr<Action> actionptr)
	{
		m_Actions.push_back(actionptr);
	}
}
}