#pragma once
#include <cstdio>
#include <stdexcept>
#include <string>

class cfile {
public:
   explicit cfile(FILE *fp) : m_fp(fp), m_own(false) {}

   cfile(const std::wstring& path, const std::wstring& mode)
   {
      m_fp = ::_wfopen(path.c_str(),mode.c_str());
      if(!m_fp)
         throw std::runtime_error("can't open file");
      m_own = true;
   }

   ~cfile() { if(m_own) ::fclose(m_fp); }

   template<class T> T read()
   {
      T obj;
      auto rVal = ::fread(&obj,sizeof(T),1,m_fp);
      if(rVal != 1)
         throw std::runtime_error("failed to read from file");
      return obj;
   }

   void seek(long offset)
   {
      auto zero = ::fseek(m_fp,offset,SEEK_SET);
      if(zero != 0)
         throw std::runtime_error("failed to seek");
   }

   long tell()
   {
      auto r = ::ftell(m_fp);
      if(r == -1L)
         throw std::runtime_error("failed to tell");
      return r;
   }

   FILE *fp() { return m_fp; }

private:
   FILE *m_fp;
   bool m_own;
};
