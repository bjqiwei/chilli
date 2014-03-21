#ifndef _XMLHELPER_HEADER_
#define _XMLHELPER_HEADER_
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/tree.h>
//#include <WinSock.h>
#include <vector>
#include <string>
#include <log4cplus/logger.h>
#include "config.h"


//#pragma comment(lib,"ws2_32.lib")

using namespace std;
namespace fsm{
namespace xmlHelper{


FSM_EXPORT string  getXmlChildNodeValue(const xmlNodePtr xNode,const string &strChildNodeName);
FSM_EXPORT xmlNodePtr  getXmlChildNode(const xmlNodePtr xNode,const string &strChildNodeName);
FSM_EXPORT string  getXmlNodeAttributesValue( xmlNodePtr xNode,const string &strAttributeName);
FSM_EXPORT void setXmlNodeAttributesValue (xmlNodePtr xNode ,const string &strAttributeName,const string strValue);
FSM_EXPORT std::vector<xmlNodePtr> filterChildNodes(const string& tagName, const xmlNodePtr node);


class FSM_EXPORT XStr
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
	XStr(const xmlChar * const xmlCh);

    ~XStr();
    XStr(const XStr & other);
	XStr & operator=(const XStr & other);
	const string & strForm() const;
private:
    std::string _strValue ;
private:
	const xmlChar * _xChValue;
};

#define X(str) XStr(str).strForm()

class FSM_EXPORT xmlDocumentPtr
{
public :
	// -----------------------------------------------------------------------
	//  Constructors and Destructor
	// -----------------------------------------------------------------------
	xmlDocumentPtr(const xmlDocPtr xDoc);

	~xmlDocumentPtr();
	xmlDocumentPtr(xmlDocumentPtr & other);
	xmlDocumentPtr & operator=( xmlDocumentPtr & other);
	xmlDocumentPtr & operator=(const xmlDocPtr xDoc);
public :
	xmlDocPtr _xDocPtr;
};


class FSM_EXPORT CXPathContextPtr
{
public :
	// -----------------------------------------------------------------------
	//  Constructors and Destructor
	// -----------------------------------------------------------------------
	CXPathContextPtr(const xmlXPathContextPtr xPathCtxPtr);

	~CXPathContextPtr();
	CXPathContextPtr(CXPathContextPtr & other);
	CXPathContextPtr & operator=( CXPathContextPtr & other);
	CXPathContextPtr & operator=(const xmlXPathContextPtr xDoc);
public :
	xmlXPathContextPtr _xPathCtxPtr;
};

class FSM_EXPORT CXPathObjectPtr
{
public :
	// -----------------------------------------------------------------------
	//  Constructors and Destructor
	// -----------------------------------------------------------------------
	CXPathObjectPtr(const xmlXPathObjectPtr xPathObjPtr);

	~CXPathObjectPtr();
	CXPathObjectPtr(CXPathObjectPtr & other);
	CXPathObjectPtr & operator=( CXPathObjectPtr & other);
	CXPathObjectPtr & operator=(const xmlXPathObjectPtr xPathObjPtr);
public :
	xmlXPathObjectPtr _xPathObjPtr;
};

class FSM_EXPORT CXmlDocmentHelper{
public: 
	CXmlDocmentHelper(void);
	~CXmlDocmentHelper();
	void setRootNode(const std::string &strRoot);
	void setRootNode(xmlNodePtr rootNode);
	void newRootProp(const std::string  &name, const std::string &strValue);
	xmlAttrPtr copyProp2Root(xmlAttrPtr cur);
	void addChild(xmlNodePtr xChild);
	void addAddChildList(xmlNodePtr xChild);
	void addChild(const std::string &name,const std::string  &content);
	std::string getContent();
private:
	xmlDocumentPtr doc;
	xmlNodePtr _root;
	CXmlDocmentHelper(CXmlDocmentHelper & other);
	CXmlDocmentHelper & operator=( CXmlDocmentHelper & other);

};

class FSM_EXPORT CXmlParseHelper{
public: 
	CXmlParseHelper(const std::string &str);
	CXmlParseHelper(const char * xmlCh);
	std::string getRootName();
	std::string getRootProp(std::string name);
	std::string getChildContent(std::string childName);
	void setRootAttributesValue (const std::string &strAttributeName,const std::string &strValue);
	std::string getContent();
	~CXmlParseHelper(){};
private:
	log4cplus::Logger log;
	xmlDocumentPtr doc;
	xmlNodePtr _root;
	CXmlParseHelper(CXmlParseHelper & other);
	CXmlParseHelper & operator=( CXmlParseHelper & other);

};
}//end namespace xmlHelper
}//end namespace Fsm

#endif