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

	SimpleContext::SimpleContext(std::map<std::string,std::string>const &initialVars):Context(NULL,NULL)
	{
		InitializeInstanceFields();
		this->eventVars = initialVars;
		LOG4CPLUS_TRACE(log,"construct a SimpleContext object.");
	}

	SimpleContext::SimpleContext(Context *const parent, std::map<std::string,std::string>const &initialVars):Context(NULL,NULL)
	{
		InitializeInstanceFields();
		this->parent = parent;
		this->eventVars = initialVars;
		LOG4CPLUS_TRACE(log,"construct a SimpleContext object.");
	}
	SimpleContext::~SimpleContext(){
		LOG4CPLUS_TRACE(log,"deconstruct a SimpleContext object.");
	}

	

	
	void SimpleContext::Reset()
	{
		eventVars.clear();
	}

	Context *SimpleContext::getParent()
	{
		return parent;
	}

	void SimpleContext::setLocal(const std::string &name, const std::string & value,bool isDelete)
	{
		if(isDelete)eventVars[name]=value;
		LOG4CPLUS_ERROR(log, name << "=" << value);
	}

	void SimpleContext::SetEventVars(std::map<std::string,std::string>const & vars)
	{
		this->eventVars = vars;
	}

	std::map<std::string,std::string> & SimpleContext::getEventVars()
	{
		return eventVars;
	}



	void SimpleContext::InitializeInstanceFields()
	{
		log = log4cplus::Logger::getInstance("SimpleContext");
	}
	bool SimpleContext::CompileScript(const std::string &script,const std::string &filename, unsigned int line,void *xmlNode)
	{
		LOG4CPLUS_ERROR(log, "CompileScript is not implement.");
		return true;
	}

	std::string SimpleContext::eval(const std::string &expr,const std::string &filename, unsigned int line,void *xmlNode)
	{
		return get(expr);
	}

	bool SimpleContext::evalCond(const std::string &expr,const std::string &filename, unsigned int line,void *xmlNode)
	{
		if(get(expr).compare("0") ==0)
			return false;
		return true;
	}

	xmlNodePtr SimpleContext::evalLocation(const std::string &expr,const std::string &filename, unsigned int line,void *xmlNode)
	{
		if (expr == "")
		{
			return NULL;
		}
		return NULL;
	}
	void SimpleContext::SetContextPrivate(void *data)
	{

	}
	void SimpleContext::ExecuteFile(const std::string &fileName)
	{

	}
}
}
