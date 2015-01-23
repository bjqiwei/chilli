#pragma once
#ifndef _CTI_DEVICE_CHANNLE_HEADER_
#define _CTI_DEVICE_CHANNLE_HEADER_
#include <log4cplus/loggingmacros.h>
namespace chilli{
namespace abstract{
class Channel
{
public:
	Channel(void):ch(-1){};
	Channel(int _ch):ch(_ch){};
	virtual ~Channel(void){};
	virtual int Answer() = 0;
	virtual int PlayFile(const std::string &fileName) = 0;
	virtual int HangUp() = 0;
protected: 
	int ch;
	int	nType;

public:
	void setChannelID(int _ch){
		ch = _ch;
	}
	void setType(int _type){
			nType = _type;
		}
	int getChannelID(){return ch;}
	int getType(){return nType;}


private:
	//Only define a copy constructor and assignment function, these two functions can be disabled
	Channel(const Channel &);
	Channel & operator=(const Channel &);
};
}
}
#endif //end channle header
