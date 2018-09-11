#include "FSMimp.h"
#include "common/xmlHelper.h"
#include "scxml/env/JSEvaluator.h"
#include <log4cplus/loggingmacros.h>
#include "common/stringHelper.h"
#include "common/Timer.h"
#include "common/tls.h"


using namespace std;

namespace fsm {
	//static std::atomic_ulong g_StateMachineReferce = 0;
	//static Evaluator * g_Evaluator = nullptr;
	static tls_key_type g_tls_storage_key = 0;
	typedef struct {
		std::shared_ptr<Evaluator> evaluator = nullptr;
		std::shared_ptr<helper::TimerServer>  timerServer = nullptr;
	}per_thread_data;
	
}

fsm::StateMachineimp::StateMachineimp(): m_Running(false), m_Block(false)
{
	LOG4CPLUS_DEBUG(log4cplus::Logger::getInstance("scxml"), "", ",creat a scxml object." << this);
}

fsm::StateMachineimp::~StateMachineimp()
 { 
	m_States.clear();
	m_ScriptModel.clear();
	m_Datamodel.clear();
	LOG4CPLUS_DEBUG(log4cplus::Logger::getInstance("scxml"), "." + m_strSessionID, ",destruction a scxml object." << this);
 }

fsm::StateMachineimp::StateMachineimp(const StateMachineimp & other)
{
	this->m_initState = other.m_initState;
	this->m_finalState = other.m_finalState;
	this->m_Datamodel = other.m_Datamodel;
	this->m_strName = other.m_strName;
	this->m_ScriptModel = other.m_ScriptModel;
	this->m_Datamodel = other.m_Datamodel;
	this->m_States = other.m_States;
	this->m_strStateFile = other.m_strStateFile;
	LOG4CPLUS_DEBUG(log4cplus::Logger::getInstance("scxml"), "", ",creat a scxml object." << this);
}

fsm::StateMachineimp & fsm::StateMachineimp::operator=(const StateMachineimp & other)
{
	// TODO: insert return statement here
	this->m_initState = other.m_initState;
	this->m_finalState = other.m_finalState;
	this->m_Datamodel = other.m_Datamodel;
	this->m_strName = other.m_strName;
	this->m_ScriptModel = other.m_ScriptModel;
	this->m_Datamodel = other.m_Datamodel;
	this->m_States = other.m_States;
	this->m_strStateFile = other.m_strStateFile;
	LOG4CPLUS_DEBUG(log4cplus::Logger::getInstance("scxml"), "", ",creat a scxml object." << this);
	return *this;
}


//const model::State* fsm::StateMachine::getCurrentState(void) const
//{
//	return m_currentState;
//}

const std::string fsm::StateMachineimp::getCurrentStateID(void) const
{
	if (m_currentState)
		return m_currentState->getId();
	return std::string();
}

void fsm::StateMachineimp::pushEvent(const TriggerEvent & trigEvent)
{
	m_externalQueue.Put(trigEvent);
}

bool fsm::StateMachineimp::processEvent(const fsm::model::Event * event)const
{
	if (!event){
		return false ;
	}
	bool doneSomething = false;
	for (const auto & action : event->m_Actions)
	{
		model::Log * log = dynamic_cast<model::Log*>(action.get());
		if (log) {
			processLog(log) ? doneSomething = true : false;
			continue;
		}
		model::Raise * raise = dynamic_cast<model::Raise*>(action.get());
		if (raise) {
			processRaise(raise) ? doneSomething = true : false;
			continue;
		}
		model::Script * script = dynamic_cast<model::Script*>(action.get());
		if (script) {
			processScript(script) ? doneSomething = true : false;
			continue;
		}
		model::Send * send = dynamic_cast<model::Send*>(action.get());
		if (send) {
			processSend(send) ? doneSomething = true : false;
			continue;
		}
		model::Sleep * sleep = dynamic_cast<model::Sleep*>(action.get());
		if (sleep) {
			processSleep(sleep) ? doneSomething = true : false;
			continue;
		}
		model::Timer * timer = dynamic_cast<model::Timer*>(action.get());
		if (timer) {
			processTimer(timer) ? doneSomething = true : false;
			continue;
		}
		model::Transition * transition = dynamic_cast<model::Transition*>(action.get());
		if (transition) {
			if (processTransition(transition)) {
				doneSomething = true;
				break;//transition 元素下的元素将不再执行
			}
			continue;
		}

	}
	
	if (!doneSomething)
	{
		LOG4CPLUS_WARN(this->log, "." + m_strSessionID, getCurrentStateID() << " state occur event " << event->getEvent() << " done nothing,line:" << event->getLineNo());
	}
	return doneSomething;
}

