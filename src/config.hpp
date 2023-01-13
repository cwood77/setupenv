#pragma once
#include <string>

class iConfigInternal {
public:
   virtual bool getBool(const std::string& name, bool defVal) const = 0;
   virtual std::string getString(const std::string& name, const std::string& defVal) const = 0;
};

class boolConfig {
public:
   typedef bool innerType;
   std::string name;
   bool defVal;

   boolConfig(const std::string& name, bool defVal) : name(name), defVal(defVal) {}
   bool get(const iConfigInternal& c) const { return c.getBool(name,defVal); }
};

class config {
public:
   explicit config(const iConfigInternal& c) : m_c(c) {}

   template<class T>
   typename T::innerType get(const T& c) { return c.get(m_c); }

private:
   const iConfigInternal& m_c;
};
