#include "SCXML.h"


namespace fsm
{
namespace model
{

	SCXML::SCXML():_docPtr(NULL)
	{
		InitializeInstanceFields();
	}

	void SCXML::setXMLDocument(xmlDocPtr xDOC)
	{
		_docPtr = xDOC;
	}

	xmlNodePtr SCXML::getDatamodel()
	{
		return datamodel;
	}

	void SCXML::setDatamodel(xmlNodePtr xNode)
	{
		this->datamodel = xNode;
	}

	State SCXML::getInitialState()
	{
		return State(initalState);
	}

	void SCXML::setInitialState(xmlNodePtr xNode)
	{
		this->initalState = xNode;
	}

	xmlDocPtr SCXML::getXMLDocument()
	{
		return _docPtr._xDocPtr;
	}
	void SCXML::InitializeInstanceFields()
	{
		log = log4cplus::Logger::getInstance("scxml.model.SCXML");
	}

}
}

