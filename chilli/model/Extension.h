#pragma once
#ifndef _CHILLI_CTI_EXTENSION_HEADER_
#define _CHILLI_CTI_EXTENSION_HEADER_
#include <string>
#include <memory>
#include <thread>
#include <atomic>
#include <FSM.h>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

namespace chilli{
namespace model{

class Extension: public fsm::SendInterface
{
public:
	Extension(const std::string &ext, const std::string &smFileName):SendInterface("this") 
	{
		m_SM = new fsm::StateMachine(ext,smFileName);
	};

	virtual ~Extension(){
		if (m_thread.joinable()){
			Stop();
		}
		delete m_SM;
	};

	virtual void Start() final {
		if (!m_thread.joinable()) {
			m_thread = std::thread(&Extension::run, this);
		}
	};

	virtual void Stop() final {

		if (m_thread.joinable()){
			m_SM->termination();
			m_thread.join();
		}
	};

	bool AddSendImplement(SendInterface * evtDsp){
		return m_SM->addSendImplement(evtDsp);
	}


	virtual const std::string & getExtensionNumber() const = 0;
	virtual int pushEvent(const std::string &evt) = 0;
	virtual void setSessionId(const std::string & sessinId) = 0;
	virtual const std::string & getSessionId() = 0;

//media interface
	virtual int Answer() = 0;
	virtual int PlayFile(const std::string &fileName) = 0;
	virtual int HangUp() = 0;

	//Only define a copy constructor and assignment function, these two functions can be disabled
	Extension(const Extension &) = delete;
	Extension & operator=(const Extension &) = delete;
private:
	void run()
	{
		try
		{
			m_SM->addSendImplement(this);
			m_SM->go();
			m_SM->mainEventLoop();
		}
		catch (std::exception & e)
		{
			LOG4CPLUS_ERROR(log, e.what());
		}
	};

	std::atomic_bool m_Running = false;
	std::thread m_thread;
protected:
	fsm::StateMachine * m_SM = nullptr;
	log4cplus::Logger log;

};
typedef std::shared_ptr<model::Extension> ExtensionPtr;
}
}
#endif // end extension header
