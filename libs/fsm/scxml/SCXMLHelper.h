#pragma once
#ifndef _SCXMLHELPER_HEADER_
#define _SCXMLHELPER_HEADER_

#include <string>
#include <vector>
#include <set>
#include<functional>
#include<algorithm>
#include<iostream>
#include<cctype>
#include <xmlHelper.h>
#include <log4cplus/logger.h>


// Base class include file.

#include "model\Datamodel.h"
#include "Context.h"
#include "Evaluator.h"


namespace fsm
{



	/// <summary>
	/// Helper class, all methods static final.
	/// 
	/// </summary>
	class FSM_EXPORT SCXMLHelper
	{

		/// <summary>
		/// Return true if the string is empty.
		/// </summary>
		/// <param name="attr"> The String to test </param>
		/// <returns> Is string empty </returns>
	public:
		static inline std::string &ltrim(std::string &s);
		static inline std::string &rtrim(std::string &s);
		static inline std::string &trim(std::string &s);
		static bool isStringEmpty(const std::string &attr);


		/// <summary>
		/// Set node value, depending on its type, from a String.
		/// </summary>
		/// <param name="node"> A Node whose value is to be set </param>
		/// <param name="value"> The new value </param>
		static void setNodeValue(xmlNodePtr const node, const std::string &value);

		/// <summary>
		/// Retrieve a DOM node value as a string depending on its type.
		/// </summary>
		/// <param name="node"> A node to be retreived </param>
		/// <returns> The value as a string </returns>
		static std::string getNodeValue(xmlNodePtr const node);



		/// <summary>
		/// Clone function model.
		/// </summary>
		/// <param name="fucmodel"> The function model to clone. </param>
		/// <param name="ctx"> The context to clone to. </param>
		/// <param name="evaluator"> The expression evaluator. </param>
		/// <param name="log"> The error log. </param>
		static void cloneFunctionmodel(const xmlNodePtr fucmodel, Context *const ctx, Evaluator *const evaluator, log4cplus::Logger const log);
		/// <summary>
		/// Escape XML strings for serialization.
		/// The basic algorithm is taken from Commons Lang (see oacl.Entities.java)
		/// </summary>
		/// <param name="str"> A string to be escaped </param>
		/// <returns> The escaped string </returns>
		static std::string escapeXML(const std::string &str);

	private:

		SCXMLHelper(); //super();

	};
}//end namespace fsm

#endif // end scxml helper header