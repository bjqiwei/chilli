#pragma once
#include "Context.h"
#include "libxml/tree.h"
#include <list>


namespace fsm
{

	class jsexception : public std::runtime_error {
	public:
		jsexception(const char * what, const char * file, uint32_t line, uint32_t column) :std::runtime_error(what), m_file(file ? file : ""), m_line(line), m_column(column)
		{

		}
		~jsexception()
		{

		}
		std::string m_file;
		uint32_t m_line;
		uint32_t m_column;
	};

	/// <summary>
	/// Interface for a component that may be used by the fsm engines to
	/// evaluate the expressions within the fsm document.
	/// 
	/// </summary>
	class  Evaluator
	{

	public:
		Evaluator() {};
		virtual ~Evaluator() {};
		virtual Context * newContext(const std::string &sessionid, Context * const parent) = 0;
		virtual void releaseContext(Context * const cx) = 0;
		virtual void deleteContext(size_t count) = 0;
		virtual size_t getContextCount() = 0;
		virtual bool hasContext() = 0;

	};

}