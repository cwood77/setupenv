#pragma once
#include "vectorset.hpp"

class splitter {
public:
   static void split(const std::wstring& total, iVectorSet<std::wstring>& parts, wchar_t delim=L';');
   static std::wstring join(const iVectorSet<std::wstring>& parts, wchar_t delim=L';');
};
