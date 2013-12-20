#include "xmlHelper.h"
#include <string>
#include <vector>
#include <cstring>
#include <log4cplus/loggingmacros.h>


using namespace std;
namespace fsm{
namespace xmlHelper{


string  getXmlChildNodeValue(const xmlNodePtr  xNode, const string strChildNodeName)
{
	if (!xNode)
	{
		return "";
	}
	
	for (xmlNodePtr  xchildNode = xNode->children; xchildNode != NULL; xchildNode = xchildNode->next)
	{
				
		if(xchildNode->type == XML_ELEMENT_NODE && xmlStrEqual(xchildNode->name,BAD_CAST(strChildNodeName.c_str())))
		{
			return XStr(xmlNodeGetContent(xchildNode)).strForm();
		}
	}
	return "";
}
xmlNodePtr  getXmlChildNode(const xmlNodePtr  xNode,const string strChildNodeName)
{
	if (!xNode)
	{
		return NULL;
	}
	
	for (xmlNodePtr  xchildNode = xNode->children; xchildNode != NULL; xchildNode = xchildNode->next)
	{
		if(xchildNode->type == XML_ELEMENT_NODE && xmlStrEqual(xchildNode->name,BAD_CAST(strChildNodeName.c_str())))
		{
			return xchildNode;
		}
	}
	return NULL;
}

void setXmlNodeAttributesValue (xmlNodePtr xNode ,const string strAttributeName,const string strValue)
{
	if (!xNode) return ;

	xmlSetProp(xNode,BAD_CAST strAttributeName.c_str(),BAD_CAST strValue.c_str());
	return ;
}

string getXmlNodeAttributesValue (xmlNodePtr xNode ,const string strAttributeName)
{
	if (!xNode) return  "";

	try
	{
		return XStr(xmlGetProp(xNode,BAD_CAST strAttributeName.c_str())).strForm();
	}
	catch(...)
	{
		throw;
	}
	return "";
}
 std::vector <xmlNodePtr > filterChildNodes(const string& tagName, const xmlNodePtr  node)
{
	std::vector<xmlNodePtr> filteredChilds;
	for (xmlNodePtr  childNode = node->children; childNode != NULL; childNode = childNode->next) {
		if (childNode->type != XML_ELEMENT_NODE ||
			!xmlStrEqual(childNode->name, BAD_CAST(tagName.c_str())))
			continue;
		filteredChilds.push_back(childNode);
	}
	return filteredChilds;
}


 XStr::XStr(const xmlChar* const toTranscode):_xChValue(NULL)
 {
	 // Call the private transcoding method
	 _xChValue = toTranscode;
	 if (_xChValue) _strValue = string((char *) _xChValue);
	 else
		 _strValue = "";
 }

 XStr::~XStr()
 {
	 if (_xChValue)
	 {
		 xmlFree((void *)_xChValue);
	 }
 }

 string  XStr::strForm() const
 {
	 return _strValue;
 }
 xmlDocumentPtr::xmlDocumentPtr(const xmlDocPtr xDoc):_xDocPtr(xDoc){}

 xmlDocumentPtr::~xmlDocumentPtr()
 {
	 if (_xDocPtr) xmlFreeDoc(_xDocPtr);
 }
 xmlDocumentPtr::xmlDocumentPtr(xmlDocumentPtr & other)
 {
	 if (_xDocPtr && _xDocPtr != other._xDocPtr)xmlFreeDoc(_xDocPtr);
	 this->_xDocPtr = other._xDocPtr;
	 other._xDocPtr = NULL;
 }
 xmlDocumentPtr & xmlDocumentPtr::operator=( xmlDocumentPtr & other)
 {
	 if (_xDocPtr && _xDocPtr != other._xDocPtr)xmlFreeDoc(_xDocPtr);
	 this->_xDocPtr = other._xDocPtr;
	 other._xDocPtr = NULL;
	 return *this;
 }

