#pragma once
#ifndef _CHILLI_SHDEV_MODULE_HEADER_
#define _CHILLI_SHDEV_MODULE_HEADER_
#include "..\Device\DevModule.h"
#include "shpa3api.h"
#include "scxml\SMInstance.h"
#include "..\model\Extension.h"

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
		IVR_Extension = 9,
	};

class ShDevModule :
	public chilli::abstract::DevModule
{
public:
	ShDevModule(void);
	virtual ~ShDevModule(void);

	virtual bool Init(xmlNodePtr xNode) ;
	virtual void Start() ;
	virtual int Close(void);


private:

	//Only define a copy constructor and assignment function, these two functions can be disabled
	ShDevModule(const ShDevModule & other);
	ShDevModule & operator=(const ShDevModule &);

public:
	//sanhuid event callback function
	static int CALLBACK EvtHandler(PSSM_EVENT pEvent);
	static int getDeviceTypeByName(std::string strType);
	static std::string TransferEvtToXmlEvent(PSSM_EVENT pEvent,std::string extNum);
	static char *GetString_EventType ( int nEvent );
	static char *GetString_State ( int state );
	static char *GetString_PengdingReason(int nReason);

};
typedef ShDevModule * ShDevModulePtr;
}
}
#endif // end shdev module header

