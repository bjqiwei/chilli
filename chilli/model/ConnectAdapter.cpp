#pragma once

#include "ConnectAdapter.h"
#include <map>
#include <mutex>
#include <atomic>

namespace chilli
{
namespace model {

	static std::map<uint64_t, ConnectAdapter *> g_ConnecterSet;
	static std::mutex g_ConnecterSetMtx;
	static std::atomic_uint64_t g_ConnecterId;

	ConnectAdapter::ConnectAdapter():m_ConnecterId(++g_ConnecterId)
	{
		std::unique_lock<std::mutex> lcx(g_ConnecterSetMtx);
		g_ConnecterSet.insert(std::make_pair(m_ConnecterId, this));
	}

	ConnectAdapter::~ConnectAdapter()
	{
		std::unique_lock<std::mutex> lcx(g_ConnecterSetMtx);
		g_ConnecterSet.erase(m_ConnecterId);
	}


	uint64_t ConnectAdapter::GetId()
	{
		return m_ConnecterId;
	}

	int ConnectAdapter::Send(uint64_t id, const char * lpBuf, int nBufLen)
	{
		std::unique_lock<std::mutex> lcx(g_ConnecterSetMtx);
		auto & it = g_ConnecterSet.find(id);
		if (it != g_ConnecterSet.end()){
			return it->second->Send(lpBuf, nBufLen);
		}
		return 0;
	}

	void ConnectAdapter::Close(uint64_t id)
	{
		std::unique_lock<std::mutex> lcx(g_ConnecterSetMtx);
		auto & it = g_ConnecterSet.find(id);
		if (it != g_ConnecterSet.end()) {
			return it->second->Close();
		}
		return ;
	}

	bool ConnectAdapter::SetExtension(uint64_t id, const std::string & ext)
	{
		std::unique_lock<std::mutex> lcx(g_ConnecterSetMtx);
		auto & it = g_ConnecterSet.find(id);
		if (it != g_ConnecterSet.end()) {
			it->second->m_Extension = ext;
			return true;
		}
		return false;
	}

	std::string ConnectAdapter::GetExtension(uint64_t id)
	{
		std::unique_lock<std::mutex> lcx(g_ConnecterSetMtx);
		auto & it = g_ConnecterSet.find(id);
		if (it != g_ConnecterSet.end()) {
			return it->second->m_Extension;
		}
		return std::string();
	}

}
}