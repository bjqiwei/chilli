#include <FSM.h>
#include <scxml/EventDispatcher.h>
#include <string>

using namespace fsm::xmlHelper;

class SendImp :public fsm::EventDispatcher
{
public:
	SendImp():EventDispatcher("testsend"){}
	~SendImp(){}
	virtual void fireSend(const std::string& strContent);

};