#include "accumulator.hpp"
#include "log.hpp"

void pathAccumulator::add(const std::wstring& path)
{
   log().writeLn("adding path '%S'",path.c_str());
   m_cont.appendIf(path);
}
