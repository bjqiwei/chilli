#pragma once
#include "..\Extension\ExtensionImp.h"
#include <log4cplus\logger.h>


namespace chilli{
namespace ACD{

class ACDExtension :public Extension::ExtensionImp{
public:
	ACDExtension(model::ProcessModule * model, const std::string &ext, const std::string &smFileName);
	virtual ~ACDExtension();

};
typedef std::shared_ptr<ACDExtension>  ACDExtensionPtr;
}
}