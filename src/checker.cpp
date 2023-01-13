#include "cfile.hpp"
#include "checker.hpp"
#include "log.hpp"
#include <cstring>

bool fileChecker::shouldAddToPath(const folder& f) const
{
   for(auto fileName : f.exeNames)
   {
      auto fullPath = f.folderPath + L"\\" + fileName;
      if(shouldAddToPath(fullPath))
         return true;
   }
   return false;
}

bool fileChecker::shouldAddToPath(const std::wstring& fullExePath) const
{
   cfile f(fullExePath,L"rb");
   winPeReader reader(f.fp());
   return subtie(reader).isConsoleSubsystem();
}

bool winPeReader::isConsoleSubsystem()
{
   cfile f(m_fp);

   // lookup offset to PE header (after DOS shim)
   f.seek(0x3c);
   auto offset = f.read<unsigned long>();

   // verify PE header
   f.seek(offset);
   char actual[4];
   actual[0] = f.read<char>();
   actual[1] = f.read<char>();
   actual[2] = f.read<char>();
   actual[3] = f.read<char>();
   char expected[] = { 'P', 'E', 0, 0 };
   if(::strncmp(actual,expected,4)!=0)
   {
      log().writeLn("bad PE header signature (%s)",actual);
      throw std::runtime_error("EXE file bad format?");
   }

   // skip past the COFF header
   auto x = f.tell();
   const long coffHeaderSize = 20;
   x += coffHeaderSize;
   f.seek(x);

   // examine the optional header for sanity
   auto magic = f.read<short>();
   log().writeLn("magic is %hx",magic);

   // pull the subsystem from the optional header
   x = f.tell();
   const long optHeader_subsysOffset = 68;
   x += (optHeader_subsysOffset - sizeof(short));
   f.seek(x);

   auto subsys = f.read<short>();
   log().writeLn("subsystem is %hd",subsys);

   return subsys == 3; // WINDOWS_CUI
}
