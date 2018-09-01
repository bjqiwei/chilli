#include "CallModule.h"
#include "Call.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/config.h>
#include <json/json.h>
#include "../uuid.h"
#include <apr_hash.h>


namespace chilli{
namespace Call{

CallModule::CallModule(const std::string & id, uint32_t threadSize) :ProcessModule(id, threadSize)
{
	log =log4cplus::Logger::getInstance("chilli.CallModule");
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " Constuction a Call module.");
}


CallModule::~CallModule(void)
{
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " Destruction a ACD module.");
}

int CallModule::Start()
{
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " Start...  CallModule");
	if (!m_bRunning) {
		ProcessModule::Start();
	}
	return 0;
}

int CallModule::Stop()
{
	LOG4CPLUS_DEBUG(log, "." + this->getId(), "Stop...  CallModule");
	if (m_bRunning)
	{
		ProcessModule::Stop();
	}
	return 0;
}


bool CallModule::LoadConfig(const std::string & configContext)
{
	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if(config.Parse(configContext.c_str()) != XMLError::XML_SUCCESS) 
	{ 
		LOG4CPLUS_ERROR(log, "." + this->getId(), " load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}
	
	tinyxml2::XMLElement * ecall = config.FirstChildElement();
	const char * sm = ecall->Attribute("StateMachine");
	m_SMFileName = sm ? sm : "";
	return true;
}

void CallModule::processSend(const fsm::FireDataType & fireData, const void * param, bool & bHandled)
{

	if (!fireData.dest.empty())
	{
		Json::Value newEvent;
		newEvent["from"] = fireData.from;
		newEvent["event"] = fireData.event;
		newEvent["type"] = fireData.type;
		newEvent["param"] = fireData.param;
		std::string callid;
		if (getCallBySession(fireData.dest, callid)) {
			newEvent["id"] = callid;
		}
		else {
			if (fireData.param.isMember("otherSessionID") && fireData.param["otherSessionID"].isString()) {
				std::string otherSessionId = fireData.param["otherSessionID"].asString();
				if (getCallBySession(otherSessionId, callid)) {
					newEvent["id"] = callid;
					setCallSession(fireData.dest, callid);
				}
				else {
					std::string newCallId = helper::uuid();
					newEvent["param"]["callID"] = newCallId;
					std::string newConnectionID = helper::uuid();
					newEvent["param"]["connectionID"] = newConnectionID;
					setCallSession(fireData.dest, newCallId);
					newEvent["id"] = newCallId;
				}
			}
		}

		this->PushEvent(model::EventType_t(new model::_EventType(newEvent)));
		bHandled = true;
	}
	else {
		LOG4CPLUS_WARN(log, "." + this->getId(), " fireSend, dest is null " << fireData.event);
	}

	
}


void CallModule::fireSend(const fsm::FireDataType & fireData, const void * param)
{
	LOG4CPLUS_TRACE(log, "." + this->getId(), " fireSend:" << fireData.event);
	bool bHandled = false;
	processSend(fireData, param, bHandled);
}

void CallModule::run()
{

	LOG4CPLUS_INFO(log, "." + this->getId(), " Starting...");
	try
	{
		while (m_bRunning)
		{
			try
			{
				model::EventType_t evt;
				if (m_RecEvtBuffer.Get(evt) && !evt->eventName.empty())
				{
					//LOG4CPLUS_DEBUG(log, evt.event.toStyledString());
					Json::Value & jsonEvent = evt->jsonEvent;
					LOG4CPLUS_DEBUG(log, "." + this->getId(), "event buffer size:" << m_RecEvtBuffer.size());

					const std::string & sessionid = evt->sessionid;
					
					std::string callid;
					if (!this->hasCallBySession(sessionid)) {
						this->setCallSession(sessionid, evt->id);
					}
					
					apr_ssize_t klen = evt->id.length();
					uint32_t hash = apr_hashfunc_default(evt->id.c_str(), &klen);
					hash %= m_executeThread.size();
					m_executeThread[hash].eventQueue.Put(evt);
				}
			}
			catch (std::exception & e)
			{
				LOG4CPLUS_ERROR(log, "." + this->getId(), " " << e.what());
			}
		}

	}
	catch (std::exception & e)
	{
		LOG4CPLUS_ERROR(log, "." + this->getId(), " " << e.what());
	}

	LOG4CPLUS_INFO(log, "." + this->getId(), " Stoped.");
	log4cplus::threadCleanup();
}

void CallModule::execute(helper::CEventBuffer<model::EventType_t> * eventQueue)
{
	LOG4CPLUS_INFO(log, "." + this->getId(),  " Process thread Starting...");
	try
	{
		while (m_bRunning)
		{
			try
			{
				model::EventType_t evt;
				if (eventQueue->Get(evt, 1000 * 5) && !evt->eventName.empty())
				{
					//LOG4CPLUS_DEBUG(log, evt.event.toStyledString());

					Json::Value  & jsonEvent = evt->jsonEvent;
					std::string & callId = evt->id;

					model::PerformElementPtr call;
					if ((call = this->getPerformElement(callId)) == nullptr){
						model::PerformElementPtr newCall(new Call(this, callId, m_SMFileName));
						std::string newConnectionID;
						if (jsonEvent["param"].isMember("connectionID"))
							newConnectionID = jsonEvent["param"]["connectionID"].asString();

						newCall->setVar("_callid", callId);
						newCall->setVar("_connectionid", newConnectionID);
						this->addPerformElement(callId, newCall);
						LOG4CPLUS_INFO(log, "." + this->getId(), "current call size:" << getPerformElementCount());
						call = newCall;
					}
				

					call->pushEvent(evt);
					call->mainEventLoop();

					if (call->IsClosed()) {
						this->removePerfromElement(call->getId());
						LOG4CPLUS_INFO(log, "." + this->getId(), "current call size:" << getPerformElementCount());
					}

					if (evt->eventName == "Null") {
						removeCallSession(evt->sessionid);
					}
				}
				else {
					fsm::threadIdle();
				}
			}
			catch (std::exception & e)
			{
				LOG4CPLUS_ERROR(log, "." + this->getId(), " " << e.what());
			}
		}

	}
	catch (std::exception & e)
	{
		LOG4CPLUS_ERROR(log, "." + this->getId(), " " << e.what());
	}

	LOG4CPLUS_INFO(log, "." + this->getId(), " Process thread Stoped.");
	fsm::threadCleanup();
	log4cplus::threadCleanup();
}

void CallModule::setCallSession(const TSessionID & sessionid, const TCallID & callid)
{
	if (sessionid.empty())
		return;

	std::unique_lock<std::mutex> lck(m_callMtx);
	m_SessionCalls[sessionid] = callid;
}

bool CallModule::getCallBySession(const TSessionID & sessionid, TCallID & callid)
{
	std::unique_lock<std::mutex> lck(m_callMtx);
	const auto & it = m_SessionCalls.find(sessionid);
	if (it != m_SessionCalls.end()){
		callid = it->second;
		return true;
	}
	return false;
}

bool CallModule::hasCallBySession(const TSessionID & sessionid)
{
	std::unique_lock<std::mutex> lck(m_callMtx);
	if (m_SessionCalls.find(sessionid) != m_SessionCalls.end()) {
		return true;
	}
	return false;
}

void CallModule::removeCallSession(const TSessionID & sessionid)
{
	std::unique_lock<std::mutex> lck(m_callMtx);
	m_SessionCalls.erase(sessionid);
}

}
}
