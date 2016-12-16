#include "SimpleContext.h"
#include <log4cplus/loggingmacros.h>


namespace fsm
{
namespace env
{


	SimpleContext::SimpleContext(Context * const parent):Context(nullptr,parent)
	{
		InitializeInstanceFields();
		LOG4CPLUS_TRACE(log,"construct a SimpleContext object.");
	}

	SimpleContext::~SimpleContext(){
		LOG4CPLUS_TRACE(log,"deconstruct a SimpleContext object.");
	}

	void SimpleContext::setVar(const std::string & name, const Json::Value & value, ValueContext va )
	{
	}
	
	Json::Value SimpleContext::getVar(const std::string &name, ValueContext va )
	{
		return Json::Value();
	}
	void SimpleContext::deleteVar(const std::string & name, ValueContext va )
	{
	}


	Context *SimpleContext::getParent()
	{
		return parent;
	}



	void SimpleContext::InitializeInstanceFields()
	{
		log = log4cplus::Logger::getInstance("SimpleContext");
	}


	std::string SimpleContext::eval(const std::string &expr,const std::string &filename, unsigned int line)
	{
		return "";
	}

	bool SimpleContext::evalCond(const std::string &expr,const std::string &filename, unsigned int line)
	{
		return true;
	}

	void SimpleContext::ExecuteFile(const std::string &fileName)
	{

	}

}
}
