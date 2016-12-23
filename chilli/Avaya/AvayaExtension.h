#pragma once
#ifndef _CHILLI_AVAYA_EXTENSION_HEADER_
#define _CHILLI_AVAYA_EXTENSION_HEADER_
#include "..\model\extension.h"
#include <log4cplus\logger.h>


namespace chilli{
namespace Avaya{

class AvayaExtension :public model::Extension{
public:
	AvayaExtension(const std::string &ext, const std::string &smFileName);
	virtual ~AvayaExtension();

	virtual const std::string & getExtensionNumber() const override;
	virtual void setSessionId(const std::string & sessinId) override;
	virtual const std::string & getSessionId() override;

	virtual int pushEvent(const std::string &evt) override;

	//inherit from SendInterface
	virtual void fireSend(const std::string &strContent, const void * param) override;

	//media interface
	virtual int Answer() override;
	virtual int PlayFile(const std::string &fileName) override;
	virtual int HangUp() override;

private:
	std::string m_ExtNumber;
	std::string m_SessionId;

};
typedef std::shared_ptr<AvayaExtension>  AvayaExtensionPtr;
}
}
#endif // end ivr extension header