bool fsm::StateMachineimp::processTransition(const model::Transition * transition)const
{
	try{

	if (!transition) return false;

	if (!transition->isEnabledCondition(this->getRootContext()))
		return false ;

	model::State * state = getState(transition->getTarget());
	if (state)
	{
		exitStates();
		enterStates(state);
	}
	else
	{
		LOG4CPLUS_ERROR(log, "." + m_strSessionID, m_strStateFile<<" file,not find the target:" << transition->getTarget() << " state, line:" << transition->getLineNo());
	}

	}
	catch (fsm::jsexception & e)
	{
		LOG4CPLUS_ERROR(log, "." + m_strSessionID, e.what() << "(" << e.m_file << ":" << e.m_line << ":" << e.m_column << ")");
	}
	catch (std::exception &e)
	{
		LOG4CPLUS_ERROR(log, "." + m_strSessionID, e.what());
	}
	return true;
}

bool fsm::StateMachineimp::processSend(const fsm::model::Send * send)const
{
	try
	{
	if (!send) return false;
	if (send->isEnabledCondition(this->getRootContext())){
		send->execute(this->getRootContext(), this->log, this->m_strSessionID);
	}
	else{
		return false;
	}

	std::map<std::string , SendInterface *>::const_iterator it = m_mapSendObject.find(send->getTarget());
	if (it != m_mapSendObject.end()) {
		it->second->fireSend(send->getFireData(), it->second->getUserData());
	}
	else {

		LOG4CPLUS_ERROR(log, "." + m_strSessionID, " not find the send target:" << send->getTarget());
	}
	}
	catch (fsm::jsexception & e)
	{
		LOG4CPLUS_ERROR(log, "." + m_strSessionID, e.what() << "(" << e.m_file << ":" << e.m_line << ":" << e.m_column << ")");
	}
	catch (std::exception &e)
	{
		LOG4CPLUS_ERROR(log, "." + m_strSessionID, e.what());
	}
	return true;
}


bool fsm::StateMachineimp::processTimer(const fsm::model::Timer * timer)const
{
	try {

	if (!timer) return false;

	if (timer->isEnabledCondition(this->getRootContext()))
	{
		timer->execute(this->getRootContext(), this->log, this->m_strSessionID);
	}
	else {
		return false;
	}


	//LOG4CPLUS_DEBUG(logger,_strName << ":" << _strSessionID << "execute a script:" << script.getContent());
	LOG4CPLUS_DEBUG(log, "." + m_strSessionID, ",set a timer,id=" << timer->getId() << ", interval=" << timer->getInterval());
	Json::Value vars;
	vars["sessionId"] = this->m_strSessionID;
	vars["timerId"] = timer->getId();
	vars["interval"] = timer->getInterval();

	if (this->getTimerServer())
		this->getTimerServer()->SetTimer(timer->getInterval(), vars.toStyledString(), m_TimeOutFunc, const_cast<StateMachineimp *>(this));
	
	}
	catch (fsm::jsexception & e)
	{
		LOG4CPLUS_ERROR(log, "." + m_strSessionID, e.what() << "(" << e.m_file << ":" << e.m_line << ":" << e.m_column << ")");
	}
	catch (std::exception &e)
	{
		LOG4CPLUS_ERROR(log, "." + m_strSessionID, e.what());
	}
	return true;
}

