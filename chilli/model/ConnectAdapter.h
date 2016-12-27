#pragma once

#include <stdint.h>
#include <string>

namespace chilli
{
namespace model {

	class ConnectAdapter {
	public:
		explicit ConnectAdapter();
		~ConnectAdapter();
		uint64_t GetId();
		static int Send(uint64_t id, const char * lpBuf, int nBufLen);
		static void Close(uint64_t id);
		static bool SetExtension(uint64_t id, const std::string & ext);
		static std::string GetExtension(uint64_t id);
	private:
		virtual int Send(const char * lpBuf, int nBufLen) = 0;
		virtual void Close() = 0;
	private:
		uint64_t m_ConnecterId = 0;
	protected:
		std::string m_Extension;
	};
}
}