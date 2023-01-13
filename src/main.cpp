#include "accumulator.hpp"
#include "cfile.hpp"
#include "checker.hpp"
#include "config.hpp"
#include "envvar.hpp"
#include "finder.hpp"
#include "log.hpp"
#include "split.hpp"
#include "subobject.hpp"
#include "vectorset.hpp"
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

// TODO add a report concept?  I.e. you now can call these EXEs

int main(int, const char *argv[])
{
   // basics
   streamLog log(std::cout);
   configInternal ci;
   config fig(ci);
   nullLog nowhere;

   // envvar + momento
   envVar ev;
   envVarMomento mom(ev,L"PATH");
   log.writeLn("old path was '%S'",mom.value().c_str());

   // split

   // attach accumulator
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

   // join

   // update env

   // create process

   // un-momento

   log.writeLn("usage: setupenv <cmd.exe> [--verbose]");
}
