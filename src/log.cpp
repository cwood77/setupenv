#include "log.hpp"
#include <cstdio>
#include <stdarg.h>

void streamLog::writeLn(const std::string& fmt, ...)
{
   char buffer[2000];
   va_list args;
   va_start(args, fmt);
   vsnprintf(buffer,2000,fmt.c_str(),args);
   va_end(args);

   m_out << buffer << std::endl;
}
