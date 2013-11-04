#pragma once
#ifndef _CHILLI_ACDPROCESS_HEADER_
#define _CHILLI_ACDPROCESS_HEADER_
namespace chilli{
namespace abstract{

class AcdProcess
{
public:
	AcdProcess(void) {};
	virtual ~AcdProcess(void){};
	virtual bool processTransfer(std::string strEvent,std::string from) = 0;
	virtual bool addAcdEvent(const std::string& strEvent) = 0;
};

}
}
#endif //end AcdProcess header