bool fsm::StateMachineimp::processLog(const model::Log *log)const
{
	try{

	if (!log) return false;
	
	if(log->isEnabledCondition(this->getRootContext())){
		log->execute(this->getRootContext(), this->log, m_strSessionID);
	}else{
		return false;
	}

	}
	catch (fsm::jsexception & e)
	{
		LOG4CPLUS_ERROR(this->log, "." + m_strSessionID, e.what() << "(" << e.m_file << ":" << e.m_line << ":" << e.m_column << ")");
	}
	catch (std::exception &e)
	{
		LOG4CPLUS_ERROR(this->log, "." + m_strSessionID, e.what());
	}
	return true;
}

bool fsm::StateMachineimp::processScript(const model::Script * script) const
{
	try{

	if (!script) return false;

	if(script->isEnabledCondition(this->getRootContext())){
		script->execute(this->getRootContext(), this->log, this->m_strSessionID);
		return true;
	}

	}
	catch (fsm::jsexception & e)
	{
		LOG4CPLUS_ERROR(log, "." + m_strSessionID, e.what() << "(" << e.m_file << ":" << e.m_line << ":" << e.m_column << ")");
	}
	catch (std::exception &e)
	{
		LOG4CPLUS_ERROR(log, "." + m_strSessionID, e.what());
	}
	return false;
}

bool fsm::StateMachineimp::processRaise(const model::Raise * raise)const
{
	try{

	if (!raise) return false;

	if(raise->isEnabledCondition(this->getRootContext())){
		TriggerEvent _raiseEvent;
		_raiseEvent.setEventName(raise->getEvent());
		_raiseEvent.setParam(this);
		LOG4CPLUS_TRACE(log, "." + m_strSessionID, ", Raise a event:" << _raiseEvent.ToString());
		const_cast<StateMachineimp*>(this)->m_internalQueue.push(_raiseEvent);
		return true;
	}

	}
	catch (fsm::jsexception & e)
	{
		LOG4CPLUS_ERROR(log, "." + m_strSessionID, e.what() << "(" << e.m_file << ":" << e.m_line << ":" << e.m_column << ")");
	}
	catch (std::exception &e)
	{
		LOG4CPLUS_ERROR(log, "." + m_strSessionID, e.what());
	}

	return false;
}

bool fsm::StateMachineimp::processSleep(const model::Sleep * sleep)const
{
	try{

	if (!sleep) return false;

	if(sleep->isEnabledCondition(this->getRootContext())){
		sleep->execute(this->getRootContext(), this->log, this->m_strSessionID);
		return true;
	}

	}
	catch (fsm::jsexception & e)
	{
		LOG4CPLUS_ERROR(log, "." + m_strSessionID, e.what() << "(" << e.m_file << ":" << e.m_line << ":" << e.m_column << ")");
	}
	catch (std::exception &e)
	{
		LOG4CPLUS_ERROR(log, "." + m_strSessionID, e.what());
	}
	return false;
}

const fsm::model::State * fsm::StateMachineimp::getParentState(const fsm::model::State * currentState)const
{
	if (currentState != nullptr){
		return currentState->m_Parent;
	}

	return nullptr;
}

helper::TimerServer * fsm::StateMachineimp::getTimerServer() const
{
	if (m_TimerServer == nullptr) {

		per_thread_data * pdata = reinterpret_cast<per_thread_data *>(tls_get_value(g_tls_storage_key));

		if (pdata == nullptr) {
			pdata = new per_thread_data();
			tls_set_value(g_tls_storage_key, pdata);
		}

		if (pdata->timerServer == nullptr) {
			pdata->timerServer.reset(new helper::TimerServer());
			pdata->timerServer->Start();
		}

		const_cast<StateMachineimp*>(this)->m_TimerServer = pdata->timerServer.get();
	}

	return m_TimerServer;
}

