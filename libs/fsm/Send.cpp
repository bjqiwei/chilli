#include <include/Send.h>

Interpreter::Send::Send(std::string target):_target(target)
{

}
const std::string & Interpreter::Send::getTarget() const
{
	return _target;
}

void Interpreter::Send::setTarget(const std::string target)
{
	this->_target = target;
}