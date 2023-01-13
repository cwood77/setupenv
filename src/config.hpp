#pragma once
#include <string>

class iConfigInternal {
public:
   virtual bool getBool(const std::string& name, bool defVal) const = 0;
   virtual std::wstring getString(const std::string& name, const std::wstring& defVal) const = 0;
};

class boolConfig {
public:
   typedef bool innerType;
   std::string name;
   bool defVal;

   boolConfig(const std::string& name, bool defVal) : name(name), defVal(defVal) {}
   bool get(const iConfigInternal& c) const { return c.getBool(name,defVal); }
};

class strConfig {
public:
   typedef std::wstring innerType;
   std::string name;
   std::wstring defVal;

   strConfig(const std::string& name, const std::wstring& defVal)
   : name(name), defVal(defVal) {}
   std::wstring get(const iConfigInternal& c) const { return c.getString(name,defVal); }
};

class config {
public:
   explicit config(const iConfigInternal& c) : m_c(c) {}

   template<class T>
   typename T::innerType get(const T& c) { return c.get(m_c); }

private:
   const iConfigInternal& m_c;
};
