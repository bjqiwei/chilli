#pragma once
#ifndef _CONTEXT_HEADER_
#define _CONTEXT_HEADER_
#include <map>
#include "config.h"
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
namespace fsm{


	/// <summary>
	/// A Context or &quot;scope&quot; for storing variables; usually tied to
	/// a SCXML root Object.
	/// </summary>
	class FSM_EXPORT Context
	{
	public:
		Context(void):parent(NULL){
			log = log4cplus::Logger::getInstance("fsm.Context");
			LOG4CPLUS_DEBUG(log,"new a fsm.Context object");
		};
		virtual ~Context(void){
			LOG4CPLUS_DEBUG(log,"destruction a fsm.Context object");
		};

	public:
		/// <summary>
		/// Assigns a new value to an existing variable or creates a new one.
		/// The method searches the chain of parent Contexts for variable
		/// existence.
		/// </summary>
		/// <param name="name"> The variable name </param>
		/// <param name="value"> The variable value </param>
		virtual void set(const std::string &name, const std::string & value) = 0;

		/// <summary>
		/// Assigns a new value to an existing variable or creates a new one.
		/// The method allows to shadow a variable of the same name up the
		/// Context chain.
		/// </summary>
		/// <param name="name"> The variable name </param>
		/// <param name="value"> The variable value </param>
		virtual void setLocal(const std::string &name, const std::string & value) = 0;

		/// <summary>
		/// Get the value of this variable; delegating to parent.
		/// </summary>
		/// <param name="name"> The name of the variable </param>
		/// <returns> The value (or null) </returns>
		virtual std::string get(const std::string &name) = 0;

		/// <summary>
		/// Check if this variable exists, delegating to parent.
		/// </summary>
		/// <param name="name"> The name of the variable </param>
		/// <returns> Whether a variable with the name exists in this Context </returns>
		virtual bool has(const std::string &name) = 0;

		/// <summary>
		/// Get the Map of all variables in this Context.
		/// </summary>
		/// <returns> Local variable entries Map
		/// To get variables in parent Context, call getParent().getVars(). </returns>
		/// <seealso cref= #getParent() </seealso>
		virtual std::map<std::string,std::string> & getVars() = 0;

		/// <summary>
		/// Clear this Context.
		/// </summary>
		virtual void reset() = 0;

		/// <summary>
		/// Get the parent Context, may be null.
		/// </summary>
		/// <returns> The parent Context in a chained Context environment </returns>
		virtual Context *getParent() = 0;
		virtual bool CompileScript(const std::string script) = 0;
		void setLog(log4cplus::Logger _log){log = _log;};
	public:
		log4cplus::Logger log;
	protected:
		//父Context
		Context *parent;
		//上下文中的变量
		std::map<std::string,std::string> vars;
	};

}

#endif //end Context