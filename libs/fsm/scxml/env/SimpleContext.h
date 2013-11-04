#pragma once
#ifndef _SCXML_ENV_SIMPLECONTEXT_HEADER_
#define _SCXML_ENV_SIMPLECONTEXT_HEADER_
#include <scxml/Context.h>
#include <string>
#include <map>
#include <log4cplus/logger.h>
#include <FSM.h>

namespace fsm
{
namespace env
{
	class FSM_EXPORT SimpleContext : public Context
	{

	private:

		log4cplus::Logger log;

		Context *parent;
		std::map<std::string,std::string> vars;
	public:

		SimpleContext(); 
		virtual ~SimpleContext();
	
		SimpleContext(Context *const parent); //this(parent, nullptr);

		SimpleContext(std::map<std::string,std::string>const &initialVars); //this(nullptr, initialVars);

		SimpleContext(Context *const parent, std::map<std::string,std::string>const & initialVars);

		virtual void set(const std::string &name, std::string const &value);

		virtual std::string get(const std::string &name);

		virtual bool has(const std::string &name);

		/// <summary>
		/// Clear this Context.
		/// </summary>
		/// <seealso cref= org.apache.commons.scxml.Context#reset() </seealso>
		virtual void reset();

		virtual Context *getParent();

		virtual void setLocal(const std::string &name, const std::string & value);

		
	protected:
		virtual void setVars(const std::map<std::string,std::string> & vars);

		/// <summary>
		/// Get the Map of all local variables in this Context.
		/// </summary>
		/// <returns> Returns the vars. </returns>
	public:
		virtual std::map<std::string,std::string> & getVars();

		/// <summary>
		/// Set the log used by this <code>Context</code> instance.
		/// </summary>
		/// <param name="log"> The new log. </param>
	protected:
		virtual void setLog(log4cplus::Logger log);

		/// <summary>
		/// Get the log used by this <code>Context</code> instance.
		/// </summary>
		/// <returns> Log The log being used. </returns>
		virtual log4cplus::Logger getLog();
		virtual bool CompileScript(const std::string script);

	private:
		void InitializeInstanceFields();
	};
}
}

#endif // end simple context head file