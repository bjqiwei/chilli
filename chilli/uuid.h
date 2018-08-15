#pragma once
#include <string>
#include <apr_uuid.h>
#include "stringHelper.h"

namespace helper {
static std::string uuid()
{
	#define GUID_LEN 64 
	char buffer[GUID_LEN] = { 0 };
	apr_uuid_t uuid;
	apr_uuid_get(&uuid);

	apr_uuid_format(buffer, &uuid);
	//std::cout << "create guid " << buffer << std::endl;
	std::string str(buffer);
	return helper::string::toLower(str);
}
}
