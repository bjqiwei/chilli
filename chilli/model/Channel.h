#ifndef _CTI_DEVICE_CHANNLE_HEADER_
#define _CTI_DEVICE_CHANNLE_HEADER_
#include <string>

namespace chilli{
namespace model{
class Channel
{
public:
	Channel(int _ch){};
	virtual ~Channel(void){};
	virtual int Answer() = 0;
	virtual int PlayFile(const std::string &fileName) = 0;
	virtual int HangUp() = 0;
	virtual void setChannelID(int _ch) = 0;
	virtual int getChannelID() = 0;
	virtual void setType(int _type) = 0;
	virtual int getType() = 0;

private:
	//Only define a copy constructor and assignment function, these two functions can be disabled
	Channel(const Channel &);
	Channel & operator=(const Channel &);
};
}
}
#endif //end channle header