//void fsm::StateMachineimp::setName(const string &strName)
//{
//	m_strName = strName;
//	LOG4CPLUS_DEBUG(log,"set this stateMachine name=" << m_strName);
//}


void fsm::StateMachineimp::exitStates() const
{
	if (m_currentState)
	{
		for (const auto & onexit : m_currentState->m_OnExits)
		{
			processExit(onexit.get());
		}
	}
}

void fsm::StateMachineimp::enterStates(const model::State * state) const
{
	if (state == nullptr){
		LOG4CPLUS_ERROR(log, "." + m_strSessionID, " state is null");
		return;
	}
	const_cast<StateMachineimp*>(this)->m_currentState = state;
	LOG4CPLUS_DEBUG(log, "." + m_strSessionID, ", enter state:" << getCurrentStateID());
	getRootContext()->setVar("_state._id", getCurrentStateID());
	for (auto & entry : state->m_OnEntrys)
	{
		processEntry(entry.get());
	}

}



bool fsm::StateMachineimp::processExit(const fsm::model::OnExit * onexit) const
{
	if (!onexit) return false;

	for (auto & action : onexit->m_Actions)
	{
		model::Log * log = dynamic_cast<model::Log*>(action.get());
		if (log) {
			processLog(log);
			continue;
		}
		model::Raise * raise = dynamic_cast<model::Raise*>(action.get());
		if (raise) {
			processRaise(raise);
			continue;
		}
		model::Script * script = dynamic_cast<model::Script*>(action.get());
		if (script) {
			processScript(script);
			continue;
		}
		model::Send * send = dynamic_cast<model::Send*>(action.get());
		if (send) {
			processSend(send);
			continue;
		}
		model::Sleep * sleep = dynamic_cast<model::Sleep*>(action.get());
		if (sleep) {
			processSleep(sleep);
			continue;
		}
		model::Timer * timer = dynamic_cast<model::Timer*>(action.get());
		if (timer) {
			processTimer(timer);
			continue;
		}

	}
	return true ;
}

bool fsm::StateMachineimp::processEntry(const model::OnEntry * onentry)const
{
	for (auto & action : onentry->m_Actions)
	{
		model::Log * log = dynamic_cast<model::Log*>(action.get());
		if (log) {
			processLog(log);
			continue;
		}
		model::Raise * raise = dynamic_cast<model::Raise*>(action.get());
		if (raise) {
			processRaise(raise);
			continue;
		}
		model::Script * script = dynamic_cast<model::Script*>(action.get());
		if (script) {
			processScript(script);
			continue;
		}
		model::Send * send = dynamic_cast<model::Send*>(action.get());
		if (send) {
			processSend(send);
			continue;
		}
		model::Sleep * sleep = dynamic_cast<model::Sleep*>(action.get());
		if (sleep) {
			processSleep(sleep);
			continue;
		}
		model::Timer * timer = dynamic_cast<model::Timer*>(action.get());
		if (timer) {
			processTimer(timer);
			continue;
		}
		model::Transition * transition = dynamic_cast<model::Transition*>(action.get());
		if (transition) {
			processTransition(transition);
			continue;
		}
	}

	return true;
}

fsm::model::State * fsm::StateMachineimp::getState(const std::string& stateId) const
{
	const auto & state = m_States.find(stateId);
	if (state != m_States.end()){
		return state->second.get();
	}
	LOG4CPLUS_WARN(log, "." + m_strSessionID, "not find state:" << stateId);
	return nullptr;
	/* Cleanup */
}
bool fsm::StateMachineimp::addSendImplement(SendInterface * evtDsp)
{
	if (m_mapSendObject.count(evtDsp->getTarget())) 
		return false;
	m_mapSendObject[evtDsp->getTarget()] = evtDsp;
	LOG4CPLUS_TRACE(log, "." + m_strSessionID, "addSendImplement:" << evtDsp->getTarget());
	return true;
}