 xmlDocumentPtr & xmlDocumentPtr::operator=(const xmlDocPtr xDoc)
 {
	 if (_xDocPtr && _xDocPtr != xDoc)xmlFreeDoc(_xDocPtr);
	 this->_xDocPtr = xDoc;
	 return *this;
 }

 CXPathContextPtr::CXPathContextPtr(const xmlXPathContextPtr xPathCtxPtr):_xPathCtxPtr(NULL)
 {
	 _xPathCtxPtr = xPathCtxPtr;
 }
 CXPathContextPtr::~CXPathContextPtr()
 {
	 if (_xPathCtxPtr) xmlXPathFreeContext(_xPathCtxPtr);
 }

 CXPathContextPtr::CXPathContextPtr(CXPathContextPtr & other)
 {
	 if (_xPathCtxPtr && _xPathCtxPtr != other._xPathCtxPtr)xmlXPathFreeContext(_xPathCtxPtr);
	 this->_xPathCtxPtr = other._xPathCtxPtr;
	 other._xPathCtxPtr = NULL;
 }
 CXPathContextPtr & CXPathContextPtr::operator=( CXPathContextPtr & other)
 {
	 if (_xPathCtxPtr && _xPathCtxPtr != other._xPathCtxPtr)xmlXPathFreeContext(_xPathCtxPtr);
	 this->_xPathCtxPtr = other._xPathCtxPtr;
	 other._xPathCtxPtr = NULL;
	 return *this;
 }

 CXPathContextPtr & CXPathContextPtr::operator=(const xmlXPathContextPtr xPathCtxPtr)
 {
	 if (_xPathCtxPtr && _xPathCtxPtr != xPathCtxPtr)xmlXPathFreeContext(_xPathCtxPtr);
	 this->_xPathCtxPtr = xPathCtxPtr;
	 return *this;
 }

 CXPathObjectPtr::CXPathObjectPtr(const xmlXPathObjectPtr xPathObjPtr):_xPathObjPtr(NULL)
 {
	 this->_xPathObjPtr = xPathObjPtr;
 }
 CXPathObjectPtr::~CXPathObjectPtr()
 {
	 if (_xPathObjPtr) xmlXPathFreeObject(_xPathObjPtr);
 }

 CXPathObjectPtr::CXPathObjectPtr(CXPathObjectPtr & other)
 {
	 if (_xPathObjPtr && _xPathObjPtr != other._xPathObjPtr)xmlXPathFreeObject(_xPathObjPtr);
	 this->_xPathObjPtr = other._xPathObjPtr;
	 other._xPathObjPtr = NULL;
 }
 CXPathObjectPtr & CXPathObjectPtr::operator=( CXPathObjectPtr & other)
 {
	 if (_xPathObjPtr && _xPathObjPtr != other._xPathObjPtr)xmlXPathFreeObject(_xPathObjPtr);
	 this->_xPathObjPtr = other._xPathObjPtr;
	 other._xPathObjPtr = NULL;
	 return *this;
 }

 CXPathObjectPtr & CXPathObjectPtr::operator=(const xmlXPathObjectPtr xPathObjPtr)
 {
	 if (_xPathObjPtr && _xPathObjPtr != xPathObjPtr)xmlXPathFreeObject(_xPathObjPtr);
	 this->_xPathObjPtr = xPathObjPtr;
	 return *this;
 }

 CXmlDocmentHelper::CXmlDocmentHelper(void):doc(NULL){
	 doc = xmlNewDoc(BAD_CAST "1.0");
 }

 CXmlDocmentHelper::~CXmlDocmentHelper(){

 }

 void CXmlDocmentHelper::setRootNode(std::string strRoot)
 {
	 _root = xmlNewNode(NULL,BAD_CAST strRoot.c_str());
	 xmlNodePtr ret_val = xmlDocSetRootElement(doc._xDocPtr, _root);
	 if ((ret_val != NULL)) {
		 xmlUnlinkNode(ret_val);
		 xmlFreeNode(ret_val);
	 }
 }

