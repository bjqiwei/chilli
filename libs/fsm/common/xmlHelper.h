#ifndef _XML_HELPER_HEADER_
#define _XML_HELPER_HEADER_
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/tree.h>
//#include <WinSock.h>
#include <vector>
#include <string>
#include <string.h>

namespace helper{
namespace xml{

	/// <summary>
		/// Escape XML strings for serialization.
		/// The basic algorithm is taken from Commons Lang (see oacl.Entities.java)
		/// </summary>
		/// <param name="str"> A string to be escaped </param>
		/// <returns> The escaped string </returns>
		static inline std::string escapeXML(const std::string &str){
			if (str == "")
			{
				return "";
			}

			// Make the writer an arbitrary bit larger than the source string
			size_t len = str.length();
			std::string stringWriter;

			for (size_t i = 0; i < len; i++)
			{
				char c = str.at(i);
				std::string entityName = ""; // Look for XML 1.0 predefined entities
				switch (c)
				{
				case '"':
					entityName = "quot";
					break;
				case '&':
					entityName = "amp";
					break;
				case '\'':
					entityName = "apos";
					break;
				case '<':
					entityName = "lt";
					break;
					case '>':
					entityName = "gt";
					break;
				default: break;
				}
				if (entityName == "")
				{
					if (c > 0x7F)
					{
						stringWriter.append("&#");

						stringWriter.insert(stringWriter.end(),1,c);
						stringWriter.append(";");
					}
					else
					{
						stringWriter.insert(stringWriter.end(),1,c);
					}
				}
				else
				{
					stringWriter.append("&");
					stringWriter.append(entityName);
					stringWriter.append(";");
				}
			}
			return stringWriter;
		}
	class XStr
	{
	public :
		// -----------------------------------------------------------------------
		//  Constructors and Destructor
		// -----------------------------------------------------------------------
		XStr(const xmlChar * const xmlCh):_xChValue(xmlCh)
		{
			// Call the private transcoding method
			if (_xChValue) _strValue = (char *) _xChValue;
			else
				_strValue = "";
		}

		virtual ~XStr()
		{ 
			if (_xChValue)
			{
				xmlFree((void *)_xChValue);
			}
		}
		XStr(const XStr & other);
		XStr & operator=(const XStr & other);
		inline const std::string & strForm() const
		{
			return std::move(_strValue);
		}
	private:
		std::string _strValue ;
	private:
		const xmlChar * _xChValue;
	};

#define X(str) XStr(str).strForm()


static inline std::string  getXmlChildNodeValue(const ::xmlNodePtr xNode,const std::string &strChildNodeName)
{
	if (!xNode){
		return "";
	}

	for (xmlNodePtr  xchildNode = xNode->children; xchildNode != NULL; xchildNode = xchildNode->next)
	{

		if(xchildNode->type == XML_ELEMENT_NODE && xmlStrEqual(xchildNode->name,BAD_CAST(strChildNodeName.c_str())))
		{
			xmlChar * xmlbuff = xmlNodeGetContent(xchildNode);
			std::string value;
			if (xmlbuff)
				value = (char *)xmlbuff;
			xmlFree(xmlbuff);
			return std::move(value);
		}
	}
	return "";
}
static inline ::xmlNodePtr  getXmlChildNode(const ::xmlNodePtr xNode,const std::string &strChildNodeName)
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
static inline std::string  getXmlNodeAttributesValue( xmlNodePtr xNode,const std::string &strAttributeName)
{
	if (!xNode) return  "";
	xmlChar * value = xmlGetProp(xNode, BAD_CAST strAttributeName.c_str());
	std::string str;
	if (value){
		str = (char *)value;
	}
	xmlFree(value);
	return std::move(str);
}
static inline void setXmlNodeAttributesValue (xmlNodePtr xNode ,const std::string &strAttributeName,const std::string &strValue)
{
	if (!xNode) return ;

	if(!(xmlHasProp(xNode, (xmlChar*)strAttributeName.c_str())))
	{
		xmlNewProp(xNode, (xmlChar*)strAttributeName.c_str(), (xmlChar*)strValue.c_str());	
	}
	else
	{
		xmlSetProp(xNode,BAD_CAST strAttributeName.c_str(),BAD_CAST strValue.c_str());
	}
	return ;
}
static inline std::vector<xmlNodePtr> filterChildNodes(const std::string& tagName, const xmlNodePtr node)
{
	std::vector<xmlNodePtr> filteredChilds;

	if(node == NULL) return filteredChilds;

	for (xmlNodePtr  childNode = node->children; childNode != NULL; childNode = childNode->next) {
		if (childNode->type != XML_ELEMENT_NODE ||
			!xmlStrEqual(childNode->name, BAD_CAST(tagName.c_str())))
			continue;
		filteredChilds.push_back(childNode);
	}
	return filteredChilds;
}




class  CXmlDocumentPtr
{
private ://delete
	// -----------------------------------------------------------------------
	//  Constructors and Destructor
	// -----------------------------------------------------------------------
	CXmlDocumentPtr(const xmlDocPtr xDoc):_xDocPtr(xDoc){}

