#pragma once
#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include "ShAPI.h"

namespace chilli{
namespace ShDev{
	enum ChType
	{
		Analog_Trunk = 0,
		Anolog_User =  2,
		Anolog_Record = 3,
		Anolog_MicroPhone = 3,
		Anolog_Nothing = 20,
		ISDN_User = 7,
		ISND_Trunk = 8,
	};

using namespace SHAPI;
class ShDevModule :
	public chilli::model::ProcessModule
{
public:
	explicit ShDevModule(const std::string & id, uint32_t threadSize = 16);
	virtual ~ShDevModule(void);

	virtual int Start() override;
	virtual int Stop() override;
	virtual bool LoadConfig(const std::string & configContext) override;

private:
	//inherit from SendInterface
	virtual void fireSend(const fsm::FireDataType & fireData, const void * param) override;
private:

	bool Init();
	//sanhuid event callback function
	static int CALLBACK EvtHandler(const PSSM_EVENT pEvent);
	static int getDeviceTypeByName(const std::string & strType);
	static std::string TransferEvtToJsonEvent(const PSSM_EVENT pEvent, const std::string & extNum);
	static const char *GetString_EventType ( int nEvent );
	static const char *GetString_State ( int state );
	static const char *GetString_PengdingReason(int nReason);

};
typedef ShDevModule * ShDevModulePtr;
}
}

