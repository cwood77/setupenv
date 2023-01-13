#include "accumulator.hpp"
#include "cfile.hpp"
#include "checker.hpp"
#include "config.hpp"
#include "finder.hpp"
#include "log.hpp"
#include "subobject.hpp"
#include <iostream>
#include <set>

class configInternal : public iConfigInternal {
public:
   virtual bool getBool(const std::string& name, bool defVal) const
   {
      return defVal;
   }

   virtual std::string getString(const std::string& name, const std::string& defVal) const
   {
      return defVal;
   }
};

int main(int, const char *argv[])
{
   // basics
   streamLog log(std::cout);
   configInternal ci;
   config fig(ci);
   nullLog nowhere;

   // accumulator
   pathAccumulator paths;
   paths.tie(fig,log);

   {
      // checker
      fileChecker checker;
      checker.tie(fig,nowhere);

      // finder
      folderFinder finder;
      finder.tie(fig,nowhere);
      finder.find(checker,paths);
   }

   log.writeLn("usage: setupenv <cmd.exe> [--verbose]");
}
