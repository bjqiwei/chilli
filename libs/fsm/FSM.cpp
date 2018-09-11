#include "FSM.h"
#include "FSMimp.h"
#include "parseFSM.h"



using namespace std;

fsm::StateMachine * fsm::fsmParseFile(const std::string & filename)
{
	StateMachineimp * imp = parseFSM::fsmParseFileImp(filename);
	if (imp){
		fsm::StateMachine * sm = new fsm::StateMachine();
		sm->imp = imp;
		return sm;
	}
	return nullptr;
}

fsm::StateMachine * fsm::fsmParseMemory(const char * buffer, size_t size)
{
	StateMachineimp * imp = parseFSM::fsmParseMemoryImp(buffer, size);
	if (imp) {
		fsm::StateMachine * sm = new fsm::StateMachine();
		sm->imp = imp;
		return sm;
	}
	return nullptr;
}

fsm::StateMachine::StateMachine() :imp(nullptr)
{
}

fsm::StateMachine::~StateMachine()
{ 
	delete imp;
}

fsm::StateMachine::StateMachine(const StateMachine & other)
{
	this->imp = new StateMachineimp(*other.imp);
}

fsm::StateMachine & fsm::StateMachine::operator=(const StateMachine & other)
{
	// TODO: insert return statement here
	this->imp = new StateMachineimp(*other.imp);
	return *this;
}

const std::string fsm::StateMachine::getCurrentStateID(void) const
{
	return imp->getCurrentStateID();
}

void fsm::StateMachine::pushEvent(const TriggerEvent & trigEvent)
{
	return imp->pushEvent(trigEvent);
}

//void fsm::StateMachine::setName(const string &strName)
//{
//	return imp->setName(strName);
//}


bool fsm::StateMachine::addSendImplement(SendInterface * evtDsp)
{
	return imp->addSendImplement(evtDsp);
}
const std::string & fsm::StateMachine::getName() const {
	return imp->getName();
}
void fsm::StateMachine::setOnTimer(OnTimerInterface * func)
{
	return imp->setOnTimer(func);
}
void fsm::StateMachine::setLoggerId(const std::string & logId)
{
	return imp->setLoggerId(logId);
}
const std::string & fsm::StateMachine::getSessionId()const {
	return imp->getSessionID();
}

bool fsm::StateMachine::start(bool block)
{
	return imp->start(block);
}

void fsm::StateMachine::stop()
{
	return imp->stop();
}

void fsm::StateMachine::setSessionID(const std::string &strSessionid)
{
	return imp->setSessionID(strSessionid);
}

void fsm::StateMachine::mainEventLoop()
{
	return imp->mainEventLoop();
}

bool fsm::StateMachine::isInFinalState()
{
	return imp->isInFinalState();
}

bool fsm::StateMachine::setVar(const std::string &name, const Json::Value & value)
{  
	return imp->setVar(name, value);
}

void fsm::initialize()
{
	return StateMachineimp::initialize();
}

void fsm::threadCleanup()
{
	return StateMachineimp::threadCleanup();
}

FSM_EXPORT void fsm::threadIdle()
{
	return StateMachineimp::threadIdle();
}

void fsm::unInitialize()
{
	return StateMachineimp::unInitialize();
}