	virtual ~CXmlDocumentPtr() 
	{	
		if (_xDocPtr) xmlFreeDoc(_xDocPtr);
	}
	CXmlDocumentPtr(CXmlDocumentPtr & other)
	{
		if (_xDocPtr && _xDocPtr != other._xDocPtr)xmlFreeDoc(_xDocPtr);
		this->_xDocPtr = other._xDocPtr;
		other._xDocPtr = NULL;
	}
	CXmlDocumentPtr & operator=( CXmlDocumentPtr & other)
	{
		if (_xDocPtr && _xDocPtr != other._xDocPtr)xmlFreeDoc(_xDocPtr);
		this->_xDocPtr = other._xDocPtr;
		other._xDocPtr = NULL;
		return *this;
	}
	CXmlDocumentPtr & operator=(const xmlDocPtr xDoc)
	{
		if (_xDocPtr && _xDocPtr != xDoc)xmlFreeDoc(_xDocPtr);
		this->_xDocPtr = xDoc;
		return *this;
	}

public :
	xmlDocPtr _xDocPtr;
};


class  CXPathContextPtr
{
private ://delete
	// -----------------------------------------------------------------------
	//  Constructors and Destructor
	// -----------------------------------------------------------------------
	CXPathContextPtr(const xmlXPathContextPtr xPathCtxPtr):_xPathCtxPtr(xPathCtxPtr){

	}

	virtual ~CXPathContextPtr()
	{
		 if (_xPathCtxPtr) xmlXPathFreeContext(_xPathCtxPtr);
	}
	CXPathContextPtr(CXPathContextPtr & other)
	{
		if (_xPathCtxPtr && _xPathCtxPtr != other._xPathCtxPtr)xmlXPathFreeContext(_xPathCtxPtr);
		this->_xPathCtxPtr = other._xPathCtxPtr;
		other._xPathCtxPtr = NULL;
	}
	CXPathContextPtr & operator=( CXPathContextPtr & other)
	{
		if (_xPathCtxPtr && _xPathCtxPtr != other._xPathCtxPtr)xmlXPathFreeContext(_xPathCtxPtr);
		this->_xPathCtxPtr = other._xPathCtxPtr;
		other._xPathCtxPtr = NULL;
		return *this;
	}
	CXPathContextPtr & operator=(const xmlXPathContextPtr xPathCtxPtr)
	{
		if (_xPathCtxPtr && _xPathCtxPtr != xPathCtxPtr)xmlXPathFreeContext(_xPathCtxPtr);
		this->_xPathCtxPtr = xPathCtxPtr;
		return *this;
	}
public :
	xmlXPathContextPtr _xPathCtxPtr;
};

class  CXPathObjectPtr
{
public :
	// -----------------------------------------------------------------------
	//  Constructors and Destructor
	// -----------------------------------------------------------------------
	CXPathObjectPtr(const xmlXPathObjectPtr xPathObjPtr):_xPathObjPtr(xPathObjPtr){

	}

	virtual ~CXPathObjectPtr()
	{
		if (_xPathObjPtr) xmlXPathFreeObject(_xPathObjPtr);
	}
	CXPathObjectPtr(CXPathObjectPtr & other)
	{
		if (_xPathObjPtr && _xPathObjPtr != other._xPathObjPtr)xmlXPathFreeObject(_xPathObjPtr);
		this->_xPathObjPtr = other._xPathObjPtr;
		other._xPathObjPtr = NULL;
	}
	CXPathObjectPtr & operator=( CXPathObjectPtr & other)
	{
		if (_xPathObjPtr && _xPathObjPtr != other._xPathObjPtr)xmlXPathFreeObject(_xPathObjPtr);
		this->_xPathObjPtr = other._xPathObjPtr;
		other._xPathObjPtr = NULL;
		return *this;
	}
	CXPathObjectPtr & operator=(const xmlXPathObjectPtr xPathObjPtr) 
	{
		if (_xPathObjPtr && _xPathObjPtr != xPathObjPtr)xmlXPathFreeObject(_xPathObjPtr);
		this->_xPathObjPtr = xPathObjPtr;
		return *this;
	}
public :
	xmlXPathObjectPtr _xPathObjPtr;
};

class  CXmlDocmentHelper{
private://delete
	CXmlDocmentHelper(void):doc(xmlNewDoc(BAD_CAST "1.0")){}

