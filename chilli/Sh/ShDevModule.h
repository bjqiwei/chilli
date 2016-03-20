#pragma once
#ifndef _CHILLI_SHDEV_MODULE_HEADER_
#define _CHILLI_SHDEV_MODULE_HEADER_
#include "..\Device\DevModule.h"
#include <log4cplus\logger.h>
#include "shpa3api.h"

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

class ShDevModule :
	public chilli::model::DevModule
{
public:
	ShDevModule(void);
	virtual ~ShDevModule(void);

	virtual int Start() ;
	virtual int Stop();
	virtual bool LoadConfig(const std::string & configFile);
	virtual std::vector<chilli::model::ExtensionPtr> GetExtension();

private:

	//Only define a copy constructor and assignment function, these two functions can be disabled
	ShDevModule(const ShDevModule & other);
	ShDevModule & operator=(const ShDevModule &);

private:

	bool Init();
	//sanhuid event callback function
	static int CALLBACK EvtHandler(const PSSM_EVENT const pEvent);
	static int getDeviceTypeByName(const std::string & strType);
	static std::string TransferEvtToXmlEvent(PSSM_EVENT pEvent, const std::string & extNum);
	static const char *GetString_EventType ( int nEvent );
	static const char *GetString_State ( int state );
	static const char *GetString_PengdingReason(int nReason);
private:
	log4cplus::Logger log;

};
typedef ShDevModule * ShDevModulePtr;
}
}
#endif // end shdev module header

