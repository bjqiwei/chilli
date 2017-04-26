#include "Extension.h"
#include "ProcessModule.h"

namespace chilli {
namespace model {


	Extension::Extension(ProcessModule * model, const std::string &ext, const std::string &smFileName) :
		m_model(model), m_ExtNumber(ext), SendInterface("this")
	{
		m_SM = new fsm::StateMachine(ext, smFileName, ProcessModule::OnTimerExpiredFunc);
	}

	Extension::~Extension() {
		delete m_SM;
	}

	void Extension::Start() {
		m_SM->start(false);
	}

	void Extension::Stop() {
		m_SM->stop();
	}

	bool Extension::AddSendImplement(SendInterface * evtDsp) {
		return m_SM->addSendImplement(evtDsp);
	}

	bool Extension::setVar(const std::string &name, const Json::Value &value)
	{
		return m_SM->setVar(name, value);
	}

	const std::string & Extension::getExtNumber() {
		return m_ExtNumber;
	}

	void Extension::setSessionId(const std::string & sessinId) {
		m_SessionId = sessinId;
	}

	const std::string & Extension::getSessionId() {
		return m_SessionId;
	}

	log4cplus::Logger Extension::getLogger() {
		return log;
	}

}
}