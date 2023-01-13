#include "split.hpp"
#include <sstream>

void splitter::split(const std::wstring& total, iVectorSet<std::wstring>& parts, wchar_t delim)
{
   const wchar_t *pThumb = total.c_str();
   const wchar_t *pStart = pThumb;
   for(;;++pThumb)
   {
      bool isEnd = (*pThumb == 0);
      bool isWordEnd = (isEnd || (*pThumb == delim));

      if(isWordEnd)
      {
         std::wstring word(pStart,pThumb-pStart);
         parts.appendIf(word);
         pStart = pThumb + 1;
      }

      if(isEnd)
         break;
   }
}

std::wstring splitter::join(const iVectorSet<std::wstring>& parts, wchar_t delim)
{
   std::wstringstream stream;

   bool first = true;
   parts.foreach([&](auto&e)
   {
      if(first)
         first = false;
      else
         stream << delim;
      stream << e;
   });

   return stream.str();
}
