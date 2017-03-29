#include "ProcessModule.h"


namespace chilli{
namespace model{
	helper::CEventBuffer<EventType_t> ProcessModule::g_recEvtBuffer;
	model::ExtensionMap ProcessModule::g_Extensions;
}
}