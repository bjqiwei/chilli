#include "OnExit.h"


namespace fsm{
namespace model{


	OnExit::~OnExit()
	{
		m_Actions.clear();
	}

	void OnExit::addAction(std::shared_ptr<Action> actionptr)
	{
		m_Actions.push_back(actionptr);
	}

}
}