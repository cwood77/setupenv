#pragma once
#include <string>

class iEnvVar {
public:
   virtual std::wstring get(const std::wstring& name) const = 0;
   virtual void set(const std::wstring& name, const std::wstring& value) = 0;
};

class envVarMomento {
public:
   envVarMomento(iEnvVar& v, const std::wstring& name)
   : m_ev(v), m_name(name), m_oldValue(v.get(name)) {}

   const std::wstring& value() const { return m_oldValue; }

   ~envVarMomento() { m_ev.set(m_name,m_oldValue); }

private:
   iEnvVar& m_ev;
   std::wstring m_name;
   std::wstring m_oldValue;
};

class envVar : public iEnvVar {
public:
   virtual std::wstring get(const std::wstring& name) const;
   virtual void set(const std::wstring& name, const std::wstring& value);
};
