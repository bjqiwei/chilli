#include "FreeSwitchDevice.h"
#include "FreeSwitchModule.h"
#include <log4cplus/loggingmacros.h>
#include <scxml/TriggerEvent.h>

namespace chilli {
namespace FreeSwitch {

	FreeSwitchDevice::FreeSwitchDevice(FreeSwitchModule * model, const std::string &ext, const std::string &smFileName)
		:m_model(model), Device(model, ext, smFileName)
	{
		std::string logName = "FSDevice";
		log = log4cplus::Logger::getInstance(logName);
		LOG4CPLUS_DEBUG(log, "." + this->getId(), " new a device object.");
	}

	FreeSwitchDevice::~FreeSwitchDevice() {
		LOG4CPLUS_DEBUG(log, "." + this->getId(), " destruction a device object.");
	}

	void FreeSwitchDevice::fireSend(const fsm::FireDataType & fireData, const void * param)
	{
		LOG4CPLUS_TRACE(log, "." + this->getId(), " fireSend:" << fireData.event);

		bool bHandled = false;
		this->processSend(fireData, param, bHandled);
		
	}

	void FreeSwitchDevice::processSend(const fsm::FireDataType & fireData, const void * param, bool & bHandled)
	{
		if (fireData.event == "MakeConnection")
		{
			bHandled = m_model->MakeConnection(fireData.param, log);
		}
		else if (fireData.event == "MakeCall")
		{
			bHandled = m_model->MakeCall(fireData.param, log);
		}
		else if (fireData.event == "ClearConnection")
		{
			bHandled = m_model->ClearConnection(fireData.param, this->log);
		}
		else if (fireData.event == "StartRecord")
		{
			bHandled = m_model->StartRecord(fireData.param, this->log);
		}
		else if (fireData.event == "PlayFile")
		{
			bHandled = m_model->PlayFile(fireData.param, this->log);
		}
		else if (fireData.event == "PlayFileAndCollects")
		{
			bHandled = m_model->PlayFileAndCollects(fireData.param, this->log);
		}
		else if (fireData.event == "StopPlayFile")
		{
			bHandled = m_model->StopPlayFile(fireData.param, this->log);
		}
		else if (fireData.event == "StartRecord")
		{
			bHandled = m_model->StartRecord(fireData.param, this->log);
		}
		else if (fireData.event == "StopRecord")
		{
			bHandled = m_model->StopRecord(fireData.param, this->log);
		}
		else if (fireData.event =="StartDTMFCollection")
		{
			bHandled = m_model->StartDTMFCollection(fireData.param, this->log);
		}
		else if (fireData.event == "StopDTMFCollection")
		{
			bHandled = m_model->StopDTMFCollection(fireData.param, this->log);
		}
		else
			m_model->processSend(fireData, param, bHandled, log);

		if (!bHandled) {
			Device::processSend(fireData, param, bHandled);
		}
	}

}
}