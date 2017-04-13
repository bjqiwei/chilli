#pragma once

#ifndef _CHILLI_SHDEV_SHEXTENSION_HEADER_
#define _CHILLI_SHDEV_SHEXTENSION_HEADER_
#include "..\Extension\ExtensionImp.h"
#include <log4cplus\logger.h>
#include <memory>

namespace chilli{
namespace ShDev{


class ShExtension :public Extension::ExtensionImp
{
public:
	ShExtension(model::ProcessModule * model, const std::string &ext, const std::string &smFileName);
	virtual ~ShExtension(void);


	virtual int getChannelID();
	bool setType(const std::string & strType);
	void setType(int _type);

	//media interface
	virtual int Answer() override;
	virtual int PlayFile(const std::string & file) override;
	virtual int HangUp() override;

	//inherit from SendInterface
	virtual void fireSend(const std::string &strContent, const void * param) override;
private:
	int ch;
		
};
typedef std::shared_ptr<ShExtension> ShExtensionPtr;
}
}
#endif //end shextension header