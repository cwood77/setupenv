#pragma once
#include "subobject.hpp"
#include <string>

class spawner : public subobject {
public:
   void startAndWait(const std::wstring& shell) const;
};
