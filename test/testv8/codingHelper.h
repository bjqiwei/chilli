#include<string>
#include<windows.h>
#include<vector>
using namespace std;

//utf8 转 Unicode


static std::wstring Utf82Unicode(const std::string& utf8string)
{
	int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);
	if (widesize ==0 && GetLastError() == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	else if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<wchar_t> resultstring(widesize);
	int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);
	if (convresult != widesize)
	{
		throw std::exception("Error in conversion!");
	}
	return std::wstring(&resultstring[0]);
}
//unicode 转为 ascii
static std::string WideByte2Acsi(const std::wstring& wstrcode)
{
	int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, NULL, 0, NULL, NULL);
	if (asciisize == 0 && GetLastError() == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UNICODE sequence.");
	}
	else if (asciisize == 0)
	{
		throw std::exception("Error in conversion.");
	}
    std::vector<char> resultstring(asciisize);
	int convresult =::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);
	if (convresult != asciisize)
	{
		throw std::exception("Error in conversion!");
	}
	return std::string(&resultstring[0]);
}
//utf-8 转 ascii
static std::string UTF_82ASCII(const std::string& strUtf8Code)
{
	std::string strRet("");
	//先把 utf8 转为 unicode
	std::wstring wstr = Utf82Unicode(strUtf8Code);
	//最后把 unicode 转为 ascii
	strRet = WideByte2Acsi(wstr);
	return strRet;
}
///////////////////////////////////////////////////////////////////////
//ascii 转 Unicode
static std::wstring Acsii2WideByte(const std::string& strascii)
{
	int widesize = MultiByteToWideChar (CP_ACP, 0, strascii.c_str(), -1, NULL, 0);
	if (widesize == 0 && GetLastError() == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid ACSII sequence.");
	}
	else if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<wchar_t> resultstring(widesize);
	int convresult = MultiByteToWideChar (CP_ACP, 0, strascii.c_str(), -1, &resultstring[0], widesize);
	if (convresult != widesize)
	{
		throw std::exception("Error in conversion!");
	}
	return std::wstring(&resultstring[0]);
}
//Unicode 转 Utf8
static std::string Unicode2Utf8(const std::wstring& widestring)
{
	int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
	if (utf8size == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<char> resultstring(utf8size);
	int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);
	if (convresult != utf8size)
	{
		throw std::exception("Error in conversion!");
	}
	return std::string(&resultstring[0]);
}
//ascii 转 Utf8
static std::string ASCII2UTF_8(const std::string& strAsciiCode)
{
	std::string strRet("");
	//先把 ascii 转为 unicode
	std::wstring wstr = Acsii2WideByte(strAsciiCode);
	//最后把 unicode 转为 utf8
	strRet = Unicode2Utf8(wstr);
	return strRet;
}