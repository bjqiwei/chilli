#pragma once
#ifndef _CHILLI_VIRTUALDEVICE_GROUP_HEADER_
#define _CHILLI_VIRTUALDEVICE_GROUP_HEADER_

#include "Extension.h"
#include <log4cplus/logger.h>

namespace chilli
{
namespace model{

class Group:public Extension
{
public:
	Group();
	virtual ~Group();
private:
	std::vector<std::string> m_ExtVec;
	log4cplus::Logger log;
};
typedef Group * GroupPtr;

}
}
#endif // end header define

