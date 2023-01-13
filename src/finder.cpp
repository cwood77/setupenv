#define WIN32_LEAN_AND_MEAN
#include "accumulator.hpp"
#include "checker.hpp"
#include "finder.hpp"
#include "log.hpp"
#include <string>
#include <windows.h>

void folderFinder::find(iFileChecker& fchk, iPathAccumulator& pa)
{
   std::wstring exePath;
   {
      wchar_t buffer[MAX_PATH];
      ::GetModuleFileNameW(NULL,buffer,MAX_PATH);
      exePath = buffer;
   }
   log().writeLn("exe path is '%S'",exePath.c_str());

   auto pattern = exePath + L"\\..\\..\\*";
   log().writeLn("pattern is '%S'",pattern.c_str());
   WIN32_FIND_DATAW fData;
   HANDLE hFind = ::FindFirstFileW(pattern.c_str(),&fData);
   if(hFind == INVALID_HANDLE_VALUE)
      return;
   do
   {
      if(fData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      {
         if(::wcscmp(fData.cFileName,L".")==0)
            continue;
         if(::wcscmp(fData.cFileName,L"..")==0)
            continue;

         folder f;
         f.folderPath = exePath + L"\\..\\..\\" + fData.cFileName;
         log().writeLn("checking folder '%S'",f.folderPath.c_str());
         populate(f);
         log().writeLn("  found %lu candidate EXEs",f.exeNames.size());
         if(fchk.shouldAddToPath(f))
            pa.add(f.folderPath);
      }
   } while(::FindNextFileW(hFind,&fData));
   ::FindClose(hFind);
}

void folderFinder::populate(folder& f)
{
   auto pattern = f.folderPath + L"\\*.exe";
   WIN32_FIND_DATAW fData;
   HANDLE hFind = ::FindFirstFileW(pattern.c_str(),&fData);
   if(hFind == INVALID_HANDLE_VALUE)
      return;
   do
   {
      if(fData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
         continue;
      f.exeNames.insert(fData.cFileName);
   } while(::FindNextFileW(hFind,&fData));
   ::FindClose(hFind);
}
