#pragma once
#include <string>
#include <map>
#ifdef FSM_LIB
#ifdef WIN32
#	define FSM_EXPORT __declspec(dllexport)
#else
#	define FSM_EXPORT
#endif
#else
#ifdef WIN32
#	define FSM_EXPORT __declspec(dllimport)
#else
#	define FSM_EXPORT
#endif
#endif
#define EXPIMP_TEMPLATE

//EXPIMP_TEMPLATE template class FSM_EXPORT std::allocator<char>;
//EXPIMP_TEMPLATE template class FSM_EXPORT std::basic_string<char, std::char_traits<char>, std::allocator<char>>;