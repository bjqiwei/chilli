#pragma once

#ifndef _CHILLI_CTI_DEVICE_MODULE_HEADER_
#define _CHILLI_CTI_DEVICE_MODULE_HEADER_

#include "..\model\ProcessModule.h"

namespace chilli{
namespace model{


class DevModule :
	public ProcessModule
{
public:
	DevModule(void);
	virtual ~DevModule(void);
	
private:

	//Only define a copy constructor and assignment function, these two functions can be disabled
	DevModule(const DevModule & other);
	DevModule & operator=(const DevModule &);


};
}
}
#endif //end dev module header