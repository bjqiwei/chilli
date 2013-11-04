#include "SimpleContext.h"


namespace fsm
{
namespace env
{

	SimpleContext::SimpleContext():parent(NULL)
	{
		InitializeInstanceFields();
	}

	SimpleContext::SimpleContext(Context *const parent):parent(NULL)
	{
		InitializeInstanceFields();
		this->parent  =parent;
	}

	SimpleContext::SimpleContext(std::map<std::string,std::string>const &initialVars):parent(NULL)
	{
		InitializeInstanceFields();
		this->vars = initialVars;
	}

	SimpleContext::SimpleContext(Context *const parent, std::map<std::string,std::string>const &initialVars):parent(NULL)
	{
		InitializeInstanceFields();
		this->parent = parent;
		this->vars = initialVars;

	}
	SimpleContext::~SimpleContext(){}

	void SimpleContext::set(const std::string &name, const std::string &value)
	{
		if (vars.count(name)>0) //first try to override local
		{
			setLocal(name, value);
		} //then check for global
		else if (parent != 0 && parent->has(name))
		{
			parent->set(name, value);
		} //otherwise create a new local variable
		else
		{
			setLocal(name, value);
		}
	}

	std::string SimpleContext::get(const std::string &name)
	{
		if (vars.count(name)>0)
		{
			return vars[name];
		}
		else if (parent != 0)
		{
			return parent->get(name);
		}
		else
		{
			return "";
		}
	}

	bool SimpleContext::has(const std::string &name)
	{
		if (vars.count(name)>0)
		{
			return true;
		}
		else if (parent != 0 && parent->has(name))
		{
			return true;
		}
		return false;
	}

	void SimpleContext::reset()
	{
		vars.clear();
	}

	Context *SimpleContext::getParent()
	{
		return parent;
	}

	void SimpleContext::setLocal(const std::string &name, const std::string & value)
	{
		vars[name]=value;
		LOG4CPLUS_WARN(log, name << "=" << value);
	}

	void SimpleContext::setVars(std::map<std::string,std::string>const & vars)
	{
		this->vars = vars;
	}

	std::map<std::string,std::string> & SimpleContext::getVars()
	{
		return vars;
	}

	void SimpleContext::setLog(log4cplus::Logger log)
	{
		this->log = log;
	}

	log4cplus::Logger SimpleContext::getLog()
	{
		return log;
	}

	void SimpleContext::InitializeInstanceFields()
	{
		log = log4cplus::Logger::getInstance("scxml.SimpleContext");
	}
	bool SimpleContext::CompileScript(const std::string script)
	{
		LOG4CPLUS_WARN(log,"CompileScript is not implement.");
		return true;
	}
}
}
