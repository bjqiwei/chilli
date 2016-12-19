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
	Group(const std::string &ext, const std::string &smFileName);
	virtual ~Group();
private:
	std::vector<std::string> m_ExtVec;
	log4cplus::Logger log;
};
typedef std::shared_ptr<Group> GroupPtr;

}
}
#endif // end header define

