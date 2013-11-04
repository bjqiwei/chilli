#include "stdafx.h"
#include "ShChannel.h"

namespace chilli
{
namespace ShDev{

ShChannel::ShChannel(void):Channel(){
	InitializeInstanceFields();
}
ShChannel::ShChannel(int _ch):Channel(_ch){
	InitializeInstanceFields();
}


ShChannel::~ShChannel(void)
{
}

int ShChannel::AutoSendDialTone(int nEnable)
{
	return SsmSetASDT(ch,nEnable);
}

int ShChannel::Answer()
{
	return SsmPickup(ch);
}
int ShChannel::PlayFile(std::string file)
{
	return SsmPlayFile(ch,file.c_str(),-1,0,0xFFFFFFFF);
}
int ShChannel::HangUp(){
	return SsmHangup(ch);
}

void ShChannel::InitializeInstanceFields()
{
	log = log4cplus::Logger::getInstance("chilli.ShDev.ShChannel");
}
}
}
