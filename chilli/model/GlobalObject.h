#pragma once
#ifndef _CHILLI_GLOBAL_OBJECT_HEADER_
#define _CHILLI_GLOBAL_OBJECT_HEADER_
#include "Extension.h"
namespace chilli{

class Global
{
private:
	Global(void){};
	~Global(void){};
public:
	static std::map<std::string,chilli::abstract::ExtensionPtr> m_ExtMap;

};
}
#endif //end global object header