const std::string & fsm::StateMachineimp::getName() const {
	return m_strName;
}

void fsm::StateMachineimp::setOnTimer(helper::OnTimerInterface * func)
{
	this->m_TimeOutFunc = func;
}

void fsm::StateMachineimp::setLoggerId(const std::string & logId)
{
	this->log = log4cplus::Logger::getInstance(logId);
}

const std::string & fsm::StateMachineimp::getSessionID()const {
	return m_strSessionID;
}

fsm::Context  *  fsm::StateMachineimp::getRootContext() const{
	if (m_Context == nullptr) {
		per_thread_data * pdata = reinterpret_cast<per_thread_data *>(tls_get_value(g_tls_storage_key));

		if (pdata == nullptr) {
			pdata = new per_thread_data();
			tls_set_value(g_tls_storage_key, pdata);
		}

		if (pdata->evaluator == nullptr) {
			pdata->evaluator.reset(new fsm::env::JSEvaluator());
		}

		const_cast<StateMachineimp*>(this)->m_Context = pdata->evaluator->newContext(m_strSessionID, nullptr);
	}
	
	return m_Context;
}

void fsm::StateMachineimp::releaseContext(Context * ctx)
{
	per_thread_data * pdata = reinterpret_cast<per_thread_data *>(tls_get_value(g_tls_storage_key));

	if (pdata != nullptr && pdata->evaluator != nullptr) {

		pdata->evaluator->releaseContext(m_Context);
		m_Context = nullptr;
	}
}

void fsm::StateMachineimp::setLog(log4cplus::Logger log)
{
	this->log = log;
}

bool fsm::StateMachineimp::start(bool block)
{
	m_Block = block;

	fsm::Context *ctx = getRootContext();

	if (ctx)
	{
		/*创建JsContext私有数据指针*/
		//ctx->SetContextPrivate(this);
		for (auto & it : m_globalVars) {
			ctx->setVar(it.first, it.second);
		}
		m_globalVars.clear();

		ctx->setVar("_name", getName());
		ctx->setVar("_sessionid", getSessionID());

	}

	for (const auto & dm:m_Datamodel)
	{
		for (const auto & data: dm->m_Datas)
		{
			data->execute(ctx, this->log, this->m_strSessionID);
		}
	}

	for (auto & sm:m_ScriptModel)
	{
		for (const auto & script:sm->m_Scripts)
		{
			script->execute(ctx, this->log, this->m_strSessionID);
		}
	}

	
	m_Running = true;
	LOG4CPLUS_DEBUG(log, "." + m_strSessionID, ", start");
	enterStates(getState(this->m_initState));
	return true;

}

void fsm::StateMachineimp::stop()
{
	LOG4CPLUS_DEBUG(log, "." + m_strSessionID, ", stop");
	m_Running = false;
	if (m_Block){
		TriggerEvent trigEvent;
		pushEvent(trigEvent);
	}

	if (!m_Block) {
		this->releaseContext(m_Context);
	}
}
void fsm::StateMachineimp::setSessionID(const std::string &strSessionid)
{
	m_strSessionID = strSessionid;
	LOG4CPLUS_DEBUG(log, "." + m_strSessionID, ", set this stateMachine sessionid=" << m_strSessionID);
}

void fsm::StateMachineimp::mainEventLoop()
{

	//外部事件队列循环

	do {
		try {
			//如果外部事件队列不为空，执行一个外部事件
			TriggerEvent trigEvent;
			if (m_externalQueue.Get(trigEvent, 1000)) {

				for(auto & it :m_globalVars){
					this->getRootContext()->setVar(it.first, it.second); 
				}
				m_globalVars.clear();
				processEvent(trigEvent);

			}

			//内部事件队列循环
			if (m_Running && !m_internalQueue.empty())
			{
				LOG4CPLUS_TRACE(log, "." + m_strSessionID, ", Internal Event Queue size:" << m_internalQueue.size());
				std::queue<TriggerEvent> excQueue;
				// 拷贝现在内部事件队列中的事件到执行队列中
				excQueue.swap(m_internalQueue);

				//执行当前执行队列
				while (m_Running && !excQueue.empty()) {
					TriggerEvent inEvent = excQueue.front();
					excQueue.pop();
					processEvent(inEvent);
				}
			}
		}
		catch (std::exception & e)
		{
			LOG4CPLUS_ERROR(log, "." + m_strSessionID, e.what());
		}

	} while (m_Running && m_Block);

	if (m_Block){
		this->releaseContext(m_Context);
	}
}

