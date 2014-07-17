#pragma once
#ifndef _STRING_HELPER_HEADER_
#define _STRING_HELPER_HEADER_

#include <string>
#include <algorithm>
#include<iostream>
#include<cctype>
#include <functional>



namespace helper
{


	/// <summary>
	/// helper namespace, all methods static final.
	/// 
	/// </summary>
	namespace string 
	{

		static inline std::string &ltrim(std::string &s)
		{
			s.erase(s.begin(), std::find_if(s.begin(), s.end(), 
				std::not1(std::ptr_fun<int, int>(std::isspace))));
			return s;
		}
		static inline std::string &rtrim(std::string &s)
		{
			s.erase(std::find_if(s.rbegin(), s.rend(),
				std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
			return s;
		}
		static inline std::string &trim(std::string &s)
		{
			return ltrim(rtrim(s));
		}
		static inline bool isStringEmpty(const std::string &attr)
		{
			std::string strAttr = attr;
			if (attr == "" || (trim(strAttr).length() == 0))
			{
				return true;
			}
			return false;
		}

		// relplace string content;
		static inline std::string & replaceString(std::string& str,const std::string& old_value,const std::string& new_value){
			for(std::string::size_type pos = 0;pos!=std::string::npos; pos+=new_value.length())   {   
				if( (pos=str.find(old_value,pos))!=std::string::npos   )   
					str.replace(pos,old_value.length(),new_value);   
				else   
					break;   
			}   
			return   str;  

		}

		//transition a string to upper
		static inline std::string & toUpper(std::string & str)
		{
			transform(str.begin(), str.end(), str.begin(), ::toupper);
		}

		//transition a string to lower
		static inline std::string & toLower(std::string &str)
		{
			transform(str.begin(), str.end(), str.begin(), ::tolower);
		}
	}
}//end namespace helper

#endif // end string helper header