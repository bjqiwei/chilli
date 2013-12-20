#include "SCXMLHelper.h"
#include "log4cplus/logger.h"
#include <log4cplus/loggingmacros.h>


namespace fsm
{
	std::string &SCXMLHelper::ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), 
			std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
	}

// trim from end
	std::string &SCXMLHelper::rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(),
			std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}

	std::string &SCXMLHelper::trim(std::string &s) {
		return ltrim(rtrim(s));
	} 

	bool SCXMLHelper::isStringEmpty(const std::string &attr)
	{
		std::string strAttr = attr;
		if (attr == "" || (trim(strAttr).length() == 0))
		{
			return true;
		}
		return false;
	}


	void SCXMLHelper::setNodeValue(xmlNodePtr const node, const std::string &value)
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("SCXMLHelper");
		switch (node->type)
		{
			case XML_ATTRIBUTE_NODE:
			case XML_ELEMENT_NODE:
				{
					xmlNodePtr child = node->children;

					while (child != NULL) {
						if (child->type == XML_TEXT_NODE) {
							xmlNodeSetContent(child,BAD_CAST value.c_str());
						}
						child = child->next;
					}
				}
				break;
			case XML_TEXT_NODE:
			case XML_CDATA_SECTION_NODE:
				xmlNodeSetContent(node,BAD_CAST value.c_str());
				break;
			default:
				LOG4CPLUS_ERROR(log, "Trying to set value of a strange Node type: " << node->type);
				//Logger.logln(Logger.E, err);
				break;
		}
	}

	std::string SCXMLHelper::getNodeValue(xmlNodePtr const node)
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("SCXMLHelper");
		std::string result = "";
		if (node == 0) return result;

		switch (node->type)
		{
			case XML_ATTRIBUTE_NODE:
			case XML_ELEMENT_NODE:
				
				{
					xmlNodePtr child = node->children;
				
					while (child != NULL) {
						if (child->type == XML_TEXT_NODE) {
							result.append(xmlHelper::XStr(xmlNodeGetContent(child)).strForm());
						}
						child = child->next;
					}
				}
				break;
			case XML_TEXT_NODE:
			case XML_CDATA_SECTION_NODE:
				result = xmlHelper::XStr(xmlNodeGetContent(node)).strForm();
				break;
			default:
				LOG4CPLUS_ERROR(log, "Trying to get value of a strange Node type: " << node->type);
		}
		return result;
	}


	std::string SCXMLHelper::escapeXML(const std::string &str)
	{
		if (str == "")
		{
			return "";
		}

		// Make the writer an arbitrary bit larger than the source string
		int len = str.length();
		std::string stringWriter;

		for (int i = 0; i < len; i++)
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

	SCXMLHelper::SCXMLHelper()
	{
	}
}

