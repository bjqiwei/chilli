#pragma once
#ifndef _CHILLI_ABSTRACT_BASEOBJECT_HEADER_
#define _CHILLI_ABSTRACT_BASEOBJECT_HEADER_
#include <log4cplus/logger.h>
namespace chilli{
namespace abstract{

class BaseObject
{
public:
	BaseObject(void);
	virtual ~BaseObject(void);
protected:
	log4cplus::Logger log;
};

}
}
#endif