bool fsm::StateMachineimp::isInFinalState()
{
	return getCurrentStateID() == m_finalState;
}

void fsm::StateMachineimp::initialize()
{
	g_tls_storage_key = tls_init(nullptr);
	xmlInitParser();
}

void fsm::StateMachineimp::threadCleanup()
{
	per_thread_data * pdata = reinterpret_cast<per_thread_data *>(tls_get_value(g_tls_storage_key));
	if (pdata != nullptr)
	{
		if (pdata->evaluator){
			if (pdata->evaluator->hasContext())
				LOG4CPLUS_ERROR(log4cplus::Logger::getRoot(), "", "has context when evaluator delete.");
		}
		if (pdata->timerServer){
			pdata->timerServer->Stop();
		}

		delete pdata;
		tls_set_value(g_tls_storage_key, nullptr);
	}
}

void fsm::StateMachineimp::threadIdle()
{
	per_thread_data * pdata = reinterpret_cast<per_thread_data *>(tls_get_value(g_tls_storage_key));
	if (pdata != nullptr)
	{
		if (pdata->evaluator) {
			pdata->evaluator->deleteContext(1);

			if (!pdata->evaluator->hasContext())
			{
				pdata->evaluator = nullptr;
			}
		}
	}
}

void fsm::StateMachineimp::unInitialize()
{
	tls_cleanup(g_tls_storage_key);
	g_tls_storage_key = 0;
	xmlCleanupParser();
}

bool fsm::StateMachineimp::processEvent(const TriggerEvent &event)
{
	using namespace helper::xml;
	LOG4CPLUS_TRACE(log, "." + m_strSessionID, ",processEvent:" << event.getEventName());
	if (getRootContext()){
		getRootContext()->deleteVar("_event");
		m_currentEvt = event;

		getRootContext()->setVar("_event._name", m_currentEvt.getEventName());
		getRootContext()->setVar("_event._type", m_currentEvt.getMsgType());
		for(auto & it : m_currentEvt.getVars())
		{
			getRootContext()->setVar("_event." + it.first, it.second);
		}
	}else
	{
		m_currentEvt = event;
	}
	bool foundEvent = false;
	 const fsm::model::State * filterState = m_currentState;
	//std::string strEventData = trigEvent.getData();
	//scInstance->getRootContext()->set("_event.data",strEventData);
	while (filterState != NULL && filterState != nullptr && foundEvent == false) 
	{
		LOG4CPLUS_TRACE(log, "." + m_strSessionID, ",matching event stateid=" << filterState.getId());
		for (const auto & event : filterState->m_Events)
		{
			if (event->isEnabledEvent(m_currentEvt.getEventName(), this->log, this->m_strSessionID)
				&& event->isEnabledCondition(this->getRootContext()))
			{
				foundEvent = true;
				processEvent(event.get());
				break;
			}

		}
		if (!foundEvent)
		{
			filterState = getParentState(filterState);
		}
	} 

	if (!foundEvent)
	{
		LOG4CPLUS_WARN(log, "." + m_strSessionID, ",stateid=" << getCurrentStateID() << " not match the event:"  << m_currentEvt.ToString());
	}
	return foundEvent;
}

bool fsm::StateMachineimp::setVar(const std::string &name, const Json::Value & value)
{  
	this->m_globalVars.push_back(std::make_pair(name,value));
	return true;
}

