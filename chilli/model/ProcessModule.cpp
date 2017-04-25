#include "ProcessModule.h"


namespace chilli{
namespace model{
	helper::CEventBuffer<EventType_t> ProcessModule::g_recEvtBuffer;
	model::ExtensionMap ProcessModule::g_Extensions;

	void ProcessModule::OnTimerExpiredFunc(unsigned long timerId, const std::string & attr, void * userdata)
	{
		Json::Value jsonAttr;
		Json::Reader jsonReader;
		if (jsonReader.parse(attr, jsonAttr)) {
			jsonAttr["extension"] = jsonAttr["sessionId"];
		}
		chilli::model::EventType_t evt(jsonAttr);
		ProcessModule::g_recEvtBuffer.Put(evt);
	}
}
}