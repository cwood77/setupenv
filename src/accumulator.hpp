#pragma once
#include "subobject.hpp"
#include "vectorset.hpp"

class iPathAccumulator {
public:
   virtual void add(const std::wstring& path) = 0;
};

class pathAccumulator : public iPathAccumulator, public subobject {
public:
   explicit pathAccumulator(iVectorSet<std::wstring>& cont) : m_cont(cont) {}

   virtual void add(const std::wstring& path);

private:
   iVectorSet<std::wstring>& m_cont;
};