 void CXmlDocmentHelper::setRootNode(xmlNodePtr rootNode)
 {
	 _root = xmlCopyNode(rootNode,1);
	 xmlNodePtr ret_val = xmlDocSetRootElement(doc._xDocPtr, _root);
	 if ((ret_val != NULL)) {
		 xmlUnlinkNode(ret_val);
		 xmlFreeNode(ret_val);
	 }
 }

 void CXmlDocmentHelper::newRootProp(std::string  name, std::string strValue){
	 xmlNewProp(_root,BAD_CAST name.c_str(),BAD_CAST strValue.c_str());
 }
 
 xmlAttrPtr CXmlDocmentHelper::copyProp2Root(xmlAttrPtr cur){
	 return xmlCopyProp(_root,cur);
 }
 std::string CXmlDocmentHelper::getContent()
 {
	 xmlChar *xmlbuff;
	 int buffersize;
	 xmlDocDumpFormatMemory(doc._xDocPtr, &xmlbuff, &buffersize, 1);
	 return XStr(xmlbuff).strForm();
 }

 void CXmlDocmentHelper::addChild(xmlNodePtr xChild)
 {
	xmlNodePtr xNewChild = xmlCopyNode(xChild,1);
	xmlAddChild(_root,xNewChild);
 }

 void CXmlDocmentHelper::addAddChildList(xmlNodePtr xChild)
 {
	 xmlNodePtr xNewChild = xmlCopyNodeList(xChild);
	 xmlAddChildList(_root,xNewChild);
 }

 void CXmlDocmentHelper::addChild(std::string name,std::string  strContent){
	 xmlNodePtr node = xmlNewNode(NULL,BAD_CAST name.c_str());
	 xmlNodePtr content = xmlNewText(BAD_CAST strContent.c_str());
	 xmlAddChild(_root,node);
	 xmlAddChild(node,content);
}

CXmlParseHelper::CXmlParseHelper(const std::string &str ):doc(NULL),_root(NULL)
{
	log = log4cplus::Logger::getInstance("CXmlParseHelper");
	doc = xmlParseMemory(str.c_str(),str.length());
	if (doc._xDocPtr == NULL)
	{
		LOG4CPLUS_ERROR(log,  ": Convert a string to xml error was encountered,string=" << str);
		return;
	}
	_root = xmlDocGetRootElement(doc._xDocPtr);

	if (_root == NULL){
		LOG4CPLUS_ERROR(log, ": Convert a string to xml error was encountered,string=" << str);
	}
}
CXmlParseHelper::CXmlParseHelper(const char * xmlCh):doc(NULL),_root(NULL){
	log = log4cplus::Logger::getInstance("CXmlParseHelper");
	doc = xmlParseMemory(xmlCh,strlen(xmlCh));
	if (doc._xDocPtr == NULL)
	{
		LOG4CPLUS_ERROR(log,": Convert a string to xml error was encountered,string=" << xmlCh);
		return;
	}

	_root = xmlDocGetRootElement(doc._xDocPtr);

	if (_root == NULL){
		LOG4CPLUS_ERROR(log, ": Convert a string to xml error was encountered,string=" << xmlCh);
	}

}
std::string CXmlParseHelper::getRootName(){
	return _root ? (char *)_root->name:"";
}
std::string CXmlParseHelper::getRootProp(std::string name){
	return getXmlNodeAttributesValue(_root,name);
}
std::string CXmlParseHelper::getChildContent(std::string childName){
	return getXmlChildNodeValue(_root,childName);
}
void CXmlParseHelper::setRootAttributesValue(const std::string strAttributeName,const std::string strValue)
{
	setXmlNodeAttributesValue(_root,strAttributeName,strValue);
}

std::string CXmlParseHelper::getContent()
{
	xmlChar *xmlbuff;
	int buffersize;
	if (doc._xDocPtr == NULL) return "";
	xmlDocDumpFormatMemory(doc._xDocPtr, &xmlbuff, &buffersize, 1);
	return XStr(xmlbuff).strForm();
}
}//end namespace xmlHelper
}//end namespace Fsm