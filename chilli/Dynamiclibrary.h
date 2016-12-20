#pragma once
#include <string>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#ifdef WIN32
#include <Windows.h>
#else
#endif

class Dynamiclibrary
{
public:
	explicit Dynamiclibrary(const std::string & libName) :m_LibName(libName)
	{
		log = log4cplus::Logger::getInstance(m_LibName);
	}

	~Dynamiclibrary(void) {

	}

	bool Open()
	{
#ifdef WIN32
		this->m_handle = LoadLibrary(m_LibName.c_str());
#else
		this->m_handle = dlopen(m_LibName.c_str(), RTLD_LAZY);
#endif

		if (this->m_handle == nullptr)
		{
#ifdef WIN32
			unsigned err = GetLastError();
#else				
			const char * err = dlerror();
#endif
			LOG4CPLUS_ERROR(log, m_LibName << " load library failed with \"" << std::hex << err << "\"");
			return false;
		}
		return true;
	}

	bool Close()
	{
		if (m_handle != nullptr) {
#ifdef  WIN32
			BOOL ret = FreeLibrary((HMODULE)m_handle);
			if (!ret) {
				unsigned err = GetLastError();
				LOG4CPLUS_ERROR(log, m_LibName << " close library failed with \"" << std::hex << err << "\"");
				return false;
			}
#else
			int ret = dlclose(m_handle);
			if (ret != 0) {
				const char * err = dlerror();
				LOG4CPLUS_ERROR(log, m_LibName << " close library failed with \"" << std::hex << err << "\"");
				return false;
			}
#endif
		}
		m_handle = nullptr;
		return true;
	}

	void* GetFunction(const std::string & funcName)
	{
		void * func_addr = nullptr;
		if (m_handle != nullptr)
		{
#ifdef  WIN32
			func_addr = GetProcAddress((HMODULE)m_handle, funcName.c_str());
#else
			func_addr = dlsym(m_handle, funcName.c_str());
#endif	
		}
		if (func_addr == nullptr) {
			LOG4CPLUS_ERROR(log, " Get function " << funcName << " is null.");
		}

		return func_addr;
	}


private:
	// name of the shared library
	std::string m_LibName;
	void* m_handle = nullptr;
	log4cplus::Logger log;

};