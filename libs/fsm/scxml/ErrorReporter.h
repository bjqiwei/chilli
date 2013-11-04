#pragma once
#ifndef _FSM_ERRORREPOERTER_HEADER_
#define _FSM_ERRORREPOERTER_HEADER_
#include <string>

namespace fsm
{

	// Used for suggesting replacement in deprecation warnings

	/// <summary>
	/// An interface for reporting SCXML errors to the host environment,
	/// containing the definition of commonly occuring errors while executing
	/// SCXML documents.
	/// 
	/// </summary>
	class ErrorReporter
	{

		/// <summary>
		/// Handler for reporting an error.
		/// </summary>
		/// <param name="errCode">
		///            one of the ErrorReporter's constants </param>
		/// <param name="errDetail">
		///            human readable description </param>
		/// <param name="errCtx">
		///            typically an SCXML element which caused an error,
		///            may be accompanied by additional information </param>
	public:
		virtual void onError(const std::string &errCode, const std::string &errDetail, std::string & errCtx) = 0;

	};

}
#endif //end error reporter head file