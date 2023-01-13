#pragma once
#include <functional>
#include <set>
#include <string>
#include <vector>

// ordered vector, but with fast delete and dedup
template<class T>
class iVectorSet {
public:
   virtual bool has(const T& e) const = 0;
   virtual void appendIf(const T& e) = 0;
   virtual void foreach(std::function<void(const T&)> f) const = 0;
};

namespace cmp {

template<class T>
class iComparitor {
public:
   virtual bool isLess(const T& lhs, const T& rhs) const = 0;
};

template<class T, class C>
class adapter {
public:
   bool operator()(const T& lhs, const T& rhs) const { return m_cmp.isLess(lhs,rhs); }

private:
   C m_cmp;
};

class wstri : public iComparitor<std::wstring> {
public:
   virtual bool isLess(const std::wstring& lhs, const std::wstring& rhs) const
   {
      return ::_wcsicmp(lhs.c_str(),rhs.c_str());
   }
};

template<class T>
class std : public iComparitor<T> {
public:
   virtual bool isLess(const T& lhs, const T& rhs) const
   {
      return lhs < rhs;
   }
};

} // namespace cmp

template<class T, class C = cmp::std<T> >
class vectorSet : public iVectorSet<T> {
public:
   virtual bool has(const T& e) const
   {
      return m_set.find(e) != m_set.end();
   }

   virtual void appendIf(const T& e)
   {
      if(has(e))
         return;
      m_vec.push_back(e);
      m_set.insert(e);
   }

   virtual void foreach(std::function<void(const T&)> f) const
   {
      for(auto e : m_vec)
         f(e);
   }

private:
   std::vector<T> m_vec;
   std::set<T,cmp::adapter<T,C> > m_set;
};

typedef vectorSet<std::wstring,cmp::wstri> wivectorSet;
