#include <scxml/SendInterface.h>
#include <string>


class SendImp :public fsm::SendInterface
{
public:
	SendImp():SendInterface("testsend", nullptr){}
	~SendImp(){}
	virtual void fireSend(const fsm::FireDataType & strContent, const void * param) override;

};