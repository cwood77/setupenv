#include "accumulator.hpp"
#include "cfile.hpp"
#include "checker.hpp"
#include "config.hpp"
#include "envvar.hpp"
#include "finder.hpp"
#include "log.hpp"
#include "spawn.hpp"
#include "split.hpp"
#include "subobject.hpp"
#include "vectorset.hpp"
#include <iostream>
#include <set>

static const strConfig kCfgShell("shell",L"cmd.exe");

class configInternal : public iConfigInternal {
public:
   virtual bool getBool(const std::string& name, bool defVal) const
   {
      return defVal;
   }

   virtual std::wstring getString(const std::string& name, const std::wstring& defVal) const
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

   // envvar + momento
   envVar ev;
   {
      envVarMomento pathMom(ev,L"PATH");

      // split
      wivectorSet paths;
      splitter::split(pathMom.value(),paths);

      // attach accumulator
      pathAccumulator accum(paths);
      accum.tie(fig,log);

      {
         // checker
         fileChecker checker;
         checker.tie(fig,nowhere);

         // finder
         folderFinder finder;
         finder.tie(fig,nowhere);
         finder.find(checker,accum);
      }

      // join
      auto newPath = splitter::join(paths);

      // update env
      ev.set(L"PATH",newPath);

      // create process
      log.writeLn("---entering nested shell; remember to EXIT to return");
      spawner spn;
      spn.tie(fig,log);
      spn.startAndWait(fig.get(kCfgShell));
      log.writeLn("---leaving nested shell");

      // un-momento
   }
}
