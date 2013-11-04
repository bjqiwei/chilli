#pragma once
#ifndef _CHILLI_SHDEV_SHCHANNEL_HEADER_
#define _CHILLI_SHDEV_SHCHANNEL_HEADER_
#include "..\model\Channel.h"
#include "shpa3api.h"


namespace chilli{
namespace ShDev{
class ShChannel :virtual public chilli::abstract::Channel
{
public:
	ShChannel(void);
	ShChannel(int _ch);
	virtual ~ShChannel(void);
	virtual int Answer();
	virtual int PlayFile(std::string file);
	virtual int HangUp();

public: // sanhuid interface
	virtual int AutoSendDialTone(int) ;
private:
	void InitializeInstanceFields();
};

}
}
#endif // end shchannel header

