#ifndef FSM_CONFIG_H
#define FSM_CONFIG_H
#include <string>
#    define FSM_EXPORT __declspec(dllexport)
#define EXPIMP_TEMPLATE
#define  USE_LOG4CPLUS

EXPIMP_TEMPLATE  template class FSM_EXPORT  std::allocator<char>;
EXPIMP_TEMPLATE  template class FSM_EXPORT  std::basic_string<char, std::char_traits<char>, std::allocator<char>>;
#endif