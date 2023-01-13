#pragma once
#include "subobject.hpp"
#include <set>
#include <string>

class iPathAccumulator {
public:
   virtual void add(const std::wstring& path) = 0;
};

class pathAccumulator : public iPathAccumulator, public subobject {
public:
   virtual void add(const std::wstring& path);

   std::set<std::wstring> paths;
};
