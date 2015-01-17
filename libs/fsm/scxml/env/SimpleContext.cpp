#include "SimpleContext.h"
#include <log4cplus/loggingmacros.h>


namespace fsm
{
namespace env
{


	SimpleContext::SimpleContext(Context * const parent):Context(NULL,parent)
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

	void SimpleContext::Reset()
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
	bool SimpleContext::CompileScript(const std::string &script,const std::string &filename, unsigned int line,const void *xmlNode)
	{
		LOG4CPLUS_ERROR(log, "CompileScript is not implement.");
		return true;
	}

	std::string SimpleContext::eval(const std::string &expr,const std::string &filename, unsigned int line,const void *xmlNode)
	{
		return "";
	}

	bool SimpleContext::evalCond(const std::string &expr,const std::string &filename, unsigned int line,const void *xmlNode)
	{
		return true;
	}

	void SimpleContext::ExecuteFile(const std::string &fileName)
	{

	}

	void SimpleContext::SetContextPrivate(void *data){

	}
}
}
