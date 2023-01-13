#pragma once
#include "subobject.hpp"
#include <set>
#include <stdio.h>
#include <string>

class folder {
public:
   std::wstring folderPath;
   std::set<std::wstring> exeNames;
};

class iFileChecker : public virtual iSubobject {
public:
   virtual bool shouldAddToPath(const folder& f) const = 0;
};

class fileChecker : public iFileChecker, public virtual subobject {
public:
   virtual bool shouldAddToPath(const folder& f) const;

private:
   bool shouldAddToPath(const std::wstring& fullExePath) const;
};

class winPeReader : public subobject {
public:
   explicit winPeReader(FILE *fp) : m_fp(fp) {}

   bool isConsoleSubsystem();

private:
   FILE *m_fp;
};
