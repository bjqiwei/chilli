#include "OnExit.h"


namespace fsm{
namespace model{

	void OnExit::addAction(std::shared_ptr<Action> actionptr)
	{
		m_Actions.push_back(actionptr);
	}

}
}