	virtual ~CXmlDocmentHelper(){}

	void setRootNode(const std::string &strRoot)
	{
		_root = xmlNewNode(NULL,BAD_CAST strRoot.c_str());
		xmlNodePtr ret_val = xmlDocSetRootElement(doc, _root);
		if ((ret_val != NULL)) {
			xmlUnlinkNode(ret_val);
			xmlFreeNode(ret_val);
		}
	}
	void setRootNode(xmlNodePtr rootNode)
	{
		_root = xmlCopyNode(rootNode,1);
		xmlNodePtr ret_val = xmlDocSetRootElement(doc, _root);
		if ((ret_val != NULL)) {
			xmlUnlinkNode(ret_val);
			xmlFreeNode(ret_val);
		}
	}
	void newRootProp(const std::string  &name, const std::string &strValue)
	{
		 xmlNewProp(_root,BAD_CAST name.c_str(),BAD_CAST strValue.c_str());
	}
	xmlAttrPtr copyProp2Root(xmlAttrPtr cur)
	{
		return xmlCopyProp(_root,cur);
	}
	void addChild(xmlNodePtr xChild)
	{
		xmlNodePtr xNewChild = xmlCopyNode(xChild,1);
		xmlAddChild(_root,xNewChild);
	}
	void addAddChildList(xmlNodePtr xChild){
		xmlNodePtr xNewChild = xmlCopyNodeList(xChild);
		xmlAddChildList(_root,xNewChild);
	}
	void addChild(const std::string &name,const std::string  &strContent)
	{
		xmlNodePtr node = xmlNewNode(NULL,BAD_CAST name.c_str());
		xmlNodePtr content = xmlNewText(BAD_CAST strContent.c_str());
		xmlAddChild(_root,node);
		xmlAddChild(node,content);
	}
	std::string getContent()
	{
		xmlChar *xmlbuff;
		int buffersize;
		xmlDocDumpFormatMemory(doc, &xmlbuff, &buffersize, 1);
		std::string value;
		if (xmlbuff)
			value = (char *)xmlbuff;
		xmlFree(xmlbuff);
		return std::move(value);
	}
private:
	xmlDocPtr doc;
	xmlNodePtr _root;
	CXmlDocmentHelper(CXmlDocmentHelper & other);
	CXmlDocmentHelper & operator=( CXmlDocmentHelper & other);

};

class  CXmlParseHelper{
private: //delete
	CXmlParseHelper(const std::string &str):doc(xmlParseMemory(str.c_str(),str.length())),_root(NULL)
	{
		if (doc == NULL)
		{
			//LOG4CPLUS_ERROR(log, "." + m_strSessionID,  ": Convert a string to xml error was encountered,string=" << str);
			return;
		}
		_root = xmlDocGetRootElement(doc);

		if (_root == NULL){
			//LOG4CPLUS_ERROR(log, "." + m_strSessionID, ": Convert a string to xml error was encountered,string=" << str);
		}
	}
	CXmlParseHelper(const char * xmlCh):doc(xmlParseMemory(xmlCh,::strlen(xmlCh))),_root(NULL){

		if (doc == NULL)
		{
			//LOG4CPLUS_ERROR(log,": Convert a string to xml error was encountered,string=" << xmlCh);
			return;
		}

		_root = xmlDocGetRootElement(doc);

		if (_root == NULL){
			//LOG4CPLUS_ERROR(log, "." + m_strSessionID, ": Convert a string to xml error was encountered,string=" << xmlCh);
		}

	}
	
	std::string getRootName()
	{
		return _root ? (char *)_root->name:"";
	}
	
	std::string getRootProp(const std::string &name)
	{
		return getXmlNodeAttributesValue(_root,name);
	}
	
	std::string getChildContent(const std::string &childName)
	{
		return getXmlChildNodeValue(_root,childName);
	}
	
	void setRootAttributesValue (const std::string &strAttributeName,const std::string &strValue)
	{
		setXmlNodeAttributesValue(_root,strAttributeName,strValue);
	}


	xmlNodePtr getRootNode()
	{
		return _root;
	}
	
	std::string getContent()
	{
		xmlChar *xmlbuff;
		int buffersize;
		if (doc == NULL) return "";
		xmlDocDumpFormatMemory(doc, &xmlbuff, &buffersize, 1);
		std::string value;
		if (xmlbuff)
			value = (char *)xmlbuff;
		xmlFree(xmlbuff);
		return std::move(value);
	}
	virtual ~CXmlParseHelper(){};
private:
	xmlDocPtr doc;
	xmlNodePtr _root;
	CXmlParseHelper(CXmlParseHelper & other);
	CXmlParseHelper & operator=( CXmlParseHelper & other);

};
}//end namespace xml
}//end namespace helper

#endif