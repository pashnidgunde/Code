#ifndef _DEMANGLE_H_
#define _DEMANGLE_H_

#include <cxxabi.h>
#include <string>
#include <typeinfo>
#include <stdexcept>

std::string demangle(const char* mangled_name)
{
    int status;
    char *demangled_name = abi::__cxa_demangle(mangled_name,nullptr,0,&status);
    if (status == 0)
    {
        std::string retval(demangled_name);
        free(demangled_name);
        return retval;
    }
    throw std::runtime_error("Error Demangling");
}

#endif