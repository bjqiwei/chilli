#include "FSM.h"
#include "FSMimp.h"
#include <string>
#include <ObjBase.h>
#include <cstdio>
#include "scxml/model/Script.h"
#include "scxml/model/Event.h"
#include "scxml/model/Script.h"
#include "scxml/model/Send.h"
#include "scxml/model/Timer.h"
#include "scxml/model/Transition.h"
#include "scxml/model/Scriptmodel.h"
#include "scxml/model/Datamodel.h"
#include "scxml/model/Log.h"
#include "scxml/model/Raise.h"
#include "scxml/model/Sleep.h"
#include <stdexcept>
#include <log4cplus/loggingmacros.h>
#include "common/stringHelper.h"


using namespace std;

fsm::StateMachine::StateMachine(const string  &xml, xmlType xtype) :imp(nullptr)
{
	imp = new fsm::StateMachineimp(xml, xtype);
}

fsm::StateMachine::~StateMachine()
 { 
	 delete imp;
 }


bool fsm::StateMachine::Init(void)
{
	return imp->Init();
}

bool fsm::StateMachine::Init(const string &xml, xmlType xtype)
{
	return imp->Init(xml, xtype);
}


const std::string fsm::StateMachine::getCurrentStateID(void) const
{
	return imp->getCurrentStateID();
}

void fsm::StateMachine::pushEvent( TriggerEvent & trigEvent)
{
	return imp->pushEvent(trigEvent);
}

void fsm::StateMachine::setName(const string &strName)
{
	return imp->setName(strName);
}


bool fsm::StateMachine::addSendImplement(SendInterface * evtDsp)
{
	return imp->addSendImplement(evtDsp);
}
const std::string & fsm::StateMachine::getName() const {
	return imp->getName();
}
const std::string & fsm::StateMachine::getSessionId()const {
	return imp->getSessionId();
}



void fsm::StateMachine::setscInstance(SMInstance * scIns)
{
	return imp->setscInstance(scIns);
}

void fsm::StateMachine::go()
{
	return imp->go();
}

void fsm::StateMachine::setSessionID(const std::string &strSessionid)
{
	return imp->setSessionID(strSessionid);
}

void fsm::StateMachine::mainEventLoop()
{
	return imp->mainEventLoop();
}



bool fsm::StateMachine::setVar(const std::string &name, const Json::Value & value)
{  
	return imp->setVar(name, value);
}

Json::Value fsm::StateMachine::getVar(const std::string &name)const
{
	return imp->getVar(name);
}
