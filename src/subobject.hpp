#pragma once
#include <cstddef>

class config;
class iLog;

class iSubobject {
public:
   virtual void tie(const config& c, iLog& l) = 0;
};

class subobject : public virtual iSubobject {
public:
   subobject() : m_pFig(NULL), m_pLog(NULL) {}

   virtual void tie(const config& c, iLog& l) { m_pFig = &c; m_pLog = &l; }

protected:
   const config& fig() const { return *m_pFig; }
   iLog& log() const { return *m_pLog; }

   template<class T>
   T& subtie(T& o) const { o.tie(fig(),log()); return o; }

private:
   const config *m_pFig;
   iLog *m_pLog;
};
