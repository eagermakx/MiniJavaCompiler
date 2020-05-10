//
// Created by Igor Maximov on 10.05.2020.
//

#pragma once

#include <string>

#include "Type/Type.h"

class FuncParameter {
 public:
  FuncParameter(Type* type, std::string name);
  
  Type* type;
  std::string name;
};
