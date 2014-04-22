#pragma once
#ifndef _STRING_HELPER_HEADER_
#define _STRING_HELPER_HEADER_

#include <string>
#include <algorithm>
#include<algorithm>
#include<iostream>
#include<cctype>
#include <xfunctional>



namespace helper
{


	/// <summary>
	/// common namespace, all methods static final.
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
	}
}//end namespace helper

#endif // end string helper header