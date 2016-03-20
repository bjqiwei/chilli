#pragma once
#ifndef _CHILLI_CTI_EXTENSION_HEADER_
#define _CHILLI_CTI_EXTENSION_HEADER_
#include <string>

namespace chilli{
namespace model{

class Extension
{
public:
	Extension(){};
	virtual ~Extension(){};
	virtual bool setExtensionNumber(const std::string & number) = 0;
	virtual const std::string & getExtensionNumber() const = 0;
	virtual bool isIdle() = 0;
	virtual void go() = 0;
	virtual void pushEvent(const std::string &evt) = 0;

//media interface
	virtual int Answer() = 0;
	virtual int PlayFile(const std::string &fileName) = 0;
	virtual int HangUp() = 0;

	//Only define a copy constructor and assignment function, these two functions can be disabled
	Extension(const Extension &) = delete;
	Extension & operator=(const Extension &) = delete;
};
typedef Extension * ExtensionPtr;
}
}
#endif // end extension header
