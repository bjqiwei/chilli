#pragma once
#ifndef _MODEL_SCXML_HEADER_
#define _MODEL_SCXML_HEADER_
#include <xmlHelper.h>
#include <Interpreter.h>
#include "scxml/model/State.h"
#include "scxml/SCXMLHelper.h"
#include <log4cplus/logger.h>
#include <string>
#include <map>


namespace fsm
{
namespace model
{



	/// <summary>
	/// The class in this SCXML object model that corresponds to the
	/// &lt;scxml&gt; root element, and serves as the &quot;document
	/// root&quot;.
	/// 
	/// </summary>
	class FSM_EXPORT SCXML 
	{

	private:
		xmlHelper::xmlDocumentPtr _docPtr;
		log4cplus::Logger log;

		xmlNodePtr datamodel;
		xmlNodePtr initalState;
	public:
		SCXML();
		~SCXML(){};

		State getInitialState();
		void setInitialState(xmlNodePtr xNode);
		void setXMLDocument(xmlDocPtr xDOC);
		xmlDocPtr getXMLDocument();
		xmlNodePtr getDatamodel();
		void setDatamodel(xmlNodePtr xNode);

;
	private:
		void InitializeInstanceFields();
	};
}
}

#endif // end scxml header
