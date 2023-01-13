#define WIN32_LEAN_AND_MEAN
#include "envvar.hpp"
#include <stdexcept>
#include <windows.h>

namespace {

class wcsBlock {
public:
   explicit wcsBlock(size_t n)
   {
      array = new wchar_t[n];
   }

   ~wcsBlock()
   {
      delete [] array;
   }

   wchar_t *array;
};

} // anonymous namespace

std::wstring envVar::get(const std::wstring& name) const
{
   auto nSize = ::GetEnvironmentVariableW(name.c_str(),NULL,0);

   wcsBlock array(nSize);
   ::GetEnvironmentVariableW(name.c_str(),array.array,nSize);

   std::wstring value = array.array;
   return value;
}

void envVar::set(const std::wstring& name, const std::wstring& value)
{
   auto success = ::SetEnvironmentVariableW(name.c_str(),value.c_str());
   if(!success)
      throw std::runtime_error("failed to set environment variable");
}
