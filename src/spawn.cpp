#define WIN32_LEAN_AND_MEAN
#include "spawn.hpp"
#include <stdexcept>
#include <windows.h>

namespace {

template<class T>
class zeroed {
public:
   zeroed() { ::memset(&buf,0,sizeof(T)); }

   T buf;
};

} // anonymous namespace

void spawner::startAndWait(const std::wstring& shell) const
{
   zeroed<STARTUPINFOW> si;
   si.buf.cb = sizeof(STARTUPINFOW);
   zeroed<PROCESS_INFORMATION> pi;

   std::wstring copy = shell.c_str();
   auto success = ::CreateProcessW(
      NULL,                               // No module name (use command line)
      const_cast<wchar_t*>(copy.c_str()), // Command line
      NULL,                               // Process handle not inheritable
      NULL,                               // Thread handle not inheritable
      FALSE,                              // Set handle inheritance to FALSE
      0,                                  // No creation flags
      NULL,                               // Use parent's environment block
      NULL,                               // Use parent's starting directory
      &si.buf,                            // Pointer to STARTUPINFO structure
      &pi.buf);                           // Pointer to PROCESS_INFORMATION structure
   if(!success)
      throw std::runtime_error("failed to create nested shell process");

   // Wait until child process exits.
   ::WaitForSingleObject(pi.buf.hProcess,INFINITE);

   // Close process and thread handles. 
   ::CloseHandle(pi.buf.hProcess);
   ::CloseHandle(pi.buf.hThread);
}
