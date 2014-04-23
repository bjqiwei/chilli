#ifndef FSM_CONFIG_H
#define FSM_CONFIG_H
#include <string>
#include <map>
#ifdef FSM_LIB
#    define FSM_EXPORT __declspec(dllexport)
#else
#	define FSM_EXPORT __declspec(dllimport)
#endif
#define EXPIMP_TEMPLATE

EXPIMP_TEMPLATE template class FSM_EXPORT std::allocator<char>;
EXPIMP_TEMPLATE template class FSM_EXPORT std::basic_string<char, std::char_traits<char>, std::allocator<char>>;
#endif