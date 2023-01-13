#pragma once
#include "subobject.hpp"

class folder;
class iFileChecker;
class iPathAccumulator;

class iFolderFinder {
public:
   virtual void find(iFileChecker& fchk, iPathAccumulator& pa) = 0;
};

class folderFinder : public iFolderFinder, public subobject {
public:
   virtual void find(iFileChecker& fchk, iPathAccumulator& pa);

private:
   void populate(folder& f);
};
