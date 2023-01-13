#pragma once
#include <ostream>
#include <string>

class iLog {
public:
   virtual void writeLn(const std::string& fmt, ...) = 0;
};

class streamLog : public iLog {
public:
   explicit streamLog(std::ostream& out) : m_out(out) {}

   virtual void writeLn(const std::string& fmt, ...);

private:
   std::ostream& m_out;
};

class nullLog : public iLog {
public:
   virtual void writeLn(const std::string& fmt, ...) {}
};
