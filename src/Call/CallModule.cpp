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

CallModule::CallModule(const std::string & id, uint32_t threadSize) :ProcessModule(id), m_executeThread(threadSize)
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
		for (auto & it : m_executeThread) {
			it.th = std::thread(&CallModule::execute, this, &it.eventQueue);
		}
	}
	return 0;
}

int CallModule::Stop()
{
	LOG4CPLUS_DEBUG(log, "." + this->getId(), "Stop...  CallModule");
	if (m_bRunning)
	{
		ProcessModule::Stop();

		for (auto & it : m_executeThread) {
			if (it.th.joinable())
				it.th.join();
		}
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

void CallModule::processSend(Json::Value & jsonData, const void * param, bool & bHandled)
{

	if (jsonData["dest"].isString() && jsonData["dest"].asString() != "this")
	{
		this->PushEvent(chilli::model::EventType_t(jsonData));
		bHandled = true;
	}

	
}


void CallModule::fireSend(const std::string & strContent, const void * param)
{
	LOG4CPLUS_TRACE(log, "." + this->getId(), " fireSend:" << strContent);
	Json::Value jsonData;
	Json::CharReaderBuilder b;
	std::shared_ptr<Json::CharReader> jsonReader(b.newCharReader());
	std::string jsonerr;
	if (!jsonReader->parse(strContent.c_str(), strContent.c_str()+strContent.length(), &jsonData, &jsonerr)) {
		LOG4CPLUS_ERROR(log, "." + this->getId(), strContent << " not json data." << jsonerr);
		return;
	}

	bool bHandled = false;
	processSend(jsonData, param, bHandled);
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
				if (m_RecEvtBuffer.Get(evt) && !evt.event.isNull())
				{
					//LOG4CPLUS_DEBUG(log, evt.event.toStyledString());

					Json::Value  & jsonEvent = evt.event;

					std::string sessionid; 
					if (jsonEvent["param"].isMember("sessionID"))
						sessionid = jsonEvent["param"]["sessionID"].asString();

					std::string newCallId;
					if(jsonEvent["param"].isMember("callID"))
						newCallId = jsonEvent["param"]["callID"].asString();

					std::string newConnectionID;
					if(jsonEvent["param"].isMember("connectionID"))
						newConnectionID = jsonEvent["param"]["connectionID"].asString();

					if (sessionid.empty()){
						LOG4CPLUS_WARN(log, "." + this->getId(), "sessionID is null");
						continue;
					}

					if (findCallBySession(sessionid, newCallId) == false) {

						std::string otherSessionId;
						if (jsonEvent["param"].isMember("otherSessionID") && jsonEvent["param"]["otherSessionID"].isString())
							otherSessionId = jsonEvent["param"]["otherSessionID"].asString();

						std::string otherCallId;
						if (findCallBySession(otherSessionId, otherCallId)) {
							setCallSession(sessionid, otherCallId);
						}
						else {
							if (newCallId.empty()) {
								newCallId = helper::uuid();
								jsonEvent["param"]["callID"] = newCallId;
							}
							if (newConnectionID.empty()) {
								newConnectionID = helper::uuid();
								jsonEvent["param"]["connectionID"] = newConnectionID;
							}

							setCallSession(sessionid, newCallId);
						}
					}

					jsonEvent["id"] = newCallId;

					apr_ssize_t klen = newCallId.length();
					uint32_t hash = apr_hashfunc_default(newCallId.c_str(), &klen);
					hash %= m_executeThread.size();
					m_executeThread[hash].eventQueue.Put(chilli::model::EventType_t(jsonEvent));
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
				if (eventQueue->Get(evt, 1000) && !evt.event.isNull())
				{
					//LOG4CPLUS_DEBUG(log, evt.event.toStyledString());

					Json::Value  & jsonEvent = evt.event;
					if (jsonEvent["type"] == "request") {
						jsonEvent["event"] = jsonEvent["request"];
					}

					std::string sessionid;
					if (jsonEvent["param"].isMember("sessionID"))
						sessionid = jsonEvent["param"]["sessionID"].asString();

					std::string callId = jsonEvent["id"].asString();

					std::string newConnectionID;
					if (jsonEvent["param"].isMember("connectionID"))
						newConnectionID = jsonEvent["param"]["connectionID"].asString();


					if (this->getPerformElement(callId) == nullptr){
						model::PerformElementPtr newCall(new Call(this, callId, m_SMFileName));
						newCall->setVar("_callid", callId);
						newCall->setVar("_connectionid", newConnectionID);
						this->addPerformElement(callId, newCall);
						LOG4CPLUS_INFO(log, "." + this->getId(), "current call size:" << getPerformElementCount());
					}
				
					const auto & call = this->getPerformElement(callId);

					call->pushEvent(chilli::model::EventType_t(jsonEvent));
					call->mainEventLoop();

					if (call->IsClosed()) {
						this->removePerfromElement(call->getId());
						LOG4CPLUS_INFO(log, "." + this->getId(), "current call size:" << getPerformElementCount());
					}

					if (jsonEvent["event"].isString() && jsonEvent["event"].asString() == "Null")
						removeCallSession(sessionid);
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
	log4cplus::threadCleanup();
}

void CallModule::setCallSession(const TSessionID & sessionid, const TCallID & callid)
{
	std::unique_lock<std::mutex> lck(m_callMtx);
	m_Calls[sessionid] = callid;
}

bool CallModule::findCallBySession(const TSessionID & sessionid, TCallID & callid)
{
	std::unique_lock<std::mutex> lck(m_callMtx);
	const auto & it = m_Calls.find(sessionid);
	if (it != m_Calls.end()){
		callid = it->second;
		return true;
	}
	return false;
}

void CallModule::removeCallSession(const TSessionID & sessionid)
{
	std::unique_lock<std::mutex> lck(m_callMtx);
	m_Calls.erase(sessionid);
}

}
}
