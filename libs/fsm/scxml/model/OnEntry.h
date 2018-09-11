#pragma once
#include <string>
#include <vector>
#include "Action.h"

namespace fsm
{
namespace model
{
	
	class OnEntry
	{
		
	public:
		OnEntry(const std::string &filename, uint32_t lineno):m_strFilename(filename), m_lineNo(lineno){};
		virtual ~OnEntry();
		std::vector<std::shared_ptr<Action>> m_Actions;
		void addAction(std::shared_ptr<Action> actionptr);
	private: 
		std::string m_strFilename;
		uint32_t m_lineNo;
	};
}
}
