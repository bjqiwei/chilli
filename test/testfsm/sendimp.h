#include <scxml/SendInterface.h>
#include <string>


class SendImp :public fsm::SendInterface
{
public:
	SendImp():SendInterface("testsend"){}
	~SendImp(){}
	virtual void fireSend(const std::string& strContent, const void * param);

};