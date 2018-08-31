#include "PerformElement.h"
#include "ProcessModule.h"
#include <log4cplus/loggingmacros.h>

namespace chilli {
namespace model {


	PerformElement::PerformElement(ProcessModule * model, const std::string &id) :SendInterface("this", this),
		m_model(model), m_Id(id)
	{
	}

	PerformElement::~PerformElement() {
		
	}

	void PerformElement::PushEvent(const EventType_t & evt)
	{
		if (m_model)
			m_model->PushEvent(evt);
	}

	const std::string & PerformElement::getId() {
		return m_Id;
	}


	log4cplus::Logger PerformElement::getLogger() {
		return log;
	}

	bool PerformElement::setVar(const std::string & name, const Json::Value & value)
	{
		if (m_Vars.isMember(name))
			return false;

		m_Vars[name] = value;
		return true;
	}

	Json::Value PerformElement::getVar(const std::string & name)
	{
		return m_Vars[name];
	}

	void PerformElement::removeVar(const std::string & name)
	{
		m_Vars.removeMember(name);
	}

}
}